#ifndef PREGUNTAS_RESPUESTAS_H
#define PREGUNTAS_RESPUESTAS_H

#include <iostream>
using namespace std;

/*
	clase madre con una pregunta y una respuesta, la cual será heredada por sus clases hijas 
	que tendrán más o menos preguntas según dificultad escogida
*/

class preguntas_respuestas
{
	protected: //para que sean accesibles para las clases derivadas

		string Pregunta;
		string Respuesta1;
		string dificultad;

	public:

		//constructores
		preguntas_respuestas();
		preguntas_respuestas(string pregunta, string Respuesta1, string dificultad);

		//destructor
		virtual ~preguntas_respuestas();

		//constructor copia
		preguntas_respuestas(const preguntas_respuestas &p_r);

		//getters y setters
		void setPregunta(string pregunta);
		void setRespuesta1(string RUno);
		void setDificultad(string dificultad);

		string getPregunta() const;
		string getRespuesta1() const;
		string getDificultad() const;

		//metodos de clase madre
		virtual void sumarPunto(jugador jugador);
		virtual void prepararRespuestas();
};

#endif