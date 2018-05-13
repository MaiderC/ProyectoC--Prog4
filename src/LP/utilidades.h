#ifndef UTILIDADES_H
#define UTILIDADES_H

namespace utilidades
{
	#include <iostream>
	#include "../LN/preguntas_respuestas.h"
	#include "../LN/jugador.h"
	#include "../LN/prfacil.h"
	#include "../LN/prmedio.h"
	#include "../LN/prdificil.h"
	#include "../LN/jugador.h"

	void mostrarMensaje(const string& str);
	void mostrarInt(const int& i);
	void mostrarPregunta(const preguntas_respuestas& Pregunta);
	void mostrarTodasPreguntas(const vector<preguntas_respuestas> TodasPreguntas);
	void mostrarPuntuacion(const jugador& jugador);
	void mensajeGanador(const jugador& ganador);
	int mensajeEmpate(const vector<jugador>& empatados);
	void recogerString(string& string_recoger);
	void recogerNick(string& nick_recoger);
	void recogerInt(int& numero_recoger);
	int recogerOpcionRespuesta(string& respuesta_recoger, string dificultad) ;
	void recogerPregunta(preguntas_respuestas& Pregunta);
}

#endif