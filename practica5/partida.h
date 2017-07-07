
//Alejandro Salgado Martin y Jorge Santos
#ifndef partida_h
#define partida_h

#include "conecta4.h"
#include "fecha.h"

typedef struct {
	std::string Jug1, Jug2;
}tIdenJugadores; /*Los identificadores de los jugadores*/

typedef enum {
	enCurso,
	terminada,
}tEstadoPartida;

typedef struct {
	std::string iden;
	tIdenJugadores jugadores;
	tConecta4 conecta4;
	tEstadoPartida estadoPartida;
	int fechaInicio, fechaActualizacion;
}tPartida;

typedef tPartida *tPntrPar; /*Creamos punteros a partidas (tipos de puntero tPartida)*/

bool carga(tPartida & partida, std::ifstream & archivo);
/* Dado un flujo de archivo de entrada (ya abierto), lee los datos que corresponden a una partida en partida.
Devuelve false si la partida no se ha podido cargar correctamente.*/

void guarda(const tPartida & partida, std::ofstream & archivo);
/*Dado un flujo de archivo de salida (ya abierto), escribe en el flujo los datos de la partida*/

void nueva(tPartida & partida, const std::string & jugador1, const std::string &jugador2);
//Recibe los identificadores de los adversarios y devuelve una partida con todos sus datos rellenos.

void abandonar(tPartida & partida);
//Modifica el estado de la partida a Terminada, y la fecha de la última actualización.

bool aplicarJugada(tPartida & partida, int col);
//Aplica la jugada col al juego, y  si se pudo realizar, devuelve true y actualiza los demás campos de la partida.

bool esJugador(const tPartida & partida, const std::string & nombreUsuario);
//True: el usuario es jugador jugador de la partida recibida. False; viceversa.

bool devuelveTurno(const tPartida & partida, const std::string & nombre);
//Dada una partida y un nombre del jugador, devuelve true si es su turno
//y false si no

#endif 
