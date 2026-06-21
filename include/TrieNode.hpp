#pragma once
#include "Cancion.hpp"


struct TrieNode {
    char caracter;
    TrieNode* primerHijo;
    TrieNode* hermano;

    struct IdNodo {
        int id;
        IdNodo* siguiente;
        IdNodo(int id) : id(id), siguiente(nullptr) {}
    };

    IdNodo* listaIds;
    bool esFin;

    TrieNode(char c);
    ~TrieNode();

    void agregarId(int id);
    bool tieneId(int id) const;
    void eliminarId(int id);
};