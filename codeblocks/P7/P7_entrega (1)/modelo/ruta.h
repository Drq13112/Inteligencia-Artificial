#ifndef RUTA
#define RUTA

#include "ciudades.h"

namespace ruta
{
    class Ruta
    {
            using tipo_valor = double;
            using tipo_contenedor = typename ciudades::Ciudades::tipo_contenedor;
        public:
            Ruta() {}
            Ruta(const ciudades::Ciudades& ciudades):p{tipo_contenedor{ciudades.size()}}
            {
                valor = ciudades.longitud_recorrido(p);
                this->ciudades = ciudades;
            }
            Ruta(const tipo_contenedor& p):p{p}
            {
                valor = ciudades.longitud_recorrido(p);
            }

            Ruta sucesor_rnd() const
            {
                //Limites para valores aleatorios elegidos "a pelo"
                constexpr double limite1 = 0.4;
                constexpr double limite2 = 0.8;
                static rng::uniforme_double aleatorio_0_1{0, 1};
                tipo_contenedor p_copia{p};

                auto aleatorio = aleatorio_0_1();

                if (aleatorio < limite1)
                    p_copia.rotacion_3_puntos();
                else if (aleatorio < limite2)
                    p_copia.rotacion_2_puntos();
                else
                    p_copia.intercambio_2_puntos();

                // Para depuración
//                if (!p_copia.es_permutacion(0))
//                {
//                    throw std::logic_error("El vector introducido no es una permutacion {inicial, inicial+1, ..., inicial + tam - 1}.");
//                }

                return Ruta{p_copia};
            }

            tipo_contenedor estado() const
            {
                return p;
            }
            tipo_valor valor;
        private:
            tipo_contenedor p;
            static inline ciudades::Ciudades ciudades;
    };
}

#endif // RUTA_H_INCLUDED
