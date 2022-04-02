#include "controlador.h"
#include "dialogo_fichero_windows.h"
#include <thread>
#include <fstream>
#include <iostream>

namespace controlador
{
    void Controlador::registra_observadores()
    {
        //EVENTOS VISTA
        vista.registra_observador(vista::Evento_vista::ejecutar,[this]()
        {
            ejecuta_rs();
        });
        vista.registra_observador(vista::Evento_vista::cargar, [this]()
        {
            carga_problema_tsplib();
        });

        vista.registra_observador(vista::Evento_vista::detener, [this]()
        {
            algoritmo_rs.detener();
        });
        vista.registra_observador(vista::Evento_vista::finalizar_programa, [this]()
        {
            finaliza_programa();
        });

        //EVENTOS MODELO
        algoritmo_rs.registra_observador(rs::Evento_modelo::nuevo_minimo,[this]()
        {
            push_datos();
        });
        algoritmo_rs.registra_observador(rs::Evento_modelo::fin,[this]()
        {
            fin_rs();
        });
    }

    bool Controlador::carga_problema_tsplib()
    {
        std::string fichero_tsp;
        if(lee_nombre_fichero(fichero_tsp))
        {
            auto tsp_lib = carga_ciudades(fichero_tsp);  //Carga el vector de coordenadas y la matriz de distancias
            ciudades = ciudades::Ciudades{tsp_lib.coordenadas};
            if(set_coordenadas_visualizacion(tsp_lib.coordenadas))
            {
                auto recorrido_optimo = permutacion::Permutacion{tsp_lib.recorrido_optimo, 0};
                vista.actualiza_recorrido(recorrido_optimo, " ", " ") ;
                vista.set_texto_distancia_optima("Óptimo : " + std::to_string(ciudades.longitud_recorrido(recorrido_optimo)));
                vista.muestra_boton_ejecutar();
                return true;
            }
        }
        return false;
    }

    void Controlador::finaliza_programa()
    {
        algoritmo_rs.detener();
        fin_algoritmo = true;
        vacia_datos();
        c_v_barrera_datos.notify_one();      //Desbloqueamos el hilo pop_datos()
        if (hilo_cola_datos.joinable())
            hilo_cola_datos.join();

        if(hilo_modelo.joinable())
            hilo_modelo.join();
    }

    void Controlador::ejecuta_rs()
    {
        vista.oculta_boton_cargar();
        vista.oculta_boton_ejecutar();
        vista.muestra_boton_detener();
        fin_algoritmo  = false;

        if (hilo_cola_datos.joinable())
            hilo_cola_datos.join();
        hilo_cola_datos = std::thread(pop_datos, this);

        if(hilo_modelo.joinable())
            hilo_modelo.join();

////////////////////////////////////////////////////////////////////////////////////
//  Podría leerse de un fichero y/o autoconfigurarse
        parametros.num_descensos = 100*ciudades.size();
        parametros.num_permutaciones = 100*ciudades.size();
        parametros.num_exitos_maximo = 10*ciudades.size();
        parametros.temperatura = algoritmo_rs.compute_initial_temperature(ruta::Ruta(ciudades));
        parametros.factor_descenso = 0.999;

        //TODO
        //A completar: el alumno invocará desde aquí a inicializacion para
        //sintonizar la temperatura inicial
////////////////////////////////////////////////////////////////////////////////////
        hilo_modelo = std::thread(algoritmo_rs.ejecutar, &algoritmo_rs, ruta::Ruta(ciudades), parametros);
    }

    void Controlador::fin_rs()
    {
        fin_algoritmo = true;
        vacia_datos();
        c_v_barrera_datos.notify_one();      //Desbloqueamos el hilo pop_datos()

        vista.oculta_boton_detener();
        vista.oculta_boton_ejecutar();
        vista.muestra_boton_cargar();
    }


    void Controlador::ejecutar()
    {
        vista.ejecutar();
    }

    void Controlador::push_datos()
    {
        std::unique_lock<std::mutex>u_l(barrera_datos);    //Bloqueamos eliminar recorrido
        datos.push({algoritmo_rs.get_solucion(), algoritmo_rs.get_iteracion_actual()});
        c_v_barrera_datos.notify_one();
    }

