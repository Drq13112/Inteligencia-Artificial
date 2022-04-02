#ifndef VISUALIZACION_H
#define VISUALIZACION_H
#include <SFML/Graphics.hpp>

#include "permutaciones.h"

namespace vista
{
    class Canvas:public sf::Drawable
    {
        public:
            Canvas(unsigned offset_x, unsigned offset_y, unsigned ancho, unsigned alto):
                offset_x{offset_x}, offset_y{offset_y}, ancho{ancho}, alto{alto}
            {
                marco = sf::RectangleShape(sf::Vector2f(ancho - 4, alto - 4));
                marco.setPosition(sf::Vector2f(2, 2));
                marco.setOutlineThickness(2);
                marco.setOutlineColor(sf::Color(0, 0, 255));
            }

            void set_coordenadas(std::vector<std::pair<unsigned,unsigned>> const & coor)
            {
                coordenadas = coor;
                set_puntos();
            }
            void set_recorrido(const permutacion::Permutacion<unsigned>& ind);

            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        private:
            unsigned offset_x, offset_y;
            unsigned ancho, alto;
            sf::RectangleShape marco;

            std::vector<std::pair<unsigned, unsigned>> coordenadas; //Coordenadas de las ciudades normalizadas a las dimensiones del CANVAS

            std::vector<sf::CircleShape> puntos;
            sf::VertexArray recorrido;

            void set_puntos();
    };
}
#endif

