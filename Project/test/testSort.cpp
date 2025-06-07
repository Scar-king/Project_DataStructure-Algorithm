#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

struct Product {
    double price;
    Product *next;
    Product *prev;
};

struct List {
    int n;
    Product *head;
    Product *tail;
};

List *create(){
    List *ls = new List;
    ls->n = 0;
    ls->head = nullptr;
    ls->tail = nullptr;
    return ls;
}

void addBeg(List *ls, double price){
    Product *p = new Product;
    p->price = price;
    p->next = ls->head;
    ls->head = p;
    p->prev = nullptr;
    if(ls->n == 0){
        ls->tail = p;
    }
    ls->n++;
}

void display(List *ls){
    Product *temp = ls->head;
    while(temp != nullptr){
        cout << temp->price << "$ ";
        temp = temp->next;
    }
    cout << endl;
}

void sort(List *ls){
    if(ls->n < 2) return;
    Product *ptr;
    Product *lastptr = nullptr;
    bool swapped;
    do {
        ptr = ls->head;
        swapped = false;
        while(ptr->next != lastptr){
            if(ptr->price > ptr->next->price){
                double temp = ptr->price;
                ptr->price = ptr->next->price;
                ptr->next->price = temp;
                swapped = true;
            }
            ptr = ptr->next;
        }
        lastptr = ptr;
    } while(swapped);
}

int main(){

    List *ls = create();

    srand(time(0));

    for(int i = 0; i <= 10; i++){
        double price = rand() % 10 + 1;
        addBeg(ls, price);
    }

    cout << "Unsort: ";
    display(ls);

    sort(ls);

    cout << "\nsorted: ";
    display(ls);

    return 0;
}