#ifndef PROBLEMA_BUSQUEDA_H_INCLUDED
#define PROBLEMA_BUSQUEDA_H_INCLUDED

#include "grafo.h"

// Esta primera práctica muestra una versión pobre desde el punto de vista de la programación
// dado que el problema (encontrar una trayectoria en un grafo) y el algoritmo (amplitud)
// están fuertemente acoplados, como muestra la necesidad de incluir "grafo.h"

namespace problema_busqueda
{
    struct Nodo_busqueda
    {
        grafo::Nodo_grafo estado;  // Acoplamiento del algoritmo con el problema: ¡¡MAL!!
        std::string operador;      // Operador tiene un tipo string: ¡¡MAL!!
        size_t padre;
    };

    struct Solucion
    {
        bool exito;
        std::vector<std::string> secuencia_operadores;
        size_t nodos_expandidos;
    };

    std::vector<std::string> set_secuencia_operadores(const std::vector<Nodo_busqueda>& lista, int indice);
    Solucion amplitud(grafo::Nodo_grafo& estado_inicial, grafo::Nodo_grafo& estado_objetivo);
    // bool repetido_lista_completa(const std::vector<Nodo_busqueda>& lista, const grafo::Nodo_grafo& estado);
}

#endif // PROBLEMA_BUSQUEDA_H_INCLUDED
