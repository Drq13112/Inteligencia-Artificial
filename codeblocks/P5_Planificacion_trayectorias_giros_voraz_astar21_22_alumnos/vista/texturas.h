#ifndef TEXTURAS_H_INCLUDED
#define TEXTURAS_H_INCLUDED

#include <SFML/Graphics.hpp>
namespace rejilla
{
    class Textura
    {
        public:
            Textura()
            {
                if (!flecha_N.loadFromFile("vista/imgs/flecha_N.png")
                        || !flecha_S.loadFromFile("vista/imgs/flecha_S.png")
                        || !flecha_E.loadFromFile("vista/imgs/flecha_E.png")
                        || !flecha_O.loadFromFile("vista/imgs/flecha_O.png")
                        || !flecha_NE.loadFromFile("vista/imgs/flecha_NE.png")
                        || !flecha_EN.loadFromFile("vista/imgs/flecha_EN.png")
                        || !flecha_NO.loadFromFile("vista/imgs/flecha_NO.png")
                        || !flecha_ON.loadFromFile("vista/imgs/flecha_ON.png")
                        || !flecha_SE.loadFromFile("vista/imgs/flecha_SE.png")
                        || !flecha_ES.loadFromFile("vista/imgs/flecha_ES.png")
                        || !flecha_SO.loadFromFile("vista/imgs/flecha_SO.png")
                        || !flecha_OS.loadFromFile("vista/imgs/flecha_OS.png")
                        || !cruz.loadFromFile("vista/imgs/cruz.png")
                        || !vacia.loadFromFile("vista/imgs/vacia.png"))
                {
                    exit(1);
                }
            }
            sf::Texture flecha_N;
            sf::Texture flecha_S;
            sf::Texture flecha_E;
            sf::Texture flecha_O;
            sf::Texture flecha_NE;
            sf::Texture flecha_EN;
            sf::Texture flecha_NO;
            sf::Texture flecha_ON;
            sf::Texture flecha_SE;
            sf::Texture flecha_ES;
            sf::Texture flecha_SO;
            sf::Texture flecha_OS;
            sf::Texture cruz;
            sf::Texture vacia;
    };
}
#endif // TEXTURAS_H_INCLUDED
