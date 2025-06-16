#include <iostream>
#include <windows.h>
#include <stdio.h>
using namespace std;

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define WHITE "\033[37m"

// void loading(int width = 50, int delay = 50){
//     cout << YELLOW << "[";

//     for (int i = 0; i < width; i++){
//         cout << "-";
//     }
//     cout << "]\r["; 
//     for (int i = 0; i <= width; i++){
//         cout << GREEN << "=";
//         Sleep(delay);
//     }
//     cout << YELLOW << "]" << RESET << endl;
//     cout << "Loading Complete!\n";
// }

// another loading style
void loading(){
    cout << GREEN;
    system("cls");
    //printf("\e[?251");

    // We use ASCII to print special character
    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    int bar1 = 177, bar2 = 219;

    cout << "\n\n\n\t\t\t\tLoading...";
    cout << "\n\n\t\t\t\t";

    for (int i = 0; i < 30; i++){
        cout << (char)bar1;
    }
    cout << "\r";
    cout << "\t\t\t\t";
    for (int i = 0; i < 30; i++){
        cout << (char)bar2;
        Sleep(50);
    }
    cout << "\n\n\t\t\t\t" << (char)1;
    system("Pause");
}

int main(){

    // loading();
    loading();

    return 0;
}