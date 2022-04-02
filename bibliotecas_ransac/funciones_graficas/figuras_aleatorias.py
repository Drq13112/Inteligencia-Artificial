# -*- coding: utf-8 -*-
"""Módulo que crea figuras aleatorias."""
import numpy as np
    
def segmento2d_rand(p1, p2, num_puntos, des_std, tol=1., rng=np.random.RandomState()):
    """Crea un segmento aleatorio con num_puntos entre p1 y p2."""
    incr_x = p2[0] - p1[0]
    incr_y = p2[1] - p1[1]
    distancia = np.sqrt(incr_x*incr_x + incr_y*incr_y)

    if distancia < tol:
        raise ValueError('Los dos puntos están muy cercanos según tol = {}.'.format(tol))

    coseno = incr_y/distancia
    seno = -incr_x/distancia

    # Creación vectorizada de los puntos del segmento
    lambda_rnd = rng.uniform(0, 1, num_puntos)
    perpendicular_rnd = rng.normal(0., des_std, num_puntos)

    x = p1[0] + lambda_rnd*incr_x + perpendicular_rnd*coseno
    y = p1[1] + lambda_rnd*incr_y + perpendicular_rnd*seno

    puntos = np.array(list(zip(x, y)))
    return puntos


def circunferencia2d_rand(centro, radio, num_puntos, des_std, radio_minimo=1.,
                          rng=np.random.RandomState()):
    """Crea una circunferencia aleatoria con num_puntos de centro y radio dados."""
    if radio < radio_minimo:
        raise ValueError('El radio es muy pequeño según radio_minimo = {}.'.format(radio_minimo))

    tita = rng.uniform(0, 2*np.pi, num_puntos)

    x = centro[0] + radio*np.cos(tita) + rng.normal(0., des_std, num_puntos)
    y = centro[1] + radio*np.sin(tita) + rng.normal(0., des_std, num_puntos)

    puntos = np.array(list(zip(x, y)))

    return puntos


def elipse2d_rand(centro, semieje_1, semieje_2, angulo, num_puntos, des_std, semieje_minimo=1.,
                  rng=np.random.RandomState()):
    """Genera una elipse aleatoria.

    Parameters
    ----------
    centro: list:float
        Coordenadas (xc, yc) del centro de la elipse
    semieje_1: float
        Uno de los semiejes de la elipse
    semieje_1: float
        El segundo semieje.
    angulo: float
        Ángulo en radianes de la elipse del semieje_1 con el eje X
    num_puntos: int
        Número de puntos a generar aleatoriamente
    des_std: float
        Desviación estándar del ruido gaussiano
    radio_minimo: float
        Valor mínimo para ambos semiejes
    rng: numpy.random.RandomState(): float
        Generador aleatorio

    Returns
    -------
    puntos: numpy array:float
        Matriz con los puntos en formato [[x1, y1], [x2, y2], ..., [xn, yn]]

    Exceptions
    ----------
    Lanza una excepción si los semiejes no son mayores o iguales al parámetro semieje_minimo
    """
    if semieje_1 < semieje_minimo or semieje_2 < semieje_minimo:
        raise ValueError('Alguno de los semiejes es muy pequeño según semieje_minimo = {}.'.
                         format(semieje_minimo))

    tita = rng.uniform(0, 2*np.pi, num_puntos)

    x_rand = np.random.normal(0, 1, num_puntos)
    y_rand = np.random.normal(0, 1, num_puntos)

    factor_cos = semieje_1*np.cos(tita)
    factor_sin = semieje_2*np.sin(tita)

    x = centro[0] + factor_cos*np.cos(angulo) - factor_sin*np.sin(angulo) + x_rand
    y = centro[1] + factor_cos*np.sin(angulo) + factor_sin*np.cos(angulo) + y_rand

    puntos = np.array(list(zip(x, y)))

    return puntos


def segmento2d_en_rectangulo_rand(rectangulo, num_puntos, des_std, distancia_minima=100.,
                                  rng=np.random.RandomState()):
    """Crea un segmento aleatorio de longitud mínima inscrito en un rectángulo."""
    x1 = rectangulo[0]
    y1 = rectangulo[1]
    x2 = rectangulo[2]
    y2 = rectangulo[3]

    if distancia_minima <= 0:
        raise ValueError('La distancia mínima debe ser un valor positivo.')

    if x1 + distancia_minima > x2 or y1 + distancia_minima > y2:
        raise ValueError('El tamaño del rectángulo no es válido según distancia_minima = {}.'.
                         format(distancia_minima))

    while True:
        x = rng.uniform(x1, x2, 2)
        y = rng.uniform(y1, y2, 2)

        incr_x = x[1] - x[0]
        incr_y = y[1] - y[0]
        dist = np.sqrt(incr_x**2 + incr_y**2)
        if dist > distancia_minima:
            break

    p1, p2 = [x[0], y[0]], [x[1], y[1]]
    return {'p1': p1,
            'p2': p2,
            'puntos': segmento2d_rand(p1, p2, num_puntos, des_std, distancia_minima, rng)}


