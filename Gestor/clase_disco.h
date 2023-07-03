#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <iomanip>
#include <sstream>
#include <istream>
#include <algorithm>

const int MAX_COLUMN_SIZE = 100;
using namespace std;



class DiscoDuro {
	
	private:
	    
	    int platos=1;
	    int superficies =platos*2;
	    int pistas = 0;
	    int sectores=0;
	    int bloques =0;
	    int registros=0;
	    
	    int tamSector = 516;//bytes
	    int tamBloque = 4000;//bytes
	    int alm_total;
	    
	public:
	    DiscoDuro(int alm_total) {
	  		this->alm_total=alm_total;
	    }
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
		
		void guardarSectores_En_Bloque(){
			int peso_act_b = 0;
		
		    for(int i = 0 ; i<=sectores;i++)
			{
				std::ostringstream nombreArchivoStream_B;
			    nombreArchivoStream_B << "bloques/bloque" << bloques << ".txt";
			    std::string nombreArchivo = nombreArchivoStream_B.str();
			    
			  
			    if (getFileSize(nombreArchivo) + peso_act_b >=  tamBloque) {
			        bloques++;
			        alm_total+=getFileSize(nombreArchivo);
			        peso_act_b = 0;
			    }
			    
			    std::ofstream archivo_B(nombreArchivo, std::ios::binary | std::ios::app);
			    if (!archivo_B) {
			        std::cout << "Error al abrir el archivo " << nombreArchivo << std::endl;
			        return;
			    }
			    std::string nombreSector = "sectores/sector" + std::to_string(i) + ".txt";
			    std::ifstream origen_(nombreSector);
			
			    if (!origen_) {
			        std::cout << "Error al abrir el archivo de origen " << nombreSector << std::endl;
			        continue;
			    }
			    std::string linea;
			    while (std::getline(origen_, linea)) {
			        archivo_B << linea << std::endl;
			    }
			    origen_.close();
			    
			    archivo_B<<endl;
			    
			    archivo_B.close();
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
	        guardarSectores_En_Bloque();
	    }
	  
	   
};
