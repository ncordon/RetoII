#include "cifras.h"
using namespace std;
typedef int (*Operacion)(int a, int b); 


Cifras::Cifras (vector<int> introducidos) :mejor(-1) {
    // Introduce los números en la doble cola.
    vector<int> numeros;
    int size = introducidos.size();
    for (int i=0; i<size; ++i)
	numeros.push_back(introducidos[i]);

    this->numeros = numeros;
}

bool Cifras::resuelve (int meta) {
    // Empieza comprobando que el número buscado no esté entre los dados.
    for (vector<int>::iterator it = numeros.begin(); it != numeros.end(); ++it)
	if (*it == meta) {
	    mejor_operaciones.push_back(aString(meta) + "\n");
	    return true;
	}
    
    // Resuelve de forma recursiva todas las posibilidades.
    bool resuelto=resuelve_rec(meta, numeros.size());
    //normalizaOperaciones();
    
    return resuelto;
}

bool Cifras::resuelve_rec (int meta, int size) {
    // Operaciones
    Operacion calcula[] = {
	[](int a, int b){ return a-b; },
	[](int a, int b){ return a/b; },
	[](int a, int b){ return a+b; },
	[](int a, int b){ return a*b; }
    };
    
    if (size < 2) return false;

    // Toma el primer número disponible
    for (int i=0; i<size-1; ++i) {
	int a = numeros[i];
	    
	if (!(a==0))
	  numeros[i]=numeros[size-1];
	else
	  continue;
	
	// Toma el segundo número disponible
	for (int j=i; j<size-1; ++j) {
	    int b = numeros[j];
	    
	    if (!(b==0))
	      numeros[j]=numeros[size-2];
	    else
	      continue;
	    
	    // Y prueba sobre ellos todas las operaciones
	    for (int op=0; op<NOP; ++op) {
		// Comprueba que la operación sea válida

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
		int resultado = calcula[op](c,d);
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
		
		// Intenta resolver o mejorar con el nuevo número, sin pasarse
		if ((meta-resultado) < (meta-mejor) && (meta-resultado)>=0) {
			mejor = resultado;
			mejor_operaciones = operaciones;
    
			if (resultado == meta)
				return true;
		}
		
		numeros[size-2]=resultado;
		
		if (resuelve_rec(meta,size-1))
		    return true;
		
		// Saca las operaciones
		operaciones.pop_back();
		operaciones.pop_back();
		operaciones.pop_back();
		operaciones.pop_back();
		operaciones.pop_back();
		operaciones.pop_back();
	    }
	    numeros[size-2]=numeros[j];
	    numeros[j]=b;
	}
	numeros[size-1]=numeros[i];
	numeros[i]=a;
    }

    return false;
}


void Cifras::escribeOperaciones() {
      for(vector<string>::iterator it=mejor_operaciones.begin(); it!=mejor_operaciones.end(); it++)
		cout << *it;
}

/* 
void Cifras::normalizaOperaciones() {
      int tope=(operaciones.size()+1)/6;
      
      cerr << tope;
      
      cin.get();
      string n_buscar,otro_n_buscar;
      int posEscribir=(tope-2)*6;
      int i,j,k;
      int utiles=1;
      bool encontrado;
      
      for (i=tope-1;i>0;i--){
	cerr << "i: " <<i << endl; 
	n_buscar=operaciones[i*6];
	otro_n_buscar=operaciones[i*6+2];
	encontrado=false;
	
	for (j=i;j>0;j--){
	  cerr << "j: " << j<< endl; 
	  cerr << "generado " << operaciones[j*6-2] << endl;
	  cerr << "n_buscar" << n_buscar;
	  cin.get();
	  if (operaciones[j*6-2]==n_buscar ||
	      operaciones[j*6-2]==otro_n_buscar){
	    encontrado=true;
	    if (posEscribir!=(j-2)*6){
	      for (k=0;k<6;k++){
		operaciones[posEscribir+k]=operaciones[(j-2)*6+k];
	      }
	    }
	    utiles++;
	    cerr << utiles << endl;
	    posEscribir-=6;
	  }
	}
      }
      
      operaciones.erase(operaciones.begin(), operaciones.begin()+6*(tope-utiles));
}

*/