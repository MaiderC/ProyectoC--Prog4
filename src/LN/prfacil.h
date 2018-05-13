#include "preguntas_respuestas.h"

#include <iostream>
using namespace std;

class prfacil :  public preguntas_respuestas
{
	private:

		string respuesta2;

	public:

		//constructores
		prfacil(): preguntas_respuestas();
		prfacil(string pregunta, string respuesta1, string respuesta2, string dificultad): preguntas_respuestas(pregunta, respuesta1, dificultad);
		
		//destructor
		virtual ~prfacil();

		//constructor copia
		prfacil(const prfacil &pf): preguntas_respuestas(pf);

		//setter y getter
		void setRespuesta2(string RDos);
		string getRespuesta2() const;

		//métodos de clase
		virtual void sumarPunto(jugador jugador);
		virtual void prepararRespuestas(); 

		//sobrecarga de operador =
		bool operator=(const prfacil& pf);

		friend ostream& operator<< (ostream& out, const t_pregunta_respuestas& Pregunta);
		friend istream& operator>>(istream& in, t_pregunta_respuestas& Pregunta);
};
