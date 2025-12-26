
# Advent of Code 2025 Day 5

**Equipo AB y Z**

## Participantes
- Finn Alai Perea Oltmann  
- Paula Barona Terol  
- Ainhoa López Gómez  
- Claudia Moreno Martínez

### Justificación de la elección del Problema 
Hemos elegido este problema porque presenta características ideales para aplicar estructuras de datos eficientes:

- **Búsqueda en rangos**: Dado un conjunto de rangos de IDs frescos y una lista de IDs a verificar, necesitamos determinar rápidamente si cada ID pertenece a algún rango. Esto hace que un BST sea una elección natural.
- **Rangos solapados**: Los rangos pueden superponerse (ej: 10-14 y 12-18), lo que requiere una estrategia de búsqueda que explore múltiples ramas del árbol.
- **Eficiencia**: Con miles de rangos y miles de IDs a verificar, una búsqueda lineal sería O(n×m). El BST reduce esto a O(m×log n) en promedio.

### Técnicas o estructuras de datos empleadas

- **Árbol Binario de Búsqueda (BST)**: Estructura de datos donde cada nodo contiene un rango `[start, end]`. Los nodos se ordenan por `start`, permitiendo búsquedas eficientes.
- **Búsqueda recursiva**: La función `searchID()` recorre el árbol buscando si un ID cae dentro de algún rango, explorando ambas ramas cuando es necesario por los rangos solapados.


### Cómo se ha abordado la resolución del problema

**Estructuras de datos principales:**
- `range`: Estructura con `start` y `end` que representa un intervalo de IDs frescos.
- `BSTNode`: Nodo del árbol con un rango y punteros a hijos izquierdo y derecho.
- `RangeBST`: Clase que encapsula el árbol con métodos de inserción y búsqueda.

**Clase `RangeBST` - Implementación del BST:**

1. **`insert(node, r)`**: Inserta un rango en el árbol recursivamente.
   - Si el nodo es `nullptr`, crea un nuevo nodo con el rango.
   - Si `r.start < node->data.start`, inserta en el subárbol izquierdo.
   - Si no, inserta en el subárbol derecho.
   - **BST**: Mantiene la propiedad de ordenación por `start`.

2. **`searchID(node, id)`**: Busca si un ID está en algún rango.
   - **Caso base**: Si `node == nullptr`, retorna `false`.
   - **Verificación**: Si `start <= id <= end`, el ID está en el rango actual → retorna `true`.
   - **Poda izquierda**: Si `id < start`, solo busca en el subárbol izquierdo (optimización).
   - **Búsqueda completa**: Si `id >= start`, busca en ambos subárboles porque rangos de la izquierda podrían tener un `end` que cubra el ID (rangos solapados).

3. **`deleteTree(node)`**: Libera memoria recursivamente (recorrido post-orden).

**Función `solve()`:**
- Crea un BST e inserta todos los rangos.
- Para cada ID, verifica si está contenido en algún rango usando `bst.contains(id)`.
- Cuenta y retorna el total de IDs frescos.

**Flujo en `main()`:**
- Lee rangos hasta encontrar línea vacía (formato `inicio-fin`).
- Lee los IDs a verificar.
- Llama a `solve()` e imprime el resultado.

### Alternativas que se han probado y descartado o que se podrían plantear para mejorar la resolución

**Evolución de la solución:**

Partimos de una versión inicial (`Day5.vs2.cpp` fuera del directorio Entregables) que utiliza **merge de intervalos + búsqueda binaria**:

1. **Merge de intervalos**: Ordena los rangos por `start` y los fusiona si se solapan (`current.start <= last.end`). Esto convierte rangos solapados en rangos disjuntos.
2. **Búsqueda binaria**: Sobre los rangos fusionados, busca en O(log n) si un ID pertenece a alguno.

Decidimos evolucionar hacia la versión con BST (`Day5.cpp`) porque:
- Demuestra conocimiento de estructuras de árboles.
- Es más flexible para operaciones dinámicas (insertar/eliminar rangos).
- La búsqueda en rangos solapados es más natural con recursión en árbol.

**Alternativas descartadas:**
- **Búsqueda lineal**: Verificar cada ID contra todos los rangos sería O(n×m), ineficiente para inputs grandes.
- **Hash set de todos los IDs frescos**: Expandir cada rango a IDs individuales consumiría demasiada memoria para rangos grandes.

**Posibles mejoras no implementadas:**
- **Árbol AVL o Red-Black**: Para garantizar O(log n) en peor caso (el BST simple puede degradarse a O(n) si los rangos están ordenados).
- **Interval Tree**: Estructura especializada para búsqueda en intervalos que optimiza la búsqueda en rangos solapados.

### Valoración personal sobre qué se ha aprendido y porqué ha sido significativo
Hemos aprendido la estructura correcta de los árboles binarios de búsqueda y cómo implementarlos desde cero para resolver problemas de búsqueda en rangos. También hemos comprendido la técnica de merge de intervalos, muy útil para problemas donde los rangos pueden solaparse. La comparación entre ambas soluciones nos ha ayudado a entender cuándo usar cada enfoque según las características del problema.
