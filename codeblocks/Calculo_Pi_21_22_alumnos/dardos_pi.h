#ifndef DARDOS_PI_H_INCLUDED
#define DARDOS_PI_H_INCLUDED

#include <stdexcept>
#include <iostream>
#include <sstream>

class Dardos_Pi
{
    public:
        double operator()(const unsigned iteraciones)
        {
            if (iteraciones < num_min_iteraciones)
            {
                std::stringstream ss;
                ss << "Las iteraciones deben ser iguales o superiores a " << num_min_iteraciones;
                throw std::invalid_argument(ss.str());
            }
            return calcular(iteraciones);
        }
    private:
        double calcular(const unsigned);
        const unsigned num_min_iteraciones = 100;
};

#endif // DARDOS_PI_H_INCLUDED
