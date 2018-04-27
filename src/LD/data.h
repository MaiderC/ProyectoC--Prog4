#ifndef DATA_H
#define DATA_H

	#include <string.h>
	#include "../INCLUDES/preguntas_respuestas.h"
	#include "../INCLUDES/jugador.h"

	void guardarJugadores(t_jugador* listaJugadores, int numElem);
	int numJugadoresTotal();
	t_jugador* leerJugadores();
	void guardarPreguntaRespuestas(t_pregunta_respuestas* PreguntasParaGuardar, int numNuevas);
	int numPreguntasEnFichero();
	t_pregunta_respuestas* leerPreguntasRespuestas();



#endif