def circunferencia2d_en_rectangulo_rand(rectangulo, num_puntos, des_std, radio_minimo=100.,
                                        rng=np.random.RandomState()):
    """Crea una circunferencia aleatoria de radio mínimo inscrita en un rectángulo."""
    x1 = rectangulo[0]
    y1 = rectangulo[1]
    x2 = rectangulo[2]
    y2 = rectangulo[3]

    if radio_minimo <= 0:
        raise ValueError('El radio minimo debe ser un valor positivo.')

    # Para garantizar que cabe la circunferencia
    radio_maximo = min([x2-x1, y2-y1])
    print('x1:',x1,'x2:',x2,'y1:',y1,'y2:',y2)
    if radio_maximo< radio_minimo:
        radio_maximo=radio_minimo

    if radio_maximo < radio_minimo:
        raise ValueError('El tamaño del rectángulo no es válido según radio_minimo.radio calculado:'
                         ,radio_maximo,'radio minimo:',format(radio_minimo))
    
    while True:
        
        cx = rng.uniform(x1, x2)
        cy = rng.uniform(y1, y2)
        radio = rng.uniform(radio_minimo, radio_maximo)

        if x1+radio < cx and cx+radio < x2 and y1+radio < cy and cy+radio < y2:
            break
    centro = [cx, cy]
    return {'centro': centro,
            'radio': radio,
            'puntos': circunferencia2d_rand(centro, radio, num_puntos, des_std, radio_minimo, rng)}


def elipse2d_en_rectangulo_rand(rectangulo, num_puntos, des_std, semieje_minimo=100.,
                                rng=np.random.RandomState()):
    """Crea una elipse aleatoria de semieje mínimo inscrita en un rectángulo."""
    x1 = rectangulo[0]
    y1 = rectangulo[1]
    x2 = rectangulo[2]
    y2 = rectangulo[3]

    if semieje_minimo <= 0:
        raise ValueError('El semieje minimo debe ser un valor positivo.')

    # Para garantizar que cabe la elipse
    semieje_maximo = min([x2-x1, y2-y1])
    if semieje_maximo < semieje_minimo:
        raise ValueError('El tamaño del rectángulo no es válido según semieje_minimo = {}.'.
                         format(semieje_minimo))

    while True:
        if(x2<x1):
            x1,x2=x2,x1
        
        if(y2<y1):
            y1,y2=y2,y1
            
        cx = rng.uniform(x1, x2)
        cy = rng.uniform(y1, y2)
            
        semieje_x = rng.uniform(semieje_minimo, semieje_maximo)
        semieje_y = rng.uniform(semieje_minimo, semieje_maximo)

        cond_1 = x1+semieje_x < cx and cx+semieje_x < x2
        cond_2 = y1+semieje_x < cy and cy+semieje_x < y2
        cond_3 = x1+semieje_y < cx and cx+semieje_y < x2
        cond_4 = y1+semieje_y < cy and cy+semieje_y < y2

        if cond_1 and cond_2 and cond_3 and cond_4:
            break

    angulo = rng.uniform(0, np.pi)
    centro = [cx, cy]

    #  semieje x siempre mayor que semieje_y para coherencia de ángulos
    if semieje_x < semieje_y:
        semieje_x, semieje_y = semieje_y, semieje_x

    semiejes = [semieje_x, semieje_y]
    return {'centro': centro,
            'semiejes': semiejes,
            'angulo': angulo,
            'puntos': elipse2d_rand(centro, semieje_x, semieje_y, angulo, num_puntos,
                                    des_std, semieje_minimo, rng)}


def nube_en_rectangulo2d_rand(rectangulo, num_puntos, distancia_minima=100.,
                              rng=np.random.RandomState()):
    """Crea una nube de num_puntos inscritos en un rectángulo."""
    x1 = rectangulo[0]
    y1 = rectangulo[1]
    x2 = rectangulo[2]
    y2 = rectangulo[3]

    if distancia_minima <= 0:
        raise ValueError('La distancia mínima debe ser un valor positivo.')

    if x1 + distancia_minima > x2 or y1 + distancia_minima > y2:
        raise ValueError('El tamaño del rectángulo no es válido según distancia_minima = {}.'.
                         format(distancia_minima))

    x = rng.uniform(x1, x2, num_puntos)
    y = rng.uniform(y1, y2, num_puntos)

    puntos = np.array(list(zip(x, y)))
    return {'rectangulo': rectangulo, 'puntos': puntos}


