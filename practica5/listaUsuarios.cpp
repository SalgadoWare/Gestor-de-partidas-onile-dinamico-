
//Alejandro Salgado Martin y Jorge Santos
#include "listaUsuarios.h"
using namespace std;

int buscarPosicionParaInsertar(tListaUsuarios & listaUsuarios, const tUsuario & usuario);
//Auxiliar de la funcion insertar, devuelve la posicion donde se va a insertar un nuevo usuario,
//es una búsqueda binaria que se aprovecha de que la lista de usuarios esté ordenada alfabéticamente

bool cargarListaUsuarios(tListaUsuarios & listaUsuarios, ifstream & archivo)
{
	bool exito = false;
	int n_usuarios;
	int indice = 0;

	archivo >> n_usuarios;

	if (n_usuarios < MAX_USUARIOS)
	{
		exito = true;
		listaUsuarios.contador = n_usuarios;
		listaUsuarios.capacidad = n_usuarios;
		listaUsuarios.usuario = new tUsuario[n_usuarios];

		while (exito && indice < listaUsuarios.contador)
		{
			tUsuario usuario = {};

			exito = cargarUs(usuario, archivo);

			if (exito)
			{
				listaUsuarios.usuario[indice] = usuario;
				indice++;
			}
		}
	}

	return exito;
}

void apagar(const tListaUsuarios & listaUsuarios, ofstream & archivo)
{
	archivo << listaUsuarios.contador << endl;

	for (int indice = 0; indice < listaUsuarios.contador; indice++)
	{
		guardarUs(listaUsuarios.usuario[indice], archivo);
	}

	delete[] listaUsuarios.usuario;
}

bool buscar(const tListaUsuarios & listaUsuarios, const string & idUser, int &pos)
{
	int inicio = 0;
	int mitad;
	int fin = listaUsuarios.contador - 1;
	bool encontrado = false;

	while ((inicio <= fin) && !encontrado)
	{
		mitad = (inicio + fin) / 2;

		if (idUser == listaUsuarios.usuario[mitad].nombre)
		{
			encontrado = true;
			pos = mitad;
		}
		else
		{
			if (idUser < listaUsuarios.usuario[mitad].nombre)
			{
				fin = mitad - 1;
			}
			else
			{
				inicio = mitad + 1;
			}
		}
	}

	return encontrado;
}

void insertar(tListaUsuarios & listaUsuarios, const tUsuario & usuario)
{
	bool exito = (listaUsuarios.contador < listaUsuarios.capacidad);

	if (exito)
	{
		int pos = buscarPosicionParaInsertar(listaUsuarios, usuario);

		for (int indice = listaUsuarios.contador; indice > pos; indice--)
		{
			listaUsuarios.usuario[indice] = listaUsuarios.usuario[indice - 1];
		}

		listaUsuarios.usuario[pos] = usuario;
		listaUsuarios.contador++;
	}
	else
	{
		redimensionar(listaUsuarios);
		insertar(listaUsuarios, usuario);
		//Recursividad
	}
}

int buscarPosicionParaInsertar(tListaUsuarios & listaUsuarios, const tUsuario & usuario)
{
	int inicio = 0;
	int fin = listaUsuarios.contador - 1;
	int mitad, pos;
	bool encontrado = false;

	while ((inicio <= fin) && !encontrado)
	{
		mitad = (inicio + fin) / 2;

		if (mitad != 0 && usuario.nombre > listaUsuarios.usuario[mitad - 1].nombre
			&& usuario.nombre < listaUsuarios.usuario[mitad].nombre)
		{
			encontrado = true;
			pos = mitad;
		}
		else
		{
			if (usuario.nombre < listaUsuarios.usuario[mitad].nombre)
			{
				fin = mitad - 1;
			}
			else
			{
				inicio = mitad + 1;
			}
		}
	}

	if (inicio > fin)
	{
		if (usuario.nombre < listaUsuarios.usuario[1].nombre) pos = 0;
		else pos = listaUsuarios.contador;
	}

	return pos;
}

bool buscarUsuarioEsperando(const tListaUsuarios & listaUsuarios, const tNivel & nivel, int & pos)
{
	bool encontrado = false;
	int indice = 0;

	while (!encontrado && indice < listaUsuarios.contador)
	{
		if ((listaUsuarios.usuario[indice].espera == esperando) &&
			(listaUsuarios.usuario[indice].nivel == nivel))
		{
			encontrado = true;

			pos = indice;
		}
		else
		{
			indice++;
		}
	}

	return encontrado;
}

bool compruebaIDvalido(const std::string IDnuevo, const tListaUsuarios listaUsuarios)
{
	int inicio = 0, fin = listaUsuarios.contador - 1, mitad;
	bool encontrado = false;
	while ((inicio <= fin) && !encontrado)
	{
		mitad = (inicio + fin) / 2;
		if (IDnuevo == listaUsuarios.usuario[mitad].nombre) {
			encontrado = true;
		}
		else
		{
			if (IDnuevo < listaUsuarios.usuario[mitad].nombre)
			{
				fin = mitad - 1;
			}
			else
			{
				inicio = mitad + 1;
			}
		}
	}

	return !encontrado;
}

void redimensionar(tListaUsuarios & listaUsuarios)
{
	int viejaCapacidad = listaUsuarios.capacidad;
	listaUsuarios.capacidad = ((listaUsuarios.capacidad * 3) / 2) + 1;

	tPntrUs punteroAnuevoArray = new tUsuario[listaUsuarios.capacidad];

	for (int indice = 0; indice < viejaCapacidad; indice++)
	{
		punteroAnuevoArray[indice] = listaUsuarios.usuario[indice];
	}

	delete[] listaUsuarios.usuario;

	listaUsuarios.usuario = punteroAnuevoArray;
}