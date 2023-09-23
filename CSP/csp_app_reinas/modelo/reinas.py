from problema_csp import ProblemaCSP

class ColeradoGrafos(ProblemaCSP):
    """Clase que define el problema de colorear mapas con 4 colores"""

    def __init__(self, provincias,vecindades,colores):
        ProblemaCSP.__init__(self, len(provincias))
        self._colores=colores
        self._provincias = provincias
        #diccionario:
        self._conjunto={}
        
        lista=[]
        #insertamos las vencidades de cada vecino
        for p in provincias:
            for p2,v in vecindades:
                
                if p==p2:
                    lista.append(v)
                elif p==v:
                    lista.append(p2)
                  
            self._conjunto[p]=lista
            lista=[]
        self._inicializa_dominio()

    def consistente(self, provincia1, color1, provincia2, color2):
        """Es consistente cuando las 2 provincias vecinas no coinciden en color"""
    
        return color1 != color2 

    def relacionadas(self, provincia1, provincia2):
        
        """Comprobamos si están relacionadas, es decir, si son vecinas"""
        #print(provincia1)
        vecinos=self._conjunto.get(self._provincias[provincia1])
        bandera=False
        for p1 in vecinos:
            if p1==self._provincias[provincia2]:
                bandera=True
                
        return bandera

    def _inicializa_dominio(self):
        
        for i in range(len(self._provincias)):
            
            """['R', 'A', 'N', 'V'],['y', 'g', 'r', 'b']"""
            if(self._colores==4):
                self._dominio[i] = ['y', 'g', 'r', 'b']
            elif(self._colores==3):
                self._dominio[i] = ['g', 'r', 'b']


class ReinasCSP(ProblemaCSP):
    """Clase que define el problema de las N reinas, colocarlas en un tablero sin amenazarse."""

    def __init__(self, num_variables):
        ProblemaCSP.__init__(self, num_variables)
        self._inicializa_dominio()

    def consistente(self, var_1, val_1, var_2, val_2):
        """No coinciden ni en la misma columna ni diagonal."""
        return (val_1 != val_2 and abs(val_1-val_2) != abs(var_1-var_2))

    def relacionadas(self, var_1, var_2):
        """Para las reinas, todas las variables relacionadas entre si en el grafo."""
        return var_1 != var_2

    def _inicializa_dominio(self):
        """Todas las reinas en todas las posibles columnas, [0, 1, ..., num_variables-1]."""
        for i in range(self._num_variables):
            self._dominio[i] = list(range(self._num_variables))


if __name__ == '__main__':
    r = ReinasCSP(4)

    assert r.size == 4

    dominio_ok = [[0, 1, 2, 3], [0, 1, 2, 3], [0, 1, 2, 3], [0, 1, 2, 3]]
    # Versión con diccionarios para el dominio
    # dominio_ok = {0: [0, 1, 2, 3], 1: [0, 1, 2, 3], 2: [0, 1, 2, 3], 3: [0, 1, 2, 3]}
    assert dominio_ok == r.dominio

    salida_ok = [False, True, True, False]
    salida = []
    for i in range(4):
        salida.append(r.consistente(0, 0, 3, i))
    assert salida_ok == salida

    salida_ok = [True, False, True, True]
    salida = []
    for i in range(4):
        salida.append(r.consistente(0, 1, 3, i))
    assert salida_ok == salida

    salida_ok = [True, False, True, False]
    salida = []
    for i in range(4):
        salida.append(r.consistente(1, 1, 3, i))
    assert salida_ok == salida

    salida_ok = [False, False, False, True]
    salida = []
    for i in range(4):
        salida.append(r.consistente(1, 1, 2, i))
    assert salida_ok == salida
