#include "../include/Design_Structure.h"
#include "../include/ProductList.h"
#include "../include/MonthlyReport.h"

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
    return 0;
}
