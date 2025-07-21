#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <vector>

#include "Constants.h"

using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define WHITE   "\033[37m"

void welcome(){
    cout << GREEN << R"(
        ____                 __           __     __  ___                                                  __     _____            __               
       / __ \_________  ____/ /_  _______/ /_   /  |/  /___ _____  ____ _____ ____  ____ ___  ___  ____  / /_   / ___/__  _______/ /____  ____ ___ 
      / /_/ / ___/ __ \/ __  / / / / ___/ __/  / /|_/ / __ `/ __ \/ __ `/ __ `/ _ \/ __ `__ \/ _ \/ __ \/ __/   \__ \/ / / / ___/ __/ _ \/ __ `__ \
     / ____/ /  / /_/ / /_/ / /_/ / /__/ /_   / /  / / /_/ / / / / /_/ / /_/ /  __/ / / / / /  __/ / / / /_    ___/ / /_/ (__  ) /_/  __/ / / / / /
    /_/   /_/   \____/\__,_/\__,_/\___/\__/  /_/  /_/\__,_/_/ /_/\__,_/\__, /\___/_/ /_/ /_/\___/_/ /_/\__/   /____/\__, /____/\__/\___/_/ /_/ /_/ 
                                                                      /____/                                       /____/                          
                            
    )" << RESET << endl;
}

void printDashedLine() {
    cout << TAB << "\t";
    for (int i = 0; i < 60; i++) cout << "-";
    cout << "\n";
}

void loading(){
    cout << GREEN;
    system("cls");
    //printf("\e[?251");

    // We use ASCII to print special character
    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    int bar1 = 177, bar2 = 219;

    cout << "\n\n\n" << INDENT << "Loading...";
    cout << "\n\n" << INDENT;

    for (int i = 0; i < 60; i++){
        cout << (char)bar1;
    }
    cout << "\r";
    cout << INDENT;
    for (int i = 0; i < 60; i++){
        cout << (char)bar2;
        Sleep(20);
    }
    cout << "\n\n" << INDENT << (char)1;
    system("Pause");
}

// Reusable menu drawer
void drawMenu(const string& title, const vector<string>& items, const string& prompt = "Please select an option: ") {
    cout << YELLOW;
    printDashedLine();

    cout << INDENT << "\tMENU\n";

    printDashedLine();

    // Menu items
    for (const auto& item : items) {
        cout << INDENT << item << "\n";
        Sleep(50);
    }

    printDashedLine();
    cout << "\n" << INDENT << prompt;
    cout << RESET;
}

void loginPageMenu(){
    cout << YELLOW;

    cout << "\n" << INDENT << "+-----------------------------+\n";
    cout << INDENT << "|     User Management System  |\n";
    cout << INDENT << "+-----------------------------+\n";
    cout << INDENT << "| 1. Administrator Login      |\n";
    cout << INDENT << "| 2. User Login               |\n";
    cout << INDENT << "| 3. Register New User        |\n";
    cout << INDENT << "| 0. Exit Application         |\n";
    cout << INDENT << "+-----------------------------+\n";
    cout << INDENT << "Please select an option: ";

    cout << RESET;
}

// When Click Login as Administrator
void menuForAdmin() {
    drawMenu("Menu", {
        "1. Add New Product",
        "2. View & Manage Product Tables",
        "3. Update Product",
        "4. Delete Product",
        "5. Search Product",
        "0. Log out"
    });
}

// When Admin click on View All Product
void viewTableMenu(){
    drawMenu("Menu", {
        "1. View Product List",
        "2. Sort Product List by Sale Price (Descending)",
        "3. Sort Product List by Sale Price (Ascending)",
        "4. View Overall Report (Profit & Sales)",
        "5. View Admin History",
        "0. Back"
    }, "Choice: ");
}

// Click login as User
void userMenu(){
    drawMenu("Menu", {
        "1. View Product List",
        "2. Search Product",
        "0. Back"
    }, "Choice: ");
}