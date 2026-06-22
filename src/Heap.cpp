#include "../include/Heap.hpp"

static std::string heapToLower(const std::string& s) {
    std::string r = s;
    for (size_t i = 0; i < r.size(); i++)
        if (r[i] >= 'A' && r[i] <= 'Z') r[i] = (char)(r[i] - 'A' + 'a');
    return r;
}


HeapCanciones::HeapCanciones(int capacidadInicial)
    : capacidad(capacidadInicial), tamanio(0) {
    datos = new EntradaHeapCancion[capacidad];
}

HeapCanciones::~HeapCanciones() {
    delete[] datos;
}

std::string HeapCanciones::toLower(const std::string& s) const {
    return heapToLower(s);
}

void HeapCanciones::expandir() {
    int nuevaCap = capacidad * 2;
    EntradaHeapCancion* nuevo = new EntradaHeapCancion[nuevaCap];
    for (int i = 0; i < tamanio; i++) nuevo[i] = datos[i];
    delete[] datos;
    datos = nuevo;
    capacidad = nuevaCap;
}

bool HeapCanciones::esMayor(const EntradaHeapCancion& a, const EntradaHeapCancion& b) const {
    if (a.reproducciones != b.reproducciones)
        return a.reproducciones > b.reproducciones;
    std::string na = toLower(a.cancion.getNombreCancion());
    std::string nb = toLower(b.cancion.getNombreCancion());
    if (na != nb) return na < nb;
    std::string aa = toLower(a.cancion.getNombreArtista());
    std::string ab = toLower(b.cancion.getNombreArtista());
    return aa < ab;
}

void HeapCanciones::subirHeap(int i) {
    while (i > 0 && esMayor(datos[i], datos[padre(i)])) {
        EntradaHeapCancion tmp = datos[i];
        datos[i] = datos[padre(i)];
        datos[padre(i)] = tmp;
        i = padre(i);
    }
}

void HeapCanciones::bajarHeap(int i) {
    int mayor = i;
    int iz = hijoIzq(i);
    int de = hijoDer(i);
    if (iz < tamanio && esMayor(datos[iz], datos[mayor])) mayor = iz;
    if (de < tamanio && esMayor(datos[de], datos[mayor])) mayor = de;
    if (mayor != i) {
        EntradaHeapCancion tmp = datos[i];
        datos[i] = datos[mayor];
        datos[mayor] = tmp;
        bajarHeap(mayor);
    }
}

void HeapCanciones::insertar(const EntradaHeapCancion& entrada) {
    if (tamanio >= capacidad) expandir();
    datos[tamanio++] = entrada;
    subirHeap(tamanio - 1);
}

EntradaHeapCancion HeapCanciones::extraerMaximo() {
    EntradaHeapCancion max = datos[0];
    datos[0] = datos[--tamanio];
    if (tamanio > 0) bajarHeap(0);
    return max;
}

const EntradaHeapCancion& HeapCanciones::verMaximo() const {
    return datos[0];
}

void HeapCanciones::actualizarOInsertar(const Cancion& cancion, int reproducciones) {
    for (int i = 0; i < tamanio; i++) {
        if (datos[i].cancion.getIdInterno() == cancion.getIdInterno()) {
            datos[i].reproducciones = reproducciones;
            datos[i].cancion = cancion;
            subirHeap(i);
            bajarHeap(i);
            return;
        }
    }
    insertar(EntradaHeapCancion(cancion, reproducciones));
}

void HeapCanciones::eliminar(int idCancion) {
    for (int i = 0; i < tamanio; i++) {
        if (datos[i].cancion.getIdInterno() == idCancion) {
            datos[i] = datos[--tamanio];
            if (i < tamanio) {
                subirHeap(i);
                bajarHeap(i);
            }
            return;
        }
    }
}

int HeapCanciones::extraerTop(int n, EntradaHeapCancion* resultado) {
    int extraidos = 0;
    while (!estaVacio() && extraidos < n) {
        resultado[extraidos++] = extraerMaximo();
    }
    return extraidos;
}

ArbolHeapArtistas::ArbolHeapArtistas(int capacidadInicial)
    : capacidad(capacidadInicial), tamanio(0) {
    datos = new EntradaHeapArtista[capacidad];
}

ArbolHeapArtistas::~ArbolHeapArtistas() {
    delete[] datos;
}

std::string ArbolHeapArtistas::toLower(const std::string& s) const {
    return heapToLower(s);
}

void ArbolHeapArtistas::expandir() {
    int nuevaCap = capacidad * 2;
    EntradaHeapArtista* nuevo = new EntradaHeapArtista[nuevaCap];
    for (int i = 0; i < tamanio; i++) nuevo[i] = datos[i];
    delete[] datos;
    datos = nuevo;
    capacidad = nuevaCap;
}

bool ArbolHeapArtistas::esMayor(const EntradaHeapArtista& a, const EntradaHeapArtista& b) const {
    if (a.reproducciones != b.reproducciones)
        return a.reproducciones > b.reproducciones;
    return toLower(a.nombreArtista) < toLower(b.nombreArtista);
}

void ArbolHeapArtistas::subirHeap(int i) {
    while (i > 0 && esMayor(datos[i], datos[padre(i)])) {
        EntradaHeapArtista tmp = datos[i];
        datos[i] = datos[padre(i)];
        datos[padre(i)] = tmp;
        i = padre(i);
    }
}

void ArbolHeapArtistas::bajarHeap(int i) {
    int mayor = i;
    int iz = hijoIzq(i);
    int de = hijoDer(i);
    if (iz < tamanio && esMayor(datos[iz], datos[mayor])) mayor = iz;
    if (de < tamanio && esMayor(datos[de], datos[mayor])) mayor = de;
    if (mayor != i) {
        EntradaHeapArtista tmp = datos[i];
        datos[i] = datos[mayor];
        datos[mayor] = tmp;
        bajarHeap(mayor);
    }
}

void ArbolHeapArtistas::insertar(const EntradaHeapArtista& entrada) {
    if (tamanio >= capacidad) expandir();
    datos[tamanio++] = entrada;
    subirHeap(tamanio - 1);
}

EntradaHeapArtista ArbolHeapArtistas::extraerMaximo() {
    EntradaHeapArtista max = datos[0];
    datos[0] = datos[--tamanio];
    if (tamanio > 0) bajarHeap(0);
    return max;
}

void ArbolHeapArtistas::actualizarOInsertar(const std::string& artista, int reproducciones) {
    for (int i = 0; i < tamanio; i++) {
        if (toLower(datos[i].nombreArtista) == toLower(artista)) {
            datos[i].reproducciones = reproducciones;
            subirHeap(i);
            bajarHeap(i);
            return;
        }
    }
    insertar(EntradaHeapArtista(artista, reproducciones));
}

void ArbolHeapArtistas::eliminar(const std::string& artista) {
    std::string clave = toLower(artista);
    for (int i = 0; i < tamanio; i++) {
        if (toLower(datos[i].nombreArtista) == clave) {
            datos[i] = datos[--tamanio];
            if (i < tamanio) {
                subirHeap(i);
                bajarHeap(i);
            }
            return;
        }
    }
}

int ArbolHeapArtistas::extraerTop(int n, EntradaHeapArtista* resultado) {
    int extraidos = 0;
    while (!estaVacio() && extraidos < n) {
        resultado[extraidos++] = extraerMaximo();
    }
    return extraidos;
}