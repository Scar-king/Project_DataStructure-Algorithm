#include "../include/Design_Structure.h"
#include "../include/ProductList.h"
#include "../include/MonthlyReport.h"
#include "../include/TransactionReport.h"

using namespace std;

int main() {

    // welcome();

    // menu();

    List *myList = createList();
    ReportList *rl = createReportList();

    addEnd(myList, "Iphone 11", 10, 10, "IOS, Ram 8GB, Storage 256GB", 1111.10);
    addEnd(myList, "Iphone 12", 3, 10, "IOS, Ram 8GB, Storage 256GB", 1111.10);
    addEnd(myList, "Iphone 13", 10, 9, "IOS, Ram 8GB, Storage 256GB", 1111.10);
    displayAdminProductList(myList);
    cout <<endl<<endl;
    displayUserProductList(myList);

    addReport(rl, "iPhone 14 Pro", 47, 50, 1000.00, 2000.00, 3000.00, 5000.00);
    addReport(rl, "iPhone 13 Pro", 47, 50, 1000.00, 2000.00, 3000.00, 5000.00);
    addReport(rl, "iPhone X", 47, 50, 1000.00, 2000.00, 3000.00, 5000.00);
    displayMonthlyReport(rl);
    cout << endl;

    Stack* s = createStack();

    push(s, 1, "iPhone 17 Pro Max", "Phone", 2, "OUT", 1599.99, "2025-06-16 10:30:00");
    push(s, 2, "MacBook Air M3", "Laptop", 1, "IN", 1299.00, "2025-06-16 11:00:00");

    displayStack(s);

    return 0;
}
