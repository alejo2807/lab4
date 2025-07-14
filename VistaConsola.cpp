#include "VistaConsola.h"
#include "Camino.h"
#include "Abismo.h"
#include "Salida.h"
#include <iostream>
#include <iostream>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()
#include <termios.h>
#include <unistd.h> // Para STDIN_FILENO
#include "AvatarCPU.h"
#include "AvatarInnovador.h"
using namespace std;
VistaConsola::VistaConsola(ITablero* tablero, IPersonaje* avatar):tablero(tablero), avatar(avatar){}

void VistaConsola::mostrarTablero() {
	limpiarPantalla();
	std::cout<<"Fil--Col\t";
	for(int i=0; i<tablero->getSize();i++) std::cout<<i<<"\t";
	std::cout<<"\n";

	for(int i=0; i<tablero->getSize();i++){
		std::cout<<i<<"\t\t";
		for(int j=0; j<tablero->getSize();j++){ 
			Ficha* ficha = tablero->getFicha(i,j);
			std::cout<<ficha->getTipo()<<"\t";
		}
		std::cout<<"\n";
	}

}
void VistaConsola::limpiarPantalla(){
	#ifdef _WIN32
		system("cls"); // Comando para Windows
	#else
		system("clear"); // Comando para Linux y macOS
	#endif
}

void VistaConsola::mostrarJuego() {
    limpiarPantalla();
    
    for(int i = 0; i < tablero->getSize(); i++) {
        for(int j = 0; j < tablero->getSize(); j++) {
            if(i == avatar->getPosicionFila() && j == avatar->getPosicionColumna()) {
                std::cout << "🧝 ";
                continue;
            }
            
            Ficha* ficha = tablero->getFicha(i,j);
            if(!ficha) {
                std::cout << "  ";
                continue;
            }
            
            switch(ficha->getTipo()) {
                case '1': std::cout << (rand() % 2 ? "🟨 " : "🟨 "); break;
                case '0': std::cout << "🟦 "; break;
                case 'S': std::cout << "💰 "; break;
                default:  std::cout << "  ";
            }
        }
        std::cout << "\n";
    }
}


// Implementación de mostrarMensaje
void VistaConsola::mostrarMensaje(const std::string& mensaje) {

	std::cout << mensaje << "\n";
}

// Implementación de leerEntrada
char VistaConsola::getEntradaConsola() {
	char entrada;
	bool entradaValida = false;
	struct termios oldt, newt;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;

	// Deshabilitar el modo de espera para Enter
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);


	bool esAvatarCPU;
	if (dynamic_cast<AvatarCPU*>(avatar)) {
    esAvatarCPU= true;
} else {
    esAvatarCPU= false;
}
	if(esAvatarCPU == false){
	do {
	std::cout << "Ingrese una opción [aA-Izquierda] [wW-Arriba] [sS-Abajo] [dD-Derecha]\n [qQ-Diagonal Arriba Izq] [eE-Diagonal Arriba Der] [zZ-Diagonal Abajo Izq] [cC-Diagonal Abajo Der]: ";
	entrada=getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

		// Convertir a minúscula para simplificar validación
		char entradaMin = std::tolower(entrada);

		// Validar que la entrada sea 'w', 'a', 's' o 'd' con los movimientos diagonales
		if (entradaMin == 'w' || entradaMin == 'a' || entradaMin == 's' || entradaMin == 'd' 
			|| entradaMin == 'q' || entradaMin == 'e' || entradaMin == 'c' || entradaMin == 'z') {
			entradaValida = true;
		} else {
			std::cout << "Entrada inválida. Por favor, introduce wW, aA, sS, dD, qQ, eE, zZ o cC.\n";
		}
	} while (!entradaValida);}
	else{

		cout << "Ingrese una letra cualquiera "<<endl;
		entrada=getchar();
	}
	

	return entrada;
}