    void Controlador::pop_datos()
    {
        while(!fin_algoritmo)
        {
            std::unique_lock<std::mutex>u_l(barrera_datos);    //Bloqueamos añadir nuevo recorrido
            while(datos.empty() && !fin_algoritmo)
            {
                c_v_barrera_datos.wait(u_l);
            }

            if(fin_algoritmo)
            {
                while(!datos.empty())
                {
                    auto dato = std::move(datos.front());
                    datos.pop();
                    vista.actualiza_recorrido(dato.ruta.estado(), "Iteración: " +
                                              std::to_string(dato.iteracion),"Distancia: " +
                                              std::to_string(dato.ruta.valor));
                }
            }
            else
            {
                auto dato = std::move(datos.front());
                datos.pop();
                u_l.unlock(); //Desbloqueamos lo antes posible
                vista.actualiza_recorrido(dato.ruta.estado(), "Iteración: " +
                                          std::to_string(dato.iteracion), "Distancia: " +
                                          std::to_string(dato.ruta.valor));
            }
        }
    }
    void Controlador::vacia_datos()
    {
        std::unique_lock<std::mutex>u_l(barrera_datos);    //Bloqueamos
        while(!datos.empty()) //Vaciamos la cola de datos
            datos.pop();
    }

    //Los valores extremos los usamos para normalizar a las dimensiones de la pantalla a la hora de dibujar
    void calcula_valores_extremos(const std::vector<std::pair<double, double>>& coordenadas,
                                  double &x_min, double &x_max, double &y_min, double &y_max)
    {
        if (coordenadas.size() > 1) //Al menos 2 ciudades
        {
            x_min = coordenadas[0].first;
            x_max = coordenadas[0].first;
            y_min = coordenadas[0].second;
            y_max = coordenadas[0].second;
        }
        for (auto &p:coordenadas)
        {
            if (p.first < x_min)
                x_min = p.first;
            else if (p.first > x_max)
                x_max = p.first;
            if (p.second < y_min)
                y_min = p.second;
            else if (p.second > y_max)
                y_max = p.second;
        }
    }
    // Transfiere coordenadas desde la clase Ciudades a la clase Canvas
    bool Controlador::set_coordenadas_visualizacion(const std::vector<std::pair<double, double>>& coordenadas)
    {
        double x_min, x_max, y_min, y_max;
        calcula_valores_extremos(coordenadas, x_min, x_max, y_min, y_max);
        if (x_min == x_max || y_min == y_max) //Las ciudades están en una vertical o en una horizontal
        {
            return false;  //El problema es trivial y no tiene sentido buscar una solución
        }

        std::vector<std::pair<unsigned, unsigned>> coordenadas_canvas; //Coordenadas de las ciudades normalizadas a las dimensiones del CANVAS

        unsigned x_sup_izq, y_sup_izq, x_inf_der, y_inf_der;
        vista.get_rectangulo_canvas(x_sup_izq, y_sup_izq, x_inf_der, y_inf_der);

        double x, y;   //coordenadas reales
        double xn, yn; //coordenadas reales normalizadas en [0,1]
        unsigned xv, yv;   //coordenadas int ajustadas al espacio de visualizacion
        for(auto& p : coordenadas)
        {
            x = p.first;
            y = p.second;
            xn = (x - x_min)/(x_max - x_min);  //No tenemos división por 0 al garantizarlo más arriba
            yn = (y - y_min)/(y_max - y_min);
            xv = unsigned(x_sup_izq + xn*(x_inf_der - x_sup_izq));
            yv = unsigned(y_sup_izq + yn*(y_inf_der - y_sup_izq));
            coordenadas_canvas.push_back({yv, xv});  //Coordenadas cambiadas
        }
        vista.set_coordenadas(coordenadas_canvas);
        return true;
    }

