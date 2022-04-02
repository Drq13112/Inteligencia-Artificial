#ifndef PANEL_H_INCLUDED
#define PANEL_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

namespace vista
{
    class Panel:public sf::Drawable
    {
        public:
            Panel(unsigned ancho, unsigned alto, unsigned pos_x, unsigned pos_y):
                ancho{ancho}, alto{alto}, pos_x{pos_x}, pos_y{pos_y}
            {
                inicializa();
            }

            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
            tgui::Button::Ptr boton_cargar;
            tgui::Button::Ptr boton_ejecutar;
            tgui::Button::Ptr boton_detener;
            tgui::Label::Ptr distancia_optima;
            tgui::Label::Ptr mejor_distancia;
            tgui::Label::Ptr iteracion;
        private:
            unsigned ancho;
            unsigned alto;
            unsigned pos_x;
            unsigned pos_y;
            sf::RectangleShape marco;

            void inicializa();
    };

}
#endif // PANEL_H_INCLUDED
