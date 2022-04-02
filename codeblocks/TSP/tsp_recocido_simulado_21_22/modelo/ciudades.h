#ifndef CIUDADES
#define CIUDADES

#include "permutaciones.h"

namespace ciudades
{
    class Ciudades
    {
        public:
            using tipo_dato = unsigned;
            using tipo_contenedor = permutacion::Permutacion<tipo_dato>;
            Ciudades() {}
            Ciudades(const std::vector<std::pair<double, double>>& coordenadas):
                coordenadas{coordenadas}, num_ciudades{coordenadas.size()}
            {
                matriz_distancias();
            }

            double longitud_recorrido(const tipo_contenedor& recorrido) const;

            size_t size() const
            {
                return num_ciudades;
            }

        private:
            std::vector<std::pair<double, double>> coordenadas;
            std::vector<std::vector<double>> distancias;
            size_t num_ciudades;
            void matriz_distancias();
    };


}
#endif // CIUDADES_H_INCLUDED
