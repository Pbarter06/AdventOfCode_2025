# Advent of Code 2025 Day 11

**Equipo AB y Z**

## Participantes
- Finn Alai Perea Oltmann  
- Paula Barona Terol  
- Ainhoa López Gómez  
- Claudia Moreno Martínez

## ¿Por qué se ha elegido este problema?
Se ha elegido este problema porque permite modelar un sistema de dispositivos conectados como una estructura de datos donde es fundamental acceder rápidamente a cada nodo por su nombre. A diferencia de otros problemas del Advent Of Code, éste no solo busca encontrar el camino más corto (optimización), sino que exige encontrar todos los caminos posibles entre dos puntos ("_you_","_out_"). Esto añade una capa de complejidad significativa, ya que se necesita gestionar tanto la memoización de resultados como la detección de ciclos para evitar bucles infinitos.

A diferencia del resto de días, este día específicamente permite la implementación de tablas hash hechas a mano sin usar la STL, lo que demuestra la comprensión profunda del funcionamiento interno de estas estructuras de datos.

## ¿Qué técnica o estructura de datos (o las dos) se emplean?
Para resolver este problema se ha optado por una implementación basada en **tablas hash manuales** con manejo de colisiones mediante listas enlazadas.

Sin embargo, este problema específicamente se ha implementado de dos maneras diferentes; con tablas hash y con grafos. Es por ello por lo que en este documento se va a tratar de explicar la implementación con tablas hash.

A primera vista, se puede observar la implementación de 3 estructuras de datos principales:
  - Clase TablaHash (para almacenar los dispositivos y sus conexiones)
  - Clase TablaMemo (para la memoización de resultados)
  - Clase TablaSet (para detectar ciclos durante la recursión)

En cuanto a la **estructura Nodo**, ésta almacena la información del dispositivo (`string clave`), sus destinos (`vector<string> destinos`) y un puntero al siguiente nodo para manejar colisiones (`Nodo* siguiente`). Dicho esto, se podría concluir que la estructura Nodo permite representar cada dispositivo como un elemento de la tabla hash.

Antes de avanzar, cabe aclarar el uso de punteros (`Nodo*`), éstos se emplean para crear listas enlazadas en cada posición de la tabla. Esto es crucial porque permite manejar colisiones de forma dinámica sin necesidad de conocer previamente cuántos elementos colisionarán en cada posición. Además, evita la copia innecesaria de objetos completos al insertar o buscar elementos.

Una vez implementada la estructura Nodo es vital la implementación de las tres clases de tabla hash, ya que éstas son las estructuras principales para la resolución del problema. Cada tabla utiliza la misma función hash basada en la suma de caracteres ASCII:

- `TablaHash`: almacena los dispositivos y sus conexiones. Permite insertar y buscar dispositivos en tiempo promedio O(1).
- `TablaMemo`: implementa la técnica de memoización, guardando los resultados ya calculados para evitar recalcular caminos.
- `TablaSet`: funciona como un conjunto para marcar los nodos que están siendo procesados, permitiendo detectar ciclos y evitar bucles infinitos.

## ¿Cómo se ha abordado la resolución del problema?
El código presenta una solución al problema de encontrar todos los caminos posibles entre dos nodos en un grafo dirigido. Se trata de un problema que dado un grafo con conexiones direccionales entre nodos, se busca contar todas las rutas que conectan un punto de inicio con un punto de destino.
En este caso, el programa busca todos los caminos que van desde el nodo llamado "**you**" hasta el nodo llamado "**out**", procesando la información desde la entrada estándar que describe la estructura de conexiones entre dispositivos.

La solución comienza con un diseño basado en tablas hash manuales. La primera estructura, **struct Nodo**, representa cada dispositivo. Cada nodo contiene su identificador en forma de cadena de texto (`string clave`), un vector con los nombres de los destinos (`vector<string> destinos`) y un puntero al siguiente nodo para manejar colisiones.
```cpp
struct Nodo {
    string clave;           
    vector<string> destinos;
    Nodo* siguiente;           
    Nodo(string c, vector<string> d) : clave(c), destinos(d), siguiente(nullptr) {}
};
```
El constructor recibe la clave y los destinos, inicializando el puntero siguiente a `nullptr`.

Por otro lado, en cuanto a la **clase TablaHash** se observa cómo contiene un vector de punteros a nodos (`vector<Nodo*> tabla`) y el tamaño de la tabla (`int m`). Esta clase implementa toda la lógica necesaria para inserción y búsqueda de dispositivos.

```cpp
int hashFunc(const string &s) {
    long long suma = 0;
    for (char c : s) suma += (int)c;
    return (int)(suma % m);
}
```
La función hash calcula la posición sumando los valores ASCII de cada carácter y aplicando el módulo con el tamaño de la tabla. Se utiliza un tamaño primo (101) para mejorar la distribución.

