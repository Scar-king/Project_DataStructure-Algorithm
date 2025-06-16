#include "../include/Design_Structure.h"
#include "../include/ProductList.h"

using namespace std;

int main() {

    // welcome();

    // menu();

    List *myList = createList();
    addEnd(myList, "Iphone 11", 10, 10, "IOS, Ram 8GB, Storage 256GB", 1111.10);
    addEnd(myList, "Iphone 12", 3, 10, "IOS, Ram 8GB, Storage 256GB", 1111.10);
    addEnd(myList, "Iphone 13", 10, 9, "IOS, Ram 8GB, Storage 256GB", 1111.10);
    displayAdminProductList(myList);
    cout <<endl<<endl;
    displayUserProductList(myList);
    return 0;
}
