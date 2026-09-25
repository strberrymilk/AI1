/*
Lectura de archivos de texto plano
Ana Camila Cuevas González - A01412609 / Cesar Augusto Ramirez Davila - A01712439
24/09/2026
*/

#ifndef ARCHIVO_H
#define ARCHIVO_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

/*
Lee todo el contenido de un archivo de texto y lo regresa como un solo string
Recibe la ruta del archivo a leer
Regresa el contenido del archivo concatenado sin saltos de línea,
o un string vacío si el archivo no se pudo abrir
*/
string leerArchivo(const string& ruta) {
	ifstream archivo(ruta);
	string contenido = "";

	if (!archivo.is_open()) {
		cerr << "No se pudo abrir el archivo: " << ruta << endl;
		return contenido;
	}

	ostringstream flujo;
	string linea = "";

	while (getline(archivo, linea)) {
		flujo << linea;
	}

	contenido = flujo.str();
	return contenido;
}

#endif