    //Lee un fichero normalizado TSPLIB
    //Para simplificar, sin pérdida de generalidad, solo contemplamos distancias euclideas 2D
    Tsp_lib carga_ciudades(const std::string& nombre_fichero)
    {
        Tsp_lib tsp_lib;

        tsp_lib.coordenadas.clear();
        tsp_lib.recorrido_optimo.clear();

        unsigned num_ciudades = 0;

        std::ifstream fichero;
        fichero.open(nombre_fichero);

        if (!fichero)
            throw std::runtime_error("No se pudo abrir el fichero " + nombre_fichero);


        // Leemos linea a linea el fichero TSPLIB
        // Verificamos que es del tipo EUC_2D
        // Formamos el vector de coordenadas

        std::string linea = " ";
        std::string palabra;

        tsp_lib.exito = false;
        while(linea != "EOF")
        {
            std::getline(fichero, linea);
            if (linea == "NODE_COORD_SECTION")
            {
                double x, y;
                //std::cout<< linea <<std::endl;
                for (unsigned i = 0; i < num_ciudades; ++i)
                {
                    std::getline(fichero, linea); //leemos las lineas con las coordenadas
                    std::stringstream linea_stream(linea);
                    getline(linea_stream, palabra, ' ');  //Obtenemos el indice de ciudad. No lo utilizamos
                    getline(linea_stream, palabra, ' ');  //Obtenemos la coordenada x;
                    std::stringstream palabra_stream_x(palabra);
                    palabra_stream_x >> x;  //Pasamos de string a double
                    getline(linea_stream, palabra, ' ');  //Obtenemos la coordenada y;
                    std::stringstream palabra_stream_y(palabra);
                    palabra_stream_y >> y;  //Pasamos de string a double
                    tsp_lib.coordenadas.push_back({x, y}); //Almacenamos las coordenadas
                }
            }
            else if (linea == "TOUR_SECTION")
            {
                // std::cout<<linea<<std::endl;
                unsigned indice;
                for (unsigned i = 0; i < num_ciudades; ++i)
                {
                    getline(fichero, linea); //leemos las lineas con las coordenadas
                    std::stringstream indice_stream(linea);
                    indice_stream >> indice;  //Pasamos de string a unsigned
                    tsp_lib.recorrido_optimo.push_back({indice-1}); //Almacenamos los indices (restamos 1)
                }
            }
            else
            {
                std::stringstream linea_stream(linea);
                getline(linea_stream, palabra, ' ');  //Obtenemos la primera palabra de la linea de texto
                if (palabra == "EDGE_WEIGHT_TYPE")
                {
                    getline(linea_stream,palabra, ' '); //Leemos el texto correspondiente a los dos puntos :
                    getline(linea_stream,palabra, ' '); //Leemos el texto correspondiente al tipo de distancia
                    if(palabra == "EUC_2D")              //solo trabajamos con ficheros TSPLIB con distancias euclideas 2D
                    {
                        tsp_lib.exito = true;
                        //std::cout << "EUC_2D" << std::endl;
                    }
                }
                else if (palabra == "EDGE_WEIGHT_TYPE:")
                {
                    getline(linea_stream, palabra, ' '); //Leemos el texto correspondiente al tipo de distancia
                    if(palabra=="EUC_2D")              //solo trabajamos con ficheros TSPLIB con distancias euclideas 2D
                    {
                        tsp_lib.exito = true;
                        // std::cout << "EUC_2D" << std::endl;
                    }
                }
                else if (palabra == "DIMENSION")
                {
                    getline(linea_stream, palabra, ' '); //Leemos el texto correspondiente a los dos puntos :
                    getline(linea_stream, palabra, ' '); //Leemos el texto correspondiente al numero de ciudades
                    std::stringstream palabra_stream(palabra);
                    palabra_stream >> num_ciudades;  //Pasamos de string a int: ¡Ya tenemos el numero de ciudades!
                    //std::cout << num_ciudades << std::endl;
                }
                else if (palabra == "DIMENSION:")
                {
                    getline(linea_stream, palabra, ' '); //Leemos el texto correspondiente al numero de ciudades
                    std::stringstream palabra_stream(palabra);
                    palabra_stream >> num_ciudades;  //Pasamos de string a int: ¡Ya tenemos el numero de ciudades!
                    // std::cout << num_ciudades << std::endl;
                }
                else if (palabra == "NAME")
                {
                    std::string nom_fich;
                    getline(linea_stream, palabra, ' '); //Leemos el texto correspondiente a los dos puntos :
                    getline(linea_stream, nom_fich, ' '); //Leemos el texto correspondiente al nombre del fichero
                    // std::cout << nombre_fich << std::endl;
                }
                else if (palabra == "NAME:")
                {
                    std::string nom_fich;
                    getline(linea_stream, nom_fich, ' '); //Leemos el texto correspondiente al nombre del fichero
                    // std::cout << nombre_fich << std::endl;
                }
            }
        }
        fichero.close();

        return tsp_lib;
    }
}
