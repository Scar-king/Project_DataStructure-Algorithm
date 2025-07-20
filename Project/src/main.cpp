#include "../include/Design_Structure.h"
#include "../include/ProductList.h"

using namespace std;

int main() {

    // welcome();

    // menu();

    // loginPage();

    // viewTableMenu();

    ProductList *myList = createList();
    ReportList *rl = createReportList();

    addProduct(myList, "Iphone 13 PRO MAX", 5, 20, "IOS, Ram 8GB, Storage 256GB", 899.99, 999.99);
    addProduct(myList, "Iphone 16 PRO", 10, 11, "IOS, Ram 8GB, Storage 1T", 1299.99, 1499.99);
    addProduct(myList, "Iphone 14 PRO MAX", 0, 30, "IOS, Ram 8GB, Storage 128GB", 999.99, 1399.99);

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

    return 0;
}


