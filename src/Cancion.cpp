#include "../include/Cancion.hpp"

Cancion::Cancion()
    : idInterno(0), nombreCancion(""), nombreArtista(""),
      nombreAlbum(""), anio(0), duracionSegundos(0),
      ubicacionArchivo(""), reproducciones(0) {}

Cancion::Cancion(int idInterno, string nombreCancion, string nombreArtista,
                 string nombreAlbum, int anio, int duracionSegundos,
                 string ubicacionArchivo, int reproducciones)
    : idInterno(idInterno), nombreCancion(nombreCancion),
      nombreArtista(nombreArtista), nombreAlbum(nombreAlbum),
      anio(anio), duracionSegundos(duracionSegundos),
      ubicacionArchivo(ubicacionArchivo), reproducciones(reproducciones) {}

int    Cancion::getIdInterno()        const { return idInterno; }
string Cancion::getNombreCancion()    const { return nombreCancion; }
string Cancion::getNombreArtista()    const { return nombreArtista; }
string Cancion::getNombreAlbum()      const { return nombreAlbum; }
int    Cancion::getAnio()             const { return anio; }
int    Cancion::getDuracionSegundos() const { return duracionSegundos; }
string Cancion::getUbicacionArchivo() const { return ubicacionArchivo; }
int    Cancion::getReproducciones()   const { return reproducciones; }

void Cancion::setIdInterno(int v)             { idInterno = v; }
void Cancion::setNombreCancion(string v)      { nombreCancion = v; }
void Cancion::setNombreArtista(string v)      { nombreArtista = v; }
void Cancion::setNombreAlbum(string v)        { nombreAlbum = v; }
void Cancion::setAnio(int v)                  { anio = v; }
void Cancion::setDuracionSegundos(int v)      { duracionSegundos = v; }
void Cancion::setUbicacionArchivo(string v)   { ubicacionArchivo = v; }
void Cancion::setReproducciones(int v)        { reproducciones = v; }
void Cancion::incrementarReproducciones()     { reproducciones++; }

Cancion::~Cancion() {}