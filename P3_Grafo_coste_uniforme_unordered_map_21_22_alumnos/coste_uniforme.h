#include <iostream>

namespace problema_busqueda
{
    template <typename T>
    void fast_vector_erase(std::vector<T>& v, size_t pos)//elimina el ultimo elemento del array y lo pone en la posicion indicada
    {
        v[pos] = v.back();
        v.pop_back();
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

            //sobrecargamos el operador < para que la funcion min_element pueda encontrar el nodo con menor coste
            bool operator< (const Nodo& nodo) const
            {
                return coste_ruta < nodo.coste_ruta;
            }
        };

        std::vector<Nodo> frontera;
        std::vector<Nodo_busqueda> visitados;
        std::unordered_map<tipo_clave, tipo_coste> claves;//

        frontera.push_back(Nodo{estado_inicial, Problema::operador_nulo(), 0, 0});
        claves[estado_inicial.clave()] = 0;

        bool exito = false;
        size_t nodos_expandidos = 0; // Para comparar entre algoritmos
        tipo_coste coste_ruta_actual = 0;


        while (exito == false && !frontera.empty())
        {
            ++nodos_expandidos;

            //1* En esta zona del codigo vamos vaciando la frontera del nodo dando prioridad a los de menor coste
            auto indice = std::distance(frontera.begin(), std::min_element(frontera.begin(), frontera.end()));
            //Obtenemos el nodo con menor coste de la frontera

            std::cout << "FRONTERA\n";
            for (auto x : frontera)
                std::cout << x.estado << " " << x.coste_ruta << " ";
            std::cout << std::endl;

            std::cout << "INDICE: " << indice << std::endl;

            visitados.push_back(frontera[indice]);  // Slicing benigno //Metemos el minimo de la frontera en los nodos visitados
            coste_ruta_actual = frontera[indice].coste_ruta;//Sacamos el coste de ruta del minimo
            fast_vector_erase(frontera, indice);//ultimo valor de frontera-> posicion indicada en frontera

            std::cout << "VISITADOS\n";
            for (auto x : visitados)
                std::cout << x.estado << " ";
            std::cout << std::endl;
            //*1

            exito = visitados.back().estado == estado_objetivo; // Prueba de meta; Comparamos con el ultimo nodo visitado

            if (exito == false)// Expandimos al siguiente nodo
            {
                std::cout << "PADRE\n" << visitados.back().estado << " " << coste_ruta_actual << std::endl;
                auto padre = visitados.size() - 1;
                for (auto& [op, estado_hijo] : visitados.back().estado.sucesores())
                {

                    auto clave_hijo = estado_hijo.clave();//clave es un string en nuestro caso; El hijo pasa a ser el padre
                    std::cout << estado_hijo << " " << coste_ruta_actual + visitados.back().estado.coste_operador(op) << std::endl;

                    auto coste = coste_ruta_actual + visitados.back().estado.coste_operador(op);

                    //genero un iterador para buscar en claves
                    auto iter = claves.find(clave_hijo);

                    if (claves.count(clave_hijo) == 0)//count devuelve el numero de elementos en el rango; devuelve cuantos elementos hay con el nombre de clave_hijo
                    {
                        //si el no encuentra nodos que coincidan con el string->Generamos la frontera del nuevo nodo
                        frontera.push_back(Nodo{ estado_hijo, op, padre, coste_ruta_actual +
                                           visitados.back().estado.coste_operador(op) });

                        claves.insert({clave_hijo,coste});
                        std::cout <<"insertado"<< estado_hijo << " " << coste_ruta_actual + visitados.back().estado.coste_operador(op) << std::endl;
                    }
                    //Esto es lo primero que se me ocurrió, pero luego me dí cuenta de que tenía un coste computacional muy alto.
                    //Asi que busqué algo mejor.
                    /*
                    else {
                        for (size_t i = 0; i < frontera.size(); i++)
                        {

                            if (frontera[i].estado.clave() == clave_hijo && frontera[i].coste_ruta>coste)
                            {
                                frontera.push_back(Nodo{ estado_hijo, op, padre, coste_ruta_actual +
                                           visitados.back().estado.coste_operador(op) });
                            }
                        }
                    }*/
                    else
                    {
                        // en caso de que se encuentre un nodo llamado igual que clave_hijo y que su coste sea menor al que ya está almacenado
                        // Como ya habrás visto en otros de mi entregables, a veces hago redundancias para entrar en los bucles.
                        // Me gusta hacerlo para asegurarme de que toda funciona bien y no dejar ningún cabo suelto.
                        // En este caso habría añadido esta condición al siguiente if: (iter != claves.end() && iter->second > coste)
                        // No hace falta hacerlo y lo sé muy bien, pero como me lo habías comentado en algunos entregables, te explico aquí por que lo hago.
                        // No es otra cosa más que una manía mía
                        if ( iter->second > coste) {
                        frontera.push_back(Nodo{ estado_hijo, op, padre, coste_ruta_actual +
                                           visitados.back().estado.coste_operador(op) });
                        }
                    }
                }
            }
           // frontera.clear(); // Eliminad esta linea
        }

        std::vector<tipo_operador> secuencia_operadores;
        if (exito)
            secuencia_operadores = set_secuencia_operadores(visitados);

        return Solucion<Problema> {exito, secuencia_operadores, nodos_expandidos, coste_ruta_actual};
    }


}

