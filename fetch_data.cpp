#include <iostream>
#include <mysql/mysql.h>  // Make sure to include the correct path for the MySQL library

using namespace std;

int main() {
    // Basic HTML structure and CSS for styling
    cout << "Content-type: text/html\n\n";
    cout << "<html><head><style>"
         << "body { font-family: Arial, sans-serif; }"
         << "ul { list-style-type: none; padding: 0; }"
         << "li { margin: 5px; padding: 5px; background-color: #f4f4f4; border: 1px solid #ddd; }"
         << "</style></head><body>";

    cout << "<h2>Users List</h2><ul>";

    MYSQL *conn;
    MYSQL_ROW row;
    MYSQL_RES *res;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        cout << "<p>Error initializing database connection: " << mysql_error(conn) << "</p>";
        return 1;
    }

    // Update connection details with the correct password and database name
    if (mysql_real_connect(conn, "127.0.0.1", "root", "mannan22", "secure_connection_db", 0, NULL, 0)) {
        
        // SQL query to fetch username, password_hash, and role
        mysql_query(conn, "SELECT username, password_hash, role FROM users;");
        res = mysql_store_result(conn);

        // Loop through the result set and display each row
        while ((row = mysql_fetch_row(res))) {
            // Display each user in a list item with their username and role
            cout << "<li><b>Username:</b> " << row[0] << " <b>Role:</b> " << row[2] 
                 << " <b>Password Hash:</b> " << row[1] << "</li>";
        }

        mysql_free_result(res);
    } else {
        // Print detailed error message if connection fails
        cout << "<p>Database connection failed: " << mysql_error(conn) << "</p>";
        cout << "<p>Error Code: " << mysql_errno(conn) << "</p>";
    }

    mysql_close(conn);  // Close the MySQL connection

    cout << "</ul></body></html>";

    return 0;
}
