#include <iostream>
#include <vector>
#include "cifras.h"
using namespace std;

/**
 * @brief Lee los números que serán usados.
 * @param n Número de números a leer.
 * @return Vector de números leidos.
 */
vector<int> leerNumeros (int n=6) {
    vector<int> numeros(n);
    bool tope = false;
    for (int i=0; i<n && !tope; ++i) {
	int leido;
	cin >> leido;
    if (cin.good()) {
	    numeros[i] = leido;
    } else {
        tope = true;
    }
    }
    return numeros;
}

int main() {
    // Lee números
    int nuevo;
    int meta;
    
    cout << "Introduce meta a resolver: ";
    cin >> meta;

    cout << "Introduce números: ";
    vector<int> leidos (leerNumeros());

    
    // Resuelve el problema
    Cifras cifras(leidos);
    if (cifras.resuelve(meta))    
        cout << "Solución\n";
    else
        cout << "Aproximación\n";
	
    cifras.escribeOperaciones();
}
