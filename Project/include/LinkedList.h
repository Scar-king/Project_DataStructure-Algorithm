#include <string>
#include <iostream>
using namespace std;

// Each Record must has 5 to 9 columns/fields
// We are using Doubly List
struct Product {
    int id;
    string name;
    int quantity;
    double price;
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
void addBeg(List *ls, string name, int quantity, double price){
    Product *p = new Product;
    p->name = name;
    p->quantity = quantity;
    p->price = price;
    p->next = ls->head;
    p->prev = nullptr;

    if(ls->n == 0){
        ls->tail = p;
    } else {
        ls->head->prev = p;
    }
    ls->head = p;
    ls->n++;
}

void addEnd(List *ls){

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

void deletePos(List *ls){

}

// Reverse List
void reverseList(List *ls){

}

// Combine List
void combine(List *ls){

}

// Search Product by ID
int searchProduct(List *ls){
    return 0;
}

// Sort Product using Bubble Sort Algorithm
void bubbleSort(List *ls){

}

// Display Product
void displayBeg(List *ls){
    Product *temp = ls->head;
    while(temp != nullptr){
        cout << temp->name << " ";
        temp = temp->next;
    }
    cout << endl;
}

void displayEnd(List *ls) {
    if(ls->n == 0) return;
    Product *p = ls->tail;
    while(p != nullptr) {
        cout << p->name << " ";
        p = p->prev;
    }
    cout << endl;
}