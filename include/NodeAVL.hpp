#pragma once
#include "Cancion.hpp"
#include <string>

// Nodo interno del árbol AVL de canciones por artista
struct NodoAVL {
    std::string clave;      // nombre de canción (clave de orden alfabético)
    Cancion cancion;        // canción almacenada
    int altura;
    NodoAVL* izquierda;
    NodoAVL* derecha;

    NodoAVL(const std::string& clave, const Cancion& cancion);
};