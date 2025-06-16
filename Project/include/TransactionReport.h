// Val - Davin
// | ID | MODEL | CATEGORY | QUANTITY | TYPE | PRICE | Transaction Time |
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct TransactionElement {
    int id;
    string model;
    string category;
    int quantity;
    string type;
    double price;
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

void push (Stack *s, int id, string model, string category, int quantity, string type, double price, string transactionTime){
    TransactionElement *t = new TransactionElement;
    t->id = 1000 + s -> size;
    t->model = model;
    t->category = category;
    t->quantity = quantity;
    t->type = type;
    t->price = price;
    t->transactionTime = transactionTime;

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

void displayStack(Stack* s) {
    TransactionElement *temp = s->top;
    cout << "\n+-------+----------------------+-----------+----------+--------+---------+---------------------+\n";
    printf("| %-5s | %-20s | %-9s | %-8s | %-6s | %-7s | %-19s |\n", 
           "ID", "MODEL", "CATEGORY", "QTY", "TYPE", "PRICE", "TIME");
    cout << "+-------+----------------------+-----------+----------+--------+---------+---------------------+\n";
    while (temp != nullptr) {
        printf("| %-5d | %-20s | %-9s | %-8d | %-6s | %-7.2f | %-19s |\n",
               temp->id, temp->model.c_str(), temp->category.c_str(), temp->quantity,
               temp->type.c_str(), temp->price, temp->transactionTime.c_str());
        temp = temp->next;
    }
    cout << "+-------+----------------------+-----------+----------+--------+---------+---------------------+\n";
}