# Taller 1 - Estructuras de Datos

## Descripción
Este proyecto corresponde al **Taller 1** de la asignatura **Estructuras de Datos**.

La aplicación consiste en un **reproductor de música por consola**, desarrollado en **C++**, que trabaja con estructuras de datos implementadas manualmente con **listas enlazadas, nodos y punteros**, sin utilizar contenedores STL. El sistema carga canciones registradas desde un archivo `music_source.txt` y maneja el estado del reproductor mediante `status.cfg`. 

## Integrantes
- Benjamín Ismael Cortés Acuña
- Catalina Isidora Rojas Macaya

## Requisitos
Para compilar y ejecutar este proyecto se requiere:

- `g++`
- `mingw32-make` en Windows

## Estructura del proyecto
```text
Taller1-EDD-rep
│   diagrama_de_clases 
│   README.md
│   Makefile
│   music_source.txt
│   status.cfg
│
├── include
│   ├── Cancion.hpp
│   ├── Node.hpp
│   ├── List.hpp
│   ├── Reproductor.hpp
│   └── FileManager.hpp
│
└── src
    ├── main.cpp
    ├── Cancion.cpp
    ├── Node.cpp
    ├── List.cpp
    ├── Reproductor.cpp
    └── FileManager.cpp
```
### Compilar
Desde la raíz del proyecto, ejecutar:

```bash
mingw32-make
```
Esto generará el ejecutable: 
```bash
reproductor.exe
```
### Ejecutar 
Para ejecutar el programa: 
```bash
mingw32-make run
```
También se puede ejecutar directamente con:
```bash
.\reproductor.exe
```
### Compilación manual alternativa
Si mingw32-make no está disponible en el sistema, se puede compilar manualmente con:
```bash
g++ -std=c++17 -Wall -Wextra -Iinclude src/main.cpp src/Cancion.cpp src/Node.cpp src/List.cpp src/Reproductor.cpp src/FileManager.cpp -o reproductor.exe
```
Luego ejecutar con: 
```bash
.\reproductor.exe
```
### Limpiar archivos generados 
Para eliminar el ejecutable:
```bash
mingw32-make clean
```
### Archivos utilizados por el programa
```md
- `music_source.txt`: registro de canciones disponibles.
- `status.cfg`: archivo de estado del reproductor.
```

## Diagrama de clases

Haz clic aquí para abrir el PDF del diagrama:

[📄 Ver diagrama de clases](diagrama_de_clases/DiagramaClases_Taller1EDD.drawio.pdf)
