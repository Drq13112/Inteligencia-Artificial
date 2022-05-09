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


def interseccion(recta1, recta2):
    """Devuelve la intersección de las dos rectas usando la regla de Cramer."""
    A1 = recta1.parametros[0]
    B1 = recta1.parametros[1]
    C1 = recta1.parametros[2]
    A2 = recta2.parametros[0]
    B2 = recta2.parametros[1]
    C2 = recta2.parametros[2]

    den = A1*B2 - A2*B1
    num_x = B1*C2 - B2*C1
    num_y = A2*C1 - A1*C2
    return num_x/den, num_y/den


def angulo_recta(recta):
    """Devuelve el ángulo en radianes en [-pi/2, pi/2]."""
    # np.arctan2 devuelve el ángulo en radianes en [-pi, pi]
    angulo = np.arctan2(recta.parametros[0], -recta.parametros[1])
    if angulo > np.pi/2:
        angulo -= np.pi
    elif angulo < -np.pi/2:
        angulo += np.pi
    return angulo


def angulo_entre_rectas(recta1, recta2):
    """Devuelve el ángulo [0, pi/2] entre dos rectas en radianes.
    Presupone A**2+B**2 = 1."""
    A1 = recta1.parametros[0]
    B1 = recta1.parametros[1]
    A2 = recta2.parametros[0]
    B2 = recta2.parametros[1]
    coseno = np.clip(A1*A2+B1*B2, -1, 1)  # Para evitar errores de redondeo
    angulo = np.arccos(coseno)  # Devuelve el ángulo en radianes en [0, pi]

    if angulo > np.pi/2:
        angulo = np.pi - angulo

    return angulo


def angulo_bisectriz(recta1, recta2):
    """Devuelve el ángulo en radianes en [-pi/2, pi/2].
    De las dos bisectrices se elige la de menor ángulo."""
    angulo_recta1 = angulo_recta(recta1)
    angulo_recta2 = angulo_recta(recta2)

    if abs(angulo_recta1-angulo_recta2) > np.pi/2:
        if angulo_recta1 < 0:
            angulo_recta1 += np.pi
        elif angulo_recta2 < 0:
            angulo_recta2 += np.pi
        else:
            assert False, 'No debería entrar aquí'
    angulo = (angulo_recta1+angulo_recta2)/2
    if angulo > np.pi/2:
        angulo -= np.pi
    return angulo


