#include <bits/stdc++.h>
using namespace std;

struct DSU{
     vector<int> padre, tam;
    int componentes; // cuántos conjuntos quedan

    //método constructor
    DSU(int n){
        padre.resize(n);    //padre tiene n posiciones
        //tamaño mínimo 1
        tam.assign(n, 1);  
        componentes = n;    //n conjuntos separados
        //inicializar cada elemento a su raíz
        for(int i = 0; i < n; i++) padre[i] = i;
    }

    //función que devuelve la raíz del conjunto al que pertenece
    int find(int x){
        if(padre[x] == x) return x;
        return padre[x] = find(padre[x]);
    }

    //función que intenta unir los conjuntos qu eocntienen a y b
    bool unir(int a, int b){
        //buscar sus raices 
        a = find(a);
        b = find(b);

        if(a == b) return false; // ya estaban unidos, no cambia nada
        
        if(tam[a] < tam[b]) swap(a, b); //son distintos-> unión por tamaño
        padre[b] = a;   //la raíz a es padre de b
        //actualizar tamaño
        tam[a] += tam[b];
        componentes--;
        return true; // hemos unido dos componentes diferentes
    }

};

int main(){
    ifstream archivo("input.txt");
    if(!archivo.is_open()){
        cout<<"Error al abrir el fichero. Inténtelo más tarde.\n"<<endl;
        return 1;
    }

    //guardar coordenadas de cada caja
    vector<array<long long,3>> cajas;
    string linea;

    // Leer coordenadas
    while(getline(archivo, linea)){
        if(linea.empty()) continue;
        replace(linea.begin(), linea.end(), ',', ' ');
        stringstream ss(linea);
        long long x, y, z;
        ss >> x >> y >> z;
        cajas.push_back({x, y, z});
    }

    //contador de cajas leídas
    int n= cajas.size();

    //generar todos los pares con su distancia al cuadrado
     vector<tuple<long long,int,int>> pares; 
    pares.reserve((long long)n * (n - 1) / 2);

    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            long long dx = cajas[i][0] - cajas[j][0];
            long long dy = cajas[i][1] - cajas[j][1];
            long long dz = cajas[i][2] - cajas[j][2];
            long long d2 = dx*dx + dy*dy + dz*dz;
            pares.push_back({d2, i, j});
        }
    }

    //ordenar por distancia creciente
    sort(pares.begin(), pares.end());

    // crear DSU y conectar hasta que haya un solo circuito
    DSU dsu(n);

    long long resultado = -1; // multiplicación de las X de la última conexión útil

    for(auto [d2, a, b] : pares){
        // solo nos interesa cuando realmente une dos componentes distintos
        bool unido = dsu.unir(a, b);
        if(!unido) continue;

        // Si después de esta unión todos están en el mismo circuito,
        // esta es la ÚLTIMA conexión necesaria.
        if(dsu.componentes == 1){
            long long x1 = cajas[a][0];
            long long x2 = cajas[b][0];
            resultado = x1 * x2;
            break;
        }
    }

    archivo.close();

    cout << resultado << endl;
    return 0;
}

