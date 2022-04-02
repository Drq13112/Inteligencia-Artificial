#ifndef CONTROLADOR_H_INCLUDED
#define CONTROLADOR_H_INCLUDED

#include <chrono>
#include "vista.h"            // Clase vista
#include "cuadricula.h"       // Clase modelo
#include "nodo_cuadricula.h"  // Clase modelo

namespace controlador
{
    class Controlador
    {
    public:

        using posicion_casilla = vista::Vista::posicion_casilla;
        using posicion_y_tipo_casilla = vista::Vista::posicion_y_tipo_casilla;
        Controlador(std::string nombre_algoritmo, unsigned filas, unsigned columnas, unsigned tam_casilla,
                    cuadricula::Nodo_cuadricula::tipo_coste coste_avanzar, cuadricula::Nodo_cuadricula::tipo_coste coste_girar):
                        nombre_algoritmo{nombre_algoritmo}, coste_avanzar{coste_avanzar}, coste_girar{coste_girar}
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
        std::string nombre_algoritmo;
        cuadricula::Posicion_2d posicion_inicial();
        cuadricula::Posicion_2d posicion_final();
        std::vector<cuadricula::Punto_2d> muros();
        cuadricula::Nodo_cuadricula::tipo_coste coste_avanzar;
        cuadricula::Nodo_cuadricula::tipo_coste coste_girar;
        posicion_y_tipo_casilla transforma(const cuadricula::Nodo_cuadricula& nodo);
    };

}
#endif // CONTROLADOR_H_INCLUDED
