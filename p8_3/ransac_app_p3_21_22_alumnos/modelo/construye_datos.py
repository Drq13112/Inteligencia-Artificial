# -*- coding: utf-8 -*-
"""Construye una imagen aleatoria formada por puntos, 3 segmentos y una circunferencia."""
import numpy as np
import matplotlib.pyplot as plt
import figuras_aleatorias as fig_aleat

def construye_datos(rng=np.random.RandomState()):
    """Construye una imagen aleatoria formada por puntos, 3 segmentos y una circunferencia.

    rectangulo_imagen = (x1, y1, x2, y2) -> Vértices inf izq e sup der.
    segmento_rand -> lista de puntos aleatorios pertenecientes a un segmento
    circunferencia_rand -> lista de puntos aleatorios pertenecientes a una circunferencia
    imagen_rand -> Diccionario formado por un rectangulo y puntos aleatorios que no pertenecen
                   a las figuras
    Devuelve la información a través de un diccionario.
    
    """

    DES_STD = 1
    NUM_PUNTOS = 2000
    POR_RECTANGULO=0.08
    POR_CIRCUNFERENCIA=0.05
    POR_RECTA=0.08
    NUMERO_RECTAS_MIN=4
    NUMERO_RECTAS_MAX=6
    NUM_RECTAS=int(rng.uniform(NUMERO_RECTAS_MIN,NUMERO_RECTAS_MAX))
    LONGITUD_MINIMA =350.
    

    # Rectángulo imagen HD
    x1 = 0.0
    y1 = 0.0
    x2 = 1280.
    y2 = 720.
    

    if x1 >= x2 or y1 >= y2:
        raise ValueError('No es un rectángulo válido.')

    rectangulo_imagen = (x1, y1, x2, y2)


    num_puntos = NUM_PUNTOS
    des_std = DES_STD  # Se usa el mismo ruido en todas las figuras, pero no es preceptivo

    # Segmento aleatorio 1
    ratio_inliers = POR_RECTA  # Proporción sobre el total
    num_inliers = int(num_puntos*ratio_inliers)
    Lista_rectas=[]
    for i in range(NUM_RECTAS):

        locals()["Segmento_rand_" + str(i)] = fig_aleat.segmento2d_en_rectangulo_rand(rectangulo_imagen,
                                                              num_inliers,
                                                              des_std=des_std,
                                                              distancia_minima=LONGITUD_MINIMA,
                                                              rng=rng) 

        Lista_rectas.append(locals()["Segmento_rand_" + str(i)]['puntos'])
    
    #---------------------------------------------------------------------------------------------------
    # Crea un rectangulo con desplazamiento y rotaciona aleatorias
    #---------------------------------------------------------------------------------------------------

    #Calculo aleatorio de los lados del rectangulo
    lMayor=rng.uniform(500,550)
    lmenor=rng.uniform(350,400)
    
    #Rotacion y posicion aleatorios del rectangulo
    
    #Lados del rectangulo
    r_x1,r_x2=-lMayor/2,lMayor/2
    r_y1,r_y2=-lmenor/2,lmenor/2
    
    #Vertices centrados:
    v1 = (r_x1+x2/2, r_y1+y2/2)
    v2 = (r_x1+x2/2, r_y2+y2/2)
    v3 = (r_x2+x2/2, r_y1+y2/2)
    v4 = (r_x2+x2/2, r_y2+y2/2)
    
    rectangulo=[v1[0],v1[1],v4[0],v4[1]]
    
    #Circunferencia inscrita
    ratio_inliers = POR_CIRCUNFERENCIA  # Proporción sobre el total
    num_inliers_4 = int(num_puntos*ratio_inliers)
    radio_minimo =0.3*lmenor
    circunferencia_rand = fig_aleat.circunferencia2d_en_rectangulo_rand(rectangulo,
                                                                        num_inliers_4, des_std,
                                                                        radio_minimo, rng)
    
    #Dibujo el rectangulo
    ratio_inliers = POR_RECTANGULO  # Proporción sobre el total
    num_inliers_1 = int(num_puntos*ratio_inliers)
    
    segmento_1 = fig_aleat.segmento2d_rand(v1,v2,num_inliers_1,
                                                             des_std=des_std,
                                                             rng=rng)
    segmento_2 = fig_aleat.segmento2d_rand(v1,v3,num_inliers_1,
                                                             des_std=des_std,                                                            
                                                             rng=rng)
    segmento_3 = fig_aleat.segmento2d_rand(v3,v4,num_inliers_1,
                                                             des_std=des_std,
                                                             rng=rng)
    segmento_4 = fig_aleat.segmento2d_rand(v4,v2,num_inliers_1,
                                                             des_std=des_std,                                                             
                                                             rng=rng)
    
    #Giramos el conjunto
    tita=rng.uniform(0,np.pi)
    
    rot = np.array([[np.cos(tita), -np.sin(tita)],
    [np.sin(tita), np.cos(tita)]])
    
    v1 = v1@rot
    v2 = v2@rot
    v3 = v3@rot
    v4 = v4@rot
    
    
    #Transladamos el conjunto
    num_columnas=1280
    num_filas=720
    tx_min = -min(v1[0], v2[0], v3[0], v4[0])
    tx_max = num_columnas - max(v1[0], v2[0], v3[0], v4[0])
    ty_min = -min(v1[1], v2[1], v3[1], v4[1])
    ty_max = num_filas - max(v1[1], v2[1], v3[1], v4[1])
    
    tx_rand=rng.uniform(tx_min,tx_max)
    ty_rand=rng.uniform(ty_min,ty_max)
    
    segmento_1 = segmento_1@rot + [tx_rand, ty_rand]
    Lista_rectas.append(segmento_1)
    segmento_2 = segmento_2@rot + [tx_rand, ty_rand]
    Lista_rectas.append(segmento_2)
    segmento_3 = segmento_3@rot + [tx_rand, ty_rand]
    Lista_rectas.append(segmento_3)
    segmento_4 = segmento_4@rot + [tx_rand, ty_rand]
    Lista_rectas.append(segmento_4)
    
    
    circunferencia_rand['puntos']=circunferencia_rand['puntos']@rot + [tx_rand, ty_rand]
    Lista_rectas.append(circunferencia_rand['puntos'])
    
    # Crea una nube de puntos aleatoria en un rectángulo
    num_puntos_imagen = num_puntos- (num_inliers*NUM_RECTAS+num_inliers_1*4+num_inliers_4)
    if num_puntos_imagen < 0:
        raise ValueError('El número de inliers total supera al número de puntos estimado')

    nube_rectangulo_rand = fig_aleat.nube_en_rectangulo2d_rand(rectangulo_imagen, num_puntos_imagen)
    # unimos los vectores de puntos
    
    Lista_rectas.append(nube_rectangulo_rand['puntos'])
    # for recta in Lista_rectas:
    puntos = np.concatenate((Lista_rectas), axis=0)
    
    # Desordenamos los puntos
    np.random.shuffle(puntos)
    
    
    #devolvemos un diccionario
    return {'imagen': nube_rectangulo_rand,
            'segmento':Lista_rectas ,
            'rectangulo':[segmento_1,segmento_2,segmento_3,segmento_4],
            'circunferencia': [circunferencia_rand],
            'puntos': puntos}


def test_contruye_datos():
    datos = construye_datos()
    puntos = datos['puntos']
    rectangulo = datos['imagen']['rectangulo']

    x1 = rectangulo[0]
    y1 = rectangulo[1]
    x2 = rectangulo[2]
    y2 = rectangulo[3]

    fig, ax = plt.subplots()
    plt.xlim(x1, x2)
    plt.ylim(y1, y2)

    plt.scatter(puntos[:, 0], puntos[:, 1], s=0.1)
    ax.set_aspect(1)
    plt.show()


if __name__ == '__main__':
    test_contruye_datos()
