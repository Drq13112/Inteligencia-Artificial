# -*- coding: utf-8 -*-
"""
Created on Sun Mar 13 18:17:50 2022

@author: David Redondo Quintero

Se trata de la implentación de un módulo de una cola de prioridad
con prioridad según el menor valor.

Clase con las funciones de la cola de prioridad y comprobación de las
mismas mediante la funcion assert().
"""

       
class Priority_Queue():
    def __init__(self):
        self.lista_string=""
        self.lista=[]
    def __str__(self):
        #devuelve la cola en formato string
        
        for i in self.lista:
            self.lista_string=self.lista_string+str(i)+","
            
        return self.lista_string
        
    def tamano(self):
        return len(self.lista)

    def __getitem__(self, posicion):
        return self.lista[posicion]
    
    def inserta(self,value,posicion):
        self.lista[posicion]=value
    
    def __setattr__(self, name, value):
        self.__dict__[name] = value
        
    def push(self, valor):

        self.lista.append(valor)
        self.heapsort(self.lista)
        return self.lista

    def pop(self):

        print("Valor eliminado:", self.lista[0])
        #self.heapsort(self.lista)
        # Sobreescribimos el ultimo elemento como el primero
        # Reducimos el tamaño del array
        # y reordenamos
        self.lista[0] = self.lista[len(self.lista)-1]
        self.lista.pop()
        self.heapsort(self.lista)
        print(" ")
        return self.lista

    def top(self):

        print("Valor de la raiz:", self.lista[0])
        print(" ")
        return self.lista[0]

    def Mostrar(self):

        print("Cola: ", end=" ")
        for i in self.lista:
            print(i, end=",")
        print(" ")
        print(" ")
        return self.lista

    def montoniza(self,lista, n, i):

        # inicializamos el padre como el valor más grande
        padre = i

        # n=tamano del array
        # l->left; Hijo de la izquierda
        l = 2 * i + 1
        # r->right; Hijo de la derecha
        r = 2 * i + 2

        # Vemos si el hijo de la izquierda del padre existe y si es
        # mayor que su padre
        if l < n and lista[i] < lista[l]:
            padre = l

        # Vemos si el hijo de la derecha del padre existe y si es
        # mayor que su padre
        if r < n and lista[padre] < lista[r]:
            padre = r

        # Si el padre no es el más grande, intercambianmos con el más grande
        if padre != i:
            lista[i],lista[padre]=lista[padre],lista[i]
            self.montoniza(lista,n, padre)

    def heapsort(self, lista_new):
        
        self.lista=list(lista_new)
        #lista = Priority_Queue(lista_new)
        # opcion rapida
        # lista_new.sort()

        # Usando monticulos
        n = self.tamano()

        # Construimos el monticulo max
        for i in range(n//2, -1, -1):
            self.montoniza(self.lista, n, i)

        for i in range(n-1, 0, -1):
            # intercambiamos
            self.lista[i], self.lista[0] = self.lista[0], self.lista[i]
            self.montoniza(self.lista,i, 0)
            
            
        return self.lista


if __name__ == '__main__':

    Lista = [-10, 2, 4, 6, 90, 2, -5]
    ClaseLista = Priority_Queue()
    try:
        assert ClaseLista.heapsort(Lista) == [-10, -5, 2, 2, 4, 6, 90]
    except (AssertionError):
        print("Error en heapsort")
        print(" ")
        print("Resultado:")
        ClaseLista.Mostrar()
        print("Resultado correcto:")
        print("-10,-5,2,2,4,6,90")
        print(" ")
    else:
        print("-heapsort OK")

    try:
        assert ClaseLista.push(0) == [-10, -5, 0, 2, 2, 4, 6, 90]
    except (AssertionError):
        print("Error en el push")
        print(" ")
        print("Resultado:")
        ClaseLista.Mostrar()
        print("Resultado correcto:")
        print("-10,-5,0,2,2,4,6,90")
        print(" ")
    else:
        print("-push OK")
    try:
        assert ClaseLista.pop() == [-5, 0, 2, 2, 4, 6, 90]
    except (AssertionError):
        print("Error en el pop")
        print(" ")
        print("Resultado:")
        ClaseLista.Mostrar()
        print("Resultado correcto:")
        print("-5,0,2,2,4,6,90")
        print(" ")
    else:
        print("-pop OK")

    try:
        assert ClaseLista.top() == -5
    except (AssertionError):
        print("Error en el top")
        print(" ")
        print("Resultado:")
        ClaseLista.Mostrar()
        print("Resultado correcto:")
        print("-5")
        print(" ")
    else:
        print("-top OK")
    try:
        assert str(ClaseLista)== "-5,0,2,2,4,6,90,"
    except (AssertionError):
        print("Error en el str()")
        print(" ")
        print("Resultado:")
        print(str(ClaseLista))
        print("Resultado correcto:")
        print("-5,0,2,2,4,6,90,")
        print(" ")
    else:
        print("-str OK")
