#pragma once
#include "Cancion.hpp"
#include <string>

// Entrada para el Heap de canciones
struct EntradaHeapCancion {
    Cancion cancion;
    int reproducciones;
    EntradaHeapCancion() : reproducciones(0) {}
    EntradaHeapCancion(const Cancion& c, int r) : cancion(c), reproducciones(r) {}
};

// Entrada para el Heap de artistas
struct EntradaHeapArtista {
    std::string nombreArtista;
    int reproducciones;
    EntradaHeapArtista() : nombreArtista(""), reproducciones(0) {}
    EntradaHeapArtista(const std::string& n, int r) : nombreArtista(n), reproducciones(r) {}
};

// Max-Heap de canciones (por reproducciones, desempate alfabético)
// Implementado con arreglo dinámico manual (sin STL)
class A_HeapCanciones {
private:
    EntradaHeapCancion* datos;
    int capacidad;
    int tamanio;

    void expandir();
    void subirHeap(int i);
    void bajarHeap(int i);
    int padre(int i) const { return (i - 1) / 2; }
    int hijoIzq(int i) const { return 2 * i + 1; }
    int hijoDer(int i) const { return 2 * i + 2; }
    bool esMayor(const EntradaHeapCancion& a, const EntradaHeapCancion& b) const;
    std::string toLower(const std::string& s) const;

public:
    A_HeapCanciones(int capacidadInicial = 64);
    ~A_HeapCanciones();

    void insertar(const EntradaHeapCancion& entrada);
    EntradaHeapCancion extraerMaximo();
    const EntradaHeapCancion& verMaximo() const;

    // Actualiza las reproducciones de una canción por ID
    // Si no existe, la inserta
    void actualizarOInsertar(const Cancion& cancion, int reproducciones);

    // Elimina una canción del heap por ID
    void eliminar(int idCancion);

    int getTamanio() const { return tamanio; }
    bool estaVacio() const { return tamanio == 0; }

    // Extrae los top N elementos (los destruye del heap, úsalo en copia)
    // Retorna la cantidad extraída
    int extraerTop(int n, EntradaHeapCancion* resultado);
};

// Max-Heap de artistas (por reproducciones, desempate alfabético)
class A_HeapArtistas {
private:
    EntradaHeapArtista* datos;
    int capacidad;
    int tamanio;

    void expandir();
    void subirHeap(int i);
    void bajarHeap(int i);
    int padre(int i) const { return (i - 1) / 2; }
    int hijoIzq(int i) const { return 2 * i + 1; }
    int hijoDer(int i) const { return 2 * i + 2; }
    bool esMayor(const EntradaHeapArtista& a, const EntradaHeapArtista& b) const;
    std::string toLower(const std::string& s) const;

public:
    A_HeapArtistas(int capacidadInicial = 64);
    ~A_HeapArtistas();

    void insertar(const EntradaHeapArtista& entrada);
    EntradaHeapArtista extraerMaximo();

    // Actualiza o inserta artista
    void actualizarOInsertar(const std::string& artista, int reproducciones);

    // Elimina artista por nombre
    void eliminar(const std::string& artista);

    int getTamanio() const { return tamanio; }
    bool estaVacio() const { return tamanio == 0; }

    int extraerTop(int n, EntradaHeapArtista* resultado);
};