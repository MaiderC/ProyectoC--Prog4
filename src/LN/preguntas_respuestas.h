#ifndef PREGUNTAS_RESPUESTAS_H
#define PREGUNTAS_RESPUESTAS_H

#include <iostream>
#include <string.h>
#include "jugador.h"

using namespace std;

/*
	clase madre con una pregunta y una respuesta, la cual será heredada por sus clases hijas 
	que tendrán más o menos preguntas según dificultad escogida
*/
 
class preguntas_respuestas
{
	protected: //para que sean accesibles para las clases derivadas

		string pregunta;
		string respuesta1;
		string dificultad;
		
		//para tener siempre el último id y ponerle al sigueinte el siguiente id
		static int cont;
		int id;

	public:

		//constructores
		preguntas_respuestas();
		preguntas_respuestas(string pregunta, string respuesta1, string dificultad,  bool leerBD);

		//destructor
		virtual ~preguntas_respuestas();

		//constructor copia
		preguntas_respuestas(const preguntas_respuestas &p_r);

		//getters y setters
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

		//metodos de clase madre
		virtual void sumarPunto(jugador jug);
		virtual void prepararRespuestas();

		//sobrecarga de operador =
		bool operator=(const preguntas_respuestas& p_r);

};

#endif