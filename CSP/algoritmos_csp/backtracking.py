# -*- coding: utf-8 -*-
"""
Módulo con la clase Backtracking de un algoritmo CSP.

@author: migtr, 2022
"""

from algoritmo_csp import AlgoritmoCSP


class Backtracking(AlgoritmoCSP):
    """Implementa un algoritmo CSP mediante Backtracking."""

    def __init__(self, problema, metodo_seleccion):
        AlgoritmoCSP.__init__(self, problema, metodo_seleccion)

    def __call__(self):
        """
        Ejecución del algoritmo Backtracking.

        Returns
        -------
        exito : bool
            True si se encontró una solución, False en caso contrario.

        """
        exito = None
        self._nodos_expandidos = 0

        lista_asignaciones = []

        while exito is None:
            self._nodos_expandidos += 1
            variable = self._seleccion()

            lista_asignaciones_variable = self._expandir(variable)
            lista_asignaciones.extend(lista_asignaciones_variable)

            if not lista_asignaciones:
                self._solucion = []
                exito = False
            else:
                if not lista_asignaciones_variable:
                    self._backtracking(lista_asignaciones)
                self._asignacion(lista_asignaciones)
                if not self._variables_sin_etiquetar:
                    exito = True

        return exito

    def _expandir(self, variable):
        """
        Crea la lista de tuplas (variable, valor del dominio) que son consistentes con la solución
        parcial obtenida hasta ese momento.

        Parameters
        ----------
        variable : int
            Variable del problema CSP.

        Returns
        -------
        lista_asignaciones_variable : list of tuples (int, tipo del dominio)
            Lista con las tuplas [(variable, valor_1), ..., (variable, valor_n)] donde valor_i
            son valores del dominio consistentes con la solución parcial actual.

        """
        lista_asignaciones_variable = []
        for valor in self._dominio[variable]:
            consistente = True
            for var, val in self._solucion:
                if self._relacionadas[variable, var]:
                    if not self._consistente(variable, valor, var, val):
                        consistente = False
                        break

            if consistente:
                lista_asignaciones_variable.append((variable, valor))

        return lista_asignaciones_variable


if __name__ == '__main__':
    pass
