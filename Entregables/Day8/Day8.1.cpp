#include <bits/stdc++.h>
using namespace std;

struct DSU {
    //padre-> para cada nodo i (alamacena su representante)
    //tam-> tamaño del componente 
    vector<int> padre, tam;

    //método constructor-> inicializar estructura para n elementos
    DSU(int n){
        padre.resize(n);
        //mínimo tamaño 1
        tam.assign(n, 1);
        for(int i = 0; i < n; i++) padre[i] = i;
    }

    //devuelve la raíz del conjunto donde se encuentra x
    int find(int x){
        //CASO BASE
        //si x ya es raíz-> devolver la raiz, osea x
        if(padre[x] == x) return x;
        //llamar recursivamente
        return padre[x] = find(padre[x]);
    }

    //función que une los componentes donde están a y b
    void unir(int a, int b){
        //buscar raices-> llamar a la función
        a = find(a);
        b = find(b);
        //si es la misma raiz continuar
        if(a == b) return;
        //si son diferentes-> unir el + pequeño al grande
        if(tam[a] < tam[b]) swap(a, b);
        //a-> padre de b
        padre[b] = a;
        //sumar los tamaños porque se une
        tam[a] += tam[b];
    }
};


int main(){
    ifstream archivo("input.txt");
    if(!archivo.is_open()){
        cout << "Error al abrir el fichero." << endl;
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
    int n = cajas.size();

    // generar todos los pares con su distancia al cuadrado
    vector<tuple<long long,int,int>> pares; 
    pares.reserve((long long)n * (n - 1) / 2);

    //recorrer todos los pares (j>i para no comparar una caja consigo misma)
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            long long dx = cajas[i][0] - cajas[j][0];
            long long dy = cajas[i][1] - cajas[j][1];
            long long dz = cajas[i][2] - cajas[j][2];
            long long d2 = dx*dx + dy*dy + dz*dz;
            pares.push_back({d2, i, j});
        }
    }

    //ordenar por distancia de menor a mayor
    sort(pares.begin(), pares.end());

    //crear DSU y unir los 1000 pares más cercanos
    DSU dsu(n);

    int limite = min(1000, (int)pares.size());  //número de pares límite para procesar
    for(int k = 0; k < limite; k++){
        auto [d2, a, b] = pares[k];
        dsu.unir(a, b);
    }

    //contar tamaños de cada componente
    unordered_map<int, long long> tamComp;

    for(int i = 0; i < n; i++){ 
        int r = dsu.find(i);
        tamComp[r]++;
    }

    //pasar tamaños a vector y guardarlos (forma vector)
    vector<long long> tamanos;
    for(auto &p : tamComp) tamanos.push_back(p.second);

    //ordenar de mayor a menor
    sort(tamanos.rbegin(), tamanos.rend());

    //multiplicar los 3 mayores
    long long resultado = 1;    //inicializar resultado a 1
    for(int i = 0; i < 3 && i < (int)tamanos.size(); i++){
        resultado *= tamanos[i];
    }

    archivo.close();
    cout << resultado << endl;

    return 0;
}

