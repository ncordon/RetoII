#ifndef CLASS
#define CLASS

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdlib.h>

class Cifras {
private:
    
    /**
     * Cola/Pila con los n�meros que deben ser probados.
     */
    std::vector<int> numeros;
  
#ifndef GRUPOS
    /**
     * TDA Cuenta. Representa una operaci�n binaria, concretamente
     * una suma, resta, multiplicaci�n o divisi�n. Permite adem�s
     * almacenar el resultado.
     */
    struct Cuenta {
        int primero;
        int segundo;
        char operador;
        int resultado;
    };
    
    /**
     * Pila en la que se guardan las operaciones que se han realizado,
     * para mostrarlas luego por pantalla.
     */
    std::vector<Cuenta> operaciones;
  
    /**
     * Almacena la mejor aproximaci�n hasta el momento y las operaciones
     * que requiere llegar a ese resultado.
     */
    int mejor;
    std::vector<Cuenta> mejor_operaciones;
  
    /**
     * @brief Normalizador de operaciones realizadas
     * 
     * Permite dejar en operaciones s�lo aquellas que han sido estrictamente
     * necesarias para llegar a meta
     * 
     */
    void normalizaOperaciones();
  
    /**
     * @brief Permite buscar el origen de dos operandos dados
     * 
     * Funci�n recursiva que busca para una Cuenta dada de qu� otras operaciones 
     * derivan sus operandos, hasta que llega a la ra�z de los mismos, 
     * y las apila a partir de pos_escribir 
     * 
     */
    void buscaOperandos(Cuenta unaCuenta, int& pos_escribir);
  
#endif
  
    /**
     * C�digos de las operaciones permitidas y n�mero de operaciones.
     * N�tese el orden de prioridad de las operaciones que reducen para optimizar
     */
    static const int SUM = 2;
    static const int RES = 0;
    static const int MUL = 3;
    static const int DIV = 1;
    static const int NOP = 4;
  
    /**
     * @brief Resuelve recursivamente para un n�mero dado.
     * @return Verdadero si hay soluci�n.
     */
    bool resuelve_rec (int meta, int size);
  
#ifdef GRUPOS
    /**
     * N�mero hasta el que se busca.
     */
    static const int BUSCADOS = 1000;
  
    /**
     * @brief Vector que contiene los n�meros de 3 cifras.
     * Verdadero si el n�mero ya ha sido encontrado.
     */
    std::vector<bool> encontrado;
  
    /**
     * @brief Cantidad de n�meros encontrados actualmente
     */
    int total_encontrados;
  
    /**
     * Marca como encontrado el n�mero n.
     * @param N�mero a marcar como encontrado.
     * @return Verdadero si ha encontrado todos.
     */
    bool marcar (int n);
#endif
  
public:
#ifdef GRUPOS
    /**
     * Imprime los que faltan por marcar.
     */
    void imprime_restantes ();
  
    /**
     * Comprueba que est�n todos marcados.
     */
    bool todos_marcados ();
#endif
  
    /**
     * @brief Constructor. Selecciona un conjunto de n�meros aleatorio.
     * Entre los n�meros [1,2,3,4,5,6,7,8,9,10,25,50,75,100], escoge seis.
     */
    Cifras ();
  
    /**
     * @brief Constructor. Dado un vector de n�meros.
     */
    Cifras (std::vector<int> numeros);
  
    /**
     * @brief Une dos cifras en una usando la operaci�n indicada.
     * @param a Primera cifra.
     * @param b Segunda cifra.
     * @param codop C�digo de operaci�n que se realizar� entre ellas.
     * @pre La operaci�n se puede realizar produciendo un entero no negativo.
     * @pre Es un n�mero de operaci�n v�lido.
     */
    int calcula (int a, int b, int codop);
  
    /**
     * @brief Muestra las operaciones para llegar a la soluci�n.
     * Las operaciones se encontraban en la pila de operaciones.
     */
    void escribeOperaciones ();
  
    /**
     * @brief Resuelve para un n�mero dado.
     * @param meta N�mero buscado.
     * @return Verdadero si hay soluci�n.
     */
    bool resuelve (int meta = 0);
    
    #ifndef GRUPOS
    /**
     * Sobrecarga del operador << para salida de datos del TDA Cuenta
     */
    friend std::ostream& operator<<(std::ostream& salida, const Cifras::Cuenta& operacion);
    #endif
};

const char SIMBOLOS[] = "-/+*";


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
