#include "../include/Node.hpp"

Node::Node(const Cancion& dato) {
    this->dato = dato;
    this->next = nullptr;
}

const Cancion& Node::getDato() const {
    return this->dato;
}

Node* Node::getNext() const {
    return this->next;
}

void Node::setDato(const Cancion& dato) {
    this->dato = dato;
}

void Node::setNext(Node* next) {
    this->next = next;
}

Node::~Node() {
}