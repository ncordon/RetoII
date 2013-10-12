# -*- coding: utf-8 -*-
#!/bin/python3
# Precalculador
# Precalcula la suma y producto de todas las parejas de números
# hasta un máximo dado y los escribe como una matriz en C++ lista
# para insertarse en el código.
# USO: python precalculador.py > precalculos.h
# CUIDADO: Con python2 el programa escribe incorrectamente. Debe usarse python3.

# A MEJORAR: Escribe una matriz completa, en lugar de escribir una matriz triangular
#  lo que le ahorraría la mitad de peso.

MAXIMO = 1000

# Inicio de la cabecera
print('''
#ifndef PRECALCULOS
#define PRECALCULOS

''')

print("const int MAXIMO = ", MAXIMO, ";")

# Matriz de sumas: inicio
print("const int SUMAS[",MAXIMO,"][",MAXIMO,"] = {")

for i in range(MAXIMO):
    print("{",end="")
    for j in range(MAXIMO):
        print(i+j,end="")
        if j != MAXIMO-1: print(",",end="")
    print("}",end="")
    if i != MAXIMO-1: print(",")

# Matriz de sumas: final
print("};")


# Matriz de productos: inicio
print("const int PRODUCTOS[",MAXIMO,"][",MAXIMO,"] = {")

for i in range(MAXIMO):
    print("{",end="")
    for j in range(MAXIMO):
        print(i*j,end="")
        if j != MAXIMO-1: print(",",end="")
    print("}",end="")
    if i != MAXIMO-1: print(",")

# Matriz de productos: final
print("};")


# Cierre de la cabecera
print('''
#endif
''')
