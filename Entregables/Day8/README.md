# Advent of Code 2025 Day 8

**Equipo AB y Z**

## Participantes
- Finn Alai Perea Oltmann  
- Paula Barona Terol  
- Ainhoa López Gómez  
- Claudia Moreno Martínez

## ¿Por qué se ha elegido este problema?
Este problema ha sido elegido porque combina la estructura de agrupación con la ordenación de cajas. 

## ¿Qué técnica o estructura de datos (o las dos) se emplean?
La estructura principal que se ha implementado en el código de este día es DSU (Disjoint Set Union). Esta estructura permite que en el problema se agrupen elementos en componentes que estén conectados entre sí. De esta manera, permite que se eviten ciclos a la hora de ejecutar el código. Asimismo, se utiliza un vector para almacenar dichas distancias entre los pares de cajas para más tarde ordenarse entre los pares más cercanos.

## ¿Cómo se ha abordado la resolución del problema?
Este código aborda un problema de agrupamiento de puntos a través de la identificación de componentes conectados que están próximos. 
El prolema busca identificar un conjunto de elementos que están relacionados entre sí mediante un criterio de proxmidad. En este caso, el criterio de prooximidad es el siguiente; la distancia entre dos cajas conectadas mediante una hilera de luces debe ser la más cercana para que la electricidad pueda circular por ellas.

El núcleo de la solución propuesta se basa en una estructura de datos conocida como DSU (Disjoint Set Union) o también conocida como Union-Find. Esta estructura de datos permite gestionar de manera eficiente conjuntos disjuntos de elementos y permite realizar operaciones de unión y de búsqueda, en este caso de cajas, de una manera óptima.
La estructura utilizada mantiene dos componentes principales. En primer lugar,  DSU trabaja con el vector `padre`que 


-----------------------------------------------------------------------------------------------------------
En primer lugar, se leen las coordenadas de las cajas desde el fichero obtenido por la página web de Advent of Code ('input.txt').
A continuación, se generan todos los pares posibles de las cajas y se calcula la distancia. Para así, más tarde ordenar los pares por distancias de menor a mayor (crecientes).
De igual manera, se utiliza la estructura DSU para unir los 1000 pares más cercanos, siempre que pertenezcana  componentes diferentes, como indica el problema, formando así componentes nuevos.
Luego, se cuenta el tamaño de cada componente y se seleccionan los tres más grandes. Finalmente, se calcula el producto de esos tres tamaños como resultado final y se imprime por pantalla.
Sin embargo, en la segunda parte del día 8, una vez que todas las cajas están conectadas, se calcula el producto de las coordenadas X de esa última conexión útil para a continuación imprimir el resultado.

## ¿Qué alternativas se han probado o descartado?
Incialmente se planteó recorrer todos los pares de forma bruta. Luego, se consideró recorrer también todos los pares y unirlos si la distancia era menor que una variable fija que implementaríiamos nosotros manualmente. Sin embargo, eso no garantizaba que se seleccionaran los pares correctos por lo que el margen de error aumentaba a un porcentaje muy alto.

## Valoración personal
Este porblema nos ha ayudado a consolidar el uso de estrcuturas y recursividad en diferentes contextos. Asimismo, ha reforzado de igual manera el manejo de vectores, ordenación y grafos. 
Dicho porblema nos ha parecido significativo ya que requiere la aplicación de diferentes técnicas de manera eficiente.
