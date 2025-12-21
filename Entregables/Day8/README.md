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

Así pues, a la hora de revisar el código se puede verificar a simple vista que se ha hecho uso de un tipo de estructura denominada **DSU** (_Disjoint Set Union_/_Union-Find_). Esta estructura se emplea generalmente para gestionar conjuntos de elementos particionados. Consta de:
- `vector<int>padre`: almacena el árbol genealógico de los nodos. Si `padre[i]==1`, entonces ese nodo es la raíz (`root`) de su grupo.
- `vector<int>tam`: mantiene el conteo de cuántos elementos pertenecen a cada conjunto. Es muy importante para optimizar las uniones de las cajas.

En conclusión, esta estructura permite que en el problema se agrupen elementos en componentes que estén conectados entre sí. De esta manera, accede que se eviten ciclos a la hora de ejecutar el código. Y, por ende, se utilizará un vector para almacenar dichas distancias entre los pares de cajas para más tarde ordenarse entre los pares más cercanos.

## ¿Cómo se ha abordado la resolución del problema?
Este código aborda un problema de agrupamiento de puntos a través de la identificación de componentes conectados que están próximos. 
El prolema busca identificar un conjunto de elementos que están relacionados entre sí mediante un criterio de proxmidad. En este caso, el criterio de proximidad es el siguiente; "_la distancia entre dos cajas conectadas mediante una hilera de luces debe ser la más cercana para que la electricidad pueda circular por ellas_".

La primera parte del programa consiste en la definición de la estructura `DSU` (_Disjoint Set Union_), que es una estructuta que como se ha explicado anteriormente gestiona conjuntos disjuntos de forma eficiente. Esta estructura mantiene dos vectores:
  1. `padre`: almacena para cada elemento cuál es su representante dentro del conjunto.
  2. `tam`: guarda el tamaño del conjunto cuya raíz es cada elemento.

```
    DSU(int n){
        padre.resize(n);
        tam.assign(n, 1);
        for(int i = 0; i < n; i++) padre[i] = i;
    }
```
El método constructor de la estructura `DSU` recibe un número `n`y crea incialmente `n` conjuntos independientes. De esa manera, asigna a cada elemento como padre de sí mismo y establece el tamaño de cada conjunto en uno.

```
    int find(int x){
        if(padre[x] == x) return x;
        return padre[x] = find(padre[x]);
    }
```
El método `find()` implementa la operación fundamental de búsqueda del respesentante de un elemento. Si el elemento es su propio padre, es decir, que es la raíz del conjunto (sería equivalente al caso base), se devuelve (`return x`). En cambio, si no se trata del caso base, entonces se llama recursivamnete a `find()` sobre su padre. De la misma manera, el padre del elemento se actualiza para apuntar directamente a la raíz. Esta implementación recursiva reduce a gran escala la profundidad compleja de los árboles internos.

```
    void unir(int a, int b){
        a = find(a);
        b = find(b);
        if(a == b) return;
        if(tam[a] < tam[b]) swap(a, b);
        padre[b] = a;
        tam[a] += tam[b];
    }
```
El método `unir()` permite fusionar los conjuntos que contienen a dos elementos dados. Primero se obtienen las raíces reales de ambos a través de la función `find()`. Si ambas raíces coindicen (`if(a==b)`) significa que pertenecer al mismo conjunto y no es necesario hacer nada. Sin embargo, si son diferentes, se aplica la técnica de unión por tamaño, es decir, el conjunto más pequeño se une al más grande para mantener los árboles lo más planos posibles para evitar mayores dificultades. 
Finalmente, se actualiza el tamaño del conjunto resultante sumando los tamaños de ambos porque se han unido.


Una vez ya se ha definido la estructura DSU, está el programa principal `int main()`.
Una vez llegados a este punto, lo primero que se ejecuta es la instrucción de abrir el fichero _input.txt_ obtenido por la página del Advent Of Code. Si se ha abierto correctamente, se procede a leer las coordenadas de cada caja, para ello ha sido necesario declarar un vector de arrays donde se almacenarán las coordenadas `x`, `y`, `z` de cada caja.

Una vez que ya se han leído todas las lineas del archivo, se calcula el número total de cajas y se prepara un vector donde se almacenarán todos los pares posibles de cajas junto con la distancia al cuadrado entre ellas como se indica a continuación:
```
vector<tuple<long long,int,int>> pares; 
    pares.reserve((long long)n * (n - 1) / 2);
```
Cabe recalcar que para evitar comparaciones redundantes, solo se considerarán pares `(i,j)`con `j>i`. A continuación, para cada par, se calcula la diferencia en cada coordenada y se obtiene la distancia al cuadrado, la cual será almacenada junto con los índices de ambas cajas.

```
sort(pares.begin(), pares.end());
```
Una vez se han generado todos los pares, el vector se ordena de menor a mayor distancia. Esto permitirá procesar primero las cajas más cercanas entre sí, de esa forma se creará una estructura DSU con tantas posiciones como cajas que haya. Por consiguiente, se procederá a unir únicamente los mil pares más cercanos.
```
DSU dsu(n);
```
Después de haberse realizado todas las uniones, el programa recorre todas las cajas y, para cada una, obtiene su raíz mediante la función `find()`.
Los tamaños de los componentes se vuelcan a un vector y se ordenan de mayor a menor. Y finalmente, el programa calcula el producto de los tres componentes más grandes, inicializando el resultado a  uno e iterando sobre los tres primeros tamaños del vector. 
Este último valor será la solución al desafío del día 8 del Advent Of Code.


## ¿Qué alternativas se han probado o descartado?
Incialmente se planteó recorrer todos los pares de forma bruta, pero esa opción se descartó  de forma casi automática, puesto que suponía una eficiencia casi nula. 
Luego, se consideró recorrer también todos los pares y unirlos si la distancia era menor que una variable fija que implementaríiamos nosotros manualmente. Sin embargo, eso no garantizaba que se seleccionaran los pares correctos por lo que el margen de error aumentaba a un porcentaje muy alto.

## Valoración personal
Este porblema nos ha ayudado a consolidar el uso de estructuras y recursividad en diferentes contextos. Asimismo, ha reforzado de igual manera el manejo de vectores, ordenación y grafos. 
Dicho porblema nos ha parecido significativo, ya que requiere la aplicación de diferentes técnicas de manera eficiente.
