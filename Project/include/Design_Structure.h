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
    cout <<  YELLOW <<  R"(
                    1. Login as Administrator
                    2. Login as User
                    3. Register
                    4. Exit

                    Choice: 
    )" << RESET;
}

// When Click Login as Administrator
void menu(){
    cout << YELLOW << "\t\t\t\t\t";
    for(int i = 0; i <= 50; i++){
        cout << "-";
        Sleep(10);
    }
    printf("\n\t\t\t\t\t\t\t\t%-20s", "Menu");
    Sleep(500);
    cout << "\n\t\t\t\t\t";
    for(int i = 0; i <= 50; i++){
        cout << "-";
        Sleep(10);
    }
    printf("\n\t\t\t\t\t\t\t%-20s", "1. Add New Product");
    Sleep(500);
    printf("\n\t\t\t\t\t\t\t%-20s", "2. View All Product");
    Sleep(500);
    printf("\n\t\t\t\t\t\t\t%-20s", "3. Update Product");
    Sleep(500);
    printf("\n\t\t\t\t\t\t\t%-20s", "4. Delete Product");
    Sleep(500);
    printf("\n\t\t\t\t\t\t\t%-20s", "5. Quit");
    Sleep(500);
    cout << "\n\t\t\t\t\t";
    for(int i = 0; i <= 50; i++){
        cout << "-";
        Sleep(10);
    }
    cout << RESET;
}

// Click login as User
void loginAsUser(){
    cout << R"(
                    1. View Product List
                    2. Search 
                    0. Back

                    Choice:
    )";
}