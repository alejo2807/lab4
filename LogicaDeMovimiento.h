#ifndef LOGICA_DE_MOVIMIENTO_H
#define LOGICA_DE_MOVIMIENTO_H

#include "IPersonaje.h"
#include "ITablero.h"  // se agrega para usar ITablero

class LogicaDeMovimiento {
public:
	// Método que mueve al personaje basado en la dirección dada
	// Agrega el tablero como parámetro para verificar límites
	void mover(IPersonaje &personaje, char direccion, const ITablero& tablero);
};

#endif // LOGICA_DE_MOVIMIENTO_H
