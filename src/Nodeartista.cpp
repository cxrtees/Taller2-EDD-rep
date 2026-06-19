#include "../include/Nodeartista.hpp"

NodoArtista::NodoArtista(const std::string& clave, const std::string& nombre, const Cancion& cancion)
    : clave(clave), nombre(nombre), canciones(), altura(1),
      izquierda(nullptr), derecha(nullptr) {
    canciones.insertar(cancion);
}

