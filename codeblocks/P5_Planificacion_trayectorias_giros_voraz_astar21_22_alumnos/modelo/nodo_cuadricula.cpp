#include "nodo_cuadricula.h"
#include <cmath>

namespace cuadricula
{
    Cuadricula Nodo_cuadricula::cuadricula = Cuadricula();
    unsigned Nodo_cuadricula::filas = 0;
    unsigned Nodo_cuadricula::columnas = 0;

    Nodo_cuadricula::tipo_coste Nodo_cuadricula::coste_avanzar = 0;
    Nodo_cuadricula::tipo_coste Nodo_cuadricula::coste_girar = 0;

    // El eje X aumenta hacia el SUR
    // El eje Y aumenta hacia el ESTE
    std::vector<std::pair<Nodo_cuadricula::tipo_operador, Nodo_cuadricula>> Nodo_cuadricula::sucesores() const
    {
        std::vector<std::pair<tipo_operador, Nodo_cuadricula>> hijos;

        switch(posicion.direccion)
        {
            case Direccion::ON:
            case Direccion::EN:
            case Direccion::N:
            {
                auto x = posicion.punto.x - 1;
                auto y = posicion.punto.y;
                auto clave_muro = x*columnas + y;
                if(!cuadricula.get_muros().count(clave_muro))
                {
                    hijos.push_back({Operador::GD, Posicion_2d({x, y, Direccion::NE})});
                    hijos.push_back({Operador::GI, Posicion_2d({x, y, Direccion::NO})});
                    hijos.push_back({Operador::A, Posicion_2d({x, y, Direccion::N})});
                }
            }
            break;
            case Direccion::OS:
            case Direccion::ES:
            case Direccion::S:
            {

                auto x = posicion.punto.x + 1;
                auto y = posicion.punto.y;
                auto clave_muro = x*columnas + y;
                if(!cuadricula.get_muros().count(clave_muro))
                {
                    hijos.push_back({Operador::GI, Posicion_2d({x, y, Direccion::SE})});
                    hijos.push_back({Operador::GD, Posicion_2d({x, y, Direccion::SO})});
                    hijos.push_back({Operador::A, Posicion_2d({x, y, Direccion::S})});
                }
            }
            break;
            case Direccion::NE:
            case Direccion::SE:
            case Direccion::E:
            {
                auto x = posicion.punto.x;
                auto y = posicion.punto.y + 1;
                auto clave_muro = x*columnas + y;
                if(!cuadricula.get_muros().count(clave_muro))
                {
                    hijos.push_back({Operador::GI, Posicion_2d({x, y, Direccion::EN})});
                    hijos.push_back({Operador::GD, Posicion_2d({x, y, Direccion::ES})});
                    hijos.push_back({Operador::A, Posicion_2d({x, y, Direccion::E})});
                }
            }
            break;
            case Direccion::NO:
            case Direccion::SO:
            case Direccion::O:
            {
                auto x = posicion.punto.x;
                auto y = posicion.punto.y - 1;
                auto clave_muro = x*columnas + y;
                if(!cuadricula.get_muros().count(clave_muro))
                {
                    hijos.push_back({Operador::GD, Posicion_2d({x, y, Direccion::ON})});
                    hijos.push_back({Operador::GI, Posicion_2d({x, y, Direccion::OS})});
                    hijos.push_back({Operador::A, Posicion_2d({x, y, Direccion::O})});
                }
            }
            break;
        }
        return hijos;
    }

    Nodo_cuadricula Nodo_cuadricula::sucesor(const Nodo_cuadricula::tipo_operador& op) const
    {
        Nodo_cuadricula nuevo_estado;
        switch(posicion.direccion)
        {
            case Direccion::ON:
            case Direccion::EN:
            case Direccion::N:
            {
                auto x = posicion.punto.x - 1;
                auto y = posicion.punto.y;
                if (op == Operador::A)
                    nuevo_estado = Posicion_2d{x, y, Direccion::N};
                else if (op == Operador::GD)
                    nuevo_estado = Posicion_2d{x, y, Direccion::NE};
                else
                    nuevo_estado = Posicion_2d{x, y, Direccion::NO};
            }
            break;
            case Direccion::OS:
            case Direccion::ES:
            case Direccion::S:
            {

                auto x = posicion.punto.x + 1;
                auto y = posicion.punto.y;
                if (op == Operador::A)
                    nuevo_estado = Posicion_2d{x, y, Direccion::S};
                else if (op == Operador::GD)
                    nuevo_estado = Posicion_2d{x, y, Direccion::SO};
                else
                    nuevo_estado = Posicion_2d{x, y, Direccion::SE};
            }
            break;
            case Direccion::NE:
            case Direccion::SE:
            case Direccion::E:
            {
                auto x = posicion.punto.x;
                auto y = posicion.punto.y + 1;
                if (op == Operador::A)
                    nuevo_estado = Posicion_2d{x, y, Direccion::E};
                else if (op == Operador::GD)
                    nuevo_estado = Posicion_2d{x, y, Direccion::ES};
                else
                    nuevo_estado = Posicion_2d{x, y, Direccion::EN};
            }
            break;
            case Direccion::NO:
            case Direccion::SO:
            case Direccion::O:
            {
                auto x = posicion.punto.x;
                auto y = posicion.punto.y - 1;
                if (op == Operador::A)
                    nuevo_estado = Posicion_2d{x, y, Direccion::O};
                else if (op == Operador::GD)
                    nuevo_estado = Posicion_2d{x, y, Direccion::ON};
                else
                    nuevo_estado = Posicion_2d{x, y, Direccion::OS};
            }
            break;
        }
        return nuevo_estado;
    }
    Nodo_cuadricula::tipo_clave Nodo_cuadricula::clave() const
    {
        return columnas*(filas*static_cast<tipo_clave>(posicion.direccion) + posicion.punto.x)
               + posicion.punto.y;
    }

    Nodo_cuadricula::tipo_coste Nodo_cuadricula::coste_operador(const tipo_operador& op) const
    {
        tipo_coste coste;
        if (op == Operador::A)
            coste = coste_avanzar;
        else
            coste = coste_girar;

        return coste;
    }

    // Heur�stica v�lida siempre que coste_avanzar < = coste_girar
    Nodo_cuadricula::tipo_coste Nodo_cuadricula::heuristica(const Nodo_cuadricula& nodo) const
    {
        tipo_coste coste;


        //Calculo la distancia Manhanttan
        //fabs
        coste=std::fabs(nodo.get_x()-posicion.punto.x)+std::fabs(nodo.get_y()-(posicion.punto.y));

        //coste = 1; // BORRAR ESTA L�NEA
        // QUILOMBO que no programaremos pero sirve para intuir la dificultad que puede tener calcular una heur�stica
        // o el coste computacional que haga que el ahorro en nodos expandidos no compense

        /*
        if (dist1 == 0 && dist2 > 0)  // Nodos en la misma vertical
        {
            if (nodo.posicion.direccion == posicion.Direccion)
            {

            }
            else
            {

            }
        }
        else if (dist1 > 0 && dist2 == 0) // Nodos en la misma horizontal
        {
            if (nodo.posicion.direccion == posicion.Direccion)
            {

            }
            else
            {

            }
        }
        else if (dist1 > 0 && dist2 > 0) // Nodos en posicion "diagonal"
        {
            if (nodo.posicion.direccion == posicion.Direccion)
            {

            }
            else
            {

            }
        }
        */

        return coste;
    }
}
