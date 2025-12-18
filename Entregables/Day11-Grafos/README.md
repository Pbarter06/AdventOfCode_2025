# Advent of Code 2025 Day 11

**Equipo AB y Z**

## Participantes
- Finn Alai Perea Oltmann  
- Paula Barona Terol  
- Ainhoa López Gómez  
- Claudia Moreno Martínez

## ¿Por qué se ha elegido este problema?
Este problema ha sido elegido porque presenta un esquema ideal para la aplicación de los grafos. Asimismo, a la hora de aplicar esta técnica de programación, la cual implica una mayor eficiencia a la hora de resolverlo, ayuda a la comprensión de los mismos. 
A diferencia del resto de días, este día específicamente permite la representación de datos no lineales en memoria y el uso de la recursividad en algunas funciones implementadas para la exploración de espacios de búsqueda de espacios.

## ¿Qué técnica o estructura de datos ( o las dos) se emplean?
En este problema específicamente se ha implementado de dos maneras diferentes; con tablas hash y con grafos. Es por ello por lo que en este documento se va a tratar de explicar la implementación con grafos.
A primera vista, se puede observar la implementación de 2 estructuras de datos principales:
  - Clase Nodo
  - Clase Grafo
    
En cuanto a la clase Nodo, ésta representa cada dispositivo como un nodo del grafo. Mientras que en la clase Grafo contiene todos los nodos y, por ende, permite construir el grafo a partir del input obtenido por el problema del Advent Of Code.
Asimismo, otra de las técnicas utilizadas ha sido la recursividad. Dicha técnica cumple con un papel fundamental, ya que explora cada rama completa hasta llegar al final o, la otra opción posible, es que explore hasta que no tenga más ramas por las que avanzar. Tambi.en se emplea la recursión a la hora de explorar un nodno hijo, es en ese caso cuando se emplea `camino.pop_back()` para eliminar el nodo de la ruta actual y poder explorar otras alternativas desde el nodo padre (o raíz).

## ¿Cómo se ha abordado la resolución del problema?
El código presenta una solución al problema de encontrar todos los caminos posibles entre dos nodos en un grafo dirigido. Se trata de un problema que dado un grafo con conexiones direccionales entre nodos, se busca enumerar todas las rutas que conectan un punto de inicio con un punto de destino.
En este caso, el programa busca todos los caminos que van desde el nodo llamado "you" hasta el nodo llamado "out" , procesando la información desde un archivo de entrada que describe la estructura de un grafo.

La solución comienza con un diseño orientado a objetos que modela el grafo mediante dos clases principales. La primera clase, clase Nodo. Esta clase representa cada vértice individual del grafo. Cada nodo contiene su identificador en forma de cadena de texto y mantiene una lista de punteros hacia otros nodos, representadno de esta manera las conexiones salientes o aristas dirigidas desde ese nodo.
La segunda clase, clase Grafo, actúa como contenedor y gestor de toda la estructura. Dicha estructura utiliza un diccionario implementado mediante `unordered_map` que asocia el nombre de cada nodo con su puntero correspondiente. Esta estructura permite un acceso eficiente en tiempo constante promedio para localizar cualquier nodo por su nombre.

Sin embargo, en cuanto a la construcción del grafo se puede observar que se realiza a través de la función `pareInput()`, ésta lee el archivo de texto línea por línea. Cada línea sigue un formato específico donde un nodo origen aparece seguido de dos puntos y luego una lista de nodos destino separados por espacios, es decir, en el caso de `xki: xvs ddo vdf` indica que desde el nodo _xki_ existen aristas dirigidas hacia los nodos _xvs_, _ddo_ y _cdf_. Por eso mismo, el método `unirNodos()` es el encargado de crear esas conexiones. Para cada línea procesada, primero obtiene (o crea el nodo si no existiera) origen, luego recorre la lista de destinos, creando o recuperando cada nodo destino y estableciendo las aristas correspondientes. Este enfoque garantiza que todos los nodos mencionados en el archivo input existan en el grafo, incluso si no tiene conexiones salientes propias.

Para abordar el algoritmo de la búsqueda hay que fijarse en el método reursivo `Camino()`, éste implementa una búsqueda con retroceso (push_back()). Este algoritmo explora de manera sistemática todas las posibles rutas desde el nodo actual hasta el nodo objetivo. De manera que cuando llega al nodn destino, éste guarda una copia del camino actual en la lista de todos los caminos encontrados e incrementa el contador para verificar que hay ya una opción de camino. No obstante, si no se ha llegado al detsino, el algoritmo examina cada una de las opciones (conexiones) salientes que tiene el nodo actual. Para cada conexión, añade el nodo siguiente al camino actual y realiza una llamada recursiva para continuar la exploración desde ese nuevo nodo (pasará a ser el nodo actual). Después de explorar por completo ese camino, elimina el último nodo añadido mediante `pop_back())` , permitiendo así explorar rutas alternativas. Este proecso específicamente permite explorar a fondo todas las posibilidades de caminos sin mantener múltiples copias del mismo en memoria de manera simultánea.

Este programa mantiene dos formas de verificar el número de caminos encontrados. Por un lado, utiliza un contador que incrementa cada vez que se completa un camino válido. Por otro lado, almacena todos los caminos en un vector, cuto tamaño también refleja el número total de rutas encontradas.
Finalmente, el programa imprime por pantalla el número total de caminos encontrados y cuales son esos caminos.

## ¿Qué alternativas se han probado o descartado?
Al enfretarnos al desafío de encontrar caminos con un inicio y un final fuimos conscientes de que existen numerosos enfoques algorítmivos que podrían resolver dicho desafio. Cada uno de los métodos alternativos que al final optamos por no implementar tenían sus ventajas y desventajas, como es obvio. 
Por una parte pensamos en implementar programación dinámica, ya que pensábamos que nos ayudaría a dividir en problema en porciones más simples y más fáciles de resolver, aunque también se planteó la opción de implementar la técnica de tablas hash, la cual sí se implementó y resultó ser también muy eficiente a la hora de resolver el desafío, es por ello por lo que ambas implementaciones, aunque sean diferentes, son soluciones igual de válidas entre ellas, ya que ambas ya sea de una manera u otra consigue resolver el desafío de forma correcta y de forma eficaz.

## Valoración personal
Este problema ha resultado ser un ejercicio complejo para el equipo. Sin embargo, nos ha ayudado a consolidar el uso de los grafos y las estructuras. La mayor dificultad con la que nos hemos encontrado ha sido que el agoritmo funcionara correctamente, para ello hemos necesitado previamente entender que había que añadir los nodos antes de la llamada recursiva. No obstante, al haber implementado la solución con nodos y grafos hace que el código sea más eficiente.
En conclusión, ha sido un día donde hemos aprendido a implementar diferentes soluciones eficientes a un problema complejo como ha sido éste.
