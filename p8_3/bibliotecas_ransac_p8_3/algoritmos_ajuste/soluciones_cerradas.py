# -*- coding: utf-8 -*-
"""Soluciones cerradas para rectas y circunferencias."""
import numpy as np


def recta_2_puntos(puntos, tol=1.0e-10):
    """Solución cerrada a partir de 2 puntos.

    La tolerancia se usa para filtrar situaciones con puntos excesivamente cercanos.
    """
    if puntos.shape != (2, 2):
        raise ValueError('El número de puntos 2d para obtener la ecuación de la recta debe ser 2.')

    incr_x = puntos[1][0] - puntos[0][0]
    incr_y = puntos[1][1] - puntos[0][1]

    modulo = np.sqrt(incr_x**2+incr_y**2)
    if modulo < tol:
        raise ValueError('Puntos muy cercanos para calcular la recta.')

    A = incr_y/modulo
    B = -incr_x/modulo
    C = -(A*puntos[0][0]+B*puntos[0][1])

    return A, B, C


def circunferencia_3_puntos(puntos, tol=1.0e-10):
    """Solución cerrada a partir de 3 puntos.

    La tolerancia se usa para filtrar situaciones con puntos excesivamente cercanos.
    """
    if len(puntos) != 3:
        raise ValueError('El número de puntos para determinar la ecuación debe ser 3.')

    b = puntos[0]
    c = puntos[1]
    d = puntos[2]

    temp = c[0]**2 + c[1]**2
    bc = (b[0]**2 + b[1]**2 - temp)/2
    cd = (temp - d[0]**2 - d[1]**2)/2
    det = (b[0] - c[0])*(c[1] - d[1]) - (c[0] - d[0])*(b[1] - c[1])

    if abs(det) < tol:
        raise ValueError('Puntos muy cercanos entre sí en la circunferencia.')

    cx = (bc*(c[1] - d[1]) - cd*(b[1] - c[1])) / det
    cy = ((b[0] - c[0]) * cd - (c[0] - d[0]) * bc) / det
    radio = ((cx - b[0])**2 + (cy - b[1])**2)**.5

    return cx, cy, radio


if __name__ == '__main__':
    tol = 1e-10

    # =============================================================================
    # Testando recta
    # =============================================================================
    print('Testando recta_2_puntos() \n...')
    A, B, C = recta_2_puntos(np.array([[0, 0], [1, 1]]))
    if A < 0:
        assert np.isclose(A, -np.sqrt(2)/2, atol=tol)
        assert np.isclose(B, np.sqrt(2)/2, atol=tol)
        assert np.isclose(C, 0, atol=tol)
    else:
        assert np.isclose(A, np.sqrt(2)/2, atol=tol)
        assert np.isclose(B, -np.sqrt(2)/2, atol=tol)
        assert np.isclose(C, 0, atol=tol)

    A, B, C = recta_2_puntos(np.array([[1, 1], [5, 4]]))
    if A < 0:
        assert np.isclose(A, -0.6, atol=tol)
        assert np.isclose(B, 0.8, atol=tol)
        assert np.isclose(C, -0.2, atol=tol)
    else:
        assert np.isclose(A, 0.6, atol=tol)
        assert np.isclose(B, -0.8, atol=tol)
        assert np.isclose(C, +0.2, atol=tol)
    print('recta_2_puntos() ---> OK')

    # =============================================================================
    # Testando circunferencia
    # =============================================================================
    print('\nTestando circunferencia_3_puntos() \n...')
    cx, cy, radio = circunferencia_3_puntos([[0, 2], [2, 0], [2, 2]], tol)
    assert np.isclose(cx, 1.0, atol=tol)
    assert np.isclose(cy, 1.0, atol=tol)
    assert np.isclose(radio, np.sqrt(2), atol=tol)
    print('circunferencia_3_puntos() ---> OK')
