#include <iostream>
#include <vector>
#include <unordered_map>
//#include "registro_bloque.h"



class BufferFrame {
public:
    //int frameID = 0 ;
    int pageID ;
    bool dirtyBit ;
    int pinCount  ;
    bool refBit = false; // Nuevo atributo para el bit de referencia
    Bloque* Page = NULL;
    BufferFrame( int pageID) :  pageID(pageID), dirtyBit(false), pinCount(0), refBit(true) {}//frameID(frameID)
    
    void set_page(Bloque* page){Page = page;} 
    // Getter para el atributo frameID
    //int getFrameID() const {return frameID;}
    // Getter para el atributo pageID
    int getPageID() const {return pageID;}
    // Getter para el atributo dirtyBit
    bool isDirty() const {return dirtyBit;}
    // Setter para el atributo dirtyBit
    void setDirty(bool dirty) {dirtyBit = dirty;}
   // Setter para el atributo refBit
    void setReferenced(bool referenced) {refBit = referenced;}
    // Setter para el atributo pinCount
    void setPinCount(int count) {pinCount = count;}
    // Getter para el atributo refBit
    bool isReferenced() const {return refBit;}
 	// Getter para el atributo pinCount
    int getPinCount() const {return pinCount;}
    // Getter para el atributo Page
    Bloque* getPage() const {return Page;}

};

class BufferManager {
private:
	int num_pages;
    std::vector<BufferFrame*> bufferPool;
    std::unordered_map<int, int> frameLookup;
	int bloque_buscado;
	int id = 1;
public:
	
    BufferManager(int poolSize) : num_pages(poolSize) {
        bufferPool.reserve(num_pages);
    }
    
	void insertar(Bloque* bloque_) {
		//cout<<"SE INSERTA"<<endl;
		//cout<<endl<<"BLOQUE ID"<<bloque_->get_id()<<endl;
	    BufferFrame* aux = new BufferFrame(bloque_->get_id());
	    aux->set_page(bloque_);  // Utiliza el operador -> para acceder a los miembros de aux
	    //cout<<endl<<"CONTENIDO AUX PAGE "<<endl;
		//aux->Page->mostrarContenido();
		
	    if (bufferPool.size() < bufferPool.capacity()) {
	        // El vector todavía tiene espacio disponible para agregar más elementos
	        bufferPool.push_back(aux);
	        //cout<<"primer caso"<<endl;
	    } else {
	        // El vector ha alcanzado su capacidad máxima
	
	        // Ordenar el vector bufferPool por pinCount de mayor a menor
	        std::sort(bufferPool.begin(), bufferPool.end(), [](const BufferFrame* a, const BufferFrame* b) {return a->getPinCount() > b->getPinCount();});
	
	        // Obtener el BufferFrame con menor pinCount
	        BufferFrame* bufferFrameMenorPin = bufferPool.back();
	
	        // Reemplazar el BufferFrame con menor pinCount por el nuevo BufferFrame
	        bufferPool.pop_back();
	        bufferPool.push_back(aux);
	
	        // Liberar la memoria del BufferFrame reemplazado
	        delete bufferFrameMenorPin;
		}
	}
    
    bool existeRegistroConBloqueID(int id_r) {
        for (BufferFrame*& frame : bufferPool) {
            Bloque* bloque = frame->getPage();  // Suponiendo que el método para obtener el Bloque sea getPage()
            if (bloque && bloque->id == id_r) {  // Comprobar si el ID del bloque coincide
            	cout<<endl<<"SI EXISTE"<<endl;
                return true;
            }
        }
        return false;
    }
    
   Bloque* obtenerBloqueEnBufferFramePorID(int bloqueID) {
	    for (BufferFrame* frame : bufferPool) {
	        Bloque* bloque = frame->getPage();  // Suponiendo que el método para obtener el Bloque sea getPage()
	        //bloque->mostrarContenido();
	        //cout<<endl<<"ID PARAMETERO: "<<bloqueID<<" "<<"IDBLOQUE"<<bloque->get_id()<<endl;
	        
	        if (bloque->get_id() == bloqueID) {
	        	//cout<<endl<<"ENTRA A OBTNER"<<endl;
	         	return bloque;
	        }
	    }	
    	return nullptr;  // Devuelve nullptr si no se encuentra el bloque en ningún BufferFrame
	}
	
};


