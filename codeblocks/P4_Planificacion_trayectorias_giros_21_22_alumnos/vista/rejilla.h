#ifndef REJILLA_H_INCLUDED
#define REJILLA_H_INCLUDED

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include "casilla.h"
#include <vector>
#include <random>

namespace rejilla
{
    class Rejilla:public sf::Drawable
    {
        public:
            Rejilla(unsigned filas, unsigned columnas, unsigned tam_casilla);

            using posicion_casilla = std::pair<unsigned, unsigned>;
            using posicion_y_tipo_casilla = std::pair<posicion_casilla, Tipo_casilla>;

            //Manipulacion de la posicion y tipo de casillas
            void set_casilla_inicial(const sf::Vector2u& posicion, std::pair<bool, bool>& inicial_final);
            void set_casilla_final(const sf::Vector2u& posicion, std::pair<bool, bool>& inicial_final);
            void gira_casilla(const sf::Vector2u& posicion);
            void cambia_casilla(const sf::Vector2u& posicion,std::pair<bool, bool>& inicial_final);
            void borra_casilla_inicial_final(const sf::Vector2u& posicion);

            //Obtencion de casillas inicial y final y muros
            posicion_y_tipo_casilla get_casilla_inicial() const;
            posicion_y_tipo_casilla get_casilla_final() const;
            std::vector<posicion_casilla> muros() const;

            void borra_trayectoria();
            void inicializa_rejilla();
            void dibuja_trayectoria(const std::vector<posicion_y_tipo_casilla>& solucion);
            void crea_rejilla_aleatorio();

            virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        private:
            unsigned filas, columnas;
            unsigned tam_casilla;
            std::vector<Casilla> casillas;
            unsigned indice_casilla(const sf::Vector2u& posicion) const;
            Tipo_casilla get_tipo_casilla(const sf::Vector2u& posicion) const;
            void set_tipo_casilla(const sf::Vector2u& posicion, Tipo_casilla tipo_casilla);
            void set_tipo_casilla(const posicion_casilla& posicion, Tipo_casilla tipo_casilla);

    };
}
#endif // REJILLA_H_INCLUDED
