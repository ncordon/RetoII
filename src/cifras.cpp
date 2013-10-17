#include "cifras.h"
using namespace std;
typedef int (*Operacion)(int a, int b); 


Cifras::Cifras (vector<int> introducidos) {
    #ifndef GRUPOS
    // Primera aproximación
    mejor = -1;
    #endif

    #ifdef GRUPOS
    // Números marcados
    total_encontrados = 0;
    vector<bool> encontrado_inicial(BUSCADOS);
    for (int i=0; i<BUSCADOS; ++i)
	encontrado_inicial[i] = false;
    encontrado = encontrado_inicial;

    // El cero se marca por defecto
    marcar(0);
    #endif

    // Introduce los números en la doble cola.
    vector<int> numeros;
    int size = introducidos.size();
    for (int i=0; i<size; ++i)
        numeros.push_back(introducidos[i]);

    this->numeros = numeros;
}




bool Cifras::resuelve (int meta) {
    // Empieza comprobando que el número buscado no esté entre los dados.
    for (vector<int>::iterator it = numeros.begin(); it != numeros.end(); ++it) {
	
        #ifndef GRUPOS
	if (*it == meta) {
	    mejor_operaciones.push_back(aString(meta) + "\n");
	    return true;
	}
        #endif

        #ifdef GRUPOS
	marcar(*it);
        #endif

    }

    // Resuelve de forma recursiva todas las posibilidades.
    return resuelve_rec(meta);
}




bool Cifras::resuelve_rec (int meta) {
    // Operaciones
    Operacion calcula[] = {
	[](int a, int b){ return a-b; },
	[](int a, int b){ return a/b; },
	[](int a, int b){ return a+b; },
	[](int a, int b){ return a*b; }
    };
    
    int size = numeros.size();
    if (size < 2) return false;

    // Toma el primer número disponible
    for (int i=0; i<size-1; ++i) {
	int a = numeros[i];
	
	if (!(a==0))
	    numeros.erase(numeros.begin()+i);
	else
	    continue;
	
	// Toma el segundo número disponible
	for (int j=i; j<size-1; ++j) {
	    int b = numeros[j];
	    
	    if (!(b==0))
		numeros.erase(numeros.begin()+j);
	    else
		continue;
	    
	    // Y prueba sobre ellos todas las operaciones
	    for (int op=0; op<NOP; ++op) {
		int c=a;
		int d=b;
		
		// Cogemos siempre c como el mayor de ambos
		if (a<b){
		    d=a;
		    c=b;
		}
		
		// Comprueba que la operación sea válida
		bool indivisible = ((c%d != 0) and op==DIV);
		if (indivisible)
		    continue;

		// Comprueba que la operación sea útil
		int resultado = calcula[op](c,d);
		bool trivial = (resultado == a or resultado == b);
		bool zero = (resultado == 0);
		bool overflow = (resultado < 0);
		if (trivial or overflow or zero)
		    continue;

		// Calcula y guarda la operación.
		#ifndef GRUPOS
		operaciones.push_back(aString(c) + aString(SIMBOLOS[op]) + aString(d) + "=" + aString(resultado));
		#endif

		// Intenta resolver o mejorar con el nuevo número, sin pasarse
		#ifndef GRUPOS
		if ((meta-resultado) < (meta-mejor) && (meta-resultado)>=0) {
		    mejor = resultado;
		    mejor_operaciones = operaciones;
    
		    if (resultado == meta)
			return true;
		}
		#endif
		
		// Marca el nuevo resultado y comprueba si están todos marcados
		#ifdef GRUPOS
		if (marcar(resultado))
		    return true;
		#endif

		// Guarda el nuevo resultado
		numeros.push_back(resultado);
		
		if (resuelve_rec(meta))
		    return true;
		
		// Saco resultado y operaciones
		numeros.pop_back();

                #ifndef GRUPOS
		operaciones.pop_back();
		#endif
	    }
	   
       	    numeros.insert(numeros.begin()+j,b);
	}
	
	numeros.insert(numeros.begin()+i,a);
    }

    return false;
}

#ifndef GRUPOS
void Cifras::escribeOperaciones() {
    for(vector<string>::iterator it=mejor_operaciones.begin(); it!=mejor_operaciones.end(); it++)
	cout << *it << "\n";
}
#endif

#ifdef GRUPOS
bool Cifras::marcar(int n) {
    if (n<1000 and !encontrado[n]) {
	encontrado[n] = true;
	--total_encontrados;
	if (total_encontrados == BUSCADOS)
	    return true;
    }
    
    return false;
}
#endif

#ifdef GRUPOS
void Cifras::imprime_restantes () {
    for (int i=0; i<BUSCADOS; ++i)
	if (!encontrado[i])
	    cout << i << ' ';
    cout << endl;
}
#endif

#ifdef GRUPOS
bool Cifras::todos_marcados () {
    bool todos = true;
    for (int i=0; i<BUSCADOS and todos; ++i)
	todos = encontrado[i];
    return todos;
}
#endif
