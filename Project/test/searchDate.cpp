#include <string>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
using namespace std;

struct AdminHistory
{ // Sokleap
    int adminID;
    string adminName;
    string commandType;
    string description;
    chrono::system_clock::time_point utcTime;

    AdminHistory *next;
};

struct AdminHistoryStack
{
    int size;
    AdminHistory *top;
};

AdminHistoryStack *createEmptyStack()
{
    AdminHistoryStack *s = new AdminHistoryStack();
    s->size = 0;
    s->top = nullptr;
    return s;
}

chrono::system_clock::time_point getCurrentUTCTime()
{
    chrono::system_clock::time_point utc_time_point = chrono::system_clock::now();
    return utc_time_point;
}

string getCambodiaTime(chrono::system_clock::time_point utcTimePoint)
{

    const std::chrono::hours CAMBODIA_OFFSET = std::chrono::hours(7); // ICT is UTC+07:00

    chrono::system_clock::time_point cambodia_time_point = utcTimePoint + CAMBODIA_OFFSET;

    time_t cambodiaTimeT = chrono::system_clock::to_time_t(cambodia_time_point);

    tm *cambodiaTime = gmtime(&cambodiaTimeT);

    char timeBuffer[30];
    strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M:%S", cambodiaTime);

    return string(timeBuffer);
}

void push(AdminHistoryStack *s, int adminID, string adminName, string commandType, string description, chrono::system_clock::time_point utcTime)
{
    AdminHistory *history = new AdminHistory;

    history->adminID = adminID;
    history->adminName = adminName;
    history->commandType = commandType;
    history->description = description;
    history->utcTime = utcTime;
    history->next = s->top;
    s->top = history;
    s->size++;
}

void pop(AdminHistoryStack *s)
{
    if (s->top == nullptr)
    {
        cout << "History is empty!\n";
        return;
    }
    AdminHistory *temp = s->top;
    s->top = s->top->next;
    delete temp;
    s->size--;
}

void displayHistory(int i, AdminHistory *temp)
{
    string formattedTime = getCambodiaTime(temp->utcTime);
    printf("| %4d | %-5d | %-20s | %-10s | %-50s | %-20s |\n",
           i, temp->adminID, temp->adminName.c_str(), temp->commandType.c_str(), temp->description.c_str(), formattedTime.c_str());
}

void displayAllAdminHistory(AdminHistoryStack *s)
{
    AdminHistory *temp = s->top;
    int i = 1;
    cout << "\n--- All Admin History ---\n";
    cout << "\n+------+-------+----------------------+------------+----------------------------------------------------+----------------------+\n";
    printf("| %4s | %-5s | %-20s | %-10s | %-50s | %-20s |\n",
           "N0", "ID", "NAME", "TYPE", "DESCRIPTION", "HISTORY TIME");
    cout << "+------+-------+----------------------+------------+----------------------------------------------------+----------------------+\n";
    while (temp != nullptr)
    {
        displayHistory(i, temp);
        temp = temp->next;
        i++;
    }
    cout << "+------+-------+----------------------+------------+----------------------------------------------------+----------------------+\n";
}

void displayLastDay(AdminHistoryStack *s)
{
    auto twentyFourHoursAgo = getCurrentUTCTime() - chrono::hours(24);
    AdminHistory *temp = s->top;
    int i = 1;
    bool found = false;
    cout << "\n--- Admin History within the last 24 hours ---\n";
    cout << "\n+------+-------+----------------------+------------+----------------------------------------------------+----------------------+\n";
    printf("| %4s | %-5s | %-20s | %-10s | %-50s | %-20s |\n",
           "N0", "ID", "NAME", "TYPE", "DESCRIPTION", "HISTORY TIME");
    cout << "+------+-------+----------------------+------------+----------------------------------------------------+----------------------+\n";
    while (temp != nullptr)
    {
        if (temp->utcTime >= twentyFourHoursAgo)
        {
            displayHistory(i, temp);
            found = true;
            i++;
        }
        temp = temp->next;
    }
    cout << "+------+-------+----------------------+------------+----------------------------------------------------+----------------------+\n";
    if (!found)
    {
        cout << "No admin history found within the last 24 hours.\n";
    }
}

void displayLastMonth(AdminHistoryStack *s)
{
    auto thirtyDaysAgo = getCurrentUTCTime() - chrono::hours(24 * 30);
    AdminHistory *temp = s->top;
    int i = 1;
    bool found = false;
    cout << "\n--- Admin History within the last 30 days ---\n";
    cout << "\n+------+-------+----------------------+------------+----------------------------------------------------+----------------------+\n";
    printf("| %4s | %-5s | %-20s | %-10s | %-50s | %-20s |\n",
           "N0", "ID", "NAME", "TYPE", "DESCRIPTION", "HISTORY TIME");
    cout << "+------+-------+----------------------+------------+----------------------------------------------------+----------------------+\n";
    while (temp != nullptr){
        if (temp->utcTime >= thirtyDaysAgo)
        {
            displayHistory(i, temp);
            found = true;
            i++;
        }
        temp = temp->next;
    }
    cout << "+------+-------+----------------------+------------+----------------------------------------------------+----------------------+\n";
    if (!found)
    {
        cout << "No admin history found within the last 30 days.\n";
    }
}

int main()
{
    AdminHistoryStack *s = createEmptyStack();

    push(s, 111, "Sok Leap", "Update", "Iphone11 sales price from 1000 to 1100", getCurrentUTCTime());
    push(s, 222, "Sok Leap", "Add", "Add Iphone11 20 units", getCurrentUTCTime());

    displayAllAdminHistory(s);

    displayLastDay(s);

    displayLastMonth(s);

    while (s->top != nullptr) {
        pop(s);
    }
    delete s; 

    return 0;
}