if __name__ == '__main__':
    import matplotlib.pyplot as plt
    from matplotlib.patches import Ellipse
    p1 = (10, 10)
    p2 = (400, 400)
    num_puntos = 100
    des_std = 1

    print('Testando segmento2d_rand() \n...')
    puntos = segmento2d_rand(p1, p2, num_puntos, des_std)
    print('Mostrando segmento aleatorio entre {} y {}'.format(p1, p2))
    print('con {} puntos y desviación estandar {}.'.format(num_puntos, des_std))

    plt.figure()
    plt.scatter(puntos[:, 0], puntos[:, 1], s=0.1)
    plt.axis('equal')
    plt.show()

    # Verificamos que salta una excepción si los puntos están cercanos
    try:
        puntos = segmento2d_rand((10, 10), (10.05, 10.05), 100, 1, tol=1e-1)
    except ValueError:
        pass
    else:
        assert False, 'Fallo con la tolerancia en segmento2d_rand()'

    print('segmento2d_rand() ---> OK')

    centro = [100, 100]
    radio = 100
    print('Testando circunferencia2d_rand() \n...')
    puntos = circunferencia2d_rand(centro, radio, num_puntos, des_std)
    print('Mostrando circunferencia aleatoria de centro {} y radio {}'.format(centro, radio))
    print('con {} puntos y desviación estandar {}.'.format(num_puntos, des_std))

    plt.figure()
    plt.scatter(puntos[:, 0], puntos[:, 1], s=0.1)
    plt.axis('equal')
    plt.show()

    # Verificamos que salta una excepción si los puntos están cercanos
    try:
        puntos = circunferencia2d_rand([100, 100], 0.99, num_puntos, 1, radio_minimo=1)
    except ValueError:
        pass
    else:
        assert False, 'Fallo con la tolerancia en genera_segmento2d_rand()'

    print('circunferencia2d_rand() ---> OK')

    centro = [100, 100]
    semieje_1 = 100
    semieje_2 = 50
    angulo = np.pi/4
    print('Testando elipse2d_rand() \n...')
    puntos = elipse2d_rand(centro, semieje_1, semieje_2, angulo, num_puntos, des_std)
    print('Mostrando elipse aleatoria de centro {}, semiejes ({}, {}) y ángulo {}'.
          format(centro, semieje_1, semieje_2, angulo))
    print('con {} puntos y desviación estandar {}.'.format(num_puntos, des_std))

    plt.figure()
    plt.scatter(puntos[:, 0], puntos[:, 1], s=0.1)
    plt.axis('equal')
    plt.show()

    # Verificamos que salta una excepción si los puntos están cercanos
    try:
        puntos = circunferencia2d_rand([100, 100], 0.99, num_puntos, 1, radio_minimo=1)
    except ValueError:
        pass
    else:
        assert False, 'Fallo con la tolerancia en genera_segmento2d_rand()'

    print('elipse2d_rand() ---> OK')

    print('\n\nTestando rectangulo2d_rand() \n...')
    puntos = nube_en_rectangulo2d_rand([0, 0, 640, 480], num_puntos, distancia_minima=200)['puntos']
    print('Mostrando rectangulo entre {} y {}'.format(p1, p2))
    print('con {} puntos uniformemente distribuidos.'.format(num_puntos))
    plt.figure()
    plt.scatter(puntos[:, 0], puntos[:, 1], s=0.1)
    plt.axis('equal')
    plt.show()

    # Verificamos que salta una excepción si los puntos están cercanos
    try:
        puntos = nube_en_rectangulo2d_rand([10, 10, 10.05, 10.05], 100, distancia_minima=1e-1)
    except ValueError:
        pass
    else:
        assert False, 'Fallo con la tolerancia en rectangulo2d_rand()'

    print('rectangulo2d_rand() ---> OK')

    print('\n\nTestando circunferencia2d_en_rectangulo_rand() \n...')

    x1 = 0
    y1 = 0
    x2 = 1280
    y2 = 720
    rectangulo = [x1, y1, x2, y2]
    num_puntos = 400
    des_std = 2

    datos = circunferencia2d_en_rectangulo_rand(rectangulo, num_puntos, des_std, radio_minimo=100.,
                                        rng=np.random.RandomState())

    puntos = datos['puntos']
    centro = datos['centro']
    radio = datos['radio']

    fig, ax = plt.subplots()

    plt.scatter(puntos[:, 0], puntos[:, 1], s=1, zorder=1)
    ax.add_artist(plt.Circle((centro[0], centro[1]), radio, color='r', fill=False))
    ax.set(xlim=[x1, x2], ylim=[y1, y2])
    # ax.axis('equal')

    print()

    print('circunferencia2d_en_rectangulo_rand() ---> OK')

    print('\n\nTestando elipse2d_en_rectangulo_rand() \n...')

    x1 = 0
    y1 = 0
    x2 = 1280
    y2 = 720
    rectangulo = [x1, y1, x2, y2]
    num_puntos = 400
    des_std = 2

    datos = elipse2d_en_rectangulo_rand(rectangulo, num_puntos, des_std, semieje_minimo=20.,
                                        rng=np.random.RandomState())

    puntos = datos['puntos']
    centro = datos['centro']
    semiejes = datos['semiejes']
    angulo = datos['angulo']
    eje_1 = 2*semiejes[0]
    eje_2 = 2*semiejes[1]

    fig, ax = plt.subplots()

    plt.scatter(puntos[:, 0], puntos[:, 1], s=1, zorder=1)
    ellipse = Ellipse(centro, eje_1, eje_2, np.rad2deg(angulo), edgecolor='r', fill=False, zorder=2)
    ax.add_artist(ellipse)
    ax.set(xlim=[x1, x2], ylim=[y1, y2])
    # ax.axis('equal')

    print()

    print('elipse2d_en_rectangulo_rand() ---> OK')
