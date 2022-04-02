#include "vista.h"
#include <iostream>
#include <string>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Event.hpp>

namespace vista
{
    Vista::Vista(unsigned filas, unsigned columnas, unsigned tam_casilla, unsigned alto_panel):
        rejilla(rejilla::Rejilla(filas, columnas, tam_casilla)),
        panel(sf::RectangleShape(sf::Vector2f(columnas*tam_casilla, alto_panel))),
        render_window(sf::VideoMode(columnas*tam_casilla,
                                    filas*tam_casilla + alto_panel), "Planificacion Trayectoria")
    {
        panel.setPosition(sf::Vector2f(0, columnas*tam_casilla));
        panel.setFillColor(sf::Color::White);
    }

    void Vista::ejecutar()
    {
        configura_mensajes_texto();
        while(render_window.isOpen())
        {
            procesa_eventos();
            render();
        }
    }

    void Vista::configura_mensajes_texto()
    {
        font.loadFromFile("vista/resources/sansation.ttf");
        auto alto = render_window.getSize().y;
        const auto black = sf::Color::Black;

        //set up texts
        texto_num_movimientos.setPosition(20.f, alto - 80.f);// - 110.f);
        texto_num_movimientos.setScale(0.7f, 0.7f);
        texto_num_movimientos.setFont(font);
        texto_num_movimientos.setFillColor(black);

        texto_coste.setPosition(20.f, alto - 55.f);// - 110.f);
        texto_coste.setScale(0.7f, 0.7f);
        texto_coste.setFont(font);
        texto_coste.setFillColor(black);

        texto_tiempo.setPosition(20.f, alto - 30.f);
        texto_tiempo.setScale(0.7f, 0.7f);
        texto_tiempo.setFont(font);
        texto_tiempo.setFillColor(black);

        texto_trayectoria_encontrada.setPosition(20.f, alto - 30.f);
        texto_trayectoria_encontrada.setScale(0.7f, 0.7f);
        texto_trayectoria_encontrada.setFont(font);
        texto_trayectoria_encontrada.setFillColor(black);

        texto_falta_casilla.setPosition(20.f, alto - 30.f);
        texto_falta_casilla.setScale(0.7f, 0.7f);
        texto_falta_casilla.setFont(font);
        texto_falta_casilla.setFillColor(sf::Color::Red);
    }

    rejilla::Rejilla::posicion_y_tipo_casilla Vista::casilla_inicial()
    {
        return(rejilla.get_casilla_inicial());
    }
    rejilla::Rejilla::posicion_y_tipo_casilla Vista::casilla_final()
    {
        return(rejilla.get_casilla_final());
    }
    std::vector<rejilla::Rejilla::posicion_casilla> Vista::muros()
    {
        return(rejilla.muros());
    }


    void Vista::procesa_eventos()
    {
        sf::Event event;

        while (render_window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    render_window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                {
                    borra_texto();
                    if(event.mouseButton.button == sf::Mouse::Left)
                    {
                        procesa_eventos_raton_izq();
                    }
                    else if(event.mouseButton.button == sf::Mouse::Right)
                    {
                        procesa_eventos_raton_der();
                    }
                    break;
                }
                case sf::Event::KeyPressed:
                {
                    procesa_eventos_teclado(event.key.code);
                    break;
                }
                default:
                    break;
            }
        }
    }

    void Vista::procesa_eventos_teclado(sf::Keyboard::Key& key)
    {
        static int estado_borrado = 0;
        switch(key)
        {
            case sf::Keyboard::S: //Busca solucion
            {
                estado_borrado=0;
                if(existe_inicial_final == std::pair<bool, bool> {true, true})
                {
                    rejilla.borra_trayectoria();
                    tiempo_resolucion.restart();
                    notifica(Evento_Vista::EJECUTAR);
                }
                else
                {
                    texto_falta_casilla.setString("Falta casilla inicial y/o final");
                }
                break;
            }
            case sf::Keyboard::C: //Borra trayectaria: 1 vez, rejilla: 2 veces
            {
                borra_texto();
                if(estado_borrado == 0)
                {
                    rejilla.borra_trayectoria();
                    estado_borrado = 1;
                }
                else if(estado_borrado == 1)
                {
                    rejilla.inicializa_rejilla();
                    estado_borrado = 0;
                    existe_inicial_final = std::pair<bool, bool> {true, true};
                }
                break;
            }
            case sf::Keyboard::R: //Aleatoria
            {
                borra_texto();
                estado_borrado = 0;
                rejilla.crea_rejilla_aleatorio();
                existe_inicial_final = std::pair<bool, bool> {true, true};
                break;
            }
            default:
                break;
        }
    }

    //Cambia el tipo de casilla
    void Vista::procesa_eventos_raton_izq()
    {
        auto posicion_raton = static_cast<sf::Vector2u>(sf::Mouse::getPosition(render_window));

        if(existe_inicial_final == std::pair<bool, bool> {false, true})
        {
            rejilla.set_casilla_inicial(posicion_raton, existe_inicial_final);
            if(existe_inicial_final == std::pair<bool, bool> {true, false})
                texto_falta_casilla.setString("Falta casilla final");
            else
                texto_falta_casilla.setString("");
        }
        else if(existe_inicial_final == std::pair<bool, bool> {true, false})
        {
            rejilla.set_casilla_final(posicion_raton, existe_inicial_final);
            if(existe_inicial_final == std::pair<bool,bool> {false, true})
                texto_falta_casilla.setString("Falta casilla inicial");
            else
                texto_falta_casilla.setString("");
        }
        else
        {
            rejilla.cambia_casilla(posicion_raton, existe_inicial_final);
            if(existe_inicial_final==std::pair<bool, bool> {false, true})
                texto_falta_casilla.setString("Falta casilla inicial");
            else if(existe_inicial_final==std::pair<bool, bool> {true, false})
                texto_falta_casilla.setString("Falta casilla final");
        }
    }

    //Permite girar la casilla inicial y final cuando estas no estan en la periferia
    void Vista::procesa_eventos_raton_der()
    {
        auto posicion_raton=static_cast<sf::Vector2u>(sf::Mouse::getPosition(render_window));
        rejilla.gira_casilla(posicion_raton);
    }

    void Vista::render()
    {
        render_window.clear();
        render_window.draw(rejilla);
        render_window.draw(panel);
        render_window.draw(texto_num_movimientos);
        render_window.draw(texto_coste);
        render_window.draw(texto_tiempo);
        render_window.draw(texto_trayectoria_encontrada);
        render_window.draw(texto_falta_casilla);

        render_window.display();
    }



    void Vista::trayectoria_encontrada(const std::vector<rejilla::Rejilla::posicion_y_tipo_casilla>& solucion,
                                       unsigned num_nodos_expandidos, double coste)
    {
        texto_tiempo.setString("Tiempo de resolucion: " +
                               std::to_string(tiempo_resolucion.getElapsedTime().asMilliseconds()) +
                               " milisegundos");
        texto_num_movimientos.setString("Se expandieron " +
                                        std::to_string(num_nodos_expandidos)+" nodos");
        if (!solucion.empty())
        {
            texto_trayectoria_encontrada.setString("");
            texto_coste.setString("El coste de la solución es " +
                                  std::to_string(coste));
            rejilla.dibuja_trayectoria(solucion);
        }
        else
        {
            texto_trayectoria_encontrada.setString("No se ha encontrado trayectoria");
        }
    }
    void Vista::borra_texto()
    {
        texto_tiempo.setString("");
        texto_num_movimientos.setString("");
        texto_coste.setString("");
        texto_trayectoria_encontrada.setString("");
    }
}
