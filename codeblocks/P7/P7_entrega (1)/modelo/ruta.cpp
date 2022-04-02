#include "ruta.h"

#include <set>
namespace ruta
{
    //ciudades::Ciudades Ruta::ciudades;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // NO USADO EN EL PROYECTO                                                                                                 //
    // Genera un recorrido según el orden de ciudad inicial
//    void crea_recorrido(unsigned num_ciudades, std::vector<unsigned>& recorrido)
//    {
//        recorrido.clear();
//        for(unsigned i=0; i!=num_ciudades; ++i)
//        {
//            recorrido.push_back(i);
//        }
//    }
//    // Buscamos ciudad mas proxima a ciudad de entre las que quedan en set
//    unsigned get_vecino_mas_proximo( const unsigned c, const std::set<unsigned>& set_ciudades, const ciudades::Ciudades& ciudades)
//    {
//        unsigned ciudad = 0;
//        std::set<unsigned>::iterator it=set_ciudades.begin();
//        // Inicializa la distancia minima
//        double min_dist = ciudades.distancia(c,*it);
//
//
//        for(it=set_ciudades.begin(); it!= set_ciudades.end(); it++)
//        {
//            unsigned n = *it;
//            double dist=ciudades.distancia(c,n);
//
//            if(dist<=min_dist)
//            {
//                ciudad = n;
//                min_dist = dist;
//            }
//        }
//        return ciudad;
//    }
//// Ruta que escoge la primera ciudad, luego la más cercana, luego la mas cercana a esta última, etc...
//    void crea_recorrido_avaro(std::vector<unsigned>& recorrido,const ciudades::Ciudades& ciudades)
//    {
//        recorrido.clear();
//        std::set<unsigned> set_ciudades; //Lista ordenada (posiblemente un arbol rojinegro)
//        std::set<unsigned>::iterator it;
//
//        auto num_ciudades = ciudades.size();
//
//        for(unsigned i=0; i!=num_ciudades; ++i)
//        {
//            set_ciudades.insert(i);
//        }
//
//        unsigned ciudad=0; //Nuestra primera ciudad del recorrido
//        for(unsigned i=0; i<num_ciudades-1; ++i)
//        {
//            // Añadimos ciudad
//            recorrido.push_back(ciudad);
//            // Eliminamos la ciudad de nuestro conjunto
//            it = set_ciudades.find(ciudad); //Al estar ordenadas dentro de set su búsqueda es rápida
//            set_ciudades.erase(it);
//            ciudad=get_vecino_mas_proximo(ciudad,set_ciudades,ciudades);
//        }
//        recorrido.push_back(ciudad);
//    }

}
