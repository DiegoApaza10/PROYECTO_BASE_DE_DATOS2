#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <iomanip>
#include <sstream>
#include <istream>
#include <algorithm>
#include "clase_disco.h"
using namespace std;
class Pagina {
	private:
		int tamanioP=4000;
    	vector<ifstream> sectores_alm;
};


// Crear un disco duro con 2 platos, 2 superficies, 2 pistas, 2 sectores y un tamaño de sector de 256 bytes
class file{
	private:
		DiscoDuro disco;
		Pagina pagina;
		int sectores;
		int paginas;
	public:
		file() : disco(1000) {}
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
		
		void abrir_file(const char* nombreArchivo){disco.abrirArchivoTxt(nombreArchivo);}
		int sectores_c(){return disco.get_sector();} 
		int tam_sec(){return disco.gettam_sector();}
	///////////////////////////METADATA/////////////////////////////////////
		void meta_1(){
	        std::cout << "Informacion del disco duro:" << std::endl;
	        std::cout << "Numero de sectores: " << disco.get_sector()<< std::endl;
	        std::cout << "Tamanio GENERAL de sector: " << disco.gettam_sector() << std::endl;
	        sectores=disco.get_sector();
	        //pagina.num_sectores = disco.get_sector();
	    }
		void Meta2() {
			for (int i = 0; i <= sectores; i++) {
		        std::ostringstream nombreArchivoStream;
		        nombreArchivoStream << "sectores/sector" << i << ".txt";
		        std::string nombreArchivo = nombreArchivoStream.str();
		
		        std::cout << "Metadata del archivo " << nombreArchivo << ":" << std::endl;
		        int fileSize = getFileSize(nombreArchivo);
		        	if (fileSize != -1) {
		            std::cout << "Tamanio REAL del archivo: " << fileSize << " bytes" << std::endl;
		            std::ifstream archivo(nombreArchivo);
		            if (archivo) {
		                int numRegistros = std::count(std::istreambuf_iterator<char>(archivo), std::istreambuf_iterator<char>(), '\n');
		                    std::cout << "Numero de registros: " << numRegistros << std::endl;
		                } else {
		                    std::cout << "Error al abrir el archivo " << nombreArchivo << std::endl;
		                }
		            } else {
		                std::cout << "Error al obtener el tamanio del archivo " << nombreArchivo << std::endl;
		            }
		        std::cout << std::endl;
		    }
		}
		void Meta3(int numSector) {
	    	std::ostringstream nombreArchivoStream;
		    nombreArchivoStream << "sectores/sector" << numSector << ".txt";
		    std::string nombreArchivo = nombreArchivoStream.str();
		
		    std::cout << "Metadata del archivo " << nombreArchivo << ":" << std::endl;
		    int fileSize = getFileSize(nombreArchivo);
		    if (fileSize != -1) {
		        std::cout << "Tamanio del archivo: " << fileSize << " bytes" << std::endl;
		
		        std::ifstream archivo(nombreArchivo);
		        if (archivo) {
		            int numRegistros = std::count(std::istreambuf_iterator<char>(archivo), std::istreambuf_iterator<char>(), '\n');
		            std::cout << "Numero de registros: " << numRegistros << std::endl;
		
		            archivo.clear();
		            archivo.seekg(0, std::ios::beg); // Volver al principio del archivo
		
		            std::cout << "Contenido del sector:" << std::endl;
		            std::string linea;
		            while (std::getline(archivo, linea)) {
		                std::cout << linea << std::endl;
		            }
		        } else {
		            std::cout << "Error al abrir el archivo " << nombreArchivo << std::endl;
		        }
		    } else {
		        std::cout << "Error al obtener el tamaño del archivo " << nombreArchivo << std::endl;
		    }
	    }
//////////////////////////////////////////////////////////////////////////////////////////
		const int MAX_COLUMN_SIZE = 100;
		int leer_tamanio(const char* esquema_file1)
		{
			int tamanio=0;
			std::ifstream esquema_file(esquema_file1);
			string linea;
			std::getline(esquema_file, linea);
			
			size_t posInicio = linea.find('[');
		    size_t posFin = linea.find(']');
		
		    while (posInicio != std::string::npos && posFin != std::string::npos) {
		        string contenido = linea.substr(posInicio + 1, posFin - posInicio - 1);
		        if(contenido=="int")
				{
		        	tamanio+=4;
				}else if(contenido=="float")
				{
					tamanio+=8;
				}else if(contenido=="string")
				{
					tamanio+=40;
				}
		        posInicio = linea.find('[', posFin);
		        posFin = linea.find(']', posInicio);
		    }
		    esquema_file.close();
		    return tamanio;
		}
	
