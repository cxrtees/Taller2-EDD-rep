#pragma once
#include <string>

class Reproductor; // forward declaration, evita include circular

class FileManager {
public:
    static bool existeArchivo(const std::string& nombreArchivo);

    static bool cargarCanciones(const std::string& nombreArchivo, Reproductor& reproductor);
    static bool guardarCanciones(const std::string& nombreArchivo, Reproductor& reproductor);

    static bool cargarStatus(const std::string& nombreArchivo, Reproductor& reproductor);
    static bool guardarStatus(const std::string& nombreArchivo, Reproductor& reproductor);

    // helpers
    static std::string trim(const std::string& s);
    static char detectarDelimitador(const std::string& line);

    static std::string escape(const std::string& s);
    static std::string unescape(const std::string& s);

    static int toIntSafe(const std::string& s, int def);
    static bool toBoolSafe(const std::string& s, bool def);
};