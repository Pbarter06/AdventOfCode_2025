#include <bits/stdc++.h>
using namespace std;

// Función que comprueba si un número es inválido
// Un número es inválido si está formado por repeticiones exactas de un bloque
bool esInvalido(unsigned long long num) {
    string s = to_string(num);            // Convertimos el número a string
    int n = s.size();

    // Probamos todos los posibles tamaños de bloque
    for (int tam = 1; tam <= n/2; ++tam) {
        if (n % tam != 0) continue;       // El tamaño debe dividir la longitud total
        int repeticiones = n / tam;
        if (repeticiones < 2) continue;   // Debe repetirse al menos 2 veces

        string bloque = s.substr(0, tam); // Tomamos el bloque inicial
        string construido;
        construido.reserve(n);

        // Construimos la cadena repitiendo el bloque
        for (int i = 0; i < repeticiones; i++) {
            construido += bloque;
        }

        // Si coincide con el número original, es inválido
        if (construido == s) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string entrada;
    getline(cin, entrada);                // Leemos toda la línea de entrada

    stringstream ss(entrada);             // Usamos stringstream para separar por comas
    string rango;
    unsigned long long total = 0ULL;      // Acumulador del resultado

    // Procesamos cada rango separado por comas
    while (getline(ss, rango, ',')) {
        size_t guion = rango.find('-');
        if (guion == string::npos) continue; // Si no hay guion, saltamos

        unsigned long long inicio = stoull(rango.substr(0, guion));
        unsigned long long fin    = stoull(rango.substr(guion + 1));
        if (inicio > fin) swap(inicio, fin); // Aseguramos que inicio <= fin

        // Recorremos todos los números del rango
        for (unsigned long long x = inicio; x <= fin; ++x) {
            if (esInvalido(x)) {          // Si el número es inválido
                total += x;               // Lo sumamos al total
            }
        }
    }

    cout << total << "\n";                // Mostramos el resultado final
    return 0;
}

