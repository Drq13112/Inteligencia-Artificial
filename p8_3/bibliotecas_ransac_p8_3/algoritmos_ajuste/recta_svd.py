"""Ajuste a una recta utilizando Descomposición en valores Singulares (SVD)."""
import numpy as np
import copy


def recta_svd(puntos):
    """Recibe una nube de puntos y devuelve los parámetros (A, B, C)."""
    num_puntos = puntos.shape[0]

    if num_puntos < 3:
        raise ValueError('Deben proporcionarse al menos tres puntos.')

    puntos = copy.deepcopy(puntos)
    #  Centro de gravedad
    c_g = np.sum(puntos, axis=0)/num_puntos

    # Trasladamos el origen al centro de gravedad
    puntos -= c_g

    u, s, v = np.linalg.svd(puntos, full_matrices=False)

    # La solución es el vector "fila" asociado al menor autovalor
    # numpy svd los ordena en orden descendiente
    A = v[1][0]
    B = v[1][1]
    C = -(A*c_g[0]+B*c_g[1])

    return A, B, C


if __name__ == '__main__':
    puntos = np.array([[1, 1], [2, 2], [3, 3], [4.01, 4.01]])
    parametros = recta_svd(puntos)
    print(parametros)
