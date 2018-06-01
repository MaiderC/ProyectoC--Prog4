#ifndef UTILIDADES_H
#define UTILIDADES_H

	#include "../LN/jugador.h"
	#include <iostream>
	#include <vector>
	#include "../LN/preguntas_respuestas.h"
	#include "../LN/prfacil.h"
	#include "../LN/prmedio.h"
	#include "../LN/prdificil.h"
	#include <string.h>

	using namespace std;

	namespace utilidades
	{
		void mostrarMensaje(const string& str);
		void mostrarInt(const int& i);
		void mostrarPregunta(const prfacil& Pregunta);
		void mostrarPregunta(const prmedio& Pregunta);
		void mostrarPregunta(const prdificil& Pregunta);
		void mostrarTodasPreguntas(const vector<preguntas_respuestas*> TodasPreguntas);
		void mostrarPuntuacion(const jugador& jugador);
		void mensajeGanador(const jugador& ganador);
		int mensajeEmpate(const vector<jugador>& empatados);
		void recogerString(string& string_recoger);
		void recogerInt(int& numero_recoger);
		char recogerOpcionRespuesta(int& respValida, string dificultad);
		void recogerPregunta(prfacil& Pregunta);
		void recogerPregunta(prmedio& Pregunta);
		void recogerPregunta(prdificil& Pregunta);
	}
	
#endif