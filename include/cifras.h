#ifndef CLASS
#define CLASS

#include <string>
//#include <deque>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdlib.h>


class Cifras {
private:
    /**
     * Cola/Pila con los números que deben ser probados.
     */
    std::vector<int> numeros;

    /**
     * Pila en la que se guardan las operaciones que se han realizado,
     * para mostrarlas luego por pantalla.
     */
    std::vector<std::string> operaciones;
	
	/**
	 * Almacena la mejor aproximación hasta el momento y las operaciones
	 * que requiere llegar a ese resultado.
	 */
	int mejor;
	std::vector<std::string> mejor_operaciones;

    /**
     * Códigos de las operaciones permitidas y número de operaciones.
     * Nótese el orden de prioridad de las operaciones que reducen para optimizar
     */
    static const int SUM = 2;
    static const int RES = 0;
    static const int MUL = 3;
    static const int DIV = 1;
    static const int NOP = 4;

    /**
     * @brief Resuelve recursivamente para un número dado.
     * @return Verdadero si hay solución.
     */
    bool resuelve_rec (int meta);

public:
    /**
     * @brief Constructor. Selecciona un conjunto de números aleatorio.
     * Entre los números [1,2,3,4,5,6,7,8,9,10,25,50,75,100], escoge seis.
     */
    Cifras ();
    
    /**
     * @brief Constructor. Dado un vector de números.
     */
    Cifras (std::vector<int> numeros);

    /**
     * @brief Une dos cifras en una usando la operación indicada.
     * @param a Primera cifra.
     * @param b Segunda cifra.
     * @param codop Código de operación que se realizará entre ellas.
     * @pre La operación se puede realizar produciendo un entero no negativo.
     * @pre Es un número de operación válido.
     */
    int calcula (int a, int b, int codop);

    /**
     * @brief Muestra las operaciones para llegar a la solución.
     * Las operaciones se encontraban en la pila de operaciones.
     */
    void escribeOperaciones ();

    /**
     * @brief Resuelve para un número dado.
     * @param meta Número buscado.
     * @return Verdadero si hay solución.
     */
    bool resuelve (int meta);
};

const std::string SIMBOLOS = "-/+*";


/**
 * Auxiliar que transforma un int en string.
 */
inline std::string aString (int n) {
    std::stringstream ss;
    ss << n;
    return ss.str();
}
/**
 * Auxiliar que transforma un char en string.
 */
inline std::string aString (char c) {
    std::stringstream ss;
    ss << c;
    return ss.str();
}

inline std::string operator+(std::string a, std::string b) {
	return a.append(b);
}

#endif

