# -*- coding: utf-8 -*-
"""Módulo de procesamiento de la imagen."""
import ransac
import modelo_recta2d as mod_rect
import modelo_circunferencia2d as mod_circ
import modelo_geometrico as mod_geom
import numpy as np
from math import dist


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

    # Creamos un estimador Ransac para rectas
    ransac_recta = ransac.Ransac(mod_rect.ModeloRecta2d, TOL_RANSAC)
    marcador=False
    iterador=0
    #print('puntos:',len(puntos))
    diccionario={'outliers':[],'recta':[],'inliers':[],'circunferencia':[] }
    lista_rectas=[]
    lista_rectas_raw=[]
    lista_rectangulo=[]
    lista_circunferencias=[]
    lista_inliers=[]
    while(1):
        if marcador==False:
            marcador=True
            recta=ransac_recta(puntos)
            print('Detectando recta ',iterador,'...')
            inliers_recta, outliers = mod_geom.inliers_outliers(recta, puntos,
                                                          tolerancias=TOL_DISTANCIA_RECTAS)
            
            
        else:
            recta=ransac_recta(outliers)
            print('Detectando recta ',iterador,'...')
            inliers_recta, outliers = mod_geom.inliers_outliers(recta, outliers,
                                                          TOL_DISTANCIA_RECTAS)
            
        # Errores recta 
        sum_errores = sum(mod_geom.errores(recta, inliers_recta))
        print('errores recta ransac:', sum_errores)
        #print('num_iliers:',num_inliers)
        #print('num_outliers:',len(outliers))
        if(len(inliers_recta)>=TOL_NUM_INLIERS_RECTA):
            iterador=iterador+1
            """
            locals()["recta_" + str(iterador)] = recta
            locals()["inliers_recta_" + str(iterador)] = inliers_recta
            """
            lista_rectas.append(recta.parametros)
            lista_rectas_raw.append(recta)
            lista_inliers.append(inliers_recta)
        else:
            break
             
    # =============================================================================
    #  Detección de la circunferencia
    # =============================================================================
    
    # Creamos un estimador Ransac para circunferencias
    ransac_circunferencia = ransac.Ransac(mod_circ.ModeloCircunferencia2d, TOL_RANSAC)
    iterador=0
    
    while(1):
        # Detectamos circunferencia
        print('Detectando circunferencia',iterador,'...')
        circ_1 = ransac_circunferencia(outliers)
        inliers_circ_1, outliers = mod_geom.inliers_outliers(circ_1, outliers,
                                                             TOL_DISTANCIA_CIRCUNFERENCIAS)
    
        sum_errores = sum(mod_geom.errores(circ_1, inliers_circ_1))
        print('errores circ ransac 1:', sum_errores)
        
        if(len(inliers_circ_1)>=TOL_NUM_INLIERS_CIRCUNFERENCIA):
            
            iterador=iterador+1
        
            #añadimos la diccionario circunferencia
            #diccionario['circunferencia']=circ_1.parametros
            lista_circunferencias.append(circ_1.parametros)
            lista_inliers.append(inliers_circ_1)
            break
            
        else:
            break
        
    #diccionario['outliers']=outliers
    #diccionario['recta']=lista_rectas
    #diccionario['inliers']= lista_inliers    
    
    # =============================================================================
    #  Detección de rectangulos
    # =============================================================================
    
    """
    Método empleado para la detección y selección del rectangulo
    Durante la detección de las rectas, se han ido guardando en un array
    cada una de las rectas.
    
    Una vez que ya tenemos todas las rectas, comprobamos sus angulos y
    miramos las que son iguales, de esta forma obtenemos las paralelas
    
    Teniendo las candidatas paralelas, comparamos el angulo entre ellas
    Si cumple los requisitos, pasan al siguiente nivel.
    
    Obtenemos los puntos de corte y comprobamos si la distancia entre ellos
    está dentro de los margenes posibles.
    
    Por ultimo comprobamos si la circunferencia generada está dentro de algunos
    de los rectangulos obtenidos
    """
    
    lista_paralelas=paralelas(lista_rectas_raw,TOL_ANGULO)
    lista_candidatas=perpendiculares(lista_paralelas,TOL_ANGULO)
    
    #Declaro todas las listas que voy a usar en el proceso
    vertices_rectangulo=[]
    Lista_vertices=[]
    Lista_distancias=[]
    lista_rectas_rectangulo=[]
    inliers_recta_rectangulo=[]
    it=0
    
    for set in lista_candidatas:
        
        recta_1,recta_2,_=set[0]
        recta_3,recta_4,_=set[1]
        lista_rectas_rectangulo=(recta_1,recta_2,recta_3,recta_4)
        #angulo1 = mod_rect.angulo_entre_rectas(recta_1, recta_3)
        #angulo2 = mod_rect.angulo_entre_rectas(recta_1, recta_4)
        
        punto1=mod_rect.interseccion(recta_1, recta_4)
        punto2=mod_rect.interseccion(recta_1, recta_3)
        punto3=mod_rect.interseccion(recta_2, recta_3)
        punto4=mod_rect.interseccion(recta_2, recta_4)
        vertices_rectangulo=(punto1,punto2,punto3,punto4)
        
        i=0
        for point in vertices_rectangulo:
            locals()["dist_" + str(i)]=dist(vertices_rectangulo[0],point)
            Lista_distancias.append(locals()["dist_" + str(i)])
            i=i+1
        
        #Compruebo que el conjunto de rectas cumple el tamaño del rectangulo
        lado_menor=False
        lado_mayor=False
        for distancia in Lista_distancias:
            if (distancia>=350 and distancia<=400):
                lado_menor=True
                
            if (distancia>=500 and distancia<=550):
                lado_mayor=True
            
        if lado_mayor==True and lado_menor==True:
            
            #Ahora comprobamos que el circulo tmb esté dentro del cuadrado
            """
            Recorremos los inliers de las rectas que pertenecen al rectangulo.
            Calculo la distancia del centro del circulo a cada uno de los inliers
            de las rectas qeu forman el rectangulo.
            Si la distancia es menor al radio de la circunferencia rechazo el cuadrado
            """
            centro_circunferencia=(circ_1.parametros[0],circ_1.parametros[1])
            
            #Identifico los inliers que pertenecen al rectangulo y los meto dentro de inliers_recta_rectangulo
            for rect in lista_rectas_rectangulo:
                indice=lista_rectas.index(rect.parametros)
                inliers_recta_rectangulo.append(lista_inliers[indice])
            
            #Compruebo la distancia de cada inliers respecto al centro de la
            #de la circunferencia es mayor que el radio de la misma
            dentro=True
            for q in range(len(inliers_recta_rectangulo)):
                for punto in inliers_recta_rectangulo[q]:
                    distancia=dist(centro_circunferencia,punto)
                    if distancia<circ_1.parametros[2]:
                        dentro=False
                        
            if dentro==True:
                
                #elimino las rectas que pertenecen al rectangulo
                #for recta in lista_rectas_rectangulo:
                #    lista_rectas.remove(recta.parametros)
                    
                lista_rectangulo.append(vertices_rectangulo) 
    
    #Devuelve solo los parametros
    return {'recta': lista_rectas,
            'rectangulo':lista_rectangulo,
            'circunferencia': lista_circunferencias,
            'inliers': lista_inliers,
            'outliers': outliers}

if __name__ == '__main__':
    pass
