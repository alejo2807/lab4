#include <iostream>
#include <cctype>
#include <thread>   // Para std::this_thread
#include <chrono>   // Para std::chrono
#include <limits>   // Para std::numeric_limits
#include "Tablero.h"
#include "Juego.h"
#include "LogicaDeMovimiento.h"
#include "VistaConsola.h"
#include "AvatarInnovador.h"
#include "AvatarCPU.h"

using namespace std;

int main() {
	// Inicializar componentes comunes
	Tablero tablero;
	tablero.cargarDesdeArchivo("dataTablero.txt");
	LogicaDeMovimiento logicaDeMovimiento;
	VistaConsola vista(&tablero, nullptr); // Inicialmente sin avatar
	
	// Menú de selección
	char eleccion;
	do {
		cout << "╔══════════════════════════════╗\n";
		cout << "║        JUEGO DE AVATAR       ║\n";
		cout << "╠══════════════════════════════╣\n";
		cout << "║ 1. Jugar yo mismo            ║\n";
		cout << "║ 2. Ver jugar a la CPU        ║\n";
		cout << "║ 3. Salir                     ║\n";
		cout << "╚══════════════════════════════╝\n";
		cout << "Seleccione una opción: ";
		cin >> eleccion;
		
		// Limpiar buffer de entrada
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		IPersonaje* avatar = nullptr;
		bool modoCPU = false;
		
		switch(eleccion) {
			case '1': // Modo jugador humano
				avatar = new AvatarInnovador();
				avatar->setPosicionFila(2);
				avatar->setPosicionColumna(2);
				vista.setAvatar(avatar);
				modoCPU = false;
				break;
				
			case '2': // Modo CPU
				avatar = new AvatarCPU();
				avatar->setPosicionFila(2);
				avatar->setPosicionColumna(2);
				vista.setAvatar(avatar);
				modoCPU = true;
				break;
				
			case '3': // Salir
				cout << "¡Hasta pronto!\n";
				return 0;
				
			default:
				cout << "Opción inválida. Intente nuevamente.\n";
				continue;
		}
		
		// Configurar e iniciar juego
		Juego juego(&tablero, avatar, &logicaDeMovimiento, true);
		juego.iniciar();
		
		if (modoCPU) {
			cout << "Iniciando simulación de CPU...\n";
			cout << "Presione Ctrl+C para detener en cualquier momento.\n";
		}

		// Bucle principal del juego
		do {
			vista.mostrarJuego();
			
			if (modoCPU) {
				// Espera automática para modo CPU
				vista.mostrarMensaje("CPU jugando...");
				this_thread::sleep_for(chrono::milliseconds(500)); // Pausa entre movimientos
				juego.play(' '); // Carácter dummy, la lógica de CPU lo ignora
			} else {
				vista.mostrarMensaje("Digite su movimiento:");
				juego.play(vista.getEntradaConsola());
			}
			
			// Verificar estado del juego
			if (!juego.getEstado()) {
				vista.limpiarPantalla();
				vista.mostrarJuego();
				vista.mostrarMensaje("¡PERDISTE! Caíste en un abismo.");
				break;
			}
			
		} while(!juego.getWin());

		// Resultado final
		if (juego.getWin()) {
			vista.limpiarPantalla();
			vista.mostrarJuego();
			vista.mostrarMensaje("¡GANASTE! Puntaje final: " + 
								to_string(juego.getPuntaje()));
		}

		// Limpiar para nueva partida
		delete avatar;
		cout << "\nPresione Enter para continuar...";
		cin.ignore();
		vista.limpiarPantalla();
		
	} while(true);

	return 0;
}