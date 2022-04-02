#ifndef PERMUTACION_H_INCLUDED
#define PERMUTACION_H_INCLUDED

#include "generador_aleatorios.h"
#include <vector>

#include <iostream>
namespace permutacion
{
    //IMPORTANTE: El diseño prima la rápida ejecución de los aleatorios. De ahí su caracter static.
    //Por eso, no es factible tener simultáneamente en un programa dos permutaciones de tamaño
    //diferente.

    template<typename T>
    class Permutacion
    {
            friend std::ostream& operator << (std::ostream& os, const Permutacion<T>& p)
            {
                for (auto x : p.v)
                    os << x << "\n";
                return os;
            }
        public:
            Permutacion()
            {
            }
            Permutacion(size_t tam)
            {
                if (tam < 2)
                    throw std::length_error("La dimension de la permutacion debe ser mayor que 1.");
                v.resize(tam);
                std::iota(v.begin(), v.end(), 0);
                std::random_shuffle(v.begin(), v.end());

                aleatorio = rng::uniforme_size_t{0, v.size() - 1};
            }
            Permutacion(const std::vector<T>& v, size_t inicial=0): v{v}
            {
                if (v.size() < 2)
                    throw std::length_error("La dimension de la permutacion debe ser mayor que 1.");

                // Verificamos que p es una permutacion de {inicial, inicial+1, ..., inicial + tam - 1}
                if (!es_permutacion(inicial))
                    throw std::logic_error("El vector introducido no es una permutacion {inicial, inicial+1, ..., inicial + tam - 1}.");

                aleatorio = rng::uniforme_size_t{0, v.size() - 1};
            }

            bool operator == (const Permutacion& p)
            {
                return p.v == v;
            }

            T operator[](size_t indice) const
            {
                return v[indice];
            }

            bool empty() const
            {
                return v.empty();
            }

            size_t size() const
            {
                return v.size();
            }

            void rotacion_2_puntos();
            void intercambio_2_puntos();
            void rotacion_3_puntos();
            bool es_permutacion(size_t inicial);
        private:
            std::vector<T> v;
            static inline rng::uniforme_size_t aleatorio;
    };


    template<typename T>
    bool Permutacion<T>::es_permutacion(size_t inicial)
    {
        auto aux1{v}, aux2{v};
        std::sort(aux1.begin(), aux1.end());
        std::iota(aux2.begin(), aux2.end(), inicial);
        return aux1 == aux2;
    }

    template<typename T>
    void Permutacion<T>::rotacion_2_puntos()
    {
        size_t c1 = aleatorio();
        size_t c2;
        do
        {
            c2 = aleatorio();
        }
        while (c1 == c2);

        if (c1 > c2)
            std::swap(c1, c2);

        auto it1 = v.begin() + c1;
        auto it2 = v.begin() + c2 + 1;

        std::reverse(it1, it2);
    }

    template<typename T>
    void Permutacion<T>::intercambio_2_puntos()
    {
        size_t c1 = aleatorio();
        size_t c2;
        do
        {
            c2 = aleatorio();
        }
        while (c1 == c2);

        std::swap(v[c1], v[c2]);
    }

    template<typename T>
    void Permutacion<T>::rotacion_3_puntos()
    {
        size_t c[3] {aleatorio(), aleatorio(), aleatorio()};

        std::sort(c, c+3);

        auto it1 = v.begin() + c[0];
        auto it2 = v.begin() + c[1];
        auto it3 = v.begin() + c[2] + 1;
        std::rotate(it1, it2, it3);
    }

    template<typename T>
    Permutacion<T> rotacion_2_puntos(const Permutacion<T>& p)
    {
        auto p_copia = p;
        p_copia.rotacion_2_puntos();
        return p_copia;
    }

    template<typename T>
    Permutacion<T> rotacion_3_puntos(const Permutacion<T>& p)
    {
        auto p_copia = p;
        p_copia.rotacion_3_puntos();
        return p_copia;
    }

    template<typename T>
    Permutacion<T> intercambio_2_puntos(const Permutacion<T>& p)
    {
        auto p_copia = p;
        p_copia.intercambio_2_puntos();
        return p_copia;
    }
}
#endif // PERMUTACION_H_INCLUDED
