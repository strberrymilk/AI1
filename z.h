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
#include <algorithm> // usar función min()

using namespace std;

/*
Función que se encarga de construir
el arreglo Z de una cadena
*/
inline vector<int> construirZ(const string& texto) {
    int n = static_cast<int>(texto.size()); // guarda el tamaño total del texto

    vector<int> z(n, 0); // crea Z con n posiciones iniciadas en cero

    int L = 0; // límite izquierdo de la ventana Z actual
    int R = 0; // límite derecho de la ventana Z actual

    // i inicia en 1 y avanza hasta n-1
    for (int i = 1; i < n; i++) {
        if (i <= R) { // si i sigue dentro de la ventana Z conocida
            z[i] = min( // reutiliza la coincidencia
                R - i + 1, // máximo espacio disponible antes de salir de R
                z[i - L]); // valor equivalente calculado dentro de Z
        }

        while (i + z[i] < n && texto[z[i]] == texto[i + z[i]]) { // compara el inicio del texto con la posición actual
            z[i]++; // aumenta la coincidencia si ambos caracteres son iguales
        }
        if (i + z[i] - 1 > R) { // si esta coincidencia llega más lejos que R
            L = i; // mueve L al inicio de la nueva ventana
            R = i + z[i] - 1; // mueve R al último carácter que coincidió
        }
    }

    return z; // retorna el arreglo Z terminado
}

/*
Función que busca un patrón dentro de una transmisión usando
Z Algorithm
*/
inline int buscarConZ(const string& texto, const string& patron) {
    if (patron.empty()) { // si el patrón está vacío
        return -1; // retorna menos 1
    }

    string combinado = patron + "$" + texto; // une patrón y texto para aplicar Z una sola vez
    vector<int> z = construirZ(combinado); // calcula Z sobre la cadena combinada

    int inicioTexto = static_cast<int>(patron.size()) + 1; // salta el patrón y el símbolo $

    for (int i = inicioTexto; // inicio i justo donde inicia la transmisión
        i < static_cast<int>(combinado.size()); // continúa mientras i siga dentro de la cadena
        i++) // avanza una posición en cada vuelta
        {
            if (z[i] >= static_cast<int>(patron.size())) { // si la coincidencia tiene el tamaño del patrón
                int posicionBaseCero = i - inicioTexto; // convierte i a una posición dentro de la transmisión

                return posicionBaseCero + 1;
            }
        }
        return -1; // si el patrón no se encuentra
}

/*
Función que busca un mcode y muestra el resultado
True
False
*/
inline void imprimirResultadoZ(
    const string& transmision,
    const string& mcode
) {
    int posicion = buscarConZ(transmision, mcode); // busca el mcode dentro de la transmisión

    if (posicion == -1) { // si no encuentra nada
        cout << "false" << endl; // imprime false
    } else {
        cout << "true " << posicion << endl; // imprime true y posición encontrada
    }
}

/*
Ejecuta todas las comparaciones necesarias de la parte 1
(no se usa desde main, la parte 1 se resuelve con KMP; se deja
disponible por si se necesita comparar con el algoritmo Z)
*/
inline void ejecutarParte1Z(
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
    imprimirResultadoZ(transmision2, mcode1);
    imprimirResultadoZ(transmision2, mcode2);
    imprimirResultadoZ(transmision2, mcode3);
}
#endif