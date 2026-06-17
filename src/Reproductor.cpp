#include "../include/Reproductor.hpp"
#include "../include/FileManager.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


void Reproductor::limpiarConsola() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

string Reproductor::leerLinea() {
    string s;
    getline(cin, s);
    return s;
}

Reproductor::Reproductor() {
    this->hayCancionActual = false;
    this->estadoReproduccion = "detenido";
    this->modoAleatorio = false;
    this->modoRepeticion = 0;
    srand((unsigned)time(nullptr));
}


bool Reproductor::tieneCancionActual() { return this->hayCancionActual; }
string Reproductor::getEstadoReproduccion() { return this->estadoReproduccion; }
bool Reproductor::getModoAleatorio() { return this->modoAleatorio; }
int Reproductor::getModoRepeticion() { return this->modoRepeticion; }
Cancion Reproductor::getCancionActual() { return this->cancionActual; }

int Reproductor::getCantidadCancionesRegistradas() { return this->cancionesRegistradas.getSize(); }
int Reproductor::getCantidadCancionesEnListaActual() { return this->listaReproduccionActual.getSize(); }
Cancion Reproductor::getCancionRegistrada(int index) { return this->cancionesRegistradas.get(index); }
Cancion Reproductor::getCancionEnListaActual(int index) { return this->listaReproduccionActual.get(index); }


void Reproductor::setHayCancionActual(bool v) { this->hayCancionActual = v; }
void Reproductor::setEstadoReproduccion(const std::string& e) { this->estadoReproduccion = e; }
void Reproductor::setModoAleatorio(bool v) { this->modoAleatorio = v; }
void Reproductor::setModoRepeticion(int r) {
    this->modoRepeticion = r;
    if (this->modoRepeticion < 0) this->modoRepeticion = 0;
    if (this->modoRepeticion > 2) this->modoRepeticion = 2;
}
void Reproductor::setCancionActual(Cancion c) { this->cancionActual = c; }

void Reproductor::clearListaActual() { this->listaReproduccionActual.clear(); }
void Reproductor::appendListaActual(Cancion c) { this->listaReproduccionActual.insertLast(c); }
void Reproductor::clearRegistro() { this->cancionesRegistradas.clear(); }


void Reproductor::actualizarCicloBaseDesdeListaActual() {
    this->cicloBase.clear();
    for (int i = 0; i < this->listaReproduccionActual.getSize(); i++) {
        this->cicloBase.insertLast(this->listaReproduccionActual.get(i));
    }
}

void Reproductor::recargarListaActualDesdeCicloBase() {
    this->listaReproduccionActual.clear();
    for (int i = 0; i < this->cicloBase.getSize(); i++) {
        this->listaReproduccionActual.insertLast(this->cicloBase.get(i));
    }
}


void Reproductor::agregarCancionAlRegistro(Cancion cancion) {
    this->cancionesRegistradas.insertLast(cancion);
}

void Reproductor::eliminarCancionDelRegistro(int index) {
    if (index < 0 || index >= this->cancionesRegistradas.getSize()) return;
    this->cancionesRegistradas.remove(index);
}

void Reproductor::reproducirCancionDelRegristro(int index) {
    if (index < 0 || index >= this->cancionesRegistradas.getSize()) return;

    if (this->hayCancionActual) {
        this->historial.insertFirst(this->cancionActual);
    }
    this->cancionActual = this->cancionesRegistradas.get(index);
    this->hayCancionActual = true;
    this->estadoReproduccion = "reproduciendo";
}

void Reproductor::agregarCancionAListaActual(int index) {
    if (index < 0 || index >= this->cancionesRegistradas.getSize()) return;
    this->listaReproduccionActual.insertLast(this->cancionesRegistradas.get(index));

    actualizarCicloBaseDesdeListaActual();
}

void Reproductor::togglePlayPause() {
    if (this->cancionesRegistradas.isEmpty()) return;

    if (!this->hayCancionActual) {
        if (this->listaReproduccionActual.isEmpty()) {
            generarListaAleatoriaDesdeRegistro();
        }

        if (!this->listaReproduccionActual.isEmpty()) {
            this->cancionActual = this->listaReproduccionActual.popFirst();
            this->hayCancionActual = true;
            this->estadoReproduccion = "reproduciendo";
        }
        return;
    }

    if (this->estadoReproduccion == "reproduciendo") this->estadoReproduccion = "en pausa";
    else if (this->estadoReproduccion == "en pausa") this->estadoReproduccion = "reproduciendo";
    else this->estadoReproduccion = "reproduciendo";
}

