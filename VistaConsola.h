#ifndef VISTA_CONSOLA_H
#define VISTA_CONSOLA_H

#include "IVistaJuego.h"
#include "Tablero.h"
#include "Avatar.h"
#include <vector>
#include <string>

// Implementación concreta de IVistaJuego
class VistaConsola : public IVistaJuego {
private:
    ITablero* tablero;          // Puntero al tablero
    IPersonaje* avatar;         // Puntero al personaje
public:
    // Constructor y destructor
    VistaConsola(ITablero* tablero, IPersonaje* avatar);
    ~VistaConsola() override = default;

    // Métodos que implementan IVistaJuego
    void mostrarTablero() override;
    void mostrarJuego() override;
    void limpiarPantalla() override;
    void mostrarMensaje(const std::string& mensaje) override;
    char getEntradaConsola() override;
};

#endif // VISTA_CONSOLA_H
