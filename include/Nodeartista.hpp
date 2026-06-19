#pragma once
#include "AVL.hpp"
#include "Cancion.hpp"
#include <string>

struct EntradaArtista {
    std::string nombre;
    int reproducciones;
    A_ALV* canciones; 

    EntradaArtista() : nombre(""), reproducciones(0), canciones(nullptr) {}
}; 

struct NodoArtista {
    std::string clave;
    std::string nombre;
    A_AVL canciones;
    int altura;
    NodoArtista* izquierda;
    NodoArtista* derecha;

    NodoArtista(const std::string& clave, const std::string& nombre, const Cancion& cancion);
};


