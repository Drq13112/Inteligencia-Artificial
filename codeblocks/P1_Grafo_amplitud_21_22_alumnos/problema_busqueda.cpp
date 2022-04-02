#include "problema_busqueda.h"
#include <algorithm>
#include <iostream>

namespace problema_busqueda
{
    bool repetido_lista_completa(const std::vector<Nodo_busqueda>& lista, const grafo::Nodo_grafo& estado)
    {
        Nodo_busqueda nodo;
        bool interno = false;
        for (size_t i = 0; i < lista.size(); i++)
        {
            nodo = lista[i];

            if (estado == nodo.estado)//comparo con cada nodo que ya hay en la lista
            {   
                interno = true;
            }
        }
        return interno;
    }
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


        // Dado que el estado inicial no tiene ningún antecesor, ponemos que el es su propio padre
        // Otra opción hubiese sido poner -1, pero en este caso habría que declara int padre en lugar de size_t padre
        // Del mismo modo, al estado inicial no se llega aplicando ningún operador. De ahí, la existencia
        // de la función miembro operador_nulo()
        lista.push_back({ estado_inicial, grafo::Nodo_grafo::operador_nulo(), 0 });

        size_t indice = 0; // Variable que indica cual será el nodo a expandir
        bool exito = false;
        size_t nodos_expandidos = 0; // Para comparar entre algoritmos

        while (exito == false && indice < lista.size())// se terminará el bucle cuando se hayan examinado todos los nodos
        {   

            /*
            * Aspecto de lista:
            * Estado      Operador     Padre
            *  A           null         0//A
            *  B            B           0//A
            *  C            C           0//A
            *  D            D           0//A
            *  A            A           1//B //Este habría que eliminarlo para que no haya repetidos en caso de insertar el indice
            *  E            E           1//B
            *  I            I           1//B
            */

            //Por si el nodo no se ha encontrado
            if (indice >= lista.size())
            {
            
                std::cout << "No se ha podido encontrar el nodo objetivo" << std::endl;
                break;
            }
            
            nodo = lista[indice];
            estado_inicial = nodo.estado;

            //Coloco aquí la comprobación, porque en teoría se tiene que esperar a que se expanda 
            // el nodo objetivo. Pero se podría hacer comprobando los hijos de cada nodo
            if (estado_inicial == estado_objetivo)
            {
                exito = true;
            }
            //En caso de que no sea el nodo objetivo, expandimos el nodo
            nodos_expandidos++;// Como no estamos expandiendo al siguiente nodo, incrementamos la variable
            
            
            if (exito == false) {
                //Expandimos el circulo del nodo-> Sucede una vez que se han expandido todos los nodos del nivel
                //Uso un bucle burbuja para comprobar si uno de los nodos que vamos a meter en la lista ya está incluido
                hijos = estado_inicial.sucesores();
                for (size_t n = 0; n < hijos.size(); n++)
                {
                    hijo = hijos[n];// Saco uno de los hijos
                    nodo_repetido = repetido_lista_completa(lista, hijo.second);
                    if (nodo_repetido == false)
                    {
                        lista.push_back({ hijo.second,hijo.first, indice });
                        num_hijos_en_lista++;

                    }
                    nodo_repetido = false;
                }
                //Ahora actualizamos el nodo a expandir-> uno de los hijos del nodo anterior
                //Para ello expandimos el último nodo de la lista, para ello podemos usar el propio indice
            
            indice++;
            
            }
        }

        for (auto& it : lista)
        {
            std::cout << "Operador: "+it.operador+" Posicion Padre: "<<it.padre<< std::endl;
        }

        std::vector<std::string> secuencia_operadores;  // Nuevo acoplamiento entre problema y algoritmo ¡¡MAL!!
        if (exito)
            secuencia_operadores = set_secuencia_operadores(lista, indice);

        return Solucion{exito, secuencia_operadores, nodos_expandidos};
    }

    // Devuelve la solución como secuencia de operadores
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
}
