# -*- coding: utf-8 -*-
"""
Módulo con la clase LookAheadFC de un algoritmo CSP.

@author: migtr
"""

from algoritmo_csp import AlgoritmoCSP


class LookAheadFC(AlgoritmoCSP):
    """Implementa un algoritmo CSP mediante Forward Checking.
    _lista_exclusiones_dominio     Esta lista de listas almacena para cada variable ya asignada
                                   las posibles asignaciones de variables por asignar que fueron
                                   eliminadas como consecuencia de su asignación actual
    """

    def __init__(self, problema, met_sel):
        AlgoritmoCSP.__init__(self, problema, met_sel)
        # Mucho cuidado con = [[]]*problema.size -> mal: crea copias referencia
        self._lista_exclusiones_dominio = [[] for _ in range(problema.size)]

    def __call__(self):
        """
        Ejecución del algoritmo Fordward Checking.

        Returns
        -------
        exito : bool
            True si se encontró una solución, False en caso contrario.

        """

        exito = False
        self._nodos_expandidos = 0
        bloqueo = False
        lista_asignaciones = []
        while not exito:
            self._nodos_expandidos += 1
            if not bloqueo:
                variable = self._seleccion()
                # No hace falta comprobar la consistencia de las asignaciones, pues el algoritmo
                # garantiza que los valores que quedan en el dominio son consistentes con las
                # asignaciones anteriores
                for valor in self._dominio[variable]:
                    lista_asignaciones.append((variable, valor))
            else:
                if not lista_asignaciones:  # Está vacía
                    self._solucion = []
                    break
                else:
                    variables_eliminadas = self._backtracking(lista_asignaciones)
                    for var in variables_eliminadas:
                        self._restaura_dominio(var)

            self._asignacion(lista_asignaciones)
            if not self._variables_sin_etiquetar:  # Está vacía
                exito = True
            else:
                bloqueo = self._actualiza_dominio(self._solucion[-1])

        return exito

    def _restaura_dominio(self, variable):
        """
        Restaura el dominio

        Parameters
        ----------
        variable : TYPE
            DESCRIPTION.

        Returns
        -------
        None.

        """
        for asignacion in self._lista_exclusiones_dominio[variable]:
            self._dominio[asignacion[0]].append(asignacion[1])

        self._lista_exclusiones_dominio[variable].clear()

    def _actualiza_dominio(self, asignacion):
        """
        Dada una nueva asignación en la solución parcial, se realiza consistencia de arco entre
        la variable asignada y el resto de variables aún no asignadas.

        Parameters
        ----------
        asignacion : tupla : (int, tipo del dominio)
            Tupla con una asignación: (variable, valor).

        Returns
        -------
        bool
            DESCRIPTION.

        """
        var_asig = asignacion[0]
        val_asig = asignacion[1]
        for var in self._variables_sin_etiquetar:
            if self._relacionadas[var_asig, var]:
                if self._revisar_ac_fc(var, var_asig, val_asig):
                    if not self._dominio[var]:  # Hemos detectado un dominio vacio
                        return True
        return False

    def _revisar_ac_fc(self, var, var_asig, val_asig):
        """
        Comprueba la consistencia de arco direccional entre la asignación (var_asig, val_asig) y
        los valores del dominio de la variable var.
        Si no hay consistencia para una asignación (var,val) se elimina del dominio y se añade
        la tupla (var,val) a la lista de exclusiones asociada a la variable var_asig:
        _lista_exclusiones_dominio[var_asig]

        Parameters
        ----------
        var : int
            Variable con la que se comprueba la consistencia de arco de su dominio.
        var_asig : int
            Variable asignada.
        val_asig : tipo del dominio
            Valor de la variable asignada.

        Returns
        -------
        cambio : bool
            True si se ha alterado el dominio de la variable var.

        """
        cambio = False
        # Se usa un bucle while para recorrer el dominio porque se altera dinámicamente en su
        # interior
        i = 0
        while i < len(self._dominio[var]):
            val = self._dominio[var][i]
            if not self._consistente(var, val, var_asig, val_asig):
                # Borramos la asignación del dominio
                # Tal y como está programado, "desordenamos" el dominio
                self._dominio[var][i] = self._dominio[var][-1]
                self._dominio[var].pop()
                # La guardamos por si hay que restaurarla
                self._lista_exclusiones_dominio[var_asig].append((var, val))
                i -= 1
                cambio = True
            i += 1
        return cambio


if __name__ == '__main__':
    pass
