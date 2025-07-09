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

ProductElement *split(ProductElement *head) {
    // Both fast and slow are starting from head
    ProductElement *fast = head;
    ProductElement *slow = head;

    // This technique helps you find the middle node efficiently.
    while(fast->next && fast->next->next) { // Finding the middle node
        fast = fast->next->next;
        slow = slow->next;
    }

    ProductElement *second = slow->next; // the node after the midpoint become the head of the second half
    slow->next = nullptr; // cuts the list at midpoint, ending the first half
    if(second) second->prev = nullptr; // avoid second node point back to the first half

    return second; // second half
}

ProductElement *merge(ProductElement *first, ProductElement *second) {
    // Base cases to handle null inputs
    if(!first) return second;
    if(!second) return first;

    if(first->salePrice >= second->salePrice) { // >= for descending order
        first->next = merge(first->next, second);
        if(first->next) first->next->prev = first;
        first->prev = nullptr;
        return first;
    } else {
        second->next = merge(first, second->next);
        if(second->next) second->next->prev = second;
        second->prev = nullptr;
        return second;
    }
}

ProductElement *mergeSort(ProductElement *head) {
    // prevents null or only one element
    if(!head || !head->next) return head;

    ProductElement *second = split(head);
    // Both head and second keep splitting until each part has 1 node
    head = mergeSort(head);
    second = mergeSort(second); 

    // Now it take 2 sorted halves, and combine them into one sorted list
    return merge(head, second);
}

/*

    This is how ProductElement *mergeSort(ProductElement *head) work: 

    mergeSort([899, 999, 699, 799])
    ├── mergeSort([899, 999])
    │   ├── mergeSort([899]) → [899]
    │   └── mergeSort([999]) → [999]
    │   → merge([899], [999]) → [999 ⇄ 899]
    ├── mergeSort([699, 799])
    │   ├── mergeSort([699]) → [699]
    │   └── mergeSort([799]) → [799]
    │   → merge([699], [799]) → [799 ⇄ 699]
    → merge([999 ⇄ 899], [799 ⇄ 699])
    → [999 ⇄ 899 ⇄ 799 ⇄ 699]


*/

void sortProductList(ProductList *plist){
    plist->head = mergeSort(plist->head);

    ProductElement *temp = plist->head;
    plist->tail = nullptr;
    while(temp && temp->next){
        temp = temp->next;
    }
    plist->tail = temp;
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

    sortProductList(productList);

    cout << "\nAfter Sorting by Sale Price: \n";
    displayAdminProductList(productList);

    return 0;
}