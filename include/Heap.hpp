#pragma once
#include "Cancion.hpp"
#include <string>


struct EntradaHeapCancion {
    Cancion cancion;
    int reproducciones;
    EntradaHeapCancion() : reproducciones(0) {}
    EntradaHeapCancion(const Cancion& c, int r) : cancion(c), reproducciones(r) {}
};

struct EntradaHeapArtista {
    std::string nombreArtista;
    int reproducciones;
    EntradaHeapArtista() : nombreArtista(""), reproducciones(0) {}
    EntradaHeapArtista(const std::string& n, int r) : nombreArtista(n), reproducciones(r) {}
};


class HeapCanciones {
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
    HeapCanciones(int capacidadInicial = 64);
    ~HeapCanciones();

    void insertar(const EntradaHeapCancion& entrada);
    EntradaHeapCancion extraerMaximo();
    const EntradaHeapCancion& verMaximo() const;

    void actualizarOInsertar(const Cancion& cancion, int reproducciones);

    void eliminar(int idCancion);

    int getTamanio() const { return tamanio; }
    bool estaVacio() const { return tamanio == 0; }
    int extraerTop(int n, EntradaHeapCancion* resultado);
};

class ArbolHeapArtistas {
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
    ArbolHeapArtistas(int capacidadInicial = 64);
    ~ArbolHeapArtistas();

    void insertar(const EntradaHeapArtista& entrada);
    EntradaHeapArtista extraerMaximo();

    void actualizarOInsertar(const std::string& artista, int reproducciones);

    void eliminar(const std::string& artista);

    int getTamanio() const { return tamanio; }
    bool estaVacio() const { return tamanio == 0; }

    int extraerTop(int n, EntradaHeapArtista* resultado);
};