#include <iostream>
#include <mysql/mysql.h>
#include <cstdlib>
#include <cstring>
#include <bcrypt.h>  // Secure password hashing

using namespace std;

int main() {
    cout << "Content-type: text/html\n\n";
    cout << "<html><body>";

    MYSQL *conn;
    conn = mysql_init(NULL);
    if (conn == NULL) {
        cout << "<p>Error initializing database connection.</p>";
        return 1;
    }

    if (!mysql_real_connect(conn, "127.0.0.1", "root", "mannan22", "secure_connection_db", 0, NULL, 0)) {
        cout << "<p>Database connection failed: " << mysql_error(conn) << "</p>";
        return 1;
    }

    // Read POST data from form
    char *content_length = getenv("CONTENT_LENGTH");
    if (!content_length) {
        cout << "<p>No input received.</p></body></html>";
        return 1;
    }

    int len = atoi(content_length);
    char post_data[len + 1];
    cin.read(post_data, len);
    post_data[len] = '\0';

    // Extract username, password, and role
    char *username = strstr(post_data, "username=") + 9;
    char *password = strstr(post_data, "password=") + 9;
    char *role = strstr(post_data, "role=") + 5;

    // Secure password hashing
    char hashed_password[64];
    bcrypt_hashpw(password, bcrypt_gensalt(10), hashed_password);

    // Securely insert new user into database
    char query[512];
    sprintf(query, "INSERT INTO users (username, password_hash, role) VALUES ('%s', '%s', '%s');", username, hashed_password, role);

    if (mysql_query(conn, query) == 0) {
        cout << "<p>User created successfully!</p>";
    } else {
        cout << "<p>Error creating user: " << mysql_error(conn) << "</p>";
    }

    mysql_close(conn);
    cout << "</body></html>";
    return 0;
}
