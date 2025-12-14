#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <set>
using namespace std;

map<string, vector<string>> conexiones;

// DFS que cuenta caminos válidos directamente
long long contar(string actual, set<string> &visitados, bool tieneFFT, bool tieneDAC) {
    if (actual == "out") {
        return (tieneFFT && tieneDAC) ? 1 : 0;
    }
    if (visitados.count(actual)) return 0;

    visitados.insert(actual);

    long long total = 0;
    for (string siguiente : conexiones[actual]) {
        total += contar(siguiente, visitados,
                        tieneFFT || (siguiente == "fft"),
                        tieneDAC || (siguiente == "dac"));
    }

    visitados.erase(actual);
    return total;
}

int main() {
    string linea;
    while (getline(cin, linea)) {
        if (linea.empty()) continue;
        size_t pos = linea.find(':');
        if (pos == string::npos) continue;

        string nombre = linea.substr(0, pos);
        string resto = linea.substr(pos + 1);

        auto trim = [](string s) {
            size_t a = s.find_first_not_of(" \t");
            size_t b = s.find_last_not_of(" \t");
            if (a == string::npos) return string();
            return s.substr(a, b - a + 1);
        };
        nombre = trim(nombre);
        resto = trim(resto);

        vector<string> lista;
        string palabra;
        stringstream ss(resto);
        while (ss >> palabra) {
            lista.push_back(palabra);
        }
        conexiones[nombre] = lista;
    }

    set<string> visitados;
    cout << contar("svr", visitados, false, false) << endl;
    return 0;
}

