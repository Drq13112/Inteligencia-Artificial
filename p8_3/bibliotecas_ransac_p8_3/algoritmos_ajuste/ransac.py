# -*- coding: utf-8 -*-
"""Módulo que implementa el algoritmo RANSAC."""
import numpy as np
from copy import copy

from seleccion_aleatoria import SeleccionAleatoria


class Ransac:
    """Clase que implementa el algoritmo RANSAC."""

    def __init__(self, Modelo, tolerancia=1., probabilidad_fallo=0.01,
                 ratio_inliers=None, min_iter=100, max_iter=1e4):
        self.set_tolerancia(tolerancia)
        self.set_probabilidad_fallo(probabilidad_fallo)
        self.set_ratio_inliers(ratio_inliers)
        self.set_min_iter(min_iter)
        self.set_max_iter(max_iter)
        self._Modelo = Modelo

    def __call__(self, datos):
        """Sobrecarga para invocar a RANSAC como una función."""
        max_iter = self._calcula_max_iteraciones(self._ratio_inliers)
        selector = SeleccionAleatoria(datos, self._Modelo.dimension())
        mejor_modelo = None
        mejor_puntuacion = 0.0
        mejor_num_inliers = 0
        inlier_ratio = 0.0

        num_datos = len(datos)

        contador = 0
        modelo = self._Modelo()
        while contador < max_iter:
            datos_seleccionados = selector()

            # Estima el modelo actual a partir de los datos seleccionados.
            # Aquí podrían filtrarse los datos seleccionados, por ejempplo,
            # puntos que no estén entre sí en un rango de distancias.
            # Se puede gestionar con una excepción

            try:
                modelo.calcula(datos_seleccionados)
            except ValueError:  # Con esos datos el modelo está mal condicionado
                continue
            else:
                # Calcula la puntuacion y el vector de indices de los inliers
                # num_inliers = mod_geo.num_inliers(self._modelo, datos, self._tolerancia)
                # puntuacion = num_inliers
                puntuacion, num_inliers = msac(modelo, datos, self._tolerancia)

                if puntuacion > mejor_puntuacion:
                    mejor_modelo = copy(modelo)  # Necesario usar copy()
                    mejor_puntuacion = puntuacion
                    mejor_num_inliers = num_inliers
                    # Actualiza max_iter
                    inlier_ratio = num_inliers/num_datos
                    max_iter = min((self._calcula_max_iteraciones(inlier_ratio), max_iter))
            contador += 1

        # Estas dos líneas se deberían comentar. Son para hacernos una idea de cuantas iteraciones
        # han sido necesarias y cuantos inliers se han obtenido
        # Podrían enviarse a la función "llamante" vía return
        print('Iteraciones realizadas:{:d}'.format(int(max_iter)))
        print('Porcentaje de inliers:{:.2f}'.format(100*mejor_num_inliers/num_datos))

        # Podemos devolver una estructura de datos con más información
        return mejor_modelo

    def set_tolerancia(self, tolerancia):
        """Función que fija la tolerancia de la banda RANSAC."""
        if tolerancia <= 0:
            raise ValueError('El valor de la tolerancia debe ser positivo.')
        self._tolerancia = tolerancia

    def set_probabilidad_fallo(self, probabilidad_fallo):
        """Función que fija la probabilidad de que no escojamos dimension datos válidos."""
        if probabilidad_fallo <= 0 or probabilidad_fallo >= 1:
            raise ValueError('El valor es una probabilidad.')
        self._probabilidad_fallo = probabilidad_fallo

    def set_ratio_inliers(self, ratio_inliers):
        """Estimación inicial del porcentaje (tanto por uno) de inliers."""
        if ratio_inliers is not None and (ratio_inliers < 0 or ratio_inliers > 1):
            raise ValueError('El valor es un tanto por 1.')
        self._ratio_inliers = ratio_inliers

    def set_min_iter(self, min_iter):
        """Mínimo de iteraciones del algoritmo."""
        if min_iter <= 0:
            raise ValueError('El valor de iteraciones minimas debe ser positivo.')
        self._min_iter = min_iter

    def set_max_iter(self, max_iter):
        """Máximo de iteraciones del algoritmo."""
        if max_iter <= self._min_iter:
            raise ValueError('''El valor de iteraciones maximas debe ser superior
                             al de iteraciones minimas''')
        self._max_iter = max_iter

    def _calcula_max_iteraciones(self, porcentaje_inliers=None):
        """Función que permite calcular el número máximo de iteraciones dinámicamente."""
        if porcentaje_inliers is None:  # No sabemos nada del porcentage de inliers
            num_iteraciones = self._max_iter
        elif porcentaje_inliers > 0.99:  # Practicamente todos los puntos son inliers
            num_iteraciones = self._min_iter
        else:
            # max_iter = log(epsilon)/log(1-q)  y q =~ (num_inliers/num_datos)^dimendion
            num = np.log(self._probabilidad_fallo)
            den = np.log(1.0 - porcentaje_inliers**self._Modelo.dimension())
            num_iter = num/den
            num_iteraciones = max((self._min_iter, min(num_iter, self._max_iter)))
        return num_iteraciones


def msac(modelo, datos, tolerancia=1.):
    """Cálculo de puntuación para medir la calidad de una estimación.

    Se basa en valorar más aquellos puntos dentro de la banda de tolerancia con un error menor.
    A los que están fuera de la banda se los penaliza con el mismo valor.
    Devuelve una tupla: la puntuación y el número de inliers
    """
    valor = 0.
    num_inliers = 0
    for dato in datos:
        error = np.abs(modelo.error(dato))
        if error < tolerancia:
            valor += error
            num_inliers += 1
        else:
            valor += tolerancia
    return 1./valor, num_inliers


if __name__ == '__main__':
    pass
