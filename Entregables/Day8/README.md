# Advent of Code 2025 Day 8

**Equipo AB y Z**

## Participantes
- Finn Alai Perea Oltmann  
- Paula Barona Terol  
- Ainhoa López Gómez  
- Claudia Moreno Martínez

## ¿Por qué se ha elegido este problema?
Se ha elegido este problema concretamente porque combina los grafos junto a la ordenación de las cajas.

A diferencia de un problema de grafos como el desafío del día 11, este problema juega con una variable física que el día 11 no tiene en cuenta. Este problema se basa en la distancia entre cajas, es decir, dado un conjunto de puntos en el espacio, se debe determinar cómo agrupar las cajas solamente considerando las distancias más cortas.

Es por este enfoque diferente por lo que nos hemos querido atrever a resolverlo y elegirlo como candidato.

## ¿Qué técnica o estructura de datos (o las dos) se emplean?
Para la resolución de este problema no se ha optado por un enfoque simple, al revés, se busca una solución que implemente una estructura de datos avanzada lo cual supondrá una gran ventaja a la hora de resolverlo.

En la resolución se ha empleado una **estructura de datos de grafo no dirigido** , representada mediante una matriz de adyacencia. 
Cada caja de conexiones se moldea como un `vértice (nodo)` del grafo y cada `enlace` entre dos cajas se representa como un `1` en la matriz, indicando la existencia de una conexión bidireccional entre ambos vértices, es decir, que ese nodo ya ha sido visitado. Esta representación del problema permite comprobar de forma **directa** si dos cajas están conectadas y facilita la construcción progresiva del grafo a medida que se añaden los pares más cercanos.

Una vez construido el grafo, se utiliza la técnica de `DFS` (_Depth First Search_) que permite un recorrido en profundidad para identificar los distintos componentes conexos. Esta técnica permite explorar todos los vértices alcanzables desde un vértice inicial (origen) y acumulando el tamaño del componente correspondiente. DFS es la forma estándar de recorrer un grafo y de determinar qué vértices pertenecen al mismo siguiendo exactamente los procedimientos adecuados.

En conclusión, la solución se basa exclusivamente en una **matriz de adyacencia** como estructura de representación de un grafo y un **recorrido en profundidad** (_DFS_) como técnica de exploración para obtener los tamaños de los componentes.

## ¿Cómo se ha abordado la resolución del problema?
Este código aborda un problema de agrupamiento de puntos a través de la identificación de componentes conectados que están próximos. 
El prolema busca identificar un conjunto de elementos que están relacionados entre sí mediante un criterio de proxmidad. En este caso, el criterio de proximidad es el siguiente; "_la distancia entre dos cajas conectadas mediante una hilera de luces debe ser la más cercana para que la electricidad pueda circular por ellas_".

La resolución se ha basado en moldear la situación descrita anteriormente como un **grafo no dirigido** , donde cada caja de conexiones corresponde a un **vértice** y cada conexión entre dos cajas corresponde a un **enlace (arista)** del grafo. A partir de las coordenadas (_x, y, z_) se calcula la distancia en línea recta entre todas las parejas de cajas y se seleccionan los 1000 pares más cercanos para conectarlos en el grafo. Una vez construidos todos estos enlaces, el grafo queda estructurado en varios componentes conectados, éstos representan las diferentes hileras  de luces  formadas. Para conocer el tamaño de cada hilera, se ha recurrido a una técnica que permite **recorrer en profundidad** (`DFS`), la cual ayuda a la identificación de qué cajas pertenecen a cada componente y, además, determinar su tamaño. Finalmente, se ordenan los tamaños de los componentes y se calcula el producto de los tres mayores, este valor será la solución del día 8 del Advent Of Code.

A partir de esta idea general, el código se organiza en dos partes principales:
- Clase Grafo
- Función main

La clase **Grafo** encapsula la representación y el recorrido de él mismo. Mientras que por otro lado, la función **main** será el encargado de gestionar la lectura de datos, construcción de los pares más cercanos, la creación de las conexiones y el cálculo final del resultado.

