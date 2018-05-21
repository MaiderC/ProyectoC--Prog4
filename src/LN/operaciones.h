#ifndef OPERACIONES_H
#define OPERACIONES_H

	#include "preguntas_respuestas.h"
	#include "prfacil.h"
	#include "prmedio.h"
	#include "prdificil.h"
	#include "jugador.h"
	#include <vector>
	#include <iostream>
	#include <string.h>

	using namespace std;

	void siguienteID(const vector<preguntas_respuestas>& listaTodasRespuestas);
	preguntas_respuestas generarPregunta(const vector<preguntas_respuestas>& listaTodasPreguntas, vector<preguntas_respuestas>& preguntasSalidas);
	int comprobarRespuesta(const string& respuesta);
	int maxPreguntas(const int cantPreguntas, const int sizeTotalPreguntas);
	void ordenarJugadores(vector<jugador>& jugadoresLeidos);
	int maxPuntuacion(const vector<jugador>& jugadores);
	vector<jugador> actualizarPuntuacion(const vector<jugador>& listaTodosJugadores, vector<jugador>& listaJugadoresSesion);
	vector<jugador> actualizarPuntuacion(const vector<jugador>& listaTodosJugadores, jugador jugadorPrincipal);


#endif