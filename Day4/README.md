# Advent of Code 2025 Day 4.2

**Equipo AB y Z**

## Participantes
- Finn Alai Perea Oltmann  
- Paula Barona Terol  
- Ainhoa López Gómez  
- Claudia Moreno Martínez

### Justificación de la elección del Problema 
Hemos elegido este problema porque se trata de una matriz en la que hay que acceder a sus componentes para hacer comprobaciones. Primeramente, pensamos en emplear Tablas Hash pero a medida que fuimos avanzando vimos que no era tan eficiente como esperábamos. 

### Técnicas o estructuras de datos empleadas
- **Versión 1:** Lógica propia de Grafos
- **Versión 2:** Estructuras y clases propias de las Tablas Hash

### Cómo se ha abordado la resolución del problema
- **Versión 1:**
Se ha empleado una cuadrícula representada como un vector<string> para almacenar los caracteres leídos desde la entrada estándar. Cada fila se agrega al vector conforme se recibe, formando así una estructura matricial accesible mediante índices. Junto a esta cuadrícula se utiliza un arreglo fijo de direcciones que define las ocho posiciones adyacentes a cualquier celda, lo cual permite evaluar la vecindad completa, incluyendo diagonales.
El programa ejecuta un proceso iterativo en el que, en cada ciclo, se recorren todas las celdas de la cuadrícula buscando aquellas que contienen el carácter '@'. Para cada una de estas celdas se cuenta cuántos vecinos inmediatos también contienen '@'. Si una celda no cuenta con al menos cuatro vecinos de este tipo, se marca para ser eliminada. Con el fin de evitar interferencias durante el recorrido, se utiliza una lista temporal donde se almacenan las celdas que deben eliminarse, aplicando después la eliminación de forma conjunta, técnica que corresponde a una actualización diferida.
Este procedimiento se repite hasta que ninguna celda resulte eliminable, lo que indica que el sistema ha alcanzado un estado estable. En cada iteración se acumula la cantidad de celdas eliminadas y, finalmente, se imprime el total de eliminaciones realizadas a lo largo de todo el proceso.

- **Versión 2:**
Se ha empleado una tabla hash personalizada para almacenar la cuadrícula  de caracteres, donde cada celda se representa mediante un objeto que contiene una clave única, el carácter asociado y un indicador de eliminación. Esta tabla utiliza direccionamiento abierto con *linear probing* para resolver colisiones, lo que permite realizar de forma eficiente las operaciones de inserción, consulta y marcado de eliminación. Las coordenadas de la cuadrícula se transforman en una clave unidimensional mediante la expresión `key = row * cols + col`, lo que facilita su gestión dentro de la estructura.
Una vez cargada la cuadrícula en la tabla hash, se ha aplicado de manera iterativa un proceso de eliminación basado en la vecindad de cada celda. En cada ciclo se examinan las posiciones que contienen '@' y se cuentan sus ocho vecinos inmediatos; aquellas que presentan menos de cuatro vecinos del mismo tipo se marcan para ser eliminadas. La eliminación se ejecuta de forma conjunta tras la evaluación completa de la cuadrícula para evitar inconsistencias entre las decisiones tomadas en la misma iteración. Este proceso se repite hasta que no queden celdas eliminables, acumulando el número total de eliminaciones efectuadas.
Finalmente, se ha impreso el total de símbolos '@' eliminados, reflejando así el resultado del sistema una vez alcanzado su estado estable conforme a las reglas de vecindad definidas.


### Alternativas que se han probado y descartado o que se podrían plantear para mejorar la resolución
Inicialmente hemos penaso en la solución de la versión2 del problema (Day4.2.vs2.cpp), pero la principal solución es la versión1 (Day4.2.cpp) ya que es mucho más ágil. Hemos observado que la versión 2 funciona muy bien para entradas pequeñas como **p**, pero cuando recibe entradas superiores como **input4** se queda procesando mucho rato. 

### Valoración personal sobre qué se ha aprendido y porqué ha sido significativo
A pesar de que nuestra propuesta inicial no haya conseguido ser tan eficiente como se esperaba, hemos aprendido la lógica de las Tablas Hash y asentado su implementación. 
