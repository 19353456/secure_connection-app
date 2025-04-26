import mysql.connector

def connect_to_db():
    # Connect to MySQL
    conn = mysql.connector.connect(
        host="127.0.0.1",      # or your server IP
        user="root",           # your MySQL username
        password="mannan227",  # your MySQL password
        database="secure_connection_db"  # your database name
    )
    return conn

def fetch_users():
    conn = connect_to_db()
    cursor = conn.cursor()

    cursor.execute("SELECT * FROM users")
    users = cursor.fetchall()

    print("Users:")
    for user in users:
        print(user)  # This will print the entire row from the 'users' table

    cursor.close()
    conn.close()

if __name__ == "__main__":
    fetch_users()
