#include "panel.h"

namespace vista
{
    void Panel::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(marco);
    }

    void Panel::inicializa()
    {
        tgui::Theme theme{"vista/resources/Black.txt"};

        boton_cargar = tgui::Button::create();
        boton_cargar->setRenderer(theme.getRenderer("Button"));
        boton_cargar->setText("CARGAR TSP");
        boton_cargar->setSize(ancho-20, 40);
        boton_cargar->setPosition(pos_x + 10, 15);
        boton_cargar->setTextSize(25);
        boton_cargar->setVisible(false);

        boton_ejecutar=tgui::Button::create();
        boton_ejecutar->setRenderer(theme.getRenderer("Button"));
        boton_ejecutar->setText("CALCULAR");
        boton_ejecutar->setSize(ancho - 20, 40);
        boton_ejecutar->setPosition(pos_x + 10, 60);
        boton_ejecutar->setTextSize(25);
        boton_ejecutar->setVisible(false);

        boton_detener=tgui::Button::create();
        boton_detener->setRenderer(theme.getRenderer("Button"));
        boton_detener->setText("DETENER");
        boton_detener->setSize(ancho - 20, 40);
        boton_detener->setPosition(pos_x + 10, 105);
        boton_detener->setTextSize(25);
        boton_detener->setVisible(false);

        distancia_optima=tgui::Label::create();
        distancia_optima->setRenderer(theme.getRenderer("Label"));
        distancia_optima->setPosition(pos_x + 10, 150);
        distancia_optima->setTextSize(18);

        iteracion=tgui::Label::create();
        iteracion->setRenderer(theme.getRenderer("Label"));
        iteracion->setPosition(pos_x + 10, 170);
        iteracion->setTextSize(18);

        mejor_distancia=tgui::Label::create();
        mejor_distancia->setRenderer(theme.getRenderer("Label"));
        mejor_distancia->setPosition(pos_x + 10, 190);
        mejor_distancia->setTextSize(18);

        marco = sf::RectangleShape(sf::Vector2f(ancho, alto));
        marco.setPosition(sf::Vector2f(pos_x, pos_y));
        marco.setFillColor(sf::Color(128, 128, 128));
    }
}
