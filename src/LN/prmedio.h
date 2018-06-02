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

		prmedio();
		prmedio(string pregunta, string respuesta1, string respuesta2, string respuesta3, int ID, bool leerBD);
	
		virtual ~prmedio();

		prmedio(const prmedio &pm);

		void setRespuesta2(string RDos);
		string getRespuesta2() const;
		void setRespuesta3(string RTres);
		string getRespuesta3() const;

		virtual void sumarPunto(jugador& jugador);
		virtual void prepararRespuestas();

		prmedio& operator=(const prmedio& pm);

		friend ostream& operator<<(ostream& out, const prmedio& preguntamedio);
		friend istream& operator>>(istream& in, prmedio& preguntamedio);

	};
#endif
