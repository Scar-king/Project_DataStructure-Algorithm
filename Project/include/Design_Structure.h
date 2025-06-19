#include <iostream>
#include <cstdlib>
#include <windows.h>
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define WHITE   "\033[37m"

void welcome(){
    cout << GREEN << R"(
                       ___              __         __    __  ___                                       __    
                      / _ \_______  ___/ /_ ______/ /_  /  |/  /__ ____  ___ ____ ____ __ _  ___ ___  / /_   
                     / ___/ __/ _ \/ _  / // / __/ __/ / /|_/ / _ `/ _ \/ _ `/ _ `/ -_)  ' \/ -_) _ \/ __/   
                    /_/  /_/  \___/\_,_/\_,_/\__/\__/ /_/  /_/\_,_/_//_/\_,_/\_, /\__/_/_/_/\__/_//_/\__/    
                                                                            /___/                            
    )" << RESET << endl;
}

void loginPage(){
    cout << YELLOW << "\n\t\t\t\t\t";
    for(int i = 0; i <= 50; i++){
        cout << "-";
        Sleep(10);
    }
    printf("\n\t\t\t\t\t\t\t\t%s", "Menu");
    Sleep(500);
    cout << "\n\t\t\t\t\t";
    for(int i = 0; i <= 50; i++){
        cout << "-";
        Sleep(10);
    }
    printf("\n\t\t\t\t\t\t\t%-20s", "1. Login as Administrator");
    Sleep(50);
    printf("\n\t\t\t\t\t\t\t%-20s", "2. Login as User");
    Sleep(50);
    printf("\n\t\t\t\t\t\t\t%-20s", "3. Register");
    Sleep(50);
    printf("\n\t\t\t\t\t\t\t%-20s", "0. Quit");
    Sleep(50);
    cout << "\n\t\t\t\t\t";
    for(int i = 0; i <= 50; i++){
        cout << "-";
        Sleep(10);
    }
    printf("\n\n\t\t\t\t\t%s", "Choice: ");
    Sleep(50);
    cout << RESET;
}

// When Click Login as Administrator
void menu(){
    cout << YELLOW << "\t\t\t\t\t";
    for(int i = 0; i <= 50; i++){
        cout << "-";
        Sleep(10);
    }
    printf("\n\t\t\t\t\t\t\t\t%s", "Menu");
    Sleep(500);
    cout << "\n\t\t\t\t\t";
    for(int i = 0; i <= 50; i++){
        cout << "-";
        Sleep(10);
    }
    printf("\n\t\t\t\t\t\t\t%-20s", "1. Add New Product");
    Sleep(50);
    printf("\n\t\t\t\t\t\t\t%-20s", "2. View Table");
    Sleep(50);
    printf("\n\t\t\t\t\t\t\t%-20s", "3. Update Product");
    Sleep(50);
    printf("\n\t\t\t\t\t\t\t%-20s", "4. Delete Product");
    Sleep(50);
    printf("\n\t\t\t\t\t\t\t%-20s", "5. Search Product");
    Sleep(50);
    printf("\n\t\t\t\t\t\t\t%-20s", "0. Back");
    Sleep(50);
    cout << "\n\t\t\t\t\t";
    for(int i = 0; i <= 50; i++){
        cout << "-";
        Sleep(10);
    }
    printf("\n\n\t\t\t\t\t%s", "Choice: ");
    Sleep(50);
    cout << RESET;
}

// When Admin click on View All Product
void viewTableMenu(){
    cout << YELLOW << "\n\t\t\t\t\t";
    for(int i = 0; i <= 50; i++){
        cout << "-";
        Sleep(10);
    }
    printf("\n\t\t\t\t\t\t\t\t%s", "Menu");
    Sleep(500);
    cout << "\n\t\t\t\t\t";
    for(int i = 0; i <= 50; i++){
        cout << "-";
        Sleep(10);
    }
    printf("\n\t\t\t\t\t\t\t%-20s", "1. View Product List");
    Sleep(50);
    printf("\n\t\t\t\t\t\t\t%-20s", "2. View Overall Report");
    Sleep(50);
    printf("\n\t\t\t\t\t\t\t%-20s", "3. View Transaction Report");
    Sleep(50);
    printf("\n\t\t\t\t\t\t\t%-20s", "0. Back");
    Sleep(50);
    cout << "\n\t\t\t\t\t";
    for(int i = 0; i <= 50; i++){
        cout << "-";
        Sleep(10);
    }
    printf("\n\n\t\t\t\t\t%s", "Choice: ");
    Sleep(50);
    cout << RESET;
}

// Click login as User
void loginAsUser(){
        cout << YELLOW << "\n\t\t\t\t\t";
    for(int i = 0; i <= 50; i++){
        cout << "-";
        Sleep(10);
    }
    printf("\n\t\t\t\t\t\t\t\t%s", "Menu");
    Sleep(500);
    cout << "\n\t\t\t\t\t";
    for(int i = 0; i <= 50; i++){
        cout << "-";
        Sleep(10);
    }
    printf("\n\t\t\t\t\t\t\t%-20s", "1. View Product List");
    Sleep(50);
    printf("\n\t\t\t\t\t\t\t%-20s", "2. Search Product");
    Sleep(50);
    printf("\n\t\t\t\t\t\t\t%-20s", "0. Back");
    Sleep(50);
    cout << "\n\t\t\t\t\t";
    for(int i = 0; i <= 50; i++){
        cout << "-";
        Sleep(10);
    }
    printf("\n\n\t\t\t\t\t%s", "Choice: ");
    Sleep(50);
    cout << RESET;
}