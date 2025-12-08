#include <bits/stdc++.h>
using namespace std;


// Estructura Union-Find (DSU)

struct DSU {
    vector<int> padre, tam;
    DSU(int n) : padre(n), tam(n,1) {
        iota(padre.begin(), padre.end(), 0); // cada nodo es su propio padre
    }
    int find(int x){ return padre[x]==x ? x : padre[x]=find(padre[x]); }
    bool unite(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return false;       // ya están unidos
        if(tam[a]<tam[b]) swap(a,b); // unimos el más pequeño al más grande
        padre[b]=a;
        tam[a]+=tam[b];
        return true;                 // unión efectiva
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
    sort(distancias.begin(), distancias.end());

    // 4. Creamos la estructura Union-Find para manejar los circuitos
    DSU dsu(n);

    int conjuntos = n;       // al inicio cada caja es su propio circuito
    int ultimoA=-1, ultimoB=-1; // guardaremos el último par conectado

    // 5. Vamos conectando pares hasta que quede un solo circuito
    for(auto &[d,i,j] : distancias){
        if(dsu.unite(i,j)){      // si la unión fue efectiva
            conjuntos--;         // reducimos el número de circuitos
            ultimoA=i;           // guardamos la última conexión
            ultimoB=j;
            if(conjuntos==1) break; // ya están todas conectadas
        }
    }

    // 6. Multiplicamos las coordenadas X de las dos últimas cajas conectadas
    long long resultado = 1LL * cajas[ultimoA][0] * cajas[ultimoB][0];

    // 7. Mostramos el resultado final
    cout << "Resultado: " << resultado << "\n";
    return 0;
}

