#include "controlador.h"
#include "problema_busqueda.h"
#include "nodo_cuadricula.h"

namespace controlador
{
    void Controlador::registra_observadores()
    {
        vista->registra_observador(vista::Evento_Vista::EJECUTAR,[this]()
        {
            ejecuta_modelo();
        });
    }
    void Controlador::ejecutar()
    {
        vista->ejecutar();
    }

//  FUNCIONES DEL CONTROLADOR RELATIVAS AL MODELO
    // Deduce de la vista la posicion inicial en la cuadr�cula del modelo
    cuadricula::Posicion_2d Controlador::posicion_inicial()
    {
        posicion_y_tipo_casilla p_e = vista->casilla_inicial();
        cuadricula::Posicion_2d p_s;
        p_s.punto.x = p_e.first.first;
        p_s.punto.y = p_e.first.second;

        switch(p_e.second)
        {
            case rejilla::Tipo_casilla::inicio_N:
                p_s.direccion = cuadricula::Direccion::N;
                break;
            case rejilla::Tipo_casilla::inicio_S:
                p_s.direccion = cuadricula::Direccion::S;
                break;
            case rejilla::Tipo_casilla::inicio_O:
                p_s.direccion = cuadricula::Direccion::O;
                break;
            case rejilla::Tipo_casilla::inicio_E:
                p_s.direccion = cuadricula::Direccion::E;
                break;
            default:
                break;
        }
        return p_s;
    }

    // Deduce de la vista la posicion final en la cuadr�cula del modelo
    cuadricula::Posicion_2d Controlador::posicion_final()
    {
        posicion_y_tipo_casilla p_e=vista->casilla_final();
        cuadricula::Posicion_2d p_s;
        p_s.punto.x=p_e.first.first;
        p_s.punto.y=p_e.first.second;

        switch(p_e.second)
        {
            case rejilla::Tipo_casilla::fin_N:
                p_s.direccion = cuadricula::Direccion::N;
                break;
            case rejilla::Tipo_casilla::fin_S:
                p_s.direccion = cuadricula::Direccion::S;
                break;
            case rejilla::Tipo_casilla::fin_O:
                p_s.direccion = cuadricula::Direccion::O;
                break;
            case rejilla::Tipo_casilla::fin_E:
                p_s.direccion = cuadricula::Direccion::E;
                break;
            default:
                break;
        }
        return p_s;
    }

    // Vector con las posiciones de los obst�culos
    std::vector<cuadricula::Punto_2d> Controlador::muros()
    {
        std::vector<cuadricula::Punto_2d> pos_muros;
        for (auto& pos : vista->muros())
        {
            pos_muros.push_back(cuadricula::Punto_2d{pos.first, pos.second});
        }
        return pos_muros;
    }

    void Controlador::ejecuta_modelo()
    {
        cuadricula::Cuadricula cuadricula;
        auto pos_inicial = posicion_inicial();;
        auto pos_final = posicion_final();
        //Inicializa la cuadricula con los datos recogidos de la Vista
        cuadricula.crea_cuadricula(pos_inicial.punto, pos_final.punto, muros());
        
        //Asocia la cuadricula (static) a los nodos cuadricula
        cuadricula::Nodo_cuadricula::set_cuadricula(cuadricula);
        cuadricula::Nodo_cuadricula nodo_inicial(pos_inicial);
        cuadricula::Nodo_cuadricula nodo_objetivo(pos_final);
        cuadricula::Nodo_cuadricula::set_costes(coste_avanzar, coste_girar);

        std::function<problema_busqueda::Solucion<cuadricula::Nodo_cuadricula> (cuadricula::Nodo_cuadricula& nodo_inicial, cuadricula::Nodo_cuadricula& nodo_objetivo)> metodo_busqueda;

        if (nombre_algoritmo == "coste_uniforme")
            metodo_busqueda = problema_busqueda::coste_uniforme<cuadricula::Nodo_cuadricula>;
        else if (nombre_algoritmo == "voraz")
            metodo_busqueda = problema_busqueda::voraz<cuadricula::Nodo_cuadricula>;
        else if (nombre_algoritmo == "amplitud")
            metodo_busqueda = problema_busqueda::amplitud<cuadricula::Nodo_cuadricula>;
        else if (nombre_algoritmo == "a_estrella")
            metodo_busqueda = problema_busqueda::a_estrella<cuadricula::Nodo_cuadricula>;
        else
            throw std::runtime_error("El nombre del algoritmo, " + nombre_algoritmo + ", no es valido.\n");

        auto solucion = metodo_busqueda(nodo_inicial, nodo_objetivo);


        std::vector<posicion_y_tipo_casilla> solucion_vista;
        std::cout << "\n\n************************************\n";
        std::cout << "SOLUCION\n\n";

        if (!solucion.exito)
            std::cout << "No se encontro solucion\n";
        else
        {
            std::cout << nodo_inicial;
            auto siguiente = nodo_inicial;
            for (auto& op : solucion.secuencia_operadores)
            {
                std::cout << ": Operador " << op << " -->\n";
                siguiente = siguiente.sucesor(op);
                std::cout << siguiente;
                solucion_vista.push_back(transforma(siguiente));
            }
            vista->trayectoria_encontrada(solucion_vista, solucion.nodos_expandidos, solucion.coste);
            std::cout << "\n\nCoste de la solucion: " << solucion.coste << std::endl;
        }
        std::cout << "\n\nNumero de nodos expandidos: " << solucion.nodos_expandidos << std::endl;
        std::cout << "************************************\n";


    }

    Controlador::posicion_y_tipo_casilla Controlador::transforma(const cuadricula::Nodo_cuadricula& nodo)
    {
        rejilla::Tipo_casilla tipo;
        switch (nodo.get_direccion())
        {
            case cuadricula::Direccion::N:
            {
                tipo = rejilla::Tipo_casilla::trayectoria_N;
                break;
            }
            case cuadricula::Direccion::S:
            {
                tipo = rejilla::Tipo_casilla::trayectoria_S;
                break;
            }
            case cuadricula::Direccion::E:
            {
                tipo = rejilla::Tipo_casilla::trayectoria_E;
                break;
            }
            case cuadricula::Direccion::O:
            {
                tipo = rejilla::Tipo_casilla::trayectoria_O;
                break;
            }
            case cuadricula::Direccion::NE:
            {
                tipo = rejilla::Tipo_casilla::trayectoria_NE;
                break;
            }
            case cuadricula::Direccion::EN:
            {
                tipo = rejilla::Tipo_casilla::trayectoria_EN;
                break;
            }
            case cuadricula::Direccion::NO:
            {
                tipo = rejilla::Tipo_casilla::trayectoria_NO;
                break;
            }
            case cuadricula::Direccion::ON:
            {
                tipo = rejilla::Tipo_casilla::trayectoria_ON;
                break;
            }
            case cuadricula::Direccion::SE:
            {
                tipo = rejilla::Tipo_casilla::trayectoria_SE;
                break;
            }
            case cuadricula::Direccion::ES:
            {
                tipo = rejilla::Tipo_casilla::trayectoria_ES;
                break;
            }
            case cuadricula::Direccion::SO:
            {
                tipo = rejilla::Tipo_casilla::trayectoria_SO;
                break;
            }
            case cuadricula::Direccion::OS:
            {
                tipo = rejilla::Tipo_casilla::trayectoria_OS;
                break;
            }
        }
        return {{nodo.get_x(), nodo.get_y()}, tipo};
    }
}
