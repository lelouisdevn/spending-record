// #include "iostream"
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
class User
{
    int userId;
    string username;
    string password;
    string email;
    string signedUpAt;
    
    // ERRORS
    string errors[3] = {
        "",
        "There's an account with this username, use a different one!",
        "There's an account with this email, use a different one!"};

public:
    User()
    {
        userId = -1;
        username = "";
        password = "";
        email = "";
        signedUpAt = "";
    }
    User(string username, string email, string password)
    {
        this->username = username;
        this->email = email;
        this->password = password;
    }
    User(User &u) {
        userId = u.userId;
        username  = u.username;
        email = u.email;
    }
    void printInfo();
    int isDataAvailable();
    void signUp();
    void logIn();
    void logOut();
    int isLoggedIn();
    void updateAttrs(int, string, string, string, string);
};
void User::printInfo()
{
    cout << username << " " << email << endl;
}
void User::updateAttrs(int uid, string usr, string eml, string passwd, string at)
{
    userId = uid;
    username = usr;
    email = eml;
    password = passwd;
    signedUpAt = at;
}
int User::isLoggedIn()
{
    return (userId != -1 ? 1 : 0);
}
void User::logOut()
{
    updateAttrs(-1, "", "", "", "");
    // delete this;
}
void User::logIn()
{
    try
    {
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "");
        con->setSchema("spending-record");

        pstmt = con->prepareStatement("SELECT * FROM user WHERE (email=(?) OR username=(?)) AND password=(?)");
        pstmt->setString(1, email);
        pstmt->setString(2, username);
        pstmt->setString(3, password);

        res = pstmt->executeQuery();
        if (res->next())
        {
            int uid = res->getInt("userId");
            string usr = res->getString("username");
            string eml = res->getString("email");
            string sgUpAt = res->getString("signedUpAt");
            updateAttrs(uid, usr, eml, "", sgUpAt);
        }
        else
        {
            cout << "Wrong login information!" << endl;
        }
    }
    catch (sql::SQLException &e)
    {
        cout << e.what() << endl;
    }
}
void User::signUp()
{
    int status = isDataAvailable();
    switch (status)
    {
    case 0:
        try
        {
            pstmt = con->prepareStatement("INSERT INTO user (username, password, email, signedUpAt) VALUES (?, ?, ?, ?)");
            pstmt->setString(1, username);
            pstmt->setString(2, password);
            pstmt->setString(3, email);
            pstmt->setString(4, signedUpAt);

            status = pstmt->executeUpdate();
            if (!status)
            {
                throw(status);
            }
            else
            {
                cout << "Your account is created successfully!" << endl;
                logIn();
            }
        }
        catch (int err)
        {
            cout << "There occured an error: " << err << endl;
        }
        break;
    case 1:
    case 2:
        cout << this->errors[status] << endl;
        break;
    default:
        cout << "Undefined error occured!" << endl;
        break;
    }
}


// Check the availability of username and email;
int User::isDataAvailable()
{
    int response_code = 0;
    try
    {
        driver = get_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", "root", "");
        con->setSchema("spending-record");

        pstmt = con->prepareStatement("SELECT * FROM user WHERE email=(?) OR username=(?)");
        pstmt->setString(1, this->email);
        pstmt->setString(2, this->username);
        res = pstmt->executeQuery();

        res->afterLast();
        while (res->previous())
        {
            if (res->getString("username") == this->username)
            {
                response_code = 1;
            }
            else if (res->getString("email") == this->email)
            {
                response_code = 2;
            }
        }
    }
    catch (sql::SQLException &e)
    {
        cout << e.what() << endl;
    }
    return response_code;
}