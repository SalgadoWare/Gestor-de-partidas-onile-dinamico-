
//Alejandro Salgado Martin y Jorge Santos
#include "gestor.h"
#include <iostream>
using namespace std;

void actualizarPorVictoria(tGestor & gestor);
void actualizarPorEmpate(tGestor & gestor);
//Ambas funciones son auxiliares de jugarPartida, actualizan los campos necesarios en un final de partida

bool arrancar(tGestor & gestor)
{
	gestor = {};

	ifstream flujoLecturaPartidas, flujoLecturaUsuarios;

	flujoLecturaPartidas.open("partidas.txt");
	flujoLecturaUsuarios.open("usuarios.txt");

	bool exito = flujoLecturaPartidas.is_open() && flujoLecturaUsuarios.is_open();

	if (exito)
	{
		bool exitoEnCargaDeListaPartidas = cargarListaPartidas(gestor.listaPartidas, flujoLecturaPartidas);
		bool exitoEnCargaDeListaUsuarios = cargarListaUsuarios(gestor.listaUsuarios, flujoLecturaUsuarios);

		flujoLecturaPartidas.close();
		flujoLecturaUsuarios.close();

		exito = exitoEnCargaDeListaPartidas && exitoEnCargaDeListaUsuarios;
	}

	return exito;
}

void apagar(tGestor & gestor)
{
	ofstream flujoGuardarPartidas, flujoGuardarUsuarios, flujoHistorico;

	flujoGuardarPartidas.open("partidas.txt");
	flujoGuardarUsuarios.open("usuarios.txt");
	flujoHistorico.open("historico.txt", ios::app);

	detectaAntiguedad(gestor);
	apagar_Historicos(gestor.listaPartidas, flujoHistorico);
	apagar(gestor.listaPartidas, flujoGuardarPartidas);
	apagar(gestor.listaUsuarios, flujoGuardarUsuarios);

	flujoGuardarPartidas.close();
	flujoGuardarUsuarios.close();
}

bool iniciarSesion(tGestor & gestor, const std::string & idUsu, const std::string & clave)
{
	int pos;
	bool exito = false;

	if (buscar(gestor.listaUsuarios, idUsu, pos))
	{
		if (iniciarSesion(gestor.listaUsuarios.usuario[pos], clave))
		{
			exito = true;
			gestor.enlaceUsuarioActual = pos;
			generarAccesos(gestor);
		}
	}

	return exito;
}

bool crearCuenta(tGestor & gestor, const std::string & idUsu, const std::string & clave)
{
	bool exito = (gestor.listaUsuarios.contador < MAX_USUARIOS) && compruebaIDvalido(idUsu, gestor.listaUsuarios);

	if (exito)
	{
		tUsuario nuevoUsuario;
		iniciar(nuevoUsuario, idUsu, clave);

		insertar(gestor.listaUsuarios, nuevoUsuario);
	}

	return exito;
}

bool tieneAvisos(const tGestor & gestor, std::string & aviso)
{
	bool exito = tieneAvisos(gestor.listaUsuarios.usuario[gestor.enlaceUsuarioActual]);

	if (exito)
	{
		aviso = gestor.listaUsuarios.usuario[gestor.enlaceUsuarioActual].avisos;
	}

	return exito;
}

void limpiarAvisos(tGestor & gestor)
{
	limpiarAvisos(gestor.listaUsuarios.usuario[gestor.enlaceUsuarioActual]);
}

string resumenActividad(const tGestor & gestor)
{
	return resumenActividad(gestor.listaUsuarios.usuario[gestor.enlaceUsuarioActual]);
}

int partidasUsuario(const tGestor & gestor)
{
	return gestor.listaAccesoPartidas.contador;
}

string cabecera(const tGestor & gestor, tPntrPar puntero)
{
	tPartida partida = *puntero;
	string nombreJug1partida = partida.jugadores.Jug1;
	string nombreJug2partida = partida.jugadores.Jug2;
	string nombre = gestor.listaUsuarios.usuario[gestor.enlaceUsuarioActual].nombre;
	ostringstream flujo;
	string cabecera;

	if (devuelveTurno(*puntero, nombre))
	{
		flujo << "*   ";
	}
	else
	{
		flujo << "    ";
	}

	int fecha = partida.fechaActualizacion;

	flujo << setw(10) << nombreJug1partida << setw(20) << nombreJug2partida <<
		setw(30) << stringFecha(fecha, true) << endl;

	cabecera = flujo.str();

	return cabecera;
}

