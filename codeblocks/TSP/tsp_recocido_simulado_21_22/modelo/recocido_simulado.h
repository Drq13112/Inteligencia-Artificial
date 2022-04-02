#ifndef RECOCIDO_SIMULADO
#define RECOCIDO_SIMULADO

#include "observador.h"
#include <atomic>

namespace rs
{
enum class Evento_modelo {nuevo_minimo,nueva_iteracion, fin};

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
    unsigned Calcula_temperatura(Muestra, Parametros);

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

        //Notificamos al controlador de que se est� haciendo una nueva iteracion
        notifica(Evento_modelo::nueva_iteracion);
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

template<typename Muestra>
unsigned Recocido_simulado<Muestra>::Calcula_temperatura(Muestra muestra, Parametros parametros)
{
        auto num_descensos = parametros.num_descensos;
        auto num_permutaciones = parametros.num_permutaciones;
        auto num_exitos_maximo = parametros.num_exitos_maximo;
        auto temperatura = parametros.temperatura;
        auto factor_descenso = parametros.factor_descenso;

        rng::uniforme_double aleatorio_0_a_1{0, 1};

        solucion = muestra;
        unsigned num_exitos_totales = 0;
        std::cout<<"Aqui"<<std::endl;

        for (iteracion_actual = 0; iteracion_actual < num_descensos; ++iteracion_actual)
        {
            unsigned num_exitos = 0;
            for (unsigned j = 0; j < num_permutaciones; ++j)
            {
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
                    }

                    if (++num_exitos > num_exitos_maximo)
                        break;
                }

            }
            if (num_exitos == 0)
                break;

            temperatura *= factor_descenso;
            num_exitos_totales += num_exitos;

        }
        return num_exitos_totales;

    }


}


#endif // RECOCIDO_SIMULADO_H_INCLUDED