```cpp
class Grafo {
public:
    int n;                                 
    vector<vector<int>> adj;                 
    Grafo(int n) : n(n) {
        adj.assign(n, vector<int>(n, 0));    
    }
    ...
};

````
Para representar el conjunto de cajas de conexiones y sus posibles enlaces, se ha implementado la **clase Grafo** basada en una **matriz de adyacencia** .
En primer lugar, el método constructor `Grafo(int n): n(n)` recibe como parámetro el número total de nodos `n` , que en este contexto serían el número de cajas que han sido leídas del fichero _input.txt_ . A partir de este valor, se inicializa la matriz de adyacencia de tamaño `n x n` de enteros a cero. En la matriz cada posición `adj[i][j]` indicará si existe (1) o no existe (0) un enlace entre las cajas (i, j). De este modo, el grafo comienza vacío, sin ninguna conexión y se irá complementando posteriormente a medida que se procesen los pares de cajas más cercanas.

```cpp
    void unir(int a, int b) {
        adj[a][b] = 1;                       
        adj[b][a] = 1;                       
    }
```
La fución `unir()` es la encargada de añadir un enlace entre dos cajas del grafo. Dado que el problema moldea con variables físicas se ha optado por la implementación de un **grafo no dirigido**. Por ello, al añadir una conexión entre los vértices `a` y `b` , se marcan ambas posiciones en la matriz de adyacencia (`adj[a][b]  adj[b][a]`). Cada llamada a esta función corresponde, por tanto a una nueva hilera de luces que une dos cajas de conexiones.

```cpp
    int dfs(int nodo, vector<int>& visitado) {
        visitado[nodo] = 1;                  
        int tam = 1;                      
        for (int i = 0; i < n; i++) {
            if (adj[nodo][i] == 1 && !visitado[i]) {
                tam += dfs(i, visitado);    
            }
        }
        return tam;
    }
```
Una vez construido el grafo, es necesario determinar qué cajas forman parte de cada hilera, es decir, de cada componente conexo. Para ello se utiliza un **recorrido en profundidad (_DFS_)**, técnica estándar de la teoría de grafos.
La función `dfs` recibe como parámetros el índice del nodo inicial (origen) y un vector `visitado`que indica qué nodos han sido explorados previamente. En primer lugar, el nodo actual se marca como visitado y se inicializa el tamaño del componente a 1, ya que como mínimo el propio nodo pertenece al circuito. A continuación, se recorre la fila `adj[nodo]` de la matriz de adyacencia para comprobar qué otros nodos están conectados directamente al nodo actual. Si existe un enlace, es decir, `adj[nodo]==1` y el nodo `i` aún no ha sido visitado, se llama recursivamente a `dfs` sobre dicho nodo. La llamada recursiva devuelve el tamaño del subcomponente alcanzado de ese vecino, que se suma al tamaño acumulado. Cuando no quedan más vecinos por explorar, la función devuelve el tamaño total del componente conexo al que pertenece el nodo inicial.

```cpp
    vector<int> obtenerComponentes() {
        vector<int> visitado(n, 0);       
        vector<int> tamanos;                
        for (int i = 0; i < n; i++) {
            if (!visitado[i]) {             
                int tam = dfs(i, visitado); 
                tamanos.push_back(tam);     
            }
        }
        return tamanos;
    }
```
La función `obtenerComponentes()` coordina la ejecución de `DFS` para descubrir **todos los componentes conexos** del grafo. Para ello, mantiene un vector `visitado` que inicialmente marca todos los nodos como no visitados. Se recorre secuencialmente cada nodo del grafo y, cuando se encuentra uno que todavía no ha sido visitado, se lanza un `dfs` desde él. Este DFS explora todo el componente conexo asociado a ese nodo, marcando todos los vértices alcanzables y devolviendo el tamaño total del circuito. Dicho tamaño se añade al vector `tamanos`. De esta forma, al finalizar el bucle, `tamanos`contiene el tamaño de cada componente conexo, es decir, de cada hilera de luces de cajas conectadas entre sí.

```cpp
int main() {
    ifstream archivo("input.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir el fichero." << endl;
        return 1;
    }
    vector<array<long long,3>> cajas;
    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        replace(linea.begin(), linea.end(), ',', ' ');
        stringstream ss(linea);
        long long x, y, z;
        ss >> x >> y >> z;
        cajas.push_back({x, y, z});
    }
    int n = cajas.size();
