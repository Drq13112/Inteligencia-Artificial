#include "problema_busqueda.h"
#include <algorithm>
#include <iostream>

namespace problema_busqueda
{
    Solucion amplitud(grafo::Nodo_grafo& estado_inicial, grafo::Nodo_grafo& estado_objetivo)
    {
        std::vector<Nodo_busqueda> lista;//array de estructuras
        grafo::Nodo_grafo Nodo_sucesor;
        std::vector<std::pair<std::string, grafo::Nodo_grafo>> hijos;
        std::pair<std::string, grafo::Nodo_grafo> hijo;
        size_t num_hijos_en_lista = 0;
        Nodo_busqueda nodo;
        bool nodo_repetido = false;
        //std::string nombre_nodo;


        // Dado que el estado inicial no tiene ning�n antecesor, ponemos que el es su propio padre
        // Otra opci�n hubiese sido poner -1, pero en este caso habr�a que declara int padre en lugar de size_t padre
        // Del mismo modo, al estado inicial no se llega aplicando ning�n operador. De ah�, la existencia
        // de la funci�n miembro operador_nulo()
        lista.push_back({ estado_inicial, grafo::Nodo_grafo::operador_nulo(), 0 });

        size_t indice = 0; // Variable que indica cual ser� el nodo a expandir
        bool exito = false;
        size_t nodos_expandidos = 0; // Para comparar entre algoritmos

        while (exito == false && indice < lista.size())// se terminar� el bucle cuando se hayan examinado todos los nodos
        {   

            /*
            * Aspecto de lista:
            * Estado      Operador     Padre
            *  A           null         0//A
            *  B            B           0//A
            *  C            C           0//A
            *  D            D           0//A
            *  A            A           1//B //Este habr�a que eliminarlo para que no haya repetidos en caso de insertar el indice
            *  E            E           1//B
            *  I            I           1//B
            */

              
            //Expandimos el circulo del nodo-> Sucede una vez que se han expandido todos los nodos del nivel
            //Uso un bucle burbuja para comprobar si uno de los nodos que vamos a meter en la lista ya est� incluido
            hijos = estado_inicial.sucesores();
            for (size_t n = 0; n<hijos.size(); n++)
            {
                hijo = hijos[n];// Saco uno de los hijos
                for(size_t i=0;i<lista.size();i++)
                {
                    nodo = lista[i];

                    nodo_repetido = repetido_lista_completa(lista, hijo.second);

                    if (hijo.second == nodo.estado)//comparo con cada nodo que ya hay en la lista
                    {
                        nodo_repetido = true;
                    }
                }
                if (nodo_repetido==false)
                {
                    lista.push_back({ hijo.second,hijo.first, indice });
                    num_hijos_en_lista++;
                }
                nodo_repetido = false;
            }
            //Ahora actualizamos el nodo a expandir-> uno de los hijos del nodo anterior
            //Para ello expandimos el �ltimo nodo de la lista, para ello podemos usar el propio indice

            indice++;// nodo completado, pasamos al siguiente nodo
            nodos_expandidos++;
            if (indice<lista.size())
            {
                nodo = lista[indice];
                estado_inicial = nodo.estado;
                if (estado_inicial == estado_objetivo)
                {
                    exito = true;

                }

            }else
            {
               
                std::cout << "No se ha podido encontrar el nodo objetivo" << std::endl;
                break;
            }
        }

        for (auto& it : lista)
        {
            std::cout << "Operador: "+it.operador+" Posicion Padre: "<<it.padre<< std::endl;
        }

        std::vector<std::string> secuencia_operadores;  // Nuevo acoplamiento entre problema y algoritmo ��MAL!!
        if (exito)
            secuencia_operadores = set_secuencia_operadores(lista, indice);

        return Solucion{exito, secuencia_operadores, nodos_expandidos};
    }

    // Devuelve la soluci�n como secuencia de operadores
    std::vector<std::string> set_secuencia_operadores(const std::vector<Nodo_busqueda>&lista, int indice)
    {
        std::vector<std::string> secuencia_operadores;
        while (indice > 0)
        {
            secuencia_operadores.push_back(lista[indice].operador);
            indice = lista[indice].padre;
        }
        std::reverse(secuencia_operadores.begin(), secuencia_operadores.end());
        return secuencia_operadores;
    }


    bool repetido_lista_completa(const std::vector<Nodo_busqueda>& lista, const grafo::Nodo_grafo& estado)
    {
        Nodo_busqueda nodo;
        for (size_t i = 0; i < lista.size(); i++)
        {
            nodo = lista[i];

            if (estado == nodo.estado)//comparo con cada nodo que ya hay en la lista
            {
                return true;
            }
        }
        
    }
}
