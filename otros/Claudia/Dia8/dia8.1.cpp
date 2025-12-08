#include <bits/stdc++.h>
using namespace std;


// Estructura Union-Find (DSU)

struct DSU {
    vector<int> padre, tam;
    DSU(int n) : padre(n), tam(n,1) {
        iota(padre.begin(), padre.end(), 0); // cada nodo es su propio padre
    }
    int find(int x){ return padre[x]==x ? x : padre[x]=find(padre[x]); }
    void unite(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return;              // ya están unidos
        if(tam[a]<tam[b]) swap(a,b);  // unimos el más pequeño al más grande
        padre[b]=a;
        tam[a]+=tam[b];
    }
    int size(int x){ return tam[find(x)]; }
};


// Programa principal

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 1. Abrimos el archivo de entrada con las coordenadas de las cajas
    ifstream archivo("dia8.txt");
    vector<array<int,3>> cajas;
    int x,y,z;
    while(archivo >> x){          // leemos el primer número (X)
        char c;                   // variable para la coma
        archivo >> c >> y >> c >> z; // leemos coma, Y, coma, Z
        cajas.push_back({x,y,z}); // guardamos la caja en el vector
    }

    int n = (int)cajas.size();    // número total de cajas

    // 2. Calculamos todas las distancias entre pares de cajas
    vector<tuple<double,int,int>> distancias;
    distancias.reserve((size_t)n*(n-1)/2); // reservamos memoria
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            long long dx = (long long)cajas[i][0] - cajas[j][0];
            long long dy = (long long)cajas[i][1] - cajas[j][1];
            long long dz = (long long)cajas[i][2] - cajas[j][2];
            double d = sqrt((double)dx*dx + (double)dy*dy + (double)dz*dz);
            distancias.emplace_back(d,i,j); // guardamos distancia y los índices
        }
    }

    // 3. Ordenamos todas las distancias de menor a mayor
    //    (std::sort usa divide y vencerás internamente)
    sort(distancias.begin(), distancias.end());

    // 4. Creamos la estructura Union-Find para manejar los circuitos
    DSU dsu(n);

    // 5. Conectamos exactamente los 1000 pares más cortos
    //    aunque algunos ya estén unidos, se cuentan igual
    for(int k=0; k<1000 && k<(int)distancias.size(); k++){
        auto [d,i,j] = distancias[k]; // sacamos distancia y cajas
        dsu.unite(i,j);               // unimos esas dos cajas
    }

    // 6. Calculamos los tamaños de todos los circuitos resultantes
    vector<int> tamanos;
    for(int i=0;i<n;i++){
        if(dsu.find(i)==i)            // si es raíz de un circuito
            tamanos.push_back(dsu.size(i)); // guardamos su tamaño
    }
    sort(tamanos.rbegin(), tamanos.rend()); // ordenamos de mayor a menor

    // 7. Multiplicamos los tres circuitos más grandes
    long long resultado = 1;
    for(int i=0;i<3 && i<(int)tamanos.size(); i++)
        resultado *= tamanos[i];

    // 8. Mostramos el resultado final
    cout << "Resultado: " << resultado << "\n";
    return 0;
}

