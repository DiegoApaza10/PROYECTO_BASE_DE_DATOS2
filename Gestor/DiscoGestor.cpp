#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <iomanip>
#include <sstream>
#include <istream>
#include <algorithm>
#include "clase_file.h"

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
    std::cout << "Ingrese el nombre del archivo de texto: ";
    std::cin.getline(nombreArchivo, 20);
    gestor.abrir_file(nombreArchivo);
 	int opcion;
    do {
        // Mostrar el menú
        std::cout << "----- Menu -----" << std::endl;
        std::cout << "1. Ejecutar meta_1" << std::endl;
        std::cout << "2. Ejecutar Meta2" << std::endl;
        std::cout << "3. Ejecutar Meta3" << std::endl;
        std::cout << "4. Salir" << std::endl;
        std::cout << "----------------" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        // Realizar la acción según la opción seleccionada
        switch (opcion) {
            case 1:
                gestor.meta_1();
                break;
            case 2:
                gestor.Meta2();
                break;
            case 3: {
                int num;
                std::cout << "Ingrese un numero: ";
                std::cin >> num;
                gestor.Meta3(num);
                break;
            }
            case 4:
                std::cout << "Saliendo..." << std::endl;
                break;
            default:
                std::cout << "Opción invalida. Intente nuevamente." << std::endl;
                break;
        }

        std::cout << std::endl;
    } while (opcion != 4);

    return 0;
}



