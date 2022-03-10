#include "rejilla.h"
#include <stdexcept>
#include <iostream>
#include <string>
namespace rejilla
{
    Rejilla::Rejilla(unsigned filas, unsigned columnas, unsigned tam_casilla):
        filas(filas), columnas(columnas), tam_casilla(tam_casilla)
    {
        casillas.reserve(filas*columnas);
        for (auto i=0u; i < filas; ++i)
            for (auto j=0u; j < columnas; ++j)
                casillas.push_back(Casilla{sf::Rect<unsigned>(j*tam_casilla, i*tam_casilla, tam_casilla, tam_casilla), i, j});

        inicializa_rejilla();
    }

    unsigned Rejilla::indice_casilla(const sf::Vector2u& posicion) const
    {
        auto col = (posicion.x)/tam_casilla;
        auto fil = (posicion.y)/tam_casilla;
        return (fil*columnas + col);
    }

    void Rejilla::inicializa_rejilla()
    {
        for (auto& casilla : casillas)
        {
            casilla.set_tipo(Tipo_casilla::vacia);
        }
        for (auto i=0u; i != filas; ++i)
        {
            casillas[i].set_tipo(Tipo_casilla::periferia);
            casillas[i + filas*(columnas-1)].set_tipo(Tipo_casilla::periferia);
        }
        for (auto i=1u; i != columnas-1; ++i)
        {
            casillas[i*columnas].set_tipo(Tipo_casilla::periferia);
            casillas[columnas*(i+1) - 1].set_tipo(Tipo_casilla::periferia);
        }

        // DIBUJA LOS NÚMEROS
        unsigned contador = 1;
        for (auto i=1u; i != filas-1; ++i)
        {
            auto cadena = std::to_string(contador);
            casillas[i*columnas].set_texto(cadena);
            ++contador;
        }
        for (auto i=1u; i != columnas-1; ++i)
        {
            auto cadena = std::to_string(contador);
            casillas[i + (filas-1)*columnas].set_texto(cadena);
            ++contador;
        }

        // DIBUJA LAS LETRAS
        // Si sobrepasa la 'z' daría fallo, pero no se contempla
        std::string cadena;
        cadena.resize(1);
        char letra = 'A';
        bool primera_vez = true;
        for (auto i=1u; i != columnas - 1; ++i)
        {
            cadena[0] = letra;
            casillas[i].set_texto(cadena);
            ++letra;
            if(primera_vez && letra > 'Z')
            {
                letra = 'a';
                primera_vez = false;
            }
        }
        for (auto i=1u; i != filas - 1; ++i)
        {
            cadena[0] = letra;
            casillas[(i+1)*columnas - 1].set_texto(cadena);
            ++letra;

            if(primera_vez && letra > 'Z')
            {
                letra = 'a';
                primera_vez  = false;
            }
        }
        casillas[columnas].set_tipo(Tipo_casilla::inicio_E);
        casillas[filas*(columnas-1)-1].set_tipo(Tipo_casilla::fin_E);
    }


    void Rejilla::set_tipo_casilla(const sf::Vector2u& posicion, Tipo_casilla tipo_casilla)
    {
        casillas[indice_casilla(posicion)].set_tipo(tipo_casilla);
    }
    Tipo_casilla Rejilla::get_tipo_casilla(const sf::Vector2u& posicion) const
    {
        return(casillas[indice_casilla(posicion)].get_tipo());
    }

    void Rejilla::dibuja_trayectoria(const std::vector<posicion_y_tipo_casilla>& solucion)
    {
        for(size_t i=0; i != solucion.size(); ++i)
        {
            auto pos = solucion[i].first;
            if(casillas[pos.first*columnas+pos.second].get_tipo() == Tipo_casilla::vacia)
                casillas[pos.first*columnas+pos.second].set_tipo(solucion[i].second);
        }
    }
    void Rejilla::borra_trayectoria()
    {
        for (auto& casilla:casillas)
        {
            if(casilla.get_tipo()>=Tipo_casilla::trayectoria_N &&
                    casilla.get_tipo() <= Tipo_casilla::trayectoria_OS)
                casilla.set_tipo(Tipo_casilla::vacia);
        }
    }

