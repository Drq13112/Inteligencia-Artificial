# include "vista.h"
#include <iostream>

namespace vista
{
    void muestra_solucion(const problema_busqueda::Solucion<grafo::Nodo_grafo>& solucion, const grafo::Nodo_grafo& inicio)
    {
        std::cout << "\n\n************************************\n";
        std::cout << "SOLUCION\n\n";

        if (!solucion.exito)
            std::cout << "No se encontro solucion\n";
        else
        {
            std::cout << inicio;
            auto siguiente = inicio;
            for (auto& op : solucion.secuencia_operadores)
            {
                std::cout << ": Operador " << op << " -->\n";
                siguiente = siguiente.sucesor(op);
                std::cout << siguiente;
            }
        }
        std::cout << "\n\nCoste de la solucion: " << solucion.coste << std::endl;
        std::cout << "\n\nNumero de nodos expandidos: " << solucion.nodos_expandidos << std::endl;
        std::cout << "************************************\n";
    }
}
