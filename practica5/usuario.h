
//Alejandro Salgado Martin y Jorge Santos

#ifndef usuario_h
#define usuarios_h

#include "fecha.h"

const int NRN = 5;

typedef enum {
	principiante,
	medio,
	experto,
}tNivel;

typedef enum {
	no_espera,
	esperando,
}tEspera;

typedef struct {
	std::string nombre, contraseña, avisos;
	tNivel nivel;
	int racha, ganadas, perdias, empatadas, fecha;
	tEspera espera;
}tUsuario;

typedef tUsuario *tPntrUs;		/*Creamos punteros a un dato tipo tUsuario*/

typedef enum {
	Gana,
	Pierde,
	Empata,
}tResultado;

bool cargarUs(tUsuario & usuario, std::ifstream & archivo);
/*: Dado un flujo de archivo (ya abierto), lee los datos que corresponde a un usuario en usuario*/

void guardarUs(const tUsuario & usuario, std::ofstream & archivo);
/*Dado un flujo de archivo	(ya abierto), escribe en el flujo los datos del usuario*/

bool iniciarSesion(tUsuario & usuario, const std::string & clave);
/*Recibe una contraseña (clave) y un usuario y devuelve si la contraseña es correcta o no.
Además, en	caso de ser correcta, actualiza la fecha de la última conexión.*/

void limpiarAvisos(tUsuario & usu);
//Elimina el campo de avisos del usuario

void iniciar(tUsuario & usuario, const std::string & id, const std::string & pas);
//Recibe un identificador de usuario y una contraseña e inicia todos los campos del usuario.*/

bool tieneAvisos(const tUsuario & usuario);
//True; tiene avios. False; no tiene

std::string resumenActividad(const tUsuario & gestor);
//void actualizarAvisos(tUsuario & usu, const string & aviso) : Actualiza el
//campo avisos añadiendo al final del string una nueva línea con el nuevo aviso.

void actualizarAvisos(tUsuario & usu, const std::string & aviso);
//Actualiza el campo avisos añadiendo al final del string una nueva línea con el nuevo aviso.

void aplicarFinPartida(tUsuario & usuario, const  tResultado &resultado);
//ml enumerado{ Gana, Pierde, Empata }) :
//	partidas ganadas, perdidas, empataodifica los campos afectados por el final de una partida en
//	curso del usuario con el resultado dado(valor dedas, racha, nivel y lista de partidas en curso.
//	Importante : El usuario sube de nivel cada vez que consigue ganar NRN partidas
//	consecutivas(racha == NRN), y baja de nivel si lleva una racha de NRN partidas perdidas
//	(racha == -NRN).Un empate reinicia la racha.Define la constante NRN = 5.

void nuevaPartida(tUsuario & usuario, const bool & exito);
//Actualiza el campo referente a la espera del usuario según al éxito de conseguir crear una nueva partida

#endif // !usuario_h
