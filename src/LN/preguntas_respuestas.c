#include "../INCLUDES/preguntas_respuestas.h"
#include <stdlib.h>
#include <string.h>

void prepararRespuestas(t_pregunta_respuestas* pregunta)
{
	char respuestas[3][252];
	int i = 2;
	int igual = 0;
	int r;
	int random[3];

	random[0] = -1;
	random[1] = -1;
	random[2] = -1;
 	
	// Este while llena el array random con números aleatorios de 0 a 2, pero que no se repitan.
	while(i>=0)
	{
		igual = 0;
		r = rand() % 3;

		for(int j = 0; j<3; j++)
		{
			if(r == random[j])
				igual = 1;
		}

		if(igual == 0)
		{
			random[i] = r;
			i--;
		}
	}

	strcpy(respuestas[random[0]], (*pregunta).Respuesta1);
	strcpy(respuestas[random[1]], (*pregunta).Respuesta2);
	strcpy(respuestas[random[2]], (*pregunta).Respuesta3);

	strcpy((*pregunta).Respuesta1, respuestas[0]);
	strcpy((*pregunta).Respuesta2, respuestas[1]);
	strcpy((*pregunta).Respuesta3, respuestas[2]);
}