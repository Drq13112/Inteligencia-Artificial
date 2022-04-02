# -*- coding: utf-8 -*-
"""
Created on Thu Mar  3 20:07:04 2022

@author: david

Este codigo implementa un menu interactivo para crear colas de prioridad.
Se almecenarán los datos numericos de menor a mayor mediante moticulos binarios
"""




        
def push(lista,valor):
    
    lista.append(valor)
    ordenar_lista(lista)
def pop(lista):
    
    
    print("Valor eliminado:",lista[0])
    #Sobreescribimos el ultimo elemento como el primero
    #Reducimos el tamaño del array
    #y reordenamos
    lista[0]=lista[len(lista)-1]
    lista.pop()
    ordenar_lista(lista)
    print(" ")

def top(lista):
   
    print("Valor de la raiz:",lista[0])
    print(" ")
    return lista[0]

def Mostrar(lista):
    
    print("Cola: ",end=" ")
    for i in lista:
        print(i,end=",")
    print(" ")
    print(" ")
    
def montoniza(lista, n, i):
    
        #inicializamos el padre como el valor más grande
        padre = i
        
        #n=tamano del array
        #l->left; Hijo de la izquierda
        l = 2 * i + 1
        #r->right
        r = 2 * i + 2
        
        
        #Vemos si el hijo de la izquierda del padre existe y si es
        #mayor que su padre
        if l < n and lista[i] < lista[l]:
            padre = l
        
        #Vemos si el hijo de la derecha del padre existe y si es
        #mayor que su padre
        if r < n and lista[padre] < lista[r]:
            padre = r
            
        # Si el padre no es el más grande, intercambianmos con el más grande
        if padre != i:
            lista[i], lista[padre] = lista[padre], lista[i]
            montoniza(lista, n, padre)
    
def ordenar_lista(lista):
    
    #opcion rapida
    #lista_new.sort()
    
    #Usando monticulos
    n = len(lista)
  
    # Construimos el monticulo max
    # El operador // es de division entera.
    for i in range(n//2, -1, -1):
        montoniza(lista, n, i)
        
        #Recorre el array desde tamaño_array-1 hasta 0 en pasos de 1
        #Ejemplo: 20,19,18,17,.....2,1
    for i in range(n-1, 0, -1):
        # intercambiamos
        lista[i], lista[0] = lista[0], lista[i]

        montoniza(lista, i, 0)
        
        
        
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
              
              
    
