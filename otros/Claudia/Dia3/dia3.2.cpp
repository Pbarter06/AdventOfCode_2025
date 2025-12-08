#include <bits/stdc++.h>
using namespace std;

// Función que obtiene la subsecuencia máxima de longitud k
string subsecuenciaMaxima(const string &linea, int k) {
    vector<char> pila;
    int porEliminar = (int)linea.size() - k; // cuántos dígitos podemos descartar

    // Recorremos cada dígito de la línea
    for (char c : linea) {
        // Mientras podamos eliminar y el último dígito sea menor que el actual, lo quitamos
        while (!pila.empty() && porEliminar > 0 && pila.back() < c) {
            pila.pop_back();
            porEliminar--;
        }
        // Añadimos el dígito actual a la pila
        pila.push_back(c);
    }

    // Si aún quedan por eliminar, recortamos al final
    while (porEliminar > 0) {
        pila.pop_back();
        porEliminar--;
    }

    // Construimos el resultado con los primeros k dígitos
    return string(pila.begin(), pila.begin() + k);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ifstream archivo("dia3.txt");
    if (!archivo) {
        cerr << "No se pudo abrir el archivo dia3.txt\n";
        return 1;
    }

    string linea;
    long long total = 0;

    // Leer cada línea del archivo
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        // Obtenemos la mejor subsecuencia de 12 dígitos
        string mejor = subsecuenciaMaxima(linea, 12);

        // Convertimos la subsecuencia en número
        long long valor = stoll(mejor);

        // Sumamos al total
        total += valor;
    }

    cout << "Voltaje total de salida (12 dígitos): " << total << "\n";
    return 0;
}

