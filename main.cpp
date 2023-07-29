#include "iostream"
#include "user/user.cpp"
void menu() {
    cout << "----------------------------------" << endl;
    cout << "Add new record: 1" << endl;
    cout << "View records today: 2" << endl;
    cout << "View money sources: 3" << endl;
    cout << "----------------------------------" << endl;
}

// Remove whitespace from both ends; convert whitespace to '-';
string format_username(string usr) {
    if (usr[0] == ' ') 
        usr = usr.substr(1);

    if (usr[usr.length()-1] == ' ')
        usr = usr.substr(0, usr.length()-1);
    
    for (int i=0; i<usr.length(); i++)
        if (usr[i] == ' ')
            usr[i] = '-';

    return usr;
}
void signUp(User *u) {
    string usr, passwd, eml;

    cout << "Enter username: " << endl;
    getline(cin, usr);

    cout << "Enter email: " << endl;
    getline(cin, eml);

    cout << "Enter password: " << endl;
    getline(cin, passwd);

    // Create user with submitted info; save to database;
    u->update_attrs(-1, format_username(usr), eml, passwd);
    u->signUp();
}

void login(User *u) {
    string u_e, passwd;

    cout << "Enter username or email: " << endl;
    getline(cin, u_e);

    cout << "Enter password: " << endl;
    getline(cin, passwd);

    u->update_attrs(-1, u_e, u_e, passwd);
    u->login();
}

int main() {
    int start;
    cout << "------------------------" << endl;
    cout << "Login : 1" << endl;
    cout << "Sign up: 2" << endl;
    cout << "------------------------" << endl;
    cin >> start; cin.ignore(1);

    User guest;
    switch(start) {
        case 1:
            login(&guest);
            break;
        case 2:
            signUp(&guest);
            break;
    }

    guest.printInfo();
    // cout << format_username(" thai ngo ") << endl;
}