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
	    operaciones.push("Solución:");
	    operaciones.push(aString(meta));
	    operaciones.push("\n");
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
	int a = numeros.front();
	numeros.pop_front();

	///////////////
	cout << "Primero: " << a << endl;
	for (deque<int>::iterator it = numeros.begin(); it != numeros.end(); ++it)
	     cerr << *it << ' ';
	cerr << endl;
	//////////////
	
	// Toma el segundo número disponible
	for (int j=0; j<size; ++j) {
	    int b = numeros.front(); 
	    numeros.pop_front();

	    ///////////////
	    cout << "Segundo: " << '('<<a<<','<<b<<')'<< endl;
	    for (deque<int>::iterator it = numeros.begin(); it != numeros.end(); ++it)
		cerr << *it << ' ';
	    cerr << endl;
	    //////////////

	    // Y prueba sobre ellos todas las operaciones
	    for (int op=0; op<NOP; ++op) {
		// Comprueba que la operación sea válida
		if ((a < b and op==RES) or ((b == 0 or a%b != 0) and op==DIV))
		    continue;

		// Calcula y guarda la operación.
		int resultado = calcula(a,b,op);
		operaciones.push(aString(a));
		operaciones.push(aString(SIMBOLOS[op]));
		operaciones.push(aString(b));
		operaciones.push("=");
		operaciones.push(aString(resultado));
		operaciones.push("\n");

		// Intenta resolver con el nuevo número.
		if (resultado == meta)
		    return true;
		numeros.push_back(resultado);		
		if (resuelve_rec(meta))
		    return true;
		
		// Sigue probando
		numeros.pop_back();
		int tirarI; char tirarC;
		operaciones.pop();
		operaciones.pop();
		operaciones.pop();
		operaciones.pop();
		operaciones.pop();
		operaciones.pop();
	    }
	   
	    numeros.push_back(b);
	}
	
	numeros.push_back(a);
    }
}


void Cifras::escribeOperaciones() {
    cout << "Solución\n";
    while (!operaciones.empty()) {
	cout << operaciones.front();
	operaciones.pop();
    }
}