void Reproductor::anterior() {
    if (this->cancionesRegistradas.isEmpty()) return;

   
    if (this->modoRepeticion == 1 && this->hayCancionActual) {
        this->estadoReproduccion = "reproduciendo";
        return;
    }

    if (this->historial.isEmpty()) return;

    if (this->hayCancionActual) {
        this->listaReproduccionActual.insertFirst(this->cancionActual);
    }

    this->cancionActual = this->historial.popFirst();
    this->hayCancionActual = true;
    this->estadoReproduccion = "reproduciendo";
}

void Reproductor::siguiente() {
    if (this->cancionesRegistradas.isEmpty()) return;

    
    if (this->modoRepeticion == 1 && this->hayCancionActual) {
        this->estadoReproduccion = "reproduciendo";
        return;
    }

    
    if (!this->hayCancionActual) {
        if (this->listaReproduccionActual.isEmpty()) {
            generarListaAleatoriaDesdeRegistro();
        }

        if (this->listaReproduccionActual.isEmpty() && this->modoRepeticion == 2 && !this->cicloBase.isEmpty()) {
            recargarListaActualDesdeCicloBase();
            if (this->modoAleatorio) mezclarListaActual();
        }

        if (this->listaReproduccionActual.isEmpty()) return;

        this->cancionActual = this->listaReproduccionActual.popFirst();
        this->hayCancionActual = true;
        this->estadoReproduccion = "reproduciendo";
        return;
    }

    
    if (this->listaReproduccionActual.isEmpty()) {
        if (this->modoRepeticion == 2) {
            // RA: mismo orden anterior
            if (!this->cicloBase.isEmpty()) {
                recargarListaActualDesdeCicloBase();
                
                if (this->modoAleatorio) mezclarListaActual();
            } else {
                
                generarListaAleatoriaDesdeRegistro();
            }
        } else {
            
            generarListaAleatoriaDesdeRegistro();
        }
    }

    if (this->listaReproduccionActual.isEmpty()) return;

    this->historial.insertFirst(this->cancionActual);
    this->cancionActual = this->listaReproduccionActual.popFirst();
    this->hayCancionActual = true;
    this->estadoReproduccion = "reproduciendo";
}

void Reproductor::cambiarModoAleatorio() {
    if (this->cancionesRegistradas.isEmpty()) return;

    bool antes = this->modoAleatorio;
    this->modoAleatorio = !this->modoAleatorio;

    
    if (!antes && this->modoAleatorio) {
        mezclarListaActual();
    }
}

void Reproductor::cambiarModoRepeticion() {
    this->modoRepeticion++;
    if (this->modoRepeticion > 2) this->modoRepeticion = 0;
}


void Reproductor::generarListaAleatoriaDesdeRegistro() {
    this->listaReproduccionActual.clear();

    int n = this->cancionesRegistradas.getSize();
    if (n == 0) return;

    List temp;
    for (int i = 0; i < n; i++) {
        temp.insertLast(this->cancionesRegistradas.get(i));
    }

    
    if (this->hayCancionActual) {
        for (int i = 0; i < temp.getSize(); i++) {
            if (temp.get(i).getIdInterno() == this->cancionActual.getIdInterno()) {
                temp.remove(i);
                break;
            }
        }
    }

    while (!temp.isEmpty()) {
        int len = temp.getSize();
        int k = rand() % len;          
        Cancion picked = temp.popAt(k);
        this->listaReproduccionActual.insertLast(picked);
    }

    
    actualizarCicloBaseDesdeListaActual();
}


void Reproductor::mezclarListaActual() {
    if (this->listaReproduccionActual.getSize() <= 1) return;

    List temp;
    while (!this->listaReproduccionActual.isEmpty()) {
        temp.insertLast(this->listaReproduccionActual.popFirst());
    }

    while (!temp.isEmpty()) {
        int len = temp.getSize();
        int k = rand() % len;
        this->listaReproduccionActual.insertLast(temp.popAt(k));
    }
}


void Reproductor::mostrarLineaActual() {
    if (!this->hayCancionActual) {
        cout << "Reproduccion Detenida\n";
        return;
    }

    string state = this->estadoReproduccion;
    if (state == "detenido") state = "Reproduccion Detenida";

    string flags = "";
    if (this->modoAleatorio) flags += "S";
    if (this->modoRepeticion == 1) {
        if (!flags.empty()) flags += "-";
        flags += "R1";
    } else if (this->modoRepeticion == 2) {
        if (!flags.empty()) flags += "-";
        flags += "RA";
    }

    if (!flags.empty())
        cout << state << " (" << flags << "): " << this->cancionActual.getNombreCancion() << "\n";
    else
        cout << state << ": " << this->cancionActual.getNombreCancion() << "\n";

    cout << "Artista: " << this->cancionActual.getNombreArtista() << "\n";
    cout << "Album: " << this->cancionActual.getNombreAlbum() << " [" << this->cancionActual.getAnio() << "]";
}

