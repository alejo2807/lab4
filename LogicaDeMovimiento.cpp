#include "LogicaDeMovimiento.h"
#include "Personaje.h"
#include "AvatarInnovador.h"  // Incluimos la clase del nuevo tipo de avatar
#include <iostream>

void LogicaDeMovimiento::mover(IPersonaje &personaje, char direccion, const ITablero& tablero) {
	
	
	
	
	
	int nuevaFila = personaje.getPosicionFila();
	int nuevaColumna = personaje.getPosicionColumna();
	
	
	// Verificar si el personaje es un AvatarInnovador con diferente a null ptr
	bool esAvatarInnovador = (dynamic_cast<AvatarInnovador*>(&personaje) != nullptr);
	// Verificar si el personaje es un AvatarCPU (si se implementa en el futuro)
	//bool esAvatarCPU = dynamic_cast<AvatarCPU*>(&personaje);  // For future use


	// Ajustar posición según la dirección
	switch (direccion) {
		
		//if(!esAvatarCPU){}
		
		case 'W': case 'w': nuevaFila--; break;  // Mover hacia arriba
		case 'S': case 's': nuevaFila++; break;  // Mover hacia abajo
		case 'A': case 'a': nuevaColumna--; break;  // Mover hacia la izquierda
		case 'D': case 'd': nuevaColumna++; break;  // Mover hacia la derecha

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
}
