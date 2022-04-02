# -*- coding: utf-8 -*-
"""Se modela las rectas en formato implícito."""
import numpy as np

import modelo_geometrico as mod_geo
from soluciones_cerradas import recta_2_puntos


class ModeloRecta2d(mod_geo.ModeloGeometrico):
    """Ax + By + C = 0.

    param[0] -> A
    param[1] -> B
    param[2] -> C
    Por construcción de la clase, se garantiza que A^2+B^2 = 1
    ya que recta_2_puntos(puntos) es la única forma de actualizar los parámetros
    """

    _dimension = 2

    def __init__(self, *args):
        """Si pasamos una matriz 2x2 con dos puntos, calcula la ecuación de la recta."""
        mod_geo.ModeloGeometrico.__init__(self, 3)  # 3 parámetros son necesarios (A, B, C)
        if len(args) == 1:
            self.calcula(np.array(args[0]))
        elif len(args) > 1:
            raise ValueError('Número de argumentos incorrecto.')

    def calcula(self, puntos):
        """Invoca a la solución cerrada recta_2_puntos(puntos) que garantiza A^2+B^2 = 1."""
        self._parametros = recta_2_puntos(puntos)

    def error(self, punto):
        """Al ser A^2+B^2 = 1,  error(x) = Ax+By+C es con signo."""
        return self._parametros[0]*punto[0] + self._parametros[1]*punto[1] + self._parametros[2]


if __name__ == '__main__':
    recta = ModeloRecta2d()  # Ejemplo sin argumentos
    print(recta.parametros)
    recta.calcula(np.array([[0, 0], [1, 1]]))
    print(recta.parametros)
    error = recta.error((1, 0))
    print(error)

    recta = ModeloRecta2d(np.array([[0, 0], [1, 1]]))  # Ejemplo con argumentos
    print(recta.parametros)
    error = recta.error((1, 0))
    print(error)
