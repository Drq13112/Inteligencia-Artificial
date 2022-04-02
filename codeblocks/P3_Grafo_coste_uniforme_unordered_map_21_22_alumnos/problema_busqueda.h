#ifndef PROBLEMA_BUSQUEDA_H_INCLUDED
#define PROBLEMA_BUSQUEDA_H_INCLUDED

#include <cstddef>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <deque>

namespace problema_busqueda
{
    template<typename Problema>
    using tipo_operador = typename Problema::tipo_operador;

    template<typename Problema>
    using tipo_coste = typename Problema::tipo_coste;

    template<typename Problema>
    using tipo_clave = typename Problema::tipo_clave;

    template<typename Problema>
    struct Nodo_busqueda
    {
        Nodo_busqueda() {}
        Nodo_busqueda(const Problema& estado, const tipo_operador<Problema>& operador, size_t padre):
            estado(estado), operador(operador), padre(padre) {}
        Problema estado;
        tipo_operador<Problema> operador;
        size_t padre;
    };

    template<typename Problema>
    struct Solucion
    {
        bool exito;
        std::vector<tipo_operador<Problema>> secuencia_operadores;
        size_t nodos_expandidos;
        tipo_coste<Problema> coste;
    };

    template<typename Problema>
    std::vector<tipo_operador<Problema>> set_secuencia_operadores(const std::vector<Nodo_busqueda<Problema>>& lista)
    {
        size_t indice = lista.size() - 1;
        std::vector<tipo_operador<Problema>> secuencia_operadores;
        while (indice > 0)
        {
            secuencia_operadores.push_back(lista[indice].operador);
            indice = lista[indice].padre;
        }
        std::reverse(secuencia_operadores.begin(), secuencia_operadores.end());
        return secuencia_operadores;
    }
}

#include "amplitud.h"
#include "coste_uniforme.h"
#endif // PROBLEMA_BUSQUEDA_H_INCLUDED
