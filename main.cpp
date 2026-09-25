/*
Programa principal: analiza transmisiones en busca de código malicioso
Usa KMP (parte 1), Manacher (parte 2) y LCS (parte 3)
Ana Camila Cuevas González - A01412609
Cesar Augusto Ramirez Davila - A01712439
24/09/2026
*/

#include <string>

#include "archivo.h"
#include "kmp.h"
#include "manacher.h"
#include "lcs.h"

using namespace std;

// archivos de la carpeta texto/ que se usarán para este análisis
const string RUTA_MCODE1 = "texto/mcode01.txt";
const string RUTA_MCODE2 = "texto/mcode02.txt";
const string RUTA_MCODE3 = "texto/mcode03.txt";
const string RUTA_TRANSMISION1 = "texto/transmission01.txt";
const string RUTA_TRANSMISION2 = "texto/transmission02.txt";

int main() {
	string mcode1 = leerArchivo(RUTA_MCODE1);
	string mcode2 = leerArchivo(RUTA_MCODE2);
	string mcode3 = leerArchivo(RUTA_MCODE3);
	string transmision1 = leerArchivo(RUTA_TRANSMISION1);
	string transmision2 = leerArchivo(RUTA_TRANSMISION2);

	// parte 1: busca si los mcode están contenidos en las transmisiones (KMP)
	ejecutarParte1KMP(transmision1, transmision2, mcode1, mcode2, mcode3);

	// parte 2: busca el código espejeado (palíndromo) más largo en cada transmisión (Manacher)
	ejecutarParte2(transmision1, transmision2);

	// parte 3: busca el substring común más largo entre ambas transmisiones (LCS)
	ejecutarParte3(transmision1, transmision2);

	return 0;
}
