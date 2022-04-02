#ifndef NODO_CUADRICULA_H_INCLUDED
#define NODO_CUADRICULA_H_INCLUDED
#include <vector>
#include <iostream>
#include <cstddef>
#include <cstdint>
#include "cuadricula.h"

namespace cuadricula
{
    enum class Direccion: uint8_t {N=0, S, E, O, NE, NO, SE, SO, EN, ES, ON, OS};
    struct Posicion_2d
    {
        Punto_2d punto;
        Direccion direccion;
    };
    enum class Operador: uint8_t {A=0, GD, GI, Nulo};
    inline std::ostream& operator << (std::ostream& os, const Operador& op)
    {
        if (op == Operador::A)
            os << "Avanzar";
        else if (op == Operador::GD)
            os << "Girar a la derecha";
        else if (op == Operador::GI)
            os << "Girar a la izquierda";
        return os;
    }

    class Nodo_cuadricula
    {
        public:
            using tipo_coste = double;
            using tipo_operador = Operador;
            using tipo_clave = unsigned;

            Nodo_cuadricula() {}

            Nodo_cuadricula(const Posicion_2d& posicion): posicion(posicion) {}

            std::vector<std::pair<tipo_operador, Nodo_cuadricula>> sucesores() const;

            tipo_coste coste_operador(const tipo_operador& op) const;
            tipo_coste heuristica(const Nodo_cuadricula& nodo) const;

            tipo_clave clave() const;
            Nodo_cuadricula sucesor(const tipo_operador& op) const;
            static void set_cuadricula(const cuadricula::Cuadricula& cuad)
            {
                cuadricula=cuad;
                columnas = cuadricula.get_columnas();
                filas = cuadricula.get_filas();
            }
            unsigned get_x() const
            {
                return posicion.punto.x;
            }
            unsigned get_y() const
            {
                return posicion.punto.y;
            }
            Direccion get_direccion() const
            {
                return posicion.direccion;
            }
            static tipo_operador operador_nulo()
            {
                return Operador::Nulo;
            }

            static void set_costes(tipo_coste coste_avanzar, tipo_coste coste_girar)
            {
                Nodo_cuadricula::coste_avanzar = coste_avanzar;
                Nodo_cuadricula::coste_girar = coste_girar;
            }

            friend bool operator == (const Nodo_cuadricula& nodo1, const Nodo_cuadricula& nodo2)
            {
                return nodo1.posicion.punto.x == nodo2.posicion.punto.x &&
                       nodo1.posicion.punto.y == nodo2.posicion.punto.y &&
                       nodo1.posicion.direccion == nodo2.posicion.direccion;
            }
            friend std::ostream& operator << (std::ostream& os, const Nodo_cuadricula& nodo)
            {
                std::string direccion;
                switch(nodo.posicion.direccion)
                {
                    case Direccion::E:
                        direccion = "E";
                        break;
                    case Direccion::S:
                        direccion = "S";
                        break;
                    case Direccion::O:
                        direccion = "O";
                        break;
                    case Direccion::N:
                        direccion = "N";
                        break;
                    case Direccion::SE:
                        direccion = "SE";
                        break;
                    case Direccion::NE:
                        direccion = "NE";
                        break;
                    case Direccion::SO:
                        direccion = "SO";
                        break;
                    case Direccion::NO:
                        direccion = "NO";
                        break;
                    case Direccion::ES:
                        direccion = "ES";
                        break;
                    case Direccion::OS:
                        direccion = "OS";
                        break;
                    case Direccion::EN:
                        direccion = "EN";
                        break;
                    case Direccion::ON:
                        direccion = "ON";
                        break;

                }
                os << "[(" << nodo.posicion.punto.x << "," << nodo.posicion.punto.y << "), "
                   << direccion << "]";
                return os;
            }
        private:
            static Cuadricula cuadricula;
            static unsigned filas;
            static unsigned columnas;
            static tipo_coste coste_avanzar;
            static tipo_coste coste_girar;
            Posicion_2d posicion;
    };
}

#endif
