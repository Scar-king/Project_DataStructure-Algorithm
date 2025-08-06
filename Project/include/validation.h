#include <iostream>
#include <string>
#include <limits> // For using numeric_limits<streamsize>
#include <cctype>
#include <stdexcept> // For exception handling (stoi, stod)
#include <functional>

bool isNumber(const string& s) {
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return !s.empty();
}

bool isValidDouble(const string& s) {
    if(s.empty()) return false;

    bool hasDecimal = false;

    for(char c : s) {
        if(c == '.') {
            if (hasDecimal) return false; // already has one dot
            hasDecimal = true;
        } else if (!isdigit(c)) {
            return false;
        }
    }

    return true;
}

bool isChar(const string& s) {
    return s.length() == 1 && (s[0] == 'M' || s[0] == 'F');
}

char validateChar() {
    string gender;
    do {
        cout << YELLOW << INDENT << "Input GENDER (M/F): " << RESET;
        getline(cin, gender);

        if (!isChar(gender)) {
            cout << RED << INDENT << "Invalid input. Please enter 'M' or 'F'.\n" << RESET;
        }

    } while (!isChar(gender));

    return toupper(gender[0]);  
}


int validateMenu(int min, int max, const function<void()> &menuCallback) {
    string input;
    int option;

    while(true) {
        cin >> input;

        if(isNumber(input)) {

            option = stoi(input);

            if(cin.fail() || option < min || option > max) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << RED << INDENT
                        << "Invalid input. Enter a number between "
                        << min << " and " << max << ".\n" << RESET;
                system("pause");
                system("cls");
                menuCallback();
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return option;
            }
        } else {
            cout << RED << INDENT << "Please enter a valid positive number (no letters or symbols).\n" << RESET;
            system("pause");
            system("cls");
            menuCallback();
        }
    }  
}

// Detect invalid inStock & sold input
int getValidateIntInRange(const string &text, int min, int max) {
    string input;
    int value;
    while(true) {
        cout << text;
        cin >> input;

        if(isNumber(input)) {

            value = stoi(input);

            // cin.fail(): checks if the user entered invalid data (Ex: letters or symbols)
            if(cin.fail() || value < min || value > max) {
                cin.clear(); // Clear error flags (like failbit)
    
                // Flush the rest of the inupt line
                // cin.ignore(1000, '\n'); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
                cout << RED << INDENT << "Invalid input. Enter a number between " << min << " and " << max << ".\n" << RESET;
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush remaining input
                return value;
            }
        } else {
            cout << RED << INDENT << "Please enter a valid positive number (no letters or symbols).\n" << RESET;
        }
    }
}

// Detect invalid purchaseCost & temp->salePrice input
double getValidateDoubleInRange(const string &text, double min, double max) {
    string input;
    double value;
    while(true) {
        cout << text;
        cin >> input;

        if(isValidDouble(input)) {

            value = stod(input);

            if(cin.fail() || value <= 0 || value < min || value > max) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << RED << INDENT << "Invalid input. Enter a non-zero number between " << min << " and " << max << ".\n" << RESET;
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return value;
            }
        } else {
            cout << RED << INDENT << "Please enter a valid positive number (no letters or symbols).\n" << RESET;
        }
    }
}

void modelLenValidation (string &model) {
    do {
        cout << YELLOW << INDENT << "Please enter a product Model: " << RESET;
        getline(cin, model);

        if(model.empty()) {
            cout << RED << INDENT << "MODEL cannot be empty. Please enter a valid MODEL.\n" << RESET;
        }

        else if (model.length() > 20) {
            cout << RED << INDENT << "MODEL too long. Max allowed is 20 characters (" 
                    << model.length() << " entered).\n" << RESET;
            model.clear();
        }
    } while(model.empty() || model.length() > 20);
}

void modelUpdateLenValidation (string &model, int &targetId) {
    cout << YELLOW << INDENT << "Updating Product ID: " << RESET << targetId;
    cout << "\n" << YELLOW << INDENT << "Current model: " << RESET << model;
    do {
        cout << "\n" << YELLOW << INDENT << "New model: " << RESET;
        getline(cin, model);

        if(model.empty()) {
            cout << RED << INDENT << "MODEL cannot be empty. Please enter a valid MODEL.\n" << RESET;
        }

        else if (model.length() > 20) {
            cout << RED << INDENT << "MODEL too long. Max allowed is 20 characters (" 
                    << model.length() << " entered).\n" << RESET;
            model.clear();
        }
    } while(model.empty() || model.length() > 20);
}

void descLenValidation (string &description) {
    do {
        cout << YELLOW << INDENT << "Enter Description: " << RESET;
        getline(cin, description);

        if(description.empty()) {
            cout << RED << INDENT << "Description cannot be empty. Please enter a valid Description.\n" << RESET;
        }

        else if (description.length() > 35) {
            cout << RED << INDENT << "Description too long. Max allowed is 35 characters (" 
                    << description.length() << " entered).\n" << RESET;
            description.clear();
        }
    } while(description.empty() || description.length() > 35);
}

void descUpdateLenValidation (string &newDescription) {
    do {
        cout << YELLOW << INDENT << "Enter new Description: " << RESET;
        getline(cin, newDescription);

        if(newDescription.empty()) {
            cout << RED << INDENT << "Description cannot be empty. Please enter a valid description.\n" << RESET;
        }

        else if (newDescription.length() > 35) {
            cout << RED << INDENT << "Description too long. Max allowed is 35 characters (" 
                    << newDescription.length() << " entered).\n" << RESET;
            newDescription.clear();
        }
    } while(newDescription.empty() || newDescription.length() > 35);
}