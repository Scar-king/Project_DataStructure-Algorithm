#include <string>
#include <iostream>
#include <cstdio>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <windows.h>
#include <regex>

#include "validation.h"

using namespace std;

struct ProductElement { // We are using Doubly List.
    int id, inStock, sold;
    string model, description, status;
    double purchaseCost, salePrice;
    ProductElement *next;
    ProductElement *prev;
};

struct ProductList {
    int n, i;
    ProductElement *head;
    ProductElement *tail;
};

ProductList *createList(){
    ProductList *ls = new ProductList;
    ls-> n = 0;
    ls -> i = 1000;
    ls->head = nullptr;
    ls->tail = nullptr;
    return ls;
}

// We're using Add End Algorithm
void addProduct(ProductList *ls, string model, int inStock, int sold, string description, double purchaseCost, double salePrice, bool isLoadData, int id) {
    ProductElement *p = new ProductElement;

    if (isLoadData) {
        p->id = id;
        ls->i = id;
    } else {
        p->id = ls->i;
    }

    p -> model = model;
    p -> inStock = inStock;
    p -> sold = sold;
    p -> description = description;
    p -> purchaseCost = purchaseCost;
    p -> salePrice = salePrice;
    p -> next = nullptr;
    p -> prev = ls -> tail;

    if (inStock == 0) {
        p->status = "\033[31mOut of Stock\033[0m";   
    } else if (inStock <= static_cast<int>((inStock + sold) * 0.25)){
        p->status = "\033[33mLow Stock\033[0m   ";  
    } else {
        p->status = "\033[32mAvailable\033[0m   ";  
    }

    if(ls->n == 0){
        ls->head = p;
    } else {
        ls->tail->next = p; 
    }
    ls->tail = p;
    ls->n++;
    ls->i++;
}

void storeProduct(ProductList *ls) { // Implemented by Sokleap
    ofstream productFile("../data/ProductList.csv");
    ProductElement *temp = ls->head;
    while(temp != nullptr) {
        productFile << temp->id << "|" << temp->model << "|" << temp->inStock << "|" << temp->sold << "|" 
                    << temp->description << "|" << temp->purchaseCost << "|" << temp->salePrice << endl;
        temp = temp -> next;
    }

    productFile.close();
}

void updateProductById(ProductList *ls, ProductElement* temp, int targetId) { // Update Product by ID (Davin)

    if(temp == nullptr) {
        cout << RED << INDENT << "Product with ID " << targetId << " not found.\n" << RESET;
        return;
    }

    cout << YELLOW;
    cout << "\n" << INDENT << "Updating Product ID: " << targetId << "\n";
    cout << INDENT << "Current model: " << temp->model << "\n" << INDENT << "New model: ";
    cin.ignore();
    getline(cin, temp->model);

    temp->inStock = getValidateIntInRange(INDENT + "Enter new quantity in stock (1-1000): ", MIN_STOCK, MAX_STOCK);
    temp->sold = getValidateIntInRange(INDENT + "Enter new quantity sold (1-1000): ", MIN_STOCK, MAX_STOCK);
    
    cout << INDENT << "New description: ";
    getline(cin, temp->description);

    temp->purchaseCost = getValidateDoubleInRange(INDENT + "New purchase cost($1.00 - $10000.00): ", MIN_PRICE, MAX_PRICE);
    temp->salePrice = getValidateDoubleInRange(INDENT + "New sale price($1.00 - $10000.00): ", MIN_PRICE, MAX_PRICE);
    cout << RESET;

    if(temp->inStock == 0) { // Update status
        temp->status = "\033[31mOut of Stock\033[0m";
    } else if(temp->inStock <= static_cast<int>((temp->inStock + temp->sold) * 0.25)) {
        temp->status = "\033[33mLow Stock\033[0m   ";
    } else {
        temp->status = "\033[32mAvailable\033[0m   ";
    }

    storeProduct(ls);

    cout << GREEN << INDENT << "Product updated successfully.\n" << RESET;
}

ProductElement* searchProductByID(ProductList *ls, int ID) { // Implemented by Sokleap (Search Product by ID)
    ProductElement* temp = ls->head;
    while(temp != nullptr){
        if(temp->id == ID){
            return temp;
        } 
        temp = temp->next;
    }
    return nullptr;
}

