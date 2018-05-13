#ifndef OPERACIONES_H
#define OPERACIONES_H

	#include <preguntas_respuestas.h>
	#include <prfacil.h>
	#include <prmedio.h>
	#include <prdificil.h>
	#include <jugador.h>

	preguntas_respuestas generarPregunta(const vector<preguntas_respuestas>& arrPreg, vector<preguntas_respuestas>& preguntasSalidas);
	int comprobarRespuesta(const string& respuesta);
	int maxPreguntas(const int cantPreguntas, const int sizeTotalPreguntas);
	void ordenarJugadores(vector<jugador>& jugadoresLeidos);
	int maxPuntuacion(const vector<jugador>& jugadores);


#endif