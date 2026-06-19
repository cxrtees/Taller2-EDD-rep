#include "../include/Arbolartista.hpp"

Arbol_Artistas::Arbol_Artistas() : raiz(nullptr) {}

Arbol_Artistas::~Arbol_Artistas() {
    limpiar();
}

std::string Arbol_Artistas::toLower(const std::string& texto) const {
    std::string r = texto;
    for (size_t i = 0; i < r.size(); i++) {
        if (r[i] >= 'A' && r[i] <= 'Z') {
            r[i] = char(r[i] - 'A' + 'a');
        }
    }
    return r;
}

int Arbol_Artistas::altura(NodoArtista* nodo) const {
    return nodo ? nodo->altura : 0;
}

int Arbol_Artistas::maximo(int a, int b) const {
    return a > b ? a : b;
}

int Arbol_Artistas::balance(NodoArtista* nodo) const {
    return nodo ? altura(nodo->izquierda) - altura(nodo->derecha) : 0;
}

NodoArtista* Arbol_Artistas::rotarDerecha(NodoArtista* y) {
    NodoArtista* x = y->izquierda;
    NodoArtista* t2 = x->derecha;

    x->derecha = y;
    y->izquierda = t2;

    y->altura = 1 + maximo(altura(y->izquierda), altura(y->derecha));
    x->altura = 1 + maximo(altura(x->izquierda), altura(x->derecha));

    return x;
}

NodoArtista* Arbol_Artistas::rotarIzquierda(NodoArtista* x) {
    NodoArtista* y = x->derecha;
    NodoArtista* t2 = y->izquierda;

    y->izquierda = x;
    x->derecha = t2;

    x->altura = 1 + maximo(altura(x->izquierda), altura(x->derecha));
    y->altura = 1 + maximo(altura(y->izquierda), altura(y->derecha));

    return y;
}

NodoArtista* Arbol_Artistas::rebalancear(NodoArtista* nodo) {
    if (!nodo) return nodo;

    nodo->altura = 1 + maximo(altura(nodo->izquierda), altura(nodo->derecha));
    int b = balance(nodo);

    if (b > 1 && balance(nodo->izquierda) >= 0) {
        return rotarDerecha(nodo);
    }
    
    if (b > 1 && balance(nodo->izquierda) < 0) {
        nodo->izquierda = rotarIzquierda(nodo->izquierda);
        return rotarDerecha(nodo);
    }

    if (b < -1 && balance(nodo->derecha) <= 0) {
        return rotarIzquierda(nodo);
    }

    if (b < -1 && balance(nodo->derecha) > 0) {
        nodo->derecha = rotarDerecha(nodo->derecha);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

NodoArtista* Arbol_Artistas::insertar(NodoArtista* nodo, const Cancion& cancion) {
    std::string nombreArtista = cancion.getNombreArtista();
    std::string clave = toLower(nombreArtista);

    if (!nodo) {
        return new NodoArtista(clave, nombreArtista, cancion);
    }

    if (clave < nodo->clave) {
        nodo->izquierda = insertar(nodo->izquierda, cancion);
    } else if (clave > nodo->clave) {
        nodo->derecha = insertar(nodo->derecha, cancion);
    } else {
        nodo->canciones.insertar(cancion);
        return nodo;
    } 

    return rebalancear(nodo);
}

NodoArtista* Arbol_Artistas::buscar(NodoArtista* nodo, const std::string& clave) const {
    if (!nodo) return nullptr;

    if (clave == nodo->clave) return nodo;

    if (clave < nodo->clave) {
        return buscar(nodo->izquierda, clave);
    }

    return buscar(nodo->derecha, clave);
}

void Arbol_Artistas::destruir(NodoArtista* nodo) {
    if (!nodo) return;

    destruir(nodo->izquierda);
    destruir(nodo->derecha);

    delete nodo;
}

int Arbol_Artistas::contar(NodoArtista* nodo) const {
    if (!nodo) return 0;
    return 1 + contar(nodo->izquierda) + contar(nodo->derecha);
}

void Arbol_Artistas::inorden(NodoArtista* nodo, EntradaArtista* arreglo, int maxSize, int& indice) const {
    if (!nodo || indice >= maxSize) return;

    inorden(nodo->izquierda, arreglo, maxSize, indice);

    if (indice < maxSize) {
        arreglo[indice].nombre = nodo->nombre;
        arreglo[indice].reproducciones = 0;
        arreglo[indice].canciones = &(nodo->canciones);
        indice++;
    }
    inorden(nodo->derecha, arreglo, maxSize, indice);
}

void Arbol_Artistas::insertar(const Cancion& cancion) {
    raiz = insertar(raiz, cancion);
}

A_AVL* Arbol_Artistas::buscarCancionesDeArtista(const std::string& artista) const {
    NodoArtista* nodo = buscar(raiz, toLower(artista));

    if (!nodo) return nullptr;

    return &(nodo->canciones);
}

int Arbol_Artistas::obtenerTodos(EntradaArtista* arreglo, int maxSize) const {
    int indice = 0;
    inorden(raiz, arreglo, maxSize, indice);
    return indice;
}

int Arbol_Artistas::getCantidad() const {
    return contar(raiz);
}

bool Arbol_Artistas::estaVacio() const {
    return raiz == nullptr;
}

void Arbol_Artistas::limpiar() {
    destruir(raiz);
    raiz = nullptr;
}

