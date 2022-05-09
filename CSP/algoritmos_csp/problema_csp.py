# -*- coding: utf-8 -*-
"""
Módulo con la clase base de un problema CSP.

@author: migtr
"""


class ProblemaCSP:
    """Clase base de un problema CSP.

    _num_variables                   Número de variables del problema
    _dominio                         Dominio de las variables, lista de listas

    """

    def __init__(self, num_variables):
        # Mucho cuidado con = [[]]*num_variables -> mal: crea copias referencia
        self._dominio = [[] for _ in range(num_variables)]
        # self._dominio = {clave: None for clave in range(num_variables)}
        self._num_variables = num_variables

    @property
    def size(self):
        """Accede al número de variables del problema."""
        return self._num_variables

    @property
    def dominio(self):
        """Accede a la matriz dominio."""
        return self._dominio

    def _inicializa_dominio(self):
        """Función 'virtual' que inicializa el dominio."""
        raise NotImplementedError('Debes definir el método inicializa_dominio()')

    def consistente(self, var_1, val_1, var_2, val_2):
        """Función 'virtual' que determina si dos asignaciones son consistentes."""
        raise NotImplementedError('Debes definir el método consistente()')

    def relacionadas(self, var_1, var_2):
        """Función virtual que determina si dos variables están relacionadas."""
        raise NotImplementedError('Debes definir el método relacionadas()')

    # Función que permite depurar fallos.
    def solucion_consistente(self, solucion):
        """Determina si una solución es consistente.

        Una solucion, quizás parcial, es una lista formada por parejas (variable, valor).
        """
        for i, x in enumerate(solucion):
            for j in range(i+1, len(solucion)):
                y = solucion[j]
                if x[0] == y[0]:
                    # print('Variables repetidas')
                    return False
                if self.relacionadas(x[0], y[0]):
                    if not self.consistente(x[0], x[1], y[0], y[1]):
                        # print('Valores no consistentes')
                        return False
        return True


if __name__ == '__main__':
    pass
