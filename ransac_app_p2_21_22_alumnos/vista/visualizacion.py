# -*- coding: utf-8 -*-
"""Funciones de visualización."""

import matplotlib.pyplot as plt


def visualiza_puntos(rectangulo_imagen, puntos):
    """Visualiza usando scatter() una colección de puntos 2d en un rectángulo."""
    x1 = rectangulo_imagen[0]
    y1 = rectangulo_imagen[1]
    x2 = rectangulo_imagen[2]
    y2 = rectangulo_imagen[3]

    fig, ax = plt.subplots()
    plt.xlim(x1, x2)
    plt.ylim(y1, y2)

    if puntos:
        plt.scatter(puntos[:, 0], puntos[:, 1], s=0.1)
    ax.set_aspect(1)
    plt.show()


def visualiza_figuras(rectangulo_imagen, figuras, puntos):
    """Visualiza segmentos y circunferencias en un rectángulo.

    Las figuras se reciben mediante un diccionario:
    figuras['segmento'] es una lista de segmentos.
    figuras['circunferencia'] es una lista de circunferencias.
    figuras['rectangulo'] es una lista con los vértices ordenados de un rectángulo.
    """
    x1 = rectangulo_imagen[0]
    y1 = rectangulo_imagen[1]
    x2 = rectangulo_imagen[2]
    y2 = rectangulo_imagen[3]

    fig, ax = plt.subplots()
    plt.xlim(x1, x2)
    plt.ylim(y1, y2)

    if puntos:
        plt.scatter(puntos[:, 0], puntos[:, 1], s=0.1)

    for segmento in figuras['segmento']:
        p1 = segmento[0]
        p2 = segmento[1]
        plt.plot([p1[0], p2[0]], [p1[1], p2[1]], 'g')

    for circ in figuras['circunferencia']:
        ax.add_artist(plt.Circle((circ[0], circ[1]), circ[2], color='r', fill=False))

    for rect in figuras['rectangulo']:
        p1 = rect[0]
        p2 = rect[1]
        p3 = rect[2]
        p4 = rect[3]
        plt.plot([p1[0], p2[0]], [p1[1], p2[1]], 'g')
        plt.plot([p2[0], p3[0]], [p2[1], p3[1]], 'g')
        plt.plot([p3[0], p4[0]], [p3[1], p4[1]], 'g')
        plt.plot([p4[0], p1[0]], [p4[1], p1[1]], 'g')

    ax.set_aspect(1)
    plt.show()


if __name__ == '__main__':
    pass
