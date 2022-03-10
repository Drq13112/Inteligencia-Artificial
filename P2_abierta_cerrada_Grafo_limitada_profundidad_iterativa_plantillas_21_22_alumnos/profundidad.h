#include <iostream>

namespace problema_busqueda
{
    template<typename Problema>
    Solucion<Problema> profundidad(Problema& estado_inicial, Problema& estado_objetivo,
                                   size_t limite = std::numeric_limits<size_t>::max())
    {
        using tipo_operador = tipo_operador<Problema>;
        using Nodo_busqueda = Nodo_busqueda<Problema>;//Siempre que pongamos Nodo_busqueda, en realidad estamos poniendo Nodo_busqueda<Problema>

        std::vector<Nodo_busqueda> frontera;
        std::vector<Nodo_busqueda> visitados;

        frontera.push_back(Nodo_busqueda{estado_inicial, Problema::operador_nulo(),0});//No entiendo porque pone Problema::

        bool exito = false;
        size_t nodos_expandidos = 0; // Para comparar entre algoritmos
        size_t profundidad_actual = 0;

        while (exito == false && !frontera.empty())//El momento en que la frontera este vacia sale del bucle
        {
            visitados.resize(profundidad_actual + 1);
            visitados[profundidad_actual] = frontera.back();

            frontera.pop_back();

            ++nodos_expandidos;
            exito = visitados[profundidad_actual].estado == estado_objetivo; // Prueba de meta

            if (exito == false)
            {
                if (profundidad_actual < limite)
                {
                    auto hijos = visitados[profundidad_actual].estado.sucesores();
                    for (auto& [op, estado] : hijos)
                    {
                        if (!repetido_contenedor_nodo_busqueda(visitados, estado) &&
                                !repetido_contenedor_nodo_busqueda(frontera, estado))
                        {
                            frontera.push_back(Nodo_busqueda{estado, op, profundidad_actual});
                        }
                    }
                }
            }
            if (!frontera.empty())
                profundidad_actual = frontera.back().padre + 1;
        }

        std::vector<tipo_operador> secuencia_operadores;

        if (exito)
            secuencia_operadores = set_secuencia_operadores(visitados);

        return Solucion<Problema> {exito, secuencia_operadores, nodos_expandidos};
    }

    template<typename Problema>
    Solucion<Problema> profundizacion_iterativa(Problema& estado_inicial, Problema& estado_objetivo,
                                   size_t limite = std::numeric_limits<size_t>::max())
    {
        size_t depth = 0;
        size_t nodos=0;
        while (true)
        {
           auto Salida= profundidad(estado_inicial, estado_objetivo, depth);
           /*
           * Saldrá del bucle cuando haya encontrado la solucion o cuando se de cuenta
           * de que ha alcanzado la maxima profundidad del grafo, es decir, 
           * cuando los nodos expandidos de la anterior busqueda son los mismos que la de esta nueva busqueda
           */

           if (Salida.exito == true || nodos==Salida.nodos_expandidos) 
               return Salida;
           depth++;
           nodos = Salida.nodos_expandidos;

        }
    }
}
