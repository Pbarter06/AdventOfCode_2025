
# Advent of Code 2025 Day 5

**Equipo AB y Z**

## Participantes
- Finn Alai Perea Oltmann  
- Paula Barona Terol  
- Ainhoa López Gómez  
- Claudia Moreno Martínez

### Justificación de la elección del Problema 
Hemos elegido este problema porque se trata de la búsqueda de un dato dentro de intervalos que además hay que modificar. Por esto, hemos deducido que un Binary Search sería una buena forma de plantear la solución. 

### Técnicas o estructuras de datos empleadas
Se han empleado las tecnicas propias de Búsqueda Binaria y estructura de Árbol para conseguir una estrategia BST (Binary Search Tree). 

### Cómo se ha abordado la resolución del problema
La solución planteada utiliza la estructura de Árbol Binario de Búsqueda (BST) como un método para acelerar la verificación de si un identificador disponible se encuentra dentro de un rango de IDs frescos. La solución se centra en la eficiencia de la búsqueda. El código implementa una clase RangeBST que trata cada rango (start, end) como un nodo, ordenándolos estrictamente por el valor de start.
La función insert construye el árbol siguiendo la regla estándar del BST: si el valor start del nuevo rango es menor que el valor del nodo actual, se inserta a la izquierda; si es mayor, se inserta a la derecha. La lógica crítica está en la función searchID, cuyo propósito es determinar si un id está contenido en cualquier rango del árbol. Si un ID no cae en el rango del nodo actual, el algoritmo debe tomar decisiones para el recorrido: si el id es menor que el start del nodo, solo necesita buscar en la rama izquierda. Sin embargo, si el id es mayor o igual al start del nodo, la búsqueda debe propagarse a la rama derecha (por si hay rangos que comienzan más tarde) y también a la rama izquierda (porque los rangos de la izquierda podrían tener un end que todavía cubre el id actual).

### Alternativas que se han probado y descartado o que se podrían plantear para mejorar la resolución
Hemos implementado también una segunda versión más sencilla a nivel de código que también es funcional. Esta versión no utiliza estructura de árbol por lo que no es tan eficiente. 

### Valoración personal sobre qué se ha aprendido y porqué ha sido significativo
Hemos aprendido la estructura correcta de los árboles y cómo implementarlos para mejorar la eficiencia y el orden del código.
