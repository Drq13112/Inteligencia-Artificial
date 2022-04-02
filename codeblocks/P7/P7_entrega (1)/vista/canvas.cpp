#include "canvas.h"

namespace vista
{
    void Canvas::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(marco);
        for (const auto& punto : puntos)
            target.draw(punto);

        target.draw(recorrido);

    }
    void Canvas::set_recorrido(const permutacion::Permutacion<unsigned>& nuevo_recorrido)
    {
        if (!nuevo_recorrido.empty()) //Se ha cargado un recorrido
        {
            recorrido = sf::VertexArray(sf::LineStrip);
            unsigned indice;
            for (size_t i = 0; i != nuevo_recorrido.size(); ++i)
            {
                indice = nuevo_recorrido[i];
                sf::Vertex vertice(sf::Vector2f(coordenadas[indice].first,
                                                coordenadas[indice].second),
                                                sf::Color::Black);
                recorrido.append(vertice);
            }
            indice = nuevo_recorrido[0];
            sf::Vertex vertice(sf::Vector2f(coordenadas[indice].first,
                                            coordenadas[indice].second), sf::Color::Black);

            recorrido.append(vertice);
        }
    }

    void Canvas::set_puntos()
    {
        constexpr float radio = 2.;
        puntos.clear();
        if (!coordenadas.empty()) //Se han cargado coordenadas
        {
            sf::CircleShape punto;
            for (auto& p:coordenadas)
            {
                punto.setRadius(radio);
                punto.setFillColor(sf::Color::Black);
                punto.setPosition(p.first - radio, p.second - radio);
                puntos.push_back(punto);
            }
        }
    }

}










