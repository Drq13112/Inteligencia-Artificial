#include "casilla.h"
#include "texturas.h"
namespace rejilla
{
    namespace detail
    {
        Textura textura;
        sf::Font font;
        const sf::Texture& textura_casilla(const Tipo_casilla tipo_casilla)
        {
            switch(tipo_casilla)
            {
                case Tipo_casilla::vacia:
                    return textura.cruz;
                case Tipo_casilla::trayectoria_N:
                    return textura.flecha_N;
                case Tipo_casilla::trayectoria_S:
                    return textura.flecha_S;
                case Tipo_casilla::trayectoria_E:
                    return textura.flecha_E;
                case Tipo_casilla::trayectoria_O:
                    return textura.flecha_O;
                case Tipo_casilla::trayectoria_NE:
                    return textura.flecha_NE;
                case Tipo_casilla::trayectoria_NO:
                    return textura.flecha_NO;
                case Tipo_casilla::trayectoria_SE:
                    return textura.flecha_SE;
                case Tipo_casilla::trayectoria_SO:
                    return textura.flecha_SO;
                case Tipo_casilla::trayectoria_EN:
                    return textura.flecha_EN;
                case Tipo_casilla::trayectoria_ON:
                    return textura.flecha_ON;
                case Tipo_casilla::trayectoria_ES:
                    return textura.flecha_ES;
                case Tipo_casilla::trayectoria_OS:
                    return textura.flecha_OS;
                case Tipo_casilla::inicio_N:
                    return textura.flecha_N;
                case Tipo_casilla::inicio_S:
                    return textura.flecha_S;
                case Tipo_casilla::inicio_E:
                    return textura.flecha_E;
                case Tipo_casilla::inicio_O:
                    return textura.flecha_O;
                case Tipo_casilla::fin_N:
                    return textura.flecha_N;
                case Tipo_casilla::fin_S:
                    return textura.flecha_S;
                case Tipo_casilla::fin_E:
                    return textura.flecha_E;
                case Tipo_casilla::fin_O:
                    return textura.flecha_O;
                default:
                    return textura.vacia;
            }
        }
        sf::Color color_casilla(const Tipo_casilla tipo_casilla)
        {
            switch(tipo_casilla)
            {
                case Tipo_casilla::vacia:
                case Tipo_casilla::periferia:
                    return sf::Color::White;
                case Tipo_casilla::trayectoria_N:
                case Tipo_casilla::trayectoria_S:
                case Tipo_casilla::trayectoria_E:
                case Tipo_casilla::trayectoria_O:
                case Tipo_casilla::trayectoria_NE:
                case Tipo_casilla::trayectoria_NO:
                case Tipo_casilla::trayectoria_SE:
                case Tipo_casilla::trayectoria_SO:
                case Tipo_casilla::trayectoria_EN:
                case Tipo_casilla::trayectoria_ON:
                case Tipo_casilla::trayectoria_ES:
                case Tipo_casilla::trayectoria_OS:
                    return sf::Color(0,76,132); //Azul
                case Tipo_casilla::inicio_N:
                case Tipo_casilla::inicio_S:
                case Tipo_casilla::inicio_E:
                case Tipo_casilla::inicio_O:
                    return sf::Color(200,50,50); //Rojo
                case Tipo_casilla::fin_N:
                case Tipo_casilla::fin_S:
                case Tipo_casilla::fin_E:
                case Tipo_casilla::fin_O:
                    return sf::Color(250,150,100); //Naranja
                default:
                    return sf::Color::Black;
            }
        }
    }


    Casilla::Casilla(sf::Rect<unsigned> r, unsigned fil, unsigned col, Tipo_casilla tipo_casilla):
        rect(sf::Vector2f(r.width, r.height)), tipo_casilla(tipo_casilla)
    {
        setPosition(r.left,r.top);
        set_tipo(tipo_casilla);

        if(!detail::font.loadFromFile("vista/resources/sansation.ttf"))
        {
            exit(1);
        }
        texto.setFont(detail::font); // font is a sf::Font
        auto tam = rect.getSize();
        texto.setCharacterSize(0.7*tam.x);
        texto.setFillColor(sf::Color::Red);
        texto.setStyle(sf::Text::Bold);
    }

    //Funcion virtual heredada
    void Casilla::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(rect,states);
        target.draw(texto);
    }
    void Casilla::set_tipo(Tipo_casilla tipo_casilla)
    {
        this->tipo_casilla = tipo_casilla;
        rect.setFillColor(detail::color_casilla(tipo_casilla));
        auto& textura=detail::textura_casilla(tipo_casilla);
        rect.setTexture(&textura);
    }
    void Casilla::set_texto(const std::string& cadena)
    {
        texto.setString(cadena);
        auto pos=getPosition();
        auto tam=rect.getSize();
        texto.setPosition(pos.x + 0.15*tam.x, pos.y);
    }
    Tipo_casilla Casilla::get_tipo() const
    {
        return tipo_casilla;
    }
}
