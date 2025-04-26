import mysql.connector
from mysql.connector import Error

def connect_to_db():
    try:
        # Connect to MySQL
        conn = mysql.connector.connect(
            host="127.0.0.1",      # or your server IP
            user="root",           # your MySQL username
            password="mannan227",  # your MySQL password
            database="secure_connection_db"  # your database name
        )
        print("Database connection successful")
        return conn
    except Error as e:
        print(f"Error: {e}")
        return None

def fetch_and_format_sql_to_html():
    conn = connect_to_db()

    if conn is None:
        return  # Exit if connection failed

    cursor = conn.cursor()

    try:
        cursor.execute("SELECT * FROM users")
        users = cursor.fetchall()

        print(f"Fetched {len(users)} users")  # Debug: how many users were fetched

        # HTML header
        html_output = "<html><head><title>Users Table</title></head><body>"
        html_output += "<h1>Users</h1>"
        html_output += "<table border='1'><tr><th>ID</th><th>Username</th><th>Email</th><th>Password</th></tr>"

        # Loop through users and build HTML table
        for user in users:
            html_output += f"<tr><td>{user[0]}</td><td>{user[1]}</td><td>{user[2]}</td><td>{user[3]}</td></tr>"

        html_output += "</table></body></html>"

        # Output the HTML to a file
        with open("output.html", "w") as file:
            file.write(html_output)
        print("HTML file generated successfully: output.html")

    except Error as e:
        print(f"Error fetching data: {e}")
    finally:
        cursor.close()
        conn.close()

if __name__ == "__main__":
    fetch_and_format_sql_to_html()