void Reproductor::mostrarPantallaPrincipal() {
    mostrarLineaActual();
    cout << "Opciones:\n";
    cout << "W - Reproducir/Pausar\n";
    if (this->historial.getSize() > 0) cout << "Q - Pista Anterior\n";
    cout << "E - Pista Siguiente\n";
    cout << "S - Activar/Desactivar modo aleatorio\n";
    cout << "R - Repeticion (Desactivado/Repetir una/Repetir todas)\n";
    cout << "A - Ver lista de reproduccion actual\n";
    cout << "L - Listado de canciones\n";
    cout << "X - Salir\n";
    cout << "Ingrese Opcion: ";
}

void Reproductor::menuListaActual() {
    if (this->cancionesRegistradas.isEmpty()) return;

    while (true) {
        limpiarConsola();

        if (this->hayCancionActual) {
            cout << "Actual: " << this->cancionActual.getNombreCancion()
                 << " - " << this->cancionActual.getNombreArtista() << "\n";
        } else {
            cout << "Actual: (sin pista)\n";
        }

        cout << "Lista de reproduccion actual:\n";

        if (this->listaReproduccionActual.isEmpty()) {
            cout << "Vacia\n";
            cout << "Opciones:\n";
            cout << "V - Volver al menu principal\n";
            cout << "Ingrese Opcion: ";
            string op = leerLinea();
            if (!op.empty() && (op[0] == 'V' || op[0] == 'v')) return;
            continue;
        }

        for (int i = 0; i < this->listaReproduccionActual.getSize(); i++) {
            Cancion c = this->listaReproduccionActual.get(i);
            cout << (i + 1) << ". " << c.getNombreCancion() << " - " << c.getNombreArtista() << "\n";
        }

        cout << "Opciones:\n";
        cout << "S<num> - Saltar a la cancion seleccionada\n";
        cout << "V - Volver al menu principal\n";
        cout << "Ingrese Opcion: ";

        string op = leerLinea();
        if (op.empty()) continue;

        if (op[0] == 'V' || op[0] == 'v') return;

        if (op[0] == 'S' || op[0] == 's') {
            int pos = 0;
            for (size_t i = 1; i < op.size(); i++) {
                if (op[i] < '0' || op[i] > '9') { pos = 0; break; }
                pos = pos * 10 + (op[i] - '0');
            }
            if (pos <= 0 || pos > this->listaReproduccionActual.getSize()) continue;

            if (this->hayCancionActual) {
                this->historial.insertFirst(this->cancionActual);
            }

            
            for (int i = 1; i < pos; i++) {
                this->listaReproduccionActual.popFirst();
            }

            
            this->cancionActual = this->listaReproduccionActual.popFirst();
            this->hayCancionActual = true;
            this->estadoReproduccion = "reproduciendo";

            return; 
        }
    }
}

