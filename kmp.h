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
Busca las apariciones de un patrón dentro de un texto utilizando KMP
Recibe el patrón y el texto donde se realizará la búsqueda
Muestra el índice donde comienza cada aparición del patrón
*/
void KMPSearch(const string& pat, const string& txt) {
	int N = txt.size();
	int M = pat.size();
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
			cout << i - j << endl;
			j = lps[j - 1];
		}
	}
}

#endif
