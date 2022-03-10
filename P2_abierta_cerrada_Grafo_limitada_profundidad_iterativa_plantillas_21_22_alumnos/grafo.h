#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include <vector>
#include <string>
#include <sstream>
#include <map>

namespace grafo
{
    using tipo_nodo = std::string;  // Definimos el tipo de dato tipo_nodo y lo hacemos público dentro del namespace
    class Grafo
    {
        public:

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

            void crea_nodo(const tipo_nodo& s, const std::vector<tipo_nodo>& v)
            {
                nodos[s] = v;
            }
            bool existe_nodo(const tipo_nodo& nodo) const
            {
                return nodos.find(nodo) != nodos.end();
            }
        private:
            std::map<tipo_nodo, std::vector<tipo_nodo>> nodos;
            void inicializa_grafo(const std::string& nombre_fichero);
    };

    class Nodo_grafo
    {
        public:
            using tipo_operador = std::string; //Definimos el tipo de dato tipo_operador y lo hacemos público dentro de la clase
            Nodo_grafo() {}
            Nodo_grafo(const tipo_nodo& nodo): nodo{nodo}
            {
                if (!grafo.existe_nodo(nodo))
                {
                    std::stringstream cadena;
                    cadena << *this;
                    throw std::logic_error("No existe en el grafo un nodo con el valor " +
                                           cadena.str());
                }
            }
            std::vector<std::pair<tipo_operador, Nodo_grafo>> sucesores() const;
            Nodo_grafo sucesor(const tipo_operador& op) const
            {
                return op;
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
