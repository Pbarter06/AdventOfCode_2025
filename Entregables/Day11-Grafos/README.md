# Advent of Code 2025 Day 11

**Equipo AB y Z**

## Participantes
- Finn Alai Perea Oltmann  
- Paula Barona Terol  
- Ainhoa López Gómez  
- Claudia Moreno Martínez

## ¿Por qué se ha elegido este problema?
Se ha elegido este problema porque permite modelar un sistema como un conjunto de nodos que se encuentran conectados entre sí, esto mismo nos permite resolver problemas complejos de logística. A diferencia de otros problemas del Advent Of Code, éste no solo busca encontrar el camino más corto (optimización), sino que exige encontrar todos los caminos posibles entre dos puntos ("_you_","_out_"). Esto añade una capa de complejidad significativa, obligando a  gestionar el historial de visita, es decir, la memoria del camino y el retroceso (utilizando _backtracking_), lo que convierte este problema en un ideal candidato para la implementación de la técina algorítimica de Grafos.
 
A diferencia del resto de días, este día específicamente permite la representación de datos no lineales en memoria y el uso de la recursividad en algunas funciones implementadas para la exploración de espacios de búsqueda de espacios.

## ¿Qué técnica o estructura de datos ( o las dos) se emplean?
Para resolver este problema no se ha optado por un enfoque simple de fuerza bruta, sino se ha optado más por una implementación orientada a objetos basada en punteros.

Sin embargo, este problema específicamente se ha implementado de dos maneras diferentes; con tablas hash y con grafos. Es por ello por lo que en este documento se va a tratar de explicar la implementación con grafos.

A primera vista, se puede observar la implementación de 2 estructuras de datos principales:
  - Clase Nodo
  - Clase Grafo
    
En cuanto a la **clase Nodo**, ésta almacena la información del vértice ( `string nombre`) y, lo más importante, un  vector de punteros (`vector<Nodo*> siguiente`). Dicho esto, se podría concluir que la clase Nodo permite representar cada dispositivo como un nodo del grafo.
Antes de avanzar, cabe aclarar el uso de punteros (`Nodo*`), éstos se emplean para la vinculación a los nodos. Esto es crucial porque permite que el grafo crezca dinámicamente (`new Nodo`) sin necesidad de conocer el tamaño del grafo previamente. Además, evita la copia innecesaria de objetos completos al pasar datos entre funciones, ya que solamente se pasan las direcciones de memoria.

Una vez implementada la clase Nodo es vital la implementación de la clase Grafos, ya que ésta es la técnica principal para la resolución del problema.  Para ello, se ha implementado una mezcla de la técnica algorítmica DFS (_Depth First Search_) con la técnica de Backtracking. 

- `DFS (Depth First Search)`: se utiliza esta destructura porque se necesita explorar una rama completa del gafo hasta llegar al final (o a una rama sin salida) antes de probar otra ruta, esto es posible gracias a las llamadas recursivas, las cuales emplean un papel fundamental. De igual manera, la recursión también permite que a la hora de explorar un nodo hijo se emplee la técnica de Backtracking (`camino.pop_back()`) para eliminar el nodo de la ruta actual y poder explorar otras alternativas desde el nodo padre.

- `Backtracking`: en la función `Camino()` se utiliza la pila de llamadas al sistema (recursividad) para manetener el estado. En primer lugar, se añade el nodo actual al camino, se hace una llamada recursiva para explorar los vecinos y, por último, una vez se ha llevado a cabo la llamada recursiva y ésta devuelve un valor, se hace `camino.pop_back()`. Esto "limpia" de cierta manera el nodo actual del historial para que otras rutas puedan usar el camino previo sin "contaminación" de la ruta que se acaba de explorar.

En conclusión,  la clase Grafo contiene todos los nodos y, por ende, permite construir el grafo a partir del _input.txt_ obtenido por el problema del Advent Of Code.

## ¿Cómo se ha abordado la resolución del problema?
El código presenta una solución al problema de encontrar todos los caminos posibles entre dos nodos en un grafo dirigido. Se trata de un problema que dado un grafo con conexiones direccionales entre nodos, se busca enumerar todas las rutas que conectan un punto de inicio con un punto de destino.
En este caso, el programa busca todos los caminos que van desde el nodo llamado "**you**" hasta el nodo llamado "**out**" , procesando la información desde un archivo de entrada que describe la estructura de un grafo.

