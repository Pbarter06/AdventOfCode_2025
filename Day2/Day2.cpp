#include <bits/stdc++.h>
using namespace std;


long long StringToLong(string s){
    long long n = 0;
    for(char c : s){
        n = n * 10 + (c - '0');
    }
    return n;
}

bool esRepetido(const string& s) {
    int n = s.size();
    if (n % 2 != 0) return false;

    string left = s.substr(0, n/2);
    string right = s.substr(n/2);

    return left == right;
}



int main(){

    long long ans = 0;
    string linea; 
    getline(cin, linea);
    stringstream ss(linea);
    string segment; 

    while(getline(ss, segment, ',')){
        int pos = segment.find('-');
        long long L = StringToLong(segment.substr(0, pos));
        long long R = StringToLong(segment.substr(pos+1));

        for (long long n = L; n <= R; n++) {
            string s = to_string(n);
            if (esRepetido(s)) {
                ans += n;
            }
        }
    }

    cout << ans << "\n";
    return 0; 
}