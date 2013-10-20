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
	    Cuenta encontrada = {meta, meta, ' '};
	    mejor_operaciones.push_back(encontrada);
	    
	    return true;
	}
        #endif
    
        #ifdef GRUPOS
	marcar(*it);
        #endif
    }
  
    // Resuelve de forma recursiva todas las posibilidades.
    bool resuelto=resuelve_rec(meta, numeros.size());
  
    #ifndef GRUPOS
    normalizaOperaciones();
    #endif
  
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
    
    #ifndef GRUPOS
    Cuenta opActual;
    #endif
  
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
	    if (b != 0)
		numeros[j] = numeros[size-2];
	    else
		continue;
      
	    // Y prueba sobre ellos todas las operaciones
	    for (int op=0; op<NOP; ++op) {
		// Cogemos siempre c como el mayor de ambos
		int c=(a>b?a:b), d=(c==a?b:a);
        
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
		opActual = {c, d, SIMBOLOS[op], resultado};
		operaciones.push_back(opActual);
            
		// Intenta resolver o mejorar con el nuevo número, sin pasarse
		if ((meta-resultado) < (meta-mejor) && (meta-resultado) >= 0) {
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
              
		// Guarda el nuevo resultado y sigue buscando
		numeros[size-2] = resultado;
		if (resuelve_rec(meta,size-1))
		    return true;
        
                #ifndef GRUPOS
		//Saca las operaciones
		operaciones.pop_back();
                #endif
	    }
	    numeros[size-2]=numeros[j];
	    numeros[j]=b;
	}
	numeros[i]=a;
    }
    return false;
}

#ifndef GRUPOS
void Cifras::escribeOperaciones() {    
    vector<Cuenta>::iterator it;
  
    for(it=mejor_operaciones.begin(); it!=mejor_operaciones.end(); it++){
	cout << *it << endl;
    }
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

#ifndef GRUPOS
void Cifras::normalizaOperaciones() {
    int size = mejor_operaciones.size();
    int pos_escribir = size - 2;
    
    if (pos_escribir >= 0){
	buscaOperandos (mejor_operaciones[size-1],pos_escribir);
  
	mejor_operaciones.erase(mejor_operaciones.begin(),
				mejor_operaciones.begin() + pos_escribir + 1);   
    }
}

void Cifras::buscaOperandos(Cuenta unaCuenta, int& pos_escribir){
    bool uno_encontrado=false, otro_encontrado=false;
    int j = pos_escribir;
    int un_operando = unaCuenta.primero,
        otro_operando = unaCuenta.segundo;
        
    while ((!uno_encontrado || !otro_encontrado) && j>=0){
	if ((mejor_operaciones[j].resultado == un_operando) || 
	    (mejor_operaciones[j].resultado == otro_operando)){
      
	    if (uno_encontrado)
		otro_encontrado=true;
	    else
		uno_encontrado=true;

	    Cuenta aux(mejor_operaciones[j]);
	    mejor_operaciones[j]=mejor_operaciones[pos_escribir];
	    mejor_operaciones[pos_escribir]=aux;
	    pos_escribir--;
      
	    buscaOperandos(mejor_operaciones[pos_escribir+1], pos_escribir);
	    j = pos_escribir;
	}
	else
	    j--;
    }
}


std::ostream& operator<<(std::ostream& salida, const Cifras::Cuenta& operacion) {
    if (operacion.operador != ' ')
        salida << operacion.primero << operacion.operador << operacion.segundo << '=' << operacion.resultado;
    else 
        salida << operacion.primero;
    
    return salida;
}
#endif
