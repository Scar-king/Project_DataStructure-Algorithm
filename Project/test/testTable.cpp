#include <iostream>
#include <cstdlib>
using namespace std;

struct ReportElement {
    int id;
    string model;
    int totalStock;
    int sold;
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

ReportList *createList(){
    ReportList *ls = new ReportList;
    ls->n = 0;
    ls->head = nullptr;
    ls->tail = nullptr;
    return ls;
}

void addEnd(ReportList *ls, string model, int totalStock, int sold, double totalPurchaseCost, double totalEarn, double profit, double estimatProfit){
    ReportElement *re = new ReportElement;
    re -> id = 1000 + ls -> n;
    re -> model = model;
    re -> totalStock = totalStock;
    re -> sold = sold;
    re -> totalPurchaseCost = totalPurchaseCost;
    re -> totalEarn = totalEarn;
    re -> profit = profit;
    re -> estimatProfit = estimatProfit;
    re -> next = nullptr;
    re -> prev = ls -> tail;

    // totalStock = qtyIn - qtyOut;
    // sold = qtyOut;
    // totalPurchaseCost = costPrice * sold;
    // totalEarn = price * sold;
    // profit = totalEarn - totalPurchaseCost;
    // estimatProfit = profit + (totalStock * (price - costPrice));

    if(ls -> n == 0){
        ls -> head = re;
    }
    else{
        ls -> tail -> next = re; 
    }
    ls -> tail = re;
    ls -> n++;
}

void AdminProductList(){ // Sok Leap

}

void displayMonthlyReport(ReportList *ls) { // Davin
    ReportElement *temp = ls->head;
    cout << "\n+------+-----------------+--------------+-------+----------------------+-------------+-------------+------------------+\n";
    printf("| %-4s | %-15s | %-12s | %-5s | %-20s | %-11s | %-11s | %-16s |\n",
           "ID", "MODEL", "TOTAL STOCK", "SOLD", "TOTAL PURCHASE COST", "TOTAL EARN", "PROFIT", "ESTIMATE PROFIT");
    cout << "+------+-----------------+--------------+-------+----------------------+-------------+-------------+------------------+\n";
    while (temp != nullptr) {
        printf("| %-4d | %-15s | %-12d | %-5d | %-20.2f | %-11.2f | %-11.2f | %-16.2f |\n",
               temp->id, temp->model.c_str(), temp->totalStock, temp->sold,
               temp->totalPurchaseCost, temp->totalEarn, temp->profit, temp->estimatProfit);
        temp = temp->next;
    }
    cout << "+------+-----------------+--------------+-------+----------------------+-------------+-------------+------------------+\n";
}


void transactionReport(){ // Val

}

void userProductList(){ // Kheang ann

}

int main(){

    ReportList *ls = createList();

    // List *ls, string model, int inStock, int sold, string description, double price
    addEnd(ls, "iPhone 14 Pro", 47, 50, 1000.00, 2000.00, 3000.00, 5000.00);
    addEnd(ls, "iPhone 13 Pro", 47, 50, 1000.00, 2000.00, 3000.00, 5000.00);
    addEnd(ls, "iPhone X", 47, 50, 1000.00, 2000.00, 3000.00, 5000.00);

    displayMonthlyReport(ls);
  

    return 0;
}