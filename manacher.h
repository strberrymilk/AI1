/*
Implementación del algoritmo Manacher
Cesar Augusto Ramirez Davila - A01712439
23/09/2026
*/

#ifndef MANACHER_H
#define MANACHER_H


#include <iostream>
#include <string>
#include <vector>
#include <utility>    // usar pair
#include <algorithm>  // usar funcion min()

using namespace std;


/*
Funcion que encuentra el palindromo mas largo
dentro de una cadena usando Manacher
*/

inline pair<int, int> manacher(const string& texto) {

    int n = static_cast<int>(texto.size()); // guarda el tamano total del texto

    if (n == 0) { // si el texto esta vacio

        return {0, 0}; // no existen posiciones para regresar
    }


    int mejorInicio = 0; // posicion donde inicia el mejor palindromo encontrado

    int mejorLongitud = 1; // un caracter solo ya cuenta como palindromo



/*
PALINDROMOS IMPARES
*/

    vector<int> d1(n, 0); // guarda el radio de cada palindromo impar

    int L = 0; // limite izquierdo del palindromo conocido

    int R = -1; // limite derecho, inicia en -1 porque aun no existe un rango


    // i recorre cada posicion del texto como posible centro
    for (int i = 0; i < n; i++) {

        int k; // radio del palindromo en la posicion actual


        if (i > R) { // si i esta fuera del rango conocido

            k = 1; // comienza desde 1 porque el centro ya es un palindromo
        }

        else { // si i se encuentra dentro del rango conocido

            k = min(
                d1[L + R - i], // reutiliza el valor de la posicion espejo
                R - i + 1      // evita que el radio pase de R
            );
        }


        while (
            i - k >= 0 &&                  // evita salir del texto por la izquierda
            i + k < n &&                   // evita salir del texto por la derecha
            texto[i - k] == texto[i + k]   // compara los caracteres a ambos lados
        ) {

            k++; // aumenta el radio mientras los caracteres sean iguales
        }


        d1[i] = k; // guarda el radio encontrado en la posicion i


        int longitudActual =
            2 * d1[i] - 1; // calcula la longitud del palindromo impar


        int inicioActual =
            i - d1[i] + 1; // calcula donde inicia el palindromo


        if (longitudActual > mejorLongitud) { // si encontro un palindromo mas largo

            mejorLongitud = longitudActual; // guarda la nueva longitud maxima

            mejorInicio = inicioActual; // guarda donde inicia
        }


        k--; // regresa a la ultima expansion que fue valida


        if (i + k > R) { // si el palindromo llega mas lejos que R

            L = i - k; // mueve L al nuevo limite izquierdo

            R = i + k; // mueve R al nuevo limite derecho
        }
    }


/*
PALINDROMOS PARES
*/

    vector<int> d2(n, 0); // guarda el radio de cada palindromo par

    L = 0; // reinicia el limite izquierdo

    R = -1; // reinicia el limite derecho


    // vuelve a recorrer cada posicion para buscar palindromos pares
    for (int i = 0; i < n; i++) {

        int k; // radio del palindromo actual


        if (i > R) { // si i esta fuera del rango conocido

            k = 0; // en palindromos pares el radio inicia en cero
        }

        else { // si i se encuentra dentro del rango conocido

            k = min(
                d2[L + R - i + 1], // reutiliza el valor de la posicion espejo
                R - i + 1          // evita que el radio pase de R
            );
        }


        while (
            i - k - 1 >= 0 &&                  // evita salir por la izquierda
            i + k < n &&                       // evita salir por la derecha
            texto[i - k - 1] == texto[i + k]   // compara ambos lados del centro
        ) {

            k++; // aumenta el radio si los caracteres coinciden
        }


        d2[i] = k; // guarda el radio encontrado


        int longitudActual =
            2 * d2[i]; // calcula la longitud del palindromo par


        int inicioActual =
            i - d2[i]; // calcula donde inicia el palindromo


        if (longitudActual > mejorLongitud) { // si encontro uno mas largo

            mejorLongitud = longitudActual; // actualiza la longitud maxima

            mejorInicio = inicioActual; // actualiza la posicion inicial
        }


        k--; // regresa a la ultima expansion valida


        if (i + k > R) { // si este palindromo llega mas lejos que R

            L = i - k - 1; // mueve L al nuevo limite izquierdo

            R = i + k; // mueve R al nuevo limite derecho
        }
    }


    int mejorFin =
        mejorInicio + mejorLongitud - 1; // calcula donde termina el mejor palindromo


    return {
        mejorInicio + 1, // convierte el inicio de posicion 0 a posicion 1
        mejorFin + 1     // convierte el final de posicion 0 a posicion 1
    };
}



/**
Funcion que ejecuta Manacher sobre
ambas transmisiones e imprime sus posiciones
 */

inline void ejecutarParte2(
    const string& transmision1,
    const string& transmision2
) {

    pair<int, int> resultado1 =
        manacher(transmision1); // busca el palindromo mas largo en transmision1


    pair<int, int> resultado2 =
        manacher(transmision2); // busca el palindromo mas largo en transmision2


    cout
        << resultado1.first << " "  // imprime posicion inicial de transmision1
        << resultado1.second        // imprime posicion final de transmision1
        << endl;


    cout
        << resultado2.first << " "  // imprime posicion inicial de transmision2
        << resultado2.second        // imprime posicion final de transmision2
        << endl;
}


#endif