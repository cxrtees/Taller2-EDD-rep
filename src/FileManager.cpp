#include "../include/FileManager.hpp"
#include "../include/Reproductor.hpp"
#include "../include/Cancion.hpp"
#include <fstream>

bool FileManager::existeArchivo(const std::string& nombreArchivo) {
    std::ifstream in(nombreArchivo.c_str());
    return in.good();
}

std::string FileManager::trim(const std::string& s) {
    int i = 0;
    int j = (int)s.size() - 1;
    while (i <= j && (s[i] == ' ' || s[i] == '\t' || s[i] == '\r' || s[i] == '\n')) i++;
    while (j >= i && (s[j] == ' ' || s[j] == '\t' || s[j] == '\r' || s[j] == '\n')) j--;
    if (j < i) return "";
    return s.substr(i, j - i + 1);
}

int FileManager::toIntSafe(const std::string& s, int def) {
    std::string t = trim(s);
    if (t.empty()) return def;
    int sign = 1;
    int i = 0;
    if (t[0] == '-') { sign = -1; i = 1; }
    if (i >= (int)t.size()) return def;

    int val = 0;
    for (; i < (int)t.size(); i++) {
        if (t[i] < '0' || t[i] > '9') return def;
        val = val * 10 + (t[i] - '0');
    }
    return val * sign;
}

bool FileManager::toBoolSafe(const std::string& s, bool def) {
    std::string t = trim(s);
    for (size_t i = 0; i < t.size(); i++) {
        if (t[i] >= 'A' && t[i] <= 'Z') t[i] = (char)(t[i] - 'A' + 'a');
    }
    if (t == "1" || t == "true" || t == "on" || t == "yes") return true;
    if (t == "0" || t == "false" || t == "off" || t == "no") return false;
    return def;
}

char FileManager::detectarDelimitador(const std::string& line) {
    const char delims[5] = {',', '.', ':', ';', '-'};
    int bestCount = -1;
    char best = ',';

    for (int d = 0; d < 5; d++) {
        int c = 0;
        for (size_t i = 0; i < line.size(); i++) if (line[i] == delims[d]) c++;
        if (c > bestCount) { bestCount = c; best = delims[d]; }
    }
    return best;
}

std::string FileManager::escape(const std::string& s) {
    std::string out = "";
    for (size_t i = 0; i < s.size(); i++) {
        char c = s[i];
        if (c == '\\') out += "\\\\";
        else if (c == '|') out += "\\|";
        else if (c == '=') out += "\\=";
        else if (c == '\n') out += "\\n";
        else if (c == '\r') out += "\\r";
        else if (c == '\t') out += "\\t";
        else out += c;
    }
    return out;
}

std::string FileManager::unescape(const std::string& s) {
    std::string out = "";
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '\\' && i + 1 < s.size()) {
            char n = s[i + 1];
            if (n == '\\') out += '\\';
            else if (n == '|') out += '|';
            else if (n == '=') out += '=';
            else if (n == 'n') out += '\n';
            else if (n == 'r') out += '\r';
            else if (n == 't') out += '\t';
            else out += n;
            i++;
        } else {
            out += s[i];
        }
    }
    return out;
}

bool FileManager::cargarCanciones(const std::string& nombreArchivo, Reproductor& reproductor) {
    std::ifstream in(nombreArchivo.c_str());
    if (!in.is_open()) return false;

    reproductor.clearRegistro();

    std::string line;
    bool delimDetected = false;
    char delim = ',';

    while (std::getline(in, line)) {
        line = trim(line);
        if (line.empty()) continue;

        if (!delimDetected) {
            delim = detectarDelimitador(line);
            delimDetected = true;
        }

        std::string parts[7];
        int part = 0;
        std::string cur = "";

        for (size_t i = 0; i < line.size(); i++) {
            if (line[i] == delim) {
                if (part < 7) parts[part] = cur;
                part++;
                cur = "";
            } else {
                cur += line[i];
            }
        }
        if (part < 7) parts[part] = cur;
        part++;

        if (part < 7) continue;

        int id = toIntSafe(parts[0], 0);
        int anio = toIntSafe(parts[4], 0);
        int dur = toIntSafe(parts[5], 0);

        Cancion c(id, trim(parts[1]), trim(parts[2]), trim(parts[3]), anio, dur, trim(parts[6]));
        reproductor.agregarCancionAlRegistro(c);
    }

    return true;
}

