
//Alejandro Salgado Martin 51544280S y Jorge Santos 05460315T
#include "gestor.h"
//#include <vld.h>
#include <iostream>
using namespace std;

void menuUsuario(tGestor & gestor);
//Muestra y gestiona el menú principal de una sesión de usuario.

int opcionMenuRegistro();
//Muestra las diferentes opciones del menuRegistro y devuelve una valida (entero)

void leerDatosRegistro(string & nombre, string & clave);
//Devuelve por referencia el nombre y la clave proporcionados, esta funcion se usa en menuRegistro

void menuRegistro(tGestor & gestor);
//Muestra y gestiona el menú inicial de la aplicación

void mostrarDatosUsu(tGestor & gestor);
//Una vez abierta una sesion con éxito, se muestran todos sus datos de su actividad por pantalla

int opcionMenuUsuario();
//Muestra las diferentes opciones del menuUsuario y devuelve una valida (entero)

void mostrarPartidasEnCurso(const tGestor & gestor);
//Muestra todas las partidas que está jugando el usuario de la sesion, en total las n_partidasActivas

void menuPartida(tGestor & gestor);
//Muestra y gestiona el menú de una partida

void elegirPartida(tGestor & gestor);
//Solicita un número válido de partida(de entre la lista mostrada),
//y lo apunta como partida seleccionada del usuario de la sesión

int opcionMenuPartida();
//Muestra las diferentes opciones del menuPartida y devuelve una valida (entero)

void leerJugada(int & col);
//Solicita y devuelve una columna válida.

int main()
{
	tGestor gestor;

	if (arrancar(gestor))
	{
		menuRegistro(gestor);
		apagar(gestor);
	}
	else
	{
		cout << " Existe algun problema al arrancar el gestor de partidas " << endl;
		system("pause");
		return 1;
	}

	system("pause");
	return 0;
}

void menuRegistro(tGestor & gestor)
{
	int numero;

	do
	{
		numero = opcionMenuRegistro();

		switch (numero)
		{
		case 0:
			break;

		case 1:
		{
			string nombre, clave;

			leerDatosRegistro(nombre, clave);

			if (!iniciarSesion(gestor, nombre, clave))
			{
				cout << " Comprueba los datos introducidos " << endl << endl;
			}
			else
			{
				mostrarDatosUsu(gestor);

				menuUsuario(gestor);
			}
			break;
		}

		case 2:
		{
			string nombre, clave;

			leerDatosRegistro(nombre, clave);

			if (!crearCuenta(gestor, nombre, clave))
			{
				cout << " Ya existe un usuario con ese nombre " << endl << endl;
			}
			else
			{
				cout << " Cuenta creada con exito, ya puedes acceder a tu cuenta " << endl << endl;
			}
			break;
		}

		default:
			break;
		}
	} while (numero != 0);
}

int opcionMenuRegistro()
{
	int numero = -1;

	while (numero < 0 || numero > 3)
	{
		cout << " MENU REGISTRO " << endl;
		cout << "	1 - Acceder a mi cuenta " << endl;
		cout << "	2 - Registrarse " << endl;
		cout << "	0 - Salir " << endl;
		cout << " Elije una opcion : ";
		cin >> numero;

		if (numero < 0 || numero > 3)
		{
			cout << " Una opcion valida " << endl << endl;
		}
	}

	return numero;
}

void leerDatosRegistro(string & nombre, string & clave)
{
	cout << " Introduce tu nombre de usuario : ";
	cin >> nombre;
	cin.sync();
	cout << " Introduce tu contrasenia : ";
	cin >> clave;
	cin.sync();
}

void menuUsuario(tGestor & gestor)
{
	cout << " MENU USUARIO " << endl << endl;

	int n_partidasActivas = partidasUsuario(gestor);

	bool tienePartidas = false;

	if (n_partidasActivas != 0)
	{
		tienePartidas = true;
		mostrarPartidasEnCurso(gestor);
	}
	else
	{
		cout << " Aun no has empezado ninguna partida! " << endl;
	}

	int opcion;

	do
	{
		opcion = opcionMenuUsuario();

		switch (opcion)
		{
		case 0:
			cout << endl << "		-Sesion cerrada- " << endl << endl;
			gestor.listaAccesoPartidas = {};
			break;

		case 1:
		{
			if (tienePartidas)
			{
				gestor.punteroPartidaActual = NULL;

				elegirPartida(gestor);

				if (gestor.punteroPartidaActual != NULL)
				{
					menuPartida(gestor);
				}
			}
			else
			{
				cout << " Aun no has empezado ninguna partida! " << endl << endl;
			}
		}
		break;

		case 2:
		{
			if (gestor.listaUsuarios.usuario[gestor.enlaceUsuarioActual].espera == no_espera)
			{
				if (nuevaPartida(gestor))
				{
					cout << " Exito al crear la partida " << endl << endl;
					tienePartidas = true;
					mostrarPartidasEnCurso(gestor);
				}
				else
				{
					cout << " Aun no tenemos adversario disponible de tu nivel " << endl;
					cout << " Recuerda que tienes " << 	partidasUsuario(gestor) << 
						" de " << MAX_PAR_US << " disponibles " << endl;
				}
			}
			else
			{
				cout << " Ya estas esperando a que aparezca un adversario de tu nivel " << endl << endl;
			}
		}
		break;

		case 3:
		{
			if (tienePartidas)
			{
				ordenar_Fecha(gestor.listaAccesoPartidas);
				mostrarPartidasEnCurso(gestor);
			}
			else
			{
				cout << " Aun no has empezado ninguna partida! " << endl << endl;
			}

		}
		break;

		case 4:
		{
			if (tienePartidas)
			{
				ordenar_Turno(gestor.listaAccesoPartidas, gestor.listaUsuarios.usuario[gestor.enlaceUsuarioActual].nombre);
				mostrarPartidasEnCurso(gestor);
			}
			else
			{
				cout << " Aun no has empezado ninguna partida! " << endl << endl;
			}
		}
		break;

		default:
			break;
		}

	} while (opcion != 0);
}

