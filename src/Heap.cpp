#include "../include/Heap.hpp"

// ─── Helpers ────────────────────────────────────────────────────────────────

static std::string heapToLower(const std::string& s) {
    std::string r = s;
    for (size_t i = 0; i < r.size(); i++)
        if (r[i] >= 'A' && r[i] <= 'Z') r[i] = (char)(r[i] - 'A' + 'a');
    return r;
}

// ─── A_HeapCanciones ────────────────────────────────────────────────────────

A_HeapCanciones::A_HeapCanciones(int capacidadInicial)
    : capacidad(capacidadInicial), tamanio(0) {
    datos = new EntradaHeapCancion[capacidad];
}

A_HeapCanciones::~A_HeapCanciones() {
    delete[] datos;
}

std::string A_HeapCanciones::toLower(const std::string& s) const {
    return heapToLower(s);
}

void A_HeapCanciones::expandir() {
    int nuevaCap = capacidad * 2;
    EntradaHeapCancion* nuevo = new EntradaHeapCancion[nuevaCap];
    for (int i = 0; i < tamanio; i++) nuevo[i] = datos[i];
    delete[] datos;
    datos = nuevo;
    capacidad = nuevaCap;
}

// Compara: mayor reproducción primero, desempate alfabético por nombre asc, luego artista
bool A_HeapCanciones::esMayor(const EntradaHeapCancion& a, const EntradaHeapCancion& b) const {
    if (a.reproducciones != b.reproducciones)
        return a.reproducciones > b.reproducciones;
    std::string na = toLower(a.cancion.getNombreCancion());
    std::string nb = toLower(b.cancion.getNombreCancion());
    if (na != nb) return na < nb; // menor alfabéticamente es "mayor" en el heap
    std::string aa = toLower(a.cancion.getNombreArtista());
    std::string ab = toLower(b.cancion.getNombreArtista());
    return aa < ab;
}

void A_HeapCanciones::subirHeap(int i) {
    while (i > 0 && esMayor(datos[i], datos[padre(i)])) {
        EntradaHeapCancion tmp = datos[i];
        datos[i] = datos[padre(i)];
        datos[padre(i)] = tmp;
        i = padre(i);
    }
}

void A_HeapCanciones::bajarHeap(int i) {
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

void A_HeapCanciones::insertar(const EntradaHeapCancion& entrada) {
    if (tamanio >= capacidad) expandir();
    datos[tamanio++] = entrada;
    subirHeap(tamanio - 1);
}

EntradaHeapCancion A_HeapCanciones::extraerMaximo() {
    EntradaHeapCancion max = datos[0];
    datos[0] = datos[--tamanio];
    if (tamanio > 0) bajarHeap(0);
    return max;
}

const EntradaHeapCancion& A_HeapCanciones::verMaximo() const {
    return datos[0];
}

void A_HeapCanciones::actualizarOInsertar(const Cancion& cancion, int reproducciones) {
    // Buscar si ya existe por ID
    for (int i = 0; i < tamanio; i++) {
        if (datos[i].cancion.getIdInterno() == cancion.getIdInterno()) {
            datos[i].reproducciones = reproducciones;
            datos[i].cancion = cancion;
            // Reheapify desde esa posición
            subirHeap(i);
            bajarHeap(i);
            return;
        }
    }
    insertar(EntradaHeapCancion(cancion, reproducciones));
}

void A_HeapCanciones::eliminar(int idCancion) {
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

int A_HeapCanciones::extraerTop(int n, EntradaHeapCancion* resultado) {
    int extraidos = 0;
    while (!estaVacio() && extraidos < n) {
        resultado[extraidos++] = extraerMaximo();
    }
    return extraidos;
}

// ─── A_HeapArtistas ─────────────────────────────────────────────────────────

A_HeapArtistas::A_HeapArtistas(int capacidadInicial)
    : capacidad(capacidadInicial), tamanio(0) {
    datos = new EntradaHeapArtista[capacidad];
}

A_HeapArtistas::~A_HeapArtistas() {
    delete[] datos;
}

std::string A_HeapArtistas::toLower(const std::string& s) const {
    return heapToLower(s);
}

void A_HeapArtistas::expandir() {
    int nuevaCap = capacidad * 2;
    EntradaHeapArtista* nuevo = new EntradaHeapArtista[nuevaCap];
    for (int i = 0; i < tamanio; i++) nuevo[i] = datos[i];
    delete[] datos;
    datos = nuevo;
    capacidad = nuevaCap;
}

bool A_HeapArtistas::esMayor(const EntradaHeapArtista& a, const EntradaHeapArtista& b) const {
    if (a.reproducciones != b.reproducciones)
        return a.reproducciones > b.reproducciones;
    return toLower(a.nombreArtista) < toLower(b.nombreArtista);
}

void A_HeapArtistas::subirHeap(int i) {
    while (i > 0 && esMayor(datos[i], datos[padre(i)])) {
        EntradaHeapArtista tmp = datos[i];
        datos[i] = datos[padre(i)];
        datos[padre(i)] = tmp;
        i = padre(i);
    }
}

void A_HeapArtistas::bajarHeap(int i) {
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

void A_HeapArtistas::insertar(const EntradaHeapArtista& entrada) {
    if (tamanio >= capacidad) expandir();
    datos[tamanio++] = entrada;
    subirHeap(tamanio - 1);
}

EntradaHeapArtista A_HeapArtistas::extraerMaximo() {
    EntradaHeapArtista max = datos[0];
    datos[0] = datos[--tamanio];
    if (tamanio > 0) bajarHeap(0);
    return max;
}

void A_HeapArtistas::actualizarOInsertar(const std::string& artista, int reproducciones) {
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

void A_HeapArtistas::eliminar(const std::string& artista) {
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

int A_HeapArtistas::extraerTop(int n, EntradaHeapArtista* resultado) {
    int extraidos = 0;
    while (!estaVacio() && extraidos < n) {
        resultado[extraidos++] = extraerMaximo();
    }
    return extraidos;
}