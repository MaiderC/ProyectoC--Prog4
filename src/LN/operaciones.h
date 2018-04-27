#ifndef OPERACIONES_H
#define OPERACIONES_H

	#include "../INCLUDES/preguntas_respuestas.h"
	#include "../INCLUDES/jugador.h"

	t_pregunta_respuestas generarPregunta (t_pregunta_respuestas *arrPreg, t_pregunta_respuestas* *preguntasSalidas, int* sizePreguntasSalidas, int sizeTotalPreguntas);
	int comprobarRespuesta(char* respuesta);
	int maxPreguntas (int cantPreguntas, int sizeTotalPreguntas);
	void ordenarJugadores(t_jugador* jugadoresLeidos, int size);
	int maxPuntuacion(t_jugador* jugadores, int sizeJugadores);

#endif