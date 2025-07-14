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
