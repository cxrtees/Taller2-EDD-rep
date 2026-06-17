#pragma once
#include "Cancion.hpp"

class Node {
private:
    Cancion dato;
    Node* next;

public:
    Node(const Cancion& dato);

    const Cancion& getDato() const;
    Node* getNext() const;

    void setDato(const Cancion& dato);
    void setNext(Node* next);

    ~Node();
};