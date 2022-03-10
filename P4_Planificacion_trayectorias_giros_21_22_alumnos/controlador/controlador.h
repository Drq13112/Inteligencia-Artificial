#ifndef CONTROLADOR_H_INCLUDED
#define CONTROLADOR_H_INCLUDED

#include <chrono>
#include "../vista/vista.h"            // Clase vista
#include "../modelo/cuadricula.h"       // Clase modelo
#include "../modelo/nodo_cuadricula.h"  // Clase modelo

namespace controlador
{
    class Controlador
    {
    public:

        using posicion_casilla = vista::Vista::posicion_casilla;
        using posicion_y_tipo_casilla = vista::Vista::posicion_y_tipo_casilla;
        Controlador(unsigned filas, unsigned columnas, unsigned tam_casilla)
        {
            vista = std::unique_ptr<vista::Vista>(new vista::Vista(filas, columnas, tam_casilla));
            registra_observadores();
        }
        ~Controlador()
        {
        }
        void ejecutar();
    private:
        std::unique_ptr<vista::Vista> vista;
        void registra_observadores();
        void busca_trayectoria();
        void ejecuta_vista();
        void ejecuta_modelo();
        cuadricula::Posicion_2d posicion_inicial();
        cuadricula::Posicion_2d posicion_final();
        std::vector<cuadricula::Punto_2d> muros();
        posicion_y_tipo_casilla transforma(const cuadricula::Nodo_cuadricula& nodo);
    };

}
#endif // CONTROLADOR_H_INCLUDED
