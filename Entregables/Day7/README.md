# Advent of Code 2025 Day 7

**Equipo AB y Z**

## Participantes
- Finn Alai Perea Oltmann  
- Paula Barona Terol  
- Ainhoa López Gómez  
- Claudia Moreno Martínez

### Justificación de la elección del Problema 
Hemos elegido este problema porque presenta características ideales para aplicar las técnicas de DFS y Programación Dinámica:

- **Estructura de grafo implícito**: La cuadrícula representa un grafo donde cada celda es un nodo y los movimientos hacia abajo (o en diagonal tras un split) son las aristas. Esto hace que DFS sea una elección natural para explorar todos los caminos posibles.
- **Caminos que convergen**: Cuando múltiples caminos llegan a la misma celda desde distintas direcciones, sin memoización contaríamos los mismos splits varias veces. La PD evita este sobreconteo marcando las celdas ya visitadas.
- **Eficiencia**: Sin memoización, la complejidad sería exponencial (cada split duplica caminos). Con PD, cada celda se procesa una sola vez, reduciendo la complejidad.

### Técnicas o estructuras de datos empleadas
En este día hemos implementado las siguientes técnicas:

- **DFS (Depth-First Search)**: Búsqueda en profundidad que explora cada rama hasta el fondo antes de retroceder. Se implementa mediante recursión en la función `explore()`, donde cada llamada recursiva representa seguir un rayo hacia abajo o en diagonal.

- **Programación Dinámica (memoización)**: Se utiliza una tabla `dp[r][c]` que controla si una celda ya ha sido procesada. La memoización funciona de la siguiente manera:
  - Si `dp[r][c] >= 0`, significa que esta celda ya fue visitada y sus splits ya fueron contados. Se devuelve `0` para no contarlos de nuevo.
  - Si `dp[r][c] == -1`, significa que aún no se ha visitado, por lo que se calcula el resultado, se guarda `0` en la tabla (indicando "ya procesado") y se devuelve el número de splits encontrados.
  
  Este esquema sigue el patrón clásico de memoización donde la función **consulta primero la tabla** antes de calcular, similar al ejemplo de los números de Stirling donde `M[n,k]` se consulta al inicio de la función.

### Cómo se ha abordado la resolución del problema
La solución modela la cuadrícula como un grafo implícito donde el camino se propaga hacia abajo, dividiéndose en dos al encontrar un separador (`^`).

**Estructuras de datos principales:**
- `grid`: Vector de strings que almacena el mapa del manifold.
- `dp`: Matriz de enteros para memoización. Cada `dp[r][c]` indica si la celda ya fue procesada: `-1` significa "no visitada" y `0` significa "ya visitada".

**Función `explore(r, c)` - DFS recursivo con memoización:**

La función devuelve el número de splits **nuevos** encontrados desde la celda `(r, c)`:

1. **Caso base (línea 17)**: Si la posición está fuera de límites, devuelve 0 (no hay splits fuera del grid).

2. **Consulta de memoización (líneas 20-22)**: Si `dp[r][c] >= 0`, la celda ya fue visitada y sus splits ya fueron contados. Se devuelve `0` para evitar contarlos de nuevo. Este es el patrón clásico de memoización:
   ```cpp
   if (dp[r][c] >= 0) return dp[r][c];
   ```

3. **Cálculo del resultado (líneas 24-31)**:
   - Si encontramos un separador (`^`): `resultado = 1 + explore(izquierda) + explore(derecha)`
   - Si es espacio vacío: `resultado = explore(abajo)`

4. **Guardado en tabla de memoización (líneas 34-36)**: Antes de devolver, se marca la celda como visitada guardando `0` en `dp[r][c]`:
   ```cpp
   dp[r][c] = 0;
   return resultado;
   ```

Este esquema es análogo al de los números de Stirling donde primero se consulta `M[n,k]` y se guarda el resultado antes de devolverlo. La diferencia es que aquí guardamos `0` porque queremos indicar "ya procesado" y evitar contar los mismos splits múltiples veces.

**Flujo en `main()`:**
- Lee el grid y localiza la posición inicial `S`.
- Inicializa la tabla `dp` con `-1` en todas las celdas (indica "no visitada").
- Inicia el DFS desde la posición de `S` llamando a `explore(startR, startC)`.
- El valor devuelto por `explore()` es el total de splits, que se imprime directamente.

### Alternativas que se han probado y descartado o que se podrían plantear para mejorar la resolución

**Evolución de la solución:**

Partimos de una versión inicial (`Day7.vs2.cpp`) que implementa **DFS iterativo con pila explícita**:
- Usa `stack<pair<int,int>>` en lugar de recursión.
- El bucle `while (!pila.empty())` extrae celdas y las procesa.
- Los vecinos se añaden a la pila con `pila.push()` en lugar de llamadas recursivas.

Esta versión es funcionalmente equivalente, pero hemos decidido evolucionar hacia la versión recursiva (`Day7.cpp`) porque:
- El código es más legible y compacto.
- La estructura recursiva refleja mejor la naturaleza del problema (un rayo que se divide en dos).
- Mejora la eficiencia. 

**Alternativas descartadas:**
- **Fuerza bruta sin memoización**: Explorar todos los caminos sin marcar visitados llevaría a complejidad exponencial, ya que cada split duplica el trabajo. Descartado por ineficiencia.
- **BFS (Breadth-First Search)**: Aunque válido, BFS explora por niveles y requiere una cola. Para este problema donde solo necesitamos contar splits (no encontrar el camino más corto), DFS es más natural y eficiente en memoria.


### Valoración personal sobre qué se ha aprendido y porqué ha sido significativo
A pesar de que ya éramos más familiares con la PD, hemos asentado la estructura y el procedimiento a seguir para pasar de una solución iterativa (DFS con pila), a recursiva (DFS con llamadas), y finalmente añadir memoización para convertirla en una solución dinámica eficiente. Este proceso nos ha ayudado a entender cómo estas técnicas se complementan y cuándo aplicar cada una. 
