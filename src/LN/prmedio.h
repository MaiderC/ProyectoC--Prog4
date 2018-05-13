#include "preguntas_respuestas.h"

#include <iostream>
using namespace std;

class prmedio :  public preguntas_respuestas
{
	private:

		string respuesta2;
		string respuesta3;

	public:

		//constructores
		prmedio(): preguntas_respuestas(){};
		prmedio(string pregunta, string respuesta1, string respuesta2, string respuesta3, string dificultad): preguntas_respuestas(pregunta, respuesta1, dificultad){};
	
		//destructor
		virtual ~prmedio();

		//constructor copia
		prmedio(const prmedio &pm): preguntas_respuestas(pm){};

		//getter y setter
		void setRespuesta3(string RTres);
		string getRespuesta3() const;

		//metodos de clase
		virtual void sumarPunto(jugador jugador);
		virtual void prepararRespuestas();

		//sobrecarga de operador =
		bool operator=(const prmedio& p_m);

		friend ostream& operator<<(ostream& out, const preguntas_respuestas& Pregunta);
		friend istream& operator>>(istream& in, preguntas_respuestas& Pregunta);

	};

