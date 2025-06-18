#include "../include/Design_Structure.h"
#include "../include/ProductList.h"

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
    // cout <<endl;
    // displayUserProductList(myList);

    // ProductElement *curr = myList->head;
    // while(curr != nullptr){
    //     addReport(rl , curr);
    //     curr = curr->next;
    // }

    // displayMonthlyReport(rl);
    // cout << endl;

    // Testing Stack
    Stack* s = createStack();

    ProductElement *curr = myList->head;
    while(curr != nullptr){
        push(s, curr, "Phone", 100, "IN", "2025-06-16 10:30:00");
        curr = curr->next;
    }

    displayStack(s);

    // displayProductByID(myList, 1004); // search not exist productID
    // displayProductByID(myList, 999); // search not exist productID
    // displayProductByID(myList, 1000); // search correct ProductID

    // cout << "\nDeleted: \n";

    // deleteProductByID(myList, 1004); // delete not exist productID
    // deleteProductByID(myList, 999); // delete not exist productID
    // deleteProductByID(myList, 1000); // delete first ProductID

    // displayAdminProductList(myList);

    // deleteProductByID(myList, 1002); // delete last ProductID

    // displayAdminProductList(myList);
    // addProduct(myList, "Iphone 14", 1, 5, "IOS, Ram 8GB, Storage 256GB", 1411.10, 1600.10);
    // displayAdminProductList(myList);
    return 0;
}