    Rejilla::posicion_y_tipo_casilla Rejilla::get_casilla_inicial() const
    {
        unsigned indice = 0;
        posicion_y_tipo_casilla salida;
        for(const auto& casilla : casillas)
        {
            if(casilla.get_tipo() >= Tipo_casilla::inicio_N && casilla.get_tipo() <= Tipo_casilla::inicio_O)
            {
                unsigned fil = indice/columnas;
                unsigned col = indice%columnas;
                salida = {{fil, col}, casilla.get_tipo()};
                break;
            }
            ++indice;
        }
        return salida;
    }
    Rejilla::posicion_y_tipo_casilla Rejilla::get_casilla_final() const
    {
        unsigned indice = 0;
        posicion_y_tipo_casilla salida;
        for(const auto& casilla : casillas)
        {
            if(casilla.get_tipo() >= Tipo_casilla::fin_N && casilla.get_tipo() <= Tipo_casilla::fin_O)
            {
                unsigned fil = indice/columnas;
                unsigned col = indice%columnas;
                salida = {{fil, col}, casilla.get_tipo()};
                break;
            }
            ++indice;
        }
        return salida;
    }

    std::vector<Rejilla::posicion_casilla> Rejilla::muros() const
    {
        std::vector<Rejilla::posicion_casilla> muros;

        unsigned indice=0;
        for(const auto& casilla : casillas)
        {
            if (casilla.get_tipo() == Tipo_casilla::muro || casilla.get_tipo() == Tipo_casilla::periferia)
            {
                unsigned fil = indice/columnas;
                unsigned col = indice%columnas;
                muros.push_back({fil, col});
            }
            else if (casilla.get_tipo() == Tipo_casilla::inicio_E)
            {
                unsigned fil = indice/columnas;
                unsigned col = indice%columnas;
                if(col == 0)
                    muros.push_back({fil, col});
            }
            else if (casilla.get_tipo() == Tipo_casilla::inicio_N)
            {
                unsigned fil = indice/columnas;
                unsigned col = indice%columnas;
                if(fil == filas-1)
                    muros.push_back({fil, col});
            }
            else if (casilla.get_tipo() == Tipo_casilla::inicio_O)
            {
                unsigned fil = indice/columnas;
                unsigned col = indice%columnas;
                if(col == columnas-1)
                    muros.push_back({fil, col});
            }
            else if (casilla.get_tipo() == Tipo_casilla::inicio_S)
            {
                unsigned fil = indice/columnas;
                unsigned col = indice%columnas;
                if(fil==0)
                    muros.push_back({fil,col});
            }
            ++indice;
        }
        return muros;
    }


    void Rejilla::draw(sf::RenderTarget& target, sf::RenderStates) const
    {
        for (const auto& casilla : casillas)
            target.draw(casilla);
    }


    void Rejilla::crea_rejilla_aleatorio()
    {
        static std::mt19937 engine(std::random_device{}());
        std::uniform_int_distribution<> distr(0, (casillas.size() / 2));
        std::uniform_int_distribution<> distr_fil(0,filas-1);
        std::uniform_int_distribution<> distr_col(0,columnas-1);

        inicializa_rejilla();

        auto num_casillas_muro = distr(engine);
        for (auto i=0; i<num_casillas_muro; ++i)
        {
            auto indice=distr_col(engine)+distr_fil(engine)*columnas;
            if (casillas[indice].get_tipo()==Tipo_casilla::vacia)
            {
                casillas[indice].set_tipo(Tipo_casilla::muro);
            }
        }
    }