```cpp
void insertar(const string &clave, const vector<string> &destinos) {
    int idx = hashFunc(clave);
    Nodo* nuevo = new Nodo(clave, destinos);
    if (tabla[idx] == nullptr) {
        tabla[idx] = nuevo;
    } else {
        Nodo* actual = tabla[idx];
        while (actual->siguiente != nullptr) actual = actual->siguiente;
        actual->siguiente = nuevo;
    }
}
```
El método `insertar()` calcula la posición con la función hash, crea un nuevo nodo y lo añade. Si la posición está vacía, lo coloca directamente; si hay colisión, recorre la lista enlazada hasta el final y lo añade ahí.

```cpp
Nodo* buscar(const string &clave) {
    int idx = hashFunc(clave);
    Nodo* actual = tabla[idx];
    while (actual != nullptr) {
        if (actual->clave == clave) return actual;
        actual = actual->siguiente;
    }
    return nullptr;
}
```
El método `buscar()` localiza un dispositivo por su nombre, recorriendo la lista enlazada en la posición calculada por la función hash.

Para la memoización se implementa la **clase TablaMemo**, que funciona de manera similar pero almacena pares clave-valor donde el valor es el número de caminos calculados:
```cpp
struct NodoMemo {
    string clave;
    long long valor;
    NodoMemo* sig;
    NodoMemo(string c, long long v) : clave(c), valor(v), sig(nullptr) {}
};
```
Esta estructura permite guardar resultados ya calculados y recuperarlos en tiempo constante promedio.

Para la detección de ciclos se implementa la **clase TablaSet**, que funciona como un conjunto:
```cpp
struct NodoSet {
    string clave;
    NodoSet* sig;
    NodoSet(string c) : clave(c), sig(nullptr) {}
};
```
Esta estructura permite marcar qué nodos están siendo procesados actualmente en la pila de recursión.

La función principal es `contarCaminos()`, que implementa un recorrido recursivo con memoización y detección de ciclos:
```cpp
long long contarCaminos(TablaHash &TH, const string &nodo, TablaMemo &memo, TablaSet &enProceso) {
    if (nodo == "out") return 1;        
    if (memo.count(nodo)) return memo.get(nodo); 
    if (enProceso.count(nodo)) return 0;  
    enProceso.insert(nodo);

    long long total = 0;
    Nodo* N = TH.buscar(nodo);
    if (N != nullptr) {
        for (auto &dest : N->destinos) {
            total += contarCaminos(TH, dest, memo, enProceso);
        }
    }
    enProceso.erase(nodo);
    memo.set(nodo, total);
    return total;
}
```
Esta función:
1. Si el nodo es "out", devuelve 1 (camino encontrado)
2. Si el resultado ya está en memo, lo devuelve directamente
3. Si el nodo está en proceso, devuelve 0 (ciclo detectado)
4. Marca el nodo como en proceso
5. Suma recursivamente los caminos de todos los destinos
6. Desmarca el nodo y guarda el resultado en memo

En el `main()` se construye la tabla hash leyendo las líneas de entrada. Cada línea sigue el formato `dispositivo: destino1 destino2 ...`. Se utiliza una función lambda `trim` para limpiar espacios y se procesan los destinos con `istringstream`:
```cpp
auto trim = [](string s){
    size_t i = s.find_first_not_of(" \t");
    size_t j = s.find_last_not_of(" \t");
    if (i==string::npos) return string("");
    return s.substr(i, j-i+1);
};
```

Finalmente, se llama a `contarCaminos()` empezando desde "you" y se muestra el resultado.

## ¿Qué alternativas se han probado o descartado?
Al enfrentarnos al desafío de encontrar caminos con un inicio y un final fuimos conscientes de que existen numerosos enfoques algorítmicos que podrían resolver dicho desafío. Cada uno de los métodos alternativos que al final optamos por no implementar tenían sus ventajas y desventajas como se explican a continuación:
- Divide y Vencerás: una manera de abordar el problema sería dividir el grafo en subgrafos más pequeños. Sin embargo, se descartó esta opción porque los caminos no se pueden separar sin tener que recalcular muchas conexiones, lo que haría el algoritmo más lento y complejo.
- Grafos con lista de adyacencia: esta opción resultó ser equivalente en términos de eficiencia, por lo que se decidió implementarla también y explicar dos tipos de soluciones diferentes para un mismo problema.

## Valoración personal
Este problema ha resultado ser un ejercicio muy completo para el equipo. Nos ha ayudado a consolidar el uso de las tablas hash y entender cómo funcionan internamente sin depender de la STL. La mayor dificultad con la que nos hemos encontrado ha sido implementar correctamente la detección de ciclos usando una tabla hash adicional como conjunto. No obstante, al haber implementado la solución con tablas hash manuales hace que el código demuestre un entendimiento profundo de estas estructuras de datos.
En conclusión, ha sido un día donde hemos aprendido a implementar tablas hash desde cero y a combinarlas con técnicas de memoización y detección de ciclos para resolver un problema complejo de manera eficiente.
