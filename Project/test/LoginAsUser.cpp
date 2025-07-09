#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

using namespace std;

const char Encryption_key = 'K';

struct User { // Kheang Ann
    string username;
    string password;
    User* prev;
    User* next;
};

struct Userlist {
    int n;
    User* head;
    User* tail;
};

Userlist* createList() {
    Userlist* ls = new Userlist;
    ls->n = 0;
    ls->head = nullptr;
    ls->tail = nullptr;
    return ls;
}

void AddEnd(Userlist* ls, string username, string password) {
    User* user = new User;
    user->username = username;
    user->password = password;
    user->next = nullptr;
    user->prev = ls->tail;

    if (ls->n == 0) {
        ls->head = user;
    } else {
        ls->tail->next = user;
    }
    ls->tail = user;
    ls->n++;
}

string encryptPassword(const string& password) {
    string encrypted = password;
    for (char& ch : encrypted) {
        ch ^= Encryption_key;
    }
    return encrypted;
}

string decryptPassword(const string& encrypted) {
    return encryptPassword(encrypted);
}

void DisplayUsername(Userlist* ls) {
    User* user = ls->head;
    while (user != nullptr) {
        cout << "Username: " << user->username << ", Password: " << user->password << endl;
        user = user->next;
    }
}

void addUserToFile(const string& username, const string& password) {
    ofstream user("../data/userdata.txt", ios::app);
    if (user.is_open()) {
        user << username << " " << encryptPassword(password) << "\n";
        user.close();
    } else {
        cout << "Error writing to file.\n";
    }
}

void loadUsersFromFile(Userlist* ls) {
    ifstream user("../data/userdata.txt");
    if (!user) {
        cout << "Error loading file.\n";
        return;
    }

    string username, encryptedPassword;
    while (user >> username >> encryptedPassword) {
        string decrypted = decryptPassword(encryptedPassword);
        AddEnd(ls, username, decrypted);
    }
    user.close();
}

string getMaskedPassword(const string& prompt) {
    string password;
    char ch;

    cout << prompt;
    while (true) {
        ch = _getch();
        if (ch == 13) {
            cout << endl;
            break;
        }
        else if (ch == 10) {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else {
            password += ch;
            cout << '*';
        }
    }
    return password;
}

int main() {
    Userlist* users = createList();
    loadUsersFromFile(users);

    string username, pw1, pw2;
    bool running = true;

    do {
        cout << "Enter username: ";
        getline(cin, username);

        pw1 = getMaskedPassword("Create your own password: ");
        pw2 = getMaskedPassword("Confirm password: ");

        if (pw1 == pw2) {
            AddEnd(users, username, pw1);
            addUserToFile(username, pw1);
            running = false;
        } else {
            cout << "Password Doesn't Match! Try Again!" << endl;
        }
    } while (running);

    cout << "\nCurrent Users:\n";
    DisplayUsername(users);

    return 0;
}
