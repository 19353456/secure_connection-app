#include <mysql/mysql.h>
#include <iostream>
#include <cstring>

// Function to search providers based on skill and location
void search_providers(MYSQL *conn, const char* skill, const char* location) {
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *query = "SELECT name, skill, location FROM providers WHERE skill = ? AND location = ?";
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    if (!stmt) {
        std::cerr << "Failed to initialize statement: " << mysql_error(conn) << std::endl;
        return;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        std::cerr << "Failed to prepare statement: " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)skill;
    bind[0].buffer_length = strlen(skill);

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char *)location;
    bind[1].buffer_length = strlen(location);

    if (mysql_stmt_bind_param(stmt, bind)) {
        std::cerr << "Failed to bind parameters: " << mysql_error(conn) << std::endl;
        return;
    }

    if (mysql_stmt_execute(stmt)) {
        std::cerr << "Failed to execute statement: " << mysql_error(conn) << std::endl;
        return;
    }

    res = mysql_stmt_result_metadata(stmt);
    while ((row = mysql_fetch_row(res)) != NULL) {
        std::cout << row[0] << " " << row[1] << " " << row[2] << std::endl;
    }

    mysql_free_result(res);
    mysql_stmt_close(stmt);
}

// Function to update client details
void update_client_details(MYSQL *conn, int client_id, const char* new_email, const char* new_location) {
    const char *query = "UPDATE clients SET contact_details = ?, location = ? WHERE id = ?";
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    if (!stmt) {
        std::cerr << "Failed to initialize statement: " << mysql_error(conn) << std::endl;
        return;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        std::cerr << "Failed to prepare statement: " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_BIND bind[3];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)new_email;
    bind[0].buffer_length = strlen(new_email);

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char *)new_location;
    bind[1].buffer_length = strlen(new_location);

    bind[2].buffer_type = MYSQL_TYPE_LONG;
    bind[2].buffer = &client_id;

    if (mysql_stmt_bind_param(stmt, bind)) {
        std::cerr << "Failed to bind parameters: " << mysql_error(conn) << std::endl;
        return;
    }

    if (mysql_stmt_execute(stmt)) {
        std::cerr << "Failed to execute statement: " << mysql_error(conn) << std::endl;
    }

    mysql_stmt_close(stmt);
}

// Function to update provider details
void update_provider_details(MYSQL *conn, int provider_id, const char* new_service_type, const char* new_location) {
    const char *query = "UPDATE providers SET service_type = ?, location = ? WHERE id = ?";
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    if (!stmt) {
        std::cerr << "Failed to initialize statement: " << mysql_error(conn) << std::endl;
        return;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        std::cerr << "Failed to prepare statement: " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_BIND bind[3];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)new_service_type;
    bind[0].buffer_length = strlen(new_service_type);

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char *)new_location;
    bind[1].buffer_length = strlen(new_location);

    bind[2].buffer_type = MYSQL_TYPE_LONG;
    bind[2].buffer = &provider_id;

    if (mysql_stmt_bind_param(stmt, bind)) {
        std::cerr << "Failed to bind parameters: " << mysql_error(conn) << std::endl;
        return;
    }

    if (mysql_stmt_execute(stmt)) {
        std::cerr << "Failed to execute statement: " << mysql_error(conn) << std::endl;
    }

    mysql_stmt_close(stmt);
}

// Function to create a new user (admin functionality)
void create_user(MYSQL *conn, const char* username, const char* password, const char* role) {
    const char *query = "INSERT INTO users (username, password, role) VALUES (?, ?, ?)";
    MYSQL_STMT *stmt = mysql_stmt_init(conn);
    if (!stmt) {
        std::cerr << "Failed to initialize statement: " << mysql_error(conn) << std::endl;
        return;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        std::cerr << "Failed to prepare statement: " << mysql_error(conn) << std::endl;
        return;
    }

    MYSQL_BIND bind[3];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].buffer_length = strlen(username);

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char *)password;
    bind[1].buffer_length = strlen(password);

    bind[2].buffer_type = MYSQL_TYPE_STRING;
    bind[2].buffer = (char *)role;
    bind[2].buffer_length = strlen(role);

    if (mysql_stmt_bind_param(stmt, bind)) {
        std::cerr << "Failed to bind parameters: " << mysql_error(conn) << std::endl;
        return;
    }

    if (mysql_stmt_execute(stmt)) {
        std::cerr << "Failed to execute statement: " << mysql_error(conn) << std::endl;
    }

    mysql_stmt_close(stmt);
}

int main() {
    MYSQL *conn;

    // Connect to the MySQL database
    conn = mysql_init(NULL);
    if (conn == NULL) {
        std::cerr << "mysql_init() failed\n" << std::endl;
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, "localhost", "root", "analysis", "secure_connections", 0, NULL, 0) == NULL) {
        std::cerr << "MySQL connection failed: " << mysql_error(conn) << std::endl;
        return EXIT_FAILURE;
    }

    // Call functions as needed
    // For example, to search for providers:
    search_providers(conn, "plumbing", "New York");

    // To update a client
    update_client_details(conn, 1, "newemail@example.com", "Los Angeles");

    // To update a provider
    update_provider_details(conn, 1, "Electrician", "San Francisco");

    // To create a new user (admin)
    create_user(conn, "newuser", "newpassword", "client");

    // Close MySQL connection
    mysql_close(conn);
    return 0;
}
