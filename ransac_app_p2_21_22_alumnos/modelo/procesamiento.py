# -*- coding: utf-8 -*-
"""Módulo de procesamiento de la imagen."""
import ransac
import modelo_recta2d as mod_rect
import modelo_circunferencia2d as mod_circ
import modelo_geometrico as mod_geom
import numpy as np


def paralelas(lista_rectas, tol=np.pi/180):
    """Devuelve una tupla formada por las dos rectas y el ángulo promedio en [-pi/2, pi/2]."""
    lista_paralelas = []
    for i, recta1 in enumerate(lista_rectas):
        for j in range(i+1, len(lista_rectas)):
            recta2 = lista_rectas[j]
            angulo = mod_rect.angulo_entre_rectas(recta1, recta2)
            if np.abs(angulo) < tol:
                angulo_paralelas = mod_rect.angulo_bisectriz(recta1, recta2)
                lista_paralelas.append((recta1, recta2, angulo_paralelas))
    return lista_paralelas


def perpendiculares(lista_paralelas, tol=np.pi/180):
    """Devuelve una tupla con las dos parejas de paralelas mutuamente perpendiculares."""
    lista_perpendiculares = []
    for i, paralelas1 in enumerate(lista_paralelas):
        for j in range(i+1, len(lista_paralelas)):
            paralelas2 = lista_paralelas[j]
            angulo1 = paralelas1[2]
            angulo2 = paralelas2[2]
            if np.abs(np.pi/2 - np.abs(angulo1 - angulo2)) < tol:
                lista_perpendiculares.append((paralelas1, paralelas2))
    return lista_perpendiculares


def procesamiento(puntos):
    TOL_NUM_INLIERS_RECTA = 80
    TOL_NUM_INLIERS_CIRCUNFERENCIA = 50
    TOL_RANSAC = 1.
    TOL_DISTANCIA_RECTAS = (1., 2.)
    TOL_DISTANCIA_CIRCUNFERENCIAS = (1., 1.)
    TOL_ANGULO = np.pi/180
    # =============================================================================
    #  Detección de las rectas
    # =============================================================================

    # TODO

    # =============================================================================
    #  Detección de paralelas y perpendiculares
    # =============================================================================
    
    # TODO
    
    # =============================================================================
    #  Detección de rectángulos
    # =============================================================================

    # TODO

    # # =============================================================================
    # #  Detección de la circunferencia
    # # =============================================================================
    
    # TODO

    # =============================================================================
    #  Devolvemos los resultados con un diccionario
    # =============================================================================

    # Borrar estas lineas con listas vacías
    lista_rectangulos = []
    lista_circunferencias = []
    lista_inliers = []
    outliers = []
    return {'rectangulo': lista_rectangulos,
            'circunferencia': [circ.parametros for circ in lista_circunferencias],
            'recta': [],
            'inliers': lista_inliers,
            'outliers': outliers}


if __name__ == '__main__':
    pass
