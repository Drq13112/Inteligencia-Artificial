#ifndef CONTROLADOR_H_INCLUDED
#define CONTROLADOR_H_INCLUDED
#include "..\vista\vista.h"   // Nuestra clase vista
#include "..\modelo\ciudades.h"
#include "..\modelo\ruta.h"
#include "..\modelo\recocido_simulado.h"

#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <queue>

namespace controlador
{

    struct Datos_visualizacion
    {
        ruta::Ruta ruta;
        unsigned iteracion;
    };

    struct Tsp_lib
    {
        std::vector<std::pair<double, double>> coordenadas;
        std::vector<unsigned> recorrido_optimo;
        bool exito; // Lectura correcta del fichero
    };

    Tsp_lib carga_ciudades(const std::string& nombre_fichero);

    class Controlador
    {
    public:
        Controlador()
        {
            registra_observadores();
        }
        void ejecutar();
    private:
        vista::Vista vista;

        rs::Recocido_simulado<ruta::Ruta> algoritmo_rs;
        rs::Parametros parametros;

        // HILOS
        std::thread hilo_modelo;
        std::thread hilo_cola_datos;

        std::atomic<bool> fin_algoritmo;
        std::mutex barrera_datos;
        std::condition_variable c_v_barrera_datos;

        std::queue<Datos_visualizacion> datos;

        ciudades::Ciudades ciudades;
        void registra_observadores();
        void actualiza_contador();

        bool carga_problema_tsplib();
        bool set_coordenadas_visualizacion(const std::vector<std::pair<double, double>>& coordenadas);

        void finaliza_programa();

        void ejecuta_rs();  //Hilo rs
        void fin_rs();

        void push_datos();
        void pop_datos();    //Hilo cola de datos
        void vacia_datos();
    };
}
#endif // CONTROLADOR_H_INCLUDED