    void Rejilla::set_casilla_inicial(const sf::Vector2u& posicion,std::pair<bool,bool>& inicial_final)
    {
        Tipo_casilla tipo_casilla=get_tipo_casilla(posicion);
        if(tipo_casilla>=Tipo_casilla::fin_N && tipo_casilla<=Tipo_casilla::fin_O)
            inicial_final= {true,false};
        else
            inicial_final= {true,true};
        auto col=(posicion.x)/tam_casilla;
        auto fil=(posicion.y)/tam_casilla;
        if(fil==0)
            set_tipo_casilla(posicion,Tipo_casilla::inicio_S);
        else if(fil==filas-1)
            set_tipo_casilla(posicion,Tipo_casilla::inicio_N);
        else if(col==columnas-1)
            set_tipo_casilla(posicion,Tipo_casilla::inicio_O);
        else
            set_tipo_casilla(posicion,Tipo_casilla::inicio_E);
    }
    void Rejilla::set_casilla_final(const sf::Vector2u& posicion,std::pair<bool,bool>& inicial_final)
    {
        Tipo_casilla tipo_casilla=get_tipo_casilla(posicion);
        if(tipo_casilla>=Tipo_casilla::inicio_N && tipo_casilla<=Tipo_casilla::inicio_O)
            inicial_final= {false,true};
        else
            inicial_final= {true,true};
        auto col=(posicion.x)/tam_casilla;
        auto fil=(posicion.y)/tam_casilla;
        if(fil==0)
            set_tipo_casilla(posicion,Tipo_casilla::fin_N);
        else if(fil==filas-1)
            set_tipo_casilla(posicion,Tipo_casilla::fin_S);
        else if(col==columnas-1)
            set_tipo_casilla(posicion,Tipo_casilla::fin_E);
        else
            set_tipo_casilla(posicion,Tipo_casilla::fin_O);
    }
    void Rejilla::cambia_casilla(const sf::Vector2u& posicion,std::pair<bool,bool>& inicial_final)
    {
        Tipo_casilla tipo_casilla=get_tipo_casilla(posicion);
        switch(tipo_casilla)
        {
            case Tipo_casilla::muro:
                set_tipo_casilla(posicion,Tipo_casilla::vacia);
                break;
            case Tipo_casilla::vacia:
                set_tipo_casilla(posicion,Tipo_casilla::muro);
                break;
            case Tipo_casilla::trayectoria_N:
            case Tipo_casilla::trayectoria_S:
            case Tipo_casilla::trayectoria_E:
            case Tipo_casilla::trayectoria_O:
            case Tipo_casilla::trayectoria_NE:
            case Tipo_casilla::trayectoria_SE:
            case Tipo_casilla::trayectoria_NO:
            case Tipo_casilla::trayectoria_SO:
            case Tipo_casilla::trayectoria_EN:
            case Tipo_casilla::trayectoria_ES:
            case Tipo_casilla::trayectoria_ON:
            case Tipo_casilla::trayectoria_OS:
                set_tipo_casilla(posicion,Tipo_casilla::muro);
                break;
            case Tipo_casilla::inicio_N:
            case Tipo_casilla::inicio_S:
            case Tipo_casilla::inicio_E:
            case Tipo_casilla::inicio_O:
                borra_casilla_inicial_final(posicion);
                inicial_final= {false,true};
                break;
            case Tipo_casilla::fin_N:
            case Tipo_casilla::fin_S:
            case Tipo_casilla::fin_E:
            case Tipo_casilla::fin_O:
                borra_casilla_inicial_final(posicion);
                inicial_final= {true,false};
            default:
                break;
        }
    }
    void Rejilla::gira_casilla(const sf::Vector2u& posicion)
    {
        auto col=(posicion.x)/tam_casilla;
        auto fil=(posicion.y)/tam_casilla;
        if(fil!=0 && fil!=filas-1 && col!=0 && col!=columnas-1)
        {
            if(get_tipo_casilla(posicion)==Tipo_casilla::inicio_E)
                set_tipo_casilla(posicion,Tipo_casilla::inicio_S);
            else if(get_tipo_casilla(posicion)==Tipo_casilla::inicio_S)
                set_tipo_casilla(posicion,Tipo_casilla::inicio_O);
            else if(get_tipo_casilla(posicion)==Tipo_casilla::inicio_O)
                set_tipo_casilla(posicion,Tipo_casilla::inicio_N);
            else if(get_tipo_casilla(posicion)==Tipo_casilla::inicio_N)
                set_tipo_casilla(posicion,Tipo_casilla::inicio_E);
            else if(get_tipo_casilla(posicion)==Tipo_casilla::fin_E)
                set_tipo_casilla(posicion,Tipo_casilla::fin_S);
            else if(get_tipo_casilla(posicion)==Tipo_casilla::fin_S)
                set_tipo_casilla(posicion,Tipo_casilla::fin_O);
            else if(get_tipo_casilla(posicion)==Tipo_casilla::fin_O)
                set_tipo_casilla(posicion,Tipo_casilla::fin_N);
            else if(get_tipo_casilla(posicion)==Tipo_casilla::fin_N)
                set_tipo_casilla(posicion,Tipo_casilla::fin_E);
        }
    }
    void Rejilla::borra_casilla_inicial_final(const sf::Vector2u& posicion)
    {
        auto col=(posicion.x)/tam_casilla;
        auto fil=(posicion.y)/tam_casilla;

        if(fil==0||fil==filas-1||col==0||col==columnas-1)
            set_tipo_casilla(posicion,Tipo_casilla::periferia);
        else
            set_tipo_casilla(posicion,Tipo_casilla::vacia);
    }
}
