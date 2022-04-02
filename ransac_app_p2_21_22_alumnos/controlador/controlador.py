# -*- coding: utf-8 -*-
"""Módulo controlador."""
import numpy as np

# Importaciones bibliotecas
import funciones_graficas as fun_graf
from soluciones_cerradas import recta_2_puntos

# Importaciones aplicación
from modelo.construye_datos import construye_datos
from modelo.procesamiento import procesamiento
from vista.visualizacion import visualiza_puntos
from vista.visualizacion import visualiza_figuras


def run():
    """Ejecución principal del programa."""
    # =============================================================================
    # Creamos una nube de puntos aleatoria con figuras geometricas
    # =============================================================================

    # Quitad la semilla para obtener diferentes datos
    # Mantenedla para depurar
    # datos = construye_datos(np.random.RandomState(4))
    datos = construye_datos()

    # =============================================================================
    # Visualizamos la nube de puntos de partida
    # =============================================================================

    puntos = datos['puntos']
    rectangulo_imagen = datos['imagen']['rectangulo']
    visualiza_puntos(rectangulo_imagen, puntos)

    # =============================================================================
    # Detectamos las figuras geométricas
    # =============================================================================

    resultados = procesamiento(puntos)

    # =============================================================================
    # Visualizamos los inliers
    # =============================================================================

    puntos_inliers = np.array([], dtype=float).reshape(0, 2)
    for inliers in resultados['inliers']:  # Es una lista con inliers de diferentes figuras
        puntos_inliers = np.vstack([inliers, puntos_inliers])

    visualiza_puntos(rectangulo_imagen, puntos_inliers)

    # =============================================================================
    # Visualizamos los outliers
    # =============================================================================

    visualiza_puntos(rectangulo_imagen, resultados['outliers'])

    # =============================================================================
    # Visualizamos las figuras
    # =============================================================================

    figuras = {'segmento': [], 'circunferencia': [], 'rectangulo': []}

    for recta in resultados['recta']:
        # Obtenemos dos puntos de la recta que son corte con los límites de la "imagen"
        p1, p2 = fun_graf.puntos_corte_recta(rectangulo_imagen, recta)
        figuras['segmento'].append((p1, p2))

    for circ in resultados['circunferencia']:
        figuras['circunferencia'].append(circ)

    for rect in resultados['rectangulo']:
        figuras['rectangulo'].append(rect)

    visualiza_figuras(rectangulo_imagen, figuras, puntos)


if __name__ == '__main__':
    run()
