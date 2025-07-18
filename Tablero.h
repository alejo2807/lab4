#ifndef TABLERO_H
#define TABLERO_H

#include <vector>
#include <string>
#include "ITablero.h"

class Tablero : public ITablero {
private:
	std::vector<std::vector<Ficha*>> tablero;
	
	// Add limpiarTablero declaration
	void limpiarTablero();
public:
	int getColumnCount() const;  // Se agrega para solucionar el error de que el usuario perdia siempre
	void cargarDesdeArchivo(const std::string& archivo) override;
	Ficha* getFicha(int fila, int columna) const override;
	int getSize()const override;
	~Tablero();
};

#endif
