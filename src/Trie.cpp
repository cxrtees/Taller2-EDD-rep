#include "../include/Trie.hpp"
#include <cctype>

// ─── ListaResultados ────────────────────────────────────────────────────────

ListaResultados::~ListaResultados() {
    limpiar();
}

void ListaResultados::agregar(int id) {
    if (contiene(id)) return;
    Nodo* nuevo = new Nodo(id);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
    cantidad++;
}

bool ListaResultados::contiene(int id) const {
    Nodo* cur = cabeza;
    while (cur) {
        if (cur->id == id) return true;
        cur = cur->siguiente;
    }
    return false;
}

void ListaResultados::limpiar() {
    Nodo* cur = cabeza;
    while (cur) {
        Nodo* sig = cur->siguiente;
        delete cur;
        cur = sig;
    }
    cabeza = nullptr;
    cantidad = 0;
}

// ─── A_Trie ─────────────────────────────────────────────────────────────────

A_Trie::A_Trie() {
    raiz = new TrieNode('\0');
}

A_Trie::~A_Trie() {
    eliminarArbol(raiz);
}

std::string A_Trie::toLower(const std::string& s) const {
    std::string result = s;
    for (size_t i = 0; i < result.size(); i++) {
        if (result[i] >= 'A' && result[i] <= 'Z')
            result[i] = (char)(result[i] - 'A' + 'a');
    }
    return result;
}

void A_Trie::eliminarArbol(TrieNode* nodo) {
    if (!nodo) return;
    // Eliminar todos los hijos (primer hijo + hermanos)
    TrieNode* hijo = nodo->primerHijo;
    while (hijo) {
        TrieNode* sig = hijo->hermano;
        eliminarArbol(hijo);
        hijo = sig;
    }
    delete nodo;
}

TrieNode* A_Trie::obtenerOCrearHijo(TrieNode* padre, char c) {
    // Buscar si ya existe el hijo
    TrieNode* cur = padre->primerHijo;
    while (cur) {
        if (cur->caracter == c) return cur;
        cur = cur->hermano;
    }
    // Crear nuevo hijo e insertarlo al frente de la lista de hijos
    TrieNode* nuevo = new TrieNode(c);
    nuevo->hermano = padre->primerHijo;
    padre->primerHijo = nuevo;
    return nuevo;
}

TrieNode* A_Trie::buscarHijo(TrieNode* padre, char c) const {
    TrieNode* cur = padre->primerHijo;
    while (cur) {
        if (cur->caracter == c) return cur;
        cur = cur->hermano;
    }
    return nullptr;
}

void A_Trie::insertarString(const std::string& texto, int idCancion) {
    std::string lower = toLower(texto);
    // Insertar todos los sufijos para permitir búsqueda por subcadena
    for (size_t inicio = 0; inicio < lower.size(); inicio++) {
        TrieNode* actual = raiz;
        for (size_t i = inicio; i < lower.size(); i++) {
            char c = lower[i];
            // Solo indexar caracteres alfanuméricos y espacio
            if (!((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == ' '))
                c = ' ';
            actual = obtenerOCrearHijo(actual, c);
        }
        actual->esFin = true;
        actual->agregarId(idCancion);
    }
}

void A_Trie::eliminarString(const std::string& texto, int idCancion) {
    std::string lower = toLower(texto);
    for (size_t inicio = 0; inicio < lower.size(); inicio++) {
        TrieNode* actual = raiz;
        for (size_t i = inicio; i < lower.size(); i++) {
            char c = lower[i];
            if (!((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == ' '))
                c = ' ';
            actual = buscarHijo(actual, c);
            if (!actual) break;
        }
        if (actual) actual->eliminarId(idCancion);
    }
}

TrieNode* A_Trie::buscarNodo(const std::string& prefijo) const {
    std::string lower = toLower(prefijo);
    TrieNode* actual = raiz;
    for (size_t i = 0; i < lower.size(); i++) {
        char c = lower[i];
        if (!((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == ' '))
            c = ' ';
        actual = buscarHijo(actual, c);
        if (!actual) return nullptr;
    }
    return actual;
}

void A_Trie::recolectarIds(TrieNode* nodo, ListaResultados& resultado) const {
    if (!nodo) return;
    if (nodo->esFin) {
        TrieNode::IdNodo* cur = nodo->listaIds;
        while (cur) {
            resultado.agregar(cur->id);
            cur = cur->siguiente;
        }
    }
    // Recorrer todos los hijos
    TrieNode* hijo = nodo->primerHijo;
    while (hijo) {
        recolectarIds(hijo, resultado);
        hijo = hijo->hermano;
    }
}

void A_Trie::insertar(const Cancion& cancion) {
    insertarString(cancion.getNombreCancion(), cancion.getIdInterno());
    insertarString(cancion.getNombreArtista(), cancion.getIdInterno());
}

void A_Trie::eliminar(const Cancion& cancion) {
    eliminarString(cancion.getNombreCancion(), cancion.getIdInterno());
    eliminarString(cancion.getNombreArtista(), cancion.getIdInterno());
}

void A_Trie::buscar(const std::string& texto, ListaResultados& resultado) const {
    resultado.limpiar();
    if (texto.empty()) return;
    TrieNode* nodo = buscarNodo(texto);
    if (!nodo) return;
    // Recolectar todos los IDs desde este nodo hacia abajo
    recolectarIds(nodo, resultado);
}

bool A_Trie::estaVacio() const {
    return raiz->primerHijo == nullptr;
}