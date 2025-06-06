#include <string>
#include <iostream>
using namespace std;

// Define Product structure
struct Product {
    int data;
    // int id;
    // string name;
    // int quantity;
    // float price;
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
void addBeg(List *ls, int data){
    Product *p = new Product;
    p->data = data;
    p->next = ls->head;
    p->prev = nullptr;
    ls->head = p;

    if(ls->n == 0){
        ls->tail = p;
    }
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
void display(List *ls){
    Product *temp = ls->head;
    while(temp != nullptr){
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}