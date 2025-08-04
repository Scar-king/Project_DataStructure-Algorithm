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