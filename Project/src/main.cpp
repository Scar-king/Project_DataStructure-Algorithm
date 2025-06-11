#include "../include/Design_Structure.h"
#include "../include/LinkedList.h"

using namespace std;

int main() {

    welcome();

    menu();

    List *myList = createList();

    addBeg(myList, "iPhone", 1, 10.0); 
    addEnd(myList, "Samsung", 1, 99.99);
    addEnd(myList, "Oppo", 1, 1.99);
    cout << "\nList: ";
    displayBeg(myList);
    deletePos(myList, 0);
    deletePos(myList, 1);

    return 0;
}
