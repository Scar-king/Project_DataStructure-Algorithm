// Sok Leap
#include <string>
#include <iostream>
#include <cstdio>
using namespace std;

// Each Record must has 5 to 9 columns/fields
// We are using Doubly List
struct Product {
    int id;
    string model;
    int inStock;
    int sold;
    string description;
    double purchaseCost;
    double salePrice;
    string status;
    Product *next;
    Product *prev;
    // Add More Attributes
};

// Define Linked List structure
struct ProductList {
    int n;
    Product* head;
    Product* tail;
};

ProductList *createList(){
    ProductList *ls = new ProductList;
    ls->n = 0;
    ls->head = nullptr;
    ls->tail = nullptr;
    return ls;
}

// Add Product
// void addBeg(List *ls, int id, string model, int inStock, int sold, string description, double price, string status){
//     Product *p = new Product;
//     p->name = name;
//     p->quantity = quantity;
//     p->price = price;
//     p->next = ls->head;
//     p->prev = nullptr;

//     if(ls->n == 0){
//         ls->tail = p;
//     } else {
//         ls->head->prev = p;
//     }
//     ls->head = p;
//     ls->n++;
// }

void addProduct(ProductList *ls, string model, int inStock, int sold, string description, double purchaseCost, double salePrice){
    Product *p = new Product;
    p -> id = 1000 + ls -> n;
    p -> model = model;
    p -> inStock = inStock;
    p -> sold = sold;
    p -> description = description;
    p -> purchaseCost = purchaseCost;
    p -> salePrice = salePrice;
    p -> next = nullptr;
    p -> prev = ls -> tail;
    if(inStock == 0){
        p -> status = "Out of Stock";   
    }
    else if(inStock < (sold/4)){
        p -> status = "Low Stock";  
    }
    else{
        p -> status = "Available";  
    }

    if(ls -> n == 0){
        ls -> head = p;
    }
    else{
        ls -> tail -> next = p; 
    }
    ls -> tail = p;
    ls -> n++;
}

void addPos(ProductList *ls, int pos){

}

// Update Product
void updateProduct(ProductList *ls){

}

// Delete Product
void deleteBeg(ProductList *ls){

}

void deleteEnd(ProductList *ls){

}

void deletePos(ProductList *ls, int pos){
    Product* temp = ls -> head;
    // 1 2 3 4
    // 2
    if(ls -> n == 0){
        cout << "The list is empty!" << endl;
        return;
    }
    else if(pos > ls -> n || pos < 1){
        cout << "Invalid position!" << endl;
        return;
    }

    for(int i = 1; i < pos; i++){
        temp = temp -> next;
    }
    temp -> next -> prev = temp -> prev;
    temp -> prev = temp -> next;
    delete temp;
    ls -> n--;
    cout << "Successfully deleted product at position" << pos << endl;
}

// Reverse ProductList
void reverseList(ProductList *ls){

}

// Combine List
void combine(ProductList *ls){

}

// Search Product by ID
int searchProductID(ProductList *ls, int ID){
    Product* temp = ls -> head;
    while(temp != nullptr){
        if(temp -> id == ID){
            // cout << "Product found:\n";
            // cout << "Product ID: " << temp -> id << ", \n";
            // cout << "Product Name: " << temp -> name << ", \n";
            // cout << "Quantity" << temp -> quantity << ", \n";
            // cout << "Price: " << temp -> price << ", \n\n";
            return ID;
        } 
        temp = temp -> next;
    }
    return 0;
}

// Sort Product using Bubble Sort Algorithm
void bubbleSort(ProductList *ls){

}

// Display Product
void displayUserProductList(ProductList *ls){ // Kheang Ann, Not include *** inStock and sold ***
    Product *temp = ls->head;
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

void displayAdminProductList(ProductList *ls){ 
    Product *temp = ls->head;
    cout << "\n+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
    printf("| %-5s | %-20s | %-5s | %-5s | %-35s | %-16s | %-13s | %-12s |\n","ID", "MODEL", "STOCK", "SOLD", "DESCRIPTION", "PURCHASE COST($)","SALE PRICE($)", "STATUS");
    cout << "+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
    while(temp != nullptr){
        printf("| %5d | %-20s | %5d | %5d | %-35s | %16.2f | %13.2f | %-12s |\n", temp -> id, temp -> model.c_str(), temp -> inStock, temp -> sold, temp -> description.c_str(), temp -> purchaseCost, temp -> salePrice, temp -> status.c_str());
        temp = temp->next;
    }
    cout << "+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
}

void displayEnd(ProductList *ls) {
    if(ls->n == 0) return;
    Product *p = ls->tail;
    while(p != nullptr) {
        // cout << p->name << " ";
        p = p->prev;
    }
    cout << endl;
}