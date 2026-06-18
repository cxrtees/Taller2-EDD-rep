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
    int reproducciones; // contador de veces reproducida

public:
    Cancion();
    Cancion(int idInterno, string nombreCancion, string nombreArtista,
            string nombreAlbum, int anio, int duracionSegundos,
            string ubicacionArchivo, int reproducciones = 0);

    int getIdInterno() const;
    string getNombreCancion() const;
    string getNombreArtista() const;
    string getNombreAlbum() const;
    int getAnio() const;
    int getDuracionSegundos() const;
    string getUbicacionArchivo() const;
    int getReproducciones() const;

    void setIdInterno(int idInterno);
    void setNombreCancion(string nombreCancion);
    void setNombreArtista(string nombreArtista);
    void setNombreAlbum(string nombreAlbum);
    void setAnio(int anio);
    void setDuracionSegundos(int duracionSegundos);
    void setUbicacionArchivo(string ubicacionArchivo);
    void setReproducciones(int reproducciones);
    void incrementarReproducciones();

    ~Cancion();
};