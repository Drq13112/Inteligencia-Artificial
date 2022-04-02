#ifndef VISTA_H_INCLUDED
#define VISTA_H_INCLUDED

#include "observador.h"
#include "rejilla.h"
#include "texturas.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace vista
{
    enum class Evento_Vista {EJECUTAR, FIN};
    class Vista: public Observable<Evento_Vista>
    {
        public:
            Vista(unsigned filas, unsigned columnas, unsigned tam_casilla, unsigned alto_panel=80);
            using posicion_y_tipo_casilla = rejilla::Rejilla::posicion_y_tipo_casilla;
            using posicion_casilla = rejilla::Rejilla::posicion_casilla;
            posicion_y_tipo_casilla casilla_inicial();
            posicion_y_tipo_casilla casilla_final();
            std::vector<posicion_casilla> muros();
            void trayectoria_encontrada(const std::vector<posicion_y_tipo_casilla>& solucion, unsigned num_nodos_expandidos, double coste);
            void ejecutar();
        private:
            rejilla::Rejilla rejilla;
            sf::RectangleShape panel;
            sf::RenderWindow render_window;
            std::pair<bool,bool> existe_inicial_final{true,true};

            sf::Text texto_num_movimientos,texto_tiempo, texto_trayectoria_encontrada, texto_coste, texto_falta_casilla;
            sf::Clock tiempo_resolucion;
            sf::Font font;
            void procesa_eventos();
            void procesa_eventos_raton_izq();
            void procesa_eventos_raton_der();
            void borra_texto();
            void procesa_eventos_teclado(sf::Keyboard::Key& evt);
            void render();
            void configura_mensajes_texto();
    };
}
#endif // VISTA_H_INCLUDED