int opcionMenuUsuario()
{
	int numero = -1;

	while (numero < 0 || numero > 4)
	{
		cout << endl << endl;
		cout << "	1 - Ver partida " << endl;
		cout << "	2 - Nueva partida " << endl;
		cout << "	3 - Partidas por actualizacion " << endl;
		cout << "	4 - Partidas por turno y fecha " << endl;
		cout << "	0 - Salir " << endl;
		cout << "   Elige una opcion: ";
		cin >> numero;

		if (numero < 0 || numero > 4)
		{
			cout << " Una opcion valida " << endl << endl;
		}
	}

	return numero;
}

void mostrarDatosUsu(tGestor & gestor)
{
	string avisos;
	char letra;
	cout << " Exito al abrir sesion " << endl << endl;

	if (tieneAvisos(gestor, avisos))
	{
		cout << " Tiene avisos : " << endl;
		cout << avisos << endl << endl;
		cout << " Quieres borrarlos? [S/N]: ";
		cin >> letra;
		cin.sync();
		letra = toupper(letra);

		switch (letra)
		{
		case 'S':
			limpiarAvisos(gestor);
			break;
		case 'N':
		default:
			break;
		}
	}

	cout << endl << resumenActividad(gestor);
}

void mostrarPartidasEnCurso(const tGestor & gestor)
{
	int n_partidasActivas = partidasUsuario(gestor);

	cout << endl << endl;
	cout << "  #   T   Jugador1" << setw(20) << "Jugador2" << setw(20) << "Fecha" << endl;
	cout << "-------------------------------------------------------------------------" << endl;

	for (int indice = 0; indice < n_partidasActivas; indice++)
	{
		tPntrPar puntero = gestor.listaAccesoPartidas.partidaUsuario[indice];
		cout << "  " << indice + 1 << "   " << cabecera(gestor, puntero);
	}
}

void elegirPartida(tGestor & gestor)
{
	int numero = -1;
	int maxPartidasUsuario = partidasUsuario(gestor);

	while (numero < 0 || numero > maxPartidasUsuario)
	{
		cout << endl << " Introduce el numero de la partida (0 - Salir) :";
		cin >> numero;
	}

	if (numero != 0)
	{
		apuntaPartida(gestor, numero - 1);
	}
}

void menuPartida(tGestor & gestor)
{
	mostrarPartida(gestor);

	int opcion = opcionMenuPartida();

	switch (opcion)
	{
	case 0:
		cout << endl;
		break;

	case 1:
	{
		if (!esSuTurno(gestor))
		{
			cout << " No es tu turno " << endl << endl;
		}
		else
		{
			int columna = -1;
			leerJugada(columna);
			jugarPartida(gestor, columna);
		}
	}
	break;

	case 2:
	{
		abandonarPartida(gestor);
		eliminar(gestor.listaAccesoPartidas, gestor.punteroPartidaActual);
		cout << endl << " Abandono con exito " << endl << endl;
	}

	break;

	default:
		break;
	}
}

int opcionMenuPartida()
{
	int numero = -1;

	while (numero < 0 || numero > 2)
	{
		cout << endl;
		cout << "	1 - Jugar " << endl;
		cout << "	2 - Abandonar " << endl;
		cout << "	0 - Salir " << endl;
		cout << " Elige una opcion: ";
		cin >> numero;

		if (numero < 0 || numero > 2)
		{
			cout << " Una opcion valida " << endl << endl;
		}
	}

	return numero;
}

void leerJugada(int & col)
{
	do
	{
		cout << endl << "	Introduce una columna: ";
		cin >> col;

		if (col < 1 || col > COLS)
		{
			cout << " Columna no valida, " << col << " esta fuera del rango";
		}

	} while (col < 1 || col > COLS);

	col--;
	cin.sync();
}