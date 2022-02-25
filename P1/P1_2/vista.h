#ifndef VISTA_H_INCLUDED
#define VISTA_H_INCLUDED

#include "grafo.h"
#include "problema_busqueda.h"

namespace vista
{
    std::string solicita_string(const std::string& mensaje);
    void muestra_solucion(const problema_busqueda::Solucion& solucion, const grafo::Nodo_grafo& inicio);
}
#endif // VISTA_H_INCLUDED
