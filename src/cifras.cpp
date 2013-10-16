#include "cifras.h"
using namespace std;


Cifras::Cifras (vector<int> introducidos) :mejor(-1) {
    // Introduce los números en la doble cola.
    vector<int> numeros;
    int size = introducidos.size();
    for (int i=0; i<size; ++i)
	numeros.push_back(introducidos[i]);

    this->numeros = numeros;
}


int Cifras::calcula (int a, int b, int codop) {
    switch (codop) {
      case SUM: return a+b; break;
      case RES: return a-b; break;
      case MUL: return a*b; break;
      case DIV: return a/b; break;
    }
}

bool Cifras::resuelve (int meta) {
    // Empieza comprobando que el número buscado no esté entre los dados.
    for (vector<int>::iterator it = numeros.begin(); it != numeros.end(); ++it)
	if (*it == meta) {
	    mejor_operaciones.push_back(aString(meta));
	    mejor_operaciones.push_back("\n");
	    return true;
	}
    
    // Resuelve de forma recursiva todas las posibilidades.
    resuelve_rec(meta);
}

bool Cifras::resuelve_rec (int meta) {
    int size = numeros.size();
    if (size < 2) return false;
    
    // Toma el primer número disponible
    for (int i=0; i<size-1; ++i) {
	//cerr << "Sale " << numeros.front() << endl;
	int a = numeros[i];
	
	if (!(a==0))
	  numeros.erase(numeros.begin()+i);
	else
	  continue;
	
	// Toma el segundo número disponible
	for (int j=i; j<size-1; ++j) {
	    //cerr << "Sale " << numeros.front() << endl;
	    int b = numeros[j];
	    
	    if (!(b==0))
	      numeros.erase(numeros.begin()+j);
	    else
	      continue;
	    
	    // Y prueba sobre ellos todas las operaciones
	    for (int op=0; op<NOP; ++op) {
		// Comprueba que la operación sea válida
		////
		//cerr << "Operación: " << a << SIMBOLOS[op] << b << endl;

		int c=a;
		int d=b;
		
		// Cogemos siempre c como el mayor de ambos
		if (a<b){
		  d=a;
		  c=b;
		}
		
		bool indivisible = ((c%d != 0) and op==DIV);
		if (indivisible)
		  continue;
		// Comprueba que la operación sea útil
		int resultado = calcula(c,d,op);
		bool trivial = (resultado == a or resultado == b);
		bool zero = (resultado == 0);
		bool overflow = (resultado < 0);
		if (trivial or overflow or zero)
		    continue;

		// Calcula y guarda la operación.
		operaciones.push_back(aString(c));
		operaciones.push_back(aString(SIMBOLOS[op]));
		operaciones.push_back(aString(d));
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
		
		//cerr << "Entra " << resultado << endl;
		numeros.push_back(resultado);
		
		if (resuelve_rec(meta))
		    return true;
		
		// Sigue probando
		//cerr << "Sale " << numeros.back() << " que debería ser " << resultado << endl;
		
		// Saco resultado
		numeros.pop_back();
		
		// Saca las operaciones
		operaciones.pop_back();
		operaciones.pop_back();
		operaciones.pop_back();
		operaciones.pop_back();
		operaciones.pop_back();
		operaciones.pop_back();
	    }
	   
	    //cerr << "Entra " << b << endl;
	    numeros.insert(numeros.begin()+j,b);
	}
	
	//cerr << "Entra " << a << endl;
	numeros.insert(numeros.begin()+i,a);
    }
}


void Cifras::escribeOperaciones() {
	for(vector<string>::iterator it=mejor_operaciones.begin(); it!=mejor_operaciones.end(); it++)
		cout << *it;
}
