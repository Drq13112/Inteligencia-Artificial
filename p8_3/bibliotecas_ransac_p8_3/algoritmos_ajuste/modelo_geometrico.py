# -*- coding: utf-8 -*-
"""Clase base de la que heredan los modelos geometricos: rectas, circunferencias, planos, etc."""
import numpy as np
from copy import deepcopy



class ModeloGeometrico:
    """Clase base de un modelo geométrico.

    Definido por una tupla de parámetros y su dimensión, el número de puntos necesarios para
    definir unívocamente el modelo.
    Se elige una tupla para los parámetros por su inmutabilidad.
    """

    _dimension = None

    @classmethod
    def dimension(cls):
        """Devuelve el atributo dimensión."""
        return cls._dimension

    def __init__(self, num_parametros):
        self._parametros = tuple([None]*num_parametros)

    def __copy__(self):
        """Sobrecarga de la función copy()."""
        clase = self.__class__
        nueva_instancia = clase.__new__(clase)
        nueva_instancia.__dict__.update(self.__dict__)
        nueva_instancia._parametros = deepcopy(self._parametros)
        return nueva_instancia

    def calcula(self, puntos):
        """Virtual, calcula el modelo a partir de un vector de puntos de tamaño _dimension."""
        raise NotImplementedError('Debes definir el método calcula()')

    def ajusta(self, estimador, puntos, *args):
        """Realiza un ajuste con el estimador pasado como parámetro y una nube de puntos.

        *args se utiliza para parámetros adicionales necesarios para el estimador
        """
        self._parametros = estimador(puntos, *args)

    def error(self, punto):
        """Virtual, calcula el "error", con signo, entre punto y el modelo dado por _parametros."""
        raise NotImplementedError('Debes definir el método error()')

    @property
    def parametros(self):
        """Tupla con los parámetros."""
        return self._parametros


def num_inliers(modelo_geometrico, datos, tolerancia=1.):
    """Devuelve el número de datos dentro de una banda tolerancia de error."""
    num_inliers = 0
    for dato in datos:
        if np.abs(modelo_geometrico.error(dato)) < tolerancia:
            num_inliers += 1
    return num_inliers


def inliers_outliers(modelo_geometrico, datos, tolerancias=(1., 1.)):
    """Devuelve una tupla formada por los inliers y los outliers.

    Existen tolerancias diferenciadas para filtrar outliers cercanos que interfieran
    en la detección de otras figuras geométricas.
    """
    tol_inliers = tolerancias[0]
    tol_outliers = tolerancias[1]
    if tol_inliers > tol_outliers:
        raise ValueError('La tolerancia para los inliers debe ser inferior que para los outliers.')
    inliers = []
    outliers = []

    for x in datos:
        error = np.abs(modelo_geometrico.error(x))
        if error < tol_inliers:
            inliers.append(x)
        elif error >= tol_outliers:
            outliers.append(x)

    return np.array(inliers), np.array(outliers)


def errores(modelo_geometrico, datos, tolerancia=1):
    """Devuelve el vector de errores en valor absoluto."""
    errores = np.array([modelo_geometrico.error(x) for x in datos])
    return errores


def errores_abs(modelo_geometrico, datos, tolerancia=1):
    """Devuelve el vector de errores en valor absoluto."""
    errores = np.abs(np.array([modelo_geometrico.error(x) for x in datos]))
    return errores


def errores_cuadrado(modelo_geometrico, datos, tolerancia=1):
    """Devuelve el vector de errores en valor absoluto."""
    errores = np.array([modelo_geometrico.error(x)**2 for x in datos])
    return errores


if __name__ == '__main__':
    modelo = ModeloGeometrico(3)
    print(modelo.parametros)
    print(ModeloGeometrico.dimension())
