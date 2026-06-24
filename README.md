# Reproductor de Música - SoundStructure

## Integrantes del Equipo

* Matías Antonio Collao Valdivia
* Benjamín Ismael Cortés Acuña
* Catalina Isidora Rojas Macaya

## Descripción del Proyecto

Este proyecto consiste en un reproductor de música interactivo por consola desarrollado en C++ para la asignatura de Estructuras de Datos. La aplicación permite gestionar una biblioteca musical local mediante estructuras de datos implementadas manualmente, evitando el uso de contenedores STL para cumplir con los requerimientos del taller.

El sistema permite cargar canciones desde archivos planos, reproducir pistas, avanzar o retroceder dentro de la cola, activar modo aleatorio, controlar estados de repetición y mantener persistencia del estado de reproducción. Además, incorpora funcionalidades de búsqueda, ordenamiento y ranking de canciones y artistas según la cantidad de reproducciones.

## Funcionamiento de la Aplicación

El programa opera mediante una interfaz por consola, utilizando archivos locales para cargar y guardar información relevante del reproductor.

Los principales archivos utilizados son:

```text
music_source.txt   # Fuente principal de canciones
status.cfg         # Estado actual del reproductor
song_ranking.txt   # Registro de reproducciones y ranking
```

El reproductor cuenta con las siguientes funcionalidades principales:

1. **Control de reproducción:** permite iniciar, pausar, avanzar y retroceder canciones dentro de la cola de reproducción.
2. **Modo aleatorio:** permite reproducir canciones en orden aleatorio.
3. **Modo repetición:** permite alternar entre repetición desactivada, repetir una canción o repetir toda la lista.
4. **Gestión de biblioteca musical:** carga canciones desde un archivo externo y las almacena en estructuras propias.
5. **Persistencia de datos:** guarda información del estado actual del reproductor para mantener continuidad entre ejecuciones.
6. **Ranking de canciones:** permite registrar y consultar las canciones más reproducidas.

## Estructuras de Datos Utilizadas

Para implementar el reproductor se utilizaron estructuras de datos desarrolladas manualmente en C++.

### Lista Enlazada Simple (`List`)

La lista enlazada simple se utiliza para gestionar canciones dentro del sistema. Cada nodo almacena una canción y una referencia al siguiente nodo de la lista.

Esta estructura permite representar:

* Biblioteca musical cargada.
* Cola de reproducción actual.
* Historial de canciones reproducidas.
* Recorrido secuencial entre canciones.

### Nodo (`Node`)

La clase `Node` representa cada elemento dentro de la lista enlazada. Su función principal es almacenar un objeto de tipo canción y enlazarlo con el siguiente nodo.

### Canción (`Cancion`)

La clase `Cancion` almacena los datos principales de cada pista musical, tales como:

* Nombre de la canción.
* Artista.
* Duración u otros datos asociados.
* Cantidad de reproducciones, en caso de utilizar ranking.

### Reproductor (`Reproductor`)

La clase `Reproductor` se encarga de controlar la lógica principal de la aplicación. Administra la reproducción de canciones, los cambios de pista, el modo aleatorio, los estados de repetición y la interacción general con el usuario.

### FileManager

La clase `FileManager` se encarga de gestionar la lectura y escritura de archivos. Permite cargar canciones desde `music_source.txt`, guardar configuraciones en `status.cfg` y mantener registros asociados al ranking o estado del reproductor.

## Estructura del Proyecto

La estructura actual del proyecto es la siguiente:

```text
Taller1-EDD-rep
│
├── diagrama_de_clases
├── README.md
├── Makefile
├── music_source.txt
├── status.cfg
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

## Instrucciones de Compilación y Ejecución

El proyecto se compila y ejecuta desde consola. No depende de un IDE específico para su construcción.

El código fuente se encuentra separado en:

```text
include/    # Archivos de cabecera .hpp
src/        # Archivos de implementación .cpp
```

Antes de ejecutar el programa, el archivo `music_source.txt` debe estar ubicado en la raíz del proyecto, al mismo nivel que el `Makefile`.

## Requisitos

Para compilar el proyecto se necesita:

* Compilador `g++` compatible con C++17.
* `make` o `mingw32-make`, según el sistema operativo.

## Compilación con Makefile

Desde una terminal ubicada en la raíz del proyecto, ejecutar:

### Windows con MinGW

```bash
mingw32-make
```

### Linux, Mac o WSL

```bash
make
```

Esto genera el ejecutable:

```text
reproductor.exe
```

## Ejecución

### Windows

```bash
.\reproductor.exe
```

O también:

```bash
mingw32-make run
```

### Linux, Mac o WSL

```bash
./reproductor.exe
```

O también:

```bash
make run
```

## Compilación manual sin Makefile

Si no se desea utilizar `make`, el proyecto también puede compilarse directamente con `g++` desde la raíz del proyecto:

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude src/main.cpp src/Cancion.cpp src/Node.cpp src/List.cpp src/Reproductor.cpp src/FileManager.cpp -o reproductor.exe
```

Luego se ejecuta con:

### Windows

```bash
.\reproductor.exe
```

### Linux, Mac o WSL

```bash
./reproductor.exe
```

## Limpieza de archivos generados

### Windows con MinGW

```bash
mingw32-make clean
```

### Linux, Mac o WSL

```bash
make clean
```

## Diagrama de Clases

El proyecto incluye un diagrama de clases que representa la relación entre las principales estructuras utilizadas en el reproductor.

```text
diagrama_de_clases
```

En este diagrama se muestra la relación entre las clases principales del sistema, como `Cancion`, `Node`, `List`, `Reproductor` y `FileManager`.

## Consideraciones del Proyecto

* El proyecto fue desarrollado en C++.
* La interacción con el usuario se realiza mediante consola.
* La información de canciones se carga desde archivos planos.
* Se implementan estructuras de datos manuales, principalmente listas enlazadas.
* El sistema busca aplicar los contenidos vistos en la asignatura de Estructuras de Datos.
