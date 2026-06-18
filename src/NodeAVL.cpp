#include "../include/NodoAVL.hpp"

NodoAVL::NodoAVL(const std::string& clave, const Cancion& cancion)
    : clave(clave), cancion(cancion), altura(1),
      izquierda(nullptr), derecha(nullptr) {}