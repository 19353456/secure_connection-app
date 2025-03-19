#include <cgicc/Cgicc.h>
#include <cgicc/HTMLClasses.h>
#include <mysql/mysql.h>
#include <iostream>
#include <string>

using namespace cgicc;

void display_providers(MYSQL *conn) {
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Execute SQL query
    const char *query = "SELECT name, skill, location FROM providers";
    if (mysql_query(conn, query)) {
        std::cerr << "Query failed: " << mysql_error(conn) << std::endl;
        return;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        std::cerr << "Store result failed: " << mysql_error(conn) << std::endl;
        return;
    }

    // Start HTML template and table
    std::cout << "Content-Type: text/html\n\n";  // Important for CGI scripts to return HTML
    std::cout << "<html><body><h2>List of Providers</h2><table border='1'>"
              << "<tr><th>Provider Name</th><th>Skill</th><th>Location</th></tr>";

    // Fetch and display each row dynamically
    while ((row = mysql_fetch_row(res)) != NULL) {
        std::cout << "<tr><td>" << row[0] << "</td><td>" << row[1] << "</td><td>" << row[2] << "</td></tr>";
    }

    std::cout << "</table></body></html>";

    mysql_free_result(res);
}

int main() {
    Cgicc form;
    MYSQL *conn;

    // Connect to the database
    conn = mysql_init(NULL);
    if (conn == NULL) {
        std::cerr << "MySQL initialization failed" << std::endl;
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, "localhost", "root", "analysis", "secure_connections", 0, NULL, 0) == NULL) {
        std::cerr << "MySQL connection failed: " << mysql_error(conn) << std::endl;
        return EXIT_FAILURE;
    }

    // Call the function to display the providers in HTML
    display_providers(conn);

    mysql_close(conn);
    return EXIT_SUCCESS;
}
