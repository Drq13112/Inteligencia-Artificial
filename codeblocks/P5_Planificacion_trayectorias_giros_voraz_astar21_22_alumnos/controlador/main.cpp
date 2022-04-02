#include "controlador.h"
#include <iostream>
int main()
{
    // Estos parametros podrian elegirse por linea de comandos o
    // leerse desde un fichero de configuracion
    const auto tam_casilla = 40u;
    const auto filas = 20u;
    const auto columnas = 20u;
    const auto coste_avanzar = 1.;
    const auto coste_girar = 10.;

    // Cadenas validas //////////////////////////////////
    // "coste_uniforme"
    // "voraz"
    // "amplitud"
    // "a_estrella"
    ////////////////////////////////////////////////////

    try
    {
        controlador::Controlador c("voraz", filas, columnas, tam_casilla, coste_avanzar, coste_girar);
        c.ejecutar();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << '\n';
    }

}
