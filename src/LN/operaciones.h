#ifndef OPERACIONES_H
#define OPERACIONES_H

	#include <preguntas_respuestas.h>
	#include <prfacil.h>
	#include <prmedio.h>
	#include <prdificil.h>
	#include <jugador.h>

	t_pregunta_respuestas generarPregunta(const vector<t_pregunta_respuestas>& arrPreg, vector<t_pregunta_respuestas>& preguntasSalidas);
	int comprobarRespuesta(const string& respuesta);
	int maxPreguntas(const int cantPreguntas, const int sizeTotalPreguntas);
	void ordenarJugadores(vector<t_jugador>& jugadoresLeidos);
	int maxPuntuacion(const vector<t_jugador>& jugadores);


#endif