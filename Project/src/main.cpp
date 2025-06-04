/* 
    Note. How to Complie this project:
    Open Terminal
    cd Project
    g++ -std=c++17 -Wall -Iinclude src\Database.cpp src\Design_Structure.cpp src\LinkedList.cpp src\main.cpp -o main.exe
    ./main 
 */

#include <iostream>
#include "Database.h" // Not yet Implement
#include "Design_Structure.h"
#include "LinkedList.h"
using namespace std;

int main() {

    welcome();

    List *myList = createList();

    for(int i = 1; i <= 10; i++){
        addBeg(myList, i);
    }

    cout << "List: ";
    display(myList);

    return 0;
}
