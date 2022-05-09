# -*- coding: utf-8 -*-
"""Módulo de procesamiento de la imagen."""
import ransac
import modelo_recta2d as mod_rect
import modelo_circunferencia2d as mod_circ
import modelo_geometrico as mod_geom
import numpy as np
import recta_svd as svd
import circunferencia_odr as circ_odr
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

def extrae_rectangulo(lista_rectas,
                      lista_rectangulo,
                      lista_inliers,
                      circ_1,
                      lista_candidatas):
    
    Lista_distancias=[]
    vertices_rectangulo=[]
    lista_rectas_rectangulo=[]
    inliers_recta_rectangulo=[]
    vertices_de_cada_recta=[]
    lista_indices=[]
    #Cada iteracion del for es el analisis de un rectangulo
    for set in lista_candidatas:
        
        recta_1,recta_2,_=set[0]
        recta_3,recta_4,_=set[1]
        lista_rectas_rectangulo=(recta_1,recta_2,recta_3,recta_4)
        
        punto1=mod_rect.interseccion(recta_1, recta_4)
        punto2=mod_rect.interseccion(recta_1, recta_3)
        punto3=mod_rect.interseccion(recta_2, recta_3)
        punto4=mod_rect.interseccion(recta_2, recta_4)
        vertices_rectangulo=(punto1,punto2,punto3,punto4)
        
        #vertices_de_cada_recta=(Vertices de la recta1, Vertices de la recta2,Vertices de la recta3,Vertices de la recta4)
        vertices_de_cada_recta.append([(punto1,punto2),(punto3,punto4),(punto2,punto3),(punto1,punto4)])
        
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
                
                #guardo los indices de las rectas que pueden formar parte de los rectangulos,
                #para actualizar los inliers tras el ajuste fino
                
                #(indice recta1,indice recta2, indice recta3, indice recta4)
                lista_indices.append(indice)
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
                    
                lista_rectangulo.append(vertices_rectangulo) 
    return (lista_rectangulo,inliers_recta_rectangulo,vertices_de_cada_recta,lista_indices)
    
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
    #diccionario={'outliers':[],'recta':[],'inliers':[],'circunferencia':[] }
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
    new_lista_rectas_rectangulo=[]
    new_inliers_recta_rectangulo=[[],[],[],[]]
    
    (lista_rectangulo,
    inliers_recta_rectangulo,
    vertices_de_cada_recta,
    lista_indices)=extrae_rectangulo(lista_rectas,
                      lista_rectangulo,
                      lista_inliers,
                      circ_1,
                      lista_candidatas)
    
    if lista_rectangulo!=[]:
        
        #Filtrado de los inliers de las rectas:
            
            
        #Estructura de la lista de vertices:
        #vertices_de_cada_recta=(Vertices de la recta1, Vertices de la recta2,Vertices de la recta3,Vertices de la recta4)
        #Estructura de la lista inliers_recta_rectangulo:
        #inliers_recta_rectangulo= (inliers_recta1,inliers_recta2,inliers_recta3,inliers_recta4)
        
        #sacamos los vertices de cada recta y como la tupla de vertices y lista de inliers de cada recta 
        #comparten la misma posición en sus respectivas listas, puedo usar el mismo indice
        #para buscar en cada lista
        
        #La variable k hace referencia a los rectangulos dectados;
        #Por ejemplo, si se dectanto 2 rectangulos, se recorreá dos veces el bucle for de la k
        puntos_malos=0
        for k in range(len(vertices_de_cada_recta)):
            
            for j,vertice in enumerate(vertices_de_cada_recta[k]):
                for punto in inliers_recta_rectangulo[j]:
                    
                    distancia1=dist(punto,vertice[0])
                    distancia2=dist(punto,vertice[1])
                    distancia= max(distancia1,distancia2)
                    longitud= dist(vertice[0],vertice[1])
                    
                    if distancia>longitud+TOL_RANSAC:
                        puntos_malos=puntos_malos+1
                    else:
                        #guardo los puntos buenos
                        #En un primer momento intenté eliminar aquellos puntos que no eran validos
                        #pero me salían errores y no me dejaba, asi que opté por guardar en otra lista
                        #los puntos válidos
                        new_inliers_recta_rectangulo[j].append(punto)
                        
                #En caso de que el nuevo ajuste no cumpla con la inliers minimos, se descarta el rectangulo
                if len(new_inliers_recta_rectangulo[j])<TOL_NUM_INLIERS_RECTA:
                    for i in range(3*k+j):
                        new_inliers_recta_rectangulo.pop()
                    break
                    
        print("Puntos eliminados:",puntos_malos)                   
        #Ajuste fino mediante Descomposición de valores singulares de todas las rectas:
        for set_puntos in new_inliers_recta_rectangulo:
            lista_numpy =np.array(set_puntos)
            
            if lista_numpy.shape[0]>0:
                
                recta=mod_rect.ModeloRecta2d()
                recta.ajusta(svd.recta_svd,lista_numpy)
                
                sum_errores = sum(mod_geom.errores(recta, set_puntos))
                print('errores recta ajuste fino:', sum_errores)
                
                new_lista_rectas_rectangulo.append(recta)               
            
        #Obtengo los nuevos vertices
        lista_paralelas=paralelas(new_lista_rectas_rectangulo,TOL_ANGULO)
        lista_candidatas=perpendiculares(lista_paralelas,TOL_ANGULO)
        
        #vacio la lista
        lista_rectangulo=[]
        for set in lista_candidatas:
            
            recta_1,recta_2,_=set[0]
            recta_3,recta_4,_=set[1]
            
            punto1=mod_rect.interseccion(recta_1, recta_4)
            punto2=mod_rect.interseccion(recta_1, recta_3)
            punto3=mod_rect.interseccion(recta_2, recta_3)
            punto4=mod_rect.interseccion(recta_2, recta_4)
            
            lista_rectangulo.append([punto1,punto2,punto3,punto4])
            
        #Actualizo los nuevos inliers
        if len(new_inliers_recta_rectangulo)!=0 :
            for j,indice in enumerate (lista_indices):
                lista_inliers[indice]=new_inliers_recta_rectangulo[j]
    
    """
    Ahora realizamos un ajuste fino a la circunferencia
    """
    circ_ajustada=mod_circ.ModeloCircunferencia2d()
    
    #lista_inliers[-1] porque sé que solo se va a generar unica circunferencia
    #y siempre va a estar en la última posicion del lista_inliers
    circ_ajustada.ajusta(circ_odr.circunferencia_odr_geometrica,lista_inliers[-1],circ_1.parametros)
    
    sum_errores = sum(mod_geom.errores(circ_ajustada, lista_inliers[-1]))
    print('errores circunferencia ajuste fino:', sum_errores)
    
    #lista_circunferencias.appendappend(circ_ajustada.parametros)
    lista_circunferencias[0]=(circ_ajustada.parametros)

    #Devuelve solo los parametros
    return {'recta': lista_rectas,
            'rectangulo':lista_rectangulo,
            'circunferencia': lista_circunferencias,
            'inliers': lista_inliers,
            'outliers': outliers}

if __name__ == '__main__':
    pass
