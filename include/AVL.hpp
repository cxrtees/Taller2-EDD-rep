#pragma once
#include "NodeAVL.hpp"
#include "Cancion.hpp"
#include <string>


class AVL {
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

    void inorden(NodoAVL* nodo, Cancion* arreglo, int maxSize, int& indice) const;
    void eliminarArbol(NodoAVL* nodo);
    int contarNodos(NodoAVL* nodo) const;

    std::string toLower(const std::string& s) const;

public:
    AVL();
    ~AVL();

    void insertar(const Cancion& cancion);

    void eliminar(const std::string& nombreCancion);

    int obtenerEnOrden(Cancion* arreglo, int maxSize) const;

    int getCantidad() const;
    bool estaVacio() const;
};