La solución comienza con un diseño orientado a objetos que modela el grafo mediante dos clases principales. La primera clase, **clase Nodo**. Esta clase representa cada vértice individual del grafo. Cada nodo contiene su identificador en forma de cadena de texto (`string nombre`) y mantiene una lista de punteros hacia otros nodos (`vector<Nodo*>siguiente`), representando de esta manera las conexiones salientes o aristas dirigidas desde ese nodo. 
```cpp
Nodo(const string& nombre): nombre(nombre){
}
```
El método constructor recibe el nombre del nodo y lo almacena. Asimismo, la **clase Nodo** también implementa la siguiente función:
```cpp
void nextnodo(Nodo* otro){
  siguiente.push_back(otro);
}
```
Este método implementado en la **clase Nodo** añade un puntero a otro nodo dentro del vector `siguiente`, representando de esa manera una arista dirigida desde el nodo hacia el nodo anterior como parámetro.

Por otro lado, en cuanto a la **clase Grafo** se observa como contiene un atributo (`vector<Nodo*>nodos`) que permitirá almacenar todos los nodos creados. Esta clase implementa toda la lógica necesaria para la contrucción y recorrido del grafo. Asimismo, la clase Nodo va a permitir una gran ventaja, ya que permite un acceso eficiente en tiempo constante promedio para localizar cualquier nodo por su nombre.

```cpp
Nodo *buscarNodo(const string& nombre){
  for(Nodo * n: nodos){
    if(n->nombre==nombre){
      return n;
    }
  }
  return nullptr;
}
```
El primer método que se observa en la **clase Grafo** es `buscarNodo`, este método recibe un nombre y recorre de manera secuencial el vector de nodos buscando un nodo cuyo atributo `nombre`coincida con el que se ha solicitado. Si lo encuentra, es decir, la condición del if es `True` (entra en el if) devolverá el puntero; si no encuentra el atributo `nombre`que coincida, en ese caso devolverá `nullptr`. 
El objetivo de la función es localizar nodos ya existentes evitando así duplicarlos.

```cpp
    Nodo* crearNodo(const string& nombre){
        Nodo* nuevo= new Nodo(nombre);    
        nodos.push_back(nuevo);    
        return nuevo;    
    }
```
Este método recibe un nombre de nodo origen y un vector de nombres destino. Para cada uno de ellos, crea los nodos correspondientes y añade una arista desde el nodo origen hacia cada nodo destino mediante el método `nextnodo`.

```cpp
void Camino(Nodo* nactual, Nodo* final, vector<string>& camino, vector<vector<string>>&todosCaminos, int& contadorCaminos){
        if(nactual==final){
            todosCaminos.push_back(camino);
            contadorCaminos++;
            return;
        }
        for(Nodo* nxt: nactual->siguiente){ 
            camino.push_back(nxt->nombre);
            Camino(nxt, final, camino, todosCaminos, contadorCaminos);
            camino.pop_back();
        }
    }
```
La función `Camino` implementa un recorrido en profundidad (_DFS_). Recibe el nodo actual, el nodo final, el camino recorrido hasta el momento, un vector donde se almacena todos los caminos completos y un contador de caminos pasado por referencia. Si el nodo actual es el nodo final, significa que se ha encontrado un camino completo, por lo que se añade una copia del camino al vector de caminos y se incrementa el contador. Si no se ha llegado al final, la función recorre todas las salidas del nodo actual. Por cada nodo siguiente, añade un nombre al camino, llama recursivamente a `Camino` para seguir explorando y luego, elimina el último elemento del camino para deshacer el paso (técnica _backtracking_).

