#include "cifras.h"
using namespace std;


Cifras::Cifras (vector<int> introducidos) {
    // Introduce los números en la doble cola.
    deque<int> numeros;
    int size = introducidos.size();
    for (int i=0; i<size; ++i)
	numeros.push_back(introducidos[i]);

    this->numeros = numeros;
}


int Cifras::calcula (int a, int b, int codop) {
    switch (codop) {
    case SUM: return a+b;
    case RES: return a-b;
    case MUL: return a*b;
    case DIV: return a/b;
    }
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
    resuelve_rec(meta);
}

bool Cifras::resuelve_rec (int meta) {
    int size = numeros.size();
    if (size < 2) return false;
    
    // Toma el primer número disponible
    for (int i=0; i<size; ++i) {
	//cerr << "Sale " << numeros.front() << endl;
	int a = numeros.front();
	numeros.pop_front();
	
	// Toma el segundo número disponible
	for (int j=0; j<size; ++j) {
	    //cerr << "Sale " << numeros.front() << endl;
	    int b = numeros.front(); 
	    numeros.pop_front();

	    // Y prueba sobre ellos todas las operaciones
	    for (int op=0; op<NOP; ++op) {
		// Comprueba que la operación sea válida
		cerr << "Operación: " << a << SIMBOLOS[op] << b << endl;

		bool negativo = (a<b and op==RES);
		bool indivisible = ((b==0 or a%b != 0) and op==DIV);
		bool cero_trivial = (a==0);
		if (negativo or indivisible or cero_trivial)
		    continue;

		// Comprueba que la operación sea útil
		int resultado = calcula(a,b,op);
		bool trivial = (resultado == a or resultado == b);
		bool overflow = (resultado < 0);
		if (trivial or overflow)
		    continue;

		// Calcula y guarda la operación.
		operaciones.push_back(aString(a));
		operaciones.push_back(aString(SIMBOLOS[op]));
		operaciones.push_back(aString(b));
		operaciones.push_back("=");
		operaciones.push_back(aString(resultado));
		operaciones.push_back("\n");

		// Intenta resolver con el nuevo número.
		if (resultado == meta)
		    return true;
		
		//cerr << "Entra " << resultado << endl;
		numeros.push_back(resultado);		
		if (resuelve_rec(meta))
		    return true;
		
		// Sigue probando
		//cerr << "Sale " << numeros.back() << " que debería ser " << resultado << endl;

		numeros.pop_back();

		int tirarI; char tirarC;
		operaciones.pop_back();
		operaciones.pop_back();
		operaciones.pop_back();
		operaciones.pop_back();
		operaciones.pop_back();
		operaciones.pop_back();
	    }
	   
	    //cerr << "Entra " << b << endl;
	    numeros.push_back(b);
	}
	
	//cerr << "Entra " << a << endl;
	numeros.push_back(a);
    }
}


void Cifras::escribeOperaciones() {
    cout << "Solución\n";
    while (!operaciones.empty()) {
	cout << operaciones.front();
	operaciones.pop_front();
    }
}
