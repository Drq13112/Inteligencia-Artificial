#include <iostream>

namespace problema_busqueda
{
    template <typename T>
    void fast_vector_erase(std::vector<T>& v, size_t pos)
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

        struct Nodo_con_coste:Nodo_busqueda  //Herencia
        {
            Nodo_con_coste(const Problema& estado, const tipo_operador& op, size_t padre, tipo_coste coste_ruta):
                Nodo_busqueda{estado, op, padre}, coste_ruta{coste_ruta} {}
            tipo_coste coste_ruta;
            bool operator< (const Nodo_con_coste& nodo) const
            {
                return coste_ruta < nodo.coste_ruta;
            }
        };

        std::vector<Nodo_con_coste> frontera;
        std::vector<Nodo_busqueda> visitados;
        std::unordered_set<tipo_clave> claves;

        frontera.push_back(Nodo_con_coste{estado_inicial, Problema::operador_nulo(), 0, 0});
        claves.insert(estado_inicial.clave());


        bool exito = false;
        size_t nodos_expandidos = 0; // Para comparar entre algoritmos
        tipo_coste coste_ruta_actual = 0;

        while (exito == false && !frontera.empty())
        {
            ++nodos_expandidos;

            auto indice = std::distance(frontera.begin(), std::min_element(frontera.begin(), frontera.end()));
            //me devuelve la posición en el vector del elemento de la frontera que me toca expandir, por que es el más pequeño

            std:: cout << "FRONTERA\n";
            for (auto x : frontera)
                std::cout << x.estado << " " << x.coste_ruta << " ";
            std::cout << std::endl;

            std::cout << "INDICE: " << indice << std::endl;
            visitados.push_back(frontera[indice]);  // Slicing benigno
            coste_ruta_actual = frontera[indice].coste_ruta;
            fast_vector_erase(frontera, indice);

            std:: cout << "VISITADOS\n";
            for (auto x : visitados)
                std::cout << x.estado << " ";
            std::cout << std::endl;

            exito = visitados.back().estado == estado_objetivo; // Prueba de meta

            if (exito == false)
            {
                std::cout << "PADRE\n" << visitados.back().estado << " " << coste_ruta_actual << std::endl;
                auto padre = visitados.size() - 1;
                for (auto& [op, estado_hijo] : visitados.back().estado.sucesores())
                {
                    auto clave_hijo = estado_hijo.clave();
                    std::cout << estado_hijo << " " << coste_ruta_actual + visitados.back().estado.coste_operador(op) << std::endl;
                    if (claves.count(clave_hijo) == 0)
                    {
                        frontera.push_back(Nodo_con_coste{estado_hijo, op, padre, coste_ruta_actual +
                                           visitados.back().estado.coste_operador(op)});
                        claves.insert(clave_hijo);
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

