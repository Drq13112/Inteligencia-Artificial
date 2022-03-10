# -*- coding: utf-8 -*-
"""
Created on Thu Mar  3 20:07:04 2022

@author: david

Este codigo implementa un menu interactivo para crear colas de prioridad.
Se almecenarán los datos numericos de menor a mayor
"""




        
def push(lista,valor):
    
    lista.append(valor)
    ordenada=False
    while(ordenada==False):
        ordenada=True
        
        for i in range(len(lista)-1):
            
            if(lista[i]>lista[i+1]):
                ordenada=False
                lista[i+1],lista[i]=lista[i],lista[i+1]
def pop(lista):
    
    print("Valor eliminado:")
    min_valor=lista[0]
    lista.remove(min_valor)
    print(" ")

def top(lista):
   
    print("Valor de la raiz:")
    print(lista[0])
    print(" ")

def Mostrar(lista):
    
    print("Cola: ",end=" ")
    for i in lista:
        print(i,end=",")
    print(" ")
    print(" ")
    
def ordenar_lista(lista_new):

    
    #1º opcion: La que yo usaria personalmente
    #lista_new.sort()
    
    #2ºopcion; En caso de que prefieras que desarrollemos por nuestra cuenta:
    ordenada=False
    while(ordenada==False):
        ordenada=True
        
        for i in range(len(lista_new)-1):
            
            if(lista_new[i]>lista_new[i+1]):
                ordenada=False
                lista_new[i+1],lista_new[i]=lista_new[i],lista_new[i+1]
                
    
    print("Lista ordenada")
        
        
        
lista=[]
while(True):
    opcion=-1
    print("Menu:")
    print("-Insertar valor en la lista->0")
    print("-Eliminar la raíz de la cola->1")
    print("-Leer el elemento en la raíz->2")
    print("-Ordenar una lista solicitando valores->3")
    print("-Mostrar lista actual->4")
    print("-Salir->5")
    
    opcion=input("opcion:")
    opcion=int(opcion)
        
    if (opcion==0):
        valor=input("Inserte valor: ")
        valor=int(valor)
        push(lista,valor)
    if(opcion==1):
        pop(lista)
    if(opcion==2):
        top(lista)
    if(opcion==3):
        #Cola1.ordenar()
        lista_new=[]
        print("Se le preguntará uno a uno los valores de la lista")
        while(True):
            valor=input("Inserte valor en la lista o pulse 'q' para salir:")
            if(valor=="q"):
                break
            valor=int(valor)
            lista_new.append(valor)
        
        ordenar_lista(lista_new)
        Mostrar(lista_new)
    if(opcion==4):
        Mostrar(lista)
    if(opcion==5):
        print("adios")
        break
              
              
    
