# -*- coding: utf-8 -*-
"""Funciones de visualización."""

import matplotlib.pyplot as plt


def visualiza_puntos(rectangulo, puntos):
    """Visualiza usando scatter() una colección de puntos 2d en un rectángulo."""
    x1 = rectangulo[0]
    y1 = rectangulo[1]
    x2 = rectangulo[2]
    y2 = rectangulo[3]

    fig, ax = plt.subplots()
    plt.xlim(x1, x2)
    plt.ylim(y1, y2)

    plt.scatter(puntos[:, 0], puntos[:, 1], s=0.1)
    ax.set_aspect(1)
    plt.show()


def visualiza_figuras(rectangulo, figuras, puntos):
    """Visualiza segmentos y circunferencias en un rectángulo.

    Las figuras se reciben mediante un diccionario:
    figuras['segmento'] es una lista de segmentos.
    figuras['circunferencia'] es una lista de circunferencias.
    """
    x1 = rectangulo[0]
    y1 = rectangulo[1]
    x2 = rectangulo[2]
    y2 = rectangulo[3]

    fig, ax = plt.subplots()
    plt.xlim(x1, x2)
    plt.ylim(y1, y2)

    plt.scatter(puntos[:, 0], puntos[:, 1], s=0.1)

    for segmento in figuras['segmento']:
        p1 = segmento[0]
        p2 = segmento[1]
        plt.plot([p1[0], p2[0]], [p1[1], p2[1]], 'g')

    for circ in figuras['circunferencia']:
        ax.add_artist(plt.Circle((circ[0], circ[1]), circ[2], color='r', fill=False))

    ax.set_aspect(1)
    plt.show()


if __name__ == '__main__':
    pass
