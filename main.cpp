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
    for (int i=0; i<n; ++i) {
	int leido;
	cin >> leido;
	numeros[i] = leido;
    }
}

int main() {
    // Lee números
    vector<int> leidos;
    int nuevo;
    int meta;
    
    cout << "Introduce meta a resolver: ";
    cin >> meta;

    cout << "Introduce números: ";
    while (cin >> nuevo)
	leidos.push_back(nuevo);

    // Resuelve el problema
    Cifras cifras(leidos);
    cifras.resuelve(meta);
    cifras.escribeOperaciones();
}
