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

    figuras = {'segmento': [], 'circunferencia': []}

    for recta in resultados['recta']:
        # Obtenemos dos puntos de la recta que son corte con los límites de la "imagen"
        p1, p2 = fun_graf.puntos_corte_recta(rectangulo_imagen, recta)
        figuras['segmento'].append((p1, p2))

    for circ in resultados['circunferencia']:
        figuras['circunferencia'].append(circ)

    visualiza_figuras(rectangulo_imagen, figuras, puntos)

    # =============================================================================
    # Comparamos resultados reales y estimados
    # =============================================================================

    # Datos rectas y circunferencia reales
    """

    print('PARÁMETROS REALES')
    print('Parámetros reales rectas')
    for i, segmento in enumerate(datos['segmento']):
        print('Recta {}'.format(i+1))
        p1 = segmento['p1']
        p2 = segmento['p2']
        param = recta_2_puntos(np.array([p1, p2]))
        print('{:.3f}, {:.3f}, {:.3f}'.format(param[0], param[1], param[2]))

    print('Parámetros reales circunferencia')
    for i, circ in enumerate(datos['circunferencia']):
        print('Circunferencia {}'.format(i+1))
        cx = circ['centro'][0]
        cy = circ['centro'][1]
        print('({:.3f}, {:.3f}), {:.3f}'.format(cx, cy, circ['radio']))

    # Datos rectas y circunferencia estimados
    print('\nPARÁMETROS ESTIMADOS')
    print('Parámetros estimados rectas')
    for param in resultados['recta']:
        print('{:.3f}, {:.3f}, {:.3f}'.format(param[0], param[1], param[2]))

    print('Parámetros estimados circunferencia')
    for param in resultados['circunferencia']:
        print('({:.3f}, {:.3f}), {:.3f}'.format(param[0], param[1], param[2]))

    """
if __name__ == '__main__':
    run()
