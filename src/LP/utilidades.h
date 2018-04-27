#ifndef UTILIDADES_H
#define UTILIDADES_H

	#include <string.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include "../INCLUDES/preguntas_respuestas.h"
	#include "../INCLUDES/jugador.h"

	void mostrarMensaje(char * str); 
	void mostrarInt(int i);
	void mostrarPregunta(t_pregunta_respuestas preg);
	void mostrarRespuestas(t_pregunta_respuestas preg);
	void mostrarPuntuacion(t_jugador jugador);
	void mensajeGanador(t_jugador ganador);
	void mensajeEmpate(t_jugador* empatados, int sizeEmpatados, int *opcion);
	void recogerString (char** punt_string, int max_long);
	void recogerNick (char** punt_nick);
	void recogerInt (int* punt_numero);
	int recogerRespuesta (char* respuesta);
	void clear_if_needed(char *str);

#endif