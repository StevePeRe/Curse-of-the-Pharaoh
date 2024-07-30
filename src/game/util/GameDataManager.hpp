#pragma once
// Read txt
#include <fstream>
#include <JSON/src/json.hpp>

// libs
#include <iostream>
#include <string>

using json = nlohmann::json;

struct GameDataManager
{
    explicit GameDataManager() = default;
    
    // escribe los datos pasados en la ruta pasada
    void escribirJSON(const json& datos, const std::string& ruta) {
        std::ofstream archivo(ruta);
        if (archivo.is_open()) {
            archivo << datos.dump(4);
            archivo.close();
            // std::cout << "JSON guardado en el archivo exitosamente." << std::endl;
        } else {
            // std::cerr << "Error al abrir el archivo." << std::endl;
        }
    }
    
    // lee los datos de un JSON y los devuelve en otro json
    json leerJSON(const std::string& ruta) {
        // leerlo
        json datos = json();
        if(!hasContent(ruta)){
            std::ifstream archivo(ruta);
            if (archivo.is_open()) {
                // std::cerr << "Datos leidos exitosamente" << std::endl;
                json datos;
                archivo >> datos;
                archivo.close();
                return datos;
            } else {
                // std::cerr << "Error al abrir el archivo." << std::endl;
            }
        }
        return datos; // Devuelve un JSON vacío en caso de error
    }

    bool hasContent(const std::string& ruta){
        bool dev = false;
        // Abrir el archivo JSON en modo lectura
        std::ifstream archivo_entrada(ruta);

        // Comprobar si el archivo está vacío
        archivo_entrada.seekg(0, std::ios::end);
        if (archivo_entrada.tellg() == 0) {
            // std::cout << "El archivo está vacío." << std::endl;
            dev = true;
        }

        // Cerrar el archivo
        archivo_entrada.close();

        return dev;
    }

    private:

};
