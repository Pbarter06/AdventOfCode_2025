#include <bits/stdc++.h>
using namespace std;

// Elimina iterativamente los símbolos '@' que tengan menos de 4 vecinos '@'.
// Se cuentan cuántos símbolos se eliminan en total.

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

    // Desplazamientos en las 8 direcciones
    int df[8] = {-1,-1,-1,0,0,1,1,1};
    int dc[8] = {-1,0,1,-1,1,-1,0,1};

    long long totalEliminados = 0;

    while (true) {
        vector<pair<int,int>> aEliminar;

        // Buscar todos los '@' con menos de 4 vecinos
        for (int f = 0; f < filas; f++) {
            for (int c = 0; c < columnas; c++) {
                if (rejilla[f][c] != '@') continue;

                int vecinos = 0;
                for (int k = 0; k < 8; k++) {
                    int nf = f + df[k];
                    int nc = c + dc[k];
                    if (nf >= 0 && nf < filas && nc >= 0 && nc < columnas && rejilla[nf][nc] == '@') {
                        vecinos++;
                    }
                }

                if (vecinos < 4) {
                    aEliminar.push_back({f, c});
                }
            }
        }

        // Si no hay más para eliminar, terminamos
        if (aEliminar.empty()) break;

        // Eliminar los seleccionados
        for (auto [f, c] : aEliminar) {
            rejilla[f][c] = '.'; // sustituir por punto
        }

        totalEliminados += (long long)aEliminar.size();
    }

    cout << totalEliminados << "\n";
    return 0;
}

