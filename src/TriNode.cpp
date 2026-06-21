#include "../include/TrieNode.hpp"

TrieNode::TrieNode(char c)
    : caracter(c), primerHijo(nullptr), hermano(nullptr),
      listaIds(nullptr), esFin(false) {}

TrieNode::~TrieNode() {
    IdNodo* cur = listaIds;
    while (cur) {
        IdNodo* sig = cur->siguiente;
        delete cur;
        cur = sig;
    }
}

void TrieNode::agregarId(int id) {
    if (tieneId(id)) return;
    IdNodo* nuevo = new IdNodo(id);
    nuevo->siguiente = listaIds;
    listaIds = nuevo;
}

bool TrieNode::tieneId(int id) const {
    IdNodo* cur = listaIds;
    while (cur) {
        if (cur->id == id) return true;
        cur = cur->siguiente;
    }
    return false;
}

void TrieNode::eliminarId(int id) {
    IdNodo* cur = listaIds;
    IdNodo* prev = nullptr;
    while (cur) {
        if (cur->id == id) {
            if (prev) prev->siguiente = cur->siguiente;
            else listaIds = cur->siguiente;
            delete cur;
            return;
        }
        prev = cur;
        cur = cur->siguiente;
    }
}