/*
Implementación del algoritmo Knuth-Morris-Pratt (KMP)
Ana Camila Cuevas González - A01412609
23/09/2026
*/

#ifndef KMP_H
#define KMP_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
Construye la tabla LPS del patrón
Recibe el patrón, su longitud y el vector LPS
Modifica el vector LPS con los valores correspondientes al patrón
*/
void computeLPSArray(const string& pat, int M, vector<int>& lps) {
	int len = 0;
	int i = 1;

	lps[0] = 0;

	while (i < M) {
		if (pat[i] == pat[len]) {
			lps[i] = len + 1;
			len++;
			i++;
		}
		else {
			if (len != 0) {
				len = lps[len - 1];
			}
			else {
				lps[i] = 0;
				i++;
			}
		}
	}
}

/*
Busca la primera aparición de un patrón dentro de un texto utilizando KMP
Recibe el patrón y el texto donde se realizará la búsqueda
Regresa la posición (base 0) donde inicia la primera coincidencia,
o -1 si el patrón no se encuentra dentro del texto
*/
int KMPSearch(const string& pat, const string& txt) {
	int N = txt.size();
	int M = pat.size();

	if (M == 0 || N < M) { // patrón vacío o más grande que el texto
		return -1;
	}

	vector<int> lps(M, 0);

	computeLPSArray(pat, M, lps);

	int i = 0;
	int j = 0;

	while (i < N - M + 1) {
		if (txt[i] == pat[j]) {
			i++;
			j++;
		}
		else {
			if (j != 0) {
				j = lps[j - 1];
			}
			else {
				i++;
			}
		}

		if (j == M) {
			return i - j; // primera coincidencia encontrada 
		}
	}

	return -1; // el patrón no se encontró dentro del texto
}

/*
Busca un mcode dentro de una transmisión con KMP e imprime el resultado
Recibe la transmisión donde se buscará y el mcode a buscar
Imprime "true <posición>" (base 1) si lo encuentra, o "false" si no
*/
void imprimirResultadoKMP(
	const string& transmision,
	const string& mcode
) {
	int posicion = KMPSearch(mcode, transmision);

	if (posicion == -1) {
		cout << "false" << endl;
	}
	else {
		cout << "true " << posicion + 1 << endl;
	}
}

/*
Ejecuta las 6 comparaciones de la parte 1 usando KMP
Recibe las dos transmisiones y los tres mcode a buscar en cada una
Imprime un resultado por cada combinación de transmisión y mcode
*/
void ejecutarParte1KMP(
	const string& transmision1,
	const string& transmision2,
	const string& mcode1,
	const string& mcode2,
	const string& mcode3
) {
	// busca los mcode dentro de la transmission 1
	imprimirResultadoKMP(transmision1, mcode1);
	imprimirResultadoKMP(transmision1, mcode2);
	imprimirResultadoKMP(transmision1, mcode3);

	// busca los mcode dentro de la transmissin 2
	imprimirResultadoKMP(transmision2, mcode1);
	imprimirResultadoKMP(transmision2, mcode2);
	imprimirResultadoKMP(transmision2, mcode3);
}

#endif
