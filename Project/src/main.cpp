#include "../include/Design_Structure.h"
#include "../include/ProductList.h"
#include "../include/TransactionReport.h"

using namespace std;

int main() {

    // welcome();

    // menu();

    ProductList *myList = createList();
    ReportList *rl = createReportList();

    addProduct(myList, "Iphone 11", 3, 20, "IOS, Ram 8GB, Storage 256GB", 1011.10, 1111.10);
    addProduct(myList, "Iphone 12", 0, 30, "IOS, Ram 8GB, Storage 256GB", 1111.10, 1300.10);
    addProduct(myList, "Iphone 13", 10, 5, "IOS, Ram 8GB, Storage 256GB", 1211.10, 1400.10);

    displayAdminProductList(myList); 
    cout <<endl;
    // displayUserProductList(myList);

    ProductElement *curr = myList->head;
    while(curr != nullptr){
        addReport(rl , curr);
        curr = curr->next;
    }

    displayMonthlyReport(rl);
    cout << endl;

    // Testing Stack
    // Stack* s = createStack();

    // push(s, 1, "iPhone 17 Pro Max", "Phone", 2, "OUT", 1599.99, "2025-06-16 10:30:00");
    // push(s, 2, "MacBook Air M3", "Laptop", 1, "IN", 1299.00, "2025-06-16 11:00:00");

    // displayStack(s);

    return 0;
}
