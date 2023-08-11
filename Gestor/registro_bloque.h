#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <iomanip>
#include <sstream>
#include <istream>
#include <algorithm>
using namespace std;
class Registro{
	public:
		int id_r;
		int id_b;
		string registro;
		void set_id (int id_r){this->id_r = id_r;}
		void set_idb (int id_b){this->id_b = id_b;}
		void set_registro(string r){registro = r;}
		std::string get_registro() const { return registro; }
		int get_id() const { return id_r; }
};


class Bloque
{
public:
    int id;
    int peso = 40000;
    std::vector<Registro*> registros_; 

    void set_id(int id) { this->id = id; }
    int get_id() { return id; }

    void agregarRegistro(Registro* registro) { registros_.push_back(registro); }

    void mostrarContenido() {
        std::cout << "Contenido del bloque con ID " << id << ":" << std::endl;
        for (const auto& registro : registros_) {
            std::cout << registro->registro << std::endl;
        }
    }
/*
    Registro* obtenerRegistro(int indice)  {
        if (indice >= 0 && indice < registros_.size()) {
            return registros_[indice];
        } else {
            // Manejo de error si el índice está fuera de rango
            throw std::out_of_range("indice de registro fuera de rango");
        }
    }*/
    public:
	    Registro* obtenerRegistroPorId(int id_r) {
		    for (const auto& registro : registros_) {
		        if (registro->get_id() == id_r) {
		            return registro;
		        }
		    }
		    
		    // Si no se encuentra el registro con el id_r dado, lanzar una excepción
		    throw std::runtime_error("registro con id_r no encontrado");
		}




};