```
La función `main()` comienza abriendo el fichero de entrada _input.txt_ obtenido en Advent Of Code. Este fichero de entrada contiene las coordenadas tridimensionales de cada caja de conexiones. Si el fichero no puede abrise se mostrará por pantalla un mensaje de error y el programa finalizará.

A continuación, se declara un vector `cajas` donde se almacenará las coordenadas (`x,y,z`) de cada caja, y se lee el archivo línea a línea. Para facilitar la lectura de las coordenadas, se sustituten las comas por espacios y se utiliza `stringstream` para extraer los tres valores numéricos correspondientes a las coordenadas. Cada trío de coordenadas se guardan en el vector `cajas`. Finalmente, la variable `n` se inicializa con el número total de cajas leídas, que coincidirá con el número de vértices del grafo.

```cpp
    vector<tuple<long long,int,int>> pares;
    pares.reserve((long long)n * (n - 1) / 2);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            long long dx = cajas[i][0] - cajas[j][0];
            long long dy = cajas[i][1] - cajas[j][1];
            long long dz = cajas[i][2] - cajas[j][2];
            long long d2 = dx*dx + dy*dy + dz*dz;
            pares.push_back({d2, i, j});
        }
    }
    sort(pares.begin(), pares.end());
```
Una vez almacenadas las cajas, se genera la lista de todos los pares posibles de cajas, junto con la distancia al cuadrado entre ellas. Para ello se recorre con dos bucles anidados el rango de ínidices `[0, n]` considerando únicamente parejas con `j>i ` para no repetir ni comparar una caja consigo misma. Para cada par de índices (i,j), se calculan las diferencias `dx`, `dy` y `dz` entre las coordenadas de ambas cajas, y se obtiene la distancia al cuadrado.

Cada par se almacena en el vector `pares`. Antes de llenar el vector, se reserva memoria suficiente para albergar todas las combinaciones posibles, lo que mejora la eficiencia al evitar realocaciones repetidas. Una vez generados todos los pares, el vector se ordena de menor a mayor en función de la distancia, de forma que los pares más cercanos quedan al principio, tal como indica el enunciando del día 8 del Advent Of Code (primero conectar las cajas más próximas).

```cpp
    Grafo g(n);
    int limite = min(1000, (int)pares.size());
    for (int k = 0; k < limite; k++) {
        auto [d2, a, b] = pares[k];
        g.unir(a, b);
    }
```
Tras ordenar los pares, se crea un obteo `Grafo g(N)` con `n` vértices y sin enlaces iniciales. A continuación, se determinará cuántos pares deben procesarse, en este caso los **1000 pares más cercanos** , por lo que se toma el mínimo entre 1000 y el número total de pares disponibles.

En bucle, se recorren los `limite` primero elementos del vector `pares`, que corresponden exactamente a los pares de cajas más próximos entre sí. Para cada una de éstas, se extraen los ínidices `a` y `b` de las cajas implicadas y se llama a `g.unir(a,b)` , que añade un enlace no dirigido entre ambos vértices en la matriz de adyacencia. Al finalizar este bucle, el grafo representa completamente todos los hilos de luces generados al conectar los 1000 pares de cajas más cercanos.

```cpp
    vector<int> tamanos = g.obtenerComponentes();
    sort(tamanos.rbegin(), tamanos.rend());
    long long resultado = 1;
    for (int i = 0; i < 3 && i < (int)tamanos.size(); i++) {
        resultado *= tamanos[i];
    }
    cout << resultado << endl;
    return 0;
}
```
Con el grafo ya construido, se llama al método `g.obtenerComponentes()`, que recorre el grafo mediante `DFS` para descubir todos los componentes conexos y devuelve un vector con el tamaño de cada uno de ellos. Cada posición de este vector representa el número de cajas que forman un circuito independiente.

Posteriormente, se ordenan estos tamaños de mayor a menor utilizando `sort` con iteradores inversos. Este orden permite acceder de forma directa a los tamaños de los tres circuitos más grandes, tal como se solicita. El código inicializa una variable `resultado` a 1 y recorre los tres primeros elementos del vector multiplicando sus valores. Finalmente, se muestra el resultado por pantalla y el programa termina.

## ¿Qué alternativas se han probado o descartado?
Incialmente se planteó recorrer todos los pares de forma bruta, pero esa opción se descartó  de forma casi automática, puesto que suponía una eficiencia casi nula. 
Luego, se consideró recorrer también todos los pares y unirlos si la distancia era menor que una variable fija que implementaríiamos nosotros manualmente. Sin embargo, eso no garantizaba que se seleccionaran los pares correctos por lo que el margen de error aumentaba a un porcentaje muy alto.

## Valoración personal
Este porblema nos ha ayudado a consolidar el uso de estructuras y recursividad en diferentes contextos. Asimismo, ha reforzado de igual manera el manejo de vectores, ordenación y grafos. 
Dicho porblema nos ha parecido significativo, ya que requiere la aplicación de diferentes técnicas de manera eficiente.
