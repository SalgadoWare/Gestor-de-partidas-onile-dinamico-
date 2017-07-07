
//Alejandro Salgado Martin y Jorge Santos
#include "listaPartidas.h"
#include "fecha.h"
using namespace std;

bool cargarListaPartidas(tListaPartidas & listaPartidas, ifstream & archivo)
{
	bool exito = false;
	int n_partidas;

	archivo >> n_partidas;

	if (n_partidas >= MAX_PARTIDAS_GUARDADAS)
	{
		exito = false;
	}
	else
	{
		exito = true;
		int indice = 0;
		listaPartidas.contador = n_partidas;

		while (exito && indice < listaPartidas.contador)
		{
			tPartida partida = {};

			exito = carga(partida, archivo);

			if (exito)
			{
				listaPartidas.partida[indice] = new tPartida(partida);
				indice++;
			}
		}
	}

	return exito;
}

void apagar(const tListaPartidas & listaPartidas, ofstream & archivo)
{
	archivo << listaPartidas.contador << endl;

	for (int indice = 0; indice < listaPartidas.contador; indice++)
	{
		guarda(*listaPartidas.partida[indice], archivo);
		delete listaPartidas.partida[indice];
	}
}

bool insertar(tListaPartidas & listaPartidas, const tPartida & partida)
{
	bool exito = false;

	if (listaPartidas.contador < MAX_PARTIDAS_GUARDADAS)
	{
		exito = true;
		listaPartidas.partida[listaPartidas.contador] = new tPartida(partida);
		listaPartidas.contador++;
	}

	return exito;
}

void apagar_Historicos(tListaPartidas & listaPartidas, std::ofstream & archivo)
{
	for (int indice = 0; indice < listaPartidas.contador; indice++)
	{
		if (listaPartidas.partida[indice]->estadoPartida == terminada)
		{
			guarda(*listaPartidas.partida[indice], archivo);
		}
	}

	int indice = 0;

	while (indice < listaPartidas.contador)
	{
		if (listaPartidas.partida[indice]->estadoPartida == terminada)
		{
			delete listaPartidas.partida[indice];
			/*borramos la partida terminada*/

			for (int i = indice; i < listaPartidas.contador - 1; i++)
			{
				listaPartidas.partida[i] = listaPartidas.partida[i + 1];
			}

			indice = 0;
			listaPartidas.contador--;
			/*y reconstruimos la lista sin dejar huecos*/
		}
		else
		{
			indice++;
		}
	}
}