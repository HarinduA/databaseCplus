#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/exception.h>

// Function to establish and return a database connection
sql::Connection* connectDatabase(const std::string& host, const std::string& user, const std::string& pass, const std::string& db) {
    try {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        sql::Connection* conn = driver->connect(host, user, pass);
        conn->setSchema(db);
        return conn;
    } catch (sql::SQLException& e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

// Function to insert data into the Users table
void addUser(sql::Connection* conn, const std::string& name, const std::string& email) {
    try {
        sql::PreparedStatement* pstmt = conn->prepareStatement("INSERT INTO Users (name, email) VALUES (?, ?)");
        pstmt->setString(1, name);
        pstmt->setString(2, email);
        pstmt->executeUpdate();
        delete pstmt;
        std::cout << "User added successfully!" << std::endl;
    } catch (sql::SQLException& e) {
        std::cerr << "SQL error: " << e.what() << std::endl;
    }
}

int main() {
    const std::string host = "tcp://127.0.0.1:3306"; // Change to your database host
    const std::string user = "root"; // Change to your database user
    const std::string pass = "password"; // Change to your database password
    const std::string db = "TestDB"; // Change to your database name

    sql::Connection* conn = connectDatabase(host, user, pass, db);

    std::string name, email;
    std::cout << "Enter user name: ";
    std::getline(std::cin, name);
    std::cout << "Enter user email: ";
    std::getline(std::cin, email);

    addUser(conn, name, email);

    delete conn;
    return 0;
}
