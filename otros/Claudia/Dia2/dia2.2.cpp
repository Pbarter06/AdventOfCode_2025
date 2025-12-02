#include <bits/stdc++.h>
using namespace std;

bool esInvalido(unsigned long long num) {
    string s = to_string(num);
    int n = s.size();
    for (int size = 1; size <= n/2; ++size) {
        if (n % size != 0) continue;
        int rep = n / size;
        if (rep < 2) continue; // al menos dos repeticiones
        string bloque = s.substr(0, size);
        string t;
        t.reserve(n);
        for (int i = 0; i < rep; i++) t += bloque;
        if (t == s) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string input;
    getline(cin, input); // lee toda la línea

    // separar por comas
    stringstream ss(input);
    string rango;
    unsigned long long total = 0ULL;

    while (getline(ss, rango, ',')) {
        size_t dash = rango.find('-');
        if (dash == string::npos) continue;
        unsigned long long ini = stoull(rango.substr(0, dash));
        unsigned long long fin = stoull(rango.substr(dash+1));
        if (ini > fin) swap(ini, fin);

        for (unsigned long long x = ini; x <= fin; ++x) {
            if (esInvalido(x)) total += x;
        }
    }

    cout << total << "\n";
    return 0;
}

