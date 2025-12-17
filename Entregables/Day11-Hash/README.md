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
En este apartado se emplean Tablas Hash que sirve para guardar cada dispositivo.
Además se han implementado "unordened_map" y "unordened_set" para guardar resultados calculados y no repetirlos y para evitar bucles infinitos.

### ¿Cómo se ha abordado la resolución del problema?
El programa empieza definiendo la estructura de un nodo, que guarda el nombre del dispositivo, sus destinos y un puntero al siguiente nodo en caso de colisión.
Luego se implementa la clase de la tabla hash, que tiene un vector fijo de nodos y una función hash que convierte cada palabra en un número sumando sus letras y tomando el resto con el tamaño de la tabla. Con esto se pueden insertar dispositivos y sus conexiones, y si hay colisiones se manejan con listas enlazadas. También se puede buscar un dispositivo recorriendo la lista en la posición que le corresponde.
Después está la función recursiva `contarCaminos`, que sirve para contar cuántos caminos hay desde un nodo hasta “out”. Si el nodo actual es “out” ya tenemos un camino válido, si ya se calculó antes se devuelve el resultado guardado, si el nodo está en proceso significa que hay un ciclo y no se cuenta, y si existe en la tabla se recorren sus destinos y se suman los caminos de cada uno. Al final se guarda el resultado en `memo` para no repetir cálculos.
En la función principal se crea la tabla hash con tamaño fijo, se leen las líneas de entrada con el formato dispositivo: destinos, se limpian los espacios y se separan los destinos en un vector, se insertan los dispositivos en la tabla hash y finalmente se llama a `contarCaminos` desde “you” hasta “out” para calcular el número total de caminos y mostrarlo por pantalla.
En resumen, el código construye una tabla hash para guardar dispositivos y sus conexiones y luego usa una función recursiva con memoización y control de ciclos para contar todos los caminos posibles.

### ¿Qué alternativas se han probado o descartado?
Para resolver este ejercicio hemos probado e implementado las Tablas Hash y Grafos. Hemos descartado hacerlo con DyV ya que los caminos no se pueden separarsin tener que recalcular muchas conexiones, el código tendría que repetir algunos cálculos haciendo el algoritmo más lento.

### Valoración personal
Este problema nos ha ayudado a comprender mejor el funcionamiento de las Tablas Hash.

