#pragma once
#include "NodeAVL.hpp"
#include "Cancion.hpp"
#include <string>

// Árbol AVL que almacena canciones ordenadas alfabéticamente por nombre
// Se usa uno por cada artista en el árbol de artistas
class A_AVL {
private:
    NodoAVL* raiz;

    int altura(NodoAVL* n) const;
    int balance(NodoAVL* n) const;
    NodoAVL* rotarDerecha(NodoAVL* y);
    NodoAVL* rotarIzquierda(NodoAVL* x);
    NodoAVL* rebalancear(NodoAVL* n);

    NodoAVL* insertar(NodoAVL* nodo, const std::string& clave, const Cancion& cancion);
    NodoAVL* eliminar(NodoAVL* nodo, const std::string& clave);
    NodoAVL* minimo(NodoAVL* nodo) const;

    void inorden(NodoAVL* nodo, Cancion* arreglo, int& indice) const;
    void eliminarArbol(NodoAVL* nodo);
    int contarNodos(NodoAVL* nodo) const;

    std::string toLower(const std::string& s) const;

public:
    A_AVL();
    ~A_AVL();

    // Inserta una canción ordenada por nombre de canción (en minúsculas)
    void insertar(const Cancion& cancion);

    // Elimina una canción por nombre
    void eliminar(const std::string& nombreCancion);

    // Recorre en inorden y llena el arreglo dado (debe tener tamaño suficiente)
    // Retorna la cantidad de elementos
    int obtenerEnOrden(Cancion* arreglo, int maxSize) const;

    int getCantidad() const;
    bool estaVacio() const;
};