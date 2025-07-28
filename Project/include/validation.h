#include <iostream>
#include <string>
#include <limits> // For using numeric_limits<streamsize>

// Detect invalid inStock & sold input
int getValidateIntInRange(const string &text, int min, int max) {
    int value;
    while(true) {
        cout << text;
        cin >> value;
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
    }
}

// Detect invalid purchaseCost & temp->salePrice input
double getValidateDoubleInRange(const string &text, double min, double max) {
    double value;
    while(true) {
        cout << text;
        cin >> value;
        if(cin.fail() || value <= 0 || value < min || value > max) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << INDENT << "Invalid input. Enter a non-zero number between " << min << " and " << max << ".\n" << RESET;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}