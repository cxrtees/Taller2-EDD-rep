#pragma once
#include "TrieNode.hpp"
#include "Cancion.hpp"

// Lista simple de IDs de resultados (sin STL)
struct ListaResultados {
    struct Nodo {
        int id;
        Nodo* siguiente;
        Nodo(int id) : id(id), siguiente(nullptr) {}
    };
    Nodo* cabeza;
    int cantidad;

    ListaResultados() : cabeza(nullptr), cantidad(0) {}
    ~ListaResultados();

    void agregar(int id);
    bool contiene(int id) const;
    void limpiar();
};

// Árbol Trie para búsqueda eficiente de subcadenas
// Indexa cada sufijo de los strings de nombre y artista
class A_Trie {
private:
    TrieNode* raiz;

    // Convierte string a minúsculas para búsqueda case-insensitive
    std::string toLower(const std::string& s) const;

    // Inserta un string completo desde la raíz
    void insertarString(const std::string& texto, int idCancion);

    // Elimina un string de la raíz
    void eliminarString(const std::string& texto, int idCancion);

    // Busca un nodo correspondiente al prefijo dado
    TrieNode* buscarNodo(const std::string& prefijo) const;

    // Recorre el subárbol a partir de un nodo y recolecta todos los IDs
    void recolectarIds(TrieNode* nodo, ListaResultados& resultado) const;

    // Elimina recursivamente los nodos del Trie
    void eliminarArbol(TrieNode* nodo);

    // Obtiene o crea el hijo con carácter c
    TrieNode* obtenerOCrearHijo(TrieNode* padre, char c);

    // Busca el hijo con carácter c (sin crear)
    TrieNode* buscarHijo(TrieNode* padre, char c) const;

public:
    A_Trie();
    ~A_Trie();

    // Inserta todos los sufijos de nombre y artista de una canción
    void insertar(const Cancion& cancion);

    // Elimina todos los sufijos de nombre y artista de una canción
    void eliminar(const Cancion& cancion);

    // Busca canciones cuyo nombre o artista contengan el texto dado
    // Llena resultado con los IDs encontrados
    void buscar(const std::string& texto, ListaResultados& resultado) const;

    bool estaVacio() const;
};