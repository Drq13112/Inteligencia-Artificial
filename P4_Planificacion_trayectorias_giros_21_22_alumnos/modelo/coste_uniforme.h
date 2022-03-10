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

        struct Nodo:Nodo_busqueda  //Herencia
        {
            Nodo(const Problema& estado, const tipo_operador& op, size_t padre, tipo_coste coste_ruta):
                Nodo_busqueda{estado, op, padre}, coste_ruta{coste_ruta} {}
            tipo_coste coste_ruta;
            bool operator< (const Nodo& nodo) const
            {
                return coste_ruta < nodo.coste_ruta;
            }
        };

        std::vector<Nodo> frontera;
        std::vector<Nodo_busqueda> visitados;
        std::unordered_set<tipo_clave> claves;

        frontera.push_back(Nodo{estado_inicial, Problema::operador_nulo(), 0, 0});
        claves.insert(estado_inicial.clave());

        bool exito = false;
        size_t nodos_expandidos = 0; // Para comparar entre algoritmos
        tipo_coste coste_ruta_actual = 0;

        while (exito == false && !frontera.empty())
        {
            ++nodos_expandidos;

            auto indice = std::distance(frontera.begin(), std::min_element(frontera.begin(), frontera.end()));

            visitados.push_back(frontera[indice]);  // Slicing benigno
            coste_ruta_actual = frontera[indice].coste_ruta;
            fast_vector_erase(frontera, indice);

            exito = visitados.back().estado == estado_objetivo; // Prueba de meta

            if (exito == false)
            {
                auto padre = visitados.size() - 1;
                for (auto& [op, estado_hijo] : visitados.back().estado.sucesores())
                {
                    auto clave_hijo = estado_hijo.clave();
                    auto coste_ruta_hijo = coste_ruta_actual + visitados.back().estado.coste_operador(op);

                    if (claves.count(clave_hijo)== 0)
                    {
                        claves.insert(clave_hijo);
                        frontera.push_back(Nodo{estado_hijo, op, padre, coste_ruta_hijo});
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

