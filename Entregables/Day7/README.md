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

- **Programación Dinámica (memorización)**: Se utiliza una tabla booleana `dp[r][c]` que almacena si una celda ya ha sido visitada. Esto evita procesar la misma celda múltiples veces cuando varios rayos convergen en el mismo punto, garantizando que cada split se cuente exactamente una vez.

### Cómo se ha abordado la resolución del problema
La solución modela la cuadrícula como un grafo implícito donde el camino se propaga hacia abajo, dividiéndose en dos al encontrar un separador (`^`).

**Estructuras de datos principales:**
- `grid`: Vector de strings que almacena el mapa del manifold.
- `dp`: Matriz booleana de memoización que marca celdas visitadas.
- `splits`: Contador global de divisiones encontradas.

**Función `explore(r, c)` - DFS recursivo con memoización:**

1. **Caso base (líneas 17-18)**: Si la posición está fuera de límites o la celda ya fue visitada (`dp[r][c] == true`), la recursión termina. Aquí se aplica la **memoización**: consultamos la tabla `dp` para evitar reprocesar celdas.

2. **Marcado de visitado**: Se marca `dp[r][c] = true`. Esta es la **actualización de la tabla de PD** que garantiza que cada celda se procese una sola vez.

3. **Lógica de split**: Si encontramos un separador (`^`):
   - Incrementamos el contador `splits`.
   - **DFS**: Realizamos dos llamadas recursivas (`explore(r+1, c-1)` y `explore(r+1, c+1)`) que exploran las ramas izquierda y derecha en profundidad.

4. **Paso normal**: Si es espacio vacío, **DFS** continúa hacia abajo con `explore(r+1, c)`.

5. **Backtracking implícito**: Al terminar las llamadas recursivas, el DFS retrocede automáticamente para explorar otras ramas pendientes.

**Flujo en `main()`:**
- Lee el grid y localiza la posición inicial `S`.
- Inicializa la tabla `dp` con `false` en todas las celdas.
- Inicia el DFS desde la posición de `S` llamando a `explore(startR, startC)`.
- Imprime el total de splits encontrados.

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
