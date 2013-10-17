#include <iostream>
#include <vector>
#include "cifras.h"
using namespace std;

/**
 * @brief Lee los números que serán usados.
 * @param n Número de números a leer.
 * @return Vector de números leidos.
 */
vector<int> leerNumeros () {
    vector<int> numeros;
    int leido;
    while (cin >> leido)
	numeros.push_back(leido);
    
    return numeros;
}

int main() {
    // Lee números
    int meta; 
    cout << "Introduce meta a resolver: ";
    cin >> meta;
    cout << "Introduce números: ";
    vector<int> leidos (leerNumeros());
    
    // Resuelve el problema
    cout << "Resolviendo..." << endl;
    Cifras cifras(leidos);
    if (cifras.resuelve(meta))    
        cout << "Solución" << endl;
    else
        cout << "Aproximación" << endl;
    
    cifras.escribeOperaciones();
}
