#ifndef PREGUNTAS_RESPUESTAS_H
#define PREGUNTAS_RESPUESTAS_H

#include <iostream>
#include <string.h>
#include "jugador.h"

using namespace std;
 
class preguntas_respuestas
{
	protected: 

		string pregunta;
		string respuesta1;
		string dificultad;
		
		static int cont;
		int id;

	public:

		preguntas_respuestas();
		preguntas_respuestas(string pregunta, string respuesta1, int ID, bool leerBD);

		virtual ~preguntas_respuestas();

		preguntas_respuestas(const preguntas_respuestas &p_r);

		void setPregunta(string pregunta);
		void setRespuesta1(string RUno);
		void setDificultad(string dificultad);
		void setCont(int cont);
		void setID(int ID);

		string getPregunta() const;
		string getRespuesta1() const;
		string getDificultad() const;
		int getCont () const;
		int getID () const;

		virtual void sumarPunto(jugador& jugador) = 0;
		virtual void prepararRespuestas() = 0;

		preguntas_respuestas& operator=(const preguntas_respuestas& p_r);
};

#endif