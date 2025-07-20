#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>
#include <algorithm>
#include "../include/Design_Structure.h"

using namespace std;

const char Encryption_key = 'K';
const string AdminPassword = "admin";

struct User {
    string username;
    char gender;
    int age;
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

void AddEnd(Userlist* ls, string username, char gender, int age, string password) {
    User* user = new User{username, gender, age, password, ls->tail, nullptr};
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
        cout << "Username: " << user->username
             << ", Gender: " << user->gender
             << ", Age: " << user->age << endl;
        user = user->next;
    }
}

void addUserToFile(string username, char gender, int age, string password) {
    ofstream user("../data/userdata.csv", ios::app);
    if (user.is_open()) {
        user << username << "," << gender << "," << age << "," << encryptPassword(password) << "\n";
        user.close();
    } else {
        cout << "Error writing to file.\n";
    }
}

void loadUsersFromFile(Userlist* ls) {
    ifstream user("../data/userdata.csv");
    if (!user) {
        cout << "Error loading file.\n";
        return;
    }

    string line;
    while (getline(user, line)) {
        stringstream ss(line);
        string username, genderStr, ageStr, encryptedPassword;

        getline(ss, username, ',');
        getline(ss, genderStr, ',');
        getline(ss, ageStr, ',');
        getline(ss, encryptedPassword);

        if (username.empty() || genderStr.empty() || ageStr.empty() || encryptedPassword.empty()) continue;

        char gender = genderStr[0];
        int age = stoi(ageStr);
        string decryptedPassword = decryptPassword(encryptedPassword);

        AddEnd(ls, username, gender, age, decryptedPassword);
    }
    user.close();
}

bool authenticateUser(Userlist* ls, const string& username, const string& password) {
    User* current = ls->head;
    while (current) {
        if (current->username == username && current->password == password) {
            return true;
        }
        current = current->next;
    }
    return false;
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
        } else if (ch == 8) {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        } else {
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
    char gender;
    int age;
    bool running = true;
    int choice;

    do {
        cout << "\n+-----------------------------+\n";
        cout << "|     User Management System  |\n";
        cout << "+-----------------------------+\n";
        cout << "| 1. Administrator Login      |\n";
        cout << "| 2. User Login               |\n";
        cout << "| 3. Register New User        |\n";
        cout << "| 0. Exit Application         |\n";
        cout << "+-----------------------------+\n";
        cout << "Please select an option: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter admin name: ";
                getline(cin, username);
                pw1 = getMaskedPassword("Enter password: ");
                if (username == AdminPassword && pw1 == AdminPassword) {
                    cout << "\n Admin Login successful!\n";
                    DisplayUsername(users);

                    viewTableMenu();
                } else {
                    cout << "\n Invalid admin credentials.\n";
                }
                break;

            case 2:
                cout << "Enter username: ";
                getline(cin, username);

                if (username.empty() || any_of(username.begin(), username.end(), ::isdigit)) {
                    cout << "\nInvalid username. It should not be empty or contain numbers.\n";
                    break;
                }
            
                pw1 = getMaskedPassword("Enter your password: ");
                if (authenticateUser(users, username, pw1)) {
                    cout << "\n Login successful. Welcome, " << username << "!\n";
                } else {
                    cout << "\n Login failed. Username or password incorrect.\n";
                }
                break;

            case 3: {
                cout << "Enter username: ";
                getline(cin, username);

                // Check username validity
                if (username.empty() || any_of(username.begin(), username.end(), ::isdigit)) {
                    cout << "\nInvalid username. It should not be empty or contain numbers.\n";
                    break;
                }
            
                cout << "Enter gender(M/F): ";
                cin >> gender;
                gender = toupper(gender);
            
                cout << "Enter age: ";
                cin >> age;
                cin.ignore();
            
                if (age <= 0 || age >= 100 || (gender != 'M' && gender != 'F')) {
                    cout << "\nInvalid age or gender input. Please try again.\n";
                    break;
                }
            
                int pw_attempts = 3;
                bool passwordMatched = false;
            
                while (pw_attempts-- > 0) {
                    pw1 = getMaskedPassword("Create your password: ");
                    pw2 = getMaskedPassword("Confirm password: ");
                
                    // Password strength check
                    if (pw1.length() < 4) {
                        cout << "Password too short (min 4 characters). Try again.\n";
                        continue;
                    }
                
                    if (pw1 == pw2) {
                        passwordMatched = true;
                        break;
                    } else {
                        cout << "Passwords do not match. ";
                        if (pw_attempts > 0)
                            cout << "Try again (" << pw_attempts << " attempts left).\n";
                        else
                            cout << "No attempts left. Registration canceled.\n";
                    }
                }
            
                if (passwordMatched) {
                    AddEnd(users, username, gender, age, pw1);
                    addUserToFile(username, gender, age, pw1);
                    cout << "\n Registration successful!\n";
                }
                break;
            }

            case 0:
                running = false;
                cout << "\n Thank you for using our system. Goodbye!\n";
                break;

            default:
                cout << "\n Invalid option. Please try again.\n";
                break;
        }
    } while (running);

    return 0;
}
