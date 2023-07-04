#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <algorithm>
class BufferPage {
public:
    int numero_bloque_solicitado;
    int bloque_correspondiente;
    std::vector<std::string> contenido;

public:
    BufferPage(int numero) : numero_bloque_solicitado(numero) {}

    void cargarPaginaDesdeArchivo() {
         std::string nombreArchivo = "bloques/bloque" + std::to_string(numero_bloque_solicitado) + ".txt";
	    std::ifstream archivo(nombreArchivo);
	    if (!archivo.is_open()) {
	        std::cout << "El archivo " << nombreArchivo << " no existe." << std::endl;
	        return;
	    }
    
        std::string linea;
        while (std::getline(archivo, linea)) {
            contenido.push_back(linea);
        }
    }
	void set(int num){
		bloque_correspondiente=num;
	}
    void mostrarContenido() {
        for (auto& linea : contenido) {
            std::cout << linea << std::endl;
        }
    }
};

class BufferManager {
private:
    int bufferSize;
    std::vector<BufferPage*> buffer;
    int actual = 0;

public:
    BufferManager(int size) : bufferSize(size) {}

	void solicitud(int numero_bloque) {
	    BufferPage* newPage = new BufferPage(numero_bloque);
	    newPage->cargarPaginaDesdeArchivo();
	    newPage->set(numero_bloque);
	    
	    if (actual < bufferSize) {
	        buffer.push_back(newPage);
	        actual++;
	        std::cout << "Pagina cargada en el buffer: " << numero_bloque << std::endl;
	    } else {
	        // Aplicar LRU
	        int index = findLRUIndex();
	        delete buffer[index];
	        buffer[index] = newPage;
	        std::cout << "Pagina reemplazada en el buffer: " << numero_bloque << std::endl;
	    }
	}

	int findLRUIndex() {
	    int minIndex = 0;
	    int minValue = buffer[0]->bloque_correspondiente;
	
	    for (int i = 1; i < bufferSize; i++) {
	        if (buffer[i]->bloque_correspondiente < minValue) {
	            minIndex = i;
	            minValue = buffer[i]->bloque_correspondiente;
	        }
	    }
	
	    return minIndex;
	}



    void mostrarPagina(int bloque) {
        // Verificar si el bloque solicitado está en el buffer
        auto it = std::find_if(buffer.begin(), buffer.end(), [bloque](BufferPage* page) {
            return page->bloque_correspondiente == bloque;
        });

        if (it != buffer.end()) {
            // El bloque está en el buffer, mostrar su contenido
            std::cout << "Contenido del bloque " << bloque << ":" << std::endl;
            (*it)->mostrarContenido();
        } else {
            std::cout << "El bloque " << bloque << " no está en el buffer." << std::endl;
        }
    }
};

