#include "../include/AVL.hpp"

A_AVL::A_AVL() : raiz(nullptr) {}

A_AVL::~A_AVL() {
    eliminarArbol(raiz);
}

void A_AVL::eliminarArbol(NodoAVL* nodo) {
    if (!nodo) return;
    eliminarArbol(nodo->izquierda);
    eliminarArbol(nodo->derecha);
    delete nodo;
}

std::string A_AVL::toLower(const std::string& s) const {
    std::string r = s;
    for (size_t i = 0; i < r.size(); i++) {
        if (r[i] >= 'A' && r[i] <= 'Z')
            r[i] = (char)(r[i] - 'A' + 'a');
    }
    return r;
}

int A_AVL::altura(NodoAVL* n) const {
    return n ? n->altura : 0;
}

int A_AVL::balance(NodoAVL* n) const {
    return n ? altura(n->izquierda) - altura(n->derecha) : 0;
}

static int maximo(int a, int b) { return a > b ? a : b; }

NodoAVL* A_AVL::rotarDerecha(NodoAVL* y) {
    NodoAVL* x = y->izquierda;
    NodoAVL* T2 = x->derecha;
    x->derecha = y;
    y->izquierda = T2;
    y->altura = 1 + maximo(altura(y->izquierda), altura(y->derecha));
    x->altura = 1 + maximo(altura(x->izquierda), altura(x->derecha));
    return x;
}

NodoAVL* A_AVL::rotarIzquierda(NodoAVL* x) {
    NodoAVL* y = x->derecha;
    NodoAVL* T2 = y->izquierda;
    y->izquierda = x;
    x->derecha = T2;
    x->altura = 1 + maximo(altura(x->izquierda), altura(x->derecha));
    y->altura = 1 + maximo(altura(y->izquierda), altura(y->derecha));
    return y;
}

NodoAVL* A_AVL::rebalancear(NodoAVL* n) {
    n->altura = 1 + maximo(altura(n->izquierda), altura(n->derecha));
    int b = balance(n);

    // Izquierda-Izquierda
    if (b > 1 && balance(n->izquierda) >= 0)
        return rotarDerecha(n);
    // Izquierda-Derecha
    if (b > 1 && balance(n->izquierda) < 0) {
        n->izquierda = rotarIzquierda(n->izquierda);
        return rotarDerecha(n);
    }
    // Derecha-Derecha
    if (b < -1 && balance(n->derecha) <= 0)
        return rotarIzquierda(n);
    // Derecha-Izquierda
    if (b < -1 && balance(n->derecha) > 0) {
        n->derecha = rotarDerecha(n->derecha);
        return rotarIzquierda(n);
    }
    return n;
}

NodoAVL* A_AVL::insertar(NodoAVL* nodo, const std::string& clave, const Cancion& cancion) {
    if (!nodo) return new NodoAVL(clave, cancion);

    if (clave < nodo->clave)
        nodo->izquierda = insertar(nodo->izquierda, clave, cancion);
    else if (clave > nodo->clave)
        nodo->derecha = insertar(nodo->derecha, clave, cancion);
    else {
        // Clave duplicada: actualizar canción
        nodo->cancion = cancion;
        return nodo;
    }
    return rebalancear(nodo);
}

NodoAVL* A_AVL::minimo(NodoAVL* nodo) const {
    NodoAVL* cur = nodo;
    while (cur->izquierda) cur = cur->izquierda;
    return cur;
}

NodoAVL* A_AVL::eliminar(NodoAVL* nodo, const std::string& clave) {
    if (!nodo) return nullptr;

    if (clave < nodo->clave)
        nodo->izquierda = eliminar(nodo->izquierda, clave);
    else if (clave > nodo->clave)
        nodo->derecha = eliminar(nodo->derecha, clave);
    else {
        // Nodo encontrado
        if (!nodo->izquierda || !nodo->derecha) {
            NodoAVL* hijo = nodo->izquierda ? nodo->izquierda : nodo->derecha;
            delete nodo;
            return hijo;
        }
        // Dos hijos: reemplazar con el mínimo del subárbol derecho
        NodoAVL* sucesor = minimo(nodo->derecha);
        nodo->clave = sucesor->clave;
        nodo->cancion = sucesor->cancion;
        nodo->derecha = eliminar(nodo->derecha, sucesor->clave);
    }
    return rebalancear(nodo);
}

void A_AVL::inorden(NodoAVL* nodo, Cancion* arreglo, int maxSize, int& indice) const {
   if (!nodo || indice >= maxSize) return;

    inorden(nodo->izquierda, arreglo, maxSize, indice);

    if (indice < maxSize) {
        arreglo[indice++] = nodo->cancion;
    }
    inorden(nodo->derecha, arreglo, maxSize, indice);
}

int A_AVL::contarNodos(NodoAVL* nodo) const {
    if (!nodo) return 0;
    return 1 + contarNodos(nodo->izquierda) + contarNodos(nodo->derecha);
}

void A_AVL::insertar(const Cancion& cancion) {
    std::string clave = toLower(cancion.getNombreCancion());
    raiz = insertar(raiz, clave, cancion);
}

void A_AVL::eliminar(const std::string& nombreCancion) {
    std::string clave = toLower(nombreCancion);
    raiz = eliminar(raiz, clave);
}

int A_AVL::obtenerEnOrden(Cancion* arreglo, int maxSize) const {
    if (maxSize <= 0) return 0;

    int indice = 0;
    inorden(raiz, arreglo, maxSize, indice);
    return indice;
}

int A_AVL::getCantidad() const {
    return contarNodos(raiz);
}

bool A_AVL::estaVacio() const {
    return raiz == nullptr;
}