void deleteProductByID(ProductList* ls, ProductElement* temp) { // Implemented by Sokleap (Delete Product by ID)
    if(temp != nullptr){
        if(ls->n == 1){
            ls->head = nullptr;
            ls->tail = nullptr;
        }
        else{
            // 1 2 3 4
            // delete 1 -> temp = 1, prev of temp = nullptr;
            if(temp->prev == nullptr){
                temp->next->prev = nullptr;
                ls->head = temp->next;
            }
            else{
                // 1 2 3 4
                // delete 4 -> temp = 4, next of temp = nullptr;
                temp->prev->next = temp->next; 
                ls->tail = temp->prev;
            }
        }
        delete temp;
        ls->n--;
        storeProduct(ls);
        cout << GREEN << INDENT << "Successfully deleted product!\n" << RESET;
        return;
    }
    cout << "\n" << RED << INDENT << "Entered ID not found, Please try again...\n" << RESET;
}

// *** Sort Product using Quick Sort Algorithm ***, Implemented by Davin
void swapProduct(ProductElement *a, ProductElement *b) { // Quick Sort property
    swap(a->id, b->id);
    swap(a->model, b->model);
    swap(a->inStock, b->inStock);
    swap(a->sold, b->sold);
    swap(a->description, b->description);
    swap(a->purchaseCost, b->purchaseCost);
    swap(a->salePrice, b->salePrice);
    swap(a->status, b->status);
}

ProductElement *Partition(ProductElement *low, ProductElement *high, bool ascending) {
    double pivot = low->salePrice;
    ProductElement *start = low;
    ProductElement *end = high;

    while(start != end) {
        // Adjust comparisons based on ascending flag
        while(end != start && (ascending ? end->salePrice > pivot : end->salePrice < pivot)) {
            end = end->prev;
        }

        while(start != end && (ascending ? start->salePrice <= pivot : start->salePrice >= pivot)) {
            start = start->next;
        }

        if(start != end) {
            swapProduct(start, end);
        }
    }

    swapProduct(low, end);
    return end;
}

void QuickSort(ProductElement *low, ProductElement *high, bool ascending) {
    if(low && high && low != high && low != high->next) {
        ProductElement *pivotNode = Partition(low, high, ascending);
        QuickSort(low, pivotNode->prev, ascending);
        QuickSort(pivotNode->next, high, ascending);
    }
}

void quickSort(ProductList *ls, bool ascending = false) {

    QuickSort(ls->head, ls->tail, ascending);

}

void displayProductByID(ProductList* ls, int ID) { // Display Product By ID
    ProductElement* temp = searchProductByID(ls, ID);
    if(temp != nullptr){
        cout << "\n+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
        printf("| %-5s | %-20s | %-5s | %-5s | %-35s | %-16s | %-13s | %-12s |\n","ID", "MODEL", "STOCK", "SOLD", "DESCRIPTION", "PURCHASE COST($)","SALE PRICE($)", "STATUS");
        cout << "+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
        printf("| %5d | %-20s | %5d | %5d | %-35s | %16.2f | %13.2f | %-12s |\n", temp -> id, temp -> model.c_str(), temp -> inStock, temp -> sold, temp -> description.c_str(), temp -> purchaseCost, temp -> salePrice, temp -> status.c_str());
        cout << "+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
        return;
    }
    cout << RED << INDENT << "Product not found!\n" << RESET;
}

