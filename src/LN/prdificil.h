#include "preguntas_respuestas.h"

#include <iostream>
using namespace std;

class prdificil :  public preguntas_respuestas
{
	private:
		
		string Respuesta2;
		string Respuesta3;
		string Respuesta4;

	public:

		//constructores
		prdificil(): preguntas_respuestas();
		prdificil(string pregunta, string Respuesta1, string Respuesta2, string Respuesta3, string Respuesta4, string dificultad): preguntas_respuestas(pregunta, Respuesta1, Respuesta2, Respuesta3, Respuesta4, dificultad){};
	
		//destructor
		~prdificil(): preguntas_respuestas();

		//constructor copia
		prdificil(const prdificil &pd);

		//getter y setter
		void setRespuesta4(string RCuatro);
		string getRespuesta4() const;

		//metodos de clse
		virtual void sumarPunto(jugador jugador);
		virtual void prepararRespuestas();
};

