#include "grafo.h"
#include <iostream>
#include <fstream>


namespace grafo
{
    Grafo Nodo_grafo::grafo = Grafo();  // Inicializaci�n variable est�tica de la clase

    void Grafo::borrar_nodo(const std::string& s)
    {
        //declaro el iterador
        std::map<std::string, std::vector<std::string>>::iterator it;

        //compruebo que no este vacia la lista
        if (nodos.empty() == false)
        {
            it = nodos.find(s);
            //elimino el nodo y me aseguro de que está en la lista
            if (it != nodos.end())
                nodos.erase(it);
            else {
                std::cout << "El nodo no está guardado" << std::endl;
            }
        }
        //Ahora hay que eliminar el nodo de la lista de vecinos de todos los nodos

        std::string letra_aux;
        //Creo un array para operar con el
        std::vector<std::string> array_aux;

        it = nodos.begin();

        while (it != nodos.end()) 
        {
            array_aux = it->second;

            for (size_t i = 0; i < array_aux.size(); i++)
            {
                letra_aux = array_aux[i];

                //En caso de que se encuentre el nodo en el array de vecinos, lo eliminamos
                if (letra_aux == s)
                {
                    array_aux.erase(std::remove(array_aux.begin(), array_aux.end(), s), array_aux.end());
                }

            }

            //actualizo la lista de vecino del nodo
            it->second = array_aux;
            it++;
        }
    }

    void Grafo::Crear_arista_dirigida(const std::string& s1, const std::string& s2)
    {
        //actualizo los vecinos de los dos nodos
        //Tienen que estar creados los dos
        //Si ya tiene establecida la relacion no se esta no se crea

        std::map<std::string, std::vector<std::string>>::iterator it;
        std::string letra_aux;
        //Creo un array para operar con el
        std::vector<std::string> array_aux;
        bool nodo_en_array = false;


        //actualizamos s1
        it = nodos.find(s1);//devuelve nodos.end() en caso de que no encuentre el nodo
        if (it == nodos.end())
        {
            perror ("El nodo no está en la lista");
        }
        else {
            array_aux = it->second;

            //Compruebo que el nodo objetivo no este ya guardado en el array
            for (size_t i = 0; i < array_aux.size(); i++)
            {
                letra_aux = array_aux[i];
                if (letra_aux == s2) {
                    nodo_en_array = true;
                }
            }

            if (nodo_en_array == false)
                array_aux.push_back(s2);

            //Actualizo la lista
            it->second = array_aux;
        }

        //Lo mismo pero para el s2
        nodo_en_array = false;
        it = nodos.find(s2);
        if (it == nodos.end())
            perror("El nodo no está en la lista");
        else {

            array_aux = it->second;

            //Compruebo que el nodo objetivo no este ya guardado en el array
            for (size_t i = 0; i < array_aux.size(); i++)
            {
                letra_aux = array_aux[i];
                if (letra_aux == s1) {
                    nodo_en_array = true;
                }
            }

            if (nodo_en_array == false)
                array_aux.push_back(s1);

            //Actualizo la lista
            it->second = array_aux;
        }
    }
    void Grafo::Borrar_arista_dirigida(const std::string& s1, const std::string& s2)
    {
        //Eliminamos a los dos nodos de la lista de vecinos de cada uno
        bool nodo_en_array = false;
        std::map<std::string, std::vector<std::string>>::iterator it;
        std::string letra_aux;
        //Creo un array para operar con el
        std::vector<std::string> array_aux;


        //elimino el nodo en el array de vecinos de s1
        it = nodos.find(s1);
        if (it == nodos.end())
            perror("El nodo no está en la lista");
        else {
            array_aux = it->second;

            //Compruebo que el nodo objetivo ya está guardado en el array
            for (size_t i = 0; i < array_aux.size(); i++)
            {
                letra_aux = array_aux[i];
                if (letra_aux == s2) {
                    nodo_en_array = true;
                }
            }

            //elimino el nodo de la lista
            if (nodo_en_array == true)
                array_aux.erase(std::remove(array_aux.begin(), array_aux.end(), s2), array_aux.end());

            //Actualizo la lista
            it->second = array_aux;
        }
        //Lo mismo para s2
        nodo_en_array = false;

        it = nodos.find(s2);
        if (it == nodos.end())
            perror("El nodo no está en la lista");
        else {
            array_aux = it->second;

            //Compruebo que el nodo objetivo ya está guardado en el array
            for (size_t i = 0; i < array_aux.size(); i++)
            {
                letra_aux = array_aux[i];
                if (letra_aux == s1) {
                    nodo_en_array = true;
                }
            }

            //elimino el nodo del array
            if (nodo_en_array == true)
                array_aux.erase(std::remove(array_aux.begin(), array_aux.end(), s1), array_aux.end());

            //Actualizo la lista 
            it->second = array_aux;
        }
    }

