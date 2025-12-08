#include <bits/stdc++.h>
using namespace std;

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

        int n = (int)linea.size();
        vector<int> maxDerecha(n, -1);

        // Recorremos de derecha a izquierda para precalcular
        // el máximo dígito que aparece a la derecha de cada posición
        int maxActual = -1;
        for (int i = n - 1; i >= 0; --i) {
            maxDerecha[i] = maxActual;              // guardamos el máximo visto hasta ahora
            maxActual = max(maxActual, linea[i]-'0'); // actualizamos el máximo con el dígito actual
        }

        int maxVoltaje = 0;
        // Para cada posición, formamos un número con el dígito actual y el mayor a su derecha
        for (int i = 0; i < n; ++i) {
            int A = linea[i] - '0';   // dígito actual
            int B = maxDerecha[i];    // mejor dígito a la derecha
            if (B != -1) {
                int valor = A * 10 + B;   // formamos el número de dos dígitos
                if (valor > maxVoltaje) maxVoltaje = valor; // actualizamos el máximo
            }
        }

        // Sumamos el mejor valor de esta línea al total
        total += maxVoltaje;
    }

    cout << "Voltaje total de salida: " << total << "\n";
    return 0;
}

