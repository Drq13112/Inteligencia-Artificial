# -*- coding: utf-8 -*-
"""
Created on Thu Feb 17 11:47:44 2022

@author: david
"""
lista1=[1,2,3,45,6]

#2 ways to copy lista1
lista2=list(lista1) #Llamamos al constructor de lista y creamos una nueva lista
lista2=lista1.copy()
lista2=deepcopy(lista1)

#Esto solo es necesario con las listas por que son mutables
#Mientras que con las varibales "clasicas" no pasa por que son inmutables