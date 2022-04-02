#ifndef CASILLA_H_INCLUDED
#define CASILLA_H_INCLUDED

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>


namespace rejilla
{
    enum class Tipo_casilla{inicio_N=0, inicio_S, inicio_E, inicio_O, fin_N, fin_S, fin_E, fin_O,
                  trayectoria_N, trayectoria_S, trayectoria_E, trayectoria_O,
                  trayectoria_NE, trayectoria_EN, trayectoria_NO, trayectoria_ON,
                  trayectoria_SE, trayectoria_ES,  trayectoria_SO,trayectoria_OS, vacia, muro, periferia};

    class Casilla:public sf::Drawable,public sf::Transformable
    {
        public:
            explicit Casilla(sf::Rect<unsigned> rect, unsigned fil, unsigned col, Tipo_casilla tipo_casilla=Tipo_casilla::vacia); //Por defecto, vacía
            void set_tipo(Tipo_casilla);
            void set_texto(const std::string&); // Dibuja letras y números de salida y llegada en la periferia de la cuadricula
            Tipo_casilla get_tipo() const;
            virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;
         private:
            sf::RectangleShape rect;
            sf::Text texto;
            Tipo_casilla tipo_casilla;
    };
}
#endif // CASILLA_H_INCLUDED
