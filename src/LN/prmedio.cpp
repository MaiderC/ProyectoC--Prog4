#include "prmedio.h"

using namespace std;

#include <stdlib.h>
#include <string.h>

#define DEFAULT_RESPUESTA2 defaultAnswer2
#define DEFAULT_RESPUESTA3 defaultAnswer3
#define DEFAULT_DIFICULTAD ##


//constructores
prmedio:: preguntas_respuestas()
{
  this -> Respuesta2 = DEFAULT_RESPUESTA2;
  this -> Respuesta3 = DEFAULT_RESPUESTA3;
}
		
prmedio:: preguntas_respuestas(string pregunta, string Respuesta1, string Respuesta2, string Respuesta3, string dificultad)
{
  this -> Respuesta2 = Respuesta2;
  this -> Respuesta3 = Respuesta3;
}

//destructor
prmedio::~preguntas_respuestas()
{
  // delete pregunta;
  // delete Respuesta1;
  delete Respuesta2;
  delete Respuesta3;
  // delete dificultad;
  preguntas_respuestas::~prmedio();
}

//constructor copia
prmedio(const prmedio &pm)
{
	this -> Respuesta3 = pm.Respuesta3;
	//para los atributos que están en la madre
	preguntas_respuestas :: prmedio();
}

//getter y setter
void prmedio::void setRespuesta3(string RTres)
{
	this -> RTres = Respuesta3;
}

string prmedio::void getRespuesta3() const
{
	return Respuesta3;
}

//metodos

virtual void sumarPunto(jugador jugador)
{
	jugador.puntuacion =+ 2;
}

virtual void prepararRespuestas(pregunta_respuestas pregunta, string medio)
{
	char respuestas[3][252];
	int i = 2;
	int igual = 0;
	int r;
	int random[3];

	random[0] = -1;
	random[1] = -1;
	random[2] = -1;
 	
	// Este while llena el array random con números aleatorios de 0 a 2, pero que no se repitan.
	while(i>=0)
	{
		igual = 0;
		r = rand() % 3;

		for(int j = 0; j<3; j++)
		{
			if(r == random[j])
				igual = 1;
		}

		if(igual == 0)
		{
			random[i] = r;
			i--;
		}
	}

	strcpy(respuestas[random[0]], (*pregunta).Respuesta1);
	strcpy(respuestas[random[1]], (*pregunta).Respuesta2);
	strcpy(respuestas[random[2]], (*pregunta).Respuesta3);

	strcpy((*pregunta).Respuesta1, respuestas[0]);
	strcpy((*pregunta).Respuesta2, respuestas[1]);
	strcpy((*pregunta).Respuesta3, respuestas[2]);
}

ostream& operator<< (ostream& out, const t_pregunta_respuestas& Pregunta)
{
	out << Pregunta.Pregunta << endl;

	out << "a) ";
	if(Pregunta.Respuesta1[0] == '#')
	{
		string aux = Pregunta.Respuesta1;

		aux.erase(0, 1);

		out << aux << endl;
	} else
	{
		out << Pregunta.Respuesta1 << endl;
	}

	out << "b) ";
	if(Pregunta.Respuesta2[0] == '#')
	{
		string aux = Pregunta.Respuesta2;

		aux.erase(0, 1);

		out << aux << endl;
	} else
	{
		out << Pregunta.Respuesta2 << endl;
	}

	out << "c) ";
	if(Pregunta.Respuesta3[0] == '#')
	{
		string aux = Pregunta.Respuesta3;

		aux.erase(0, 1);

		out << aux << endl;
	} else
	{
		out << Pregunta.Respuesta3 << endl;
	}

	return out;
}

istream& operator>>(istream& in, t_pregunta_respuestas& Pregunta)
{
	mostrarMensaje("Introduce la pregunta a insertar: ");
	in >> Pregunta.Pregunta;

	mostrarMensaje("*La respuesta no debe contener la letra de la opcion (a o b) ni signos de puntuacion al inicio (salvo que se trate de un guion, por ser la respuesta un numero negativo)");
	mostrarMensaje("Introduce la respuesta correcta: ");
	in >> Pregunta.Respuesta1;

	Pregunta.Respuesta1 = '#' + Pregunta.Respuesta1;

	mostrarMensaje("Introduce otra respuesta (una incorrecta): ");
	in >> Pregunta.Respuesta2;

	mostrarMensaje("Introduce otra respuesta (una incorrecta): ");
	in >> Pregunta.Respuesta3;

	return in;
}