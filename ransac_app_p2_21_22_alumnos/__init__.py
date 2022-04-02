# -*- coding: utf-8 -*-
"""Descripción de los ficheros __init__.py.

El archivo __init__.py es utilizado para inicializar paquetes de Python.
Imaginemos que tenemos un paquete de python llamado package, que además contiene un subpaquete
llamado subpackage. Imaginemos que se ve así:

package/
    __init__.py
    archivo1.py
    archivo2.py
    archivo3.py
    subpackage/
        __init__.py
        submodulo.py

En este caso, el archivo __init__.py le indica al intérprete de Python que el directorio package
contiene un módulo, y que debe tratarlo como tal
(es decir, hacer que sea posible importar los archivos como parte del módulo).
"""
