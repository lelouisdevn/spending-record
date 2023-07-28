#include "iostream"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/statement.h>

using namespace std;
int main() {
    try {
        sql::Driver *driver;
        sql::Connection *con;
        sql::Statement *stmt;

        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "");
        con->setSchema("spending-record");

        stmt = con->createStatement();
        stmt->execute("DROP TABLE IF EXISTS user");
        const string create_user_query = "CREATE TABLE user(userId INT PRIMARY KEY AUTO_INCREMENT, username VARCHAR(20),"
                                        "password VARCHAR(20), email VARCHAR(40), signedUpAt VARCHAR(30), isVerified INT)";
        stmt->execute(create_user_query);

        string insert_user_info = "INSERT INTO user (username, password, email, signedUpAt, isVerified) VALUES (\"thaingo\", "
                                        "\"thai123\", \"thaingo1202@outlook.com\", \"19:53 - 28/07/2023\", 0)";
        stmt->execute(insert_user_info);

        insert_user_info = "INSERT INTO user (username, password, email, signedUpAt, isVerified) VALUES (\"vanA\", "
                                        "\"abc1\", \"vana@example.com\", \"22:37 - 28/07/2023\", 0)";
        stmt->execute(insert_user_info);
        
        delete stmt;
        delete con;
    }catch(sql::SQLException &e) {
        cout << e.what() << endl;
    }
}