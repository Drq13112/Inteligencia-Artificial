# -*- coding: utf-8 -*-
"""Módulo controlador."""
import time
import networkx as nx
import matplotlib.pyplot as plt

# Importaciones bibliotecas
from look_ahead_fc import LookAheadFC
from backtracking import Backtracking

# Importaciones aplicacion
from modelo.reinas import ReinasCSP, ColeradoGrafos
from vista.visualizacion import imprime_resultados

def genera_graficador(alg,provincias,vecindades,method):
    G = nx.Graph()
    G.add_nodes_from(provincias)
    G.add_edges_from(vecindades)
    # Creo un nuevo diccionario con el nombre de cada provincia y su color
    color_map = {}
    for p,c in alg.solucion:
        #print(provincias[p],'->',c)
        color_map[provincias[p]] = c
    # Graficamos los colores de cada nodo
    node_colors = [color_map.get(node) for node in G.nodes()]
    nx.draw_circular(G, with_labels=True, node_color=node_colors, node_size=1000, cmap=plt.cm.rainbow)
    plt.title(method)
    plt.show()
    
def run_coloreado_grafos(provincias,vecindades,colores):
    #Ejecución principal del programa coloreado.
    mapa = ColeradoGrafos(provincias,vecindades,colores)
    ########################################################################
    # ORDINAL BACKTRACKING
    ########################################################################
    tipo_seleccion_variables = 'ordinal'
    alg = Backtracking(mapa, tipo_seleccion_variables)
   
    t_inicio = time.process_time()
    
    if alg():
        t_fin = time.process_time() - t_inicio
        ok = mapa.solucion_consistente(alg.solucion)
    else:
        t_fin = time.process_time() - t_inicio
        ok = False
    #Modifico alg.solucion para ver mejor.
    resultados = {'problema': 'MAPA',
                  'dimension': len(provincias),
                  'solucion': alg.solucion,
                  'num_nodos': alg.num_nodos,
                  'tiempo': t_fin,
                  'algoritmo': 'Backtracking',
                  'seleccion': tipo_seleccion_variables,
                  'ok': ok}

    imprime_resultados(resultados)
    if resultados['ok']:
        genera_graficador(alg,provincias,vecindades,"ORDINAL BACKTRACKING")
        
    ########################################################################
    # ORDINAL FORWARD CHECKING
    ########################################################################
    
    tipo_seleccion_variables = 'ordinal'
    alg = LookAheadFC(mapa, tipo_seleccion_variables)
    t_inicio = time.process_time()
    if alg():
        t_fin = time.process_time() - t_inicio
        ok = mapa.solucion_consistente(alg.solucion)
    else:
        t_fin = time.process_time() - t_inicio
        ok = False

    resultados = {'problema': 'MAPA',
                  'dimension': len(provincias),
                  'solucion': alg.solucion,
                  'num_nodos': alg.num_nodos,
                  'tiempo': t_fin,
                  'algoritmo': 'Forward Checking',
                  'seleccion': tipo_seleccion_variables,
                  'ok': ok}

    imprime_resultados(resultados)
    if resultados['ok']:
        genera_graficador(alg,provincias,vecindades,"ORDINAL FORWARD CHECKING")
    ########################################################################
    # ALEATORIO BACKTRACKING
    ########################################################################
    tipo_seleccion_variables = 'aleatoria'
    alg = LookAheadFC(mapa, tipo_seleccion_variables)
    t_inicio = time.process_time()
    if alg():
        t_fin = time.process_time() - t_inicio
        ok = mapa.solucion_consistente(alg.solucion)
    else:
        t_fin = time.process_time() - t_inicio
        ok = False

    resultados = {'problema': 'MAPA',
                  'dimension': len(provincias),
                  'solucion': alg.solucion,
                  'num_nodos': alg.num_nodos,
                  'tiempo': t_fin,
                  'algoritmo': 'Forward Checking',
                  'seleccion': tipo_seleccion_variables,
                  'ok': ok}

    imprime_resultados(resultados)
    if resultados['ok']:
        genera_graficador(alg,provincias,vecindades,"ALEATORIO")
    ########################################################################
    # MRV FORWARD CHECKING
    ########################################################################
    tipo_seleccion_variables = 'mrv'
    alg = LookAheadFC(mapa, tipo_seleccion_variables)
    t_inicio = time.process_time()
    if alg():
        t_fin = time.process_time() - t_inicio
        ok = mapa.solucion_consistente(alg.solucion)
    else:
        t_fin = time.process_time() - t_inicio
        ok = False

    resultados = {'problema': 'MAPA',
                  'dimension': len(provincias),
                  'solucion': alg.solucion,
                  'num_nodos': alg.num_nodos,
                  'tiempo': t_fin,
                  'algoritmo': 'Forward Checking',
                  'seleccion': tipo_seleccion_variables,
                  'ok': ok}

    imprime_resultados(resultados)
    if resultados['ok']:
        genera_graficador(alg,provincias,vecindades,"MRV")
    
 
def run_reinas(tam):
    """Ejecución principal del programa reinas."""
    reinas = ReinasCSP(tam)

    tipo_seleccion_variables = 'ordinal'
    alg = Backtracking(reinas, tipo_seleccion_variables)

    t_inicio = time.process_time()
    if alg():
        t_fin = time.process_time() - t_inicio
        ok = reinas.solucion_consistente(alg.solucion)
    else:
        t_fin = time.process_time() - t_inicio
        ok = False

    resultados = {'problema': 'REINAS',
                  'dimension': tam,
                  'solucion': alg.solucion,
                  'num_nodos': alg.num_nodos,
                  'tiempo': t_fin,
                  'algoritmo': 'Backtracking',
                  'seleccion': tipo_seleccion_variables,
                  'ok': ok}

    imprime_resultados(resultados)

    tipo_seleccion_variables = 'mrv'
    alg = LookAheadFC(reinas, tipo_seleccion_variables)
    t_inicio = time.process_time()
    if alg():
        t_fin = time.process_time() - t_inicio
        ok = reinas.solucion_consistente(alg.solucion)
    else:
        t_fin = time.process_time() - t_inicio
        ok = False

    resultados = {'problema': 'REINAS',
                  'dimension': tam,
                  'solucion': alg.solucion,
                  'num_nodos': alg.num_nodos,
                  'tiempo': t_fin,
                  'algoritmo': 'Forward Checking',
                  'seleccion': tipo_seleccion_variables,
                  'ok': ok}

    imprime_resultados(resultados)


if __name__ == '__main__':
    run_reinas(20)
