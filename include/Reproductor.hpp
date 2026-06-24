#pragma once
#include "List.hpp"
#include "Cancion.hpp"
#include "Trie.hpp"
#include "AVL.hpp"
#include "Arbolartista.hpp"
#include "Heap.hpp"
#include <string>

class Reproductor {
private:

    List cancionesRegistradas;
    List listaReproduccionActual;
    List historial;
    List cicloBase;

    Cancion cancionActual;
    bool hayCancionActual;

    std::string estadoReproduccion;
    bool modoAleatorio;
    int modoRepeticion;
    bool volverMenuPrincipalDesdeTop;


    Trie      arbolTrie;
    ArbolArtistas arbolArtistas;
    HeapCanciones Arbol_heapCanciones;
    ArbolHeapArtistas  Arbol_heapArtistas;

    //utilidades de consola
    void limpiarConsola();
    std::string leerLinea();

    // Pantalla principal
    void mostrarPantallaPrincipal();
    void mostrarLineaActual();

    // Menús del Sistema
    void menuListaActual();
    void menuCanciones();
    void menuBusqueda();
    void menuTop();
    void menuTopCanciones();
    void menuTopArtistas();
    void menuCancionesArtista(const std::string& artista, AVL* avlCanciones);

    // ciclo de reproducción
    void actualizarCicloBaseDesdeListaActual();
    void recargarListaActualDesdeCicloBase();

    // Inicialización de estructuras
    void inicializarEstructuras();

    //registrar reproducción
    void registrarReproduccion(const Cancion& c);

    // sincronizar canción del registro
    void sincronizarReproduccionesEnRegistro(int idCancion, int reproducciones);

public:
    Reproductor();

    void run();

    // Getters
    bool tieneCancionActual();
    std::string getEstadoReproduccion();
    bool getModoAleatorio();
    int getModoRepeticion();
    Cancion getCancionActual();

    int getCantidadCancionesRegistradas();
    int getCantidadCancionesEnListaActual();
    Cancion getCancionRegistrada(int index);
    Cancion getCancionEnListaActual(int index);

    //Setters
    void setHayCancionActual(bool v);
    void setEstadoReproduccion(const std::string& e);
    void setModoAleatorio(bool v);
    void setModoRepeticion(int r);
    void setCancionActual(Cancion c);

    void clearListaActual();
    void appendListaActual(Cancion c);
    void clearRegistro();
    void setReproduccionesCancion(int idCancion, int reproducciones);

    //registro
    void agregarCancionAlRegistro(Cancion cancion);
    void eliminarCancionDelRegistro(int index);

    //Reproducción
    void reproducirCancionDelRegristro(int index);
    void agregarCancionAListaActual(int index);

    void togglePlayPause();
    void siguiente();
    void anterior();

    void cambiarModoAleatorio();
    void cambiarModoRepeticion();

    void generarListaAleatoriaDesdeRegistro();
    void mezclarListaActual();
};