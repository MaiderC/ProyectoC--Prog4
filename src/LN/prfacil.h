#include "preguntas_respuestas.h"

#include <iostream>
using namespace std;

class prfacil :  public preguntas_respuestas
{
	private:

		string Respuesta2;

	public:

		//constructores
		prfacil(): preguntas_respuestas();
		prfacil(string pregunta, string Respuesta1, string Respuesta2, string dificultad): preguntas_respuestas(pregunta, Respuesta1, dificultad);
		
		//destructor
		~prfacil(): preguntas_respuestas();

		//constructor copia
		prfacil(const prfacil &pf);

		//setter y getter
		void setRespuesta2(string RDos);
		string getRespuesta2() const;

		//métodos de clase
		virtual void sumarPunto(jugador jugador);
		virtual void prepararRespuestas(); 
};
