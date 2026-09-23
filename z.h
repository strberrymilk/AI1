/*
Implementación del algoritmo Z
Cesar Augusto Ramirez Davila - A01712439
23/09/2026
*/

#ifndef Z_H
#define Z_H


#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // usar funcion min()

using namespace std;

/* 
Funcion que se encarga de construir 
el arreglo Z de una cadena 
*/

inline vector<int> construirZ(const string& texto) {
    int n = static_cast<int>(texto.size()); // Guarda el tamano total del texto

    vector<int> z(n, 0); // Crea Z con n posiciones iniciadas en cero

    int L = 0; // Limite izquierdo de la ventana Z actual
    int R = 0; // Limite derecho de la ventana Z actual

    // i inicia en 1 y avanza hasta n-1
    for (int i = 1; i < n; i++) {
        if (i <= R) { // si i sigue dentro de la ventana Z conocida
            z[i] = min( // reutiliza la coincidencia
                R - i + 1, // maximo espacio dispnible antes de salir de R
                z[i - L]); // valor equivalente calculado dentro de Z
        }

        while ( i+z[i] < n && texto[z[i]] == texto[i+z[i]]) { // verifica que la comparacion siga dentro del texto y compara el inicio del texto con la posicion actual
            z[i]++; // aumenta la coincidencia si ambos caracteres son iguales
        } 
        if (i+z[i] - 1 > R ) { // si esta coincidencia llega mas lejos que R
            L = i; // Mueve L al inicio de la nueva eventana
            R = i + z[i] - 1; // mueve R al ultimo caracter que coincidio
        }
    }

    return z; // retorna el arreglo Z terminado
}


/*
Funcion que busca un patron dentro de una transmision usando
Z Algorithm
*/
inline int buscarConZ( const string& texto, const string& patron){
    

    if (patron.empty()){ // si el patron esta vacio
        return -1;       // retorna menos 1
    }

    string combinado = patron + "$" + texto; // Une patron y texto para aplicar Z una sola vez
    vector<int> z = construirZ(combinado); // calcula Z sobre la cadena combinada

    int inicioTexto = static_cast<int>(patron.size()) + 1; // salta el patron y el simbolo $

    for (int i = inicioTexto; // inicio i en  justo donde inicia la transmision
        i < static_cast<int>(combinado.size()); // continua mientras i siga dentro de la cadena
        i++) // avanza una posicion en cada vuelta
        {
            if (z[i] >= static_cast<int>(patron.size())) { // si la coincidencia tiene el tamano del patron
                int posicionBaseCero = i - inicioTexto; // convierte i a una pos dentro de la transmision

                return posicionBaseCero + 1;
            }
        }
        return -1; // si el patron no se encuentra
}



/*
Funcion que busca un mcode y muestra el resultado
True
False
*/
inline void imprimirResultadoZ(
    const string& transmision,
    const string& mcode
) {
    int posicion = buscarConZ(transmision, mcode); // busca el mcode dentro de la transmision

    if (posicion == -1) { // si no encuentra nada
        cout << "false" << endl; // imprime false
    } else {
        cout << "true " << posicion << endl; //imprime true y posicion encontrada
    }
}

/*
Ejecuta toas las comparaciones necesarias de la parte 1
*/

inline void ejecutarParte1(
    const string& transmision1,
    const string& transmision2,
    const string& mcode1,
    const string& mcode2,
    const string& mcode3
) {
    // busca los mcode desde transmision1
    imprimirResultadoZ(transmision1, mcode1);
    imprimirResultadoZ(transmision1, mcode2);
    imprimirResultadoZ(transmision1, mcode3);


    // busca los mcode desde transmision2
    imprimirResultadoZ(transmision2,mcode1);
    imprimirResultadoZ(transmision2, mcode2);
    imprimirResultadoZ(transmision2, mcode3);

}
#endif