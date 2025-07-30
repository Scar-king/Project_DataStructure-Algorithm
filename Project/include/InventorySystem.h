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
void addProduct(
    ProductList *productList, 
    const string &model, 
    int inStock, 
    int sold, 
    string description, 
    double purchaseCost, 
    double salePrice, 
    bool isLoadData, 
    int id
) {
    // Create new product node
    ProductElement *newProduct = new ProductElement;

    // Assign ID (for new loaded product)
    if (isLoadData) {
        newProduct->id = id;
        productList->i = id; // Keep list index synced when loading
    } else {
        newProduct->id = productList->i;
    }

    // Assign basic details
    newProduct->model = model;
    newProduct->inStock = inStock;
    newProduct->sold = sold;
    newProduct->description = description;
    newProduct->purchaseCost = purchaseCost;
    newProduct->salePrice = salePrice;

    // Link to list (set prev to last node)
    newProduct->next = nullptr;
    newProduct->prev = productList->tail;

    // Set product status with color (based on stock level)
    if (inStock == 0) {
        newProduct->status = "\033[31mOut of Stock\033[0m"; // Red   
    } else if (inStock <= static_cast<int>((inStock + sold) * 0.25)){
        newProduct->status = "\033[33mLow Stock\033[0m   ";  // Yellow 
    } else {
        newProduct->status = "\033[32mAvailable\033[0m   "; // Green  
    }

    // Insert into doubly linked list
    if (productList->n == 0) {
        productList->head = newProduct;
    } else {
        productList->tail->next = newProduct; 
    }
    productList->tail = newProduct;

    // Update counters
    productList->n++;
    productList->i++;
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
    cin.ignore();
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
    cout << INDENT << "New description: ";
    getline(cin, product->description);

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

// Deletes a product from the list by its pointer (ProductElement*).
// If the product is found and removed, the updated product list is saved to file.
// Displays a confirmation or an error message accordingly.
void deleteProductByID(ProductList* productList, ProductElement* target) { 
    // Handle case where the product was not found
    if(target == nullptr){
        cout << "\n" << RED << INDENT
             << "Entered ID not found. Please try again...\n" << RESET;
        return;
    }

    // Case 1: List contains only one element
    if(productList->n == 1){
        productList->head = nullptr;
        productList->tail = nullptr;
    }
    // Case 2 : Target is the first element (head)
    else if (target->prev == nullptr) {
        productList->head = target->next;
        target->next->prev = nullptr;
    }
    // Case 3: Target is the last element (tail)
    else if (target->next == nullptr) {
        productList->tail = target->prev;
        target->prev->next = nullptr;
    }
    // Case 4: Target is in the middle
    else {
        target->prev->next = target->next;
        target->next->prev = target->prev;
    }
    
    // Delete the target node
    delete target;

    // Update product count and save changes
    productList->n--;
    storeProduct(productList);

    cout << GREEN << INDENT << "Successfully deleted product!\n" << RESET;
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

// We called this function to use Quick Sort
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

// Clears all products from the list and resets the list state.
// Frees the memory for each ProductElement, sets head and tail to nullptr.
// resets the product count, and resets the next product ID counter to 1000.
void clearProductList(ProductList *productList) {
    ProductElement *current = productList->head;

    // Delete each product node one by one
    while (current != nullptr) {
        ProductElement *nextNode = current->next; // Keep the next node
        delete current;                           // Free the current node
        current = nextNode;                       // Move to the next node
    }

    // Reset the product list to an empty state
    productList->head = nullptr;
    productList->tail = nullptr;
    productList->n = 0;

    // Reset the ID counter so new products start from 1000 again
    productList->i = 1000;
}

// Loads all products from ProductList.csv into the given product list.
// Clears the current list first, parses each row, validates fields,
// and adds valid products to the list. Skips blank or corrupted rows.
void loadProductList(ProductList *productList) { 
    ifstream productFile("../data/ProductList.csv");

    if (!productFile){
        cout << RED << INDENT << "Error: ProductList.csv not found.\n" << RESET; 
        return; // File doesn't exist yet
    }

    // Clear existing list before loading new data
    clearProductList(productList);  

    string line;
    string fields[8]; // CSV fields (expecting 7, 8 if "status" exists)
    string token;

    while (getline(productFile, line)) {
        // Skip empty lines
        if(line.empty()) continue; 

        stringstream ss(line);
        int index = 0;

        // Split the line by '|' delimiter
        while(getline(ss, token, '|') && index < 8) {
            fields[index++] = token;
        }

        // Validate row: must have at least 7 fields (status is optional)
        if(index < 7) {
            cout << RED << INDENT << "Warning: Skipped invalid row in ProductList.csv\n" << RESET;
            continue;
        }

        try {
            // Convert fields to proper data types
            int id = stoi(fields[0]);
            string model = fields[1];
            int inStock = stoi(fields[2]);
            int sold = stoi(fields[3]);
            string description = fields[4];
            double purchaseCost = stod(fields[5]);
            double salePrice = stod(fields[6]);
    
            // Add product to the list (status will be recalculated)
            addProduct(productList, model, inStock, sold, description, purchaseCost, salePrice, true, id);
        }
        catch(...) {
            cout << RED << INDENT << "Warning: Skipped a corrupted row (conversion error)\n" << RESET;
        }
    }

    productFile.close();
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
        delete toDelete; // Free memory
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
    cout << "\n" << YELLOW << "Profit Visualization (Green = Profit, Red = Estimate Profit)\n" << RESET;

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
    chrono::system_clock::time_point now = chrono::system_clock::now(); // Current time in UTC
    return now;
}

// Returns the current Cambodia time (ICT, UTC+7) as a formatted string: "dd/mm/yyyy HH:MM:SS".
string getCambodiaTime() {

    const chrono::hours CAMBODIA_OFFSET = chrono::hours(7); // Cambodia time zone offset (ICT = UTC+7)

    // Get current UTC time and add the offset for Cambodia.
    chrono::system_clock::time_point cambodia_time_point = getCurrentUTCTime() + CAMBODIA_OFFSET;

    // Convert to time_t (needed for formatting).
    time_t rawTime = chrono::system_clock::to_time_t(cambodia_time_point);

    // Convert to a tm structure (in GMT, adjusted by offset already).
    tm *cambodiaTime = gmtime(&rawTime);

    // Format the time as a string (DD/MM/YYYY HH:MM:SS).
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

    // Return without color if the type is unknown
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