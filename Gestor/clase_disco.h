#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <iomanip>
#include <sstream>
#include <istream>
#include <algorithm>
#include "registro_bloque.h"


const int MAX_COLUMN_SIZE = 100;
using namespace std;



// Definición de la lista enlazada
struct Nodo {
    Bloque* bloque;
    Nodo* siguiente;
};

class ListaEnlazada {
public:
    ListaEnlazada() : cabeza(nullptr) {}
    ~ListaEnlazada() {
        // Liberar la memoria ocupada por los bloques creados
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            Nodo* siguiente = actual->siguiente;
            delete actual->bloque;
            delete actual;
            actual = siguiente;
        }
    }
	
    void agregarBloque(Bloque* bloque) {
        Nodo* nuevoNodo = new Nodo;
        nuevoNodo->bloque = bloque;
        nuevoNodo->siguiente = nullptr;

        if (cabeza == nullptr) {
            cabeza = nuevoNodo;
        } else {
            Nodo* actual = cabeza;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevoNodo;
        }
    }
    
    void mostrarContenidoPorID(int id) const {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            if (actual->bloque->id == id) {
                actual->bloque->mostrarContenido();
                return;
            }
            actual = actual->siguiente;
        }
        std::cout << "No se encontro un bloque con el ID especificado." << std::endl;
    }	
    
	int contarElementos() const {
        int count = 0;
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            count++;
            actual = actual->siguiente;
        }
        return count;
    }
    Bloque* obtenerBloquePorID(int id) const {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            if (actual->bloque->get_id() == id) {
                return actual->bloque;
            }
            actual = actual->siguiente;
        }
        return nullptr;
    }
    


public:
    Nodo* cabeza;
};


/////////////////////////////////////////////////////////////////////////


class DiscoDuro {
	
	private:
	    
	    int platos=1;
	    int superficies =platos*2;
	    int pistas = 0;
	    int sectores=0;
	    int bloques =0;
	    int registros=0;
	    
	    int tamSector = 516;//bytes
	    int tamBloque = 40000;//bytes
	    int alm_total;

	public:
		ListaEnlazada bloques_lista;
	
	    DiscoDuro(int alm_total) {this->alm_total=alm_total;}
	    ListaEnlazada& retornar_bloque(){return bloques_lista;}
	    int get_sector(){return sectores;}
	 	int gettam_sector(){return tamSector;}
	 	
		//RETORNAR TAMANIO
		int getFileSize(const std::string& filePath) {
		    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
		    if (!file) {
		        //std::cerr << "Error al abrir el archivo: " << filePath << std::endl;
		        return -1;
		    }
		    std::streampos fileSize = file.tellg();
		    file.close();
		    return static_cast<int>(fileSize);
		}
		
		void guardarRegistrosEnArchivo(const char* registro) {
		    int peso_act = 0;
		    char delimiter = '#';
		
		    std::size_t startPos = 0;
		    std::size_t endPos = std::string(registro).find(delimiter);
		
		    while (endPos != std::string::npos) {
		        std::string subString = std::string(registro).substr(startPos, endPos - startPos);
		
		        peso_act += subString.size() * sizeof(char);
		        startPos = endPos + sizeof(delimiter);
		        endPos = std::string(registro).find(delimiter, startPos);
		    }
		
		    std::ostringstream nombreArchivoStream;
		    nombreArchivoStream << "sectores/sector" << sectores << ".txt";
		    std::string nombreArchivo = nombreArchivoStream.str();
		
		    if (getFileSize(nombreArchivo) + peso_act >=  tamSector) {
		        sectores++;
		        alm_total+=getFileSize(nombreArchivo);
		        peso_act = 0;
		    }
		
		    std::ofstream archivo(nombreArchivo, std::ios::binary | std::ios::app);
		    if (!archivo) {
		        std::cout << "Error al abrir el archivo " << nombreArchivo << std::endl;
		        return;
		    }
		    archivo.write(std::string(registro).c_str(), std::string(registro).size());
		    archivo << std::endl; // Salto de línea después de guardar la línea actual
		    archivo.close();
		}
	
		void guardar_bloque()
		{
		    int id_registro = 0;
		    int peso_act_b = 0;
		    string linea;
		
		    for (int i = 0; i <= sectores; i++)
		    {
		        std::string nombreSector = "sectores/sector" + std::to_string(i) + ".txt";
		        std::ifstream origen_(nombreSector);
		
		        if (!origen_)
		        {
		            std::cout << "Error al abrir el archivo de origen " << nombreSector << std::endl;
		            continue;
		        }
		
		        Bloque *bloque = new Bloque;
		        
		        bloque->set_id(bloques);
		
		        if (getFileSize(nombreSector) + peso_act_b <= tamBloque)
		        {
		            //cout << " \n tamanio: " << getFileSize(nombreSector) + peso_act_b << endl;
		            while (std::getline(origen_, linea))
		            {
		                Registro *registro = new Registro;  // Crear un nuevo puntero a Registro
		                registro->set_id(id_registro);
		                registro->set_idb(bloque->get_id());
		                registro->set_registro(linea);
		                bloque->agregarRegistro(registro);  // Agregar el registro al bloque
		                id_registro++;
		                //cout << "Bloque actual: " << bloques;
		            }
		            bloques_lista.agregarBloque(bloque);  // Agregar el bloque a bloques_lista
		            bloques++;
		        }
		
		        origen_.close();
		    }
		}

	   void abrirArchivoTxt(const char* nombreArchivo) {
	        std::ifstream archivo(nombreArchivo);
	        if (!archivo.is_open()) {
	            //std::cerr << "Error al abrir el archivo: " << nombreArchivo << std::endl;
	            return;
	        }
	
	        std::string linea;
	
	        while (std::getline(archivo, linea)) {
	        	//cout<<linea<<endl;
	            guardarRegistrosEnArchivo(linea.c_str());
	        }
	        guardar_bloque();
	        cout<<endl<<"Cantidad de bloques: "<<bloques_lista.contarElementos()-1<<endl;
	    }
	  
	   
};
