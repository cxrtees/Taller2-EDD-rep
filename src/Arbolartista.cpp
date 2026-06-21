#include "../include/Arbolartista.hpp"

ArbolArtistas::ArbolArtistas() : raiz(nullptr) {}

ArbolArtistas::~ArbolArtistas() {
    limpiar();
}

std::string ArbolArtistas::toLower(const std::string& texto) const {
    std::string r = texto;
    for (size_t i = 0; i < r.size(); i++) {
        if (r[i] >= 'A' && r[i] <= 'Z') {
            r[i] = char(r[i] - 'A' + 'a');
        }
    }
    return r;
}

int ArbolArtistas::altura(NodoArtista* nodo) const {
    return nodo ? nodo->altura : 0;
}

int ArbolArtistas::maximo(int a, int b) const {
    return a > b ? a : b;
}

int ArbolArtistas::balance(NodoArtista* nodo) const {
    return nodo ? altura(nodo->izquierda) - altura(nodo->derecha) : 0;
}

NodoArtista* ArbolArtistas::rotarDerecha(NodoArtista* y) {
    NodoArtista* x = y->izquierda;
    NodoArtista* t2 = x->derecha;

    x->derecha = y;
    y->izquierda = t2;

    y->altura = 1 + maximo(altura(y->izquierda), altura(y->derecha));
    x->altura = 1 + maximo(altura(x->izquierda), altura(x->derecha));

    return x;
}

NodoArtista* ArbolArtistas::rotarIzquierda(NodoArtista* x) {
    NodoArtista* y = x->derecha;
    NodoArtista* t2 = y->izquierda;

    y->izquierda = x;
    x->derecha = t2;

    x->altura = 1 + maximo(altura(x->izquierda), altura(x->derecha));
    y->altura = 1 + maximo(altura(y->izquierda), altura(y->derecha));

    return y;
}

NodoArtista* ArbolArtistas::rebalancear(NodoArtista* nodo) {
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

NodoArtista* ArbolArtistas::insertar(NodoArtista* nodo, const Cancion& cancion) {
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

NodoArtista* ArbolArtistas::buscar(NodoArtista* nodo, const std::string& clave) const {
    if (!nodo) return nullptr;

    if (clave == nodo->clave) return nodo;

    if (clave < nodo->clave) {
        return buscar(nodo->izquierda, clave);
    }

    return buscar(nodo->derecha, clave);
}

void ArbolArtistas::destruir(NodoArtista* nodo) {
    if (!nodo) return;

    destruir(nodo->izquierda);
    destruir(nodo->derecha);

    delete nodo;
}

int ArbolArtistas::contar(NodoArtista* nodo) const {
    if (!nodo) return 0;
    return 1 + contar(nodo->izquierda) + contar(nodo->derecha);
}

void ArbolArtistas::inorden(NodoArtista* nodo, EntradaArtista* arreglo, int maxSize, int& indice) const {
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

void ArbolArtistas::insertar(const Cancion& cancion) {
    raiz = insertar(raiz, cancion);
}

AVL* ArbolArtistas::buscarCancionesDeArtista(const std::string& artista) const {
    NodoArtista* nodo = buscar(raiz, toLower(artista));

    if (!nodo) return nullptr;

    return &(nodo->canciones);
}

int ArbolArtistas::obtenerTodos(EntradaArtista* arreglo, int maxSize) const {
    int indice = 0;
    inorden(raiz, arreglo, maxSize, indice);
    return indice;
}

int ArbolArtistas::getCantidad() const {
    return contar(raiz);
}

bool ArbolArtistas::estaVacio() const {
    return raiz == nullptr;
}

void ArbolArtistas::limpiar() {
    destruir(raiz);
    raiz = nullptr;
}

