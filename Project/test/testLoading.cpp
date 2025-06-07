#include <iostream>
#include <windows.h>
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define WHITE   "\033[37m"

void loading(int width = 50, int delay = 50){
    cout << YELLOW << "[";

    for(int i = 0; i < width; i++){
        cout << "-";
    }
    cout << "]\r["; // It goes back to the beginning and write the new one
    for(int i = 0; i <= width; i++){
        cout << GREEN << "=";
        Sleep(delay);
    }
    cout << YELLOW << "]" << RESET << endl;
    cout << "Loading Complete!\n";
}

int main(){

    loading();

    return 0;
}