def imprime_reinas(solucion):
    print(solucion)


def imprime_sudoku(solucion):
    from math import sqrt
    tam = sqrt(len(solucion))
    sol = sorted(solucion)
    contador = 0
    for s in sol:
        print(s[1], end=' ')
        contador += 1
        if contador == tam:
            contador = 0
            print()


imprime = {'REINAS': imprime_reinas,
           'MAPA': imprime_reinas,
           'SUDOKU': imprime_sudoku}

     
def imprime_resultados(resultados):
    print('******************************************')
    print(resultados['problema'], 'de dimensión', resultados['dimension'])
    print('SOLUCION', resultados['algoritmo'], resultados['seleccion'], '\n')
    if not resultados['solucion']:
        print('No se encontro solución.')
    else:
        if resultados['ok']:
            imprime[resultados['problema']](resultados['solucion'])
            print('\nNumero de nodos expandidos:', resultados['num_nodos'])
            print('Tiempo empleado:', resultados['tiempo'])
        else:
            print('La solución encontrada no es consistente.')
            print('Revise el algoritmo en busca de algún error.')
    print('******************************************\n')
    
    
if __name__ == '__main__':
    pass
