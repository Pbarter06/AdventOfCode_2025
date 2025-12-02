#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

bool es_invalido(long long n) {
    string s = to_string(n);
    if (s.size() % 2 != 0) return false;
    int mitad = s.size() / 2;
    return s.substr(0, mitad) == s.substr(mitad);
}

int main() {
    ifstream file("dia2.txt");
    string entrada;
    getline(file, entrada);

    long long total = 0;
    stringstream ss(entrada);
    string rango;

    while (getline(ss, rango, ',')) {
        size_t dash = rango.find('-');
        long long inicio = stoll(rango.substr(0, dash));
        long long fin = stoll(rango.substr(dash + 1));

        for (long long n = inicio; n <= fin; n++) {
            if (es_invalido(n)) {
                total += n;
            }
        }
    }

    cout << "Resultado: " << total << endl;
    return 0;
}

