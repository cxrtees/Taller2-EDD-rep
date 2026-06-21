#pragma once
#include "Cancion.hpp"
#include <string>

struct NodoAVL {
    std::string clave;
    Cancion cancion;
    int altura;
    NodoAVL* izquierda;
    NodoAVL* derecha;

    NodoAVL(const std::string& clave, const Cancion& cancion);
};