bool FileManager::guardarCanciones(const std::string& nombreArchivo, Reproductor& reproductor) {
    std::ofstream out(nombreArchivo.c_str(), std::ios::trunc);
    if (!out.is_open()) return false;

    int n = reproductor.getCantidadCancionesRegistradas();
    for (int i = 0; i < n; i++) {
        Cancion c = reproductor.getCancionRegistrada(i);
        out << c.getIdInterno() << ","
            << c.getNombreCancion() << ","
            << c.getNombreArtista() << ","
            << c.getNombreAlbum() << ","
            << c.getAnio() << ","
            << c.getDuracionSegundos() << ","
            << c.getUbicacionArchivo() << "\n";
    }
    return true;
}

static std::string serializeSong(const Cancion& c) {
    std::string s = "";
    s += std::to_string(c.getIdInterno()); s += "|";
    s += FileManager::escape(c.getNombreCancion()); s += "|";
    s += FileManager::escape(c.getNombreArtista()); s += "|";
    s += FileManager::escape(c.getNombreAlbum()); s += "|";
    s += std::to_string(c.getAnio()); s += "|";
    s += std::to_string(c.getDuracionSegundos()); s += "|";
    s += FileManager::escape(c.getUbicacionArchivo());
    return s;
}

static bool deserializeSong(const std::string& s, Cancion& out) {
    std::string parts[7];
    int part = 0;
    std::string cur = "";
    bool escaped = false;

    for (size_t i = 0; i < s.size(); i++) {
        char c = s[i];
        if (escaped) {
            cur += '\\';
            cur += c;
            escaped = false;
        } else if (c == '\\') {
            escaped = true;
        } else if (c == '|') {
            if (part < 7) parts[part] = cur;
            part++;
            cur = "";
        } else {
            cur += c;
        }
    }
    if (part < 7) parts[part] = cur;
    part++;

    if (part < 7) return false;

    int id = FileManager::toIntSafe(parts[0], 0);
    std::string nombre = FileManager::unescape(parts[1]);
    std::string artista = FileManager::unescape(parts[2]);
    std::string album = FileManager::unescape(parts[3]);
    int anio = FileManager::toIntSafe(parts[4], 0);
    int dur = FileManager::toIntSafe(parts[5], 0);
    std::string ubic = FileManager::unescape(parts[6]);

    out = Cancion(id, nombre, artista, album, anio, dur, ubic);
    return true;
}

bool FileManager::cargarStatus(const std::string& nombreArchivo, Reproductor& reproductor) {
    std::ifstream in(nombreArchivo.c_str());
    if (!in.is_open()) return false;

    // defaults
    reproductor.setHayCancionActual(false);
    reproductor.setEstadoReproduccion("detenido");
    reproductor.setModoAleatorio(false);
    reproductor.setModoRepeticion(0);
    reproductor.clearListaActual();

    std::string line;
    while (std::getline(in, line)) {
        line = trim(line);
        if (line.empty()) continue;

        size_t eq = line.find('=');
        if (eq == std::string::npos) continue;

        std::string key = trim(line.substr(0, eq));
        std::string val = trim(line.substr(eq + 1));

        if (key == "HAY_ACTUAL") {
            reproductor.setHayCancionActual(toBoolSafe(val, false));
        } else if (key == "ESTADO") {
            reproductor.setEstadoReproduccion(val);
        } else if (key == "ALEATORIO") {
            reproductor.setModoAleatorio(toBoolSafe(val, false));
        } else if (key == "REPETICION") {
            reproductor.setModoRepeticion(toIntSafe(val, 0));
        } else if (key == "ACTUAL") {
            Cancion c;
            if (deserializeSong(val, c)) {
                reproductor.setCancionActual(c);
                reproductor.setHayCancionActual(true);
            }
        } else if (key == "PENDING") {
            // PENDING=<songSerialized>
            Cancion c;
            if (deserializeSong(val, c)) {
                reproductor.appendListaActual(c);
            }
        }
    }

    return true;
}

bool FileManager::guardarStatus(const std::string& nombreArchivo, Reproductor& reproductor) {
    std::ofstream out(nombreArchivo.c_str(), std::ios::trunc);
    if (!out.is_open()) return false;

    out << "HAY_ACTUAL=" << (reproductor.tieneCancionActual() ? "1" : "0") << "\n";
    out << "ESTADO=" << reproductor.getEstadoReproduccion() << "\n";
    out << "ALEATORIO=" << (reproductor.getModoAleatorio() ? "1" : "0") << "\n";
    out << "REPETICION=" << reproductor.getModoRepeticion() << "\n";

    if (reproductor.tieneCancionActual()) {
        Cancion c = reproductor.getCancionActual();
        out << "ACTUAL=" << serializeSong(c) << "\n";
    }

    int n = reproductor.getCantidadCancionesEnListaActual();
    for (int i = 0; i < n; i++) {
        Cancion p = reproductor.getCancionEnListaActual(i);
        out << "PENDING=" << serializeSong(p) << "\n";
    }

    return true;
}