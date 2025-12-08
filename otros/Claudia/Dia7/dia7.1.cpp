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

// Procesa una fila y devuelve los haces activos en la siguiente
unordered_set<int> procesarFila(const string& fila, const unordered_set<int>& hacesActivos, long long& divisiones) {
    unordered_set<int> siguiente;
    int ancho = fila.size();

    for (int col : hacesActivos) {
        if (col < 0 || col >= ancho) continue; // seguridad: fuera de límites
        if (fila[col] == '^') {
            // Se produce una división en esta columna
            ++divisiones;
            if (col-1 >= 0) siguiente.insert(col-1); // haz nuevo a la izquierda
            if (col+1 < ancho) siguiente.insert(col+1); // haz nuevo a la derecha
        } else {
            // El haz continúa hacia abajo en la misma columna
            siguiente.insert(col);
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
        cout << 0 << "\n"; // si no hay rejilla, no hay divisiones
        return 0;
    }

    int alto = rejilla.size(); // número de filas

    // 2. Encontrar la posición del origen 'S'
    auto [filaOrigen, colOrigen] = encontrarOrigen(rejilla);
    if (filaOrigen == -1) {
        cout << 0 << "\n"; // si no hay origen, no hay haz
        return 0;
    }

    // 3. Inicializar conjunto de haces activos con la columna del origen
    unordered_set<int> hacesActivos;
    hacesActivos.insert(colOrigen);

    long long divisiones = 0; // contador de divisiones

    // 4. Recorrer fila por fila desde debajo del origen hasta el final
    for (int fila = filaOrigen+1; fila < alto; ++fila) {
        // procesarFila calcula los haces activos en la siguiente fila
        hacesActivos = procesarFila(rejilla[fila], hacesActivos, divisiones);

        // Si ya no quedan haces activos, se termina la simulación
        if (hacesActivos.empty()) break;
    }

    // 5. Mostrar el número total de divisiones
    cout << divisiones << "\n";
    return 0;
}

