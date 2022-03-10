#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include <vector>
#include <string>
#include <sstream>
#include <map>

namespace grafo
{
    using tipo_nodo = std::string;
    class Grafo
    {
        public:
            using tipo_operador = std::string;
            using tipo_clave = std::string;
            using tipo_coste = double;
            Grafo()
            {}
            Grafo(const std::string& nombre_fichero)
            {
                inicializa_grafo(nombre_fichero);
            }
            std::vector<tipo_nodo> vecinos(const tipo_nodo& s) const
            {
                return nodos.at(s);  // nodos[s]
            }

            void crea_nodo(const tipo_nodo& s, const std::vector<tipo_nodo>& v,
                           const std::vector<tipo_coste>& c)
            {
                nodos.insert({s, v});
                std::map<tipo_nodo, tipo_coste> mapa_interno;
                for(size_t i=0; i != v.size(); ++i)
                    mapa_interno.insert({v[i], c[i]});

                costes.insert({s, mapa_interno});
            }
            tipo_coste coste_arista(const tipo_nodo& s1,const tipo_nodo& s2) const
            {
                return costes.at(s1).at(s2); //Sencillez debido al map de map
            }
            bool existe_nodo(const tipo_nodo& nodo) const
            {
                return nodos.find(nodo) != nodos.end();
            }
        private:
            std::map<tipo_nodo, std::vector<tipo_nodo>> nodos;
            std::map<tipo_nodo, std::map<tipo_nodo, tipo_coste>> costes;
            void inicializa_grafo(const std::string& nombre_fichero);
    };

    class Nodo_grafo
    {
        public:
            using tipo_coste = typename Grafo::tipo_coste;
            using tipo_operador = std::string;
            using tipo_clave = std::string;
            Nodo_grafo() {}
            Nodo_grafo(const tipo_nodo& nodo): nodo{nodo}
            {
                if (!grafo.existe_nodo(nodo))
                {
                    std::stringstream cadena;
                    cadena << *this;
                    throw std::logic_error("No existe en el grafo un nodo con el nodo " +
                                           cadena.str());
                }
            }
            std::vector<std::pair<tipo_operador, Nodo_grafo>> sucesores() const;
            Nodo_grafo sucesor(const tipo_operador& op) const
            {
                return op;
            }
            tipo_coste coste_operador(const tipo_operador& op) const
            {
                return grafo.coste_arista(nodo, sucesor(op).nodo);
            }
            tipo_clave clave() const
            {
                return nodo;//en nuestro caso devuelve un string
            }
            static void asigna_grafo(const Grafo& g)
            {
                grafo = g;
            }

            static tipo_operador operador_nulo()
            {
                return "";
            }
            friend std::ostream& operator << (std::ostream& os, const Nodo_grafo& nodo)
            {
                os << nodo.nodo;
                return os;
            }
            friend bool operator == (const Nodo_grafo& nodo1, const Nodo_grafo& nodo2)
            {
                return nodo1.nodo == nodo2.nodo;
            }
        private:
            tipo_nodo nodo;
            static Grafo grafo;
    };
}

#endif // GRAFO_H_INCLUDED
