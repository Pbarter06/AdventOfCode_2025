#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// Función que comprueba si un número es "inválido"
// Un número es inválido si tiene longitud par y sus dos mitades son iguales
bool es_invalido(long long n) {
    string s = to_string(n);              // Convertimos el número a string
    if (s.size() % 2 != 0) return false;  // Si la longitud es impar, no puede ser inválido
    int mitad = s.size() / 2;             // Calculamos la mitad
    // Comparamos la primera mitad con la segunda
    return s.substr(0, mitad) == s.substr(mitad);
}

int main() {
    ifstream archivo("dia2.txt");         // Abrimos el archivo de entrada
    string entrada;
    getline(archivo, entrada);            // Leemos toda la línea

    long long total = 0;                  // Acumulador del resultado
    stringstream ss(entrada);             // Usamos stringstream para separar por comas
    string rango;

    // Procesamos cada rango separado por comas
    while (getline(ss, rango, ',')) {
        size_t guion = rango.find('-');   // Buscamos el guion que separa inicio-fin
        long long inicio = stoll(rango.substr(0, guion));
        long long fin    = stoll(rango.substr(guion + 1));

        // Recorremos todos los números del rango
        for (long long n = inicio; n <= fin; n++) {
            if (es_invalido(n)) {         // Si el número es inválido
                total += n;               // Lo sumamos al total
            }
        }
    }

    cout << "Resultado: " << total << endl; // Mostramos el resultado final
    return 0;
}

