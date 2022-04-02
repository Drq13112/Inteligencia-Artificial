#include <iostream>
#include <queue>

namespace problema_busqueda
{
    template <typename T>
    void fast_vector_erase(std::vector<T>& v, size_t pos)
    {
        v[pos] = v.back();
        v.pop_back();
    }

    //He creado una nueva funcion para mostrar el contenido de la cola de prioridad
    template<typename T>
    void print_queue(T q) { // NB: pass by value so the print uses a copy
        while (!q.empty()) {
            std::cout << q.top().estado << " " << q.top().coste_ruta << " ";
            q.pop();
        }
        std::cout << std::endl;
    }

    template<typename Problema>
    Solucion<Problema> coste_uniforme(Problema& estado_inicial, Problema& estado_objetivo)
    {
        using tipo_operador = tipo_operador<Problema>;
        using tipo_clave = tipo_clave<Problema>;
        using tipo_coste = tipo_coste<Problema>;
        using Nodo_busqueda = Nodo_busqueda<Problema>;

        struct Nodo:Nodo_busqueda  //Herencia
        {
            Nodo(const Problema& estado, const tipo_operador& op, size_t padre, tipo_coste coste_ruta):
                Nodo_busqueda{estado, op, padre}, coste_ruta{coste_ruta} {}
            tipo_coste coste_ruta;
            bool operator< (const Nodo& nodo) const
            {
                return coste_ruta < nodo.coste_ruta;
            }
            //Sobrecargo tanto > como < para que la cola ordene en base al coste_ruta de cada Nodo
            bool operator> (const Nodo& nodo) const
            {
                return coste_ruta > nodo.coste_ruta;
            }
        };

        std::priority_queue<Nodo , std::vector<Nodo>,std::greater<Nodo>> frontera;//Con greater indico que quiero ordenar la cola de menor a mayor
        std::vector<Nodo_busqueda> visitados;
        std::unordered_map<tipo_clave, tipo_coste> claves;

        frontera.push(Nodo{estado_inicial, Problema::operador_nulo(), 0, 0});
        claves[estado_inicial.clave()] = 0;

        bool exito = false;
        size_t nodos_expandidos = 0; // Para comparar entre algoritmos
        tipo_coste coste_ruta_actual = 0;


        while (exito == false && !frontera.empty())
        {
            //---------------------------------------------------------------------------------------------------------
            ++nodos_expandidos;

            //En esta zona del codigo vamos vaciando la frontera del nodo dando prioridad a los de menor coste
            //auto indice = std::distance(frontera.begin(), std::min_element(frontera.begin(), frontera.end()));
            //Obtenemos el nodo con menor coste de la frontera

            //std::cout << "FRONTERA\n";
            //print_queue(frontera);


            visitados.push_back(frontera.top());  // Slicing benigno //Metemos el minimo de la frontera en los nodos visitados
            coste_ruta_actual = frontera.top().coste_ruta;//Sacamos el coste de ruta del minimo
            //fast_vector_erase(frontera, indice);//ultimo valor de frontera-> posicion indicada en frontera
            frontera.pop();

            /*
            std::cout << "VISITADOS\n";
            for (auto x : visitados)
                std::cout << x.estado << " ";
            std::cout << std::endl;
            */

            exito = visitados.back().estado == estado_objetivo; // Prueba de meta; Comparamos con el ultimo nodo visitado

            if (exito == false)// Expandimos al siguiente nodo
            {
                //std::cout << "PADRE\n" << visitados.back().estado << " " << coste_ruta_actual << std::endl;
                auto padre = visitados.size() - 1;
                for (auto& [op, estado_hijo] : visitados.back().estado.sucesores())
                {
                    //definicion de sucesores:
                    //std::vector<std::pair<tipo_operador, Nodo_grafo>> sucesores() const;

                    auto clave_hijo = estado_hijo.clave();//clave es un string en nuestro caso; El hijo pasa a ser el padre
                    //std::cout << estado_hijo << " " << coste_ruta_actual + visitados.back().estado.coste_operador(op) << std::endl;

                    auto coste = coste_ruta_actual + visitados.back().estado.coste_operador(op);

                    //genero un iterador para buscar en claves
                    auto iter = claves.find(clave_hijo);

                    if (claves.count(clave_hijo) == 0)//count devuelve el numero de elementos en el rango; devuelve cuantos elementos hay con el nombre de clave_hijo
                    {
                        //si el no encuentra nodos que coincidan con el string->Generamos la frontera del nuevo nodo
                        frontera.push(Nodo{ estado_hijo, op, padre, coste_ruta_actual +
                                           visitados.back().estado.coste_operador(op) });

                        claves.insert({clave_hijo,coste});
                        //std::cout <<"insertado"<< estado_hijo << " " << coste_ruta_actual + visitados.back().estado.coste_operador(op) << std::endl;
                    }
                    else
                    {
                        // en caso de que se encuentre un nodo llamado igual que clave_hijo y que su coste sea menor al que ya est� almacenado
                        if (iter->second > coste){
                        frontera.push(Nodo{ estado_hijo, op, padre, coste_ruta_actual +
                                           visitados.back().estado.coste_operador(op) });
                        }
                    }
                }
            }
            //---------------------------------------------------------------------------------------------------------
           // frontera.clear(); // Eliminad esta linea
        }

        std::vector<tipo_operador> secuencia_operadores;
        if (exito)
            secuencia_operadores = set_secuencia_operadores(visitados);

        return Solucion<Problema> {exito, secuencia_operadores, nodos_expandidos, coste_ruta_actual};
    }


}

