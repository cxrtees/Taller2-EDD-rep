#pragma once
#include <string>
using namespace std;

class Cancion { 
private:
    int idInterno;
    string nombreCancion;
    string nombreArtista;
    string nombreAlbum;
    int anio;
    int duracionSegundos;
    string ubicacionArchivo;

public:
    Cancion();
    Cancion(int idInterno, string nombreCancion, string nombreArtista, string nombreAlbum, int anio, int duracionSegundos, string ubicacionArchivo);
   
    int getIdInterno() const;
    string getNombreCancion() const;
    string getNombreArtista() const;
    string getNombreAlbum() const;
    int getAnio() const;
    int getDuracionSegundos() const;
    string getUbicacionArchivo() const;

    void setIdInterno(int idInterno);
    void setNombreCancion(string nombreCancion);
    void setNombreArtista(string nombreArtista);
    void setNombreAlbum(string nombreAlbum);
    void setAnio(int anio);
    void setDuracionSegundos(int duracionSegundos);
    void setUbicacionArchivo(string ubicacionArchivo);

    ~Cancion();

};