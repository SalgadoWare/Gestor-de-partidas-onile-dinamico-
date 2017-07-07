
//Alejandro Salgado Martin y Jorge Santos
#ifndef listaPartidas_h
#define listaPartidas_h

#include "partida.h"

const int MAX_PARTIDAS_GUARDADAS = 100;

typedef tPntrPar tVectorPartidas[MAX_PARTIDAS_GUARDADAS];

typedef struct {
	tVectorPartidas partida;
	int contador;
}tListaPartidas;

bool cargarListaPartidas(tListaPartidas & listaPartidas, std::ifstream & archivo);
/*Carga la lista de partidas desde el flujo (ya abierto) archivo. Devuelve false
si la lista no se ha podido cargar correctamente*/

void apagar(const tListaPartidas & listaPartidas, std::ofstream & archivo);
//Guarda la lista de partidas en el flujo (ya abierto) y deshace los datos dinámicos

bool insertar(tListaPartidas & partidas, const tPartida & partida);
//Dada una partida, si hay espacio en la lista, la añade al final de la lista y devuelve true.
//Si no se ha podido insertar devuelve false

void apagar_Historicos(tListaPartidas & listaPartidas, std::ofstream & archivo);
//Guarda las partidas terminadas (históricas) haciendo una búsqueda de ellas en la lista de partidas,
//tambien elimina las partidas terminadas de la lista de partidas


#endif


