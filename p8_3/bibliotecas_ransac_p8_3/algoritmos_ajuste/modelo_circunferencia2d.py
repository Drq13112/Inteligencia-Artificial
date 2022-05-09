# -*- coding: utf-8 -*-
"""Se modela la circunferencia en formato (x-xc)^2 + (y-yc)^2 = R^2."""
import numpy as np

import modelo_geometrico as mod_geo
from soluciones_cerradas import circunferencia_3_puntos


class ModeloCircunferencia2d(mod_geo.ModeloGeometrico):
    """(x-xc)^2 + (y-yc)^2 = R^2.

    _parametros[0] -> xc
    _parametros[1] -> yc
    _parametros[2] -> R
    """

    _dimension = 3

    def __init__(self, *args):
        """Si pasamos una matriz 3x2 con tres puntos, calcula la ecuación de la circunferencia."""
        mod_geo.ModeloGeometrico.__init__(self, 3)
        if len(args) == 1:
            self.calcula(np.array(args[0]))
        elif len(args) > 1:
            raise ValueError('Número de argumentos incorrecto.')

    def calcula(self, puntos):
        """Invoca a la solución cerrada circunferencia_3_puntos(puntos)."""
        self._parametros = circunferencia_3_puntos(puntos)

    def error(self, punto):
        """Signo positivo para los puntos externos a la circunferencia."""
        dif_x = punto[0] - self._parametros[0]
        dif_y = punto[1] - self._parametros[1]
        return np.sqrt(dif_x**2+dif_y**2)-self._parametros[2]


if __name__ == '__main__':
    circ = ModeloCircunferencia2d()  # Ejemplo sin parámetros
    circ.calcula(np.array([[0, 2], [2, 0], [2, 2]]))
    assert np.allclose(circ.parametros, [1., 1., 1.4142], atol=1.e-5), 'No ok'
    error = circ.error((3, 3))
    assert np.isclose(error, 1.4142, atol=1.e-5), 'No ok'

    circ = ModeloCircunferencia2d([[0, 2], [2, 0], [2, 2]])  # Ejemplo con parámetros
    assert np.allclose(circ.parametros, [1., 1., 1.4142], atol=1.e-5), 'No ok'
    error = circ.error((3, 3))
    assert np.allclose(circ.parametros, [1., 1., 1.4142], atol=1.e-5), 'No ok'
