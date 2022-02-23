#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <sstream>

namespace grafo
{
    // La clase Grafo modela un grafo cuyos nodos son string
    class Grafo
    {
        public:
        //contructor por defecto
            Grafo() {}
            //contructor con argumentos
            Grafo(const std::string& nombre_fichero)
            {
                carga_grafo(nombre_fichero);
            }
            std::vector<std::string> vecinos(const std::string& s) const
            {
                return nodos.at(s);
            }
            void crea_nodo(const std::string& s, const std::vector<std::string>& v)
            {
                nodos[s] = v;//vamos actualizando el array nodos en tiemppo real 
            }
            bool existe_nodo(const std::string& nombre) const
            {
                return nodos.find(nombre) != nodos.end();
            }
        private:
            std::map<std::string, std::vector<std::string>> nodos;
            void carga_grafo(const std::string& nombre_fichero);
    };

    // La clase Nodo_grafo sirve para modelar un estado del grafo en un problema de b�squeda
    // Necesitamos definir:
    //  La funcion sucesores()
    //  EL operador == para la prueba de meta
    //  La funci�n sucesor() para configurar la soluci�n
    class Nodo_grafo
    {
        public:
            Nodo_grafo() {}
            Nodo_grafo(const std::string& nombre): nombre{nombre}
            {
                if (!grafo.existe_nodo(nombre))
                    throw std::logic_error("No existe en el grafo un nodo con el nombre " + nombre);
            }

            // sucesores() devuelve un vector de parejas
            // La pareja representa la dupla (operador, nuevo_estado)
            // El operador se toma como el propio string que representa el nodo vecino
            std::vector<std::pair<std::string, Nodo_grafo>> sucesores() const;

            // La funcion sucesor() devuelve el nuevo estado tras la aplicaci�n del operador
            Nodo_grafo sucesor(const std::string& operador) const
            {
                return Nodo_grafo(operador);
            }
            static void asigna_grafo(const Grafo& g)
            {
                grafo = g;
            }

            // Permite indicar en el problema de b�squeda que al estado inciial
            // no se llega aplicando un operador
            static std::string operador_nulo()
            {
                return "";
            }
            friend std::ostream& operator << (std::ostream& os, const Nodo_grafo& nodo)
            {
                os << nodo.nombre;
                return os;
            }
            friend bool operator == (const Nodo_grafo& nodo1, const Nodo_grafo& nodo2)
            {
                return nodo1.nombre == nodo2.nombre;
            }

        private:
            std::string nombre;
            static Grafo grafo; // static para ahorro de memoria
    };
}

#endif // GRAFO_H_INCLUDED
