
//Alejandro Salgado Martin y Jorge Santos
#include "listaAccesoPartidas.h"
using namespace std;

void iniciar(tListaAccesoPartidas & lista)
{
	lista.contador = 0;
}

bool insertar(tListaAccesoPartidas & lista, const tPntrPar & puntero)
{
	bool exito = !llena(lista);

	if (exito)
	{
		lista.partidaUsuario[lista.contador] = puntero;
		lista.contador++;
	}

	return exito;
}

bool eliminar(tListaAccesoPartidas & lista, const tPntrPar & puntero)
{
	bool encontrado = false;
	int pos = 0;
	string id = puntero->iden;

	if (buscar(lista, id, pos))
	{
		encontrado = true;

		for (pos; pos < lista.contador - 1; pos++)
		{
			lista.partidaUsuario[pos] = lista.partidaUsuario[pos + 1];
		}

		lista.contador--;
	}
	else
	{
		encontrado = false;
	}

	return encontrado;
}

bool buscar(const tListaAccesoPartidas & lista, const std::string & id, int & pos)
{
	bool encontrado = false;

	if (id == lista.partidaUsuario[pos]->iden)
	{
		encontrado = true;
	}
	else
	{
		pos++;

		if (pos < lista.contador)
		{
			encontrado = buscar(lista, id, pos);
		}
	}

	return encontrado;
}

bool llena(const tListaAccesoPartidas & lista)
{
	return lista.contador >= MAX_PAR_US;
}

void ordenar_Fecha(tListaAccesoPartidas & lista)
{
	//Utilizamos el algoritmo de inserccion con intercambios (Natural)

	for (int indice = 1; indice < lista.contador; indice++)
	{
		int pos = indice;

		while ((pos > 0) && (lista.partidaUsuario[pos - 1]->fechaActualizacion
			< lista.partidaUsuario[pos]->fechaActualizacion))
		{
			tPntrPar tmp = lista.partidaUsuario[pos];

			lista.partidaUsuario[pos] = lista.partidaUsuario[pos - 1];

			lista.partidaUsuario[pos - 1] = tmp;

			pos--;
		}
	}
}

void ordenar_Turno(tListaAccesoPartidas & lista, const  string & usuarioActual)
{
	//Utilizamos el algoritmo de inserccion con intercambios (Natural)

	for (int indice = 1; indice < lista.contador; indice++)
	{
		int pos = indice;

		while ((pos > 0) &&
			(!devuelveTurno(*lista.partidaUsuario[pos - 1], usuarioActual)
				&& devuelveTurno(*lista.partidaUsuario[pos], usuarioActual)))
		{
			tPntrPar tmp = lista.partidaUsuario[pos];

			lista.partidaUsuario[pos] = lista.partidaUsuario[pos - 1];

			lista.partidaUsuario[pos - 1] = tmp;

			pos--;
		}
	}
}