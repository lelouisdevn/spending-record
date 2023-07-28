#include "iostream"
#include "user/user.cpp"

void signUp() {
    string username, password, email;

    cout << "Enter username: " << endl;
    getline(cin, username);

    cout << "Enter email: " << endl;
    getline(cin, email);

    cout << "Enter password: " << endl;
    getline(cin, password);

    // Create user with submitted info; save to database;
    User new_user(username, email, password);
    new_user.signUp();
}

void login() {

}

void menu() {

}

int main() {
    int start;
    cout << "------------------------" << endl;
    cout << "LOGIN : 1" << endl;
    cout << "SIGN UP: 2" << endl;
    cout << "------------------------" << endl;
    cin >> start; cin.ignore(1);

    switch(start) {
        case 1:
            login();
            break;
        case 2:
            signUp();
            break;
    }
}