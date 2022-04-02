#ifndef VISTA_H_INCLUDED
#define VISTA_H_INCLUDED

#include "grafo.h"
#include "problema_busqueda.h"
#include <iostream>

namespace vista
{
    using tipo_nodo = grafo::tipo_nodo;
    void muestra_solucion(const problema_busqueda::Solucion<grafo::Nodo_grafo>& solucion, const grafo::Nodo_grafo& inicio);

    template<typename T>
    T solicita_valor(const std::string& mensaje)
    {
        T valor;
        std::cout << mensaje;
        std::cin >> valor;
        return valor;
    }
}
#endif // VISTA_H_INCLUDED
