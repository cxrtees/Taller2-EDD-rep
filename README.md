# Reproductor de Música - SoundStructure

## Integrantes del Equipo

* Matías Antonio Collao Valdivia
* Benjamín Ismael Cortés Acuña
* Catalina Isidora Rojas Macaya

## Descripción del Proyecto

Este proyecto consiste en un reproductor de música interactivo por consola desarrollado en C++ para la asignatura de Estructuras de Datos. La aplicación permite gestionar una biblioteca musical local mediante estructuras de datos implementadas manualmente, utilizando listas enlazadas, árboles AVL, árboles Trie y Heap para organizar, buscar y clasificar canciones y artistas.

El sistema permite cargar canciones desde archivos planos, reproducir pistas, avanzar o retroceder dentro de la cola de reproducción, realizar búsquedas por canción o artista, ordenar información alfabéticamente y generar rankings de reproducción. La aplicación funciona mediante consola y utiliza archivos locales para mantener la información necesaria del reproductor.

## Funcionamiento de la Aplicación

El sistema opera mediante una interfaz basada en consola. La información principal se obtiene desde archivos locales ubicados en la raíz del proyecto.

Los archivos utilizados son:

```text
music_source.txt   # Archivo fuente con la información de las canciones
status.cfg         # Archivo de configuración o estado del reproductor
```

El reproductor cuenta con las siguientes funcionalidades principales:

1. **Carga de canciones:** permite leer canciones desde el archivo `music_source.txt`.
2. **Control de reproducción:** permite iniciar, pausar, avanzar y retroceder canciones.
3. **Gestión de biblioteca musical:** almacena las canciones cargadas en estructuras propias.
4. **Búsqueda de canciones y artistas:** permite buscar información mediante estructuras Trie.
5. **Ordenamiento por artista:** organiza información utilizando árboles AVL.
6. **Ranking de reproducciones:** permite obtener canciones o artistas con mayor cantidad de reproducciones mediante Heap.
7. **Persistencia de datos:** permite guardar y recuperar información relevante del estado del reproductor.
8. **Interacción por consola:** el usuario controla el reproductor mediante opciones mostradas en pantalla.

## Estructuras y Clases Utilizadas

El proyecto está organizado mediante clases propias en C++, separadas en archivos de cabecera `.hpp` e implementación `.cpp`.

### Clase `Cancion`

La clase `Cancion` representa una pista musical dentro del reproductor. Su función principal es almacenar la información asociada a cada canción.

Puede contener datos como:

* Nombre de la canción.
* Nombre del artista.
* Duración.
* Cantidad de reproducciones.
* Otros datos necesarios para identificar o gestionar la canción.

Esta clase funciona como el objeto principal que será almacenado dentro de las estructuras del proyecto.

### Clase `Node`

La clase `Node` representa un nodo utilizado dentro de la lista enlazada. Cada nodo permite almacenar una canción y enlazarla con otro nodo.

Su propósito principal es permitir la construcción de una lista enlazada para recorrer canciones de forma dinámica.

### Clase `List`

La clase `List` implementa una lista enlazada utilizada para almacenar y recorrer canciones dentro del reproductor.

Esta estructura permite:

* Insertar canciones.
* Recorrer la lista.
* Acceder a la canción actual.
* Avanzar a la siguiente canción.
* Gestionar canciones dentro de la biblioteca musical.
* Mantener una estructura dinámica sin depender de arreglos de tamaño fijo.

### Clase `Reproductor`

La clase `Reproductor` contiene la lógica principal de funcionamiento del programa. Se encarga de administrar la reproducción de canciones y coordinar las acciones del usuario con las estructuras internas.

Entre sus responsabilidades se encuentran:

* Controlar la canción actual.
* Reproducir o pausar canciones.
* Avanzar a la siguiente canción.
* Volver a una canción anterior.
* Activar funciones del menú.
* Coordinar la interacción entre la lista de canciones, los árboles y el usuario.

### Archivo `Reproductor_menus.cpp`

El archivo `Reproductor_menus.cpp` contiene parte de la lógica asociada a los menús del reproductor. Su objetivo es separar las funciones de interacción con el usuario de la lógica principal del reproductor, facilitando la organización del código.

### Clase `FileManager`

La clase `FileManager` se encarga de la gestión de archivos del proyecto. Su función principal es leer y escribir información desde archivos planos.

Permite:

* Cargar canciones desde `music_source.txt`.
* Leer datos necesarios para inicializar el reproductor.
* Guardar información relevante del estado del programa.
* Manejar archivos de configuración como `status.cfg`.

### Clase `NodeAVL`

La clase `NodeAVL` representa un nodo dentro de un árbol AVL. Cada nodo almacena información necesaria para mantener la estructura balanceada del árbol.

