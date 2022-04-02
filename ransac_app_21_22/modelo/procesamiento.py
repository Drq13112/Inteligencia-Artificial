# -*- coding: utf-8 -*-
"""Módulo de procesamiento de la imagen."""
import ransac
import modelo_recta2d as mod_rect
import modelo_circunferencia2d as mod_circ
import modelo_geometrico as mod_geom


def procesamiento(puntos):
    """Función de procesamiento de la imagen.

    Conoce la existencia a priori de 3 rectas y una circunferencia. Este conocimiento previo
    es habitual en los problemas de visión industrial.
    """

    TOL_RANSAC = 1.
    TOL_DISTANCIA_RECTAS = (1., 2.)
    TOL_DISTANCIA_CIRCUNFERENCIAS = (1., 1.)
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
        if(len(inliers_recta)>=80):
            iterador=iterador+1
            """
            locals()["recta_" + str(iterador)] = recta
            locals()["inliers_recta_" + str(iterador)] = inliers_recta
            """
            lista_rectas.append(recta.parametros)
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
        
        if(len(inliers_circ_1)>=50):
            
            iterador=iterador+1
        
            #añadimos la diccionario circunferencia
            diccionario['circunferencia']=circ_1.parametros
            lista_circunferencias.append(circ_1.parametros)
            lista_inliers.append(inliers_circ_1)
            break
            
        else:
            break
        
    diccionario['outliers']=outliers
    diccionario['recta']=lista_rectas
    diccionario['inliers']= lista_inliers     
    
    #Devuelve solo los parametros
    return {'recta': lista_rectas,
            'circunferencia': lista_circunferencias,
            'inliers': lista_inliers,
            'outliers': outliers}


#[rectas.parametros for recta in lista_rectas]

if __name__ == '__main__':
    pass
