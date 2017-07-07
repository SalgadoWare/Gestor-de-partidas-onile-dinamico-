
//Alejandro Salgado Martin y Jorge Santos
#include "usuario.h"
using namespace std;

string nivelToString(tNivel nivel);
//Dado un nivel devuelve su string

void examinaRacha(tUsuario& usuario);
//Actualiza los campos correspondientes de la racha (aplicarFinPartida())

bool cargarUs(tUsuario & usuario, ifstream & archivo)
{
	string nombre, contraseña, centinela, linea;
	string avisos = "";
	string centinelas = "_X_X_X_";
	int representaNivel, racha, n_espera, ganadas, perdidas, empatadas, fecha;
	bool esperando;
	bool hay_avisos = false;
	char consume;

	archivo >> nombre >> contraseña;
	archivo >> representaNivel >> racha >> n_espera;
	archivo >> ganadas >> perdidas >> empatadas;
	archivo >> fecha;
	archivo.get(consume);

	while (getline(archivo, linea) && linea != centinelas && linea != "")
	{
		hay_avisos = true;
		avisos = avisos + linea + "\n";
	}

	if (!hay_avisos)
	{
		avisos = "\n";
		archivo >> centinelas;
	}

	usuario.nombre = nombre;
	usuario.contraseña = contraseña;
	usuario.nivel = tNivel(representaNivel);
	usuario.racha = racha;
	usuario.espera = tEspera(n_espera);
	usuario.ganadas = ganadas;
	usuario.empatadas = empatadas;
	usuario.perdias = perdidas;
	usuario.fecha = fecha;
	usuario.avisos = avisos;

	return !archivo.fail();
}

void guardarUs(const tUsuario & usuario, ofstream & archivo)
{
	archivo << usuario.nombre << endl << usuario.contraseña << endl;
	archivo << usuario.nivel << " " << usuario.racha << " " << usuario.espera << endl;
	archivo << usuario.ganadas << " " << usuario.perdias << " " << usuario.empatadas << endl;
	archivo << usuario.fecha << endl;
	archivo << usuario.avisos;
	archivo << "_X_X_X_" << endl;
}

bool iniciarSesion(tUsuario & usuario, const string & clave)
{
	bool exito = (usuario.contraseña == clave);

	if (exito)
	{
		usuario.fecha = fechaActual();
	}

	return exito;
}

void limpiarAvisos(tUsuario & usu)
{
	usu.avisos = "\n";
}

void iniciar(tUsuario & usuario, const string & id, const string & pas)
{
	usuario = {};
	usuario.nombre = id;
	usuario.contraseña = pas;
	usuario.fecha = fechaActual();
	usuario.avisos = "\n";
}

bool tieneAvisos(const tUsuario & usuario)
{
	return (usuario.avisos != "\n");
}

string resumenActividad(const tUsuario & usuario)
{
	ostringstream flujo;
	string aux;
	tNivel nivel = usuario.nivel;

	flujo << "		Resumen de la actividad:\n ";
	flujo << " Partidas ganadas: ";
	aux = to_string(usuario.ganadas);
	flujo << aux << endl;
	flujo << "  Partidas perdidas: ";
	aux = to_string(usuario.perdias);
	flujo << aux << endl;
	flujo << "  Partidas empatadas: ";
	aux = to_string(usuario.empatadas);
	flujo << aux << endl;
	flujo << "  Nivel actual: " << nivelToString(nivel) << endl;
	flujo << "  Racha actual: ";
	aux = to_string(usuario.racha);
	flujo << aux << endl;

	if (usuario.espera == esperando)
	{
		flujo << " Estas esperando a tener una nueva partida " << endl;
	}

	flujo << endl;
	aux = flujo.str();

	return aux;
}

string nivelToString(tNivel nivel)
{
	string palabra;
	switch (nivel)
	{
	case principiante:
		palabra = "principiante";
		break;
	case medio:
		palabra = "medio";
		break;
	case experto:
		palabra = "experto";
		break;
	default:
		break;
	}

	return palabra;
}

void aplicarFinPartida(tUsuario & usuario, const  tResultado  & resultado)
{
	switch (resultado)
	{
	case Gana:
	{
		if (usuario.racha >= 0)
		{
			usuario.racha++;
		}
		else
		{
			usuario.racha = 0;
		}

		examinaRacha(usuario);

		usuario.ganadas++;
	}
	break;

	case Empata:
	{
		usuario.racha = 0;

		usuario.empatadas++;
	}
	break;

	case Pierde:
	{
		if (usuario.racha > 0)
		{
			usuario.racha = 0;
		}
		else
		{
			usuario.racha--;
		}

		examinaRacha(usuario);

		usuario.perdias++;
	}

	default:
		break;
	}
}

void actualizarAvisos(tUsuario & usu, const std::string & aviso)
{
	ostringstream flujo;

	if (usu.avisos == "\n")
	{
		usu.avisos = aviso + "\n";
	}
	else
	{
		flujo << usu.avisos << aviso << endl;
		usu.avisos = flujo.str();
	}
}

void examinaRacha(tUsuario &usuario)
{
	switch (usuario.racha)
	{
	case NRN:
	{
		if (usuario.nivel < experto)
		{
			int indice = usuario.nivel;
			indice++;
			usuario.nivel = tNivel(indice);
			usuario.racha = 0;
			string aviso = "Has ascendido de nivel a " + nivelToString(tNivel(indice)) + " !!";
			actualizarAvisos(usuario, aviso);
		}
	}
	break;

	case -NRN:
	{
		if (usuario.nivel > principiante)
		{
			int indice = usuario.nivel;
			indice--;
			usuario.nivel = tNivel(indice);
			usuario.racha = 0;
			string aviso = "Has descendido de nivel a " + nivelToString(tNivel(indice)) + " !!";
			actualizarAvisos(usuario, aviso);
		}
	}
	break;

	default:
		break;
	}
}

void nuevaPartida(tUsuario & usuario, const bool & exito)
{
	if (exito)
	{
		usuario.espera = no_espera;
	}
	else
	{
		usuario.espera = esperando;
	}
}

