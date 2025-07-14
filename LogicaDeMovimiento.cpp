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

<<<<<<< HEAD
	/*
	
	if (!esAvatarCPU)
	{
	si no es avatar cpu, meter el switch completo aqui, ya que es avatar normal o avatar innovador
	el personaje se puede mover en las 4 direcciones con sus diagonlaes (si es innovador, sino, solo en 4 direcciones)
	}
	
	else
	{
	si es avatar cpu, meter la funcion que permite mover de forma random. 
	Le podemos pedir al usuario que ingrese una tecla para que el cpu se mueva solo, por ejemplo.
	Pero eso no implica que el usuario mueva el avatar cpu
	)*/
=======
    bool esAvatarInnovador = (dynamic_cast<AvatarInnovador*>(&personaje) != nullptr);
    bool esAvatarCPU = (dynamic_cast<AvatarCPU*>(&personaje) != nullptr);
>>>>>>> 65203f813fd2afd6e609e79a3f5591ed94efd014

    // Si es AvatarInnovador
    if (esAvatarInnovador) {
        switch (direccion) {
            case 'W': case 'w': nuevaFila--; break;
            case 'S': case 's': nuevaFila++; break;
            case 'A': case 'a': nuevaColumna--; break;
            case 'D': case 'd': nuevaColumna++; break;
            case 'Q': case 'q': nuevaFila--; nuevaColumna--; break;
            case 'E': case 'e': nuevaFila--; nuevaColumna++; break;
            case 'Z': case 'z': nuevaFila++; nuevaColumna--; break;
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

<<<<<<< HEAD
		//Agregamos los movimientos diagonales de avatar innovador
		case 'Q': case 'q': if (esAvatarInnovador) { nuevaFila--; nuevaColumna--; } break;
		case 'E': case 'e': if (esAvatarInnovador) { nuevaFila--; nuevaColumna++; } break;
		case 'Z': case 'z': if (esAvatarInnovador) { nuevaFila++; nuevaColumna--; } break;
		case 'C': case 'c': if (esAvatarInnovador) { nuevaFila++; nuevaColumna++; } break;
		
		//else{}
		
		default:
			// Dirección no válida
			return;
	}
	
	// CORRECTED BOUNDS CHECKING
	int dimension = tablero.getSize(); // Since board is square
	if (nuevaFila < 0 || nuevaFila >= dimension || 
		nuevaColumna < 0 || nuevaColumna >= dimension) {
		return;
	}

	Ficha* target = tablero.getFicha(nuevaFila, nuevaColumna);
	
	// SAFETY CHECKS
	if (!target) return; // Invalid position
	
	// Only update position if not abyss
	if (target->getTipo() != '0') {
		personaje.setPosicionFila(nuevaFila);
		personaje.setPosicionColumna(nuevaColumna);
	}
=======
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
>>>>>>> 65203f813fd2afd6e609e79a3f5591ed94efd014
}
