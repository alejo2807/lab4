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

void VistaConsola::mostrarJuego(){
    limpiarPantalla();


    for(int i=0; i<tablero->getSize();i++){
        for(int j=0; j<tablero->getSize();j++){ 
            if(avatar->getPosicionFila()==i and avatar->getPosicionColumna()==j) {
                   std::cout << "🟫🟫🟩🧝🟫🟫" <<"\t";
            }
            else {
                Ficha* ficha = tablero->getFicha(i,j);
                if(ficha->getTipo()=='1') {
                 std::srand(std::time(0));
                 // Generar un número aleatorio (0 o 1)
                int randomValue = std::rand() % 2;
                if(randomValue==0) std::cout << "🟫🟫🟩🟨🟫🟫" <<"\t";
                else std::cout << "🟫🟫🟨🟩🟫🟫" <<"\t";

            }
                else if(ficha->getTipo()=='0') std::cout << "🟫🟫🟦🟦🟫🟫" <<"\t";
                else std::cout << "🟫🟫💰💰🟫🟫" <<"\t";
                
            }
            
        }
        std::cout<<"\n";
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

    do {
    std::cout << "Ingrese una opción [aA-Izquierda] [wW-Arriba] [sS-Abajo] [dD-Derecha]: ";
    entrada=getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

        // Convertir a minúscula para simplificar validación
        char entradaMin = std::tolower(entrada);

        // Validar que la entrada sea 'w', 'a', 's' o 'd'
        if (entradaMin == 'w' || entradaMin == 'a' || entradaMin == 's' || entradaMin == 'd') {
            entradaValida = true;
        } else {
            std::cout << "Entrada inválida. Por favor, introduce wW, aA, sS o dD.\n";
        }
    } while (!entradaValida);

    return entrada;
}
