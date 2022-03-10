#ifndef PROBLEMA_BUSQUEDA_H_INCLUDED
#define PROBLEMA_BUSQUEDA_H_INCLUDED

#include <cstddef>
#include <vector>
#include <deque>
#include <algorithm>

namespace problema_busqueda
{
    template<typename Problema>
    using tipo_operador = typename Problema::tipo_operador;//No entiendo muy bien esta linea de código

    template<typename Problema>
    struct Nodo_busqueda
    {
        //Constructor por defecto de la estructura
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
        std::vector<tipo_operador<Problema>> secuencia_operadores;//vector<Problema::Tipo_operador<Problema>> ????
        size_t nodos_expandidos;
    };

    template<typename T, typename Problema>
    bool repetido_contenedor_nodo_busqueda(const T& contenedor, const Problema& estado)
    {
        for (auto &x : contenedor)
            if (x.estado == estado)
                return true;
        return false;
    }

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
#include "profundidad.h"

#endif // PROBLEMA_BUSQUEDA_H_INCLUDED
