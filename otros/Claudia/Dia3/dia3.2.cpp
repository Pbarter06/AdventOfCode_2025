#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Función para obtener el máximo número de longitud k como subsecuencia
string maxSubsequence(const string &line, int k) {
    vector<char> stack;
    int toRemove = line.size() - k; // cuántos dígitos podemos descartar

    for (char c : line) {
        while (!stack.empty() && toRemove > 0 && stack.back() < c) {
            stack.pop_back();
            toRemove--;
        }
        stack.push_back(c);
    }

    // Si aún quedan por quitar, recorta al final
    while (toRemove > 0) {
        stack.pop_back();
        toRemove--;
    }

    // Construir resultado con los primeros k dígitos
    return string(stack.begin(), stack.begin() + k);
}

int main() {
    ifstream file("dia3.txt");
    if (!file) {
        cerr << "No se pudo abrir el archivo dia3.txt" << endl;
        return 1;
    }

    string line;
    long long total = 0;

    while (getline(file, line)) {
        if (line.empty()) continue;

        string best = maxSubsequence(line, 12);

        // Convertir a número grande (usa stoll si cabe en long long)
        long long val = stoll(best);
        total += val;
    }

    cout << "Total output joltage (12 digits): " << total << endl;
    return 0;
}

