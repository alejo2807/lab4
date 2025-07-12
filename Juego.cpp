#include "Juego.h"
#include "Personaje.h"
#include <iostream>

Juego::Juego(ITablero* tablero, IPersonaje* avatar, LogicaDeMovimiento* logicaDeMovimiento, bool estado=true)
	: tablero(tablero), avatar(avatar), logicaDeMovimiento(logicaDeMovimiento), estado(estado) {}

Juego::~Juego() {
}

void Juego::moverAvatar(char direccion) {
    logicaDeMovimiento->mover(*avatar, direccion, *tablero);
    
    Ficha* ficha = tablero->getFicha(
        avatar->getPosicionFila(),
        avatar->getPosicionColumna()
    );
    
    // Immediate lose if on abyss
    if (ficha && ficha->getTipo() == '0') {
        estado = false;
        return;
    }
    
    // Win condition
    if (ficha && ficha->getTipo() == 'S') {
        std::cout << "win" << std::endl;
    }
}

void Juego::iniciar() {
	std::cout << "El juego ha comenzado." << std::endl;
	puntaje=100;
}

bool Juego::getEstado(){
	return estado;
}
bool Juego::getWin(){
	 Ficha* ficha = tablero->getFicha(avatar->getPosicionFila(),avatar->getPosicionColumna());
	   if(ficha->getTipo()=='S') return true;
	   else return false;
}
void Juego::puntuar(){
	 puntaje=puntaje-2;
}
int Juego::getPuntaje(){
	return puntaje;
}
void Juego::play(char movimiento){
	

			this->moverAvatar(movimiento);
			puntuar();

}