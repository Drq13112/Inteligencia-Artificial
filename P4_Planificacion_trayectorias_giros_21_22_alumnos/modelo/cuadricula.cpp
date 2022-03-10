#include "cuadricula.h"

namespace cuadricula
{
    void Cuadricula::set_muros(const std::vector<Punto_2d> &lista_muros)
    {
        muros.clear();
        for (auto punto : lista_muros)
        {
            muros.insert(columnas*punto.x + punto.y);
        }
    }
    void Cuadricula::set_filas_columnas(const Punto_2d &inicio, const Punto_2d &fin, const std::vector <Punto_2d> &mur)
    {
        auto fil = fin.x;
        auto col = fin.y;
        if (inicio.x > fil)
            fil = inicio.x;
        if (inicio.y > col)
            col = inicio.y;
        for (auto punto : mur)
        {
            if (punto.x > fil)
                fil = punto.x;
            if (punto.y > col)
                col = punto.y;
        }
        fil += 2;
        col += 2;
        filas = fil;
        columnas = col;
    }
}