void generarAccesos(tGestor & gestor)
{
	string nombreUser = gestor.listaUsuarios.usuario[gestor.enlaceUsuarioActual].nombre;

	for (int indice = 0; indice < gestor.listaPartidas.contador; indice++)
	{
		if (gestor.listaPartidas.partida[indice]->estadoPartida == Jugando
			&& esJugador(*gestor.listaPartidas.partida[indice], nombreUser))
		{
			insertar(gestor.listaAccesoPartidas, gestor.listaPartidas.partida[indice]);
		}
	}

	/*Menospreciamos el booleano que devuelve la funcion insertar porque siempre será true,
	porque las condiciones para no superar el límite de partidas por usuario, se revisan al crear
	una nueva partida, por lo tanto la lista de acceso de partida siempre insertará en un rango válido*/
}

bool nuevaPartida(tGestor & gestor)
{
	bool exito;

	if (gestor.listaPartidas.contador < MAX_PARTIDAS_GUARDADAS && partidasUsuario(gestor) < MAX_PAR_US)
	{
		tNivel nivel = gestor.listaUsuarios.usuario[gestor.enlaceUsuarioActual].nivel;
		int pos;

		if (buscarUsuarioEsperando(gestor.listaUsuarios, nivel, pos))
		{
			tPartida newGame = {};
			string jug1 = gestor.listaUsuarios.usuario[gestor.enlaceUsuarioActual].nombre;
			string jug2 = gestor.listaUsuarios.usuario[pos].nombre;

			nueva(newGame, jug1, jug2);

			exito = insertar(gestor.listaPartidas, newGame);
			tPntrPar puntero = gestor.listaPartidas.partida[gestor.listaPartidas.contador - 1];
			/*El contador se ha incrementado, y queremos obtener el puntero de la última partida (la creada)
			por ello gestor.listaPartidas.contador - 1*/
			
			exito = insertar(gestor.listaAccesoPartidas, puntero);

			nuevaPartida(gestor.listaUsuarios.usuario[pos], exito);
			nuevaPartida(gestor.listaUsuarios.usuario[gestor.enlaceUsuarioActual], exito);
			
			/*Llegado  a este punto exito siempre será true, ya que previamente se ha comprobado que existe espacio
			en ambas listas*/
		}
		else
		{
			exito = false;
			nuevaPartida(gestor.listaUsuarios.usuario[gestor.enlaceUsuarioActual], exito);
		}
	}
	else
	{
		exito = false;
	}

	return exito;
}

void apuntaPartida(tGestor & gestor, int posParEnCurso)
{
	gestor.punteroPartidaActual = gestor.listaAccesoPartidas.partidaUsuario[posParEnCurso];
}

void mostrarPartida(const tGestor & gestor)
{
	mostrar
		(gestor.punteroPartidaActual->conecta4,
			gestor.punteroPartidaActual->jugadores.Jug1,
			gestor.punteroPartidaActual->jugadores.Jug2);
}

string devuelveUsuarioRival(const tGestor & gestor)
{
	string usuarioRival;

	if (gestor.punteroPartidaActual->jugadores.Jug1
		== gestor.listaUsuarios.usuario[gestor.enlaceUsuarioActual].nombre)
	{
		usuarioRival = gestor.punteroPartidaActual->jugadores.Jug1;
	}
	else
	{
		usuarioRival = gestor.punteroPartidaActual->jugadores.Jug1;
	}

	return usuarioRival;
}

bool esSuTurno(const tGestor & gestor)
{
	string nombreUsActual = gestor.listaUsuarios.usuario[gestor.enlaceUsuarioActual].nombre;

	return devuelveTurno(*gestor.punteroPartidaActual, nombreUsActual);
}

void jugarPartida(tGestor & gestor, int col)
{
	if (!aplicarJugada(*gestor.punteroPartidaActual, col))
	{
		cout << " No es posible colocar la ficha aqui " << endl << endl;
	}
	else
	{
		mostrarPartida(gestor);

		tEstado estadoJuego = gestor.punteroPartidaActual->conecta4.estado;

		switch (estadoJuego)
		{
		case Jugando:
			cout << endl;
			break;

		case Ganador:
		{
			actualizarPorVictoria(gestor);
		}

		break;

		case Bloqueo:
		{
			actualizarPorEmpate(gestor);
		}
		break;

		default:
			break;
		}
	}
}

void actualizarPorVictoria(tGestor & gestor)
{
	string nombreContrincante = devuelveUsuarioRival(gestor);
	string idPartida = gestor.punteroPartidaActual->iden;
	int fecha = fechaActual();
	string aviso = "Has ganado la partida contra " + nombreContrincante + " el " + stringFecha(fecha, true);
	string nombreUsActual = gestor.listaUsuarios.usuario[gestor.enlaceUsuarioActual].nombre;
	int pos = -1;

	cout << " Enhorabuena, has ganado la partida !! " << endl << endl;
	aplicarFinPartida(gestor.listaUsuarios.usuario[gestor.enlaceUsuarioActual], Gana);
	eliminar(gestor.listaAccesoPartidas, gestor.punteroPartidaActual);
	actualizarAvisos(gestor.listaUsuarios.usuario[gestor.enlaceUsuarioActual], aviso);


	if (buscar(gestor.listaUsuarios, nombreContrincante, pos))
	{
		string aviso = "Has perdido la partida contra " + nombreUsActual + " el " + stringFecha(fecha, true);
		aplicarFinPartida(gestor.listaUsuarios.usuario[pos], Pierde);
		actualizarAvisos(gestor.listaUsuarios.usuario[pos], aviso);
	}
	else
	{
		cout << " Error inesperado, la lista de usuarios esta dañada " << endl << endl;
	}

	gestor.punteroPartidaActual->estadoPartida = terminada;
}

