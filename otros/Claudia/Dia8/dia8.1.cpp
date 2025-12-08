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

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return; // ya están en el mismo circuito
        if (tam[a] < tam[b]) swap(a, b); // unimos el más pequeño al más grande
        padre[b] = a;
        tam[a] += tam[b];
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

    // Conectar exactamente los 1000 pares más cercanos
    for (int k = 0; k < 1000 && k < (int)distancias.size(); k++) {
        auto [d,i,j] = distancias[k];
        dsu.unite(i,j); // intentamos unir aunque ya estén conectados
    }

    // Calcular tamaños de todos los circuitos
    vector<int> tamanos;
    for (int i = 0; i < n; i++) {
        if (dsu.find(i) == i) { // raíz de un conjunto
            tamanos.push_back(dsu.size(i));
        }
    }

    // Ordenamos los tamaños de mayor a menor
    sort(tamanos.rbegin(), tamanos.rend());

    // Multiplicamos los tres más grandes
    long long resultado = 1;
    for (int i = 0; i < 3 && i < (int)tamanos.size(); i++) {
        resultado *= tamanos[i];
    }

    cout << "Resultado: " << resultado << "\n";
    return 0;
}

