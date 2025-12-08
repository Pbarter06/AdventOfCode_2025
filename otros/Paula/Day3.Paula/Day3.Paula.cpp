#include <bits/stdc++.h>
using namespace std; 

vector<int> stringTovec(const string& s, vector<int>& vec){
    for(char c : s){
        vec.push_back(c - '0'); 
    }
    return vec;
}

int FindMax(const vector<int>& vec){
    int maxNum = 0;
    for(int i = 0; i + 1 < vec.size(); ++i){
        for(int j = i + 1; j < vec.size(); ++j){
            int candidate = vec[i] * 10 + vec[j];
            if(candidate > maxNum) maxNum = candidate;
        }
    }
    return maxNum;
}


 void buildMaxK(const vector<int>& vec, int start, int k, vector<int>& out){
    if(k == 0) return;
    int n = (int)vec.size();
    int bestDigit = -1;
    int bestIdx = start;
    for(int i = start; i <= n - k; ++i){
        if(vec[i] > bestDigit){
            bestDigit = vec[i];
            bestIdx = i;
            if(bestDigit == 9) break;
        }
    }
    out.push_back(bestDigit);
    buildMaxK(vec, bestIdx + 1, k - 1, out);
 }





long long FindMax_v2(const vector<int>& vec, int k = 12){
    if((int)vec.size() < k) return 0;
    vector<int> out;
    out.reserve(k);
    buildMaxK(vec, 0, k, out);
    long long value = 0;
    for(int d : out) value = value * 10 + d;
    return value;
}


int main(){

    string bank; 
    long long ans = 0; 

    while(cin >> bank){
        vector<int> vec; 
        stringTovec(bank, vec); 
        long long m = FindMax_v2(vec, 12);
        cout << m << '\n';
        ans += m;
    }
    cout << ans << '\n';
    
    return 0; 
}