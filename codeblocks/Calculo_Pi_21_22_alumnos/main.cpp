#include "dardos_pi.h"

int main()
{
    try
    {
        std::cout << Dardos_Pi{}(100000) << std::endl;
    }
    catch(const std::invalid_argument &mensaje)
    {
        std::cout << mensaje.what() << std::endl;
    }


    return 0;
}

