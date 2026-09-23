/*
Implementación del algoritmo Knuth-Morris-Pratt (KMP)
Ana Camila Cuevas González - A01412609
23/09/2026
*/

#ifndef KMP_H
#define KMP_H

#include <string>
#include <vector>

using namespace std;

/*
Construye la tabla LPS del patrón
Recibe la cadena que representa el patrón de búsqueda
Devuelve un vector con la tabla LPS del patrón
*/
vector<int> computeLPSArray(const string& pat) {
	int M = pat.size();
	vector<int> lps(M, 0);

	int i = 1;
	int j = 0;

	while (i < M) {
		if (pat[i] == pat[j]) {
			lps[i] = j + 1;
			i++;
			j++;
		}
		else if (j > 0) {
			j = lps[j - 1];
		}
		else {
			lps[i] = 0;
			i++;
		}
	}

	return lps;
}

/*
Busca la primera aparición de un patrón dentro de un texto
Recibe el patrón y el texto donde se realizará la búsqueda
Devuelve el índice donde comienza el patrón o -1 si no se encuentra
*/
int kmpSearch(const string& pat, const string& txt) {
	int M = pat.size();
	int N = txt.size();

	vector<int> lps = computeLPSArray(pat);

	int i = 0;
	int j = 0;

	while (i < N) {
		if (pat[j] == txt[i]) {
			if (j == M - 1) {
				return i - M + 1;
			}

			i++;
			j++;
		}
		else if (j > 0) {
			j = lps[j - 1];
		}
		else {
			i++;
		}
	}

	return -1;
}

#endif
