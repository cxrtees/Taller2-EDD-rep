#pragma once 
#include "Nodeartista.hpp"
#include "Cancion.hpp"
#include <string>

class Arbol_Artistas {

private: 
    NodoArtista* raiz;

    std::string toLower(const std::string& texto) const;

    int altura(NodoArtista* nodo) const;
    int maximo(int a, int b) const;
    int balance(NodoArtista* nodo) const;

    NodoArtista* rotarDerecha(NodoArtista* y);
    NodoArtista* rotarIzquierda(NodoArtista* x);
    NodoArtista* rebalancear(NodoArtista* nodo);

    NodoArtista* insertar(NodoArtista* nodo, const Cancion& cancion);
    NodoArtista* buscar(NodoArtista* nodo, const std::string& clave) const;

    void destruir(NodoArtista* nodo);
    int contar(NodoArtista* nodo) const;
    void inorden(NodoArtista* nodo, EntradaArtista& arreglo, int maxSize, int& indice) const;

public:
    Arbol_Artistas();
    ~Arbol_Artistas();

    void insertar(const Cancion& cancion);
    A_AVL* buscarCancionesDeArtista(const std::string& artista) const;

    int obtenerTodos(EntradaArtista* arreglo, int maxSize) const;
    int getCantidad() const;
    bool estaVacio() const;
    void limpiar();

};
