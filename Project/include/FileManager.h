// #include "../include/ProductList.h"
// #include <iostream>
// #include <fstream>
// #include <sstream>
// using namespace std;

// // Save all products to ProductList.csv
// void storeProduct(ProductList *ls) {
//     ofstream productFile("../data/ProductList.csv");
//     if (!productFile) {
//         cerr << "Error: Unable to open ProductList.csv for writing.\n";
//         return;
//     }

//     ProductElement *temp = ls->head;
//     while (temp != nullptr) {
//         productFile << temp->id << "|"
//                     << temp->model << "|"
//                     << temp->inStock << "|"
//                     << temp->sold << "|"
//                     << temp->description << "|"
//                     << temp->purchaseCost << "|"
//                     << temp->salePrice << "\n";
//         temp = temp->next;
//     }

//     productFile.close();
// }

// // Clear all nodes in ProductList
// void clearProductList(ProductList *ls) {
//     ProductElement *temp;
//     while (ls->head != nullptr) {
//         temp = ls->head;
//         ls->head = ls->head->next;
//         delete temp;
//     }
//     ls->tail = nullptr;
//     ls->n = 0;
// }

// // Load products from ProductList.csv into linked list
// void loadProductList(ProductList *ls) {
//     ifstream productFile("../data/ProductList.csv");
//     if (!productFile) {
//         cerr << "Warning: ProductList.csv not found. Starting with empty list.\n";
//         return;
//     }

//     clearProductList(ls);  // Reset before loading

//     string line;
//     string fields[7];
//     string token;

//     while (getline(productFile, line)) {
//         stringstream ss(line);
//         int index = 0;

//         while (getline(ss, token, '|')) {
//             fields[index++] = token;
//         }

//         if (index < 7) continue; // Skip invalid rows

//         int id = stoi(fields[0]);
//         string model = fields[1];
//         int inStock = stoi(fields[2]);
//         int sold = stoi(fields[3]);
//         string description = fields[4];
//         double purchaseCost = stod(fields[5]);
//         double salePrice = stod(fields[6]);

//         addProduct(ls, model, inStock, sold, description, purchaseCost, salePrice, true, id);
//     }

//     productFile.close();
// }

// // Save overall report to CSV (also display to console)
// void displayOverallReport(ReportList *rl) {
//     if (rl == nullptr || rl->head == nullptr) {
//         cout << "\nNo report data available.\n";
//         return;
//     }

//     ofstream reportFile("../data/OverallReport.csv");
//     if (!reportFile) {
//         cerr << "Error: Unable to open OverallReport.csv for writing.\n";
//         return;
//     }

//     ReportElement *temp = rl->head;

//     cout << "\n+-------+----------------------+--------------+-------+----------------------+-------------+-------------+------------------+\n";
//     printf("| %-5s | %-20s | %-12s | %-5s | %-20s | %-11s | %-11s | %-16s |\n",
//            "ID", "MODEL", "TOTAL STOCK", "SOLD", "TOTAL PURCHASE COST", "TOTAL EARN", "PROFIT", "ESTIMATE PROFIT");
//     cout << "+-------+----------------------+--------------+-------+----------------------+-------------+-------------+------------------+\n";

//     while (temp != nullptr) {
//         printf("| %-5d | %-20s | %-12d | %-5d | %-20.2f | %-11.2f | %-11.2f | %-16.2f |\n",
//                temp->id, temp->product->model.c_str(), temp->totalStock, temp->totalSold,
//                temp->totalPurchaseCost, temp->totalEarn, temp->profit, temp->estimatProfit);

//         // Save clean | separated data to file
//         reportFile << temp->id << "|"
//                    << temp->product->model << "|"
//                    << temp->totalStock << "|"
//                    << temp->totalSold << "|"
//                    << temp->totalPurchaseCost << "|"
//                    << temp->totalEarn << "|"
//                    << temp->profit << "|"
//                    << temp->estimatProfit << "\n";

//         temp = temp->next;
//     }
//     cout << "+-------+----------------------+--------------+-------+----------------------+-------------+-------------+------------------+\n";

//     reportFile.close();
// }

// // Append a single admin history record to History.csv
// void storeHistory(AdminHistory *temp) {
//     ofstream historyFile("../data/History.csv", ios::app);
//     if (!historyFile) {
//         cerr << "Error: Unable to open History.csv for writing.\n";
//         return;
//     }

//     historyFile << temp->adminID << "|"
//                 << temp->adminName << "|"
//                 << temp->commandType << "|"
//                 << temp->description << "|"
//                 << temp->cambodiaStringTime << "\n";

//     historyFile.close();
// }

// // Load all admin history records into a stack
// void loadAdminHistoryStack(AdminHistoryStack *s) {
//     ifstream historyFile("../data/History.csv");
//     if (!historyFile) {
//         cerr << "Warning: History.csv not found. No admin history loaded.\n";
//         return;
//     }

//     string line;
//     string fields[5];
//     string token;

//     while (getline(historyFile, line)) {
//         stringstream ss(line);
//         int index = 0;

//         while (getline(ss, token, '|')) {
//             fields[index++] = token;
//         }

//         if (index < 5) continue; // Skip invalid rows

//         int adminID = stoi(fields[0]);
//         string adminName = fields[1];
//         string commandType = fields[2];
//         string description = fields[3];
//         string time = fields[4];

//         push(s, adminID, adminName, commandType, description, time);
//     }

//     historyFile.close();
// }
