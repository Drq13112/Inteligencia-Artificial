# -*- coding: utf-8 -*-
"""Fichero principal de la practica csp_reinas.

Permite la ejecución desde línea de comandos.
"""
from controlador import controlador


def main():
    """Función main()."""
    #controlador.run_reinas(15)
    
    #CANADA
    provincias = ['AB', 'BC', 'MB', 'NB', 'NL', 'NS', 'NT', 'NU', 'ON', 'PE', 'QC', 'SK', 'YT']
    
    vecindades = [('AB', 'BC'), ('AB', 'NT'), ('AB', 'SK'), ('BC', 'NT'), ('BC', 'YT'), ('MB', 'NU'),
     ('MB', 'ON'), ('MB', 'SK'), ('NB', 'NS'), ('NB', 'QC'), ('NL', 'QC'), ('NT', 'NU'),
     ('NT', 'SK'), ('NT', 'YT'), ('ON', 'QC')]
    colores=4
    controlador.run_coloreado_grafos(provincias,vecindades,colores)
    
    print("CANADA MODIFICADO--------------------")
    print()
    #CANADA modificado y reduciendo a 3 los colores disponibles para forzar el fallo.
    #Si se añade alguna unión máS en las provincias cirticas como MB, JP o AB el problema se vuelve
    #irresoluble para 3 colores
    provincias = ['AB', 'BC', 'MB', 'NB', 'NL', 'NS', 'NT', 'NU', 'ON', 'PE', 'QC', 'SK', 'YT','JP']
    
    vecindades = [('AB', 'BC'), ('AB', 'NT'), ('AB', 'SK'), ('BC', 'NT'), ('BC', 'YT'), ('MB', 'NU'),
     ('MB', 'ON'), ('MB', 'SK'), ('NB', 'NS'), ('NB', 'QC'), ('NL', 'QC'), ('NT', 'NU'),('NL', 'JP'),
     ('NT', 'SK'), ('NT', 'YT'), ('ON', 'QC'), ('JP', 'QC'), ('ON', 'PE'), ('NL', 'SK'),('JP', 'AB'),
     ('AB', 'JP'),('JP', 'PE'),('AB', 'QC'),('NT', 'QC'),('NT', 'NS'),('AB', 'MB'),('JP', 'NL')]
    """,('JP', 'NT')]"""
     
    colores=3
    controlador.run_coloreado_grafos(provincias,vecindades,colores)
    

if __name__ == '__main__':
    main()
