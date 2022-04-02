#include <iostream>
#include <queue>

namespace problema_busqueda
{
    template<typename Problema>
    Solucion<Problema> voraz(Problema& estado_inicial, Problema& estado_objetivo)
    {
        using tipo_operador = tipo_operador<Problema>;
        using tipo_clave = tipo_clave<Problema>;
        using tipo_coste = tipo_coste<Problema>;
        using Nodo_busqueda = Nodo_busqueda<Problema>;
        struct Nodo:Nodo_busqueda  //Herencia
        {
            Nodo(const Problema& estado, const tipo_operador& op, size_t padre, tipo_coste coste_ruta, tipo_coste coste_heuristica):
                Nodo_busqueda{estado, op, padre}, coste_ruta{coste_ruta},coste_heuristica{coste_heuristica}{}
            tipo_coste coste_ruta;
            tipo_coste coste_heuristica;

            bool operator< (const Nodo& nodo) const
            {
                if(coste_heuristica == nodo.coste_heuristica)
                {
                    return coste_ruta< nodo.coste_ruta;
                }else{
                return coste_heuristica < nodo.coste_heuristica;}
            }
            //Sobrecargo tanto > como < para que la cola ordene en base al coste_ruta de cada Nodo
            bool operator> (const Nodo& nodo) const
            {

                if(coste_heuristica == nodo.coste_heuristica)
                {
                    //std::cout<<"AQUI"<<std::endl;
                    return coste_ruta> nodo.coste_ruta;

                }else{
                return coste_heuristica > nodo.coste_heuristica;}
            }
        };

        std::priority_queue<Nodo , std::vector<Nodo>,std::greater<Nodo>> frontera;//Con greater indico que quiero ordenar la cola de menor a mayor
        std::vector<Nodo_busqueda> visitados;
        std::unordered_map<tipo_clave, tipo_coste> claves;


        //Ahora hay que hacer el algoritmo de busqueda voraz

        frontera.push(Nodo{estado_inicial, Problema::operador_nulo(), 0, 0,0});
        claves[estado_inicial.clave()] = 0;

        bool exito = false;
        size_t nodos_expandidos = 0; // Para comparar entre algoritmos
        tipo_coste coste_ruta_actual = 0;
        while (exito == false && !frontera.empty())
        {

            ++nodos_expandidos;

            visitados.push_back(frontera.top());  // Slicing benigno //Metemos el minimo de la frontera en los nodos visitados
            coste_ruta_actual = frontera.top().coste_ruta;//Sacamos el coste de ruta del minimo
            //fast_vector_erase(frontera, indice);//ultimo valor de frontera-> posicion indicada en frontera
            frontera.pop();

            exito = visitados.back().estado == estado_objetivo; // Prueba de meta; Comparamos con el ultimo nodo visitado

            if (exito == false)// Expandimos al siguiente nodo
            {
                //std::cout << "PADRE\n" << visitados.back().estado << " " << coste_ruta_actual << std::endl;
                auto padre = visitados.size() - 1;
                for (auto& [op, estado_hijo] : visitados.back().estado.sucesores())
                {

                    auto clave_hijo = estado_hijo.clave();//clave es un string en nuestro caso; El hijo pasa a ser el padre
                    //std::cout << estado_hijo << " " << coste_ruta_actual + visitados.back().estado.heuristica(estado_objetivo) << std::endl;

                    //Coste de ruta
                    auto coste = coste_ruta_actual +visitados.back().estado.coste_operador(op);

                    if (claves.count(clave_hijo) == 0 || claves[clave_hijo] > coste)//count devuelve el numero de elementos en el rango; devuelve cuantos elementos hay con el nombre de clave_hijo
                    {
                        //si el no encuentra nodos que coincidan con el string->Generamos la frontera del nuevo nodo
                        frontera.push(Nodo{ estado_hijo, op, padre, coste_ruta_actual+
                                            visitados.back().estado.coste_operador(op),
                                            visitados.back().estado.heuristica(estado_objetivo)});

                        claves.insert({clave_hijo,coste});
                        //std::cout <<"insertado"<< estado_hijo << " " << coste_ruta_actual + visitados.back().estado.coste_operador(op) << std::endl;
                    }
                }
            }
        }







     std::vector<tipo_operador> secuencia_operadores;
        if (exito)
            secuencia_operadores = set_secuencia_operadores(visitados);

        return Solucion<Problema> {exito, secuencia_operadores, nodos_expandidos, coste_ruta_actual};
    }
}