```cpp
 vector<vector<string>> encontrarTodosCaminos(const string& start, const string& end, int& contadorCaminos){
        vector<vector<string>> todosCaminos;
        vector<string> camino;
        Nodo* startNodo= nodos[start];
        Nodo* endNodo= nodos[end];
        contadorCaminos=0;
        if(!startNodo|| !endNodo){
            return todosCaminos;
        }
        camino.push_back(startNodo->nombre);
        Camino(startNodo, endNodo, camino, todosCaminos, contadorCaminos);
        return todosCaminos;    
    }
```
El método `encontrarTodosCaminos()` es el encargado de iniciar el proceso de búsqueda. Su funcionamiento se basa en crear un vector para almacenar todos los caminos y otro para el camino actual. De esa manera, obtiene los nodos de inicio y fin accediendo directamente al vector `nodos`. A continuación, inicializa el contador de caminos a 0 y, si alguno de los nodos no existe, devuelve un vector vacío. Pero en el caso de que ambos existieran, añade el nombre del nodo inicial al camino y llama a `Camino()`para explorar todas las rutas posibles. Finalmente, este método devuelve el vector con todos los caminos encontrados.


Sin embargo,fuera de la **clase Grafo** se encuentra  la construcción de  éste mismo. Se puede observar que se realiza a través de la función `pareInput()`, ésta lee el archivo de texto línea por línea. Cada línea sigue un formato específico donde un nodo origen aparece seguido de dos puntos y luego una lista de nodos destino separados por espacios, es decir, en el caso de `xki: xvs ddo vdf` indica que desde el nodo _xki_ existen aristas dirigidas hacia los nodos _xvs_, _ddo_ y _cdf_. Por eso mismo, el método `unirNodos()` es el encargado de crear esas conexiones. Para cada línea procesada, primero obtiene (o crea el nodo si no existiera) origen, luego recorre la lista de destinos, creando o recuperando cada nodo destino y estableciendo las aristas correspondientes. Este enfoque garantiza que todos los nodos mencionados en el archivo input existan en el grafo, incluso si no tiene conexiones salientes propias.

Este programa mantiene dos formas de verificar el número de caminos encontrados. Por un lado, utiliza un contador que incrementa cada vez que se completa un camino válido. Por otro lado, almacena todos los caminos en un vector, cuyo tamaño también refleja el número total de rutas encontradas.
Finalmente, el programa imprime por pantalla el número total de caminos encontrados y cuales son esos caminos.

## ¿Qué alternativas se han probado o descartado?
Al enfretarnos al desafío de encontrar caminos con un inicio y un final fuimos conscientes de que existen numerosos enfoques algorítmivos que podrían resolver dicho desafío. Cada uno de los métodos alternativos que al final optamos por no implementar tenían sus ventajas y desventajas como se explican a continuación:
- Matriz de Adyacencia: una manera de abordar el problema era crear una matriz booleana de tamaño `[N][N]` donde `N` sería el número de nodos. Sin embargo, se descartó esta opción por el coste en memoria, ya que si los nodos tienen nombres (`strings`) se tendría que mapear cada string a un entero. Además, otra desventaja es que si se trataba de un grafo con pocos caminos entre muchos nodos la matriz desperdiciaría mucha memoria, mientras que la lista de adyacencia implementada solo usa memoria proporcional a las conexiones que existen entre nodos.
- Algoritmo BFS (_Breadth First Search_): este algoritmo consiste en una búsqueda en anchura usando una cola, el motivo de descarte fue que el equipo no contaba con el conocimiento necesario para implementarlo de manera eficiente y supondría más un problema a una solución eficiente.
- Tabla Hash: esta opción de abordar el problema resultó ser bastante equivalente en cuanto a términos de eficiencia como esta opción de solución, por lo que se decidió por aplicarla también y explicar dos tipos de soluciones diferentes para un mismo problema.
  

## Valoración personal
Este problema ha resultado ser un ejercicio complejo para el equipo. Sin embargo, nos ha ayudado a consolidar el uso de los grafos y las estructuras. La mayor dificultad con la que nos hemos encontrado ha sido que el agoritmo funcionara correctamente, para ello hemos necesitado previamente entender que había que añadir los nodos antes de la llamada recursiva. No obstante, al haber implementado la solución con nodos y grafos hace que el código sea más eficiente.
En conclusión, ha sido un día donde hemos aprendido a implementar diferentes soluciones eficientes a un problema complejo como ha sido éste.
