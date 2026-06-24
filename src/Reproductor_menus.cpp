#include "../include/Reproductor.hpp"
#include "../include/FileManager.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

void Reproductor::menuListaActual() {
    if (cancionesRegistradas.isEmpty()) return;
    while (true) {
        limpiarConsola();
        if (hayCancionActual)
            cout << "Actual: " << cancionActual.getNombreCancion()
                 << " - " << cancionActual.getNombreArtista() << "\n";
        else
            cout << "Actual: (sin pista)\n";

        cout << "Lista de reproduccion actual:\n";
        if (listaReproduccionActual.isEmpty()) {
            cout << "Vacia\n";
            cout << "Opciones:\nV - Volver al menu principal\nIngrese Opcion: ";
            string op = leerLinea();
            if (!op.empty() && (op[0] == 'V' || op[0] == 'v')) return;
            continue;
        }
        for (int i = 0; i < listaReproduccionActual.getSize(); i++) {
            Cancion c = listaReproduccionActual.get(i);
            cout << (i + 1) << ". " << c.getNombreCancion() << " - " << c.getNombreArtista() << "\n";
        }
        cout << "Opciones:\nS<num> - Saltar a la cancion seleccionada\nV - Volver al menu principal\nIngrese Opcion: ";
        string op = leerLinea();
        if (op.empty()) continue;
        if (op[0] == 'V' || op[0] == 'v') return;
        if (op[0] == 'S' || op[0] == 's') {
            int pos = 0;
            for (size_t i = 1; i < op.size(); i++) {
                if (op[i] < '0' || op[i] > '9') { pos = 0; break; }
                pos = pos * 10 + (op[i] - '0');
            }
            if (pos <= 0 || pos > listaReproduccionActual.getSize()) continue;
            if (hayCancionActual) historial.insertFirst(cancionActual);
            for (int i = 1; i < pos; i++) listaReproduccionActual.popFirst();
            cancionActual = listaReproduccionActual.popFirst();
            hayCancionActual = true;
            estadoReproduccion = "reproduciendo";
            registrarReproduccion(cancionActual);
            return;
        }
    }
}