if __name__ == '__main__':
    recta = ModeloRecta2d()  # Ejemplo sin argumentos
    recta.calcula(np.array([[0, 0], [1, 1]]))
    assert np.allclose(recta.parametros, [0.7071067811, -0.7071067811, -0.0], atol=1.e-5), 'No ok'
    error = recta.error((1, 0))
    assert np.isclose(error, 0.7071067811865475, atol=1.e-5), 'No ok'

    recta = ModeloRecta2d(np.array([[1, 2], [2, 1]]))  # Ejemplo con argumentos
    assert np.allclose(recta.parametros, [-0.7071067, -0.7071067, 2.1213203], atol=1.e-5), 'No ok'
    error = recta.error((1, 0))
    assert np.isclose(error, 1.414213562373095, atol=1.e-5), 'No ok'

    recta = ModeloRecta2d(np.array([[0, 0], [0, 1]]))
    assert np.isclose(angulo_recta(recta), 90*np.pi/180, atol=1.e-5), 'No ok'

    recta = ModeloRecta2d(np.array([[0, 0], [1, 0]]))
    assert np.isclose(angulo_recta(recta), 0*np.pi/180, atol=1.e-5), 'No ok'

    recta = ModeloRecta2d(np.array([[0, 0], [1, 1]]))
    assert np.isclose(angulo_recta(recta), 45*np.pi/180, atol=1.e-5), 'No ok'

    recta = ModeloRecta2d(np.array([[0, 0], [-1, -1]]))
    assert np.isclose(angulo_recta(recta), 45*np.pi/180, atol=1.e-5), 'No ok'

    recta = ModeloRecta2d(np.array([[0, 0], [1, -1]]))
    assert np.isclose(angulo_recta(recta), -45*np.pi/180, atol=1.e-5), 'No ok'

    recta = ModeloRecta2d(np.array([[0, 0], [-1, 1]]))
    assert np.isclose(angulo_recta(recta), -45*np.pi/180, atol=1.e-5), 'No ok'

    recta1 = ModeloRecta2d(np.array([[0, 0], [1, 1]]))
    recta2 = ModeloRecta2d(np.array([[0, 0], [-1, -1]]))
    assert np.isclose(angulo_entre_rectas(recta1, recta2), 0, rtol=0, atol=1.e-5), 'No ok'

    recta1 = ModeloRecta2d(np.array([[0, 0], [1, 1]]))
    recta2 = ModeloRecta2d(np.array([[0, 0], [1, -1]]))
    assert np.isclose(angulo_entre_rectas(recta1, recta2), 90*np.pi/180, atol=1.e-5), 'No ok'

    recta1 = ModeloRecta2d(np.array([[0, 0], [1, 1]]))
    recta2 = ModeloRecta2d(np.array([[0, 0], [0, 1]]))
    assert np.isclose(angulo_entre_rectas(recta1, recta2), 45*np.pi/180, atol=1.e-5), 'No ok'

    recta1 = ModeloRecta2d(np.array([[0, 0], [1, 1]]))
    recta2 = ModeloRecta2d(np.array([[0, 0], [-1, 0]]))
    assert np.isclose(angulo_entre_rectas(recta1, recta2), 45*np.pi/180, atol=1.e-5), 'No ok'

    recta1 = ModeloRecta2d(np.array([[0, 0], [1, 1]]))
    recta2 = ModeloRecta2d(np.array([[0, 0], [0, 1]]))
    assert np.isclose(angulo_entre_rectas(recta1, recta2), 45*np.pi/180, atol=1.e-5), 'No ok'

    recta1 = ModeloRecta2d(np.array([[0, 0], [1, 1]]))
    recta2 = ModeloRecta2d(np.array([[0, 0], [0, -1]]))
    assert np.isclose(angulo_entre_rectas(recta1, recta2), 45*np.pi/180, atol=1.e-5), 'No ok'

    recta1 = ModeloRecta2d(np.array([[0, 0], [1, 1]]))
    recta2 = ModeloRecta2d(np.array([[0, 0], [-1, -1]]))
    assert np.isclose(angulo_bisectriz(recta1, recta2), 45*np.pi/180, atol=1.e-5), 'No ok'

    recta1 = ModeloRecta2d(np.array([[0, 0], [1, 1]]))
    recta2 = ModeloRecta2d(np.array([[1, 1], [2.00001, 1.99999]]))
    assert np.isclose(angulo_bisectriz(recta1, recta2), 45*np.pi/180, atol=1.e-5), 'No ok'

    recta1 = ModeloRecta2d(np.array([[0, 0], [1, 0]]))
    recta2 = ModeloRecta2d(np.array([[0, 0], [-1, 0]]))
    assert np.isclose(angulo_bisectriz(recta1, recta2), 0*np.pi/180, rtol=0, atol=1.e-5), 'No ok'

    recta1 = ModeloRecta2d(np.array([[0, 0], [0.000001, 0.99999]]))
    recta2 = ModeloRecta2d(np.array([[0, 0], [0.000001, -0.99999]]))
    assert np.isclose(angulo_bisectriz(recta1, recta2), 90*np.pi/180, atol=1.e-5), 'No ok'

    recta1 = ModeloRecta2d(np.array([[0, 0], [1, 0.0001]]))
    recta2 = ModeloRecta2d(np.array([[0, 0], [-1, 0.0001]]))
    assert np.isclose(angulo_bisectriz(recta1, recta2), 0*np.pi/180, rtol=0, atol=1.e-5), 'No ok'

    recta1 = ModeloRecta2d(np.array([[1, 1], [-1, -1]]))
    recta2 = ModeloRecta2d(np.array([[-1, 1], [1, -1]]))
    assert np.allclose(interseccion(recta1, recta2), [0, 0], atol=1.e-5), 'No ok'

    recta1 = ModeloRecta2d(np.array([[1, 1], [1, -1]]))
    recta2 = ModeloRecta2d(np.array([[0, -1], [1, -1]]))
    assert np.allclose(interseccion(recta1, recta2), [1, -1], atol=1.e-5), 'No ok'

    recta1 = ModeloRecta2d(np.array([[-1, -1], [0, 1]]))
    recta2 = ModeloRecta2d(np.array([[-1, -1], [2, 1]]))
    assert np.allclose(interseccion(recta1, recta2), [-1, -1], atol=1.e-5), 'No ok'
