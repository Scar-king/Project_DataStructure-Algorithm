#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>
using namespace std;


struct AdminHistory { // Sokleap
    int adminID;
    string adminName;
    string commandType;
    string description;
    string cambodiaStringTime;

    AdminHistory *next;
};

struct AdminHistoryStack {
    int size;
    AdminHistory *top;
};

AdminHistoryStack *createEmptyStack() {
    AdminHistoryStack *s = new AdminHistoryStack();
    s -> size = 0;
    s -> top = nullptr;
    return s;
}

chrono::system_clock::time_point getCurrentUTCTime(){
    chrono::system_clock::time_point utc_time_point = std::chrono::system_clock::now();
    return utc_time_point;
}

string getCambodiaTime(chrono::system_clock::time_point utcTimePoint){

    const std::chrono::hours CAMBODIA_OFFSET = std::chrono::hours(7); // ICT is UTC+07:00

    chrono::system_clock::time_point cambodia_time_point = utcTimePoint + CAMBODIA_OFFSET;

    std::time_t cambodiaTimeT = std::chrono::system_clock::to_time_t(cambodia_time_point);

    std::tm* cambodiaTime = std::gmtime(&cambodiaTimeT);

    char timeBuffer[30];
    strftime(timeBuffer, sizeof(timeBuffer), "%d/%m/%Y %H:%M:%S", cambodiaTime);
    
    return string(timeBuffer);
}

void push (AdminHistoryStack *s, int adminID, string adminName, string commandType, string description, string cambodiaStringTime){
    AdminHistory* history = new AdminHistory;

    history -> adminID = adminID;
    history -> adminName = adminName;
    history -> commandType = commandType;
    history -> description = description;
    history -> cambodiaStringTime = cambodiaStringTime; 
    history -> next = s -> top;
    s -> top = history;
    s -> size++;
}

void pop(AdminHistoryStack *s){
    if(s->top == nullptr){
        cout << "Stack is empty!\n";
        return;
    } 
    AdminHistory *temp = s->top;
    s->top = s->top->next;
    delete temp;
    s->size--;
}

void displayHistory(int i, AdminHistory *temp)
{
    printf("| %4d | %-5d | %-20s | %-10s | %-50s | %-20s |\n",
           i, temp->adminID, temp->adminName.c_str(), temp->commandType.c_str(), temp->description.c_str(), temp -> cambodiaStringTime.c_str());
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

time_t stringToTimeT(const string &datetimeStr) {
    tm tm{};
    stringstream ss(datetimeStr);
    ss >> get_time(&tm, "%d/%m/%Y %H:%M:%S");
    return mktime(&tm);
}

void displayLastDay(AdminHistoryStack *s)
{
    auto twentyFourHoursAgo = getCurrentUTCTime() - chrono::hours(24);
    time_t twentyFourHoursAgo_t = chrono::system_clock::to_time_t(twentyFourHoursAgo);
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
        time_t recordTime = stringToTimeT(temp-> cambodiaStringTime);
        if (recordTime >= twentyFourHoursAgo_t)
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

time_t getOneMonthAgoTime() {
    time_t now = time(nullptr);
    struct tm *tmNow = localtime(&now);
    tmNow->tm_mon -= 1;
    if (tmNow->tm_mon < 0) {
        tmNow->tm_mon += 12;
        tmNow->tm_year -= 1;
    }
    return mktime(tmNow);
}

void displayLastMonth(AdminHistoryStack *s)
{
    AdminHistory *temp = s->top;
    int i = 1;
    bool found = false;
    cout << "\n--- Admin History within the last 30 days ---\n";
    cout << "\n+------+-------+----------------------+------------+----------------------------------------------------+----------------------+\n";
    printf("| %4s | %-5s | %-20s | %-10s | %-50s | %-20s |\n",
           "N0", "ID", "NAME", "TYPE", "DESCRIPTION", "HISTORY TIME");
    cout << "+------+-------+----------------------+------------+----------------------------------------------------+----------------------+\n";
    time_t oneMonthAgo = getOneMonthAgoTime();
    while (temp != nullptr){
        time_t recordTime = stringToTimeT(temp->cambodiaStringTime);
        if (recordTime >= oneMonthAgo)
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

void storeHistory(AdminHistory *temp)
{
    ofstream historyFile("History.csv", ios::app);
    historyFile << temp->adminID << "|" << temp->adminName.c_str() << "|" << temp->commandType.c_str() << "|" << temp->description.c_str() << "|" << temp -> cambodiaStringTime.c_str() << endl;
    historyFile.close();
}

void loadAdminHistoryStack(AdminHistoryStack* s)
{
    ifstream historyFile("History.csv");
    string history;
    string arrayString[5];
    int index;
    string token;
    while (getline(historyFile, history))
    {
        index = 0;
        stringstream ss(history);
        int index = 0;

        while (getline(ss, token, '|'))
        {
            arrayString[index++] = token;
        }

        int adminID = stoi(arrayString[0]);
        string adminName = arrayString[1];
        string commandType = arrayString[2];
        string description = arrayString[3];
        string time = arrayString[4];

        push(s, adminID, adminName, commandType, description, time);
        
    }
    historyFile.close();
}

int main()
{
    fstream historyFile;
    AdminHistoryStack* s = createEmptyStack();
    push(s, 111, "Sok Leap", "Update", "Iphone11 sales price from 1000 to 1100", getCambodiaTime(getCurrentUTCTime()));
    storeHistory(s -> top);
    push(s, 222, "Sok Leap", "Add", "Add Iphone11 20 units", getCambodiaTime(getCurrentUTCTime()));
    storeHistory(s -> top);
    loadAdminHistoryStack(s);
    displayLastDay(s);
    displayLastMonth(s);
}