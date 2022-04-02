#include "ciudades.h"
#include <cmath>

namespace ciudades
{
    // Calcula la matriz de distancias entre las ciudades
    void Ciudades::matriz_distancias()
    {
        //Crea e inicializa a 0 la matriz de distancias
        distancias = std::vector<std::vector<double>>(num_ciudades, std::vector<double>(num_ciudades, 0.));

        //Calcula las distancias euclideas 2D
        for (size_t i = 0; i < num_ciudades; ++i)
        {
            double x1, y1, x2, y2;
            x1 = coordenadas[i].first;
            y1 = coordenadas[i].second;
            for (size_t j = i + 1; j < num_ciudades; ++j)
            {
                x2 = coordenadas[j].first;
                y2 = coordenadas[j].second;

                distancias[i][j] = distancias[j][i] = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
            }
        }
    }

    double Ciudades::longitud_recorrido(const tipo_contenedor& recorrido) const
    {
        double distancia = 0.0;
        for (size_t i = 0; i < num_ciudades - 1; ++i)
            distancia += distancias[recorrido[i]][recorrido[i+1]];

        // Distancia entre la última y la primera
        distancia += distancias[recorrido[num_ciudades-1]][recorrido[0]];

        return(distancia);
    }


}
