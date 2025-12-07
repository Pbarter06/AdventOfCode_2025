#include <bits/stdc++.h>
using namespace std;

// Bloque de problema delimitado por columnas izquierda y derecha
struct BloqueProblema {
    int izquierda, derecha;
};

// Rellena una cadena con espacios a la derecha hasta alcanzar un ancho fijo
static string rellenarDerecha(const string &s, size_t ancho) {
    string t = s;
    if (t.size() < ancho) t.resize(ancho, ' ');
    return t;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Leer todas las líneas de la entrada
    vector<string> rejilla;
    string linea;
    size_t ancho = 0;
    while (getline(cin, linea)) {
        ancho = max(ancho, linea.size());
        rejilla.push_back(linea);
    }
    if (rejilla.empty()) {
        cout << 0 << "\n";
        return 0;
    }
    for (auto &s : rejilla) s = rellenarDerecha(s, ancho);

    int filas = (int)rejilla.size();
    int columnas = (int)ancho;

    // Detectar columnas separadoras (vacías)
    vector<bool> esSeparador(columnas, false);
    for (int c = 0; c < columnas; ++c) {
        bool sep = true;
        for (int f = 0; f < filas; ++f) {
            if (rejilla[f][c] != ' ') { sep = false; break; }
        }
        esSeparador[c] = sep;
    }

    // Construir bloques de columnas contiguas
    vector<BloqueProblema> bloques;
    int c = 0;
    while (c < columnas) {
        while (c < columnas && esSeparador[c]) ++c;
        if (c >= columnas) break;
        int inicio = c;
        while (c < columnas && !esSeparador[c]) ++c;
        int fin = c - 1;
        bloques.push_back({inicio, fin});
    }

    // Función para encontrar el operador (+ o *) dentro de un bloque
    auto encontrarOperador = [&](int izq, int der) {
        for (int f = filas - 1; f >= 0; --f) {
            for (int cc = izq; cc <= der; ++cc) {
                char ch = rejilla[f][cc];
                if (ch == '+' || ch == '*') return pair<int,char>(f, ch);
            }
        }
        return pair<int,char>(-1, 0);
    };

    long long total = 0;
    // Procesar cada bloque en orden de derecha a izquierda
    for (int bi = (int)bloques.size() - 1; bi >= 0; --bi) {
        auto bloque = bloques[bi];
        auto [filaOp, operador] = encontrarOperador(bloque.izquierda, bloque.derecha);
        if (filaOp < 0) continue;

        vector<long long> numeros;
        // Cada columna dentro del bloque representa un número
        for (int col = bloque.izquierda; col <= bloque.derecha; ++col) {
            string digitos;
            for (int f = 0; f < filaOp; ++f) {
                char ch = rejilla[f][col];
                if (isdigit(ch)) digitos.push_back(ch);
            }
            if (!digitos.empty()) {
                numeros.push_back(stoll(digitos));
            }
        }

        if (numeros.empty()) continue;

        long long resultado = (operador == '*') ? 1LL : 0LL;
        if (operador == '*') {
            for (auto v : numeros) resultado *= v;
        } else {
            for (auto v : numeros) resultado += v;
        }
        total += resultado;
    }

    cout << total << "\n";
    return 0;
}

