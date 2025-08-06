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
#define MAGENTA        "\033[35m"
#define ADD_COLOR      "\033[32m"    // Green
#define UPDATE_COLOR   "\033[36m"    // Cyan
#define DELETE_COLOR   "\033[31m"    // Red
#define BACKUP_COLOR   "\033[34m"    // Blue
#define RESTORE_COLOR  "\033[35m"    // Magenta
#define BRIGHT_YELLOW "\033[1;33m"   // Bold Yellow
#define NORMAL_YELLOW "\033[0;33m"   // Regular Yellow
#define DIM_YELLOW    "\033[2;33m"   // Dim Yellow
#define VERY_DIM      "\033[2;30m"   // Almost black (dim gray)

// FONT
#define BOLD          "\033[1m"
#define ITALIC        "\033[3m"
#define PLAIN         "\033[22m"

void welcome() {
    string art = R"(
        ____                 __           __     __  ___                                                  __     _____            __               
       / __ \_________  ____/ /_  _______/ /_   /  |/  /___ _____  ____ _____ ____  ____ ___  ___  ____  / /_   / ___/__  _______/ /____  ____ ___ 
      / /_/ / ___/ __ \/ __  / / / / ___/ __/  / /|_/ / __ `/ __ \/ __ `/ __ `/ _ \/ __ `__ \/ _ \/ __ \/ __/   \__ \/ / / / ___/ __/ _ \/ __ `__ \
     / ____/ /  / /_/ / /_/ / /_/ / /__/ /_   / /  / / /_/ / / / / /_/ / /_/ /  __/ / / / / /  __/ / / / /_    ___/ / /_/ (__  ) /_/  __/ / / / / /
    /_/   /_/   \____/\__,_/\__,_/\___/\__/  /_/  /_/\__,_/_/ /_/\__,_/\__, /\___/_/ /_/ /_/\___/_/ /_/\__/   /____/\__, /____/\__/\___/_/ /_/ /_/ 
                                                                      /____/                                       /____/                          
                            
    )";

    // Fade out: bright to dim
    system("cls");
    cout << BRIGHT_YELLOW << art << RESET << endl;
    sleep_for(milliseconds(400));

    system("cls");
    cout << NORMAL_YELLOW << art << RESET << endl;
    sleep_for(milliseconds(400));

    system("cls");
    cout << DIM_YELLOW << art << RESET << endl;
    sleep_for(milliseconds(400));

    system("cls");
    cout << VERY_DIM << art << RESET << endl;
    sleep_for(milliseconds(400));

    // Fully disappear
    system("cls");
    sleep_for(milliseconds(400));
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
    
    // Exit the program
    exit(0);
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

    cout << INDENT << title << "\n";

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
    drawMenu(string(ORANGE) + string(BOLD) + "Main Menu - Inventory System" + string(RESET) + string(YELLOW), {
        string(ITALIC) + string(WHITE) + 
        "1. " + string(YELLOW)+ "Login as Administrator"       + string(WHITE),
        "2. " + string(BLUE)  + "Login as User"                + string(WHITE),
        "3. " + string(GREEN) + "Register New User"            + string(WHITE),
        "4. " + string(CYAN)  + "About Developer (Group 1)"    + string(WHITE),
        "0. " + string(RED)   + "Exit Program" + string(RESET) + string(YELLOW)
    }, "Please select an option: ");
}

// When Click Login as Administrator
void menuForAdmin() {
    drawMenu(string(ORANGE) + string(BOLD) + "Admin Panel - Product Management" + string(RESET) + string(YELLOW), {
        string(ITALIC) + string(WHITE) +
        "1. " + string(GREEN)   + "Add New Product"               + string(WHITE),
        "2. " + string(CYAN)    + "View & Manage Product Tables"  + string(WHITE),
        "3. " + string(BLUE)    + "Update Product"                + string(WHITE),
        "4. " + string(RED)     + "Delete Product"                + string(WHITE),
        "5. " + string(WHITE)   + "Search Product"                + string(WHITE),
        "6. " + string(YELLOW)  + "View Low-Stock Products"       + string(WHITE),
        "7. " + string(MAGENTA) + "Backup & Restore Product Data" + string(WHITE),
        "8. " + string(CYAN)    + "Profile"                       + string(WHITE),
        "0. " + string(RED)     + "Log out"       + string(RESET) + string(YELLOW)
    }, "Please select an option: ");
}

// When Admin click on View All Product
void viewTableMenu(){
    drawMenu(string(ORANGE) + string(BOLD) + "Product Insights & Reports Menu" + string(RESET) + string(YELLOW), {
        string(ITALIC) + string(WHITE) +
        "1. " + string(WHITE)   + "View Product List"                            + string(WHITE),
        "2. " + string(BLUE)    + "Sort Product List by Sale Price (Descending)" + string(WHITE),
        "3. " + string(BLUE)    + "Sort Product List by Sale Price (Ascending)"  + string(WHITE),
        "4. " + string(GREEN)   + "View Overall Report (Profit & Sales)"         + string(WHITE),
        "5. " + string(CYAN)    + "View Top 5 Best-Selling Products"             + string(WHITE),
        "6. " + string(MAGENTA) + "View Admin History"                           + string(WHITE),
        "7. " + string(MAGENTA) + "View Last Month History"                      + string(WHITE),
        "8. " + string(MAGENTA) + "View Last Day History"                        + string(WHITE),
        "0. " + string(RED)     + "Back"                         + string(RESET) + string(YELLOW)
    }, "Choice: ");
}

// Click login as User
void userMenu(){
    drawMenu(string(ORANGE) + string(BOLD) + "User Panel - Product Access" + string(RESET) + string(YELLOW), {
        string(ITALIC) + string(WHITE) +
        "1. " + string(CYAN) + "View Product List"   + string(WHITE),
        "2. " + string(WHITE) + "Search Product"     + string(WHITE),
        "3. " + string(GREEN) + "Profile"            + string(WHITE),
        "0. " + string(RED) + "Back" + string(RESET) + string(YELLOW)
    }, "Please select an option: ");
}

// Backup Menu
void menuForBackupAndRestore() {
    drawMenu(string(ORANGE) + string(BOLD) + "Backup & Restore Menu" + string(RESET) + string(YELLOW), {
        string(ITALIC) + string(WHITE) +
        "1. " + string(GREEN) + "Backup Current Product Data"     + string(WHITE),
        "2. " + string(CYAN) + "Restore Product Data from Backup" + string(WHITE),
        "0. " + string(RED) + "Back"              + string(RESET) + string(YELLOW)
    }, "Choice: ");
}

void showDeveloperInfo() {
    devInfo();

    // Header
    cout << BOLD << "Welcome to Developer Information\n" << RESET;
    cout << YELLOW << "========================================================================================================\n" << RESET;

    // Table Headings
    cout << BOLD << WHITE;
    printf("%-22s %-18s %-50s\n", "Team Member", "ID", "Task / Job Description");
    cout << RESET << YELLOW;
    cout << "--------------------------------------------------------------------------------------------------------\n" << RESET;

    // Developer 1
    cout << CYAN;
    printf("%-22s %-18s ", "Do Davin", "p20230018");
    cout << ITALIC << "Data Structures, Code Integration, Program Design, clean code" << RESET << "\n";

    // Developer 2
    cout << GREEN;
    printf("%-22s %-18s ", "Sam Sok Leap", "p20230031");
    cout << ITALIC << "Data Structures, File & History Manager" << RESET << "\n";

    // Developer 3
    cout << MAGENTA;
    printf("%-22s %-18s ", "Kheang Ann", "p20230027");
    cout << ITALIC << "Data Structures, Authentication, Encryption, and Data Handling" << RESET << "\n";

    cout << YELLOW << "========================================================================================================\n" << RESET;
}