# -*- coding: utf-8 -*-
"""Módulo selección aleatoria."""
import numpy as np


class SeleccionAleatoria:
    """Clase que selecciona dimension items de una colección de vectores."""

    def __init__(self, datos, dimension):
        self._tam = len(datos)
        if self._tam <= dimension:
            raise ValueError('El numero de datos debe ser mayor la dimension del modelo.')
        self._dimension = dimension
        self._datos = datos
        self._indices = np.arange(len(datos), dtype=int)
        self._datos_seleccionados = np.zeros((dimension, self._datos.shape[1]))

    def __call__(self):
        """Sobrecarga para devolver los dimension vectores seleccionados."""
        for i in range(self._dimension):
            aleatorio = np.random.randint(i, self._tam)
            # El swap permite asegurarnos que no repetimos la selección
            self._indices[i], self._indices[aleatorio] = self._indices[aleatorio], self._indices[i]
            self._datos_seleccionados[i] = self._datos[self._indices[i]]
        return self._datos_seleccionados


if __name__ == '__main__':
    print('Testando Clase SeleccionAleatoria \n...')
    datos = np.array([[0, 1], [1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8], [8, 9]])

    dimension = 8
    selector = SeleccionAleatoria(datos, dimension)

    # Hacemos 100 selecciones de 8 entre 9 elementos
    # Si nos sale algún repetido en la primera columna set() lo eliminará y probará un fallo
    for i in range(0, 100):
        seleccion = selector()
        assert len(set(seleccion[:, 0])) == 8

    # Verificamos que salta una excepción si tam <= dimension
    try:
        print(SeleccionAleatoria(datos, len(datos)))
    except ValueError:
        pass
    else:
        assert False

    print('Clase SeleccionAleatoria ---> OK')
