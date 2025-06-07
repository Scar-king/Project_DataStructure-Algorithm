#include <iostream>
using namespace std;

void sort(string name[], int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - 1 - i; j++){
            if(name[j] > name[j + 1]){
                string temp = name[j];
                name[j] = name[j + 1];
                name[j + 1] = temp;
            }
        }
    }
}

int main(){

    string name[3] = {"Davin", "Thyda", "Layla"};

    sort(name, 3);

    for(string s : name){
        cout << s << endl;
    }

    return 0;
}