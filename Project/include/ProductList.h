#include <string>
#include <iostream>
#include <cstdio>
using namespace std;

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

void addProduct(ProductList *ls, string model, int inStock, int sold, string description, double purchaseCost, double salePrice){
    ProductElement *p = new ProductElement;
    p -> id = ls -> i;
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
void updateProductById(ProductList *ls, int ID){
    // updateTransaction(, int id);
    // updateReport(, int id);
}

// Delete Product
void deleteById(ProductList *ls, int ID){

}

// Search Product by ID
ProductElement* searchProductByID(ProductList *ls, int ID){ // Sokleap
    ProductElement* temp = ls -> head;
    while(temp != nullptr){
        if(temp -> id == ID){
            return temp;
        } 
        temp = temp -> next;
    }
    return nullptr;
}

void deleteProductByID(ProductList* ls, int ID){ // Sokleap
    ProductElement* temp = searchProductByID(ls, ID);
    if(temp != nullptr){
        if(ls -> n == 1){
            delete temp;
            ls -> head = nullptr;
            ls -> tail = nullptr;
        }
        else{
            // 1 2 3 4
            // delete 1 -> temp = 1, prev of temp = nullptr;
            if(temp -> prev == nullptr){
                temp -> next -> prev = nullptr;
                ls -> head = temp -> next;
                delete temp;
            }
            else{
                // 1 2 3 4
                // delete 4 -> temp = 4, next of temp = nullptr;
                temp -> prev -> next = temp -> next; 
                ls -> tail = temp -> prev;
                delete temp;
            }
            cout << "Successfully deleted product!\n";
            // else{
            //     temp -> next -> prev = temp -> prev;
            //     temp -> prev = temp -> next;
            //     delete temp;
            //     ls -> n--;
            // cout << "Successfully deleted product!\n";
            // }
        }
        ls -> n--;
        return;
    }
    cout << "Cannot delete!\n";
}

void displayProductByID(ProductList* ls, int ID){
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
// Reverse ProductList
void reverseList(ProductList *ls){

}

// Combine List
void combine(ProductList *ls){

}


// Sort Product using Bubble Sort Algorithm
void bubbleSort(ProductList *ls){

}

// Display Admin ProductList
void displayAdminProductList(ProductList *ls){ // Sokleap
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

void displayUserProductList(ProductList *ls){ // Kheang Ann, Not include *** inStock and sold ***
    ProductElement *temp = ls->head;
    cout << "+-------+----------------------+-------------------------------------+----------+--------------+" << endl;
    printf("| %-5s | %-20s | %-35s | %-8s | %-12s |\n", "ID","MODEL", "DESCRIPTION", "PRICE($)", "STATUS");
    cout << "+-------+----------------------+-------------------------------------+----------+--------------+" << endl;
    while(temp != nullptr){
        // cout << temp->name << " ";
        printf("| %-5d | %-20s | %-35s | %8.2f | %-12s |\n", temp->id, temp->model.c_str(), temp->description.c_str(), temp-> salePrice, temp->status.c_str());
        temp = temp->next;
    }
    cout << "+-------+----------------------+-------------------------------------+----------+--------------+" << endl;
}


void displayEnd(ProductList *ls) {
    if(ls->n == 0) return;
    ProductElement *p = ls->tail;
    while(p != nullptr) {
        // cout << p->name << " ";
        p = p->prev;
    }
    cout << endl;
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
    ReportList *ls = new ReportList;
    ls->n = 0;
    ls->head = nullptr;
    ls->tail = nullptr;
    return ls;
}

void addReport(ReportList *ls, ProductElement *p){
    ReportElement *re = new ReportElement;
    re -> id = 1000 + ls -> n;
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
    re -> prev = ls -> tail;

    if(ls -> n == 0){
        ls -> head = re;
    }
    else{
        ls -> tail -> next = re; 
    }
    ls -> tail = re;
    ls -> n++;
}

// Update Report
void updateReport(ReportList *rl){

}

void displayOverallReport(ReportList *ls) { 
    ReportElement *temp = ls->head;
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

struct TransactionElement { // Davin
    int id;
    string model;
    string category;
    int quantity;
    string type;
    double unitPrice;
    double totalPrice;
    string transactionTime;

    TransactionElement *next;
};

struct Stack {
    int size;
    TransactionElement *top;
};

Stack *createStack() {
    Stack *s = new Stack();
    s->size = 0;
    s->top = nullptr;
    return s;
}

void push (Stack *s, ProductElement *p, string category, int quantity, string type, string transactionTime){
    TransactionElement *t = new TransactionElement;
    t->id = p->id;
    t->model = p->model;
    t->category = category;
    t->quantity = quantity;
    t->type = type;
    t->transactionTime = transactionTime;

    if (type == "IN") {
        t->unitPrice = p->purchaseCost;
        p->inStock += quantity;
    } else if (type == "OUT"){
        t->unitPrice = p->salePrice;
        p->inStock -= quantity;
        p->sold += quantity;
    } else {
        t->unitPrice = 0.0; // Fallback in case of invalid type
    }

    t->totalPrice = t->unitPrice * quantity;

    t->next = s->top;
    s->top = t;
    s->size++;
}

void pop(Stack *s){
    if(s->top == nullptr){
        cout << "Stack is empty!\n";
        return;
    } 
    TransactionElement *temp = s->top;
    s->top = s->top->next;
    delete temp;
    s->size--;
}

// Update Stack
void updateTransaction(Stack *s){
    
}

void displayStack(Stack* s) {
    TransactionElement *temp = s->top;
    cout << "\n+-------+----------------------+-----------+----------+--------+----------------+----------------+---------------------+\n";
    printf("| %-5s | %-20s | %-9s | %-8s | %-6s | %-14s | %-14s | %-19s |\n", 
           "ID", "MODEL", "CATEGORY", "QTY", "TYPE", "UNIT PRICE($)", "TOTAL PRICE($)", "TIME");
    cout << "+-------+----------------------+-----------+----------+--------+----------------+----------------+---------------------+\n";
    while (temp != nullptr) {
        printf("| %-5d | %-20s | %-9s | %-8d | %-6s | %-14.2f | %-14.2f | %-19s |\n",
               temp->id, temp->model.c_str(), temp->category.c_str(), temp->quantity,
               temp->type.c_str(), temp->unitPrice, temp->totalPrice, temp->transactionTime.c_str());
        temp = temp->next;
    }
    cout << "+-------+----------------------+-----------+----------+--------+----------------+----------------+---------------------+\n";
}