		void readCSV(const char* EnFile, const char* SaFile, int tam = 232) {
		    std::ifstream inFile(EnFile);
		    std::ofstream outFile(SaFile);
		
		    char line[tam];
		    char column[MAX_COLUMN_SIZE];
		    bool insideQuotes = false;
		    bool columnIsEmpty = true;
		
		    while (inFile.getline(line, sizeof(line))) {
		        char* ptr = line;
		        int columnIndex = 0;
		
		        while (*ptr != '\0') {
		            if (*ptr == '"') {
		                insideQuotes = !insideQuotes; // Cambiar el estado dentro/fuera de las comillas
		            } else if (*ptr == ',' && !insideQuotes) {
		                if (columnIsEmpty) {
		                    column[columnIndex++] = '-';
		                }
		                column[columnIndex] = '\0';
		                outFile << column << "#";
		                columnIndex = 0;
		                columnIsEmpty = true;
		            } else {
		                column[columnIndex++] = *ptr;
		                if (*ptr != ' ') {
		                    columnIsEmpty = false;
		                }
		            }
		            ptr++;
		        }
		
		        if (columnIsEmpty) {
		            column[columnIndex++] = '-';
		        }
		        column[columnIndex] = '\0';
		        outFile << column << std::endl;
		    }
		
		    inFile.close();
		    outFile.close();
		
		    std::cout << "Archivo convertido correctamente." << std::endl;
		}
		
		
		void crearEsquema(const char* nombreTabla) {
		    ifstream archivoCSV(nombreTabla);
		    if (!archivoCSV) {
		        cout << "No se pudo abrir el archivo '" << nombreTabla << "'." << endl;
		        return;
		    }
		
		    const int TAMANIO_LINEA = 100;
		    char linea[TAMANIO_LINEA];
		    if (archivoCSV.getline(linea, TAMANIO_LINEA)) {
		        istringstream iss(linea);
		        char columna[TAMANIO_LINEA];
		        char esquema[TAMANIO_LINEA * 3] = {0};  // El doble de tamaño para almacenar "#"
		
		        size_t esquemaPos = 0;
		        size_t numColumnas = 0;
		
		        while (iss.getline(columna, TAMANIO_LINEA, ',')) {
		            char dato[TAMANIO_LINEA];
		            if (archivoCSV.getline(dato, TAMANIO_LINEA, ',')) {
		                size_t columnaLen = strlen(columna);
		                size_t datoLen = strlen(dato);
		
		                strncpy(esquema + esquemaPos, columna, columnaLen);
		                esquemaPos += columnaLen;
		
		                esquema[esquemaPos] = '[';
		                esquemaPos++;
		
		                // tipo de dato
		                if (isdigit(dato[0])) {
		                    if (strchr(dato, '.') != nullptr)
		                        strncat(esquema, "float", TAMANIO_LINEA - strlen(esquema) - 1);
		                    else
		                    	strncat(esquema, "int", TAMANIO_LINEA - strlen(esquema) - 1);
		                        //strncat(esquema, "integer", 7);
		                } else {
		                	strncat(esquema, "string", TAMANIO_LINEA - strlen(esquema) - 1);
		                    //strncat(esquema, "string", 6);
		                }
		
		                esquemaPos += strlen(esquema + esquemaPos);
		
		                esquema[esquemaPos] = ']';
		                esquemaPos++;
		
		                esquema[esquemaPos] = '#';
		                esquemaPos++;
		
		                numColumnas++;
		            } else {
		                cout << "Error al leer los datos de la columna '" << columna << "' en el archivo '" << nombreTabla << "'." << endl;
		                archivoCSV.close();
		                return;
		            }
		        }
		
		        if (numColumnas > 0) {
		            esquema[esquemaPos - 1] = '\0';  // Eliminar el último '#'
		
		            char nombreEsquema[TAMANIO_LINEA];
		            strncpy(nombreEsquema, nombreTabla, TAMANIO_LINEA);
		            strncat(nombreEsquema, "_esquema.txt", TAMANIO_LINEA - strlen(nombreTabla) - 1);
		
		            ofstream archivoEsquema(nombreEsquema);
		            if (archivoEsquema.is_open()) {
		                archivoEsquema.write(esquema, esquemaPos);
		                archivoEsquema.close();
		                cout << "Se generó el archivo de esquema '" << nombreEsquema << "' correctamente." << endl;
		            } else {
		                cout << "No se pudo crear el archivo de esquema '" << nombreEsquema << "'." << endl;
		            }
		        } else {
		            cout << "No se encontraron columnas en el archivo '" << nombreTabla << "'." << endl;
		        }
		    } else {
		        cout << "El archivo '" << nombreTabla << "' está vacío." << endl;
		    }
		
		    archivoCSV.close();
		}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		enum class DataType {
		    Integer,
		    Float,
		    String
		};
		
		DataType identifyDataType(const std::string& input) {
		    std::istringstream iss(input);
		    int intValue;
		    float floatValue;
		    
		    if (iss >> intValue && iss.eof()) {
		        return DataType::Integer;
		    }
		    
		    iss.clear();
		    
		    if (iss >> floatValue && iss.eof()) {
		        return DataType::Float;
		    }
		    
		    return DataType::String;
		}
		
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

};