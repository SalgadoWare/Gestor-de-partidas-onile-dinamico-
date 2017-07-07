
//Alejandro Salgado Martin y Jorge Santos
#ifndef listaUsuarios_h
#define listaUsuarios_h

#include "usuario.h"

const int MAX_USUARIOS = 10;

typedef struct {
	tPntrUs usuario;
	int contador, capacidad;
}tListaUsuarios;

bool cargarListaUsuarios(tListaUsuarios & listaUsuarios, std::ifstream & archivo);
/* Carga la lista de usuarios desde el flujo (ya abierto)*/

void apagar(const tListaUsuarios & listaUsuarios, std::ofstream & archivo);
/*Guarda la lista de usuarios en el flujo (ya abierto) y además elimina la memoria dinámica utilizada*/

bool buscar(const tListaUsuarios & listaUsuarios, const std::string & idUser, int &pos);
/* Dado un identificador de usuario	y la lista, devuelve, si dicho identificador existe en la lista,
su posición y el valor true, y si no existe en la lista, la posición que lecorrespondería y el valor false.*/

void insertar(tListaUsuarios & listaUsuarios, const tUsuario & usuario);
//Dada una lista y un usuario, inserta en la posición correspondiente al usuario en la lista si tiene hueco,
//si no, llama a la funcion redimensionar para hacer hueco en la lista y poder insertarle

bool buscarUsuarioEsperando(const tListaUsuarios & listaUsuarios, const tNivel & nivel, int & pos);
//Devuelve true y la posición del primer usuario del nivel dado que está esperando
//para iniciar una partida. Si no existe devuelve false.

bool compruebaIDvalido(const std::string IDnuevo, const tListaUsuarios listaUsuarios);
//Auxiliar de crearCuenta, comprueba que el ID introducido no exita ya en la lista de Usuarios

void redimensionar(tListaUsuarios & listaUsuarios);
//Crea un nuevo array dinámico mayor, y copia en él los datos del antiguo más pequeños

#endif // !listaUsuarios_h
