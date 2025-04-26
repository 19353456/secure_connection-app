#include <iostream>
#include <mysql/mysql.h>
#include <cstdlib>
#include <cstring>
#include <string>

using namespace std;

// Function to extract query parameters (e.g., provider_id) from the URL
std::string get_query_param(const std::string& param) {
    const char *query_string = getenv("QUERY_STRING");  // Get query string from environment variable
    if (query_string != NULL) {
        std::string query(query_string);
        size_t param_pos = query.find(param + "=");  // Find the position of "provider_id="
        if (param_pos != std::string::npos) {
            size_t start = param_pos + param.length() + 1; // Move to value part
            size_t end = query.find("&", start); // Find next "&" or end of string
            if (end == std::string::npos) {
                return query.substr(start); // Return value till end
            }
            return query.substr(start, end - start);
        }
    }
    return ""; // Return empty string if parameter is not found
}

int main() {
    // ✅ Step 1: Print HTTP Header (Required for CGI)
    cout << "Content-type: text/html\n\n";
    cout << "<html><body>";

    // ✅ Step 2: Get the provider_id from the URL
    std::string provider_id = get_query_param("provider_id");

    if (provider_id.empty()) {  // If no provider_id was provided
        cout << "<h1>No provider ID provided. Please add '?provider_id=1' to the URL.</h1></body></html>";
        return 1;
    }

    // ✅ Step 3: Initialize MySQL Connection
    MYSQL *conn;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[1];  // To bind the provider_id
    MYSQL_BIND result_bind[3];  // To store query results

    conn = mysql_init(NULL);
    if (conn == NULL) {
        cout << "<p>mysql_init() failed</p></body></html>";
        return 1;
    }

    // ✅ Step 4: Connect to MariaDB/MySQL Server
    if (mysql_real_connect(conn, "localhost", "mannan", "mannan22", "secure_connection_db", 0, NULL, 0) == NULL) {
        cout << "<p>mysql_real_connect() failed: " << mysql_error(conn) << "</p></body></html>";
        mysql_close(conn);
        return 1;
    }

    // ✅ Step 5: Prepare the SQL Query (Prevent SQL Injection)
    const char *query = "SELECT request_id, client_id, status FROM requests WHERE provider_id = ?";
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        cout << "<p>mysql_stmt_init() failed</p></body></html>";
        mysql_close(conn);
        return 1;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        cout << "<p>mysql_stmt_prepare() failed: " << mysql_stmt_error(stmt) << "</p></body></html>";
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return 1;
    }

    // ✅ Step 6: Bind provider_id Parameter (Prevent SQL Injection)
    memset(bind, 0, sizeof(bind));
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)provider_id.c_str();
    bind[0].buffer_length = provider_id.length();

    if (mysql_stmt_bind_param(stmt, bind)) {
        cout << "<p>mysql_stmt_bind_param() failed: " << mysql_stmt_error(stmt) << "</p></body></html>";
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return 1;
    }

    // ✅ Step 7: Execute Query
    if (mysql_stmt_execute(stmt)) {
        cout << "<p>mysql_stmt_execute() failed: " << mysql_stmt_error(stmt) << "</p></body></html>";
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return 1;
    }

    // ✅ Step 8: Bind Result Variables
    int request_id, client_id;
    char status[20];  // Assuming status is within 20 characters

    memset(result_bind, 0, sizeof(result_bind));

    result_bind[0].buffer_type = MYSQL_TYPE_LONG;
    result_bind[0].buffer = &request_id;

    result_bind[1].buffer_type = MYSQL_TYPE_LONG;
    result_bind[1].buffer = &client_id;

    result_bind[2].buffer_type = MYSQL_TYPE_STRING;
    result_bind[2].buffer = status;
    result_bind[2].buffer_length = sizeof(status);

    if (mysql_stmt_bind_result(stmt, result_bind)) {
        cout << "<p>mysql_stmt_bind_result() failed: " << mysql_stmt_error(stmt) << "</p></body></html>";
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return 1;
    }

    // ✅ Step 9: Fetch and Display Results
    cout << "<h2>Requests Assigned to You</h2><ul>";
    while (mysql_stmt_fetch(stmt) == 0) {
        cout << "<li><b>Request ID:</b> " << request_id
             << " - <b>Client ID:</b> " << client_id
             << " - <b>Status:</b> " << status << "</li>";
    }
    cout << "</ul>";

    // ✅ Step 10: Cleanup and Close Connections
    mysql_stmt_close(stmt);
    mysql_close(conn);

    cout << "</body></html>";
    return 0;
}
