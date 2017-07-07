
#ifndef fecha_h
#define fecha_h

#include <fstream>
#include <ctime>
#include <string>
#include <iomanip>
#include <sstream>
#include <string.h>

typedef time_t tFecha;

tFecha fechaActual();
/*devuelve el número de segundos desde el 1 Enero de 1970*/

std::string stringFecha(tFecha fecha, bool hora);
/*Dada la fecha (segundos desde 1970...) muestra la fecha en en formato Año / Mes / Día,
con o sin hora (booleano)*/

bool esAntigua(tFecha fechaActualizacion, tFecha fechaActual);
//Devuelve un booleano referente a si hay o si no hay una una diferencia mayor de 30 dias comparando
//la fecha actual y la fecha de actualizacion dada de una partida

#endif // fecha_h