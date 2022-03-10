#include "grafo.h"
#include <iostream>
#include <fstream>

namespace grafo
{
    Grafo Nodo_grafo::grafo = Grafo();  // Inicialización variable estática de la clase

    void Grafo::inicializa_grafo(const std::string& nombre_fichero)
    {
        std::ifstream fichero(nombre_fichero);
        if (!fichero)
            throw std::runtime_error("No se pudo abrir el fichero " + nombre_fichero);

        unsigned num_nodos;
        fichero >> num_nodos;
        for (unsigned i = 0; i < num_nodos; ++i)
        {
            tipo_nodo nombre;
            fichero >> nombre;
            unsigned num_vecinos;
            fichero >> num_vecinos;
            std::vector<tipo_nodo> vecinos(num_vecinos);
            for (unsigned j = 0; j < num_vecinos; ++j)
               fichero >> vecinos[j];

            crea_nodo(nombre, vecinos);
        }
    }
    std::vector<std::pair<Nodo_grafo::tipo_operador, Nodo_grafo>> Nodo_grafo::sucesores() const
    {
        auto nodos_sucesores = grafo.vecinos(nodo);
        std::vector<std::pair<tipo_nodo, Nodo_grafo>> hijos;
        for (const auto& x : nodos_sucesores)
            hijos.push_back({x, Nodo_grafo(x)});

        return hijos;
    }
}
