#include "grafo.h"
#include <iostream>
#include <fstream>


namespace grafo
{
    Grafo Nodo_grafo::grafo = Grafo();  // Inicializaci�n variable est�tica de la clase

    void Grafo::carga_grafo(const std::string& nombre_fichero)
    {
        std::ifstream fichero(nombre_fichero);
        if (!fichero)
            throw std::runtime_error("No se pudo abrir el fichero " + nombre_fichero);

        int num_nodos, num_sucesores;
        std::vector<std::string>sucesores;
        std::string nombre,letra;
        fichero>>num_nodos;
        
        for (int j = 0; j < num_nodos; ++j)
        {
            fichero >> nombre;
            fichero >> num_sucesores;
            
            for (int i = 0; i < num_sucesores; ++i)
            {
                fichero >> letra;
                sucesores.push_back(letra);
                //std::cout << letra;
            }
            crea_nodo(nombre, sucesores);// nodos[nombre]=sucesores;
            std::cout << "Nodo padre:"+nombre << std::endl;
            std::cout << "sucesores:" << std::endl;
            for (auto& it : sucesores) 
            { 
                std::cout << it<<" ";
            } //Para ver por terminal que el vector esta vacio
            std::cout << " " << std::endl;
            sucesores.clear();
        }
        //Cierro el fichero
        fichero.close();
    }

    std::vector<std::pair<std::string, Nodo_grafo>> Nodo_grafo::sucesores() const
    {
        auto vector_nombres = grafo.vecinos(nombre);
        std::vector<std::pair<std::string, Nodo_grafo>> hijos;
        for (const auto& x : vector_nombres)
            hijos.push_back({x, Nodo_grafo(x)});

        return hijos;
    }
}
