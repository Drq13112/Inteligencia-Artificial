#include "vista.h"

namespace vista
{
    void Vista::inicializar()
    {
        render_window.create(sf::VideoMode(ancho, alto), "TSP Recocido Simulado");
        gui.setTarget(render_window);

        gui.add(panel.boton_cargar);
        gui.add(panel.boton_ejecutar);
        gui.add(panel.boton_detener);
        gui.add(panel.distancia_optima);
        gui.add(panel.mejor_distancia);
        gui.add(panel.iteracion);

        panel.boton_cargar->connect("pressed",[&]()
        {
            notifica(Evento_vista::cargar);
        });
        panel.boton_ejecutar->connect("pressed",[&]()
        {
            notifica(Evento_vista::ejecutar);
        });
        panel.boton_detener->connect("pressed",[&]()
        {
            notifica(Evento_vista::detener);
        });

        oculta_boton_detener();
        oculta_boton_ejecutar();
        muestra_boton_cargar();
    }

    void Vista::ejecutar()
    {
        while(render_window.isOpen())
        {
            procesa_eventos();
            render();
        }
    }

    void Vista::procesa_eventos()
    {
        sf::Event event;
        while(render_window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    notifica(Evento_vista::finalizar_programa);
                    render_window.close();
                    break;
                default:
                    break;
            }
            gui.handleEvent(event);
        }
    }

    void Vista::render()
    {
        render_window.clear(sf::Color::White);
        render_window.draw(panel);
        std::lock_guard<std::mutex> lock(barrera_render);    //Bloqueamos actualizacion ruta y texto
        gui.draw();                 //Dibuja botones y texto
        render_window.draw(canvas); //Dibuja recorrido
        render_window.display();
    }
}

