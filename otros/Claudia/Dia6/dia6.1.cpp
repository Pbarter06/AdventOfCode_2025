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

    // Función para extraer números dentro de un bloque
    auto extraerNumeros = [&](int filaArriba, int filaAbajo, int izq, int der) {
        vector<long long> numeros;
        for (int f = filaArriba; f <= filaAbajo; ++f) {
            int col = izq;
            while (col <= der) {
                while (col <= der && !isdigit(rejilla[f][col])) ++col;
                if (col > der) break;
                int inicio = col;
                while (col <= der && isdigit(rejilla[f][col])) ++col;
                string token = rejilla[f].substr(inicio, col - inicio);
                numeros.push_back(stoll(token));
            }
        }
        return numeros;
    };

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
    for (auto &bloque : bloques) {
        auto [filaOp, operador] = encontrarOperador(bloque.izquierda, bloque.derecha);
        if (filaOp < 0) continue;
        vector<long long> numeros = extraerNumeros(0, filaOp - 1, bloque.izquierda, bloque.derecha);
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

