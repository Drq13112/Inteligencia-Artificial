#ifndef VISTA_H_INCLUDED
#define VISTA_H_INCLUDED

#include "observador.h"
#include "canvas.h"
#include "panel.h"
#include <mutex>

namespace vista
{
    enum class Evento_vista {cargar, ejecutar, detener, finalizar_programa};
    class Vista:public Observable<Evento_vista>
    {
        public:
            Vista():
                canvas{offset_x, offset_y, ancho - ancho_panel, alto},
                panel{ancho_panel, alto, ancho - ancho_panel, 0}
            {
                inicializar();
            }
            void set_coordenadas(const std::vector<std::pair<unsigned, unsigned>>& coor)
            {
                canvas.set_coordenadas(coor);
            }

            void get_rectangulo_canvas(unsigned& x_sup_izq, unsigned& y_sup_izq,
                                       unsigned& x_inf_der, unsigned& y_inf_der) const
            {
                x_sup_izq = offset_x;
                y_sup_izq = offset_y;
                x_inf_der = alto - offset_x;
                y_inf_der = ancho - ancho_panel - offset_y;
            }

            void ejecutar();

            void muestra_boton_cargar()
            {
                panel.boton_cargar->setVisible(true);
            }
            void oculta_boton_cargar()
            {
                panel.boton_cargar->setVisible(false);
            }
            void muestra_boton_detener()
            {
                panel.boton_detener->setVisible(true);
            }
            void oculta_boton_detener()
            {
                panel.boton_detener->setVisible(false);
            }
            void muestra_boton_ejecutar()
            {
                panel.boton_ejecutar->setVisible(true);
            }
            void oculta_boton_ejecutar()
            {
                panel.boton_ejecutar->setVisible(false);
            }
            void set_texto_distancia_optima(const std::string&& texto)
            {
                panel.distancia_optima->setText(texto);
            }
            void set_texto_mejor_distancia(const std::string&& texto)
            {
                panel.mejor_distancia->setText(texto);
            }
            void set_texto_iteracion(const std::string&& texto)
            {
                panel.iteracion->setText(texto);
            }
            void actualiza_recorrido(const permutacion::Permutacion<unsigned>& ind,
                                     const std::string&& texto1,
                                     const std::string&& texto2)
            {
                std::lock_guard<std::mutex> lock(barrera_render);    //Bloqueamos render
                panel.iteracion->setText(texto1);
                panel.mejor_distancia->setText(texto2);
                canvas.set_recorrido(ind);
            }
        private:
            //Estas dimensiones podrían ser leidas desde un fichero de configuracion,
            //elegidas por línea de comandos teniendo Vista otros constructores
            //o programar la vista para autoajustarse
            const unsigned ancho = 960;
            const unsigned alto = 720;
            const unsigned ancho_panel = 250;
            const unsigned offset_x = 5;
            const unsigned offset_y = 5;
            Canvas canvas;
            Panel panel;

            sf::RenderWindow render_window;
            tgui::Gui gui;

            std::mutex barrera_render;
            void procesa_eventos();
            void render();

            void inicializar();
    };
}
#endif // VISTA_H_INCLUDED
