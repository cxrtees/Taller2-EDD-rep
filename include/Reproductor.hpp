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
    // ── Listas del Taller 1 ───────────────────────────────────────────────
    List cancionesRegistradas;
    List listaReproduccionActual;
    List historial;
    List cicloBase;

    Cancion cancionActual;
    bool hayCancionActual;

    std::string estadoReproduccion;
    bool modoAleatorio;
    int modoRepeticion;

    // ── Nuevas estructuras Taller 2 ───────────────────────────────────────
    A_Trie       Arbol_trie;        // Trie para búsqueda de canciones
    Arbol_Artistas   Arbol_artistas;   // AVL de artistas (cada uno con su AVL de canciones)
    A_HeapCanciones Arbol_heapCanciones;   // Heap para Top 10 canciones
    A_HeapArtistas  Arbol_heapArtistas;    // Heap para Top 10 artistas

    // ── Utilidades de consola ─────────────────────────────────────────────
    void limpiarConsola();
    std::string leerLinea();

    // ── Pantalla principal ────────────────────────────────────────────────
    void mostrarPantallaPrincipal();
    void mostrarLineaActual();

    // ── Menús Taller 1 ────────────────────────────────────────────────────
    void menuListaActual();
    void menuCanciones();

    // ── Menús Taller 2 ────────────────────────────────────────────────────
    void menuBusqueda();                    // F - Buscar canciones
    void menuTop();                         // T - TOP 10
    void menuTopCanciones();                // TOP 10 canciones
    void menuTopArtistas();                 // TOP 10 artistas
    void menuCancionesArtista(const std::string& artista, A_AVL* avlCanciones);

    // ── Helpers de ciclo de reproducción ─────────────────────────────────
    void actualizarCicloBaseDesdeListaActual();
    void recargarListaActualDesdeCicloBase();

    // ── Inicialización de estructuras nuevas ─────────────────────────────
    void inicializarEstructuras();

    // ── Helper: registrar reproducción de una canción ─────────────────────
    void registrarReproduccion(const Cancion& c);

    // ── Helper: sincronizar canción del registro con cancionActual ─────────
    void sincronizarReproduccionesEnRegistro(int idCancion, int reproducciones);

public:
    Reproductor();

    void run();

    // ── Getters básicos ───────────────────────────────────────────────────
    bool tieneCancionActual();
    std::string getEstadoReproduccion();
    bool getModoAleatorio();
    int getModoRepeticion();
    Cancion getCancionActual();

    int getCantidadCancionesRegistradas();
    int getCantidadCancionesEnListaActual();
    Cancion getCancionRegistrada(int index);
    Cancion getCancionEnListaActual(int index);

    // ── Setters (usados por FileManager) ─────────────────────────────────
    void setHayCancionActual(bool v);
    void setEstadoReproduccion(const std::string& e);
    void setModoAleatorio(bool v);
    void setModoRepeticion(int r);
    void setCancionActual(Cancion c);

    void clearListaActual();
    void appendListaActual(Cancion c);
    void clearRegistro();
    void setReproduccionesCancion(int idCancion, int reproducciones);

    // ── Operaciones del registro ──────────────────────────────────────────
    void agregarCancionAlRegistro(Cancion cancion);
    void eliminarCancionDelRegistro(int index);

    // ── Reproducción ──────────────────────────────────────────────────────
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