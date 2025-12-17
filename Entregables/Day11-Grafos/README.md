# Advent of Code 2025 Day 11

**Equipo AB y Z**

## Participantes
- Finn Alai Perea Oltmann  
- Paula Barona Terol  
- Ainhoa López Gómez  
- Claudia Moreno Martínez

## ¿Por qué se ha elegido este problema?
Este problema ha sido elegido porque presenta un esquema ideal para la aplicación de los grafos. Asimismo, a la hora de aplicar esta técnica de programación, la cual implica una mayor eficiencia a la hora de resolverlo, ayuda a la comprensión de los mismos. 
A diferencia del resto de días, este día específicamente permite la representación de datos no lineales en memoria y el uso de la recursividad en algunas funciones implementadas para la exploración de espacios de búsqueda de espacios.

## ¿Qué técnica o estructura de datos ( o las dos) se emplean?
En este problema específicamente se ha implementado de dos maneras diferentes; con tablas hash y con grafos. Es por ello por lo que en este documento se va a tratar de explicar la implementación con grafos.
A primera vista, se puede observar la implementación de 2 estructuras de datos principales:
  - Clase Nodo
  - Clase Grafo
En cuanto a la clase Nodo, ésta representa cada dispositivo como un nodo del grafo. Mientras que en la clase Grafo contiene todos los nodos y, por ende, permite construir el grafo a partir del input obtenido por el problema del Advent Of Code.
Asimismo, otra de las técnicas utilizadas ha sido la recursividad. Dicha técnica cumple con un papel fundamental, ya que explora cada rama completa hasta llegar al final o, la otra opción posible, es que explore hasta que no tenga más ramas por las que avanzar. Tambi.en se emplea la recursión a la hora de explorar un nodno hijo, es en ese caso cuando se emplea camino.pop_back() para eliminar el nodo de la ruta actual y poder explorar otras alternativas desde el nodo padre (o raíz).

## ¿Cómo se ha abordado la resolución del problema?
En kmdijd

## ¿Qué alternativas se han probado o descartado?
Inicialmente...

## Valoración personal
Este problema ha resultado ser un ejercicio complejo para el equipo. Sin embargo, nos ha ayudado a consolidar el uso de los grafos y las estructuras. La mayor dificultad con la que nos hemos encontrado ha sido que el agoritmo funcionara correctamente, para ello hemos necesitado previamente entender que había que añadir los nodos antes de la llamada recursiva. No obstante, al haber implementado la solución con nodos y grafos hace que el código sea más eficiente.
En conclusión, ha sido un día donde hemos aprendido a implementar difreentes soluciones eficientes a un problema complejo como ha sido éste.
