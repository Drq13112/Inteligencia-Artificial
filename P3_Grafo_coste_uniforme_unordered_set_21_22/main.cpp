#include "problema_busqueda.h"
#include "vista.h"
#include <exception>
#include <iostream>

// main como CONTROLADOR

int main()
{
    using namespace grafo;
    using namespace problema_busqueda;

    while (true)
    {
        try
        {
            std::string nombre_fichero = vista::solicita_valor<std::string>("Dame el nombre del fichero del grafo:");
            Grafo grafo(nombre_fichero);
            Nodo_grafo::asigna_grafo(grafo);
            break;
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << '\n';
        }
    }

    while (true)
    {
        try
        {
            using tipo_nodo = grafo::tipo_nodo;
            tipo_nodo nombre_nodo_inicial = vista::solicita_valor<tipo_nodo>("Deme el nodo inicial:");
            Nodo_grafo nodo_inicial(nombre_nodo_inicial);

            tipo_nodo nombre_nodo_objetivo = vista::solicita_valor<tipo_nodo>("Deme el nodo objetivo:");
            Nodo_grafo nodo_objetivo(nombre_nodo_objetivo);

            // AMPLITUD
            auto solucion = problema_busqueda::amplitud(nodo_inicial, nodo_objetivo);

            vista::muestra_solucion(solucion, nodo_inicial);
            // COSTE UNIFORME
            solucion = problema_busqueda::coste_uniforme(nodo_inicial, nodo_objetivo);

            vista::muestra_solucion(solucion, nodo_inicial);
            break;
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << '\n';
        }
    }


    return 0;
}
