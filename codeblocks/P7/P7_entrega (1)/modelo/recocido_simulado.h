#ifndef RECOCIDO_SIMULADO
#define RECOCIDO_SIMULADO

#include <iostream>
#include "observador.h"
#include <atomic>

namespace rs
{
    enum class Evento_modelo {nuevo_minimo, fin};

    struct Parametros
    {
        unsigned num_descensos;
        unsigned num_permutaciones;
        unsigned num_exitos_maximo;
        double temperatura;
        double factor_descenso;
    };

    template<typename Muestra>
    class Recocido_simulado:public Observable<Evento_modelo>
    {
        public:
            void ejecutar(Muestra, Parametros);

            void detener()
            {
                abortar = true;
            }
            const Muestra get_solucion() const
            {
                return solucion;
            }
            unsigned get_iteracion_actual() const
            {
                return(iteracion_actual);
            }
            double compute_initial_temperature(Muestra muestra,
                                               const double target_initial_acceptance=0.6,
                                               const unsigned sample_size=1e4,
                                               const double tol = 0.02) const ;
        private:
            std::atomic<bool> abortar;

            //Datos disponibles para el observador
            unsigned iteracion_actual = 0;
            Muestra solucion;
            ////////////////////////////
    };


    // Calcula una solucion mediante recocido simulado
    template<typename Muestra>
    void Recocido_simulado<Muestra>::ejecutar(Muestra muestra, Parametros parametros)
    {
        auto num_descensos = parametros.num_descensos;
        auto num_permutaciones = parametros.num_permutaciones;
        auto num_exitos_maximo = parametros.num_exitos_maximo;
        auto temperatura = parametros.temperatura;
        auto factor_descenso = parametros.factor_descenso;

        rng::uniforme_double aleatorio_0_a_1{0, 1};



        solucion = muestra;

        notifica(Evento_modelo::nuevo_minimo);

        abortar=false;

        for (iteracion_actual = 0; iteracion_actual < num_descensos; ++iteracion_actual)
        {
            unsigned num_exitos = 0;
            for (unsigned j = 0; j < num_permutaciones; ++j)
            {
                if (abortar)
                {
                    notifica(Evento_modelo::fin);
                    return;
                }

                auto muestra_provisional = muestra.sucesor_rnd();
                auto distancia_provisional = muestra_provisional.valor;
                auto incremento = distancia_provisional - muestra.valor;

                // Problema cuando el sucesor es repetido: incremento = 0
                // y la variable que detecta el congelamiento no actúa
                if (incremento < 0 || aleatorio_0_a_1() < exp(-incremento/temperatura))
                {
                    muestra = muestra_provisional;
                    if (distancia_provisional < solucion.valor)
                    {
                        solucion = muestra;
                        //Notificamos al Controlador
                        notifica(Evento_modelo::nuevo_minimo);
                    }
                    if (++num_exitos > num_exitos_maximo)
                        break;
                }

            }
            if (num_exitos == 0)
                break;

            //std::cout << num_permutaciones << " " << num_exitos << std::endl;
            temperatura *= factor_descenso;
        }
        // std::cout<<"\nFIN " << iteracion_actual<< "\n";
        notifica(Evento_modelo::fin);
    }

    /*
    Se estimara una temperatura inicial para obtener una probabilidad de aceptar una nueva muestra
    igual a target_initial_temperature, con una tolerancia de tol.
    Esta temperatura se estimará sobre una muestra aleatoria de la población
    */
    template<typename Muestra>
    double Recocido_simulado<Muestra>::compute_initial_temperature(
            Muestra muestra,
            const double target_initial_acceptance,
            const unsigned sample_size,
            const double tol) const {

        double acceptance_estimate = 0;
        double accepted = 0; //double para no tener que utilizar casts
        double temperature = 0;
        double max_distance = 0;
        rng::uniforme_double aleatorio_0_a_1{0, 1};

        //estimate max distance between neighbors
        // S. Kirkpatrick, C.D. Gelatt, and M.P. Vecchi, “Optimization by simulated annealing,” Science, vol. 220, pp. 671–680, 1983.
        for(unsigned i=0; i < sample_size; ++i){
            auto muestra_rnd = muestra.sucesor_rnd();
            auto distancia_muestra = muestra_rnd.valor;
            auto incremento = distancia_muestra - muestra.valor;
            max_distance = std::max(std::abs(incremento), max_distance);
            if(aleatorio_0_a_1() < 0.5) { muestra = muestra_rnd; } //cambiar de muestra con una probabilidad del 50%
        }

        std::cout<<max_distance<<'\n';
        temperature = max_distance / 2; //set initial temperature at 50% of the max distance

        while(true){
            accepted = 0;
            for(unsigned i=0; i < sample_size; ++i){
                auto muestra_rnd = muestra.sucesor_rnd();
                auto distancia_muestra = muestra_rnd.valor;
                auto incremento = distancia_muestra - muestra.valor;
                if (incremento < 0 || aleatorio_0_a_1() < exp(-incremento/temperature)){
                    ++accepted;
                }
                if(aleatorio_0_a_1() < 0.5) { muestra = muestra_rnd; } //cambiar de muestra con una probabilidad del 50%
            }
            acceptance_estimate = accepted / sample_size;
            std::cout<< "Temperature estimate: " << acceptance_estimate << '\n';
            if(std::abs(acceptance_estimate-target_initial_acceptance) < tol){ break; }
            else if(acceptance_estimate < target_initial_acceptance) { temperature *= 2 ;}
            else if(acceptance_estimate > target_initial_acceptance) { temperature /= 3 ;}
        }
        std::cout<< "Initial temperature: " << temperature << '\n';
        return temperature;
    }
}
#endif // RECOCIDO_SIMULADO_H_INCLUDED
