#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
using namespace std;

// Define Product structure
struct Product {
    int data;
    // int id;
    // string name;
    // int quantity;
    // float price;
    Product* next;
    // Add More Attributes
};

// Define Linked List structure
struct List {
    int n;
    Product* head;
    Product* tail;
};

// Function Prototypes

// Create new list
List* createList();

// Add product
void addBeg(List* ls, int data);
void addEnd(List* ls);
void addPos(List* ls, int pos);

// Update product
void updateProduct(List* ls);

// Delete product
void deleteBeg(List* ls);
void deleteEnd(List* ls);
void deletePos(List* ls);

// Reverse the list
void reverseList(List* ls);

// Combine with another list
void combine(List* ls);

// Search product by ID
int searchProduct(List* ls);

// Sort list using Bubble Sort
void bubbleSort(List* ls);

// Display all products
void display(List* ls);

#endif // LINKEDLIST_H
