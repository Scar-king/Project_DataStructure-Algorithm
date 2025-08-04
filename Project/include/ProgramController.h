#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <iomanip>
#include <conio.h>
#include <algorithm>
#include "../include/ConsoleUI.h"
#include "../include/InventorySystem.h"

#include "Constants.h"

using namespace std;

// GLOBAL VAR
ProductList *ls = createList();
ReportList *rl = createReportList();
AdminHistoryStack *s = createEmptyStack();
void Authentication();

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

void AddUser(Userlist* ls, string username, char gender, int age, string password) {
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

        AddUser(ls, username, gender, age, decryptedPassword);
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

void displayAdminProfile(const string& name, int age, char gender) {
    cout << BLUE;
    cout << INDENT << "+--------------------------------+\n";
    cout << INDENT << "|         ADMIN PROFILE          |\n";
    cout << INDENT << "+--------------------------------+\n";
    cout << INDENT << "| " << YELLOW << "Name   : " << name 
         << string(22 - name.length(), ' ') << BLUE << "|\n";
    cout << INDENT << "| " << YELLOW << "Age    : " << age 
         << string(22 - to_string(age).length(), ' ') << BLUE << "|\n";
    cout << INDENT << "| " << YELLOW << "Gender : " << (gender == 'M' ? "Male" : "Female") 
         << string(18, ' ') << BLUE << "|\n";
    cout << INDENT << "+--------------------------------+\n" << RESET;
}

void displayUserProfile(const string& name, int age, char gender) {
    cout << CYAN;
    cout << INDENT << "+--------------------------------+\n";
    cout << INDENT << "|           USER PROFILE         |\n";
    cout << INDENT << "+--------------------------------+\n";
    cout << INDENT << "| " << YELLOW << "Name   : " << name 
         << string(22 - name.length(), ' ') << CYAN << "|\n";
    cout << INDENT << "| " << YELLOW << "Age    : " << age 
         << string(22 - to_string(age).length(), ' ') << CYAN << "|\n";
    cout << INDENT << "| " << YELLOW << "Gender : " << (gender == 'M' ? "Male" : "Female") 
         << string(18, ' ') << CYAN << "|\n";
    cout << INDENT << "+--------------------------------+\n" << RESET;
}

// Submenus of Admin Menu
void handleViewTableMenu() {
    bool backToAdminMenu = false;

    while(!backToAdminMenu) {
        system("cls");
        viewTableMenu();

        int tableOption = validateMenu(MIN_OPTION, MAX_SUBOPTION, viewTableMenu);

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
                ReportList rl = {};
                if(ls->head == nullptr) {
                    loadProductList(ls);
                }

                ProductElement *temp = ls->head;
                while(temp != nullptr) {
                    addReport(&rl, temp);
                    temp = temp->next;
                }

                if(rl.head == nullptr) {
                    cout << RED << INDENT << "No report data available.\n" << RESET;
                } else {
                    displayOverallReport(&rl);
                    graphVisualization(&rl);
                }

                clearReportList(&rl);
                system("pause");
                break;
            }

            case 5: {
                system("cls");

                displayBestSelling(ls);

                system("pause");
                break;
            }

            case 6: {

                displayAllAdminHistory(s);

                system("pause");
                break;
            }

            case 7:

                displayLastMonthHistory(s);
                system("pause");
                break;

            case 8: 
                displayLastDayHistory(s);
                system("pause");
                break;
            
            case 0:
                backToAdminMenu = true;
                break;

            default:
                cout << "\n" << RED << INDENT << " Invalid option. Please try again.\n" << RESET;
                Sleep(1000);
                break;
        }
    }
}

void backupAndRestoreMenu(ProductList *ls, string username) {

    bool back = false;
 
    while (!back) {
        menuForBackupAndRestore();

        int choice = validateMenu(MIN_OPTION, MAX_BACKUP_OPTION, menuForBackupAndRestore);

        switch(choice) {
            case 1:
                storeProduct(ls);
                backupProductData(ls);
                addHistory(s, username, "BACKUP", "BACKUP PRODUCT DATA", getCambodiaTime());
                storeAdminHistory(s -> top);
                system("pause");
                system("cls");
                Authentication();
                return;
            case 2:
                restoreProductData(ls);
                addHistory(s, username, "RESTORE", "RESTORE PRODUCT DATA", getCambodiaTime());
                storeAdminHistory(s -> top);
                system("pause");
                system("cls");
                Authentication();
                return;
            case 0:
                back = true;
                system("cls");
                break;
            default:
                cout << RED << INDENT << "Invalid choice. Try again...\n" << RESET;
        }    
    }
}

