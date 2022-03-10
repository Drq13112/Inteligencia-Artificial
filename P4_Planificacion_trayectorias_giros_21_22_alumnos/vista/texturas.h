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
                if (!flecha_N.loadFromFile("C:/Users/david/OneDrive/Documentos/4 curso/2 cuatri/Inteligencia artificial/P4_Planificacion_trayectorias_giros_21_22_alumnos/vista/imgs/flecha_N.png")
                        || !flecha_S.loadFromFile("C:/Users/david/OneDrive/Documentos/4 curso/2 cuatri/Inteligencia artificial/P4_Planificacion_trayectorias_giros_21_22_alumnos/C:/Users/david/OneDrive/Documentos/4 curso/2 cuatri/Inteligencia artificial/P4_Planificacion_trayectorias_giros_21_22_alumnos/vista/imgs/flecha_S.png")
                        || !flecha_E.loadFromFile("C:/Users/david/OneDrive/Documentos/4 curso/2 cuatri/Inteligencia artificial/P4_Planificacion_trayectorias_giros_21_22_alumnos/C:/Users/david/OneDrive/Documentos/4 curso/2 cuatri/Inteligencia artificial/P4_Planificacion_trayectorias_giros_21_22_alumnos/vista/imgs/flecha_E.png")
                        || !flecha_O.loadFromFile("C:/Users/david/OneDrive/Documentos/4 curso/2 cuatri/Inteligencia artificial/P4_Planificacion_trayectorias_giros_21_22_alumnos/C:/Users/david/OneDrive/Documentos/4 curso/2 cuatri/Inteligencia artificial/P4_Planificacion_trayectorias_giros_21_22_alumnos/vista/imgs/flecha_O.png")
                        || !flecha_NE.loadFromFile("C:/Users/david/OneDrive/Documentos/4 curso/2 cuatri/Inteligencia artificial/P4_Planificacion_trayectorias_giros_21_22_alumnos/C:/Users/david/OneDrive/Documentos/4 curso/2 cuatri/Inteligencia artificial/P4_Planificacion_trayectorias_giros_21_22_alumnos/vista/imgs/flecha_NE.png")
                        || !flecha_EN.loadFromFile("C:/Users/david/OneDrive/Documentos/4 curso/2 cuatri/Inteligencia artificial/P4_Planificacion_trayectorias_giros_21_22_alumnos/C:/Users/david/OneDrive/Documentos/4 curso/2 cuatri/Inteligencia artificial/P4_Planificacion_trayectorias_giros_21_22_alumnos/vista/imgs/flecha_EN.png")
                        || !flecha_NO.loadFromFile("C:/Users/david/OneDrive/Documentos/4 curso/2 cuatri/Inteligencia artificial/P4_Planificacion_trayectorias_giros_21_22_alumnos/vista/imgs/flecha_NO.png")
                        || !flecha_ON.loadFromFile("C:/Users/david/OneDrive/Documentos/4 curso/2 cuatri/Inteligencia artificial/P4_Planificacion_trayectorias_giros_21_22_alumnos/vista/imgs/flecha_ON.png")
                        || !flecha_SE.loadFromFile("C:/Users/david/OneDrive/Documentos/4 curso/2 cuatri/Inteligencia artificial/P4_Planificacion_trayectorias_giros_21_22_alumnos/vista/imgs/flecha_SE.png")
                        || !flecha_ES.loadFromFile("C:/Users/david/OneDrive/Documentos/4 curso/2 cuatri/Inteligencia artificial/P4_Planificacion_trayectorias_giros_21_22_alumnos/vista/imgs/flecha_ES.png")
                        || !flecha_SO.loadFromFile("C:/Users/david/OneDrive/Documentos/4 curso/2 cuatri/Inteligencia artificial/P4_Planificacion_trayectorias_giros_21_22_alumnos/vista/imgs/flecha_SO.png")
                        || !flecha_OS.loadFromFile("C:/Users/david/OneDrive/Documentos/4 curso/2 cuatri/Inteligencia artificial/P4_Planificacion_trayectorias_giros_21_22_alumnos/vista/imgs/flecha_OS.png")
                        || !cruz.loadFromFile("C:/Users/david/OneDrive/Documentos/4 curso/2 cuatri/Inteligencia artificial/P4_Planificacion_trayectorias_giros_21_22_alumnos/vista/imgs/cruz.png")
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
