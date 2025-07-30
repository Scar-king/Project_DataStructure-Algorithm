#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include <chrono>
#include <thread>

#include "Constants.h"

using namespace std;
using namespace std::this_thread;
using namespace std::chrono;

#define RESET          "\033[0m"
#define RED            "\033[31m"
#define GREEN          "\033[32m"
#define YELLOW         "\033[33m"
#define BLUE           "\033[34m"
#define WHITE          "\033[37m"
#define CYAN           "\033[1;36m"
#define GRAY           "\033[0;37m"
#define ORANGE         "\033[38;2;255;165;0m"
#define ADD_COLOR      "\033[32m"  // Green
#define UPDATE_COLOR   "\033[36m"  // Cyan
#define DELETE_COLOR   "\033[31m"  // Red
#define BACKUP_COLOR   "\033[34m"  // Blue
#define RESTORE_COLOR  "\033[35m"  // Magenta
#define BRIGHT_YELLOW "\033[1;33m"   // Bold Yellow
#define NORMAL_YELLOW "\033[0;33m"   // Regular Yellow
#define DIM_YELLOW    "\033[2;33m"   // Dim Yellow
#define VERY_DIM      "\033[2;30m"   // Almost black (dim gray)



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

void devInfo() {
    cout << YELLOW;  
    cout << "\n";
    cout << "     ____                 _                         ___        __       \n";
    cout << "    |  _ \\  _____   _____| | ___  _ __   ___ _ __  |_ _|_ __  / _| ___  \n";
    cout << "    | | | |/ _ \\ \\ / / _ \\ |/ _ \\| '_ \\ / _ \\ '__|  | || '_ \\| |_ / _ \\ \n";
    cout << "    | |_| |  __/\\ V /  __/ | (_) | |_) |  __/ |     | || | | |  _| (_) | \n";
    cout << "    |____/ \\___| \\_/ \\___|_|\\___/| .__/ \\___|_|    |___|_| |_|_|  \\___/  \n";
    cout << "                                 |_|                                     \n";
    cout << RESET << endl;
}

void thankyou() {

    string art = R"(
    _____ _                 _       __                        _                                                _                       ___                _ _                  _ 
   /__   \ |__   __ _ _ __ | | __  / _| ___  _ __   _   _ ___(_)_ __   __ _    ___  _   _ _ __   ___ _   _ ___| |_ ___ _ __ ___       / _ \___   ___   __| | |__  _   _  ___  / \
     / /\/ '_ \ / _` | '_ \| |/ / | |_ / _ \| '__| | | | / __| | '_ \ / _` |  / _ \| | | | '__| / __| | | / __| __/ _ \ '_ ` _ \     / /_\/ _ \ / _ \ / _` | '_ \| | | |/ _ \/  /
    / /  | | | | (_| | | | |   <  |  _| (_) | |    | |_| \__ \ | | | | (_| | | (_) | |_| | |    \__ \ |_| \__ \ ||  __/ | | | | |_  / /_\\ (_) | (_) | (_| | |_) | |_| |  __/\_/ 
    \/   |_| |_|\__,_|_| |_|_|\_\ |_|  \___/|_|     \__,_|___/_|_| |_|\__, |  \___/ \__,_|_|    |___/\__, |___/\__\___|_| |_| |_(_) \____/\___/ \___/ \__,_|_.__/ \__, |\___\/   
                                                                      |___/                          |___/                                                        |___/          
    )";

    // Cycle colors in a smooth breathing loop (2 full cycles)
    for (int cycle = 0; cycle < 2; cycle++) {
        // Fade out
        system("cls");
        cout << BRIGHT_YELLOW << art << RESET << endl; // Bright
        sleep_for(milliseconds(150));

        system("cls");
        cout << NORMAL_YELLOW << art << RESET << endl; // Dim 
        sleep_for(milliseconds(150));

        system("cls");
        cout << DIM_YELLOW << art << RESET << endl;
        sleep_for(milliseconds(150));

        system("cls");
        cout << VERY_DIM << art << RESET << endl;
        sleep_for(milliseconds(150));

        // Fade in
        system("cls");
        cout << DIM_YELLOW << art << RESET << endl;
        sleep_for(milliseconds(150));

        system("cls");
        cout << NORMAL_YELLOW << art << RESET << endl;
        sleep_for(milliseconds(150));

        system("cls");
        cout << BRIGHT_YELLOW << art << RESET << endl;
        sleep_for(milliseconds(200)); // Pause slightly longer at peak
    }

    // Hold the final bright version before exit
    system("cls");
    cout << BRIGHT_YELLOW << art << RESET << endl;
    sleep_for(milliseconds(1000));
}

void productArt() {
    cout << YELLOW << R"(
    +--------------------+--------------------------+-----------------------------+-----------------------------+-----------------------------+
    |                    |                          |                             |                             |                             |  
    |      )" << ORANGE << "[PHONE]" 
              << YELLOW << R"(       |        )" 
              << ORANGE << "[LAPTOP]" 
              << YELLOW << R"(          |          )" 
              << ORANGE << "[TABLET]" 
              << YELLOW << R"(           |         )" 
              << ORANGE << "[MONITOR]" 
              << YELLOW << R"(           |         )" 
              << ORANGE << "[CONSOLE]" 
              << YELLOW << R"(           |
    |                    |                          |                             |                             |                             |    
    +--------------------+--------------------------+-----------------------------+-----------------------------+-----------------------------+
    |     __________     |                          |                             |                             |                             |
    |    |          |    |       ____________       |     ___________________     |     ___________________     |      _________________      |
    |    |  O       |    |      |            |      |    |                   |    |    |                   |    |     /                 \     |  
    |    |  O       |    |      |            |      |    |                   |    |    |                   |    |    |      CONSOLE      |    |
    |    |  O       |    |      |            |      |    |      TABLET       |    |    |      MONITOR      |    |    |                   |    |
    |    |          |    |      |____________|      |    |                   |    |    |                   |    |     \_________________/     |  
    |    |          |    |      / o o o o o  \      |    |___________________|    |    |___________________|    |           /     \           |  
    |    |          |    |     / o o o o o o  \     |          |       |          |           ||   ||           |          (  O O  )          |  
    |    |__________|    |    /________________\    |          |_______|          |           ||___||           |           \_____/           |  
    +--------------------+--------------------------+-----------------------------+-----------------------------+-----------------------------+
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
        Sleep(15);
    }
    cout << "\n\n" << INDENT << (char)1;
    system("Pause");
}

// Reusable menu drawer
void drawMenu(
    const string& title, 
    const vector<string>& items, 
    const string& prompt = "Please select an option: "
) {
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
    cout << INDENT << "| 4. About Developer (Group *)|\n";
    cout << INDENT << "| 0. Exit Application         |\n";
    cout << INDENT << "+-----------------------------+\n";

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
        "6. View Low-Stock Products",
        "7. Backup & Restore Product Data",
        "8. Profile",
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
        "5. View Top 5 Best-Selling Products",
        "6. View Admin History",
        "7. View Last Month History",
        "8. View Last Day History",
        "0. Back"
    }, "Choice: ");
}

// Click login as User
void userMenu(){
    drawMenu("Menu", {
        "1. View Product List",
        "2. Search Product",
        "3. Profile",
        "0. Back"
    }, "Choice: ");
}

// Backup Menu
void menuForBackupAndRestore() {
    drawMenu("Backup & Restore Menu", {
        "1. Backup Current Product Data",
        "2. Restore Product Data from Backup",
        "0. Back"
    }, "Choice: ");
}