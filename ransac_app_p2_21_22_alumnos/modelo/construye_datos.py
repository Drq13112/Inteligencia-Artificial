# -*- coding: utf-8 -*-
"""Construye una imagen aleatoria formada por puntos, 3 segmentos y una circunferencia."""
import numpy as np
import matplotlib.pyplot as plt
import figuras_aleatorias as fig_aleat


def construye_datos(rng=np.random.RandomState()):
    """Construye una imagen aleatoria formada por puntos varios segmentos
    y una circunferencia inscrita en un rectángulo.

    rectangulo_imagen = (x1, y1, x2, y2) -> Vértices sup izq e inf der.

    Devuelve la información a través de un diccionario.
            'imagen': nube_rectangulo_rand -> Diccionario formado por un rectangulo y
                                     puntos aleatorios que no pertenecen a las figuras
            'segmento': lista_segmentos  -> 
            'circunferencia': [circunferencia_rand]  -> lista con la única circunferencia generada
            'puntos': puntos -> lista con todos los puntos aleatorios desordenada
    """
    RATIO_INLIERS_RECTAS = 0.08
    RATIO_INLIERS_CIRCUNFERENCIAS = 0.05
    RATIO_RADIO = 0.3
    DES_STD = 0.75
    NUM_PUNTOS = 2000
    LADO_MAYOR_INF = 500
    LADO_MAYOR_SUP = 550
    LADO_MENOR_INF = 350
    LADO_MENOR_SUP = 400
    NUM_SEGMENTOS_MIN = 4
    NUM_SEGMENTOS_MAX = 6
    LONGITUD_MINIMA_SEGMENTOS = 375.
    # Rectángulo imagen HD
    x1 = 0.0
    y1 = 0.0
    x2 = 1280.
    y2 = 720.

    if x1 >= x2 or y1 >= y2:
        raise ValueError('No es un rectángulo válido.')

    rectangulo_imagen = (x1, y1, x2, y2)

    num_puntos = NUM_PUNTOS
    des_std = DES_STD

    lado_mayor = rng.uniform(LADO_MAYOR_INF, LADO_MAYOR_SUP)
    lado_menor = rng.uniform(LADO_MENOR_INF, LADO_MENOR_SUP)

    r_x1 = -lado_mayor/2
    r_x2 = lado_mayor/2
    r_y1 = -lado_menor/2
    r_y2 = lado_menor/2
    rectangulo_centrado_origen = (r_x1, r_y1, r_x2, r_y2)

    # TODO

    return {'imagen': {'rectangulo': rectangulo_imagen, 'puntos': []},
            'segmento': [],
            'circunferencia': [],
            'puntos': []}


def test_contruye_datos():
    datos = construye_datos()
    puntos = datos['puntos']
    rectangulo_imagen = datos['imagen']['rectangulo_imagen']

    x1 = rectangulo_imagen[0]
    y1 = rectangulo_imagen[1]
    x2 = rectangulo_imagen[2]
    y2 = rectangulo_imagen[3]

    fig, ax = plt.subplots()
    plt.xlim(x1, x2)
    plt.ylim(y1, y2)

    plt.scatter(puntos[:, 0], puntos[:, 1], s=0.1)
    ax.set_aspect(1)
    plt.show()


if __name__ == '__main__':
    # test_contruye_datos()
    pass
