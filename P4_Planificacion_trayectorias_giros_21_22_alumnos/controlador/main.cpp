#include "controlador.h"
#include <iostream>
int main()
{
   //Estos parametros podrian elegirse por linea de comandos o
   //leerse desde un fichero de configuracion
    const auto tam_casilla = 40u;
    const auto filas = 20u;
    const auto columnas = 20u;

    // Podríamos pasar por aquí un string o similar para elegir el algoritmo a ejecutar
    controlador::Controlador c(filas, columnas, tam_casilla);
    c.ejecutar();
}
