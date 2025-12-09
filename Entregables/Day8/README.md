# Advent of Code 2025 Day 8

**Equipo AB y Z**

## Participantes
- Finn Alai Perea Oltmann  
- Paula Barona Terol  
- Ainhoa López Gómez  
- Claudia Moreno Martínez

## ¿Por qué se ha elegido este problema?
Este problema ha sido elegido porque combina la estructura de agrupación con la ordenación de cajas. 

## ¿Qué técnica o etsructura de datos (o las dos) se emplean?
La estructura principal que se ha implementado en el código de este día es DSU (Disjoint Set Union). Esta estructura permite que en el problema se agrupen elementos en componentes que estén conectados entre sí. De esta manera, permite que se eviten ciclos a la hora de ejecutar el código. Asimismo, se utiliza un vector para almacenar dichas distancias entre los pares de cajas para más tarde ordenarse entre los pares más cercanos.

## ¿Cómo se ha abordado la resolución del problema?
En primer lugar, se leen las coordenadas de las cajas desde el fichero obtenido por la página web de Advent of Code ('input.txt').
A continuación, se generan todos los pares posibles de las cajas y se calcula la distancia. Para así, más tarde ordenar los pares por distancias de menos a mayor (crecientes).
De igual manera, se utiliza la etsructura DSU para unir los 1000 pares más cercanos como indica el problema, formando así componentes nuevos.
Luego, se cuenta el tamaño de cada componente y se seleccionan los tres más grande. Y finalmente, se calcula el producto de esos tres tamaños como resultado final y se imprime por pantalla.

## ¿Qué alternativas se han probado o descartado?
Incialmente se planteó recorrer todos los pares de forma bruta. Luego, se consideró recorrer también todos los pares y unirlos si la distancia era menor que una variable fija que implementaríiamos nosotros manualmente. Sin embargo, eso no garantizaba que se seleccionaran los pares correctos por lo que el margen de error aumentaba a un porcentaje muy alto.

## Valoración personal
Este porblema nos ha ayudado a consolidar el uso de estrcuturas y recursividad en diferentes contextos. Asimismo, ha reforzado de igual manera el manejo de vectores, ordenación y grafos. 
Dicho porblema nos ha parecido significativo ya que requiere la aplicación de diferentes técnicas de manera eficiente.
