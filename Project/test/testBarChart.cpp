#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <windows.h>  // For SetConsoleCP & Sleep
using namespace std;

struct Report {
    string model;
    double profit;
    double estimateProfit;
};

// Colors for Windows console (ANSI codes)
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"

void printBar(int blocks, char symbol, const string &color) {
    cout << color;
    for (int i = 0; i < blocks; i++) {
        cout << symbol;
    }
    cout << RESET;
}

int main() {
    vector<Report> reports;

    ifstream file("../data/OverallReport.csv");
    if (!file) {
        cerr << "Error: Could not open OverallReport.csv\n";
        return 1;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> fields;

        while (getline(ss, token, '|')) {
            fields.push_back(token);
        }

        if (fields.size() < 8) continue;

        string model = fields[1];
        double profit = stod(fields[6]);
        double estimateProfit = stod(fields[7]);

        reports.push_back({model, profit, estimateProfit});
    }
    file.close();

    // Setup ASCII for block characters (177 for hollow, 178 for solid)
    SetConsoleCP(437);
    SetConsoleOutputCP(437);

    int barSymbol = 178;  // Solid block character
    double scale = 500.0; // 1 block ≈ $500

    cout << "\nProfit Visualization (Green = Profit, Red = Estimate Profit)\n";
    cout << "================================================================\n";

    for (auto &r : reports) {
        cout << setw(20) << left << r.model << " | ";

        // Green Profit Bar
        int profitBlocks = (int)(r.profit / scale);
        printBar(profitBlocks, barSymbol, GREEN);

        // Red Estimated Profit Bar
        int estBlocks = (int)(r.estimateProfit / scale);
        printBar(estBlocks, barSymbol, RED);

        cout << "\n";
    }

    cout << "\nLegend: " 
         << GREEN; printBar(2, barSymbol, GREEN); cout << RESET << " = Profit, "
         << RED; printBar(2, barSymbol, RED); cout << RESET << " = Estimated Profit (1 block approximately $500)\n";

    return 0;
}
