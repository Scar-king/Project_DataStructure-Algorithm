#include "../include/Design_Structure.h"
#include "../include/LinkedList.h"

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
