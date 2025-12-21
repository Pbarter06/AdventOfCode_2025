# Advent of Code 2025 Day 11
## **Equipo AB y Z**

### Participantes
- Finn Alai Perea Oltmann  
- Paula Barona Terol  
- Ainhoa López Gómez  
- Claudia Moreno Martínez  

### ¿Por qué se ha elegido este problema?
Se ha elegido este problema ya que, leyendo el enunciado era el más propenso a poder implementar casi todos los métodos. En este caso, lo hemos resuelto mediante diferentes técnicas que se explicarán a continuación

### ¿Qué técnica o estructura de datos (o las dos) se emplean?
En este ejercicio se han usado tablas hash hechas a mano, sin usar las de la STL. La primera tabla hash sirve para guardar cada dispositivo y a dónde se conecta. Además, como la función recursiva necesita recordar resultados y también saber si un nodo está siendo procesado para evitar ciclos, se han tenido que crear dos tablas hash más: una para guardar los resultados ya calculados (memoización) y otra que funciona como un “set” para marcar los nodos que están en proceso. Las tres tablas funcionan igual: tienen un vector fijo, una función hash sencilla y listas enlazadas para manejar colisiones. Con estas estructuras se  puede guardar la información rápido y evitar repetir cálculos o caer en bucles.

### ¿Cómo se ha abordado la resolución del problema?
El programa empieza definiendo un nodo que representa cada dispositivo, con su nombre, sus destinos y un puntero al siguiente por si hay colisiones en la tabla hash. Luego se crea la TablaHash, que es un vector fijo donde cada posición puede tener una lista enlazada. La función hash simplemente suma los caracteres del nombre y hace el resto con el tamaño de la tabla. Con esto se pueden insertar dispositivos y buscarlos recorriendo la lista que toque.

Como hace falta evitar repetir cálculos y también detectar ciclos, se han creado dos tablas hash más, también hechas a mano:

TablaMemo, que guarda cuántos caminos tiene cada nodo ya calculado.

TablaSet, que marca qué nodos están siendo procesados para detectar bucles.

Las dos funcionan igual que la tabla principal: vector fijo, función hash sencilla y listas enlazadas.

La función importante es contarCaminos, que es recursiva. Si el nodo es “out”, ya hay un camino. Si el resultado ya está guardado en memo, se devuelve. Si el nodo está en enProceso, significa que hay un ciclo y ese camino no vale. Si el nodo existe, se recorren sus destinos y se van sumando los caminos de cada uno. Al final se guarda el resultado en memo.

En el main se crea la tabla hash, se leen las líneas de entrada, se limpian los espacios, se separan los destinos y se insertan todos los dispositivos. Cuando ya está todo cargado, se llama a contarCaminos empezando desde “you” y se muestra el número total de caminos hasta “out”.

En resumen, el programa construye una tabla hash para representar la red y usa dos tablas hash adicionales para hacer memoización y detectar ciclos sin usar estructuras de la STL.

### ¿Qué alternativas se han probado o descartado?
Para resolver este ejercicio hemos probado e implementado las Tablas Hash y Grafos. Hemos descartado hacerlo con DyV ya que los caminos no se pueden separarsin tener que recalcular muchas conexiones, el código tendría que repetir algunos cálculos haciendo el algoritmo más lento.

### Valoración personal
Este problema nos ha ayudado a comprender mejor el funcionamiento de las Tablas Hash.

