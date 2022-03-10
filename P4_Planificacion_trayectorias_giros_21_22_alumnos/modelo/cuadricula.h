#ifndef CUADRICULA_H_INCLUDED
#define CUADRICULA_H_INCLUDED
#include <vector>
#include <unordered_set>
#include <math.h>
//Se supone que la cuadricula se desarrolla entre {0,0} y {filas-1,columnas-1}
namespace cuadricula
{
    struct Punto_2d
    {
        unsigned x;
        unsigned y;
    };

    class Cuadricula
    {
    public:
        Cuadricula(){}
        void crea_cuadricula(const Punto_2d &inicio, const Punto_2d &fin, const std::vector <Punto_2d> &lista_muros)
        {
           //Obtenemos la maxima x y la maxima y entre la posicion inicial, final y muros
            set_filas_columnas(inicio, fin, lista_muros);
            set_muros(lista_muros); //Almacenamos muros con unordered_set
        }
        unsigned get_filas() const
        {
            return(filas);
        }
        unsigned get_columnas() const
        {
            return(columnas);
        }
        const std::unordered_set<unsigned>& get_muros() const
        {
            return muros;
        }

    private:
        void set_muros(const std::vector<Punto_2d> &lista_muros);
        void set_filas_columnas(const Punto_2d &inicio, const Punto_2d &fin, const std::vector <Punto_2d> &lista_muros);
        unsigned filas;
        unsigned columnas;
        std::unordered_set<unsigned> muros;
    };
}
#endif // CUADRICULA_H_INCLUDED
