#include "LogicaDeMovimiento.h"
#include "Personaje.h"
#include "AvatarInnovador.h"
#include "AvatarCPU.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void LogicaDeMovimiento::mover(IPersonaje &personaje, char direccion, const ITablero& tablero) {
	int nuevaFila = personaje.getPosicionFila();
	int nuevaColumna = personaje.getPosicionColumna();

	bool esAvatarInnovador = (dynamic_cast<AvatarInnovador*>(&personaje) != nullptr);
	bool esAvatarCPU = (dynamic_cast<AvatarCPU*>(&personaje) != nullptr);

	// Si es AvatarInnovador
	if (esAvatarInnovador) {
		switch (direccion) {
			case 'W': case 'w': nuevaFila--; break;
			case 'S': case 's': nuevaFila++; break;
			case 'A': case 'a': nuevaColumna--; break;
			case 'D': case 'd': nuevaColumna++; break;
			
			// Movimientos diagonales
			//diagonal izquierda arriba
			case 'Q': case 'q': nuevaFila--; nuevaColumna--; break;
			// diagonal derecha arriba
			case 'E': case 'e': nuevaFila--; nuevaColumna++; break;
			// diagonal izquierda abajo
			case 'Z': case 'z': nuevaFila++; nuevaColumna--; break;
			// diagonal derecha abajo
			case 'C': case 'c': nuevaFila++; nuevaColumna++; break;
			default: return; // Dirección inválida
		}
	}
	// Si es AvatarCPU
	else if (esAvatarCPU) {
		// Intentamos hasta 10 veces encontrar un movimiento válido
		bool movimientoValido = false;
		int intentos = 0;
		int filaActual = nuevaFila;
		int columnaActual = nuevaColumna;

		while (!movimientoValido && intentos < 10) {
			int direccionAleatoria = rand() % 4;
			nuevaFila = filaActual;
			nuevaColumna = columnaActual;

			switch (direccionAleatoria) {
				case 0: nuevaFila--; cout << "AvatarCPU se mueve arriba.\n"; break;
				case 1: nuevaFila++; cout << "AvatarCPU se mueve abajo.\n"; break;
				case 2: nuevaColumna--; cout << "AvatarCPU se mueve izquierda.\n"; break;
				case 3: nuevaColumna++; cout << "AvatarCPU se mueve derecha.\n"; break;
			}

			int dimension = tablero.getSize();
			if (nuevaFila >= 0 && nuevaFila < dimension &&
				nuevaColumna >= 0 && nuevaColumna < dimension) {

				Ficha* target = tablero.getFicha(nuevaFila, nuevaColumna);
				if (target && target->getTipo() != '0') {
					movimientoValido = true;
				}
			}

			intentos++;
		}

		if (!movimientoValido) return; // No se encontró movimiento válido
	}

	// Verificación de límites y abismo para todos los personajes
	int dimension = tablero.getSize();
	if (nuevaFila < 0 || nuevaFila >= dimension ||
		nuevaColumna < 0 || nuevaColumna >= dimension) {
		return;
	}

	Ficha* target = tablero.getFicha(nuevaFila, nuevaColumna);
	if (!target || target->getTipo() == '0') return;

	personaje.setPosicionFila(nuevaFila);
	personaje.setPosicionColumna(nuevaColumna);
}
