#include <bits/stdc++.h>
using namespace std;

// Estructura Union-Find (DSU) para manejar los circuitos
struct DSU {
    vector<int> padre, tam;

    DSU(int n) {
        padre.resize(n);
        tam.resize(n, 1);
        iota(padre.begin(), padre.end(), 0); // cada nodo empieza siendo su propio padre
    }

    int find(int x) {
        if (padre[x] == x) return x;
        return padre[x] = find(padre[x]); // compresión de caminos
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false; // ya están en el mismo circuito
        if (tam[a] < tam[b]) swap(a, b); // unimos el más pequeño al más grande
        padre[b] = a;
        tam[a] += tam[b];
        return true;
    }

    int size(int x) {
        return tam[find(x)];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Leer las coordenadas desde el archivo
    ifstream archivo("dia8.txt");
    vector<array<int,3>> cajas;
    int x,y,z;
    while (archivo >> x) {
        char coma;
        archivo >> coma >> y >> coma >> z;
        cajas.push_back({x,y,z});
    }

    int n = cajas.size();

    // Guardar todas las distancias entre pares
    vector<tuple<double,int,int>> distancias;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            long long dx = cajas[i][0] - cajas[j][0];
            long long dy = cajas[i][1] - cajas[j][1];
            long long dz = cajas[i][2] - cajas[j][2];
            double d = sqrt(dx*dx + dy*dy + dz*dz); // distancia euclídea
            distancias.push_back({d,i,j});
        }
    }

    // Ordenamos las distancias de menor a mayor
    sort(distancias.begin(), distancias.end());

    DSU dsu(n);

    int conjuntos = n; // al inicio cada caja es su propio circuito
    int ultimoA = -1, ultimoB = -1;

    // Vamos conectando hasta que quede un solo circuito
    for (auto &[d,i,j] : distancias) {
        if (dsu.unite(i,j)) {
            conjuntos--;          // reducimos el número de circuitos
            ultimoA = i;          // guardamos la última conexión
            ultimoB = j;
            if (conjuntos == 1) break; // ya están todas conectadas
        }
    }

    // Multiplicamos las coordenadas X de las dos últimas cajas conectadas
    long long resultado = 1LL * cajas[ultimoA][0] * cajas[ultimoB][0];

    cout << "Resultado: " << resultado << "\n";
    return 0;
}