/*

class BufferPage {
	public:
	    int numero_bloque_solicitado;
	    LinkedList<string> contenido;
	    std::string content;
	    bool isModified;
	    bool isValid;
	    BufferPage(int numero): numero_bloque(numero){}
	    void guardar_registros()
		{
			string nombreSector = "bloques/bloque" + std::to_string(numero_bloque_solicitado) + ".txt";
			ifstream archivo(nombreSector);
	        while (std::getline(archivo, content)) {
	            if (!content.empty()) // Ignorar vacios
		        {
		            contenido.insert(content);
		        }
	        }
		}
		void mostrar_nodos(){
			contenido.mostrarNodos();
		}
};

class BufferManager {
private:
    int bufferSize;
    vector<BufferPage> buffermanager;
    unordered_map<int, typename vector<pair<int, BufferPage>>::iterator> pageMap;

public:
    BufferManager(int size) : bufferSize(size) {buffermanager.resize(size)}

    void solicitud(int pagina_deseada)
	{
	
	    // Verificar si la página solicitada ya está en el buffer
	    auto it = pageMap.find(pagina_deseada);
	    if (it != pageMap.end()) {
	        // La página está en el buffer, actualizar su orden de acceso
	        auto foundPage = it->second;
	        buffermanager.erase(foundPage);
	        buffermanager.push_back(*foundPage);
	        it->second = prev(buffermanager.end());
	        cout << "La pagina " << pagina_deseada << " ya está en el buffer." << endl;
	        return;
	    }
	
	    // Si la página no esta en el buffer, realizar la lógica de carga de la página
	    if (buffermanager.size() < bufferSize) {
	    	cout<<buffermanager.size()<<endl;
	        // El buffer aún no está lleno, agregar la página al buffer
	        BufferPage newPage(pagina_deseada);
	        newPage.guardar_registros();
	        buffermanager.push_back(make_pair(pagina_deseada, newPage));
	        pageMap[pagina_deseada] = prev(buffermanager.end());
	        cout << "Se cargo la pagina " << pagina_deseada << " en el buffer." << endl;
	    } else {
	        // El buffer esta lleno, aplicar  LRU
	        pair<int, BufferPage>& pageToRemove = buffermanager.front();
	        pageMap.erase(pageToRemove.first);
	        buffermanager.erase(buffermanager.begin());
	        BufferPage newPage(pagina_deseada);
	        newPage.guardar_registros();
	        buffermanager.push_back(make_pair(pagina_deseada, newPage));
	        pageMap[pagina_deseada] = prev(buffermanager.end());
	        cout << "Se cargo la página " << pagina_deseada << " en el buffer, reemplazando la página " << pageToRemove.first << "." << endl;
	    }
		cout<<buffermanager.size()<<endl;
	}
	void mostrar_pagina(int numero_pagina)
	{
	    // Verificar si la página solicitada está en el buffer
	    auto it = pageMap.find(numero_pagina);
	    if (it != pageMap.end()) {
	        // La página está en el buffer, mostrar su contenido
	        BufferPage& pagina = it->second->second;  // Modificar aquí para quitar la referencia constante
	        cout << "Contenido de la página " << numero_pagina << ":" << endl;
	        pagina.mostrar_nodos();  // Utilizar la función mostrar_nodos() de la clase BufferPage
	    } else {
	        cout << "La página " << numero_pagina << " no está en el buffer." << endl;
	    }
	}
};
class BufferManager {
private:
    int bufferSize;
    vector<BufferPage> buffermanager;
    unordered_map<int, typename vector<BufferPage>::iterator> pageMap;

public:
    BufferManager(int size) : bufferSize(size) {
        buffermanager.resize(size);
    }

    void solicitud(int pagina_deseada) {
        // Verificar si la página solicitada ya está en el buffer
        auto it = pageMap.find(pagina_deseada);
        if (it != pageMap.end()) {
            // La página está en el buffer, actualizar su orden de acceso
            auto foundPage = it->second;
            buffermanager.erase(foundPage);
        } else {
            // Si la página no está en el buffer, realizar la lógica de carga de la página
            if (buffermanager.size() >= bufferSize) {
                // El buffer está lleno, aplicar política de reemplazo LRU
                BufferPage& pageToRemove = buffermanager.front();
                pageMap.erase(pageToRemove.numero_bloque);
                buffermanager.erase(buffermanager.begin());
            }
        }

        // Cargar la página solicitada
        BufferPage newPage(pagina_deseada);
        newPage.guardar_registros();
        buffermanager.push_back(newPage);
        pageMap[pagina_deseada] = prev(buffermanager.end());

        cout << "Se cargó la página " << pagina_deseada << " en el buffer." << endl;
    }

    void mostrar_pagina(int numero_pagina) {
        // Verificar si la página solicitada está en el buffer
        auto it = pageMap.find(numero_pagina);
        if (it != pageMap.end()) {
            // La página está en el buffer, mostrar su contenido
            BufferPage& pagina = it->second->second;
            cout << "Contenido de la página " << numero_pagina << ":" << endl;
            pagina.mostrar_nodos();
        } else {
            cout << "La página " << numero_pagina << " no está en el buffer." << endl;
        }
    }
};

*/