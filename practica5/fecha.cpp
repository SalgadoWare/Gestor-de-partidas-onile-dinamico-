
#include "fecha.h"
using namespace std;

tFecha fechaActual()
{
	return time(0);
}

string stringFecha(tFecha fecha, bool hora)
{
	ostringstream resultado;
	tm ltm;
	localtime_s(&ltm, &fecha);

	resultado << setfill('0') << setw(4) << 1900 + ltm.tm_year << '/'
		<< setw(2) << 1 + ltm.tm_mon << '/' << setw(2) << ltm.tm_mday;

	if (hora) resultado << " (" << setw(2) << ltm.tm_hour << ':' << setw(2)
		<< ltm.tm_min << ':' << setw(2) << ltm.tm_sec << ')';

	return resultado.str();
}

bool esAntigua(tFecha fechaActualizacion, tFecha fechaActual)
{
	tm ltm;
	localtime_s(&ltm, &fechaActual);

	tm ltm_antiguo;
	localtime_s(&ltm_antiguo, &fechaActualizacion);

	bool encontrada;

	if ((1 + ltm.tm_mon) - (1 + ltm_antiguo.tm_mon) == 1)
	{
		/*Llegados a este punto existe un mes de diferencia entre ambas fechas*/
		int dias = ltm.tm_mday + (30 - ltm_antiguo.tm_mday);
		/*De esta forma conseguimos la diferencia de días entre dos fechas*/

		if (dias >= 30)
		{
			encontrada = true;
		}
		else
		{
			encontrada = false;
		}
	}
	else
	{
		if ((1 + ltm.tm_mon) - (1 + ltm_antiguo.tm_mon) == 0)
		{
			/*Llegados a este punto las fechas son del mismo mes*/
			encontrada = false;
		}
		else
		{
			/*Llegados a este punto entre las fechas existe más de 1 mes de diferencia*/
			encontrada = true;
		}
	}

	return encontrada;
}
