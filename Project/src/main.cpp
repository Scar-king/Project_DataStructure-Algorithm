#include "../include/Design_Structure.h"
#include "../include/LinkedList.h"

using namespace std;

int main() {

    welcome();

    menu();

    List *myList = createList();

    addBeg(myList, "iPhone", 1, 10.0); 

    cout << "\nList: ";
    displayBeg(myList);

    return 0;
}
