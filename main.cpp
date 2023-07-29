#include "iostream"
#include "user/user.cpp"

int menu();
string format_username(string);
void sign_up(User);
void login(User);
void call_to_method(int);
void add_new_record();
void view_today_records();
void manage_money_sources();
void log_out();
void manage_categories();
string format_username(string);


int menu() {
    int sl;
    cout << "|--------------------------------------|" << endl;
    cout << "|           spending records           |" << endl;
    cout << "|--------------------------------------|" << endl;
    cout << "|        1: Add new record             |" << endl;
    cout << "|        2: View today records         |" << endl;
    cout << "|        3: Manage sources             |" << endl;
    cout << "|        4: Log out                    |" << endl;
    cout << "|        5: Manage categories          |" << endl;
    cout << "|--------------------------------------|" << endl;
    cin >> sl;
    return sl;
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
void sign_up(User *u) {
    string usr, passwd, eml;

    cout << "Enter username: " << endl;
    getline(cin, usr);

    cout << "Enter email: " << endl;
    getline(cin, eml);

    cout << "Enter password: " << endl;
    getline(cin, passwd);

    // Create user with submitted info; save to database;
    u->updateAttrs(-1, format_username(usr), eml, passwd);
    u->signUp();
}

void log_in(User *u) {
    string u_e, passwd;

    cout << "Enter username or email: " << endl;
    getline(cin, u_e);

    cout << "Enter password: " << endl;
    getline(cin, passwd);

    u->updateAttrs(-1, u_e, u_e, passwd);
    u->logIn();
}
void log_out(User *u) {
    u->logOut();
}
void call_to_method(int option, User *u) {
    switch(option) {
        case 4:
            u->logOut();
            break;
    }
}
int main() {
    int start;
    cout << "|--------------------------|" << endl;
    cout << "|      spending records    |" << endl;
    cout << "|--------------------------|" << endl;
    cout << "|         1: Login         |" << endl;
    cout << "|         2: Sign Up       |" << endl;
    cout << "|--------------------------|" << endl;
    cin >> start; cin.ignore(1);
    User guest;
    
    switch(start) {
        case 1:
            log_in(&guest);
            break;
        case 2:
            sign_up(&guest);
            break;
        default:
            cout << "Invalid selected option!" << endl;
            break;
    }

    while (guest.isLoggedIn()) {
        int option = menu();
        call_to_method(option, &guest);
    }
}