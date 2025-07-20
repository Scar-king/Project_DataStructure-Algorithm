#include <string>
#include <iostream>
#include <cstdio>
#include <chrono>
#include <iomanip>
#include <sstream>

#include "validation.h"
using namespace std;

constexpr int MIN_STOCK = 0;
constexpr int MAX_STOCK = 1000;

constexpr double MIN_PRICE = 1.0;
constexpr double MAX_PRICE = 10000.0;

// Each Record must has 5 to 9 columns/fields
// We are using Doubly List
struct ProductElement {
    int id;
    string model;
    int inStock;
    int sold;
    string description;
    double purchaseCost;
    double salePrice;
    string status;
    ProductElement *next;
    ProductElement *prev;
};

// Define Linked List structure
struct ProductList {
    int n;
    int i;
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

    if(isLoadData) {
        p->id = id;
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
    if(inStock == 0){
        p -> status = "\033[31mOut of Stock\033[0m";   
    }
    else if(inStock <= static_cast<int>((inStock + sold) * 0.25)){
        p -> status = "\033[33mLow Stock\033[0m   ";  
    }
    else{
        p -> status = "\033[32mAvailable\033[0m   ";  
    }

    if(ls -> n == 0){
        ls -> head = p;
    }
    else{
        ls -> tail -> next = p; 
    }
    ls -> tail = p;
    ls -> n++;
    ls -> i++;
}

// Update Product
void updateProductById(ProductList *ls, int targetId) {
    ProductElement *temp = ls->head;
    while(temp != nullptr && temp->id != targetId) {
        temp = temp->next;
    }

    if(temp == nullptr) {
        cout << "Product with ID " << targetId << " not found.\n";
        return;
    }

    cout << "\nUpdating Product ID: " << targetId << "\n";
    cout << "Current model: " << temp->model << "\nNew model: ";
    getline(cin, temp->model);

    temp->inStock = getValidateIntInRange("Enter new quantity in stock (1-1000): ", MIN_STOCK, MAX_STOCK);
    temp->sold = getValidateIntInRange("Enter new quantity sold (1-1000): ", MIN_STOCK, MAX_STOCK);
    
    cout << "New description: ";
    getline(cin, temp->description);

    temp->purchaseCost = getValidateDoubleInRange("New purchase cost($1.00 - $10000.00): ", MIN_PRICE, MAX_PRICE);
    temp->salePrice = getValidateDoubleInRange("New sale price($1.00 - $10000.00): ", MIN_PRICE, MAX_PRICE);

    // Update status
    if(temp->inStock == 0) {
        temp->status = "\033[31mOut of Stock\033[0m";
    } else if(temp->inStock <= static_cast<int>((temp->inStock + temp->sold) * 0.25)) {
        temp->status = "\033[33mLow Stock\033[0m   ";
    } else {
        temp->status = "\033[32mAvailable\033[0m   ";
    }

    cout << "Product updated successfully.\n";
}

// Search Product by ID
ProductElement* searchProductByID(ProductList *ls, int ID) { // Sokleap
    ProductElement* temp = ls -> head;
    while(temp != nullptr){
        if(temp -> id == ID){
            return temp;
        } 
        temp = temp -> next;
    }
    return nullptr;
}

// Delete Product by ID
void deleteProductByID(ProductList* ls, int ID) { // Sokleap
    ProductElement* temp = searchProductByID(ls, ID);
    if(temp != nullptr){
        if(ls->n == 1){
            delete temp;
            ls->head = nullptr;
            ls->tail = nullptr;
        }
        else{
            // 1 2 3 4
            // delete 1 -> temp = 1, prev of temp = nullptr;
            if(temp->prev == nullptr){
                temp->next->prev = nullptr;
                ls->head = temp->next;
                delete temp;
            }
            else{
                // 1 2 3 4
                // delete 4 -> temp = 4, next of temp = nullptr;
                temp->prev->next = temp->next; 
                ls->tail = temp->prev;
                delete temp;
            }
            cout << "Successfully deleted product!\n";
        }
        ls->n--;
        return;
    }
    cout << "Cannot delete!\n";
}

// *** Sort Product using Merge Sort Algorithm ***
ProductElement *getNodeAt(ProductList *ls, int index) {
    ProductElement *current = ls->head;
    int i = 0;
    while(current != nullptr && i < index) {
        current = current->next;
        i++;
    }

    return current;
}

void Merge(ProductList *ls, int lb, int mid, int ub) {
    int i = lb;
    int j = mid + 1;
    int k = 0;
    int n = ub - lb + 1;
    int *b = new int[n];

    ProductElement *left = getNodeAt(ls, i);
    ProductElement *right = getNodeAt(ls, j);

    while(i <= mid && j <= ub) {
        if(left->salePrice > right->salePrice) {
            b[k++] = left->salePrice;
            left = left->next;
            i++;
        } else {
            b[k++] = right->salePrice;
            right = right->next;
            j++;
        }
    }

    while(i <= mid) {
        b[k++] = left->salePrice;
        left = left->next;
        i++;
    }

    while(j <= ub) {
        b[k++] = right->salePrice;
        right = right->next;
        j++;
    }

    ProductElement *current = getNodeAt(ls, lb);
    for(k = 0; k < n; k++) {
        current->salePrice = b[k];
        current = current->next;
    }

    delete[] b;
}

void MergeSort(ProductList *ls, int lb, int ub) {
    if(lb < ub) {
        int mid = (lb + ub) / 2;
        MergeSort(ls, lb, mid);
        MergeSort(ls, mid + 1, ub);
        Merge(ls, lb, mid, ub);
    }
}

void mergeSort(ProductList *ls) {
    if(ls->n > 1) {
        MergeSort(ls, 0, ls->n - 1);
    }
}

// Display Product By ID
void displayProductByID(ProductList* ls, int ID) {
    ProductElement* temp = searchProductByID(ls, ID);
    if(temp != nullptr){
        cout << "\n+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
        printf("| %-5s | %-20s | %-5s | %-5s | %-35s | %-16s | %-13s | %-12s |\n","ID", "MODEL", "STOCK", "SOLD", "DESCRIPTION", "PURCHASE COST($)","SALE PRICE($)", "STATUS");
        cout << "+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
        printf("| %5d | %-20s | %5d | %5d | %-35s | %16.2f | %13.2f | %-12s |\n", temp -> id, temp -> model.c_str(), temp -> inStock, temp -> sold, temp -> description.c_str(), temp -> purchaseCost, temp -> salePrice, temp -> status.c_str());
        cout << "+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
        return;
    }
    cout << "Product not found!\n";
}

// Display Admin Product List
void displayAdminProductList(ProductList *ls) { // Sokleap
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

// Display User Product List
void displayUserProductList(ProductList *ls) { // Kheang Ann, Not include *** inStock and sold ***
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

void storeProduct(ProductList *ls) { // Sokleap
    ofstream productFile("ProductList.csv");
    ProductElement *temp = ls->head;
    while(temp != nullptr) {
        productFile << temp->id << "|" << temp->model << "|" << temp->inStock << "|" << temp->sold << "|" 
                    << temp->description << "|" << temp->purchaseCost << "|" << temp->salePrice << "|" << temp->status << endl;
        temp = temp -> next;
    }

    productFile.close();
}

void loadProductList(ProductList *ls) { // Sokleap
    ifstream productFile("ProductList.csv");
    string history;
    string arrayString[8];
    int index;
    string token;

    while(getline(productFile, history)) {
        index = 0;
        stringstream ss(history);
        int index = 0;

        while(getline(ss, token, '|')) {
            arrayString[index++] = token;
        }

        int id = stoi(arrayString[0]);
        string model = arrayString[1];
        int inStock = stoi(arrayString[2]);
        int sold = stoi(arrayString[3]);
        string description = arrayString[4];
        double purchaseCost = stod(arrayString[5]);
        double salePrice = stod(arrayString[6]);
        string status = arrayString[7];

        addProduct(ls, model, inStock, sold, description, purchaseCost, salePrice, true, id);
    }

    productFile.close();
}

struct ReportElement { // Davin
    int id;
    string model;
    int totalStock;
    int totalSold;
    double totalPurchaseCost;
    double totalEarn;
    double profit;
    double estimatProfit;
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

// We're using Add End Algorithm
void addReport(ReportList *rl, ProductElement *p) {
    ReportElement *re = new ReportElement;
    re -> id = 1000 + rl -> n;
    re -> model = p -> model;
    
    int totalStock = p->inStock;
    int totalSold = p->sold;
    double totalPurchaseCost = p->purchaseCost * totalSold;
    double totalEarn = p->salePrice * totalSold;
    double profit = totalEarn - totalPurchaseCost;
    double estimatProfit = profit + (totalStock * (p->salePrice - p->purchaseCost));

    re -> totalStock = totalStock;
    re -> totalSold = totalSold;
    re -> totalPurchaseCost = totalPurchaseCost;
    re -> totalEarn = totalEarn;
    re -> profit = profit;
    re -> estimatProfit = estimatProfit;

    re -> next = nullptr;
    re -> prev = rl -> tail;

    if(rl -> n == 0){
        rl -> head = re;
    }
    else{
        rl -> tail -> next = re; 
    }
    rl -> tail = re;
    rl -> n++;
}

void displayOverallReport(ReportList *rl) { 
    if(rl == nullptr || rl->head == nullptr) {
        cout << "\nNo report data available.\n";
        return;
    }

    ReportElement *temp = rl->head;

    cout << "\n+-------+----------------------+--------------+-------+----------------------+-------------+-------------+------------------+\n";
    printf("| %-5s | %-20s | %-12s | %-5s | %-20s | %-11s | %-11s | %-16s |\n",
           "ID", "MODEL", "TOTAL STOCK", "SOLD", "TOTAL PURCHASE COST", "TOTAL EARN", "PROFIT", "ESTIMATE PROFIT");
    cout << "+-------+----------------------+--------------+-------+----------------------+-------------+-------------+------------------+\n";
    while (temp != nullptr) {
        printf("| %-5d | %-20s | %-12d | %-5d | %-20.2f | %-11.2f | %-11.2f | %-16.2f |\n",
               temp->id, temp->model.c_str(), temp->totalStock, temp->totalSold,
               temp->totalPurchaseCost, temp->totalEarn, temp->profit, temp->estimatProfit);
        temp = temp->next;
    }
    cout << "+-------+----------------------+--------------+-------+----------------------+-------------+-------------+------------------+\n";
}

struct AdminHistory { // Sokleap
    int adminID;
    string adminName;
    string commandType;
    string description;
    chrono::system_clock::time_point utcTime;

    AdminHistory *next;
};

struct AdminHistoryStack {
    int size;
    AdminHistory *top;
};

AdminHistoryStack *createEmptyStack() {
    AdminHistoryStack *s = new AdminHistoryStack();
    s -> size = 0;
    s -> top = nullptr;
    return s;
}

chrono::system_clock::time_point getCurrentUTCTime(){
    chrono::system_clock::time_point utc_time_point = std::chrono::system_clock::now();
    return utc_time_point;
}

string getCambodiaTime(chrono::system_clock::time_point utcTimePoint){

    const std::chrono::hours CAMBODIA_OFFSET = std::chrono::hours(7); // ICT is UTC+07:00

    chrono::system_clock::time_point cambodia_time_point = utcTimePoint + CAMBODIA_OFFSET;

    std::time_t cambodiaTimeT = std::chrono::system_clock::to_time_t(cambodia_time_point);

    std::tm* cambodiaTime = std::gmtime(&cambodiaTimeT);

    char timeBuffer[30];
    strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M:%S", cambodiaTime);
    
    return string(timeBuffer);
}

void push(AdminHistoryStack *s, int adminID, string adminName, string commandType, string description, chrono::system_clock::time_point utcTime) {
    AdminHistory* history = new AdminHistory;

    history -> adminID = adminID;
    history -> adminName = adminName;
    history -> commandType = commandType;
    history -> description = description;
    history -> utcTime = utcTime; 
    history -> next = s -> top;
    s -> top = history;
    s -> size++;
    
}

void pop(AdminHistoryStack *s){
    if(s->top == nullptr){
        cout << "Stack is empty!\n";
        return;
    } 
    AdminHistory *temp = s->top;
    s->top = s->top->next;
    delete temp;
    s->size--;
}

void displayHistory(int i, AdminHistory *temp) {
    string formattedTime = getCambodiaTime(temp->utcTime);
    printf("| %4d | %-5d | %-20s | %-10s | %-50s | %-20s |\n",
           i, temp->adminID, temp->adminName.c_str(), temp->commandType.c_str(), temp->description.c_str(), formattedTime.c_str());
}

void displayAllAdminHistory(AdminHistoryStack *s) {
    AdminHistory *temp = s->top;
    int i = 1;
    cout << "\n--- All Admin History ---\n";
    cout << "\n+------+-------+----------------------+------------+----------------------------------------------------+----------------------+\n";
    printf("| %4s | %-5s | %-20s | %-10s | %-50s | %-20s |\n",
           "N0", "ID", "NAME", "TYPE", "DESCRIPTION", "HISTORY TIME");
    cout << "+------+-------+----------------------+------------+----------------------------------------------------+----------------------+\n";
    while (temp != nullptr)
    {
        displayHistory(i, temp);
        temp = temp->next;
        i++;
    }
    cout << "+------+-------+----------------------+------------+----------------------------------------------------+----------------------+\n";
}

void displayLastDay(AdminHistoryStack *s) {
    auto twentyFourHoursAgo = getCurrentUTCTime() - chrono::hours(24);
    AdminHistory *temp = s->top;
    int i = 1;
    bool found = false;
    cout << "\n--- Admin History within the last 24 hours ---\n";
    cout << "\n+------+-------+----------------------+------------+----------------------------------------------------+----------------------+\n";
    printf("| %4s | %-5s | %-20s | %-10s | %-50s | %-20s |\n",
           "N0", "ID", "NAME", "TYPE", "DESCRIPTION", "HISTORY TIME");
    cout << "+------+-------+----------------------+------------+----------------------------------------------------+----------------------+\n";
    while (temp != nullptr)
    {
        if (temp->utcTime >= twentyFourHoursAgo)
        {
            displayHistory(i, temp);
            found = true;
            i++;
        }
        temp = temp->next;
    }
    cout << "+------+-------+----------------------+------------+----------------------------------------------------+----------------------+\n";
    if (!found)
    {
        cout << "No admin history found within the last 24 hours.\n";
    }
}

void displayLastMonth(AdminHistoryStack *s) {
    auto thirtyDaysAgo = getCurrentUTCTime() - chrono::hours(24 * 30);
    AdminHistory *temp = s->top;
    int i = 1;
    bool found = false;
    cout << "\n--- Admin History within the last 30 days ---\n";
    cout << "\n+------+-------+----------------------+------------+----------------------------------------------------+----------------------+\n";
    printf("| %4s | %-5s | %-20s | %-10s | %-50s | %-20s |\n",
           "N0", "ID", "NAME", "TYPE", "DESCRIPTION", "HISTORY TIME");
    cout << "+------+-------+----------------------+------------+----------------------------------------------------+----------------------+\n";
    while (temp != nullptr){
        if (temp->utcTime >= thirtyDaysAgo)
        {
            displayHistory(i, temp);
            found = true;
            i++;
        }
        temp = temp->next;
    }
    cout << "+------+-------+----------------------+------------+----------------------------------------------------+----------------------+\n";
    if (!found)
    {
        cout << "No admin history found within the last 30 days.\n";
    }
}