namespace problema_busqueda
{
    template<typename Problema>
    Solucion<Problema> amplitud(Problema& estado_inicial, Problema& estado_objetivo)
    {
        using tipo_operador = tipo_operador<Problema>;
        using Nodo_busqueda = Nodo_busqueda<Problema>;

        std::deque<Nodo_busqueda> frontera;
        std::vector<Nodo_busqueda> visitados;

        frontera.push_back(Nodo_busqueda{estado_inicial, Problema::operador_nulo(), 0});

        bool exito = false;
        size_t nodos_expandidos = 0; // Para comparar entre algoritmos

        while (exito == false && !frontera.empty())
        {
            ++nodos_expandidos;

            visitados.push_back(frontera.front());
            frontera.pop_front();

            exito = visitados.back().estado == estado_objetivo; // Prueba de meta

            if (exito == false)
            {
                auto padre = visitados.size() - 1;
                for (auto& [op, estado] : visitados.back().estado.sucesores())
                    if (!repetido_contenedor_nodo_busqueda(visitados, estado) &&
                            !repetido_contenedor_nodo_busqueda(frontera, estado))
                        frontera.push_back(Nodo_busqueda{estado, op, padre});
            }
        }

        std::vector<tipo_operador> secuencia_operadores;
        if (exito)
            secuencia_operadores = set_secuencia_operadores(visitados);

        return Solucion<Problema>{exito, secuencia_operadores, nodos_expandidos};
    }
}
