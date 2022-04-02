namespace problema_busqueda
{
    template<typename Problema>
    Solucion<Problema> amplitud(Problema& estado_inicial, Problema& estado_objetivo)
    {
        using tipo_operador = tipo_operador<Problema>;
        using tipo_clave = typename Problema::tipo_clave;
        using tipo_coste = typename Problema::tipo_coste;
        using Nodo_busqueda = Nodo_busqueda<Problema>;

        std::deque<Nodo_busqueda> frontera;
        std::vector<Nodo_busqueda> visitados;
        std::unordered_set<tipo_clave> claves;

        frontera.push_back(Nodo_busqueda{estado_inicial, Problema::operador_nulo(), 0});
        claves.insert(estado_inicial.clave());

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
                for (auto& [op, estado_hijo] : visitados.back().estado.sucesores())
                {
                    auto clave_hijo = estado_hijo.clave();
                    if (claves.count(clave_hijo) == 0)
                    {
                        frontera.push_back(Nodo_busqueda{estado_hijo, op, padre});
                        claves.insert(clave_hijo);
                    }
                }
            }
        }

        std::vector<tipo_operador> secuencia_operadores;
        if (exito)
            secuencia_operadores = set_secuencia_operadores(visitados);

        return Solucion<Problema>{exito, secuencia_operadores, nodos_expandidos, static_cast<tipo_coste>(secuencia_operadores.size())};
    }
}
