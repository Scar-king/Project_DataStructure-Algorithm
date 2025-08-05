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

// Doubly Linked List
struct ProductElement {
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

ProductList *createList() {
    ProductList *productList = new ProductList;
    productList-> n = 0;
    productList -> i = 1000;
    productList->head = nullptr;
    productList->tail = nullptr;
    return productList;
}

// Add End
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

// Saves the current product list to a CSV file (ProductList.csv)
// Each product is stored as a pipe-separated row :ID|MODEL|INSTOCK|SOLD|..
void storeProduct(ProductList *productList) { // Implemented by (Sokleap)
    // Attempt to open the CSV file for writing
    ofstream productFile("../data/ProductList.csv");
    if (!productFile.is_open()) {
        cerr << "Error: Could not open ProductList.csv for writing.\n";
        return;
    }

    // Iterate through the product list and write each product's details
    ProductElement *current = productList->head;
    while(current != nullptr) {
        productFile 
            << current->id << "|" 
            << current->model << "|" 
            << current->inStock << "|" 
            << current->sold << "|" 
            << current->description << "|" 
            << current->purchaseCost << "|" 
            << current->salePrice << "\n";
        current = current -> next;
    }

    productFile.close(); // Close the file when done
}

// Update a product's details by it's ID.
// Automatically updates the product's stock status and saves the list to file.
void updateProductById(ProductList *productList, ProductElement* product, int targetId) { 
    // Handle case where product is not found
    if(product == nullptr) {
        cout << RED << INDENT << "Product with ID " << targetId << " not found.\n" << RESET;
        return;
    }

    // Show current product info
    cout << YELLOW;
    cout << "\n" << INDENT << "Updating Product ID: " << targetId << "\n";
    cout << INDENT << "Current model: " << product->model << "\n" 
         << INDENT << "New model: ";
    
    // Clear leftover input and get new model name
    getline(cin, product->model);

    // Get new stock and sales value with validation
    product->inStock = getValidateIntInRange(
        INDENT + "Enter new quantity in stock (1-1000): ", 
        MIN_STOCK, MAX_STOCK
    );
    product->sold = getValidateIntInRange(
        INDENT + "Enter new quantity sold (1-1000): ", 
        MIN_STOCK, MAX_STOCK
    );
    
    // Get updated description
    string newDescription;
    do {
        cout << YELLOW << INDENT << "Enter new description: " << RESET;
        getline(cin, newDescription);
        if (newDescription.empty()) {
            cout << RED << INDENT << "Description cannot be empty. Please enter a valid description.\n" << RESET;
        }
    } while (newDescription.empty());
    product->description = newDescription;

    // Get updated purchase cost and sale price
    product->purchaseCost = getValidateDoubleInRange(
        INDENT + "New purchase cost($1.00 - $10000.00): ", 
        MIN_PRICE, MAX_PRICE
    );
    product->salePrice = getValidateDoubleInRange(
        INDENT + "New sale price($1.00 - $10000.00): ", 
        MIN_PRICE, MAX_PRICE
    );
    cout << RESET;

    // Update stock status based on new values
    if(product->inStock == 0) { 
        product->status = "\033[31mOut of Stock\033[0m"; // Red
    } else if(product->inStock <= static_cast<int>((product->inStock + product->sold) * 0.25)) {
        product->status = "\033[33mLow Stock\033[0m   "; // Yellow
    } else {
        product->status = "\033[32mAvailable\033[0m   "; // Green
    }

    // Save updated list to file
    storeProduct(productList);

    cout << GREEN << INDENT << "Product updated successfully.\n" << RESET;
}

// Searches for a product in the list by its ID.
// Returns a pointer to the matching ProductElement if found, or nullptr if not found.
ProductElement* searchProductByID(ProductList *productList, int searchID) { 
    ProductElement* current = productList->head;

    while(current != nullptr){
        if(current->id == searchID){
            return current; // Found the product
        } 
        current = current->next;
    }

    return nullptr; // Not found
}

void deleteProductByID(ProductList* ls, ProductElement* temp) { 
    if(temp != nullptr){
        if(ls->n == 1){
            ls->head = nullptr;
            ls->tail = nullptr;
        }
        else{
            //head
            if(temp->prev == nullptr){
                temp->next->prev = nullptr;
                ls->head = temp->next;
            }
            else{
                if(temp -> next == nullptr){
                    //tail
                    temp -> prev -> next = nullptr;
                    ls->tail = temp->prev; 
                    cout << ls -> tail -> id << endl;
                }
                //pos
                else{
                    temp -> prev-> next = temp-> next;
                    temp -> next -> prev = temp -> prev;
                }
               
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

// *** Sort Product using Quick Sort Algorithm ***
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

// ==================== MAIN QUICK SORT FUNCTION ====================
void quickSort(ProductList *productList, bool ascending = false) {

    QuickSort(productList->head, productList->tail, ascending);

}

// Displays the details of a single product by its ID in a formatted table.
void displayProductByID(ProductList* productList, int productID) { 
    ProductElement *product = searchProductByID(productList, productID);

    if (product != nullptr) {
        // Print table header
        cout << "\n+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
        printf("| %-5s | %-20s | %-5s | %-5s | %-35s | %-16s | %-13s | %-12s |\n",
               "ID", "MODEL", "STOCK", "SOLD", "DESCRIPTION", 
               "PURCHASE COST($)","SALE PRICE($)", "STATUS");
        cout << "+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";

        // Print product row
        printf("| %5d | %-20s | %5d | %5d | %-35s | %16.2f | %13.2f | %-12s |\n", 
               product->id, product->model.c_str(), product->inStock, product->sold, 
               product->description.c_str(), product->purchaseCost, 
               product->salePrice, product->status.c_str());
        cout << "+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
    } else {
        // Product not found
        cout << RED << INDENT << "Product not found!\n" << RESET;
    }
}

// Display Top 5 Best Selling Product
void displayBestSelling(ProductList *productList) {  
    // Hanle empty product list
    if(productList->n == 0) {
        cout << RED << INDENT << "No products available.\n" << RESET;
        return;
    }

    // Copy products into an array for sorting
    ProductElement *products[productList->n];
    ProductElement *current = productList->head;
    int index = 0;

    while(current != nullptr) {
        products[index++] = current;
        current = current->next;
    }

    // Sort by sold (Descending) using simple Bubble Sort
    for(int i = 0; i < productList->n - 1; i++) {
        for(int j = 0; j < productList->n - i - 1; j++) {
            if(products[j]->sold < products[j + 1]->sold) {
                swap(products[j], products[j + 1]);
            }
        }
    }

    // Display table header
    cout << "\n" << YELLOW << INDENT << "=== Top 5 Best-Selling Products ===\n" << RESET;
    cout << "\n+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
    printf("| %-5s | %-20s | %-5s | %-5s | %-35s | %-16s | %-13s | %-12s |\n",
           "ID", "MODEL", "STOCK", "SOLD", "DESCRIPTION", 
           "PURCHASE COST($)","SALE PRICE($)", "STATUS");
    cout << "+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";

    // Display up to the top 5 products
    int limit = min(5, productList->n);
    for(int i = 0; i < limit; i++) {
        printf("| %5d | %-20s | %5d | %5d | %-35s | %16.2f | %13.2f | %-12s |\n", 
        products[i]->id, products[i]->model.c_str(), products[i]->inStock, 
        products[i]->sold, products[i]->description.c_str(), 
        products[i]->purchaseCost, products[i]->salePrice, 
        products[i]->status.c_str());
    }

    cout << "+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
}

// Displays all product considered "low stock" (stock <= 25% of total stock).
void displayLowStockProducts(ProductList *productList) { 
    if(productList->n == 0) {
        cout << RED << INDENT << "No products available.\n" << RESET;
        return; 
    }

    bool found = false;
    const double LOW_STOCK = 0.25; // 25% of total (stock + sold)

    // Display table header
    cout << "\n" << INDENT << YELLOW 
         << "=== Low-Stock Products (<= 25% of total stock) ===\n" 
         << RESET;
    cout << "\n+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
    printf("| %-5s | %-20s | %-5s | %-5s | %-35s | %-16s | %-13s | %-12s |\n",
           "ID", "MODEL", "STOCK", "SOLD", "DESCRIPTION", 
           "PURCHASE COST($)", "SALE PRICE($)", "STATUS");
    cout << "+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n"; 

    // Iterate through all products and display low-stock ones
    ProductElement *current = productList->head;
    while (current != nullptr) {
        int total = current->inStock + current->sold;

        if(total > 0 && current->inStock <= static_cast<int>(total * LOW_STOCK)) {
            found = true;
            printf("| %5d | %-20s | %5d | %5d | %-35s | %16.2f | %13.2f | %-12s |\n",
                   current->id, current->model.c_str(), current->inStock, 
                   current->sold, current->description.c_str(), 
                   current->purchaseCost, current->salePrice, current->status.c_str());
        }
        current = current->next;
    }

    if(!found) {
        cout << RED << INDENT << "No low-stock products found.\n" << RESET;
    }

    cout << "+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
}

// Displays all products for the admin
void displayAdminProductList(ProductList *productList) { 
    ProductElement *current = productList->head;

    // Display table header
    cout << "\n+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
    printf("| %-5s | %-20s | %-5s | %-5s | %-35s | %-16s | %-13s | %-12s |\n",
           "ID", "MODEL", "STOCK", "SOLD", "DESCRIPTION", 
           "PURCHASE COST($)","SALE PRICE($)", "STATUS");
    cout << "+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";

    // Display each product row
    while(current != nullptr){
        printf("| %5d | %-20s | %5d | %5d | %-35s | %16.2f | %13.2f | %-12s |\n", 
               current->id, current->model.c_str(), current->inStock, current->sold, 
               current->description.c_str(), current->purchaseCost, 
               current->salePrice, current->status.c_str());
        current = current->next;
    }

    cout << "+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
}

// Displays all products for the user.
void displayUserProductList(ProductList *productList) { 
    ProductElement *current = productList->head;

    // Display table header
    cout << "+-------+----------------------+-------------------------------------+----------+--------------+" << endl;
    printf("| %-5s | %-20s | %-35s | %-8s | %-12s |\n", 
           "ID","MODEL", "DESCRIPTION", "PRICE($)", "STATUS");
    cout << "+-------+----------------------+-------------------------------------+----------+--------------+" << endl;

    // Display each product row (for users, no Purchase cost, stock or sold)
    while (current != nullptr) {
        printf("| %-5d | %-20s | %-35s | %8.2f | %-12s |\n", 
               current->id, current->model.c_str(), current->description.c_str(), 
               current-> salePrice, current->status.c_str());
        current = current->next;
    }

    cout << "+-------+----------------------+-------------------------------------+----------+--------------+" << endl;
}

void clearProductList(ProductList *productList) {
    ProductElement *current = productList->head;
    while (current != nullptr) {
        ProductElement *nextNode = current->next; 
        delete current;                         
        current = nextNode;                       
    }
    productList->head = nullptr;
    productList->tail = nullptr;
    productList->n = 0;
}

void loadProductList(ProductList *ls) { 
    ifstream productFile("../data/ProductList.csv");
    if (!productFile){
        cout << RED << INDENT << "Error: ProductList.csv not found.\n" << RESET; 
        return;
    }
    clearProductList(ls);

    string history;
    string arrayString[8];
    string token;
    int maxId = 999; // Start below minimum

    while(getline(productFile, history)) {
        if(history.empty()) continue;
        stringstream ss(history);
        int index = 0;
        while(getline(ss, token, '|') && index < 8) {
            arrayString[index++] = token;
        }
        if(index < 7) {
            cout << RED << INDENT << "Warning: Skipped invalid row in ProductList.csv\n" << RESET;
            continue;
        }
        try {
            int id = stoi(arrayString[0]);
            maxId = max(maxId, id); // Track highest ID
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
    ls->i = maxId + 1; // Set next ID to max existing + 1
}

// Doubly Linked List
struct ReportElement { 
    int id, totalStock, totalSold;
    double totalPurchaseCost, totalEarn, profit, estimatedProfit;
    ProductElement *product;
    ReportElement *next;
    ReportElement *prev;
};

struct ReportList {
    int n;
    ReportElement *head;
    ReportElement *tail;
};

ReportList *createReportList() {
    ReportList *reportList = new ReportList;
    reportList->n = 0;
    reportList->head = nullptr;
    reportList->tail = nullptr;
    return reportList;
}

// Add End
void addReport(ReportList *reportList, ProductElement *product) { 
    // Allocate and populate a new report element
    ReportElement *report = new ReportElement;
    report->product = product;
    report->id = product->id;
    
    // Calculate report values
    int totalStock = product->inStock;
    int totalSold = product->sold;
    double totalPurchaseCost = product->purchaseCost * totalSold;
    double totalEarn = product->salePrice * totalSold;
    double profit = totalEarn - totalPurchaseCost;
    double estimatedProfit = profit + (totalStock * (product->salePrice - product->purchaseCost));

    // Store computed values in the new report node
    report->totalStock = totalStock;
    report->totalSold = totalSold;
    report->totalPurchaseCost = totalPurchaseCost;
    report->totalEarn = totalEarn;
    report->profit = profit;
    report->estimatedProfit = estimatedProfit;

    // Insert into the doubly linked list (Add-End)
    report->next = nullptr;
    report->prev = reportList->tail;

    if (reportList->n == 0) {
        reportList->head = report;
    }
    else {
        reportList->tail->next = report; 
    }
    reportList->tail = report;
    reportList->n++;
}

// Displays the overall sales report and exports the same data to a CSV file.
void displayOverallReport(ReportList *reportList) { 
    // Check if the report list is empty
    if(reportList == nullptr || reportList->head == nullptr) {
        cout << "\n" << RED << INDENT << "No report data available.\n";
        return;
    }

    // Open CSV file to save report
    ofstream reportFile("../data/OverallReport.csv");

    // Start from the first report element
    ReportElement *temp = reportList->head;

    // Print the table header
    cout << "\n+-------+----------------------+--------------+-------+----------------------+-------------+-------------+------------------+\n";
    printf("| %-5s | %-20s | %-12s | %-5s | %-20s | %-11s | %-11s | %-16s |\n",
           "ID", "MODEL", "TOTAL STOCK", "SOLD", "TOTAL PURCHASE COST", 
           "TOTAL EARN", "PROFIT", "ESTIMATE PROFIT");
    cout << "+-------+----------------------+--------------+-------+----------------------+-------------+-------------+------------------+\n";

    // Loop through all report elements
    while (temp != nullptr) {
        // Display the report row
        printf("| %-5d | %-20s | %-12d | %-5d | %-20.2f | %-11.2f | %-11.2f | %-16.2f |\n",
               temp->id, temp->product->model.c_str(), temp->totalStock, temp->totalSold,
               temp->totalPurchaseCost, temp->totalEarn, temp->profit, temp->estimatedProfit);

        // Save clean | separated data
        reportFile << temp->id << "|"
                   << temp->product->model << "|"
                   << temp->totalStock << "|"
                   << temp->totalSold << "|"
                   << temp->totalPurchaseCost << "|"
                   << temp->totalEarn << "|"
                   << temp->profit << "|"
                   << temp->estimatedProfit << "\n";
        
        temp = temp->next;
    }
    cout << "+-------+----------------------+--------------+-------+----------------------+-------------+-------------+------------------+\n";

    reportFile.close();
}

// Clears all nodes in the report list and resets it to an empty state.
// Frees memory for each ReportElement to avoid memory leaks.
void clearReportList(ReportList *reportList) {
    // Start from the head of list
    ReportElement *current = reportList->head;

    // Traverse and delete each node
    while (current != nullptr) {
        ReportElement *toDelete = current;
        current = current->next;
        delete toDelete;
    }

    // Reset the list state
    reportList->head = nullptr;
    reportList->tail = nullptr;
    reportList->n = 0; // Reset node count
}

void printBar(int blocks, char symbol, const string &color) {
    cout << color;
    for (int i = 0; i < blocks; i++) {
        cout << symbol;
    }
    cout << RESET;
}

// Draws a horizontal bar chart in the console for each product's profit and estimated profit.
// Uses ASCII blocks (CP437) and colors to represent profit (green) and estimate profit (blue).
void graphVisualization(ReportList *reportList) {

    if(reportList == nullptr || reportList->head == nullptr) {
        cout << "\n" << RED << INDENT << "No report data to visualize.\n" << RESET;
        return;
    }

    // Ensure console supports ASCII block characters
    SetConsoleCP(437);
    SetConsoleOutputCP(437);

    char block = 178;     // Solid block (ASCII)
    double scale = 500.0; // 1 block = $500
    const int separatorLength = 100; // Number of '=' line

    // Chart header
    cout << "\n" << YELLOW << "Profit Visualization (Green = Profit, Blue = Estimate Profit)\n" << RESET;

    // Draw '=' line
    for(int i = 0; i < separatorLength; i++) {
        cout << YELLOW << "=";
    }
    cout << RESET << endl;

    // Iterate through each report entry and display a bar
    ReportElement *current = reportList->head;
    while(current != nullptr) {
        // Calculate blocks for profit and estimated profit
        int profitBlocks = static_cast<int>(current->profit / scale);
        int estimateBlocks = static_cast<int>((current->estimatedProfit - current->profit) / scale); 

        // Show product model name (left-aligned, fixed width)
        cout << setw(20) << left << current->product->model << YELLOW << " | " << RESET;

        // Draw profit & estimated profit bar
        printBar(profitBlocks, block, GREEN);
        printBar(estimateBlocks, block, BLUE);

        // Show numeric value after the bars
        cout << " "
             << ORANGE << "[" << RESET << GREEN << current->profit 
             << RESET << YELLOW << "$" << RESET << ORANGE << "]" << RESET << " "
             << ORANGE << "[" << RESET << BLUE << current->estimatedProfit 
             << RESET << YELLOW << "$" << RESET << ORANGE << "]" << RESET
             << "\n";

        current = current->next;
    }

    // Draw legend at the bottom
    cout << "\n" << YELLOW << "Legend: " << RESET;
    printBar(2, block, GREEN); 
    cout << YELLOW << " = Profit, " << RESET;
    printBar(2, block, BLUE); 
    cout << YELLOW << " = Estimated Profit (1 block approximately $500)\n" << RESET;
}

// Stack Algorithm for Admin history
struct AdminHistory { 
    string adminName;          
    string commandType;        // Type of command (such as ADD, UPDATE, DELETE, BACKUP, RESTORE)
    string description;        
    string cambodiaStringTime; // Timestamp (in Cambodia time)
    AdminHistory *next;        
};

struct AdminHistoryStack {
    int size;
    AdminHistory *top;
};

AdminHistoryStack *createEmptyStack() {
    AdminHistoryStack *stack = new AdminHistoryStack();
    stack->size = 0;
    stack->top = nullptr;
    return stack;
}

// Gets the current UTC time as a system_clock::time_point.
// Easy for time calculations and converting to local time later.
chrono::system_clock::time_point getCurrentUTCTime() {
    chrono::system_clock::time_point now = chrono::system_clock::now();
    return now;
}

// Returns the current Cambodia time (ICT, UTC+7) as a formatted string: "dd/mm/yyyy HH:MM:SS".
string getCambodiaTime() {

    const chrono::hours CAMBODIA_OFFSET = chrono::hours(7); // Cambodia time zone offset (ICT = UTC+7)
    
    chrono::system_clock::time_point cambodia_time_point = getCurrentUTCTime() + CAMBODIA_OFFSET;

    // Convert UTC time to Cambodia local time string (DD/MM/YYYY HH:MM:SS)
    time_t rawTime = chrono::system_clock::to_time_t(cambodia_time_point);
    tm *cambodiaTime = gmtime(&rawTime);
    char timeBuffer[30];

    strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M:%S", cambodiaTime);

    return string(timeBuffer);
}

// Add a new admin history record to the top of the stack (push).
void addHistory(AdminHistoryStack *historyStack,
                const string& adminName, 
                const string& commandType, 
                const string& description, 
                const string& cambodiaStringTime) {
    // Create a new history record
    AdminHistory *newHistory = new AdminHistory;

    // Fill in the history details
    newHistory->adminName = adminName;
    newHistory->commandType = commandType;
    newHistory->description = description;
    newHistory->cambodiaStringTime = cambodiaStringTime;

    // Insert at the top of the stack
    newHistory->next = historyStack->top;
    historyStack->top = newHistory;

    historyStack->size++;
}

// Clear all admin history records from the stack and free memory
void clearAdminHistory(AdminHistoryStack *stack) {
    // Iterate through the stack and delete each history record
    while (stack->top != nullptr) {
        AdminHistory *current = stack->top; // Store the current top element
        stack->top = stack->top->next;      // Move the top pointer to the next record
        delete current;                     // Free the memory of the removed record
    }
    // Reset the stack properties
    stack->size = 0;
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

// Display a single history entry with proper colum alignment
void displayHistory(int index, AdminHistory *historyEntry) {
    // Colorize TYPE
    string typeColored = colorizeType(historyEntry->commandType);
    string descPlain = historyEntry->description;

    // Column widths for alignment
    const int typeColWidth = 10;
    const int descColWidth = 50;

    // Calculate padding for the "Type" column (strip color codes to get correct length)
    int typeLength = stripColor(typeColored).length();
    int typePadding = max(0, typeColWidth - typeLength);

    // Calculate padding for DESCRIPTION
    int descLength = stripColor(descPlain).length();
    int descPadding = max(0, descColWidth - descLength);

    // Print the formatted row with aligned columns
    cout << "| " << setw(4) << index
         << " | " << setw(20) << historyEntry->adminName
         << " | " << typeColored << string(typePadding, ' ')
         << " | " << descPlain << string(descPadding, ' ')
         << " | " << setw(20) << historyEntry->cambodiaStringTime
         << " |" << endl;
}

// Display all admin histoy tracking
void displayAllAdminHistory(AdminHistoryStack *stack) {

    if(stack->size == 0){
        cout << "\n" << RED << INDENT << "No admin history found.\n" << RESET;
        return;
    }

    AdminHistory *current = stack->top;
    int entryIndex = 1;

    // Print the header once at the top
    cout << "\n" << YELLOW << INDENT << "--- All Admin History ---\n" << RESET;
    cout << "\n+------+----------------------+------------+----------------------------------------------------+----------------------+\n";
    printf("| %4s | %-20s | %-10s | %-50s | %-20s |\n",
           "N0","NAME", "TYPE", "DESCRIPTION", "HISTORY TIME");
    cout << "+------+----------------------+------------+----------------------------------------------------+----------------------+\n";

    // Print each history record
    while (current != nullptr)
    {
        displayHistory(entryIndex, current);
        current = current->next;
        entryIndex++;
    }

    cout << "+------+----------------------+------------+----------------------------------------------------+----------------------+\n";
}

// Convert a date-time string (DD/MM/YYYY HH:MM:SS) to time_t format.
time_t stringToTimeT(const string &datetimeStr) {
    tm timeStruct{}; // Structure to hold parsed date and time components

    // Use stringstream to parse the date-time string.
    stringstream ss(datetimeStr);

    // Parse the string using the specified date format.
    ss >> get_time(&timeStruct, "%d/%m/%Y %H:%M:%S");

    // Convert the parsed tm structure into time_t 
    // If parsing fails, mktime will return -1.
    return mktime(&timeStruct);
}

// Display all admin history entries recorded within the last 24 hours.
void displayLastDayHistory(AdminHistoryStack *stack) {
    // Calculate cutoff time (24 hours ago from now).
    auto twentyFourHoursAgo = getCurrentUTCTime() - chrono::hours(24);
    time_t twentyFourHoursAgo_t = chrono::system_clock::to_time_t(twentyFourHoursAgo);

    AdminHistory *current = stack->top;
    int entryNumber = 1;
    bool found = false;

    // Iterate through the admin history stack.
    while (current != nullptr) {
        // Convert the entry timestamp to time_t for comparison.
        time_t recordTime = stringToTimeT(current->cambodiaStringTime);
        
        // Display entry if it is within the last 24 hours.
        if (recordTime >= twentyFourHoursAgo_t) {
            // Print table header only once 
            if (entryNumber == 1) {
                cout << "\n" << YELLOW << INDENT << "--- Admin History within the last 24 hours ---\n" << RESET;
                cout << "\n+------+----------------------+------------+----------------------------------------------------+----------------------+\n";
                printf("| %4s | %-20s | %-10s | %-50s | %-20s |\n",
                       "N0", "NAME", "TYPE", "DESCRIPTION", "HISTORY TIME");
                cout << "+------+----------------------+------------+----------------------------------------------------+----------------------+\n";
            }

            displayHistory(entryNumber, current);
            found = true;
            entryNumber++;
        }
        current = current->next;
    }

    cout << "+------+----------------------+------------+----------------------------------------------------+----------------------+\n";
    
    if (!found) {
        cout << "\n" << RED << INDENT << "No admin history found within the last 24 hours.\n" << RESET;
    }
}

// Get the time_t value representing the date and time one month ago.
time_t getOneMonthAgoTime() {
    // Get the current time.
    time_t now = time(nullptr);
    
    // Convert to a tm structure to manipulate the month.
    tm *tmNow = localtime(&now);

    // Go back one month.
    tmNow->tm_mon -= 1;

    // If month underflows (less than January), wrap around to December of the previous year.
    if (tmNow->tm_mon < 0) {
        tmNow->tm_mon += 12; // Wrap to December (12 months in a year).
        tmNow->tm_year -= 1; // Move back one year.
    }
    
    // Convert back to time_t and return.
    return mktime(tmNow);
}

void displayLastMonthHistory(AdminHistoryStack *s) {
    if (s == nullptr || s->top == nullptr) {
        cout << "\n" << RED << INDENT << "No admin history stack available.\n" << RESET;
        return; 
    }

    AdminHistory *temp = s->top;
    int index = 1;
    bool found = false;

    time_t oneMonthAgo = getOneMonthAgoTime();

    while (temp != nullptr) {
        // Convert string time into time_t
        time_t recordTime = stringToTimeT(temp->cambodiaStringTime);

        if (recordTime >= oneMonthAgo) {
            if (!found) {
                // Only print header once
                cout << "\n" << YELLOW << INDENT << "--- Admin History within the last 30 days ---\n" << RESET;
                cout << "\n+------+----------------------+------------+----------------------------------------------------+----------------------+\n";
                printf("| %4s | %-20s | %-10s | %-50s | %-20s |\n",
                       "N0", "NAME", "TYPE", "DESCRIPTION", "HISTORY TIME");
                cout << "+------+----------------------+------------+----------------------------------------------------+----------------------+\n";
                found = true;
            }
            
            // Show this history record
            displayHistory(index, temp);
            index++;
        }

        temp = temp->next;
    }

    if (found) {
        cout << "+------+----------------------+------------+----------------------------------------------------+----------------------+\n";
    } else {
        cout << "\n" << RED << INDENT << "No admin history found within the last 30 days.\n" << RESET;
    }
}

void storeAdminHistory(AdminHistory *temp) {
    if (temp == nullptr) return;

    ofstream historyFile("../data/History.csv", ios::app);

    // write record in '|' separeated format
    historyFile << temp->adminName << "|" 
                << temp->commandType << "|" 
                << temp->description << "|" 
                << temp->cambodiaStringTime << "\n";

    historyFile.close();
}

void loadAdminHistoryStack(AdminHistoryStack *stack) {
    ifstream historyFile("../data/History.csv");
    if (!historyFile) {
        cerr << RED << "Failed to open History.csv!\n" << RESET;
        return;
    }

    string line;
    string fields[4];

    while (getline(historyFile, line)) {
        stringstream ss(line);
        string token;
        int index = 0;

        while (getline(ss, token, '|')) { // Split by '|'
            fields[index++] = token;
        }

        if (index == 4) {
            const string &adminName = fields[0];
            const string &commandType = fields[1];
            const string &description = fields[2];
            const string &time = fields[3];

            addHistory(stack, adminName, commandType, description, time);
        }
    }

    historyFile.close();
}

void backupProductData(ProductList *productList) {
    // Always save the latest product list before backup
    storeProduct(productList);

    ifstream productFile("../data/ProductList.csv", ios::binary);
    if (!productFile) {
        cout << RED << INDENT << "Error: ProductList.csv not found. Backup aborted.\n" << RESET;
        return;
    }

    // Check if ProductList.csv is empty
    productFile.seekg(0, ios::end);
    if (productFile.tellg() == 0) {
        cout << RED << INDENT << "Error: ProductList.csv is empty. Backup not created (to avoid wiping a good backup).\n" << RESET;
        return;
    }
    productFile.seekg(0, ios::beg); // Reset to beginning

    // Create backup file
    ofstream backupFile("../data/Backup_ProductList.csv", ios::binary);
    if (!backupFile) {
        cout << RED << INDENT << "Error: Failed to create backup file.\n" << RESET;
    }

    // Copy content
    backupFile << productFile.rdbuf();

    cout << GREEN << INDENT << "Backup completed successfully (" << productList->n << " product(s) saved).\n" << RESET;
}


void restoreProductData(ProductList *productList) {
    ifstream backupFile("../data/Backup_ProductList.csv", ios::binary);
    if (!backupFile) {
        cout << RED << INDENT << "Error: Backup file not found. Cannot restore.\n" << RESET;
        return;
    }

    // Check if backup file is empty
    backupFile.seekg(0, ios::end);
    if (backupFile.tellg() == 0) {
        cout << RED << INDENT << "Error: Backup file is empty. Restore aborted (to protect your current data).\n" << RESET;
        return;
    }
    backupFile.seekg(0, ios::beg);

    // Overwrite ProductList.csv with backup
    ofstream productFile("../data/ProductList.csv", ios::binary);
    if (!productFile) {
        cout << RED << INDENT << "Error: Failed to write to ProductList.csv.\n" << RESET;
        return;
    }

    productFile << backupFile.rdbuf();

    cout << GREEN << INDENT << "Restore completed successfully.\n" << RESET;

    // Reload the updated file into memory
    loadProductList(productList);
}