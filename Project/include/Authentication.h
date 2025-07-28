#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <iomanip>
#include <conio.h>
#include <algorithm>
#include "../include/Design_Structure.h"
#include "../include/ProductList.h"

#include "Constants.h"

using namespace std;

// GLOBAL VAR
ProductList *ls = createList();
ReportList *rl = createReportList();
AdminHistoryStack *s = createEmptyStack();

// Forward declare so compiler knows this exists
// void storeProduct(ProductList *ls);

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
                displayAdminProductList(ls);
                system("pause");
                break;
            }

            case 2: {
                quickSort(ls);
                displayAdminProductList(ls);
                system("pause");
                break;
            }

            case 3: {
                quickSort(ls, true); // Sort by lowest to highest
                displayAdminProductList(ls);
                system("pause");
                break;
            }

            case 4: {

                ProductElement *temp = ls->head;
                while(temp != nullptr) {
                    addReport(rl, temp);
                    temp = temp->next;
                }

                displayOverallReport(rl);
                graphVisualization(rl);
                system("pause");
                break;
            }

            case 5: {

                displayAllAdminHistory(s);

                system("pause");
                break;
            }

            case 6: {
                system("cls");

                displayBestSelling(ls);

                system("pause");
                break;
            }

            // case 7:

            //     displayLastMonthHistory(s);
            //     system("pause");
            //     break;

            // case 8: 
            //     displayLastDayHistory(s);
            //     system("pause");
            //     break;
            
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

void backupAndRestoreMenu(ProductList *ls) {
    int choice;
    do {
        menuForBackupAndRestore();

        cin >> choice;

        switch(choice) {
            case 1:
                storeProduct(ls);
                backupProductData(ls);
                system("pause");
                break;
            case 2:
                restoreProductData(ls);
                system("pause");
                break;
            case 0:
                break;
            default:
                cout << RED << INDENT << "Invalid choice. Try again...\n" << RESET;
        }
    } while(choice != 0);
}

void handleAdminMenu(string username) {
    bool logout = false;
    loadProductList(ls);
    loadAdminHistoryStack(s);

    while (!logout) {
        system("cls");
        menuForAdmin();

        int adminOption;
        cin >> adminOption;

        switch (adminOption) {
            case 1:{

                system("cls");

                string model;
                int inStock;
                int sold;
                string description;
                double purchaseCost;
                double salePrice;

                cin.ignore();
                cout << INDENT << "Please enter a product Model: ";
                getline(cin, model);
                cout << INDENT << "Enter in Stock: ";
                cin >> inStock;
                cout << INDENT << "Enter Sold: ";
                cin >> sold;

                cin.ignore();
                cout << INDENT << "Enter Description: ";
                getline(cin, description);
                cout << INDENT << "Enter Purchase Cost: ";
                cin >> purchaseCost;
                cout << INDENT << "Enter Sale Price: ";
                cin >> salePrice;

                addProduct(ls, model, inStock, sold, description, purchaseCost, salePrice, false, 0);
                storeProduct(ls);
                addHistory(s, username, "ADD", model, getCambodiaTime());
                storeAdminHistory(s -> top);

                cout << "\n" << INDENT << "Product added to the List successfully!\n";
                system("pause");

                break;
            }

            case 2:  
                handleViewTableMenu();  
                break;

            case 3:{
                system("cls");

                int targetId;
                cout << INDENT << "Enter ID to update: ";
                cin >> targetId;
                ProductElement* temp = searchProductByID(ls, targetId);
                updateProductById(ls, temp, targetId);
                if(temp != nullptr){
                    addHistory(s, username, "UPDATE", ("Product id: " + to_string(targetId)), getCambodiaTime());
                    storeAdminHistory(s -> top);
                }

                system("pause");
                break;
            }

            case 4: {
                system("cls");

                int id;
                cout << INDENT << "Enter ID to Delete: ";
                cin >> id;
                ProductElement* temp = searchProductByID(ls, id);
                deleteProductByID(ls, temp);
                if(temp != nullptr){
                    addHistory(s, username, "DELETE", ("Product id: " + to_string(id)), getCambodiaTime());
                    storeAdminHistory(s -> top);
                }
                system("pause");
                break;
            }

            case 5: {
                system("cls");

                int id;
                cout << INDENT << "Search ID: ";
                cin >> id;
                searchProductByID(ls, id);
                displayProductByID(ls, id);

                system("pause");
                break;
            }

            case 6: {
                system("cls");

                displayLowStockProducts(ls);

                system("pause");
                break;
            }

            case 7: {
                system("cls");

                backupAndRestoreMenu(ls);
                break;
            }

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

void handleUserMenu() {

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
                    // loading();
                    handleAdminMenu(username);

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
                    // loading();
                    handleUserMenu();
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
