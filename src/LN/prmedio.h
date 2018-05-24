#ifndef MEDIO_H
#define MEDIO_H
#include "preguntas_respuestas.h"
#include <iostream>
#include <string.h>
#include "jugador.h"

using namespace std;

class prmedio :  public preguntas_respuestas
{
	private:

		string respuesta2;
		string respuesta3;

	public:

		//constructores
		prmedio();
		prmedio(string pregunta, string respuesta1, string respuesta2, string respuesta3, string dificultad, bool leerBD);
	
		//destructor
		virtual ~prmedio();

		//constructor copia
		prmedio(const prmedio &pm);

		//getter y setter
		void setRespuesta2(string RDos);
		string getRespuesta2() const;
		void setRespuesta3(string RTres);
		string getRespuesta3() const;

		//metodos de clase
		virtual void sumarPunto(jugador jugador);
		virtual void prepararRespuestas(preguntas_respuestas pregunta, string medio);

		//sobrecarga de operador =
		bool operator=(const prmedio& p_m);

		friend ostream& operator<<(ostream& out, const preguntas_respuestas& Pregunta);
		friend istream& operator>>(istream& in, preguntas_respuestas& Pregunta);

	};
#endif
