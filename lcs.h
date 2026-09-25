/*
Implementación de la búsqueda del longest common string (lcs)
con programación dinámica (dp)
Ana Camila Cuevas González - A01412609
24/09/2026
*/

#ifndef LCS_H
#define LCS_H

#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

pair<int, int> longestCommonString(string text1, string text2) {
        vector<vector<int>> dp(text1.size()+1, vector<int>(text2.size()+1, 0));
        int mejorLongitud = 0;
        int mejorFin = 0;
        for(int i=1; i<text1.size()+1; i++){
            for(int j=1; j<text2.size()+1; j++){
                if(text1[i-1]==text2[j-1]){
                    dp[i][j] = dp[i-1][j-1]+1;
                    if(dp[i][j] > mejorLongitud){
                        mejorLongitud = dp[i][j];
                        mejorFin = i;
                    }
                }
            }
        }
        int mejorInicio = mejorFin - mejorLongitud + 1;
        return {mejorInicio, mejorFin};
    }

/*
Ejecuta la comparación de la parte 3: busca el substring común
más largo entre las dos transmisiones e imprime su posición
inicial y final (base 1) dentro de transmision1
*/
void ejecutarParte3(const string& transmision1, const string& transmision2) {
    pair<int, int> resultado = longestCommonString(transmision1, transmision2);
    cout << resultado.first << " " << resultado.second << endl;
}

#endif