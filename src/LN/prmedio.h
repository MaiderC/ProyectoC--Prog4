#include "preguntas_respuestas.h"

#include <iostream>
using namespace std;

class prmedio :  public preguntas_respuestas
{
	private:

		string Respuesta2;
		string Respuesta3;

	public:

		//constructores
		prmedio(): preguntas_respuestas();
		prmedio(string pregunta, string Respuesta1, string Respuesta2, string Respuesta3, string dificultad): preguntas_respuestas(pregunta, Respuesta1, dificultad){};
	
		//destructor
		~prmedio(): preguntas_respuestas();

		//constructor copia
		prmedio(const prmedio &pm);

		//getter y setter
		void setRespuesta3(string RTres);
		string getRespuesta3() const;

		//metodos de clase
		virtual void sumarPunto(jugador jugador);
		virtual void prepararRespuestas();

		friend ostream& operator<< (ostream& out, const t_pregunta_respuestas& Pregunta);
		friend istream& operator>>(istream& in, t_pregunta_respuestas& Pregunta);
};

