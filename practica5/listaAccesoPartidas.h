
//Alejandro Salgado Martin y Jorge Santos
#ifndef listaAccesoPartidas_h
#define listaAccesoPartidas_h

#include "partida.h"
const int MAX_PAR_US = 10;

typedef tPntrPar tVectorPartidasCurso[MAX_PAR_US];

typedef struct {
	tVectorPartidasCurso partidaUsuario;
	int contador;
}tListaAccesoPartidas;

void iniciar(tListaAccesoPartidas & lista);
//Inicia la lista vacía.

bool insertar(tListaAccesoPartidas & lista, const tPntrPar & puntero);
//Inserta en la última posicion el puntero que le viene como parámetro (está apuntando a una nueva partida creada)

bool llena(const tListaAccesoPartidas & lista);
//Comprueba si la lista está llena

bool eliminar(tListaAccesoPartidas & lista, const tPntrPar & puntero);
//Dado el puntero de la partida actual, lo elimina de la lista de acceso 
//(El usuario ha abandonado partida)

bool buscar(const tListaAccesoPartidas & lista, const std::string & id, int &/*in/out*/ pos);
//Funcion recursiva; el parámetro pos es de entrada / salida, la función empieza a buscar en
//	pos y termina en la posición de id en caso de encontrarlo

void ordenar_Fecha(tListaAccesoPartidas & lista);
//Ordena por la fecha de la última actualización la lista de partidas en curso del usuario de la sesión.

void ordenar_Turno(tListaAccesoPartidas & lista, const std::string   & usuarioActual);
//Ordena por turno (primero aquellas en las que le toca jugar al usuario de la sesión) 
//la lista de partidas en curso del usuario de la sesión. Utiliza la ordenación por inserción.
// Ademas recibe el nombre del usuario actual
#endif
