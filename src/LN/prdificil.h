#ifndef DIFICIL_H
#define DIFICIL_H

#include "preguntas_respuestas.h"
#include <iostream>
#include "jugador.h"

using namespace std;

class prdificil :  public preguntas_respuestas
{
	private:
		
		string respuesta2;
		string respuesta3;
		string respuesta4;

	public:

		//constructores
		prdificil(): preguntas_respuestas(){};
		prdificil(string pregunta, string respuesta1, string respuesta2, string respuesta3, string respuesta4, string dificultad): preguntas_respuestas(pregunta, respuesta1, dificultad){};
	
		//destructor
		virtual ~prdificil();

		//constructor copia
		prdificil(const prdificil &pd): preguntas_respuestas(pd){};

		//getter y setter
		void setRespuesta4(string RCuatro);
		string getRespuesta4() const;

		//metodos de clse
		virtual void sumarPunto(jugador jugador);
		virtual void prepararRespuestas();

		//sobrecarga de operador =
		bool operator=(const prdificil& pd);

		friend ostream& operator<<(ostream& out, const preguntas_respuestas& Pregunta);
		friend istream& operator>>(istream& in, preguntas_respuestas& Pregunta);

};

#endif