// #include "../include/Design_Structure.h"
// #include "../include/ProductList.h"
#include "../include/Authentication.h"

using namespace std;

int main() {

/* Testing
    ProductList *myList = createList();
    ReportList *rl = createReportList();

    cout << "Before sorting by sale price:\n";
    displayAdminProductList(myList); 
    cout <<endl;

    updateProductById(myList, 1000);

    mergeSort(myList);

    cout << "\nAfter sorting by sale price:\n";
    displayAdminProductList(myList); 
    cout <<endl;

    displayUserProductList(myList);
    cout << endl;

    ProductElement *curr = myList->head;
    while(curr != nullptr){
        addReport(rl , curr);
        curr = curr->next;
    }

    cout << "Report List:\n";
    displayOverallReport(rl);
    cout << endl;

    AdminHistoryStack* s = createEmptyStack();
    push(s, 111, "Sok Leap", "Update", "Iphone11 sales price from 1000 to 1100", getCurrentUTCTime());
    push(s, 222, "Sok Leap", "Add", "Add Iphone11 20 units", getCurrentUTCTime());
    displayAllAdminHistory(s);
*/

/*
    REAL PROGRAM
*/

    welcome();

    Authentication();



    return 0;
}