void displayBestSelling(ProductList *ls) { // Display Top 5 Best Selling Product (Davin)

    if(ls->n == 0) {
        cout << RED << INDENT << "No products available.\n" << RESET;
    }

    // Copy products into an array for sorting
    ProductElement *arr[ls->n];
    ProductElement *temp = ls->head;
    int index = 0;
    while(temp != nullptr) {
        arr[index++] = temp;
        temp = temp->next;
    }

    // Sort by sold (Descending) using simple Bubble Sort
    for(int i = 0; i < ls->n - 1; i++) {
        for(int j = 0; j < ls->n - i - 1; j++) {
            if(arr[j]->sold < arr[j + 1]->sold) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }

    cout << "\n" << YELLOW << INDENT << "=== Top 5 Best-Selling Products ===\n" << RESET;
    cout << "\n+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
    printf("| %-5s | %-20s | %-5s | %-5s | %-35s | %-16s | %-13s | %-12s |\n","ID", "MODEL", "STOCK", "SOLD", "DESCRIPTION", "PURCHASE COST($)","SALE PRICE($)", "STATUS");
    cout << "+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";

    for(int i = 0; i < min(5, ls->n); i++) {
        printf("| %5d | %-20s | %5d | %5d | %-35s | %16.2f | %13.2f | %-12s |\n", 
        arr[i]->id, arr[i]->model.c_str(), arr[i]->inStock, arr[i]->sold, arr[i]->description.c_str(), arr[i]->purchaseCost, arr[i]->salePrice, arr[i]->status.c_str());
    }
    cout << "+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
}

void displayLowStockProducts(ProductList *ls) { // View Low-Stock Products (Davin)
    if(ls->n == 0) {
        cout << RED << INDENT << "No products available.\n" << RESET;
        return; 
    }

    bool found = false;
    cout << "\n" << INDENT << YELLOW << "=== Low-Stock Products (<= 25% of total stock) ===\n" << RESET;
    cout << "\n+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
    printf("| %-5s | %-20s | %-5s | %-5s | %-35s | %-16s | %-13s | %-12s |\n",
           "ID", "MODEL", "STOCK", "SOLD", "DESCRIPTION", "PURCHASE COST($)", "SALE PRICE($)", "STATUS");
    cout << "+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n"; 

    ProductElement *temp = ls->head;
    while(temp != nullptr) {
        int total = temp->inStock + temp->sold;
        if(total > 0 && temp->inStock <= static_cast<int>(total * 0.25)) {
            found = true;
            printf("| %5d | %-20s | %5d | %5d | %-35s | %16.2f | %13.2f | %-12s |\n",
                   temp->id, temp->model.c_str(), temp->inStock, temp->sold,
                   temp->description.c_str(), temp->purchaseCost, temp->salePrice, temp->status.c_str());
        }
        temp = temp->next;
    }

    if(!found) {
        cout << RED << INDENT << "No low-stock products found.\n" << RESET;
    }

    cout << "+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
}

void displayAdminProductList(ProductList *ls) { // Display Admin Product List (Sokleap)
    ProductElement *temp = ls->head;
    cout << "\n+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
    printf("| %-5s | %-20s | %-5s | %-5s | %-35s | %-16s | %-13s | %-12s |\n","ID", "MODEL", "STOCK", "SOLD", "DESCRIPTION", "PURCHASE COST($)","SALE PRICE($)", "STATUS");
    cout << "+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
    while(temp != nullptr){
        printf("| %5d | %-20s | %5d | %5d | %-35s | %16.2f | %13.2f | %-12s |\n", 
        temp -> id, temp -> model.c_str(), temp -> inStock, temp -> sold, temp -> description.c_str(), temp -> purchaseCost, temp -> salePrice, temp -> status.c_str());
        temp = temp->next;
    }
    cout << "+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
}

void displayUserProductList(ProductList *ls) { // Display User Product List (Kheang Ann), Not include *** inStock and sold ***
    ProductElement *temp = ls->head;
    cout << "+-------+----------------------+-------------------------------------+----------+--------------+" << endl;
    printf("| %-5s | %-20s | %-35s | %-8s | %-12s |\n", "ID","MODEL", "DESCRIPTION", "PRICE($)", "STATUS");
    cout << "+-------+----------------------+-------------------------------------+----------+--------------+" << endl;
    while(temp != nullptr){
        printf("| %-5d | %-20s | %-35s | %8.2f | %-12s |\n", temp->id, temp->model.c_str(), temp->description.c_str(), temp-> salePrice, temp->status.c_str());
        temp = temp->next;
    }
    cout << "+-------+----------------------+-------------------------------------+----------+--------------+" << endl;
}

void clearProductList(ProductList *ls) {
    ProductElement *current = ls->head;
    while (current != nullptr) {
        ProductElement *nextNode = current->next;
        delete current;
        current = nextNode;
    }
    ls->head = nullptr;
    ls->tail = nullptr;
    ls->n = 0;
    ls->i = 1000;
}

void loadProductList(ProductList *ls) { // Sokleap
    ifstream productFile("../data/ProductList.csv");

    if (!productFile){
        cout << RED << INDENT << "Error: ProductList.csv not found.\n" << RESET; 
        return; // File doesn't exist yet
    }

    clearProductList(ls); // Reset before 

    string history;
    string arrayString[8]; // Allow space for an optional 8th column (status)
    string token;

    while(getline(productFile, history)) {
        if(history.empty()) continue; // Skip blank lines

        stringstream ss(history);
        int index = 0;

        while(getline(ss, token, '|') && index < 8) {
            arrayString[index++] = token;
        }

        // Validate row (must have at least 7 fields for a product)
        if(index < 7) {
            cout << RED << INDENT << "Warning: Skipped invalid row in ProductList.csv\n" << RESET;
            continue;
        }

        try {
            int id = stoi(arrayString[0]);
            string model = arrayString[1];
            int inStock = stoi(arrayString[2]);
            int sold = stoi(arrayString[3]);
            string description = arrayString[4];
            double purchaseCost = stod(arrayString[5]);
            double salePrice = stod(arrayString[6]);
    
            addProduct(ls, model, inStock, sold, description, purchaseCost, salePrice, true, id);
        }
        catch(...) {
            cout << RED << INDENT << "Warning: Skipped a corrupted row (conversion error)\n" << RESET;
        }
    }

    productFile.close();
}

struct ReportElement { // Davin
    int id, totalStock, totalSold;
    double totalPurchaseCost, totalEarn, profit, estimatProfit;
    ProductElement *product;
    ReportElement *next;
    ReportElement *prev;
};

struct ReportList {
    int n;
    ReportElement *head;
    ReportElement *tail;
};

ReportList *createReportList(){
    ReportList *rl = new ReportList;
    rl->n = 0;
    rl->head = nullptr;
    rl->tail = nullptr;
    return rl;
}

void addReport(ReportList *rl, ProductElement *p) { // We're using Add End Algorithm
    ReportElement *re = new ReportElement;
    re->product = p;
    re->id = p->id;
    
    int totalStock = p->inStock;
    int totalSold = p->sold;
    double totalPurchaseCost = p->purchaseCost * totalSold;
    double totalEarn = p->salePrice * totalSold;
    double profit = totalEarn - totalPurchaseCost;
    double estimatProfit = profit + (totalStock * (p->salePrice - p->purchaseCost));

    re->totalStock = totalStock;
    re->totalSold = totalSold;
    re->totalPurchaseCost = totalPurchaseCost;
    re->totalEarn = totalEarn;
    re->profit = profit;
    re->estimatProfit = estimatProfit;

    re->next = nullptr;
    re->prev = rl -> tail;

    if(rl->n == 0){
        rl->head = re;
    }
    else{
        rl->tail->next = re; 
    }
    rl->tail = re;
    rl->n++;
}

void displayOverallReport(ReportList *rl) { 
    if(rl == nullptr || rl->head == nullptr) {
        cout << "\nNo report data available.\n";
        return;
    }

    ofstream reportFile("../data/OverallReport.csv");
    ReportElement *temp = rl->head;

    cout << "\n+-------+----------------------+--------------+-------+----------------------+-------------+-------------+------------------+\n";
    printf("| %-5s | %-20s | %-12s | %-5s | %-20s | %-11s | %-11s | %-16s |\n",
           "ID", "MODEL", "TOTAL STOCK", "SOLD", "TOTAL PURCHASE COST", "TOTAL EARN", "PROFIT", "ESTIMATE PROFIT");
    cout << "+-------+----------------------+--------------+-------+----------------------+-------------+-------------+------------------+\n";

    while (temp != nullptr) {
        printf("| %-5d | %-20s | %-12d | %-5d | %-20.2f | %-11.2f | %-11.2f | %-16.2f |\n",
               temp->id, temp->product->model.c_str(), temp->totalStock, temp->totalSold,
               temp->totalPurchaseCost, temp->totalEarn, temp->profit, temp->estimatProfit);

        // Save clean | separated data
        reportFile << temp->id << "|"
             << temp->product->model << "|"
             << temp->totalStock << "|"
             << temp->totalSold << "|"
             << temp->totalPurchaseCost << "|"
             << temp->totalEarn << "|"
             << temp->profit << "|"
             << temp->estimatProfit << "\n";
        
        temp = temp->next;
    }
    cout << "+-------+----------------------+--------------+-------+----------------------+-------------+-------------+------------------+\n";

    reportFile.close();
}

void printBar(int blocks, char symbol, const string &color) { // Davin
    cout << color;
    for (int i = 0; i < blocks; i++) {
        cout << symbol;
    }
    cout << RESET;
}

void clearReportList(ReportList *rl) {
    ReportElement *current = rl->head;
    while (current != nullptr) {
        ReportElement *toDelete = current;
        current = current->next;
        delete toDelete;
    }
    rl->head = nullptr;
}

// Draw a bar chart using the data from ReportList
void graphVisualization(ReportList *rl) {
    if(rl == nullptr || rl->head == nullptr) {
        cout << "\n" << RED << INDENT << "No report data to visualize.\n" << RESET;
        return;
    }

    // Set console to CP437 for ASCII block charaters
    SetConsoleCP(437);
    SetConsoleOutputCP(437);

    char block = 178;     // Solid block (ASCII)
    double scale = 500.0; // 1 block = $500

    cout << "\n" << YELLOW << "Profit Visualization (Green = Profit, Red = Estimate Profit)\n" << RESET;
    cout << YELLOW << "===================================================================\n" << RESET;

    ReportElement *temp = rl->head;
    while(temp != nullptr) {
        // Calculate blocks for profit and estimated profit
        int profitBlocks = temp->profit / 500;
        int estimateBlocks = (temp->estimatProfit - temp->profit) / 500; // only the difference


        // Display product name and bars
        cout << setw(20) << left << temp->product->model << YELLOW << " | " << RESET;
        printBar(profitBlocks, block, GREEN);
        printBar(estimateBlocks, block, BLUE);
        cout << "\n";

        temp = temp->next;
    }

    cout << "\n" << YELLOW << "Legend: " << RESET;
    printBar(2, block, GREEN); cout << YELLOW << " = Profit, " << RESET;
    printBar(2, block, BLUE); cout << YELLOW << " = Estimated Profit (1 block approximately $500)\n" << RESET;
}

struct AdminHistory { // Sokleap
    string adminName, commandType, description, cambodiaStringTime;
    AdminHistory *next;
};

struct AdminHistoryStack {
    int size;
    AdminHistory *top;
};

AdminHistoryStack *createEmptyStack() {
    AdminHistoryStack *s = new AdminHistoryStack();
    s->size = 0;
    s->top = nullptr;
    return s;
}

chrono::system_clock::time_point getCurrentUTCTime() {
    chrono::system_clock::time_point utc_time_point = std::chrono::system_clock::now();
    return utc_time_point;
}

string getCambodiaTime() {

    const std::chrono::hours CAMBODIA_OFFSET = std::chrono::hours(7); // ICT is UTC+07:00

    chrono::system_clock::time_point cambodia_time_point = getCurrentUTCTime() + CAMBODIA_OFFSET;

    std::time_t cambodiaTimeT = std::chrono::system_clock::to_time_t(cambodia_time_point);

    std::tm *cambodiaTime = std::gmtime(&cambodiaTimeT);

    char timeBuffer[30];
    strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M:%S", cambodiaTime);

    return string(timeBuffer);
}

void addHistory(AdminHistoryStack *s, string adminName, string commandType, string description, string cambodiaStringTime) {
    AdminHistory *history = new AdminHistory;

    history->adminName = adminName;
    history->commandType = commandType;
    history->description = description;
    history->cambodiaStringTime = cambodiaStringTime;
    history->next = s->top;
    s->top = history;
    s->size++;
}

void clearAdminHistory(AdminHistoryStack *s) {
    while (s->top != nullptr) {
        AdminHistory *temp = s->top;
        s->top = s->top->next;
        delete temp;
    }
    s->size = 0;
}

// Helper to apply color based on type
string colorizeType (const string &type) {
    if (type == "ADD") {
        return string(ADD_COLOR) + type + RESET;
    }

    if (type == "UPDATE") {
        return string(UPDATE_COLOR) + type + RESET;
    }

    if (type == "DELETE") {
        return string(DELETE_COLOR) + type + RESET;
    }

    if (type == "BACKUP") {
        return string(BACKUP_COLOR) + type + RESET;
    }

    if(type == "RESTORE") {
        return string(RESTORE_COLOR) + type + RESET;
    }

    return type;
}

// Utility to remove ANSI escape codes (for correct width calculation)
string stripColor(const string &str) {
    static const regex ansiEscape("\033\\[[0-9;]*m");
    return regex_replace(str, ansiEscape, "");
}

void displayHistory(int i, AdminHistory *temp) {
    // Colorize TYPE
    string typeColored = colorizeType(temp->commandType);

    string descPlain = temp->description;

    // Column widths
    const int typeColWidth = 10;
    const int descColWidth = 50;

    // Calculate padding for TYPE (strip color codes for width)
    int typeVisibleLen = stripColor(typeColored).length();
    int typePad = max(0, typeColWidth - typeVisibleLen);

    // Calculate padding for DESCRIPTION
    int descVisibleLen = stripColor(descPlain).length();
    int descPad = max(0, descColWidth - descVisibleLen);

    // Now print each column manually with padding
    cout << "| " << setw(4) << i
         << " | " << setw(20) << temp->adminName
         << " | " << typeColored << string(typePad, ' ')
         << " | " << descPlain << string(descPad, ' ')
         << " | " << setw(20) << temp->cambodiaStringTime
         << " |" << endl;
}

void displayAllAdminHistory(AdminHistoryStack *s) {
    if(s -> size == 0){
        cout << RED << INDENT << "\nNo admin history found.\n" << RESET;
        return;
    }

    AdminHistory *temp = s->top;
    int i = 1;

    while (temp != nullptr)
    {
        if (i == 1)
        {
            cout << "\n" << YELLOW << INDENT << "--- All Admin History ---\n" << RESET;
            cout << "\n+------+----------------------+------------+----------------------------------------------------+----------------------+\n";
            printf("| %4s | %-20s | %-10s | %-50s | %-20s |\n",
                   "N0","NAME", "TYPE", "DESCRIPTION", "HISTORY TIME");
            cout << "+------+----------------------+------------+----------------------------------------------------+----------------------+\n";
        }
        displayHistory(i, temp);
        temp = temp->next;
        i++;
    }
    cout << "+------+----------------------+------------+----------------------------------------------------+----------------------+\n";
}

time_t stringToTimeT(const string &datetimeStr) {
    tm tm{};
    stringstream ss(datetimeStr);
    ss >> get_time(&tm, "%d/%m/%Y %H:%M:%S");
    return mktime(&tm);
}

void displayLastDayHistory(AdminHistoryStack *s) {
    auto twentyFourHoursAgo = getCurrentUTCTime() - chrono::hours(24);
    time_t twentyFourHoursAgo_t = chrono::system_clock::to_time_t(twentyFourHoursAgo);
    AdminHistory *temp = s->top;
    int i = 1;
    bool found = false;
    while (temp != nullptr)
    {
        time_t recordTime = stringToTimeT(temp->cambodiaStringTime);
        if (recordTime >= twentyFourHoursAgo_t)
        {
            if (i == 1)
            {
                cout << "\n" << YELLOW << INDENT << "--- Admin History within the last 24 hours ---\n" << RESET;
                cout << "\n+------+----------------------+------------+----------------------------------------------------+----------------------+\n";
                printf("| %4s | %-20s | %-10s | %-50s | %-20s |\n",
                       "N0", "NAME", "TYPE", "DESCRIPTION", "HISTORY TIME");
                cout << "+------+----------------------+------------+----------------------------------------------------+----------------------+\n";
            }
            displayHistory(i, temp);
            found = true;
            i++;
        }
        temp = temp->next;
    }
    cout << "+------+----------------------+------------+----------------------------------------------------+----------------------+\n";
    if (!found)
    {
        cout << "\n" << RED << INDENT << "No admin history found within the last 24 hours.\n" << RESET;
    }
}

time_t getOneMonthAgoTime() {
    time_t now = time(nullptr);
    struct tm *tmNow = localtime(&now);
    tmNow->tm_mon -= 1;
    if (tmNow->tm_mon < 0)
    {
        tmNow->tm_mon += 12;
        tmNow->tm_year -= 1;
    }
    return mktime(tmNow);
}

void displayLastMonthHistory(AdminHistoryStack *s) {
    AdminHistory *temp = s->top;
    int i = 1;
    bool found = false;
    time_t oneMonthAgo = getOneMonthAgoTime();
    while (temp != nullptr)
    {
        time_t recordTime = stringToTimeT(temp->cambodiaStringTime);
        if (recordTime >= oneMonthAgo)
        {
            if (i == 1)
            {
                cout << "\n" << YELLOW << INDENT << "--- Admin History within the last 30 days ---\n" << RESET;
                cout << "\n+------+----------------------+------------+----------------------------------------------------+----------------------+\n";
                printf("| %4s | %-20s | %-10s | %-50s | %-20s |\n",
                       "N0", "NAME", "TYPE", "DESCRIPTION", "HISTORY TIME");
                cout << "+------+----------------------+------------+----------------------------------------------------+----------------------+\n";
            }
            displayHistory(i, temp);
            found = true;
            i++;
        }
        temp = temp->next;
    }

    cout << "+------+----------------------+------------+----------------------------------------------------+----------------------+\n";
    if (!found)
    {
        cout << "\n" << RED << INDENT << "No admin history found within the last 30 days.\n" << RESET;
    }
}

void storeAdminHistory(AdminHistory *temp) {
    ofstream historyFile("../data/History.csv", ios::app);
    historyFile << temp->adminName << "|" << temp->commandType << "|" << temp->description << "|" << temp->cambodiaStringTime << endl;
    historyFile.close();
}

void loadAdminHistoryStack(AdminHistoryStack *s) {
    ifstream historyFile("../data/History.csv");
    string history;
    string arrayString[4];
    string token;
    while (getline(historyFile, history))
    {
        stringstream ss(history);
        int index = 0;

        while (getline(ss, token, '|'))
        {
            arrayString[index] = token;
            index++;
        }

        string adminName = arrayString[0];
        string commandType = arrayString[1];
        string description = arrayString[2];
        string time = arrayString[3];

        addHistory(s, adminName, commandType, description, time);
    }
    historyFile.close();
}

void backupProductData(ProductList *ls) {
    // Always save the latest data to ProductList.csv before backup
    storeProduct(ls);

    ifstream src("../data/ProductList.csv", ios::binary);
    if (!src) {
        cout << RED << INDENT << "Error: ProductList.csv not found. Backup aborted.\n" << RESET;
        return;
    }

    // Check if ProductList.csv is empty
    src.seekg(0, ios::end);
    if (src.tellg() == 0) {
        cout << RED << INDENT << "Error: ProductList.csv is empty. Backup not created (to avoid wiping a good backup).\n" << RESET;
        return;
    }
    src.seekg(0, ios::beg);

    ofstream dst("../data/Backup_ProductList.csv", ios::binary);
    dst << src.rdbuf();

    cout << GREEN << INDENT << "Backup completed successfully (" << ls->n << " product(s) saved).\n" << RESET;
}


void restoreProductData(ProductList *ls) {
    ifstream src("../data/Backup_ProductList.csv", ios::binary);
    if (!src) {
        cout << RED << INDENT << "Error: Backup file not found. Cannot restore.\n" << RESET;
        return;
    }

    // Check if backup file is empty
    src.seekg(0, ios::end);
    if (src.tellg() == 0) {
        cout << RED << INDENT << "Error: Backup file is empty. Restore aborted (to protect your current data).\n" << RESET;
        return;
    }
    src.seekg(0, ios::beg);

    // Overwrite ProductList.csv with backup
    ofstream dst("../data/ProductList.csv", ios::binary);
    dst << src.rdbuf();

    cout << GREEN << INDENT << "Restore completed successfully.\n" << RESET;

    // Reload into memory and show debug info
    loadProductList(ls);
}