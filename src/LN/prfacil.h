#ifndef FACIL_H
#define FACIL_H
#include "preguntas_respuestas.h"
#include <iostream>
#include <string.h>
#include "jugador.h"

using namespace std;

class prfacil :  public preguntas_respuestas
{
	private:

		string respuesta2;

	public:

		prfacil();
		prfacil(string pregunta, string respuesta1, string respuesta2, int ID, bool leerBD);
		
		virtual ~prfacil();

		prfacil(const prfacil &pf);

		void setRespuesta2(string RDos);
		string getRespuesta2() const;

		virtual void sumarPunto(jugador& jugador);
		virtual void prepararRespuestas(); 

		prfacil& operator=(const prfacil& pf);

		friend ostream& operator<< (ostream& out, const prfacil& preguntafacil);
		friend istream& operator>> (istream& in, prfacil& preguntafacil);
};
#endif