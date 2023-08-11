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





int main() {
	
	
	file gestor;

	char nombreArchivo[20];
	
    gestor.readCSV("titanic.csv","nuevo.txt",232);
    std::cout << "Ingrese el nombre del archivo de texto: (INGRESAR nuevo.txt) ";
    std::cin.getline(nombreArchivo, 20);
    gestor.abrir_file(nombreArchivo);
    gestor.set_paginas();
    int opcion;
    gestor.tree();
    do {
        // Mostrar el menú
        std::cout << "----- Menu -----" << std::endl;
        std::cout << "1. Ejecutar metadata general" << std::endl;
        std::cout << "2. Ejecutar Metadata de un sector" << std::endl;
        std::cout << "4. Obtener registro a traves del buffer (SELECT)" << std::endl;
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
                int num;
                do {
                    std::cout << "Ingrese un numero (o -1 para volver al menu): ";
                    std::cin >> num;
                    if (num != -1) {
                        gestor.llamar_registro(num);
                    }
                } while (num != -1);
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
    
    
 


