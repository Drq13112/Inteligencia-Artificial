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
        std::unordered_map<tipo_clave, tipo_coste> claves;

        frontera.push_back(Nodo{estado_inicial, Problema::operador_nulo(), 0, 0});
        claves[estado_inicial.clave()] = 0;

        bool exito = false;
        size_t nodos_expandidos = 0; // Para comparar entre algoritmos
        tipo_coste coste_ruta_actual = 0;

        while (exito == false && !frontera.empty())
        {
            // TODO
            frontera.clear(); // Eliminad esta linea
        }

        std::vector<tipo_operador> secuencia_operadores;
        if (exito)
            secuencia_operadores = set_secuencia_operadores(visitados);

        return Solucion<Problema> {exito, secuencia_operadores, nodos_expandidos, coste_ruta_actual};
    }


}

