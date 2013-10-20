#include <iostream>
#include <vector>
#include "cifras.h"
using namespace std;

/**
 * @brief Lee los n�meros que ser�n usados.
 * @param n N�mero de n�meros a leer.
 * @return Vector de n�meros leidos.
 */
vector<int> leerNumeros () {
    vector<int> numeros;
    int leido;
    while (cin >> leido)
	numeros.push_back(leido);
    
    return numeros;
}

int main() {
    // Lee n�meros
    #ifndef GRUPOS
    int meta;
    cout << "Introduce meta a resolver: ";
    cin >> meta;
    #endif

    cout << "Introduce n�meros: ";
    vector<int> leidos (leerNumeros());
    
    // Resuelve el problema
    cout << "Resolviendo..." << endl;
    Cifras cifras(leidos);

    #ifndef GRUPOS
    if (cifras.resuelve(meta))
        cout << "Soluci�n" << endl;
    else
        cout << "Aproximaci�n" << endl;
    
    cifras.escribeOperaciones();
    #endif

    #ifdef GRUPOS
    if (cifras.resuelve() or cifras.todos_marcados())
	cout << "Marcados todos" << endl;
    else {
	cout << "Faltaron por marcar:" << endl;
	cifras.imprime_restantes();
    }
    #endif
}
