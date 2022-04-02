# -*- coding: utf-8 -*-
"""
Created on Sun Mar 13 19:47:41 2022

@author: david
"""
import cola_prioridad as cp

Lista= cp.Priority_Queue()
while(True):
    try:
        nombre=input("Nombre del fichero: ")
        with open (nombre,"r") as file:
            valores = []
            try:
                for linea in file:
                    valores=[int(x) for x in linea.strip().split(",")]
                    #La funciñon strip elimina el caracter de salto de pagina 
                    #La función split divide el arcivo de texto en una lista
            except:
                print("Error al leer datos del fichero : ",nombre,"Compruebe su contenido")
            print("Contenido del fichero:",valores)
            file.close()
            Lista.heapsort(valores)
            Lista.Mostrar()
            salida=input("¿leer otro fichero? pulse: 'si' ó 'no':")
            if (salida=="no"):
                break
    except FileNotFoundError:
        print("Error al abrir el fichero: ",nombre)
            
        