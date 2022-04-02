#include "dardos_pi.h"
#include "generador_aleatorios.h"
#include <random>


double Dardos_Pi::calcular(const unsigned iteraciones)
{
    double contador=0;
    double x,y;
    rng::uniforme_double r_u_double(0.0,1.0);
    for(size_t i=0; i<iteraciones;i++)
    {
        x=r_u_double();
        y=r_u_double();
        //std::cout<<"x: "<<x<<"y: "<<y<<std::endl;
        //Si la posicion está dentro de la circunferencia de radio 1:
        if(x*x+y*y<=1)
        {
            contador ++;
        }
    }
    //std::cout<<"Resultado:"<<(contador*4)/iteraciones<<std::endl;
    return contador*4/iteraciones;
}
