#include <exception>
#include <iostream>
#include "problema_busqueda.h"
#include "vista.h"

// main como CONTROLADOR

int main()
{
    using namespace grafo;
    using namespace grafo;
    int p = 0;
    //Creamos un grafo por defecto
    Grafo grafo;
    std::string s1, s2;
    std::vector<std::string> v;
    
    while (true)
    {
        try {
            std::cout << " seleccione una opcion: " << std::endl;

            //He puesto esta función con menos 1 porque se me habia olvidado incluirla y por no ponerla al final
            std::cout << "Crear_nodo->-1" << std::endl;
            std::cout << "Borrar_nodo->0" << std::endl;
            std::cout << "Crear_arista_dirigida->1" << std::endl;
            std::cout << "Borrar_arista_dirigida->2" << std::endl;
            std::cout << "Guardar_grafo->3" << std::endl;
            std::cout << "Crear_arista_no_dirigida->4" << std::endl;
            std::cout << "Borrar_arista_no_dirigida->5" << std::endl;
            std::cout << "Mostrar_lista->6" << std::endl;
            std::cin >> p;
            std::cout << " " << std::endl;
            std::cout << p << std::endl;
            switch (p)
            {
            case -1:
                s1 = vista::solicita_string("Nombre de nodo a crear");
                std::cout << "El nodo tiene vecinos: " << std::endl;
                std::cout << "si->0" << std::endl;
                std::cout << "no->1" << std::endl;
                std::cin >> p;

                switch (p)
                {
                case 0:
                    v.clear();

                    do {

                        s2 = vista::solicita_string("Nodo vecino: ");
                        //inserto el nodo en el array
                        v.push_back(s2);
                        std::cout << "Quiere añadir otro nodo? no->1, si->0 " << std::endl;
                        std::cin >> p;
                    } while (p == 0);
                    break;

                case 1:
                    v.clear();//vacio el array por que no tiene nodos vecinos
                    break;

                default:
                    break;
                }
                //creamos el nodo
                grafo.crea_nodo(s1, v);


                break;
            case 0:
                s1 = vista::solicita_string("Nombre de nodo a borrar");
                grafo.borrar_nodo(s1);
                break;
            case 1:
                s1 = vista::solicita_string("Nodo origen");
                s2 = vista::solicita_string("Nodo destino");
                grafo.Crear_arista_dirigida(s1, s2);
                break;

            case 2:
                s1 = vista::solicita_string("Nodo origen");
                s2 = vista::solicita_string("Nodo destino");
                grafo.Borrar_arista_dirigida(s1, s2);
                break;
            case 3:
                s1 = vista::solicita_string("Nombre del grafo:");
                grafo.Guardar_grafo(s1);
                break;
            case 4:
                s1 = vista::solicita_string("Nodo origen");
                s2 = vista::solicita_string("Nodo destino");
                grafo.Crear_arista_no_dirigida(s1, s2);
                break;
            case 5:
                s1 = vista::solicita_string("Nodo origen");
                s2 = vista::solicita_string("Nodo destino");
                grafo.Borrar_arista_no_dirigida(s1, s2);
                break;
            case 6:
                grafo.Muestra_lista();
                break;
            default:
                std::cout << "Opcion no disponible" << std::endl;
                p = 0;
                break;
            }
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << '\n';
        }

    }
}
