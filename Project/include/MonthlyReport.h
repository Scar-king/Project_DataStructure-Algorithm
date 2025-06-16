// Davin
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

ReportList *createReportList(){
    ReportList *ls = new ReportList;
    ls->n = 0;
    ls->head = nullptr;
    ls->tail = nullptr;
    return ls;
}

void addReport(ReportList *ls, string model, int totalStock, int sold, double totalPurchaseCost, double totalEarn, double profit, double estimatProfit){
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

void displayMonthlyReport(ReportList *ls) { // Davin
    ReportElement *temp = ls->head;
    cout << "\n+-------+----------------------+--------------+-------+----------------------+-------------+-------------+------------------+\n";
    printf("| %-5s | %-20s | %-12s | %-5s | %-20s | %-11s | %-11s | %-16s |\n",
           "ID", "MODEL", "TOTAL STOCK", "SOLD", "TOTAL PURCHASE COST", "TOTAL EARN", "PROFIT", "ESTIMATE PROFIT");
    cout << "+-------+----------------------+--------------+-------+----------------------+-------------+-------------+------------------+\n";
    while (temp != nullptr) {
        printf("| %-5d | %-20s | %-12d | %-5d | %-20.2f | %-11.2f | %-11.2f | %-16.2f |\n",
               temp->id, temp->model.c_str(), temp->totalStock, temp->sold,
               temp->totalPurchaseCost, temp->totalEarn, temp->profit, temp->estimatProfit);
        temp = temp->next;
    }
    cout << "+-------+----------------------+--------------+-------+----------------------+-------------+-------------+------------------+\n";
}