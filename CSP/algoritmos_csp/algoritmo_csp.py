# -*- coding: utf-8 -*-
"""
Módulo con la clase base de un algoritmo CSP.

@author: migtr
"""
import numpy as np
import random
import copy


class AlgoritmoCSP:
    """Clase base de un algoritmo CSP."""

    def __init__(self, problema, metodo_seleccion):
        """
        Recibe un problema CSP y el método de selección de variables a utilizar.

        _problema                        Instancia del problema de tamaño tam a resolver
        _variables_sin_etiquetar         Lista [0, tam-1] con las variables
        _dominio                         Dominio de las tam variables, copia profunda de la recibida
                                         del problema
        _relacionadas                    Matriz tam*tam con 1's en las posiciones de variables
                                         relacionadas
        _consistente                     Referencia a la función consistente del problema, que
                                         determina si dos asignaciones son compatibles
        _seleccion                       Función que determina el orden de selección de variables
        _solucion                        Lista de tuplas con las asignaciones (variable, valor)
        _nodos_expandidos                Atributo con fines estadísticos para medir el número de
                                         nodos expandidos en un algoritmo

        Parameters
        ----------
        problema : class ProblemaCSP
            Véase implementación de la clase base
        metodo_seleccion : str
            Cadena que determina el método de selección de la variable, lo que determina el orden
            de visita.

        Raises
        ------
        KeyError
            Si el método de selección de variables no está implementado.

        Returns
        -------
        None.

        """
        self._problema = problema
        self._variables_sin_etiquetar = list(range(problema.size))
        self._dominio = copy.deepcopy(problema.dominio)
        self._relacionadas = self._set_relacionadas()
        self._consistente = problema.consistente
        self._solucion = []
        self._nodos_expandidos = None

        seleccion_callbacks = {'aleatoria': self._aleatoria,
                               'ordinal': self._ordinal,
                               'mrv': self._mrv_seleccion,
                               'mdv': self._mdv}

        # self._seleccion es una función que puede ser alterada en función del método de selección
        # En los métodos estáticos, _seleccion() reordena las variables (y quizás dominios) al
        # inicio del algoritmo.
        # En los métodos dinámicos se selecciona un índice de variable según el algoritmo de
        # selección y se coloca la variable de ese índice al final de la lista de variables
        # sin etiquetar. Es decir, todos los algoritmos acaban seleccionado siempre
        # para expandir la última variable de la lista de no etiquetadas.
        # La motivación es la sencillez de usar el método pop() para una elemento al final de
        # una lista
        self._seleccion = lambda: self._variables_sin_etiquetar[-1]

        # Se invoca al método de selección
        try:
            seleccion_callbacks[metodo_seleccion]()
        except KeyError:
            error = f'El método de selección {metodo_seleccion} no está implementado.'
            error += 'Los métodos disponibles son: '
            for key in seleccion_callbacks:
                error += key + ' '
            raise KeyError(error)

    @property
    def solucion(self):
        """Devuelve solución parcial o total formada por una lista de parejas (variable, valor)."""
        return self._solucion

    @property
    def num_nodos(self):
        """Método para obtener resultados estadísticos."""
        return self._nodos_expandidos

    def __call__(self):
        """Función 'virtual' que implementa el algoritmo CSP específico."""
        raise NotImplementedError('Debes definir el método ejecutar()')

    def _asignacion(self, lista_asignaciones):
        """
        Actualiza la solución actual añadiendo la última asignación que aparece en la
        lista de asignaciones.
        Además, elimina esa asignación de la lista de asignaciones y la variable involucrada de la
        lista de variables sin etiquetar.

        Parameters
        ----------
        lista_asignaciones : list of tuples (variable, valor)
            Lista con las tuplas (variable, valor) expandidas pero aún no "procesadas".

        Returns
        -------
        None.

        """
        self._solucion.append(lista_asignaciones[-1])
        self._variables_sin_etiquetar.pop()
        lista_asignaciones.pop()

    def _backtracking(self, lista_asignaciones):
        """
        Implementa la "vuelta atrás" cuando al expandir una nueva variable, su dominio está vacío.
        Actualiza la solución actual eliminando todas las variables hasta encontrar aquella que
        coincide que la siguiente a procesar en la lista de asignaciones.
        Las variables eliminadas de la solución son incorporadas de nuevo a la lista de variables
        sin etiquetar.
        Parameters
        ----------
        lista_asignaciones : list of tuples (variable, valor)
            Lista con las tuplas (variable, valor) expandidas pero aún no "procesadas".

        Returns
        -------
        Lista con las variables eliminadas.

        """
        eliminar = True
        variables_eliminadas = []
        while eliminar:
            variable = self._solucion[-1][0]
            variables_eliminadas.append(variable)
            if variable == lista_asignaciones[-1][0]:
                eliminar = False
            self._variables_sin_etiquetar.append(variable)
            self._solucion.pop()
        return variables_eliminadas

    # =============================================================================
    # Metodos de selección de variables estaticos
    # =============================================================================

    def _ordinal(self):  # No se altera el orden de selección n-1, n, ...., 2, 1, 0
        pass

    # hacemos shuffle al orden 0, 1, 2 de las variables y también a los dominios
    def _aleatoria(self):
        random.shuffle(self._variables_sin_etiquetar)
        for var in self._variables_sin_etiquetar:
            random.shuffle(self._dominio[var])

    # =============================================================================
    # Metodos de selección dinámico
    # =============================================================================

    def _mrv_seleccion(self):
        """Redefine _seleccion a _mrv, que altera dinámicamente el orden de selección."""
        self._seleccion = self._mrv

    # Modifica self._seleccion al ser un método dinámico
    def _mrv(self):
        """Implementa la heurística de selección de variables MRV."""
        minimo = len(self._dominio[self._variables_sin_etiquetar[-1]])
        indice = len(self._variables_sin_etiquetar) - 1
        for i, var in enumerate(self._variables_sin_etiquetar):
            if len(self._dominio[var]) < minimo:
                indice = i
                minimo = len(self._dominio[var])

        # Colocamos la variable seleccionada al final del vector
        # para su fácil bloqueo o liberación
        self._variables_sin_etiquetar[indice], self._variables_sin_etiquetar[-1] = \
            self._variables_sin_etiquetar[-1], self._variables_sin_etiquetar[indice]
        return self._variables_sin_etiquetar[-1]

    def _mdv(self):
        raise ValueError('Método mdv no implementado.')

    def _set_relacionadas(self):
        """
        Crea una matriz de 0's y 1's tam*tam, donde tam es el número de variables del problema.
        Las posiciones con 1's corresponden a las variables que están relacionadas entre sí.

        Returns
        -------
        relacionadas : Numpy array de int's
            Las posiciones con 1's corresponden a las variables que están relacionadas entre sí.

        """
        relacionadas = np.zeros((self._problema.size, self._problema.size))
        for var_i in self._variables_sin_etiquetar:
            for var_j in self._variables_sin_etiquetar:
                if var_i != var_j and self._problema.relacionadas(var_i, var_j):
                    relacionadas[var_i, var_j] = 1
        return relacionadas


if __name__ == '__main__':
    pass
