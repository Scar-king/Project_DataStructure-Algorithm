#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>
#include <algorithm>
#include "../include/Design_Structure.h"
#include "../include/ProductList.h"

#include "Constants.h"

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

Userlist* createUserList() {
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
        cerr << "Error loading file.\n";
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

// Submenus of Admin Menu
void handleViewTableMenu() {
    bool backToAdminMenu = false;

    while(!backToAdminMenu) {
        system("cls");
        viewTableMenu();

        int tableOption;
        cin >> tableOption;

        switch(tableOption) {
            case 1: {
                ProductList *ls = createList();
                displayAdminProductList(ls);
                system("pause");
                break;
            }

            case 2: {
                ReportList *rl = createReportList();
                displayOverallReport(rl);
                system("pause");
                break;
            }

            case 3: {
                AdminHistoryStack *s = createEmptyStack();
                displayAllAdminHistory(s);
                system("pause");
                break;
            }

            case 0:
                backToAdminMenu = true;
                break;

            default:
                cout << "\n" << INDENT << " Invalid option. Please try again.\n";
                Sleep(1000);
                break;
        }
    }
}

void handleAdminMenu() {
    bool logout = false;

    while (!logout) {
        system("cls");
        menuForAdmin();

        int adminOption;
        cin >> adminOption;

        switch (adminOption) {
            case 2:  
                handleViewTableMenu();  
                break;

            case 0:
                logout = true;  
                system("cls");
                break;

            default:
                cout << "\n" << INDENT << " Invalid option. Please try again.\n";
                break;
        }
    }
}

void Authentication() {
    Userlist* users = createUserList();
    loadUsersFromFile(users);

    string username, pw1, pw2;
    char gender;
    int age;
    bool running = true;
    int choice;

    do {
        loginPageMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << INDENT << "Enter admin name: ";
                getline(cin, username);
                pw1 = getMaskedPassword(INDENT + "Enter password: ");

                if (username == AdminPassword && pw1 == AdminPassword) {
                    cout << "\n" << INDENT << " Admin Login successful!\n";
                    loading();
                    handleAdminMenu();

                } else {
                    cout << "\n" << INDENT << "Invalid admin credentials.\n";
                }
                break;

            case 2:
                cout << INDENT << "Enter username: ";
                getline(cin, username);

                if (username.empty() || any_of(username.begin(), username.end(), ::isdigit)) {
                    cout << "\n" << INDENT << "Invalid username. It should not be empty or contain numbers.\n";
                    break;
                }
            
                pw1 = getMaskedPassword(INDENT + "Enter your password: ");
                if (authenticateUser(users, username, pw1)) {
                    cout << "\n" << INDENT << " Login successful. Welcome, " << username << "!\n";
                } else {
                    cout << "\n" << INDENT << " Login failed. Username or password incorrect.\n";
                }
                break;

            case 3: {
                cout << INDENT << "Enter username: ";
                getline(cin, username);

                // Check username validity
                if (username.empty() || any_of(username.begin(), username.end(), ::isdigit)) {
                    cout << "\n" << INDENT << "Invalid username. It should not be empty or contain numbers.\n";
                    break;
                }
            
                cout << INDENT << "Enter gender(M/F): ";
                cin >> gender;
                gender = toupper(gender);
            
                cout << INDENT << "Enter age: ";
                cin >> age;
                cin.ignore();
            
                if (age <= 0 || age >= 100 || (gender != 'M' && gender != 'F')) {
                    cout << "\n" << INDENT << "Invalid age or gender input. Please try again.\n";
                    break;
                }
            
                int pw_attempts = 3;
                bool passwordMatched = false;
            
                while (pw_attempts-- > 0) {
                    pw1 = getMaskedPassword(INDENT + "Create your password: ");
                    pw2 = getMaskedPassword(INDENT + "Confirm password: ");
                
                    // Password strength check
                    if (pw1.length() < 4) {
                        cout << INDENT << "Password too short (min 4 characters). Try again.\n";
                        continue;
                    }
                
                    if (pw1 == pw2) {
                        passwordMatched = true;
                        break;
                    } else {
                        cout << INDENT << "Passwords do not match. ";
                        if (pw_attempts > 0)
                            cout << INDENT << "Try again (" << pw_attempts << " attempts left).\n";
                        else
                            cout << INDENT << "No attempts left. Registration canceled.\n";
                    }
                }
            
                if (passwordMatched) {
                    AddEnd(users, username, gender, age, pw1);
                    addUserToFile(username, gender, age, pw1);
                    cout << "\n" << INDENT << " Registration successful!\n";
                }
                break;
            }

            case 0:
                running = false;
                cout << "\n" << INDENT << " Thank you for using our system. Goodbye!\n";
                break;

            default:
                cout << "\n" << INDENT << " Invalid option. Please try again.\n";
                break;
        }
    } while (running);
}
