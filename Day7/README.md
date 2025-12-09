# Advent of Code 2025 Day 7

**Equipo AB y Z**

## Participantes
- Finn Alai Perea Oltmann  
- Paula Barona Terol  
- Ainhoa López Gómez  
- Claudia Moreno Martínez

### Justificación de la elección del Problema 
Hemos elegido este problema porque trata de contar las veces que un camino se divide. Puesto que la división a veces puede coincidir con un camino ya recorrido, hemos pensado que PD podría ser una buena forma de resolver el ejercicio. 

### Técnicas o estructuras de datos empleadas
Se han implementado lógica propia de grafos, a pesar de no utilizarse estructuras como tal, y programación Dinámica. 

### Cómo se ha abordado la resolución del problema
La solución describe un recorrido en una cuadrícula tratada como un grafo implícito, donde se busca un punto de inicio **'S'** y se siguen caminos definidos por los caracteres del grid. El objetivo es contar cuántas veces aparece el carácter **'^'** (representado como *split*), que indica una división del camino. Para evitar procesar múltiples veces la misma celda, se utiliza una matriz booleana **dp**, que actúa como una tabla de visitados y permite aplicar una forma de memorización típica de la programación dinámica.
El programa lee la cuadrícula, identifica la posición inicial y luego invoca la función recursiva **explore**. Esta función implementa un recorrido en profundidad (DFS) con condiciones base que detienen la recursión al salir de los límites o al intentar visitar una celda ya marcada. Cada celda válida se marca como visitada en **dp** para evitar duplicar trabajo.
La lógica principal depende del contenido de la celda:

- Si contiene **'^'**, se incrementa el contador global de splits y se continúa el recorrido por dos direcciones: abajo-izquierda y abajo-derecha.
- Si contiene cualquier otro carácter, el recorrido sigue únicamente hacia abajo.

### Alternativas que se han probado y descartado o que se podrían plantear para mejorar la resolución
Hemos descartado la iteración por fuerza bruta, ya que es muy poco eficiente, especialmente para este problema. Hay otras soluciones que se han pensado, pero no se han implementado, como hacer DFS o BFS para ambas partes del Day7. 

### Valoración personal sobre qué se ha aprendido y porqué ha sido significativo
A pesar de que ya éramos más familiares con la PD, hemos asentado la estructura y el procedimiento a seguir para pasar de una solución iterativa, a recursiva, a dinámica. 
