
//Alejandro Salgado Martin y Jorge Santos

#include "partida.h"
using namespace std;

bool carga(tPartida & partida, ifstream & archivo)
{
	string jugador1, jugador2, identificadorPartida;
	int fechaInicio, fechaActualizacion, n_representaEstadoPartida;

	archivo >> identificadorPartida;
	archivo >> jugador1 >> jugador2;
	partida.iden = identificadorPartida;
	partida.jugadores.Jug1 = jugador1;
	partida.jugadores.Jug2 = jugador2;

	archivo >> fechaInicio >> fechaActualizacion;
	partida.fechaInicio = fechaInicio;
	partida.fechaActualizacion = fechaActualizacion;

	archivo >> n_representaEstadoPartida;
	partida.estadoPartida = tEstadoPartida(n_representaEstadoPartida);

	return cargar(partida.conecta4, archivo);
}

void guarda(const tPartida & partida, ofstream & archivo)
{
	archivo << partida.iden << endl;
	archivo << partida.jugadores.Jug1 << endl << partida.jugadores.Jug2 << endl;
	archivo << partida.fechaInicio << " " << partida.fechaActualizacion << endl;
	archivo << partida.estadoPartida << endl;

	guardar(partida.conecta4, archivo);
}

void nueva(tPartida & partida, const string & jugador1, const string & jugador2)
{
	int fecha = fechaActual();
	string s_fecha = to_string(fecha);
	string idenPartida = s_fecha + "_" + jugador1 + "_" + jugador2;

	partida.iden = idenPartida;
	partida.jugadores.Jug1 = jugador1;
	partida.jugadores.Jug2 = jugador2;

	partida.estadoPartida = enCurso;
	partida.fechaInicio = fecha;
	partida.fechaActualizacion = fecha;
	iniciar(partida.conecta4);
}

void abandonar(tPartida & partida)
{
	partida.estadoPartida = terminada;
	partida.fechaActualizacion = fechaActual();
}

bool aplicarJugada(tPartida & partida, int col)
{
	return aplicarJugada(partida.conecta4, col);
}

bool esJugador(const tPartida & partida, const std::string & nombreUsuario)
{
	return partida.jugadores.Jug1 == nombreUsuario || partida.jugadores.Jug2 == nombreUsuario;
}

bool devuelveTurno(const tPartida & partida, const string & nombre)
{
	bool jugador1 = (nombre == partida.jugadores.Jug1);
	bool jugador2 = (nombre == partida.jugadores.Jug2);

	return
		(partida.conecta4.turno == Jugador1 && jugador1)
		|| (partida.conecta4.turno == Jugador2 && jugador2);
}