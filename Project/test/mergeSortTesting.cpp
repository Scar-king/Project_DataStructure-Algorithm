#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

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

ProductElement *getNodeAt(ProductList *ls, int index) {
    ProductElement *current = ls->head;
    int i = 0;
    while(current != nullptr && i < index) {
        current = current->next;
        i++;
    }

    return current;
}

void Merge(ProductList *ls, int lb, int mid, int ub) {
    int i = lb;
    int j = mid + 1;
    int k = 0;
    int n = ub - lb + 1;
    int *b = new int[n];

    ProductElement *left = getNodeAt(ls, i);
    ProductElement *right = getNodeAt(ls, j);

    while(i <= mid && j <= ub) {
        if(left->salePrice > right->salePrice) {
            b[k++] = left->salePrice;
            left = left->next;
            i++;
        } else {
            b[k++] = right->salePrice;
            right = right->next;
            j++;
        }
    }

    while(i <= mid) {
        b[k++] = left->salePrice;
        left = left->next;
        i++;
    }

    while(j <= ub) {
        b[k++] = right->salePrice;
        right = right->next;
        j++;
    }

    ProductElement *current = getNodeAt(ls, lb);
    for(k = 0; k < n; k++) {
        current->salePrice = b[k];
        current = current->next;
    }

    delete[] b;
}

void MergeSort(ProductList *ls, int lb, int ub) {
    if(lb < ub) {
        int mid = (lb + ub) / 2;
        MergeSort(ls, lb, mid);
        MergeSort(ls, mid + 1, ub);
        Merge(ls, lb, mid, ub);
    }
}

void mergeSort(ProductList *ls) {
    if(ls->n > 1) {
        MergeSort(ls, 0, ls->n - 1);
    }
}

void displayAdminProductList(ProductList *ls){ 
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

int main(){

    ProductList *productList = createList();

    addProduct(productList, "iPhone 14", 10, 40, "Apple smartphone", 650, 999);
    addProduct(productList, "Samsung Galaxy S23", 5, 45, "Samsung flagship", 600, 899);
    addProduct(productList, "Google Pixel 7", 2, 48, "Google AI phone", 500, 799);
    addProduct(productList, "Xiaomi 13", 0, 60, "Budget high-end", 450, 699);

    cout << "\nBefore Sorting by Sale Price: \n";
    displayAdminProductList(productList);

    mergeSort(productList);

    cout << "\nAfter Sorting by Sale Price: \n";
    displayAdminProductList(productList);

    return 0;
}