#include <bits/stdc++.h>
using namespace std;

// Lee todas las líneas de la rejilla desde la entrada estándar
vector<string> leerRejilla() {
    vector<string> rejilla;
    string linea;
    while (getline(cin, linea)) {
        if (!linea.empty() && linea.back() == '\r') linea.pop_back(); // elimina retorno de carro si existe
        rejilla.push_back(linea); // añade cada línea a la rejilla
    }
    return rejilla;
}

// Encuentra la posición del origen 'S'
pair<int,int> encontrarOrigen(const vector<string>& rejilla) {
    for (int fila = 0; fila < (int)rejilla.size(); ++fila) {
        for (int col = 0; col < (int)rejilla[fila].size(); ++col) {
            if (rejilla[fila][col] == 'S') return {fila,col}; // devuelve fila y columna de S
        }
    }
    return {-1,-1}; // si no se encuentra
}

// Procesa una fila en modo cuántico:
// - Recibe un vector con el número de líneas de tiempo por columna en la fila actual.
// - Si hay '^' en una columna, las líneas de tiempo de esa columna se reparten a col-1 y col+1.
// - Si no hay '^', las líneas de tiempo continúan en la misma columna.
// - Devuelve el vector para la siguiente fila.
vector<long long> procesarFilaCuantica(const string& fila, const vector<long long>& lineasTiempo) {
    int ancho = fila.size();
    vector<long long> siguiente(ancho, 0LL);

    for (int col = 0; col < ancho; ++col) {
        long long cnt = lineasTiempo[col];
        if (cnt == 0) continue; // no hay líneas de tiempo en esta columna

        if (fila[col] == '^') {
            // Se produce división cuántica: las cnt líneas de tiempo se bifurcan
            if (col - 1 >= 0) siguiente[col - 1] += cnt; // todas van a la izquierda en una rama
            if (col + 1 < ancho) siguiente[col + 1] += cnt; // todas van a la derecha en otra rama
        } else {
            // Continúan en la misma columna
            siguiente[col] += cnt;
        }
    }
    return siguiente;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 1. Leer toda la rejilla desde stdin
    vector<string> rejilla = leerRejilla();
    if (rejilla.empty()) {
        cout << 0 << "\n"; // si no hay rejilla, no hay líneas de tiempo
        return 0;
    }

    int alto = rejilla.size();
    int ancho = rejilla[0].size();

    // 2. Encontrar la posición del origen 'S'
    auto [filaOrigen, colOrigen] = encontrarOrigen(rejilla);
    if (filaOrigen == -1) {
        cout << 0 << "\n"; // si no hay origen, no hay partícula
        return 0;
    }

    // 3. Inicializar líneas de tiempo: 1 línea en la columna del origen
    vector<long long> lineasTiempo(ancho, 0LL);
    lineasTiempo[colOrigen] = 1LL;

    // 4. Recorrer fila por fila desde debajo del origen hasta el final
    for (int fila = filaOrigen + 1; fila < alto; ++fila) {
        lineasTiempo = procesarFilaCuantica(rejilla[fila], lineasTiempo);

        // Optimización ligera: si todas son cero, podemos cortar
        bool vacio = true;
        for (long long v : lineasTiempo) {
            if (v != 0) { vacio = false; break; }
        }
        if (vacio) break;
    }

    // 5. Sumar todas las líneas de tiempo activas al terminar
    long long totalLineas = 0;
    for (long long v : lineasTiempo) totalLineas += v;

    cout << totalLineas << "\n";
    return 0;
}

