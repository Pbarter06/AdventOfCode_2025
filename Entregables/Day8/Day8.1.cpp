#include <bits/stdc++.h>
using namespace std;

//implementación de la clase Grafo
class Grafo {
public:
    int n;                                   // número de nodos (vértices)
    vector<vector<int>> adj;                 // matriz de adyacencia

    // método constructor
    //se inicializa el grafo con n vértices y una matriz nxm llena de 0 (no se ha visitado aún)
    Grafo(int n) : n(n) {
        adj.assign(n, vector<int>(n, 0));    // matriz n×n inicializada a 0
    }

    // Añadir arista no dirigida entre a y b
    void unir(int a, int b) {
        adj[a][b] = 1;           // marcar conexión a->b
        adj[b][a] = 1;          // marcar conexión b->a
    }

    // DFS para calcular el tamaño del componente conectado
    int dfs(int nodo, vector<int>& visitado) {
        // marcar nodo como visitado
        visitado[nodo] = 1;  
        //inicializar el tamaño del componente a 1
        int tam = 1;                         

        // recorrer todos los nodos para ver si hay adyacencia
        for (int i = 0; i < n; i++) {
            if (adj[nodo][i] == 1 && !visitado[i]) {    //si hay enlace y el nodo no está visitado-> continuar recorrido
                tam += dfs(i, visitado);     // sumar tamaño del subcomponente
            }
        }
        //devolver tamaño total del componente
        return tam;
    }

    // Obtener los tamaños de todos los componentes 
    vector<int> obtenerComponentes() {
        //crear vector para marcar vértices visitados
        vector<int> visitado(n, 0);          // vector de nodos visitados
        //crear vector para almacenar tamaños visitados
        vector<int> tamanos;                 // tamaños de cada componente

        //para cada vértice no visitado-> se hace un dfs y se guarda el tamaño
        for (int i = 0; i < n; i++) {
            if (!visitado[i]) {              // si el nodo no está visitado
                int tam = dfs(i, visitado);  // calcular tamaño del componente
                tamanos.push_back(tam);      // guardar tamaño
            }
        }
        //devolver tamaño de todos los componentes
        return tamanos;
    }
};

int main() {
    //comprobar que se ha abierto correctamente el input.txt
    ifstream archivo("input.txt");
    //si no se ha abierto bien-> lanzar error
    if (!archivo.is_open()) {
        cout << "Error al abrir el fichero. Inténtelo más tarde." << endl;
        return 1;
    }

    //vector para almacenar las coordenadas de las cajas
    vector<array<long long,3>> cajas;
    string linea;

    // leer todo el fichero input línea a línea
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        //separar commas por espacios
        replace(linea.begin(), linea.end(), ',', ' ');
        //extraer las coordenadas
        stringstream ss(linea);
        long long x, y, z;
        ss >> x >> y >> z;
        cajas.push_back({x, y, z});
    }

    int n = cajas.size();

    // generar todos los pares con su distancia al cuadrado
    vector<tuple<long long,int,int>> pares;
    //reservar memoria para todos los pares posibles
    pares.reserve((long long)n * (n - 1) / 2);

    //recorrer todos los pares i y j
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            //calcular la distancia al cuadrado
            long long dx = cajas[i][0] - cajas[j][0];
            long long dy = cajas[i][1] - cajas[j][1];
            long long dz = cajas[i][2] - cajas[j][2];
            long long d2 = dx*dx + dy*dy + dz*dz;
            pares.push_back({d2, i, j});
        }
    }

    // ordenar pares por distancia creciente
    sort(pares.begin(), pares.end());

    // Ccrear grafo con n vértices (vacío)
    Grafo g(n);

    // unir los 1000 pares más cercanos
    //añadir enlaces con los 1000 pares + cercanos
    int limite = min(1000, (int)pares.size());
    for (int k = 0; k < limite; k++) {
        auto [d2, a, b] = pares[k];
        g.unir(a, b);
    }

    // obtener tamaños de los componentes que están conectados
    vector<int> tamanos = g.obtenerComponentes();

    // ordenar de mayor a menor
    sort(tamanos.rbegin(), tamanos.rend());

    // multiplicar los 3 componentes más grandes
    long long resultado = 1;
    for (int i = 0; i < 3 && i < (int)tamanos.size(); i++) {
        resultado *= tamanos[i];
    }

    //imprimir resultado final
    cout << resultado << endl;
    return 0;
}




