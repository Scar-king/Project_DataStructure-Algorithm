// Sok Leap
#include <string>
#include <iostream>
using namespace std;

// Each Record must has 5 to 9 columns/fields
// We are using Doubly List
struct Product {
    int id;
    string model;
    int inStock;
    int sold;
    string description;
    double price;
    string status;
    Product *next;
    Product *prev;
    // Add More Attributes
};

// Define Linked List structure
struct List {
    int n;
    Product* head;
    Product* tail;
};

List *createList(){
    List *ls = new List;
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

void addEnd(List *ls, int id, string model, int inStock, int sold, string description, double price, string status){
    Product *p = new Product;
    p -> id = 1000 + ls -> n;
    p -> model = model;
    p -> inStock = inStock;
    p -> sold = sold;
    p -> description = description;
    p -> price = price;
    p -> status = status;
    p -> next = nullptr;
    p -> prev = ls -> tail;

    if(ls -> n == 0){
        ls -> head = p;
    }
    else{
        ls -> tail -> next = p; 
    }
    ls -> tail = p;
    ls -> n++;
}

void addPos(List *ls, int pos){

}

// Update Product
void updateProduct(List *ls){

}

// Delete Product
void deleteBeg(List *ls){

}

void deleteEnd(List *ls){

}

void deletePos(List *ls, int pos){
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

// Reverse List
void reverseList(List *ls){

}

// Combine List
void combine(List *ls){

}

// Search Product by ID
int searchProductID(List *ls, int ID){
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
void bubbleSort(List *ls){

}

// Display Product
void displayBeg(List *ls){
    Product *temp = ls->head;
    while(temp != nullptr){
        // cout << temp->name << " ";
        temp = temp->next;
    }
    cout << endl;
}

void displayEnd(List *ls) {
    if(ls->n == 0) return;
    Product *p = ls->tail;
    while(p != nullptr) {
        // cout << p->name << " ";
        p = p->prev;
    }
    cout << endl;
}