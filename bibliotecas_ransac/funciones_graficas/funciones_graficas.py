# -*- coding: utf-8 -*-
"""Funciones gráficas."""
import numpy as np


def puntos_corte_recta(rectangulo, *args):
    """Recibe un rectángulo y una recta en formato (A, B, C) o con los 3 parámetros individuales.

    Devuelve los puntos de corte de la recta con el rectángulo.
    """
    if len(args) == 1:
        A = args[0][0]
        B = args[0][1]
        C = args[0][2]
    elif len(args) == 3:
        A, B, C = args
    else:
        raise ValueError('Los parámetros de la recta no se ajustan al formato requerido.')

    inf_x = rectangulo[0]
    inf_y = rectangulo[1]
    sup_x = rectangulo[2]
    sup_y = rectangulo[3]
    if (np.abs(A) < np.sqrt(2)/2):  # Recta entre -45 y 45 grados
        x1 = inf_x
        y1 = -(A*x1 + C)/B
        x2 = sup_x
        y2 = -(A*x2 + C)/B
        cond_1 = y1 >= sup_y and y2 >= sup_y
        cond_2 = y1 <= inf_y and y2 <= inf_y
    else:  # Recta vertical
        y1 = inf_y
        x1 = -(B*y1 + C)/A
        y2 = sup_y
        x2 = -(B*y2 + C)/A
        cond_1 = x1 >= sup_x and x2 >= sup_x
        cond_2 = x1 <= inf_x and x2 <= inf_x

    if cond_1 or cond_2:
        raise ValueError('La recta no es representable dentro de los límites de la imagen.')

    if y1 < inf_y:
        y1 = inf_y
        x1 = -(B*y1 + C)/A
    elif y1 > sup_y:
        y1 = sup_y
        x1 = -(B*y1 + C)/A

    if y2 < inf_y:
        y2 = inf_y
        x2 = -(B*y2 + C)/A
    elif y2 > sup_y:
        y2 = sup_y
        x2 = -(B*y2 + C)/A

    if x1 < inf_x:
        x1 = inf_x
        y1 = -(A*x1 + C)/B
    elif x1 > sup_x:
        x1 = sup_x
        y1 = -(A*x1 + C)/B

    if x2 < inf_x:
        x2 = inf_x
        y2 = -(A*x2 + C)/B
    elif x2 > sup_x:
        x2 = sup_x
        y2 = -(A*x2 + C)/B

    return (x1, y1), (x2, y2)


if __name__ == '__main__':
    print(puntos_corte_recta([0, 0, 100, 100], 1, 0, -1))
    print(puntos_corte_recta([0, 0, 100, 100], (1, 0, -1)))
    print(puntos_corte_recta([0, 0, 100, 100], [1, 0, -1]))
