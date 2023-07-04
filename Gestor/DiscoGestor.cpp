#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <iomanip>
#include <sstream>
#include <istream>
#include <algorithm>
#include <unordered_map>
#include "clase_file.h"
#include "Buffer_Buffer_Manager.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
    switch (dataType) {
        case DataType::Integer:
            std::cout << "El valor ingresado es un entero." << std::endl;
            break;
        case DataType::Float:
            std::cout << "El valor ingresado es un flotante." << std::endl;
            break;
        case DataType::String:
            std::cout << "El valor ingresado es una cadena." << std::endl;
            break;
    }
*/





int main() {
	
	
	file gestor;

	char nombreArchivo[20];
	
    gestor.readCSV("titanic.csv","nuevo.txt",232);
    std::cout << "Ingrese el nombre del archivo de texto: (INGRESAR nuevo.txt) ";
    std::cin.getline(nombreArchivo, 20);
    gestor.abrir_file(nombreArchivo);
    int opcion;
    do {
        // Mostrar el menú
        std::cout << "----- Menu -----" << std::endl;
        std::cout << "1. Ejecutar metadata general" << std::endl;
        std::cout << "2. Ejecutar Metadata de un sector" << std::endl;
        std::cout << "4. Buffer Manager" << std::endl;
        std::cout << "5. Salir" << std::endl;
        std::cout << "----------------" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        // Realizar la acción según la opción seleccionada
        switch (opcion) {
            case 1:
                gestor.meta_1();
                break;
            case 3:
                gestor.Meta2();
                break;
            case 2: {
                int num;
                std::cout << "Ingrese un numero: ";
                std::cin >> num;
                gestor.Meta3(num);
                break;
            }
            case 4: {
                int bufferSize;
                std::cout << "Ingrese el tamanio del buffer: ";
                std::cin >> bufferSize;

                BufferManager bufferManager(bufferSize);

                int opcionBuffer;
                do {
                    // Mostrar el menú del Buffer Manager
                    std::cout << "----- Menu Buffer Manager -----" << std::endl;
                    std::cout << "1. Solicitud de pagina" << std::endl;
                    std::cout << "2. Mostrar pagina" << std::endl;
                    std::cout << "3. Volver al menu principal" << std::endl;
                    std::cout << "-------------------------------" << std::endl;
                    std::cout << "Seleccione una opcion: ";
                    std::cin >> opcionBuffer;

                    switch (opcionBuffer) {
                        case 1: {
                            int numeroBloque;
                            std::cout << "Ingrese el numero de bloque: ";
                            std::cin >> numeroBloque;
                            bufferManager.solicitud(numeroBloque);
                            break;
                        }
                        case 2: {
                            int numeroBloque;
                            std::cout << "Ingrese el numero de bloque: ";
                            std::cin >> numeroBloque;
                            bufferManager.mostrarPagina(numeroBloque);
                            break;
                        }
                        case 3:
                            std::cout << "Volviendo al menu principal..." << std::endl;
                            break;
                        default:
                            std::cout << "Opción invalida. Intente nuevamente." << std::endl;
                            break;
                    }

                    std::cout << std::endl;
                } while (opcionBuffer != 3);

                break;
            }
            case 5:
                std::cout << "Saliendo..." << std::endl;
                break;
            default:
                std::cout << "Opción inválida. Intente nuevamente." << std::endl;
                break;
        }

        std::cout << std::endl;
    } while (opcion != 5);

    return 0;
}
    
    
 


