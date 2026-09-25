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
#include <algorithm>  // usar función min()

using namespace std;

/*
Función que encuentra el palíndromo más largo
dentro de una cadena usando Manacher
*/
inline pair<int, int> manacher(const string& texto) {

    int n = static_cast<int>(texto.size()); // guarda el tamaño total del texto

    if (n == 0) { // si el texto está vacío

        return {0, 0}; // no existen posiciones para regresar
    }

    int mejorInicio = 0; // posición donde inicia el mejor palíndromo encontrado

    int mejorLongitud = 1; // un carácter solo ya cuenta como palíndromo

/*
PALÍNDROMOS IMPARES
*/

    vector<int> d1(n, 0); // guarda el radio de cada palíndromo impar

    int L = 0; // límite izquierdo del palíndromo conocido

    int R = -1; // límite derecho, inicia en -1 porque aún no existe un rango

    // i recorre cada posición del texto como posible centro
    for (int i = 0; i < n; i++) {

        int k; // radio del palíndromo en la posición actual

        if (i > R) { // si i está fuera del rango conocido

            k = 1; // comienza desde 1 porque el centro ya es un palíndromo
        }

        else { // si i se encuentra dentro del rango conocido

            k = min(
                d1[L + R - i], // reutiliza el valor de la posición espejo
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

        d1[i] = k; // guarda el radio encontrado en la posición i

        int longitudActual =
            2 * d1[i] - 1; // calcula la longitud del palíndromo impar

        int inicioActual =
            i - d1[i] + 1; // calcula dónde inicia el palíndromo

        if (longitudActual > mejorLongitud) { // si encontró un palíndromo más largo

            mejorLongitud = longitudActual; // guarda la nueva longitud máxima

            mejorInicio = inicioActual; // guarda dónde inicia
        }

        k--; // regresa a la última expansión que fue válida

        if (i + k > R) { // si el palíndromo llega más lejos que R

            L = i - k; // mueve L al nuevo límite izquierdo

            R = i + k; // mueve R al nuevo límite derecho
        }
    }

/*
PALÍNDROMOS PARES
*/

    vector<int> d2(n, 0); // guarda el radio de cada palíndromo par

    L = 0; // reinicia el límite izquierdo

    R = -1; // reinicia el límite derecho

    // vuelve a recorrer cada posición para buscar palíndromos pares
    for (int i = 0; i < n; i++) {

        int k; // radio del palíndromo actual

        if (i > R) { // si i está fuera del rango conocido

            k = 0; // en palíndromos pares el radio inicia en cero
        }

        else { // si i se encuentra dentro del rango conocido

            k = min(
                d2[L + R - i + 1], // reutiliza el valor de la posición espejo
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
            2 * d2[i]; // calcula la longitud del palíndromo par

        int inicioActual =
            i - d2[i]; // calcula dónde inicia el palíndromo

        if (longitudActual > mejorLongitud) { // si encontró uno más largo

            mejorLongitud = longitudActual; // actualiza la longitud máxima

            mejorInicio = inicioActual; // actualiza la posición inicial
        }

        k--; // regresa a la última expansión válida

        if (i + k > R) { // si este palíndromo llega más lejos que R

            L = i - k - 1; // mueve L al nuevo límite izquierdo

            R = i + k; // mueve R al nuevo límite derecho
        }
    }

    int mejorFin =
        mejorInicio + mejorLongitud - 1; // calcula dónde termina el mejor palíndromo

    return {
        mejorInicio + 1, // convierte el inicio de posición 0 a posición 1
        mejorFin + 1     // convierte el final de posición 0 a posición 1
    };
}

/*
Función que ejecuta Manacher sobre
ambas transmisiones e imprime sus posiciones
*/
inline void ejecutarParte2(
    const string& transmision1,
    const string& transmision2
) {

    pair<int, int> resultado1 =
        manacher(transmision1); // busca el palíndromo más largo en transmision1

    pair<int, int> resultado2 =
        manacher(transmision2); // busca el palíndromo más largo en transmision2

    cout
        << resultado1.first << " "  // imprime posición inicial de transmision1
        << resultado1.second        // imprime posición final de transmision1
        << endl;

    cout
        << resultado2.first << " "  // imprime posición inicial de transmision2
        << resultado2.second        // imprime posición final de transmision2
        << endl;
}

#endif