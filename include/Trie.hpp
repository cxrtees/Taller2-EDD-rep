#pragma once
#include "TrieNode.hpp"
#include "Cancion.hpp"


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

class Trie {
private:
    TrieNode* raiz;

    std::string toLower(const std::string& s) const;

    void insertarString(const std::string& texto, int idCancion);

    void eliminarString(const std::string& texto, int idCancion);

    TrieNode* buscarNodo(const std::string& prefijo) const;

    void recolectarIds(TrieNode* nodo, ListaResultados& resultado) const;

    void eliminarArbol(TrieNode* nodo);

    TrieNode* obtenerOCrearHijo(TrieNode* padre, char c);

    TrieNode* buscarHijo(TrieNode* padre, char c) const;

public:
    Trie();
    ~Trie();

    void insertar(const Cancion& cancion);

    void eliminar(const Cancion& cancion);

    void buscar(const std::string& texto, ListaResultados& resultado) const;

    bool estaVacio() const;
};