#include <bits/stdc++.h>
using namespace std;

// Día 4 - Parte 1
// Cuenta cuántos símbolos '@' tienen menos de 4 vecinos '@' alrededor.
// Se consideran las 8 direcciones (horizontal, vertical y diagonales).

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Rejilla de entrada
    vector<string> rejilla;
    string linea;

    // Leer todas las líneas de la entrada
    while (getline(cin, linea)) {
        if (!linea.empty() && linea.back() == '\r') linea.pop_back(); // limpiar CR si existe
        if (!linea.empty()) rejilla.push_back(linea);
    }

    int filas = (int)rejilla.size();
    int columnas = filas ? (int)rejilla[0].size() : 0;

    // Función para comprobar si una posición está dentro de la rejilla
    auto dentro = [&](int f, int c) {
        return f >= 0 && f < filas && c >= 0 && c < columnas;
    };

    // Desplazamientos en las 8 direcciones
    int df[8] = {-1,-1,-1,0,0,1,1,1};
    int dc[8] = {-1,0,1,-1,1,-1,0,1};

    long long accesibles = 0;

    // Recorrer toda la rejilla
    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            if (rejilla[f][c] != '@') continue;

            int vecinos = 0;
            for (int k = 0; k < 8; k++) {
                int nf = f + df[k], nc = c + dc[k];
                if (dentro(nf, nc) && rejilla[nf][nc] == '@') vecinos++;
            }

            // Si tiene menos de 4 vecinos '@', se considera accesible
            if (vecinos < 4) accesibles++;
        }
    }

    cout << accesibles << "\n";
    return 0;
}