void handleAdminMenu(string username) {
    bool logout = false;
    loadProductList(ls);

    clearAdminHistory(s); // Prevent duplicate history
    loadAdminHistoryStack(s);

    while (!logout) {
        system("cls");
        menuForAdmin();

        int adminOption = validateMenu(MIN_OPTION, MAX_SUBOPTION, menuForAdmin); 

        switch (adminOption) {
            case 1:{
                system("cls");

                string model;
                int inStock;
                int sold;
                string description;
                double purchaseCost;
                double salePrice;

                productArt();

                do {
                    cout << YELLOW << INDENT << "Please enter a product Model: " << RESET;
                    getline(cin, model);
                    if(model.empty()) {
                        cout << RED << INDENT << "MODEL cannot be empty. Please enter a valid MODEL.\n" << RESET;
                    }
                } while(model.empty());

                inStock = getValidateIntInRange(
                    INDENT + (string(YELLOW) + "Enter in Stock (0-10000): " + RESET), MIN_STOCK, MAX_STOCK
                );
                
                sold = getValidateIntInRange(
                    INDENT + (string(YELLOW) + "Enter Sold (0-10000): " + RESET), MIN_STOCK, MAX_STOCK
                );

                do {
                    cout << YELLOW << INDENT << "Enter Description: " << RESET;
                    getline(cin, description);
                    if (description.empty()) {
                        cout << RED << INDENT << "Description cannot be empty. Please enter a valid description.\n" << RESET;
                    }
                } while (description.empty());

                purchaseCost = getValidateDoubleInRange(
                    INDENT + (string(YELLOW) + "Enter Purchase Cost ( price > 0 ): " + RESET), MIN_PRICE, MAX_PRICE
                );

                salePrice = getValidateDoubleInRange(
                    INDENT + (string(YELLOW) + "Enter Sale Price ( price > 0 ): " + RESET), MIN_PRICE, MAX_PRICE
                );

                addProduct(ls, model, inStock, sold, description, purchaseCost, salePrice, false, 0);
                storeProduct(ls);
                addHistory(s, username, "ADD", ("Product name: " + model), getCambodiaTime());
                storeAdminHistory(s -> top);

                cout << "\n" << GREEN << INDENT << "Product added to the List successfully!\n" << RESET;
                system("pause");

                break;
            }

            case 2:  
                handleViewTableMenu();  
                break;

            case 3:{
                system("cls");

                displayAdminProductList(ls);

                int targetId = getValidateIntInRange(
                    INDENT + (string(YELLOW) + "Enter the (ID) of the product to modify: ") + RESET,
                    MIN_ID, MAX_ID  
                );

                ProductElement* temp = searchProductByID(ls, targetId);
                updateProductById(ls, temp, targetId);

                if(temp != nullptr){
                    addHistory(s, username, "UPDATE", ("PRODUCT ID: " + to_string(targetId) + ", NAME: " + string(temp -> model)), getCambodiaTime());
                    storeAdminHistory(s -> top);
                }

                system("pause");
                break;
            }

            case 4: {
                system("cls");

                displayAdminProductList(ls);

                int id = getValidateIntInRange(
                    INDENT + (string(YELLOW) + "Please enter the product ID you want to delete: ") + RESET,
                    MIN_ID, MAX_ID  
                );

                ProductElement* temp = searchProductByID(ls, id);
                if(temp != nullptr){
                    addHistory(s, username, "DELETE", ("Product id: " + to_string(id) + ", name: " + string(temp -> model)), getCambodiaTime());
                    storeAdminHistory(s -> top);
                }
                deleteProductByID(ls, temp);
                system("pause");
                break;
            }

            case 5: {
                system("cls");

                displayAdminProductList(ls);

                int id = getValidateIntInRange(
                    INDENT + (string(YELLOW) + "Enter the product ID to search: ") + RESET,
                    MIN_ID, MAX_ID  
                );

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

                backupAndRestoreMenu(ls, username);

                break;
            }

            case 8: {
                system("cls");
                displayAdminProfile(username, 20, 'M');
                system("pause");
                break;
            }

            case 0:
                logout = true;  
                system("cls");
                break;

            default:
                cout << "\n" << RED << INDENT << " Invalid option. Please try again.\n" << RESET;
                break;
        }
    }
}

