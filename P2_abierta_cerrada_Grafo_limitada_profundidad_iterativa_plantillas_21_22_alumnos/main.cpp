#include "problema_busqueda.h"
#include "vista.h"
#include <exception>
#include <iostream>

// main como CONTROLADOR

int main()
{
    using namespace problema_busqueda;

    while (true)
    {
        try
        {
            std::string nombre_fichero = vista::solicita_dato<std::string>("Dame el nombre del fichero del grafo:");
            grafo::Grafo grafo(nombre_fichero);
            grafo::Nodo_grafo::asigna_grafo(grafo);
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
            tipo_nodo nombre_nodo_inicial = vista::solicita_dato<tipo_nodo>("Deme el nodo inicial:");
            grafo::Nodo_grafo nodo_inicial(nombre_nodo_inicial);

            tipo_nodo nombre_nodo_objetivo = vista::solicita_dato<tipo_nodo>("Deme el nodo objetivo:");
            grafo::Nodo_grafo nodo_objetivo(nombre_nodo_objetivo);

            // AMPLITUD
            std::cout << "Busqueda en amplitud\n\n";
            auto solucion = problema_busqueda::amplitud(nodo_inicial, nodo_objetivo);
            vista::muestra_solucion(solucion, nodo_inicial);

            // PROFUNDIDAD
            std::cout << "Busqueda en profundidad\n\n";
            solucion = problema_busqueda::profundidad(nodo_inicial, nodo_objetivo);
            vista::muestra_solucion(solucion, nodo_inicial);

            // PROFUNDIZACIÓN ITERATIVA
            std::cout << "Busqueda por profundizacion iterativa\n\n";
            solucion = problema_busqueda::profundizacion_iterativa(nodo_inicial, nodo_objetivo);
            vista::muestra_solucion(solucion, nodo_inicial);
            break;
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << '\n';
        }
    }
    int p;
    std::cin >> p;


    return 0;
}
