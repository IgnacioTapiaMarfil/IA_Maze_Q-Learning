# IA_Maze_Q-Learning

# Proyecto en desarrollo
---

Proyecto de entrenamiento de un algoritmo de IA **Q-Learning / SARSA** para atravesar un laberinto.

## Descripción

Este proyecto utiliza algoritmos de refuerzo como **Q-Learning** y **SARSA** para enseñar a un agente a encontrar la salida de un laberinto, aprendiendo a base de ensayo y error.

## Añadir mapas personalizados

Puedes añadir tus propios laberintos creando un archivo `.txt` en la carpeta `resources` con la siguiente estructura:


1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 3 0 0 0 0 0 0 0 0 0 1 1 1 1 1
1 0 1 1 1 1 1 1 0 1 0 1 0 0 0 1
1 0 0 0 0 0 0 1 0 1 0 1 1 1 0 1
1 0 1 1 1 0 0 1 0 1 0 0 0 0 2 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1

### Leyenda:
- `1` = Pared  
- `0` = Suelo  
- `3` = Posición inicial del agente  
- `2` = Final del laberinto
- 
Despues en el main añade el nombre del archivo en el src.

La Q-Table se guarda en esa misma carpeta.