void handleUserMenu(string username, char gender, int age) {
    
    bool back = false;
    loadProductList(ls);

    while(!back) {
        system("cls");
        userMenu();

        int userOption = validateMenu(MIN_OPTION, MAX_CHOICE, userMenu);

        switch (userOption) {
            case 1: {
                displayUserProductList(ls);
                system("pause");
                break;
            }

            case 2: {
                system("cls");
                int id = getValidateIntInRange(
                    INDENT + (string(YELLOW) + "Enter the product ID to search: ") + RESET,
                    MIN_ID, MAX_ID  
                );
                searchProductByID(ls, id);
                displayProductByID(ls, id);
                system("pause");
                break;
            }

            case 3: {
                system("cls");
                displayUserProfile(username, age, gender);
                system("pause");
                break;
            }
            
            case 0:
                back = true;
                system("cls");
                break;

            default:
                cout << "\n" << INDENT << " Invalid option. Please try again.\n";
                Sleep(1000);
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

    do {
        loginPageMenu();

        int choice = validateMenu(MIN_OPTION, MAX_OPTION, loginPageMenu);

        switch (choice) {
            case 1:
                cout << YELLOW << INDENT << "Input ADMIN NAME: " << RESET;
                getline(cin, username);
                pw1 = getMaskedPassword(YELLOW + INDENT + "Input PASSWORD: " + RESET);

                if (username == AdminPassword && pw1 == AdminPassword) {
                    cout << "\n" << GREEN << INDENT << " ADMIN Login successfully!\n" << RESET;
                    loading();
                    handleAdminMenu(username);

                } else {
                    cout << "\n" << RED << INDENT << "Invalid admin credentials.\n" << RESET;
                    system("pause");
                    system("cls");
                }
                break;

            case 2: {
                cout << YELLOW << INDENT << "Input USERNAME: " << RESET;
                getline(cin, username);

                if (username.empty() || any_of(username.begin(), username.end(), ::isdigit)) {
                    cout << "\n" << RED << INDENT << "Invalid username. It should not be empty or contain numbers.\n" << RESET;
                    break;
                }

                bool loginSuccess = false;
                int attempts = 3;
                while (attempts-- > 0 && !loginSuccess) {
                    pw1 = getMaskedPassword(YELLOW + INDENT + "Input your PASSWORD: " + RESET);
                    if (authenticateUser(users, username, pw1)) {
                        User* u = users->head;
                        while(u) {
                            if (u->username == username) {
                                gender = u->gender;
                                age = u->age;
                                break;
                            }
                            u = u->next;
                        }
                        cout << "\n" << GREEN << INDENT << " Login successfully. Welcome, " << username << "!\n" << RESET;
                        loading();
                        handleUserMenu(username, gender, age);
                        loginSuccess = true;
                    } else {
                        cout << "\n" << RED << INDENT << "Login failed. Username or password incorrect.\n" << RESET;
                        if (attempts > 0)
                            cout << RED << INDENT << "Try again (" << attempts << " attempts left).\n" << RESET;
                        else
                            cout << RED << INDENT << "No attempts left. Returning to menu.\n" << RESET;
                        system("pause");
                        system("cls");
                    }
                }
                break;
            }

            case 3: {
                while (true) {
                    cout << YELLOW << INDENT << "Input USERNAME: " << RESET;
                    getline(cin, username);
    
                    // Check username validity
                    if (username.empty() || any_of(username.begin(), username.end(), ::isdigit)) {
                        cout << "\n" << RED << INDENT 
                             << "Invalid USERNAME. It should not be empty or contain numbers!\n" 
                             << RESET;
                    } else {
                        break;
                    }
                }
            
                while (true) {
                    cout << YELLOW << INDENT << "Input GENDER (M/F): " << RESET;
                    cin >> gender;
                    gender = toupper(gender);

                    // Validate gender first
                    if (gender != 'M' && gender != 'F') {
                        cout << "\n" << RED << INDENT
                            << "Invalid GENDER. Please enter M or F.\n"
                            << RESET;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear any leftover input
                        continue;  // Ask for gender again, skip age
                    }
                    break;
                }

                int age = getValidateIntInRange(INDENT + (string(YELLOW) + "Input AGE: ") + RESET, MIN_OPTION, MAX_AGE);

                int pw_attempts = 3;
                bool passwordMatched = false;
            
                pw1 = getMaskedPassword(YELLOW + INDENT + "Create your PASSWORD: " + RESET);

                if (pw1.length() < 4) {  // Password strength check
                    cout << RED << INDENT << "PASSWORD too short (min 4 characters), Please try again...\n" << RESET;
                    return;
                }

                while (pw_attempts-- > 0) {
                    pw2 = getMaskedPassword(YELLOW + INDENT + "Confirm PASSWORD: " + RESET);
                
                    if (pw1 == pw2) {
                        passwordMatched = true;
                        break;
                    } else {
                        cout << RED << INDENT << "PASSWORD do not matched.\n" << RESET;
                        if (pw_attempts > 0)
                            cout << RED << INDENT << "Try again (" << pw_attempts << " attempts left).\n" << RESET;
                        else {
                            cout << "\n" << RED << INDENT << "No attempts left. Registration canceled.\n" << RESET;
                            system("pause");
                            system("cls");
                        }
                    }
                }
            
                if (passwordMatched) {
                    AddUser(users, username, gender, age, pw1);
                    addUserToFile(username, gender, age, pw1);
                    cout << "\n" << GREEN << INDENT << "Registration successfully!\n" << RESET;
                    system("pause");
                    system("cls");
                }

                break;
            }

            case 4: {
                system("cls");
                showDeveloperInfo();
                system("pause");
                system("cls");
                break;
            }

            case 0: {
                system("cls");
                running = false;
                thankyou();
                break;
            }

            default:
                cout << "\n" << RED << INDENT << " Invalid option. Please try again.\n" << RESET;
                break;
        }
    } while (running);
}