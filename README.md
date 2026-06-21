# Reproductor de Música - SoundStructure

### Integrantes del Equipo
* Matías Antonio Collao Valdivia
* Benjamín Ismael Cortés Acuña
* Catalina Isidora Rojas Macaya

## Descripción del Proyecto
Este proyecto consiste en un reproductor de música interactivo por consola desarrollado en C++ para la asignatura de Estructuras de Datos. La aplicación optimiza la gestión, búsqueda y ordenamiento de una biblioteca musical mediante la implementación manual de estructuras avanzadas de datos, omitiendo por completo las librerías nativas de contenedores STL. Integra árboles Trie para búsquedas indexadas de texto por subcadenas, árboles AVL para el almacenamiento y ordenamiento alfabético de pistas por artista, y estructuras Max-Heap para el cálculo eficiente del ranking TOP 10 de reproducciones.

## Funcionamiento de la Aplicación
El sistema opera en una interfaz basada en consola de comandos síncrona con persistencia de datos local en archivos planos (`music_source.txt`, `song_ranking.txt` y `status.cfg`). Ofrece las siguientes funcionalidades principales:

1. **Control de Reproducción (Taller 1):** Operaciones básicas de reproducción (Play/Pause), control de pistas (Siguiente/Anterior), modo aleatorio (*shuffle*) y tres estados de repetición (Desactivado, Repetir una, Repetir todas).
2. **Búsqueda Avanzada (F):** Permite encontrar canciones o artistas mediante la introducción de subcadenas alfanuméricas. Devuelve un listado numerado con opciones para reproducir inmediatamente o añadir al final de la cola de reproducción actual.
3. **Ranking TOP 10 (T):** Despliega dinámicamente dos tipos de rankings basados en contadores de reproducción:
    * **TOP 10 Canciones:** Ordenadas de mayor a menor reproducción. En caso de empate, aplica un desempate alfabético por nombre de canción y luego por artista.
    * **TOP 10 Artistas:** Ordenadas por el acumulado total de reproducciones de sus obras. Incluye un submenú para inspeccionar de manera aislada las canciones del artista en orden alfabético.

## Estructuras de Datos Utilizadas
Para cumplir con las restricciones de rendimiento del taller, no se utiliza la biblioteca estándar STL de contenedores. En su lugar se codificaron nodo a nodo las siguientes estructuras:
* **Lista Enlazada Simple (`List`):** Gestiona el registro global de canciones, la cola de reproducción activa, el historial de pistas anteriores y el ciclo base.
* **Árbol Trie de Sufijos (`Trie`):** Indexa cada sufijo alfanumérico del nombre de la canción y del artista. Permite realizar búsquedas de subcadenas en tiempo lineal respecto a la longitud del patrón de búsqueda.
* **Árbol AVL (`Arbol_Artistas` y `AVL`):** Árboles binarios auto-balanceados por altura. Garantizan operaciones de inserción, eliminación y búsqueda en tiempo logarítmico $O(\log n)$, manteniendo las canciones indexadas alfabéticamente de forma automática.
* **Max-Heap (`HeapCanciones` y `HeapArtistas`):** Árboles binarios semiordenados representados mediante arreglos dinámicos manuales. Permiten la inserción en tiempo $O(\log n)$ y la extracción del máximo en $O(\log n)$ para la generación de rankings prioritarios.

## Instrucciones de Compilación y Ejecución

El proyecto está modularizado separando interfaces (`.hpp`) en la carpeta `include/` e implementaciones (`.cpp`) en la carpeta `src/`.

### Requisitos del Sistema
* Compilador GCC/G++ con soporte para el estándar **C++14** o superior.
* Herramienta de automatización CMake (Versión 3.10 o superior).

### Compilación y Ejecución vía CMake (Recomendado)
1. Abra una terminal en la carpeta raíz del proyecto.
2. Genere el directorio de construcción y compile ejecutando los siguientes comandos:
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .

