#include "Tablero.h"
#include "Camino.h"
#include "Abismo.h"
#include "Salida.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

Tablero::~Tablero() {
	limpiarTablero();
}



int Tablero::getColumnCount() const {
    if (tablero.empty()) return 0;
    return tablero[0].size();
}

void Tablero::cargarDesdeArchivo(const std::string& archivo) {
	limpiarTablero();
	std::ifstream file(archivo);
	if (!file.is_open()) {
		throw std::runtime_error("No se pudo abrir el archivo: " + archivo);
	}

	std::string linea;
	int fila = 0;
	// In Tablero::cargarDesdeArchivo
while (std::getline(file, linea)) {
	std::vector<Ficha*> filaActual;
	std::istringstream stream(linea);
	char tipoFicha;
	int columna = 0;   
	while (stream >> tipoFicha) {
		// Skip spaces and newlines
		if (tipoFicha == ' ' || tipoFicha == '\n') continue;
		
		if (tipoFicha == '1') {
			filaActual.push_back(new Camino(fila, columna, '1'));
		} else if (tipoFicha == '0') {
			filaActual.push_back(new Abismo(fila, columna, '0'));
		} else if (tipoFicha == 'S') {
			filaActual.push_back(new Salida(fila, columna, 'S'));
		} else {
			filaActual.push_back(nullptr);
		}
		columna++;
	}
	tablero.push_back(filaActual);
	fila++;
}
}

Ficha* Tablero::getFicha(int fila, int columna) const {
	if (fila < 0 || fila >= static_cast<int>(tablero.size()) ||
		columna < 0 || columna >= static_cast<int>(tablero[fila].size())) {
		return nullptr; // Fuera de los límites
	}
	return tablero[fila][columna];
}


void Tablero::limpiarTablero() {
	// Iterate through the tablero to delete dynamically allocated Ficha objects
	for (auto& fila : tablero) {
		for (auto& ficha : fila) {
			delete ficha;
		}
		fila.clear(); // Clear each row
	}
	tablero.clear(); // Clear the tablero vector
}
int Tablero::getSize() const {
	return tablero.size();
}
