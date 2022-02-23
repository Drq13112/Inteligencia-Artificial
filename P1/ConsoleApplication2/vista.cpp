# include "vista.h"
#include <iostream>

namespace vista
{
    std::string solicita_string(const std::string& mensaje)
    {
        std::string nombre;
        std::cout << mensaje;
        std::cin >> nombre;
        return nombre;
    }

    void muestra_solucion(const problema_busqueda::Solucion& solucion, const grafo::Nodo_grafo& inicio)
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
        std::cout << "\n\nNumero de nodos expandidos: " << solucion.nodos_expandidos << std::endl;
        std::cout << "************************************\n";
    }
}
