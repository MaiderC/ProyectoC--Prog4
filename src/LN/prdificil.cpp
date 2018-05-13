#include "prdificil.h"

// #include <iostream>
// using namespace std;

#define DEFAULT_RESPUESTA2 defaultAnswer2
#define DEFAULT_RESPUESTA3 defaultAnswer3
#define DEFAULT_RESPUESTA4 defaultAnswer4
#define DEFAULT_DIFICULTAD ###

//constructores
prdificil::preguntas_respuestas()
{
  this -> respuesta2 = DEFAULT_RESPUESTA2;
  this -> respuesta3 = DEFAULT_RESPUESTA3;
  this -> respuesta4 = DEFAULT_RESPUESTA4;
}
		
prdificil::preguntas_respuestas(string pregunta, string respuesta1, string respuesta2, string respuesta3, string respuesta4, string dificultad): preguntas_respuestas(pregunta, respuesta1, dificultad)
{
  // this -> pregunta = pregunta;
  // this -> respuesta1 = respuesta1;
  this -> respuesta2 = respuesta2;
  this -> respuesta3 = respuesta3;
  this -> respuesta4 = respuesta4;
  // this -> dificultad = dificultad;
}

//destructor
 prdificil::~preguntas_respuestas()
{
  delete respuesta2;
  delete respuesta3;
  delete respuesta4;
}

//constructor copia
prdificil::prdificil(const prdificil &pd): preguntas_respuestas(pd)
{
	this -> respuesta2 = pd.respuesta2;
	this -> respuesta3 = pd.respuesta3;
	this -> respuesta4 = pd.respuesta4;
}

//getter y setter
void prdificil::setRespuesta4(string RCuatro)
{
	this -> respuesta4 = RCuatro;
}

string prdificil::getRespuesta4() const
{
	return respuesta4;
}

//metodos 

 void prdificil::sumarPunto(jugador jugador)
{
	jugador.puntuacion =+ 3;
}

 void prdificil::prepararRespuestas(pregunta_respuestas pregunta, string dificil)
{
	int i = 3;
	int igual = 0;
	int r;
	int random[4];
	string respuestas[4];

	random[0] = -1;
	random[1] = -1;
	random[2] = -1;
	random[3] = -1;

 	
	// Este while llena el array random con números aleatorios de 0 a 2, pero que no se repitan.
	while(i>=0)
	{
		igual = 0;
		r = rand() % 4;

		for(int j = 0; j<4; j++)
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

	respuestas[random[0]] = this -> respuesta1;
	respuestas[random[1]] = this -> respuesta2;
	respuestas[random[2]] = this -> respuesta3;
	respuestas[random[3]] = this -> respuesta4;
		
	this->respuesta1 = respuestas[0];
	this->respuesta2 = respuestas[1];
	this->respuesta3 = respuestas[2];
	this->respuesta4 = respuestas[3];
}

//sobrecarga de operador =
bool prdificil::operator=(const prdificil& pd)
{
	this -> respuesta2 = pd.respuesta2;
	this -> respuesta3 = pd.respuesta3;
	this -> respuesta4 = pd.respuesta4;
}

ostream& operator<<(ostream& out, const t_pregunta_respuestas& Pregunta)
{
	out << Pregunta.Pregunta << endl;

	out << "a) ";
	if((Pregunta.Respuesta1.c_str())[0] == '#')
	{
		string aux = Pregunta.Respuesta1;

		aux.erase(0, 1);

		out << aux << endl;
	} else
	{
		out << Pregunta.Respuesta1 << endl;
	}

	out << "b) ";
	if((Pregunta.Respuesta2.c_str())[0] == '#')
	{
		string aux = Pregunta.Respuesta2;

		aux.erase(0, 1);

		out << aux << endl;
	} else
	{
		out << Pregunta.Respuesta2 << endl;
	}

	out << "c) ";
	if((Pregunta.Respuesta3.c_str())[0] == '#')
	{
		string aux = Pregunta.Respuesta3;

		aux.erase(0, 1);

		out << aux << endl;
	} else
	{
		out << Pregunta.Respuesta3 << endl;
	}

	out << "d) ";
	if((Pregunta.Respuesta4.c_str())[0] == '#')
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

	mostrarMensaje("Introduce otra respuesta (una incorrecta): ");
	in >> Pregunta.Respuesta4;

	return in;
}