void Reproductor::menuCanciones() {
    while (true) {
        limpiarConsola();
        if (hayCancionActual)
            cout << "Actual: " << cancionActual.getNombreCancion()
                 << " - " << cancionActual.getNombreArtista() << "\n";
        else
            cout << "Actual: (sin pista)\n";

        cout << "Canciones registradas:\n";
        if (cancionesRegistradas.isEmpty()) {
            cout << "Vacio\n";
        } else {
            for (int i = 0; i < cancionesRegistradas.getSize(); i++) {
                Cancion c = cancionesRegistradas.get(i);
                cout << (i + 1) << ". " << c.getNombreCancion() << " - " << c.getNombreArtista() << "\n";
            }
        }
        cout << "Opciones:\n";
        cout << "R<num> - Reproducir cancion seleccionada\n";
        cout << "A<num> - Agregar cancion al final de la lista actual\n";
        cout << "N      - Agregar nueva cancion al registro\n";
        cout << "D<num> - Eliminar cancion seleccionada\n";
        cout << "V      - Volver al menu principal\n";
        cout << "Ingrese Opcion: ";

        string op = leerLinea();
        if (op.empty()) continue;
        if (op[0] == 'V' || op[0] == 'v') return;

        if (op[0] == 'N' || op[0] == 'n') {
            int newId = 1;
            for (int i = 0; i < cancionesRegistradas.getSize(); i++) {
                int id = cancionesRegistradas.get(i).getIdInterno();
                if (id >= newId) newId = id + 1;
            }
            string nombre, artista, album, ubic;
            int anio = 0, dur = 0;
            cout << "Nombre cancion: "; nombre  = leerLinea();
            cout << "Nombre artista: "; artista = leerLinea();
            cout << "Nombre album: ";   album   = leerLinea();
            cout << "Anio: ";           anio    = atoi(leerLinea().c_str());
            cout << "Duracion (seg): "; dur     = atoi(leerLinea().c_str());
            cout << "Ubicacion archivo: "; ubic = leerLinea();

            Cancion c(newId, nombre, artista, album, anio, dur, ubic, 0);
            cancionesRegistradas.insertLast(c);
            // Agregar a estructuras nuevas
            arbolTrie.insertar(c);
            arbolArtistas.insertar(c);

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
        if (index < 0 || index >= cancionesRegistradas.getSize()) continue;

        if (cmd == 'R' || cmd == 'r') {
            reproducirCancionDelRegristro(index);
            listaReproduccionActual.clear();
            generarListaAleatoriaDesdeRegistro();
            estadoReproduccion = "reproduciendo";
            FileManager::guardarStatus("status.cfg", *this);
            return;
        }
        if (cmd == 'A' || cmd == 'a') {
            agregarCancionAListaActual(index);
            return;
        }
        if (cmd == 'D' || cmd == 'd') {
            Cancion toDel = cancionesRegistradas.get(index);
            int idDel = toDel.getIdInterno();
            eliminarCancionDelRegistro(index);

            auto filtrarLista = [&](List& lista) {
                List nueva;
                for (int i = 0; i < lista.getSize(); i++) {
                    Cancion c = lista.get(i);
                    if (c.getIdInterno() != idDel) nueva.insertLast(c);
                }
                lista.clear();
                for (int i = 0; i < nueva.getSize(); i++) lista.insertLast(nueva.get(i));
            };
            filtrarLista(listaReproduccionActual);
            filtrarLista(historial);
            filtrarLista(cicloBase);

            if (hayCancionActual && cancionActual.getIdInterno() == idDel) {
                hayCancionActual = false;
                estadoReproduccion = "detenido";
            }
            FileManager::guardarCanciones("music_source.txt", *this);
            FileManager::guardarRanking("song_ranking.txt", *this);
            return;
        }
    }
}



void Reproductor::menuBusqueda() {
    while (true) {
        limpiarConsola();
        cout << "Busqueda de canciones\n\n";
        cout << "Buscar canciones que contengan: ";
        string texto = leerLinea();

        if (texto.empty()) return;

        ListaResultados resultado;
        arbolTrie.buscar(texto, resultado);

        limpiarConsola();
        cout << "Busqueda de canciones\n\n";

        if (resultado.cantidad == 0) {
            cout << "No se encontraron canciones con \"" << texto << "\"\n";
            cout << "Opciones:\nF - Repetir busqueda\nV - Volver al menu principal\nIngrese Opcion: ";
            string op = leerLinea();
            if (op.empty() || op[0] == 'V' || op[0] == 'v') return;
            continue;
        }

        const int MAX_RES = 1024;
        Cancion encontradas[MAX_RES];
        int cantEncontradas = 0;

        cout << "Canciones que contienen \"" << texto << "\":\n";
        int n = cancionesRegistradas.getSize();
        for (int i = 0; i < n && cantEncontradas < MAX_RES; i++) {
            Cancion c = cancionesRegistradas.get(i);
            if (resultado.contiene(c.getIdInterno())) {
                encontradas[cantEncontradas++] = c;
                cout << " " << cantEncontradas << ". "
                     << c.getNombreCancion() << " - " << c.getNombreArtista() << "\n";
            }
        }

        cout << "\nOpciones:\n";
        cout << "R<num> - Reproducir cancion seleccionada\n";
        cout << "A<num> - Agregar cancion al final de la lista actual\n";
        cout << "F      - Repetir busqueda con un texto diferente\n";
        cout << "V      - Volver al menu principal\n";
        cout << "Ingrese Opcion: ";

        string op = leerLinea();
        if (op.empty()) continue;
        if (op[0] == 'F' || op[0] == 'f') continue;
        if (op[0] == 'V' || op[0] == 'v') return;

        char cmd = op[0];
        int num = 0;
        for (size_t i = 1; i < op.size(); i++) {
            if (op[i] < '0' || op[i] > '9') { num = 0; break; }
            num = num * 10 + (op[i] - '0');
        }
        if (num <= 0 || num > cantEncontradas) continue;

        Cancion elegida = encontradas[num - 1];
        int idxReg = -1;
        for (int i = 0; i < cancionesRegistradas.getSize(); i++) {
            if (cancionesRegistradas.get(i).getIdInterno() == elegida.getIdInterno()) {
                idxReg = i; break;
            }
        }
        if (idxReg < 0) continue;

        if (cmd == 'R' || cmd == 'r') {
            reproducirCancionDelRegristro(idxReg);
            listaReproduccionActual.clear();
            generarListaAleatoriaDesdeRegistro();
            estadoReproduccion = "reproduciendo";
            FileManager::guardarStatus("status.cfg", *this);
            return;
        }
        if (cmd == 'A' || cmd == 'a') {
            agregarCancionAListaActual(idxReg);
        }
    }
}

void Reproductor::menuTop() {
    volverMenuPrincipalDesdeTop = false;

    while (true) {
        limpiarConsola();
        cout << "Ranking TOP\n\n";
        cout << "C - Top 10 canciones mas escuchadas\n";
        cout << "A - Top 10 artistas mas escuchados\n";
        cout << "X - Salir\n";
        cout << "Ingrese Opcion: ";
        string op = leerLinea();
        if (op.empty()) continue;
        char c = op[0];
        if (c >= 'a' && c <= 'z') c = c - 'a' + 'A';
        if (c == 'C') { 
            menuTopCanciones();
            if (volverMenuPrincipalDesdeTop) return;
         }
        else if (c == 'A') { 
            menuTopArtistas(); 
            if (volverMenuPrincipalDesdeTop) return;
        }
        else if (c == 'X') return;
    }
}

void Reproductor::menuTopCanciones() {
    while (true) {
        limpiarConsola();
        cout << "Ranking TOP 10 Canciones mas escuchadas:\n\n";

        HeapCanciones copia;
        int n = cancionesRegistradas.getSize();
        for (int i = 0; i < n; i++) {
            Cancion c = cancionesRegistradas.get(i);
            if (c.getReproducciones() > 0)
                copia.insertar(EntradaHeapCancion(c, c.getReproducciones()));
        }

        const int MAX_TOP = 10;
        EntradaHeapCancion top[MAX_TOP];
        int cantTop = copia.extraerTop(MAX_TOP, top);

        if (cantTop == 0) {
            cout << "Aun no hay canciones reproducidas.\n";
            cout << "Opciones:\nA - Top 10 artistas\nV - Volver al menu principal\nIngrese Opcion: ";

            string op = leerLinea();
            if (op.empty()) continue;

            if (op[0] == 'V' || op[0] == 'v') {
                volverMenuPrincipalDesdeTop = true;
                return;
            }

            if (op[0] == 'A' || op[0] == 'a') {
                menuTopArtistas();
                if (volverMenuPrincipalDesdeTop) return;
                continue;
            }

            continue;
        }

        for (int i = 0; i < cantTop; i++) {
            cout << (i + 1) << ". [" << setw(2) << top[i].reproducciones << "] "
                 << top[i].cancion.getNombreCancion() << " - "
                 << top[i].cancion.getNombreArtista() << "\n";
        }

        cout << "\nOpciones:\n";
        cout << "R<num> - Reproducir cancion seleccionada\n";
        cout << "A<num> - Agregar cancion al final de la lista actual\n";
        cout << "A      - Top 10 artistas mas escuchados\n";
        cout << "V      - Volver al menu principal\n";
        cout << "Ingrese Opcion: ";

        string op = leerLinea();
        if (op.empty()) continue;

        if ((op[0] == 'A' || op[0] == 'a') && op.size() == 1) {
            menuTopArtistas(); 
            if (volverMenuPrincipalDesdeTop) return;
            continue;
        }
        if (op[0] == 'V' || op[0] == 'v') {
            volverMenuPrincipalDesdeTop = true;
            return;
        }

        char cmd = op[0];
        int num = 0;
        for (size_t i = 1; i < op.size(); i++) {
            if (op[i] < '0' || op[i] > '9') { num = 0; break; }
            num = num * 10 + (op[i] - '0');
        }
        if (num <= 0 || num > cantTop) continue;

        Cancion elegida = top[num - 1].cancion;
        int idxReg = -1;
        for (int i = 0; i < cancionesRegistradas.getSize(); i++) {
            if (cancionesRegistradas.get(i).getIdInterno() == elegida.getIdInterno()) {
                idxReg = i; break;
            }
        }
        if (idxReg < 0) continue;

        if (cmd == 'R' || cmd == 'r') {
            reproducirCancionDelRegristro(idxReg);
            listaReproduccionActual.clear();
            generarListaAleatoriaDesdeRegistro();
            estadoReproduccion = "reproduciendo";
            FileManager::guardarStatus("status.cfg", *this);

            volverMenuPrincipalDesdeTop = true;
            return;
        }
        if (cmd == 'A' || cmd == 'a') {
            agregarCancionAListaActual(idxReg);
        }
    }
}

void Reproductor::menuTopArtistas() {
    while (true) {
        limpiarConsola();
        cout << "Ranking TOP 10 Artistas mas escuchados:\n\n";

        ArbolHeapArtistas copiaArt;
        const int MAX_ART = 2048;
        EntradaArtista arts[MAX_ART];
        int nArts = arbolArtistas.obtenerTodos(arts, MAX_ART);
        for (int i = 0; i < nArts; i++) {
            if (arts[i].reproducciones > 0)
                copiaArt.insertar(EntradaHeapArtista(arts[i].nombre, arts[i].reproducciones));
        }
        ArbolHeapArtistas copiaCorrecta;
        for (int i = 0; i < nArts; i++) {
            int totalRep = 0;
            if (arts[i].canciones) {
                const int MAX_C = 1024;
                Cancion cancArt[MAX_C];
                int nC = arts[i].canciones->obtenerEnOrden(cancArt, MAX_C);
                for (int j = 0; j < nC; j++) {
                    // Buscar el contador actualizado en el registro
                    for (int k = 0; k < cancionesRegistradas.getSize(); k++) {
                        if (cancionesRegistradas.get(k).getIdInterno() == cancArt[j].getIdInterno()) {
                            totalRep += cancionesRegistradas.get(k).getReproducciones();
                            break;
                        }
                    }
                }
            }
            if (totalRep > 0)
                copiaCorrecta.insertar(EntradaHeapArtista(arts[i].nombre, totalRep));
        }

        const int MAX_TOP = 10;
        EntradaHeapArtista top[MAX_TOP];
        int cantTop = copiaCorrecta.extraerTop(MAX_TOP, top);

        if (cantTop == 0) {
            cout << "Aun no hay artistas con reproducciones registradas.\n";
            cout << "Opciones:\nC - Top 10 canciones\nV - Volver al menu principal\nIngrese Opcion: ";

            string op = leerLinea();
            if (op.empty()) continue;

            if (op[0] == 'V' || op[0] == 'v') {
                volverMenuPrincipalDesdeTop = true;
                return;
            }

            if (op[0] == 'C' || op[0] == 'c') {
                menuTopCanciones();
                if (volverMenuPrincipalDesdeTop) return;
                continue;
            }

            continue;
        }
        for (int i = 0; i < cantTop; i++) {
            cout << (i + 1) << ". [" << setw(2) << top[i].reproducciones << "] "
                 << top[i].nombreArtista << "\n";
        }

        cout << "\nOpciones:\n";
        cout << "S<num> - Mostrar canciones del artista\n";
        cout << "C      - Top 10 canciones mas escuchadas\n";
        cout << "V      - Volver al menu principal\n";
        cout << "Ingrese Opcion: ";

        string op = leerLinea();
        if (op.empty()) continue;
        if (op[0] == 'V' || op[0] == 'v') {
            volverMenuPrincipalDesdeTop = true;
            return;
        }

        if ((op[0] == 'C' || op[0] == 'c') && op.size() == 1) {
            menuTopCanciones();
            if (volverMenuPrincipalDesdeTop) return;
            continue;
        }

        if (op[0] == 'S' || op[0] == 's') {
            int num = 0;
            for (size_t i = 1; i < op.size(); i++) {
                if (op[i] < '0' || op[i] > '9') { num = 0; break; }
                num = num * 10 + (op[i] - '0');
            }
            if (num <= 0 || num > cantTop) continue;

            string artistaElegido = top[num - 1].nombreArtista;
            for (int i = 0; i < nArts; i++) {
                auto toLow = [](string s) {
                    for (size_t k = 0; k < s.size(); k++)
                        if (s[k] >= 'A' && s[k] <= 'Z') s[k] = s[k] - 'A' + 'a';
                    return s;
                };
                if (toLow(arts[i].nombre) == toLow(artistaElegido)) {
                    menuCancionesArtista(artistaElegido, arts[i].canciones);
                    if (volverMenuPrincipalDesdeTop) return;
                    break;
                }
            }
        }
    }
}

void Reproductor::menuCancionesArtista(const string& artista, AVL* avlCanciones) {
    while (true) {
        limpiarConsola();
        cout << "Ranking TOP 10 Artistas mas escuchados:\n";
        cout << "Artista: " << artista << "\n\n";

        if (!avlCanciones || avlCanciones->estaVacio()) {
            cout << "(Sin canciones registradas)\n";
            cout << "Opciones:\nV - Volver al listado de TOP 10 artistas\nX - Volver al menu principal\nIngrese Opcion: ";
            string op = leerLinea();
            if (op.empty()) continue;

            if (op[0] == 'X'|| op[0] == 'x') {
                volverMenuPrincipalDesdeTop = true;
                return;
            }
            if (op[0] == 'V' || op[0] == 'v') {
                return;
            }
            continue;
        }

        const int MAX_C = 1024;
        Cancion canciones[MAX_C];
        int nC = avlCanciones->obtenerEnOrden(canciones, MAX_C);

        for (int i = 0; i < nC; i++) {
            cout << (i + 1) << ". " << canciones[i].getNombreCancion() << "\n";
        }

        cout << "\nOpciones:\n";
        cout << "R<num> - Reproducir cancion seleccionada\n";
        cout << "A<num> - Agregar cancion al final de la lista actual\n";
        cout << "V      - Volver al listado de TOP 10 artistas\n";
        cout << "X      - Volver al menu principal\n";
        cout << "Ingrese Opcion: ";

        string op = leerLinea();
        if (op.empty()) continue;
        if (op[0] == 'V' || op[0] == 'v') {
            return;
        }
        if (op[0] == 'X' || op[0] == 'x') {
            volverMenuPrincipalDesdeTop = true;
            return;
        }

        char cmd = op[0];
        int num = 0;
        for (size_t i = 1; i < op.size(); i++) {
            if (op[i] < '0' || op[i] > '9') { num = 0; break; }
            num = num * 10 + (op[i] - '0');
        }
        if (num <= 0 || num > nC) continue;

        Cancion elegida = canciones[num - 1];
        int idxReg = -1;
        for (int i = 0; i < cancionesRegistradas.getSize(); i++) {
            if (cancionesRegistradas.get(i).getIdInterno() == elegida.getIdInterno()) {
                idxReg = i; break;
            }
        }
        if (idxReg < 0) continue;

        if (cmd == 'R' || cmd == 'r') {
            reproducirCancionDelRegristro(idxReg);
            listaReproduccionActual.clear();
            generarListaAleatoriaDesdeRegistro();
            estadoReproduccion = "reproduciendo";
            FileManager::guardarStatus("status.cfg", *this);

            volverMenuPrincipalDesdeTop = true;
            return;
        }
        if (cmd == 'A' || cmd == 'a') {
            agregarCancionAListaActual(idxReg);
        }
    }
}

void Reproductor::run() {
    FileManager::cargarCanciones("music_source.txt", *this);
    FileManager::cargarRanking("song_ranking.txt", *this);

    inicializarEstructuras();

    if (FileManager::existeArchivo("status.cfg"))
        FileManager::cargarStatus("status.cfg", *this);
    else
        FileManager::guardarStatus("status.cfg", *this);

    if (cancionesRegistradas.isEmpty()) {
        hayCancionActual = false;
        estadoReproduccion = "detenido";
        listaReproduccionActual.clear();
        historial.clear();
        cicloBase.clear();
        FileManager::guardarStatus("status.cfg", *this);
    }

    while (true) {
        limpiarConsola();
        mostrarPantallaPrincipal();
        string op = leerLinea();
        if (op.empty()) continue;

        char c = op[0];
        if (c >= 'a' && c <= 'z') c = c - 'a' + 'A';

        if      (c == 'W') { togglePlayPause();        FileManager::guardarStatus("status.cfg", *this); }
        else if (c == 'Q') { anterior();               FileManager::guardarStatus("status.cfg", *this); }
        else if (c == 'E') { siguiente();              FileManager::guardarStatus("status.cfg", *this); }
        else if (c == 'S') { cambiarModoAleatorio();   FileManager::guardarStatus("status.cfg", *this); }
        else if (c == 'R') { cambiarModoRepeticion();  FileManager::guardarStatus("status.cfg", *this); }
        else if (c == 'A') { menuListaActual();        FileManager::guardarStatus("status.cfg", *this); }
        else if (c == 'L') { menuCanciones();          FileManager::guardarStatus("status.cfg", *this); }
        else if (c == 'F') { menuBusqueda(); }
        else if (c == 'T') { menuTop(); }
        else if (c == 'X') { FileManager::guardarStatus("status.cfg", *this); return; }
    }
}