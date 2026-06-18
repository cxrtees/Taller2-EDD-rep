#pragma once
#include "Cancion.hpp"

// Nodo del árbol Trie
// Cada nodo representa un carácter y contiene hijos enlazados manualmente
struct TrieNode {
    char caracter;
    TrieNode* primerHijo;   // primer hijo (lista de hijos enlazados)
    TrieNode* hermano;      // siguiente hermano (lista enlazada de hermanos)

    // Lista enlazada simple de IDs de canciones que terminan en este nodo
    struct IdNodo {
        int id;
        IdNodo* siguiente;
        IdNodo(int id) : id(id), siguiente(nullptr) {}
    };

    IdNodo* listaIds;   // canciones cuyos strings indexados terminan aquí
    bool esFin;         // marca fin de una cadena indexada

    TrieNode(char c);
    ~TrieNode();

    void agregarId(int id);
    bool tieneId(int id) const;
    void eliminarId(int id);
};