#include "prdificil.h"
#include "preguntas_respuestas.h"
#include <iostream>
#include <string.h>
#include "jugador.h"

using namespace std;

#define DEFAULT_RESPUESTA2 "defaultAnswer2"
#define DEFAULT_RESPUESTA3 "defaultAnswer3"
#define DEFAULT_RESPUESTA4 "defaultAnswer4"
#define DEFAULT_DIFICULTAD "###"

//constructores
prdificil::prdificil()
{
  this -> respuesta2 = DEFAULT_RESPUESTA2;
  this -> respuesta3 = DEFAULT_RESPUESTA3;
  this -> respuesta4 = DEFAULT_RESPUESTA4;
}
		
prdificil::prdificil(string pregunta, string respuesta1, string respuesta2, string respuesta3, string respuesta4, string dificultad, bool leerBD): preguntas_respuestas(pregunta, respuesta1, dificultad, leerBD)
{
  // this -> pregunta = pregunta;
  // this -> respuesta1 = respuesta1;
  this -> respuesta2 = respuesta2;
  this -> respuesta3 = respuesta3;
  this -> respuesta4 = respuesta4;
  // this -> dificultad = dificultad;
}

//destructor
 prdificil::~prdificil()
{
}

//constructor copia
prdificil::prdificil(const prdificil &pd): preguntas_respuestas(pd)
{
	this -> respuesta2 = pd.respuesta2;
	this -> respuesta3 = pd.respuesta3;
	this -> respuesta4 = pd.respuesta4;
}

//getter y setter
void prdificil::setRespuesta2(string RDos)
{
	this -> respuesta2 = RDos;
}

string prdificil::getRespuesta2() const
{
	return respuesta2;
}

void prdificil::setRespuesta3(string RTres)
{
	this -> respuesta3 = RTres;
}

string prdificil::getRespuesta3() const
{
	return respuesta3;
}

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
	jugador.setPuntuacion(jugador.getPuntuacion() + 3);
}

 void prdificil::prepararRespuestas(preguntas_respuestas& pregunta)
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

ostream& operator<<(ostream& out, const prdificil& preguntadificil)
{
	// prdificil* preguntadificil = dynamic_cast <prdificil*>(Pregunta);
	
	out << (preguntadificil).getPregunta() << endl;

	out << "a) ";
	if((preguntadificil).getRespuesta1()[0] == '#')
	{
		string aux = (preguntadificil).getRespuesta1();

		aux.erase(0, 1);

		out << aux << endl;
	} else
	{
		out << (preguntadificil).getRespuesta1() << endl;
	}

	out << "b) ";
	if((preguntadificil).respuesta2[0] == '#')
	{
		string aux = (preguntadificil).respuesta2;

		aux.erase(0, 1);

		out << aux << endl;
	} else
	{
		out << (preguntadificil).respuesta2 << endl;
	}

	out << "c) ";
	if((preguntadificil).respuesta3[0] == '#')
	{
		string aux = (preguntadificil).respuesta3;

		aux.erase(0, 1);

		out << aux << endl;
	} else
	{
		out << (preguntadificil).respuesta3 << endl;
	}

	out << "d) ";
	if((preguntadificil).respuesta4[0] == '#')
	{
		string aux = (preguntadificil).respuesta3;

		aux.erase(0, 1);

		out << aux << endl;
	} else
	{
		out << (preguntadificil).respuesta3 << endl;
	}

	return out;
}

istream& operator>>(istream& in, prdificil& preguntadificil)
{
	// prdificil* preguntadificil = dynamic_cast <prdificil*>(Pregunta);

	string temporal;
	cout << "Introduce la pregunta a insertar: "<< endl;
	in >> temporal;
	(preguntadificil).setPregunta(temporal);

	cout << "*La respuesta no debe contener la letra de la opcion (a o b) ni signos de puntuacion al inicio (salvo que se trate de un guion, por ser la respuesta un numero negativo)"<< endl;
	cout << "Introduce la respuesta correcta: "<< endl;
	in >> temporal;
	(preguntadificil).setRespuesta1(temporal);

	(preguntadificil).respuesta1 = '#' + (preguntadificil).respuesta1;

	cout << "Introduce otra respuesta (una incorrecta): "<< endl;
	in >> (preguntadificil).respuesta2;

	cout << "Introduce otra respuesta (una incorrecta): "<< endl;
	in >> (preguntadificil).respuesta3;

	cout << "Introduce otra respuesta (una incorrecta): "<< endl;
	in >> (preguntadificil).respuesta4;

	return in;
}