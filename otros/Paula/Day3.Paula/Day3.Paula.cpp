#include <bits/stdc++.h>
using namespace std; 

vector<int> stringTovec(const string& s, vector<int>& vec){
    for(char c : s){
        vec.push_back(c - '0'); 
    }
    return vec;
}

int main(){

    string bank; 

    while(cin >> bank){
        vector<bool> visited(bank.size(), false); 
        vector<int> bankInt;
        bankInt = stringTovec(bank, bankInt);
        int first = 0, sec = 0; 
        for(int i = 0; i < bank.size(); i++){
            if(first < bankInt[i]){
                
                first = bankInt[i];
            }


            
        } 
    }

    return 0; 
}