void actualizarPorEmpate(tGestor & gestor)
{
	string nombreContrincante = devuelveUsuarioRival(gestor);
	string idPartida = gestor.punteroPartidaActual->iden;
	int fecha = fechaActual();
	string aviso = "Has empatado la partida contra " + nombreContrincante + " el " + stringFecha(fecha, true);
	string nombreUsActual = gestor.listaUsuarios.usuario[gestor.enlaceUsuarioActual].nombre;
	int pos = -1;

	cout << " Se ha bloqueado el tablero, hay empate " << endl << endl;
	aplicarFinPartida(gestor.listaUsuarios.usuario[gestor.enlaceUsuarioActual], Empata);
	eliminar(gestor.listaAccesoPartidas, gestor.punteroPartidaActual);
	actualizarAvisos(gestor.listaUsuarios.usuario[gestor.enlaceUsuarioActual], aviso);


	if (buscar(gestor.listaUsuarios, nombreContrincante, pos))
	{
		string aviso = "Has empatado la partida contra " + nombreUsActual + " el " + stringFecha(fecha, true);
		aplicarFinPartida(gestor.listaUsuarios.usuario[pos], Pierde);
		actualizarAvisos(gestor.listaUsuarios.usuario[pos], aviso);
	}
	else
	{
		cout << " Error inesperado, la lista de usuarios esta dañada " << endl << endl;
	}

	gestor.punteroPartidaActual->estadoPartida = terminada;
}

void abandonarPartida(tGestor & gestor)
{
	abandonar(*gestor.punteroPartidaActual);

	string idPartida = gestor.punteroPartidaActual->iden;

	aplicarFinPartida(gestor.listaUsuarios.usuario[gestor.enlaceUsuarioActual], Pierde);
	string usuarioRival = devuelveUsuarioRival(gestor);
	int fecha = fechaActual();
	string s_fecha = stringFecha(fecha, true);
	string aviso = "Has perdido por abandono la partida contra " + usuarioRival + " el " + s_fecha;

	actualizarAvisos(gestor.listaUsuarios.usuario[gestor.enlaceUsuarioActual], aviso);

	int pos = -1;

	if (buscar(gestor.listaUsuarios, usuarioRival, pos))
	{
		aplicarFinPartida(gestor.listaUsuarios.usuario[pos], Gana);
		string usuarioActual = gestor.listaUsuarios.usuario[gestor.enlaceUsuarioActual].nombre;
		string aviso = "Has ganado por abandono la partida contra " + usuarioActual + " el " + s_fecha;
		actualizarAvisos(gestor.listaUsuarios.usuario[pos], aviso);
	}
	else
	{
		cout << " Error inesperado, la lista de usuarios esta dañada " << endl << endl;
	}
}

void detectaAntiguedad(tGestor & gestor)
{
	tFecha fechaReciente = fechaActual();

	for (int indice = 0; indice < gestor.listaPartidas.contador; indice++)
	{
		tFecha fechaActualizacion = gestor.listaPartidas.partida[indice]->fechaActualizacion;

		if (gestor.listaPartidas.partida[indice]->estadoPartida == enCurso
			&& esAntigua(fechaActualizacion, fechaReciente))
		{
			gestor.listaPartidas.partida[indice]->estadoPartida = terminada;

			gestor.punteroPartidaActual = gestor.listaPartidas.partida[indice];

			int pos, pos2;

			buscar(gestor.listaUsuarios, gestor.listaPartidas.partida[indice]->jugadores.Jug1, pos);
			buscar(gestor.listaUsuarios, gestor.listaPartidas.partida[indice]->jugadores.Jug2, pos2);

			string jug1 = gestor.listaPartidas.partida[indice]->jugadores.Jug1;

			if (devuelveTurno(*gestor.punteroPartidaActual, jug1))
			{
				gestor.enlaceUsuarioActual = pos;
			}
			else
			{
				gestor.enlaceUsuarioActual = pos2;
			}
			/*Asignamos correctamente al usuario actual el usuario con el turno, que es el que pierde la partida*/

			abandonarPartida(gestor);
		}
	}
}