classDiagram
class Cancion {
-int idInterno
-string nombreCancion
-string nombreArtista
-string nombreAlbum
-int anio
-int duracionSegundos
-string ubicacionArchivo
-int reproducciones
+getIdInterno() int
+getNombreCancion() string
+getNombreArtista() string
+setReproducciones(int v) void
+incrementarReproducciones() void
}

    class Node {
        -Cancion dato
        -Node next
        +getDato() Cancion
        +getNext() Node
        +setNext(Node next) void
    }

    class List {
        -Node start
        -int size
        +isEmpty() bool
        +getSize() int
        +insertLast(Cancion dato) void
        +get(int index) Cancion
        +remove(int index) void
        +popFirst() Cancion
        +clear() void
    }

    class NodoAVL {
        +string clave
        +Cancion cancion
        +int altura
        +NodoAVL izquierda
        +NodoAVL derecha
    }

    class AVL {
        -NodoAVL raiz
        -rebalancear(NodoAVL n) NodoAVL
        +insertar(Cancion cancion) void
        +eliminar(string nombreCancion) void
        +obtenerEnOrden(Cancion arreglo, int maxSize) int
    }

    class NodoArtista {
        +string clave
        +string nombre
        +AVL canciones
        +int altura
        +NodoArtista izquierda
        +NodoArtista derecha
    }

    class Arbol_Artistas {
        -NodoArtista raiz
        -rebalancear(NodoArtista nodo) NodoArtista
        +insertar(Cancion cancion) void
        +buscarCancionesDeArtista(string artista) AVL
        +obtenerTodos(EntradaArtista arreglo, int maxSize) int
    }

    class TrieNode {
        +char caracter
        +TrieNode primerHijo
        +TrieNode hermano
        +IdNodo listaIds
        +bool esFin
        +agregarId(int id) void
        +eliminarId(int id) void
    }

    class Trie {
        -TrieNode raiz
        +insertar(Cancion cancion) void
        +eliminar(Cancion cancion) void
        +buscar(string texto, ListaResultados resultado) void
    }

    class HeapCanciones {
        -EntradaHeapCancion datos
        -int capacidad
        -int tamanio
        -subirHeap(int i) void
        -bajarHeap(int i) void
        +insertar(EntradaHeapCancion entrada) void
        +extraerTop(int n, EntradaHeapCancion resultado) int
    }

    class HeapArtistas {
        -EntradaHeapArtista datos
        -int capacidad
        -int tamanio
        -subirHeap(int i) void
        -bajarHeap(int i) void
        +insertar(EntradaHeapArtista entrada) void
        +extraerTop(int n, EntradaHeapArtista resultado) int
    }

    class FileManager {
        +cargarCanciones(string archivo, Reproductor rep) bool
        +guardarCanciones(string archivo, Reproductor rep) bool
        +cargarRanking(string archivo, Reproductor rep) bool
        +guardarRanking(string archivo, Reproductor rep) bool
        +cargarStatus(string archivo, Reproductor rep) bool
        +guardarStatus(string archivo, Reproductor rep) bool
    }

    class Reproductor {
        -List cancionesRegistradas
        -List listaReproduccionActual
        -List historial
        -List cicloBase
        -Cancion cancionActual
        -Trie arbolTrie
        -Arbol_Artistas arbolArtistas
        -HeapCanciones Arbol_heapCanciones
        -HeapArtistas Arbol_heapArtistas
        +run() void
        -menuBusqueda() void
        -menuTop() void
        -inicializarEstructuras() void
    }

    Node --> Cancion
    List --> Node
    NodoAVL --> Cancion
    AVL --> NodoAVL
    NodoArtista --> AVL
    Arbol_Artistas --> NodoArtista
    TrieNode --> TrieNode
    Trie --> TrieNode
    Reproductor --> List
    Reproductor --> Cancion
    Reproductor --> Trie
    Reproductor --> Arbol_Artistas
    Reproductor --> HeapCanciones
    Reproductor --> HeapArtistas
    FileManager ..> Reproductor