#include <string>
#include <iostream>
#include <cstdio>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <fstream>
using namespace std;

constexpr int MIN_STOCK = 0;
constexpr int MAX_STOCK = 1000;

constexpr double MIN_PRICE = 1.0;
constexpr double MAX_PRICE = 10000.0;

using namespace std;

struct ProductElement
{
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

// Define Linked List structure
struct ProductList
{
    int n;
    int i;
    ProductElement *head;
    ProductElement *tail;
};

ProductList *createList()
{
    ProductList *ls = new ProductList;
    ls->n = 0;
    ls->i = 1000;
    ls->head = nullptr;
    ls->tail = nullptr;
    return ls;
}

void addProduct(ProductList *ls, string model, int inStock, int sold, string description, double purchaseCost, double salePrice, bool isLoadData, int id)
{
    ProductElement *p = new ProductElement;
    if (isLoadData)
    {
        p->id = id;
    }
    else
    {
        p->id = ls->i;
    }
    p->model = model;
    p->inStock = inStock;
    p->sold = sold;
    p->description = description;
    p->purchaseCost = purchaseCost;
    p->salePrice = salePrice;
    p->next = nullptr;
    p->prev = ls->tail;
    if (inStock == 0)
    {
        p->status = "\033[31mOut of Stock\033[0m";
    }
    else if (inStock <= static_cast<int>((inStock + sold) * 0.25))
    {
        p->status = "\033[33mLow Stock\033[0m   ";
    }
    else
    {
        p->status = "\033[32mAvailable\033[0m   ";
    }

    if (ls->n == 0)
    {
        ls->head = p;
    }
    else
    {
        ls->tail->next = p;
    }
    ls->tail = p;
    ls->n++;
    ls->i++;
}

// Update Product
// void updateProductById(ProductList *ls, int targetId){
//     ProductElement *temp = ls->head;
//     while(temp != nullptr && temp->id != targetId) {
//         temp = temp->next;
//     }

//     if(temp == nullptr) {
//         cout << "Product with ID " << targetId << " not found.\n";
//         return;
//     }

//     cout << "\nUpdating Product ID: " << targetId << "\n";
//     cout << "Current model: " << temp->model << "\nNew model: ";
//     getline(cin, temp->model);

//     temp->inStock = getValidateIntInRange("Enter new quantity in stock (1-1000): ", MIN_STOCK, MAX_STOCK);
//     temp->sold = getValidateIntInRange("Enter new quantity sold (1-1000): ", MIN_STOCK, MAX_STOCK);

//     cout << "New description: ";
//     getline(cin, temp->description);

//     temp->purchaseCost = getValidateDoubleInRange("New purchase cost($1.00 - $10000.00): ", MIN_PRICE, MAX_PRICE);
//     temp->salePrice = getValidateDoubleInRange("New sale price($1.00 - $10000.00): ", MIN_PRICE, MAX_PRICE);

//     // Update status
//     if(temp->inStock == 0) {
//         temp->status = "\033[31mOut of Stock\033[0m";
//     } else if(temp->inStock <= static_cast<int>((temp->inStock + temp->sold) * 0.25)) {
//         temp->status = "\033[33mLow Stock\033[0m   ";
//     } else {
//         temp->status = "\033[32mAvailable\033[0m   ";
//     }

//     cout << "Product updated successfully.\n";
// }

// Search Product by ID
ProductElement *searchProductByID(ProductList *ls, int ID)
{ // Sokleap
    ProductElement *temp = ls->head;
    while (temp != nullptr)
    {
        if (temp->id == ID)
        {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

// Delete Product by ID
void deleteProductByID(ProductList *ls, int ID)
{ // Sokleap
    ProductElement *temp = searchProductByID(ls, ID);
    if (temp != nullptr)
    {
        if (ls->n == 1)
        {
            delete temp;
            ls->head = nullptr;
            ls->tail = nullptr;
        }
        else
        {
            // 1 2 3 4
            // delete 1 -> temp = 1, prev of temp = nullptr;
            if (temp->prev == nullptr)
            {
                temp->next->prev = nullptr;
                ls->head = temp->next;
                delete temp;
            }
            else
            {
                // 1 2 3 4
                // delete 4 -> temp = 4, next of temp = nullptr;
                temp->prev->next = temp->next;
                ls->tail = temp->prev;
                delete temp;
            }
            cout << "Successfully deleted product!\n";
        }
        ls->n--;
        return;
    }
    cout << "Cannot delete!\n";
}

void displayProductByID(ProductList *ls, int ID)
{
    ProductElement *temp = searchProductByID(ls, ID);
    if (temp != nullptr)
    {
        cout << "\n+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
        printf("| %-5s | %-20s | %-5s | %-5s | %-35s | %-16s | %-13s | %-12s |\n", "ID", "MODEL", "STOCK", "SOLD", "DESCRIPTION", "PURCHASE COST($)", "SALE PRICE($)", "STATUS");
        cout << "+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
        printf("| %5d | %-20s | %5d | %5d | %-35s | %16.2f | %13.2f | %-12s |\n", temp->id, temp->model.c_str(), temp->inStock, temp->sold, temp->description.c_str(), temp->purchaseCost, temp->salePrice, temp->status.c_str());
        cout << "+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
        return;
    }
    cout << "Product not found!\n";
}

void displayAdminProductList(ProductList *ls)
{ // Sokleap
    ProductElement *temp = ls->head;
    cout << "\n+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
    printf("| %-5s | %-20s | %-5s | %-5s | %-35s | %-16s | %-13s | %-12s |\n", "ID", "MODEL", "STOCK", "SOLD", "DESCRIPTION", "PURCHASE COST($)", "SALE PRICE($)", "STATUS");
    cout << "+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
    while (temp != nullptr)
    {
        printf("| %5d | %-20s | %5d | %5d | %-35s | %16.2f | %13.2f | %-12s |\n",
               temp->id, temp->model.c_str(), temp->inStock, temp->sold, temp->description.c_str(), temp->purchaseCost, temp->salePrice, temp->status.c_str());
        temp = temp->next;
    }
    cout << "+-------+----------------------+-------+-------+-------------------------------------+------------------+---------------+--------------+\n";
}

void displayUserProductList(ProductList *ls)
{ // Kheang Ann, Not include *** inStock and sold ***
    ProductElement *temp = ls->head;
    cout << "+-------+----------------------+-------------------------------------+----------+--------------+" << endl;
    printf("| %-5s | %-20s | %-35s | %-8s | %-12s |\n", "ID", "MODEL", "DESCRIPTION", "PRICE($)", "STATUS");
    cout << "+-------+----------------------+-------------------------------------+----------+--------------+" << endl;
    while (temp != nullptr)
    {
        // cout << temp->name << " ";
        printf("| %-5d | %-20s | %-35s | %8.2f | %-12s |\n", temp->id, temp->model.c_str(), temp->description.c_str(), temp->salePrice, temp->status.c_str());
        temp = temp->next;
    }
    cout << "+-------+----------------------+-------------------------------------+----------+--------------+" << endl;
}

void storeProduct(ProductList *ls)
{ // Sokleap
    ofstream productFile("ProductList.csv");
    ProductElement *temp = ls -> head;
    while (temp != nullptr)
    {
        productFile << temp->id << "|" << temp->model << "|" << temp->inStock << "|" << temp->sold << "|" << temp->description << "|" << temp->purchaseCost << "|" << temp->salePrice << "|" << temp->status << endl;
        temp = temp -> next;
    }
    productFile.close();
}

void loadProductList(ProductList *ls)
{ // Sokleap
    ifstream productFile("ProductList.csv");
    string history;
    string arrayString[8];
    int index;
    string token;
    while (getline(productFile, history))
    {
        index = 0;
        stringstream ss(history);
        int index = 0;

        while (getline(ss, token, '|'))
        {
            arrayString[index++] = token;
        }

        int id = stoi(arrayString[0]);
        string model = arrayString[1];
        int inStock = stoi(arrayString[2]);
        int sold = stoi(arrayString[3]);
        string description = arrayString[4];
        double purchaseCost = stod(arrayString[5]);
        double salePrice = stod(arrayString[6]);
        string status = arrayString[7];

        addProduct(ls, model, inStock, sold, description, purchaseCost, salePrice, true, id);
    }
    productFile.close();
}

int main()
{
    ProductList *myList = createList();
    addProduct(myList, "Iphone 13 PRO MAX", 5, 20, "IOS, Ram 8GB, Storage 256GB", 899.99, 999.99, false, 0);
    addProduct(myList, "Iphone 16 PRO", 10, 11, "IOS, Ram 8GB, Storage 1T", 1299.99, 1499.99, false, 0);
    addProduct(myList, "Iphone 14 PRO MAX", 0, 30, "IOS, Ram 8GB, Storage 128GB", 999.99, 1399.99, false, 0);
    storeProduct(myList);
    // loadProductList(myList);
    // displayAdminProductList(myList);
}