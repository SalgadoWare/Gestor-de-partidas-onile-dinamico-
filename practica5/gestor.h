
//Alejandro Salgado Martin y Jorge Santos
#ifndef gestor_h
#define gestor_h

#include "listaPartidas.h"
#include "listaUsuarios.h"
#include "listaAccesoPartidas.h"

typedef struct {
	tListaPartidas listaPartidas;
	tListaUsuarios listaUsuarios;
	tPntrPar punteroPartidaActual;
	tListaAccesoPartidas listaAccesoPartidas;
	int enlaceUsuarioActual;
}tGestor;

bool arrancar(tGestor & gestor);
/* Inicializa el gestor e intenta arrancarlo cargando la información del sistema.
Para ello abre los archivos y carga la lista de usuarios y de partidas.
Si tiene éxito, forma la lista de partidas en curso de cada uno de los usuarios y
devuelve true*/

void apagar(tGestor & gestor);
/*Esta operación apaga el gestor, abriendo los ficheros	para guardar las listas de usuarios y de partidas del sistema.*/

bool iniciarSesion(tGestor & gestor, const std::string & idUsu, const std::string &clave);
//Recibe los datos de usuario necesarios para validar la cuenta (id y contraseña) y
//	comprueba si el usuario existe y la contraseña coincide. Devuelve cierto y actualiza el
//	usuario de la sesión si la operación tuvo éxito.

bool crearCuenta(tGestor & gestor, const std::string & idUsu, const std::string &	clave);
//Recibe los datos de usuario necesarios para crear una cuenta(id y contraseña) y
//	si el id de usuario no existe y hay espacio en la lista de usuarios, crea la cuenta del usuario.
//	Devuelve cierto y actualiza el usuario de la sesión si la operación tuvo éxito

bool tieneAvisos(const tGestor & gestor, std::string & aviso);
//Comprueba si el usuario de la sesión tiene avisos, y en caso afirmativo los devuelve en aviso.

void limpiarAvisos(tGestor & gestor);
//Actualiza los avisos del usuario de la sesióna la cadena vacía.

std::string resumenActividad(const tGestor & gestor);
//Devuelve un string con los datos de la actividad del usuario de la sesión, las partidas ganadas, perdidas y empatadas,
//el nivel, la racha y si está esperando para una nueva partida.

int partidasUsuario(const tGestor & gestor);
//Devuelve el número de partidas en curso del usuario de la sesión.

std::string cabecera(const tGestor & gestor, tPntrPar puntero);
//Dada una posición de la lista de partidas en curso del usuario de la sesión, devuelve un string que contiene
//la información que se mostrará en la lista de partidas en curso : marca('*') si tiene el turno,
//nombres de los jugadores (jugador1, jugador2) y fecha de la última actualización.

void apuntaPartida(tGestor & gestor, int posParEnCurso);
//Dada una posición de la lista de partidas en curso del usuario de la sesión, 
//guarda en partida seleccionada, el índice de dicha partida en la lista de partidas.

void generarAccesos(tGestor & gestor);
//Recorre la lista de partidas, y para las que todavía están en curso, 
//añade el par{ identificador, índice } a la lista de partidas en curso de
//cada uno de los adversarios de la partida.

bool nuevaPartida(tGestor & gestor);
//Si el usuario de la sesión no ha alcanzado el
//	máximo número de partidas en curso y no está ya en espera, busca un usuario que esté
//	esperando para una nueva partida, que sea del mismo nivel que el usuario de la sesión.Si
//	lo encuentra crea la nueva partida e inserta en ambos adversarios los datos de acceso.En
//	otro caso deja al usuario de la sesión en estado de espera para una nueva partida.

void mostrarPartida(const tGestor & gestor);
//Muestra el estado de la partida en curso

std::string devuelveUsuarioRival(const tGestor & gestor);
//Devuelve el string que corresponde al nombre del contrincante del usuario actual

void jugarPartida(tGestor & gestor, int col);
//Aplica la jugada col a la partida, y en caso de que la partida termine, actualiza a los adversarios, 
//según termine el juego con Ganador o Bloqueo. Además envía un aviso al contrincante indicando 
//que ha perdido o empatado y la fecha.

bool esSuTurno(const tGestor & gestor);
//Comprueba si es el turno del usuario de la sesión en la partida seleccionada

void abandonarPartida(tGestor & gestor);
//Abandona la partida seleccionada del usuario, y actualiza la información de los adversarios teniendo en cuenta 
//que el que abandona pierde y el otro gana. Además avisa al contrincante indicando que ha ganado con la fecha

void detectaAntiguedad(tGestor & gestor);
//Hacemos un recorrido a la lista de partidas`para eliminar aquellas con 30 dias de antiguedad, resultanto perdedor
//aquel jugador que tenia el turno (Hacemos uso de esAntigua(), funcion definida en el módulo fecha
#endif
