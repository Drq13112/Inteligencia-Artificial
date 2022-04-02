#ifndef GENERADOR_ALEATORIOS_H
#define GENERADOR_ALEATORIOS_H

#include "randutils.h"
namespace rng
{
    template<typename Distribucion>
    class Generador_aleatorios
    {
    public:
        using T = typename Distribucion::result_type;
        Generador_aleatorios():dist{Distribucion{0, 0}}
        {
            randutils::auto_seed_256 seeds;
            rng.seed(seeds);
        }
        // Semilla "aleatoria"
        Generador_aleatorios(T min, T max):dist{Distribucion{min, max}}
        {
            randutils::auto_seed_256 seeds;
            rng.seed(seeds);
        }
        // Semilla "fija"
        Generador_aleatorios(unsigned seed, T min, T max):dist{Distribucion{min, max}}
        {
            rng.seed(seed);
        }
        T operator()()
        {
            return dist(rng);
        }
        T operator()(T min, T max)
        {
            return Distribucion{min, max}(rng);
        }
    private:
        Distribucion dist;
        std::mt19937 rng;
    };

    using uniforme_int = Generador_aleatorios<std::uniform_int_distribution<int>>;
    using uniforme_size_t = Generador_aleatorios<std::uniform_int_distribution<size_t>>;
    using uniforme_double = Generador_aleatorios<std::uniform_real_distribution<double>>;
    using normal_double = Generador_aleatorios<std::normal_distribution<double>>;


}  // namespace rng
#endif // GENERADOR_ALEATORIOS_H