Puede contener:

* Dato almacenado.
* Puntero al hijo izquierdo.
* Puntero al hijo derecho.
* Altura o factor de balance.

Esta clase es utilizada como base para implementar árboles AVL dentro del proyecto.

### Clase `AVL`

La clase `AVL` implementa un árbol binario de búsqueda auto-balanceado. Su objetivo es mantener los datos ordenados y permitir operaciones eficientes de inserción, búsqueda y recorrido.

El árbol AVL permite mantener un orden alfabético o jerárquico de canciones u otros datos, garantizando que la estructura se mantenga balanceada mediante rotaciones.

### Clase `Nodeartista`

La clase `Nodeartista` representa un nodo asociado a la información de un artista dentro del árbol de artistas.

Su función es almacenar los datos de un artista y permitir enlazarlo dentro de la estructura correspondiente.

### Clase `Arbolartista`

La clase `Arbolartista` implementa una estructura de árbol para organizar artistas. Permite almacenar, buscar y recorrer artistas de forma ordenada.

Esta estructura ayuda a gestionar la información relacionada con los artistas y sus canciones dentro del reproductor.

### Clase `TrieNode` / `TriNode`

La clase `TrieNode` o `TriNode` representa un nodo dentro de un árbol Trie. Cada nodo permite almacenar caracteres o referencias necesarias para realizar búsquedas eficientes por texto.

Esta estructura se utiliza como base para construir el Trie del proyecto.

### Clase `Trie`

La clase `Trie` implementa un árbol de búsqueda por caracteres. Su objetivo es facilitar la búsqueda de canciones o artistas mediante texto, permitiendo encontrar coincidencias a partir de cadenas o subcadenas.

Esta estructura es útil para optimizar la búsqueda dentro de la biblioteca musical.

### Clase `Heap`

La clase `Heap` implementa una estructura tipo montículo. Esta estructura permite organizar elementos según prioridad, por ejemplo, según la cantidad de reproducciones.

Dentro del proyecto puede utilizarse para generar rankings, como canciones o artistas más reproducidos.

## Estructura del Proyecto

La estructura actual del proyecto es la siguiente:

```text
Taller2-EDD-rep
│
├── .vscode
│   └── settings.json
│
├── img
│
├── include
│   ├── Arbolartista.hpp
│   ├── AVL.hpp
│   ├── Cancion.hpp
│   ├── FileManager.hpp
│   ├── Heap.hpp
│   ├── List.hpp
│   ├── Node.hpp
│   ├── Nodeartista.hpp
│   ├── NodeAVL.hpp
│   ├── Reproductor.hpp
│   ├── Trie.hpp
│   └── TrieNode.hpp
│
├── src
│   ├── Arbolartista.cpp
│   ├── AVL.cpp
│   ├── Cancion.cpp
│   ├── FileManager.cpp
│   ├── Heap.cpp
│   ├── List.cpp
│   ├── main.cpp
│   ├── Node.cpp
│   ├── Nodeartista.cpp
│   ├── NodeAVL.cpp
│   ├── Reproductor_menus.cpp
│   ├── Reproductor.cpp
│   ├── Trie.cpp
│   └── TriNode.cpp
│
├── .gitignore
├── Makefile
├── music_source.txt
├── README.md
└── status.cfg
```

La carpeta `include` contiene los archivos de cabecera `.hpp`, donde se declaran las clases, atributos y métodos principales del proyecto. La carpeta `src` contiene los archivos `.cpp`, donde se implementa la lógica de cada clase. Además, la carpeta `img` almacena recursos visuales utilizados en el README, como el diagrama de clases, y `.vscode` contiene configuraciones locales del entorno de desarrollo.


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
g++ -std=c++17 -Wall -Wextra -Iinclude src/main.cpp src/Arbolartista.cpp src/AVL.cpp src/Cancion.cpp src/FileManager.cpp src/Heap.cpp src/List.cpp src/Node.cpp src/Nodeartista.cpp src/NodeAVL.cpp src/Reproductor_menus.cpp src/Reproductor.cpp src/Trie.cpp src/TriNode.cpp -o reproductor.exe
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

## Consideraciones del Proyecto

* El proyecto fue desarrollado en C++.
* La interacción con el usuario se realiza mediante consola.
* La información de canciones se carga desde archivos planos.
* Se implementan estructuras de datos manuales.
* El proyecto utiliza listas enlazadas, árboles AVL, árboles Trie y Heap.
* El sistema busca aplicar los contenidos vistos en la asignatura de Estructuras de Datos.

## Diagrama de Clases (Estándar UML)

![Diagrama de Clases UML](img/diagrama_clases.png)
