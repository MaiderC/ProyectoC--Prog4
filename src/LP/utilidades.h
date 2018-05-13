#ifndef UTILIDADES_H
#define UTILIDADES_H

	#include <string.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <../LN/preguntas_respuestas.h>
	#include <../LN/jugador.h>
	#include <../LN/prfacil.h>
	#include <../LN/prmedio.h>
	#include <../LN/prdificil.h>

	void mostrarMensaje(const string& str);
	void mostrarInt(const int& i);
	void mostrarPregunta(const t_pregunta_respuestas& Pregunta);
	void mostrarTodasPreguntas(const vector<t_pregunta_respuestas> TodasPreguntas);
	void mostrarPuntuacion(const t_jugador& jugador);
	void mensajeGanador(const t_jugador& ganador);
	int mensajeEmpate(const vector<t_jugador>& empatados);
	void recogerString(string& string_recoger);
	void recogerNick(string& nick_recoger);
	void recogerInt(int& numero_recoger);
	int recogerOpcionRespuesta(string& respuesta_recoger, string dificultad) ;
	void recogerPregunta(t_pregunta_respuestas& Pregunta);

#endif