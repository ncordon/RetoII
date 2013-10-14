#include <stdlib.h>
#include "cifras.h"
using namespace std;

typedef int (*Operacion)(int a, int b);

Cifras::Cifras (vector<int> introducidos) {
    // Introduce los números en la doble cola.
    deque<int> numeros;
    int size = introducidos.size();
    for (int i=0; i<size; ++i)
    numeros.push_back(introducidos[i]);

    this->numeros = numeros;
}

bool Cifras::resuelve (int meta) {
    // Empieza comprobando que el número buscado no esté entre los dados.
    for (deque<int>::iterator it = numeros.begin(); it != numeros.end(); ++it)
        if (*it == meta) {
            operaciones.push_back("Solución:");
            operaciones.push_back(aString(meta));
            operaciones.push_back("\n");
            return true;
        }
    
    // Resuelve de forma recursiva todas las posibilidades.
    return resuelve_rec(meta);
}

bool Cifras::resuelve_rec (int meta) {
    Operacion calcula[] = {
		[](int a, int b){ return a-b; }, 
		[](int a, int b){ return a/b; }, 
		[](int a, int b){ return a+b; }, 
		[](int a, int b){ return a*b; }
    };
    
    int size = numeros.size();
    if (size < 2) return false;
    
    // Toma el primer número disponible
    for (int i=0; i<size; ++i) {
        //cerr << "Sale " << numeros.front() << endl;
        int a = numeros.front();
        numeros.pop_front();
	
        // Toma el segundo número disponible
        for (int j=0; j<size-1; ++j) {
            int b = numeros.front(); 
            numeros.pop_front();

            // Y prueba sobre ellos todas las operaciones
            for (int op=0; op<NOP; ++op) {
                // Comprueba que la operación sea válida

                bool negativo = (a<b and op==RES);
                bool indivisible = ((b==0 or a%b != 0) and op==DIV);
                bool cero_trivial = (a==0);
                if (negativo or indivisible or cero_trivial)
                    continue;

                // Comprueba que la operación sea útil
                int resultado = calcula[op](a,b);
                bool trivial = (resultado == a or resultado == b);
                bool zero = (resultado == 0);
                bool overflow = (resultado < 0);
                if (trivial or overflow or zero)
                    continue;

                // Calcula y guarda la operación.
                operaciones.push_back(aString(a));
                operaciones.push_back(aString(SIMBOLOS[op]));
                operaciones.push_back(aString(b));
                operaciones.push_back("=");
                operaciones.push_back(aString(resultado));
                operaciones.push_back("\n");

                // Intenta resolver con el nuevo número.
                if (abs(resultado - meta) < abs(mejor - meta)) {
                    mejor = resultado;
                    mejor_operaciones = operaciones;
                
                    if (resultado == meta)
                        return true;
                }

                numeros.push_back(resultado);
                if (resuelve_rec(meta))
                    return true;

                // Sigue probando
                numeros.pop_back();

                operaciones.pop_back();
                operaciones.pop_back();
                operaciones.pop_back();
                operaciones.pop_back();
                operaciones.pop_back();
                operaciones.pop_back();
            }
	   
            numeros.push_back(b);
        }
	
        numeros.push_back(a);
    }

    return false;
}


void Cifras::escribeOperaciones() {
    while (!mejor_operaciones.empty()) {
        cout << mejor_operaciones.front();
        mejor_operaciones.pop_front();
    }
}