    void Grafo::Guardar_grafo(const std::string& nombre_fichero)
    {
        std::ofstream fichero(nombre_fichero);

        if (!fichero)
            throw std::runtime_error("No se pudo abrir el fichero " + nombre_fichero);

        //Incluyo todos los datos en el fichero
        
        //Tamano de la lista de nodos
        fichero << nodos.size();

        //Bucle en el que metemos todos los nodos:

        std::map<std::string, std::vector<std::string>>::iterator it;
        std::vector<std::string> array_aux;

        it = nodos.begin();

        while (it != nodos.end())
        {
            fichero << it->first;
            array_aux=it->second;
            //Salto de linea
            fichero << "/n";
            //incluyo los vecinos en el fichero
            for (size_t i = 0; i < array_aux.size(); i++)
            {
                fichero << array_aux[i];
            }
            //Salto de linea
            fichero << "/n";
        }
        //cierro el fichero;
        fichero.close();
    }
    void Grafo::Crear_arista_no_dirigida(const std::string& s1, const std::string& s2)
    {

        //Establecemos una relación de s1 a s2, pero no de s2 a s1
        //De modo que guardamos a s2 en la lista de vecinos de s1, pero no guardamos a s1 en la lista de vecinos de s2
        //Si ya tiene establecida la relacion no se esta no se crea

        std::map<std::string, std::vector<std::string>>::iterator it;
        std::string letra_aux;
        //Creo un array para operar con el
        std::vector<std::string> array_aux;
        bool nodo_en_array = false;


        //actualizamos s1
        it = nodos.find(s1);
        if (it == nodos.end())
            perror("El nodo no está en la lista");
        else {
            array_aux = it->second;

            //Compruebo que el nodo objetivo no este ya guardado en el array
            for (size_t i = 0; i < array_aux.size(); i++)
            {
                letra_aux = array_aux[i];
                if (letra_aux == s2) {
                    nodo_en_array = true;
                }
            }

            if (nodo_en_array == false)
                array_aux.push_back(s2);

            //Actualizo la lista
            it->second = array_aux;
        }

    }
    void Grafo::Borrar_arista_no_dirigida(const std::string& s1, const std::string& s2)
    {
        //Si ya tiene establecida la relacion no se esta no se crea

        //Se elimina la relacion de s1 a s2, es decir, elimnamos a s2 del array de vecinos de s1

        bool nodo_en_array = false;
        std::map<std::string, std::vector<std::string>>::iterator it;
        std::string letra_aux;
        //Creo un array para operar con el
        std::vector<std::string> array_aux;


        //elimino el nodo en el array de vecinos de s1
        it = nodos.find(s1);
        if (it == nodos.end())
            perror("El nodo no está en la lista");
        else {
            array_aux = it->second;

            //Compruebo que el nodo objetivo ya está guardado en el array
            for (size_t i = 0; i < array_aux.size(); i++)
            {
                letra_aux = array_aux[i];
                if (letra_aux == s2) {
                    nodo_en_array = true;
                }
            }

            //elimino el nodo de la lista
            if (nodo_en_array == true)
                array_aux.erase(std::remove(array_aux.begin(), array_aux.end(), s2), array_aux.end());

            //Actualizo la lista
            it->second = array_aux;
        }
    }
    void Grafo::Muestra_lista()
    {
        std::string nombre;
        std::vector<std::string>sucesores;
        std::map<std::string, std::vector<std::string>>::iterator it;
        //compruebo que no este vacia la lista
        if (nodos.empty() == false)
        {
            //elimino el nodo y me aseguro de que está en la lista
            it = nodos.begin();
            while (it != nodos.end())
            {
                nombre = it->first;
                std::cout <<"Nodo:" << nombre << std::endl;
                sucesores = it->second;
                std::cout <<"sucesores:" << std::endl;
                for (auto& iter : sucesores)
                {
                    std::cout << iter << " ";
                } //Para ver por terminal que el vector esta vacio
                std::cout << " " << std::endl;
                it++;
            }
        }
    }
    void Grafo::carga_grafo(const std::string& nombre_fichero)
    {
        std::ifstream fichero(nombre_fichero);
        if (!fichero)
            throw std::runtime_error("No se pudo abrir el fichero " + nombre_fichero);

        int num_nodos, num_sucesores;
        std::vector<std::string>sucesores;
        std::string nombre,letra;
        fichero>>num_nodos;
        
        for (int j = 0; j < num_nodos; ++j)
        {
            fichero >> nombre;
            fichero >> num_sucesores;
            
            for (int i = 0; i < num_sucesores; ++i)
            {
                fichero >> letra;
                sucesores.push_back(letra);
                //std::cout << letra;
            }
            crea_nodo(nombre, sucesores);// nodos[nombre]=sucesores;
            std::cout << "Nodo padre:"+nombre << std::endl;
            std::cout << "sucesores:" << std::endl;
            for (auto& it : sucesores) 
            { 
                std::cout << it<<" ";
            } //Para ver por terminal que el vector esta vacio
            std::cout << " " << std::endl;
            sucesores.clear();
        }
        //Cierro el fichero
        fichero.close();
    }

    std::vector<std::pair<std::string, Nodo_grafo>> Nodo_grafo::sucesores() const
    {
        auto vector_nombres = grafo.vecinos(nombre);
        std::vector<std::pair<std::string, Nodo_grafo>> hijos;
        for (const auto& x : vector_nombres)
            hijos.push_back({x, Nodo_grafo(x)});

        return hijos;
    }
}