void Reproductor::menuCanciones() {
    while (true) {
        limpiarConsola();

        if (this->hayCancionActual) {
            cout << "Actual: " << this->cancionActual.getNombreCancion()
                 << " - " << this->cancionActual.getNombreArtista() << "\n";
        } else {
            cout << "Actual: (sin pista)\n";
        }

        cout << "Canciones registradas:\n";
        if (this->cancionesRegistradas.isEmpty()) {
            cout << "Vacio\n";
        } else {
            for (int i = 0; i < this->cancionesRegistradas.getSize(); i++) {
                Cancion c = this->cancionesRegistradas.get(i);
                cout << (i + 1) << ". " << c.getNombreCancion() << " - " << c.getNombreArtista() << "\n";
            }
        }

        cout << "Opciones:\n";
        cout << "R<num> - Reproducir cancion seleccionada\n";
        cout << "A<num> - Agregar cancion seleccionada al final de la lista actual\n";
        cout << "N - Agregar cancion al registro\n";
        cout << "D<num> - Eliminar cancion seleccionada\n";
        cout << "V - Volver al menu principal\n";
        cout << "Ingrese Opcion: ";

        string op = leerLinea();
        if (op.empty()) continue;

        if (op[0] == 'V' || op[0] == 'v') return;

        
        if (op[0] == 'N' || op[0] == 'n') {
            int newId = 1;
            for (int i = 0; i < this->cancionesRegistradas.getSize(); i++) {
                int id = this->cancionesRegistradas.get(i).getIdInterno();
                if (id >= newId) newId = id + 1;
            }

            string nombre, artista, album, ubic;
            int anio = 0, dur = 0;

            cout << "Nombre cancion: ";
            nombre = leerLinea();
            cout << "Nombre artista: ";
            artista = leerLinea();
            cout << "Nombre album: ";
            album = leerLinea();
            cout << "Anio: ";
            anio = atoi(leerLinea().c_str());
            cout << "Duracion (segundos): ";
            dur = atoi(leerLinea().c_str());
            cout << "Ubicacion archivo: ";
            ubic = leerLinea();

            Cancion c(newId, nombre, artista, album, anio, dur, ubic);
            agregarCancionAlRegistro(c);

            FileManager::guardarCanciones("music_source.txt", *this);
            return;
        }


        char cmd = op[0];
        int num = 0;
        for (size_t i = 1; i < op.size(); i++) {
            if (op[i] < '0' || op[i] > '9') { num = 0; break; }
            num = num * 10 + (op[i] - '0');
        }
        if (num <= 0) continue;

        int index = num - 1;
        if (index < 0 || index >= this->cancionesRegistradas.getSize()) continue;

        if (cmd == 'R' || cmd == 'r') {
            reproducirCancionDelRegristro(index);

            
            this->listaReproduccionActual.clear();
            generarListaAleatoriaDesdeRegistro();

            this->estadoReproduccion = "reproduciendo";
            return;
        }

        if (cmd == 'A' || cmd == 'a') {
            agregarCancionAListaActual(index);
            return;
        }

        if (cmd == 'D' || cmd == 'd') {
            Cancion toDel = this->cancionesRegistradas.get(index);
            int idDel = toDel.getIdInterno();

            eliminarCancionDelRegistro(index);

        
            List nuevaActual;
            for (int i = 0; i < this->listaReproduccionActual.getSize(); i++) {
                Cancion c = this->listaReproduccionActual.get(i);
                if (c.getIdInterno() != idDel) nuevaActual.insertLast(c);
            }
            this->listaReproduccionActual.clear();
            for (int i = 0; i < nuevaActual.getSize(); i++) this->listaReproduccionActual.insertLast(nuevaActual.get(i));

        
            List nuevoHist;
            for (int i = 0; i < this->historial.getSize(); i++) {
                Cancion c = this->historial.get(i);
                if (c.getIdInterno() != idDel) nuevoHist.insertLast(c);
            }
            this->historial.clear();
            for (int i = 0; i < nuevoHist.getSize(); i++) this->historial.insertLast(nuevoHist.get(i));

        
            List nuevoCiclo;
            for (int i = 0; i < this->cicloBase.getSize(); i++) {
                Cancion c = this->cicloBase.get(i);
                if (c.getIdInterno() != idDel) nuevoCiclo.insertLast(c);
            }
            this->cicloBase.clear();
            for (int i = 0; i < nuevoCiclo.getSize(); i++) this->cicloBase.insertLast(nuevoCiclo.get(i));

            if (this->hayCancionActual && this->cancionActual.getIdInterno() == idDel) {
                this->hayCancionActual = false;
                this->estadoReproduccion = "detenido";
            }

            FileManager::guardarCanciones("music_source.txt", *this);
            return;
        }
    }
}


void Reproductor::run() {
    
    FileManager::cargarCanciones("music_source.txt", *this);

    
    if (FileManager::existeArchivo("status.cfg")) {
        FileManager::cargarStatus("status.cfg", *this);
    } else {
        FileManager::guardarStatus("status.cfg", *this);
    }

    if (this->cancionesRegistradas.isEmpty()) {
        this->hayCancionActual = false;
        this->estadoReproduccion = "detenido";
        this->listaReproduccionActual.clear();
        this->historial.clear();
        this->cicloBase.clear();
        FileManager::guardarStatus("status.cfg", *this);
    }

    while (true) {
        limpiarConsola();
        mostrarPantallaPrincipal();
        string op = leerLinea();
        if (op.empty()) continue;

        char c = op[0];
        if (c >= 'a' && c <= 'z') c = char(c - 'a' + 'A');

        if (c == 'W') {
            togglePlayPause();
            FileManager::guardarStatus("status.cfg", *this);
        } else if (c == 'Q') {
            anterior();
            FileManager::guardarStatus("status.cfg", *this);
        } else if (c == 'E') {
            siguiente();
            FileManager::guardarStatus("status.cfg", *this);
        } else if (c == 'S') {
            cambiarModoAleatorio();
            FileManager::guardarStatus("status.cfg", *this);
        } else if (c == 'R') {
            cambiarModoRepeticion();
            FileManager::guardarStatus("status.cfg", *this);
        } else if (c == 'A') {
            menuListaActual();
            FileManager::guardarStatus("status.cfg", *this);
        } else if (c == 'L') {
            menuCanciones();
            FileManager::guardarStatus("status.cfg", *this);
        } else if (c == 'X') {
            FileManager::guardarStatus("status.cfg", *this);
            return;
        }
    }
}