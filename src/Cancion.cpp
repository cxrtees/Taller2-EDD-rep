#include "../include/Cancion.hpp"
using namespace std;

Cancion::Cancion() {
    this->idInterno = 0;
    this->nombreCancion = "";
    this->nombreArtista = "";
    this->nombreAlbum = "";
    this->anio = 0;
    this->duracionSegundos = 0;
    this->ubicacionArchivo = "";
}

Cancion::Cancion(int idInterno, string nombreCancion, string nombreArtista, string nombreAlbum, int anio, int duracionSegundos, string ubicacionArchivo) {
    this->idInterno = idInterno;
    this->nombreCancion = nombreCancion;
    this->nombreArtista = nombreArtista;
    this->nombreAlbum = nombreAlbum;
    this->anio = anio;
    this->duracionSegundos = duracionSegundos;
    this->ubicacionArchivo = ubicacionArchivo;
}

int Cancion::getIdInterno() const {
    return this->idInterno;
}
string Cancion::getNombreCancion() const {
    return this->nombreCancion;
}
string Cancion::getNombreArtista() const {
    return this->nombreArtista;
}
string Cancion::getNombreAlbum() const {
    return this->nombreAlbum;
}
int Cancion::getAnio() const {
    return this->anio;
}
int Cancion::getDuracionSegundos() const {
    return this->duracionSegundos;
}
string Cancion::getUbicacionArchivo() const {
    return this->ubicacionArchivo;
}

void Cancion::setIdInterno(int idInterno) {
    this->idInterno = idInterno;
}
void Cancion::setNombreCancion(string nombreCancion) {
    this->nombreCancion = nombreCancion;
}
void Cancion::setNombreArtista(string nombreArtista) {
    this->nombreArtista = nombreArtista;
}
void Cancion::setNombreAlbum(string nombreAlbum) {
    this->nombreAlbum = nombreAlbum;
}
void Cancion::setAnio(int anio) {
    this->anio = anio;
}
void Cancion::setDuracionSegundos(int duracionSegundos) {
    this->duracionSegundos = duracionSegundos;
}
void Cancion::setUbicacionArchivo(string ubicacionArchivo) {
    this->ubicacionArchivo = ubicacionArchivo;
}

Cancion::~Cancion() {
    // destructor :b
}

