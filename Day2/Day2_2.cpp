#include <bits/stdc++.h>
using namespace std;


long long StringToLong(string s){
    long long n = 0;
    for(char c : s){
        n = n * 10 + (c - '0');
    }
    return n;
}



bool esRepetido_v2(const string& s, int p) {
    int n = s.size();
    string pat = s.substr(0, p);
    int rep = n / p;

    for (int k = 1; k < rep; k++) {
        if (s.compare(k * p, p, pat) != 0) {
            return false;
        }
    }
    return true;
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
        cout << segment << "\n";

        for (long long n = L; n <= R; n++) {
            string s = to_string(n);
            int len = s.size();

            for (int p = 1; p <= len/2; p++) {
                if (len % p != 0) continue;

                if (esRepetido_v2(s, p)) {
                    ans += n;
                    break;     
                }
            }

                        
        }
    }

    cout << ans << "\n";
    return 0; 
}