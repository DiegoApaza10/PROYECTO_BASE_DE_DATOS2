#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <iomanip>
#include <sstream>
#include <istream>
#include <algorithm>
#include "Lista_Enlazada.h"
class Registro {
    // Implementación de la clase Registro
};

class Sector {
	public:
	    // Variables miembro y métodos de la clase Sector
	private:
	    LinkedList<Sector> registros;
};

class Pista {
	public:
	    // Variables miembro y métodos de la clase Pista
	private:
	    LinkedList<Sector> sectores;
};

class Plato {
	public:
	    // Variables miembro y métodos de la clase Plato
	private:
	    LinkedList<Pista> pistas;
};

class DiscoDuro {
	public:
	    // Variables miembro y métodos de la clase DiscoDuro
	private:
	    LinkedList<Plato> platos;
};


