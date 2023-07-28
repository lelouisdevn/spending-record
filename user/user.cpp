#include "iostream"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

using namespace std;

sql::Driver *driver;
sql::Connection *con;
sql::PreparedStatement *pstmt;
sql::ResultSet *res;
class User {
    string userId;
    string username;
    string password;
    string email;
    string signedUpAt;
    bool isVerified;

    // ERRORS
    string errors[3] = {
        "", 
        "There's an account with this username, use a different one!",
        "There's an account with this email, use a different one!"
    };

public:
    User(string username, string email, string password) {
        this->username = username;
        this->email = email;
        this->password = password;
    }

    // Method to check if username or email exists in database;
    int isAccountExisted() {
        int response_code = 0;
        try {
            driver = get_driver_instance();
            con = driver->connect("tcp://127.0.0.1:3306", "root", "");
            con->setSchema("spending-record");

            pstmt = con->prepareStatement("SELECT * FROM user WHERE email=(?) OR username=(?)");
            pstmt->setString(1, this->email);
            pstmt->setString(2, this->username);
            res = pstmt->executeQuery();

            res->afterLast();
            while (res->previous()) {
                if (res->getString("username") == this->username) {
                    response_code = 1;
                }
                else if (res->getString("email") == this->email) {
                    response_code = 2;
                }
            }
        } catch (sql::SQLException &e) {
            cout << e.what() << endl;
        }
        return response_code;
    }
    void signUp() {
        int status = isAccountExisted();
        if (status == 0) {
            try {
                pstmt = con->prepareStatement("INSERT INTO user (username, password, email) VALUES (?, ?, ?)");
                pstmt->setString(1, username);
                pstmt->setString(2, password);
                pstmt->setString(3, email);

                status = pstmt->executeUpdate();
                if (!status) {
                    throw(status);
                }else {
                   cout << "Your account is created successfully!" << endl; 
                }
            }catch(int err) {
                cout << "There occured an error: " << err << endl;
            }
        } else {
            cout << this->errors[status] << endl;
        }
    }
};