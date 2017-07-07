
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
//Inicia la lista vac�a.

bool insertar(tListaAccesoPartidas & lista, const tPntrPar & puntero);
//Inserta en la �ltima posicion el puntero que le viene como par�metro (est� apuntando a una nueva partida creada)

bool llena(const tListaAccesoPartidas & lista);
//Comprueba si la lista est� llena

bool eliminar(tListaAccesoPartidas & lista, const tPntrPar & puntero);
//Dado el puntero de la partida actual, lo elimina de la lista de acceso 
//(El usuario ha abandonado partida)

bool buscar(const tListaAccesoPartidas & lista, const std::string & id, int &/*in/out*/ pos);
//Funcion recursiva; el par�metro pos es de entrada / salida, la funci�n empieza a buscar en
//	pos y termina en la posici�n de id en caso de encontrarlo

void ordenar_Fecha(tListaAccesoPartidas & lista);
//Ordena por la fecha de la �ltima actualizaci�n la lista de partidas en curso del usuario de la sesi�n.

void ordenar_Turno(tListaAccesoPartidas & lista, const std::string   & usuarioActual);
//Ordena por turno (primero aquellas en las que le toca jugar al usuario de la sesi�n) 
//la lista de partidas en curso del usuario de la sesi�n. Utiliza la ordenaci�n por inserci�n.
// Ademas recibe el nombre del usuario actual
#endif
