#include "prfacil.h"
#include "preguntas_respuestas.h"
#include <iostream>
#include <string.h>
#include "jugador.h"

using namespace std;

#define DEFAULT_RESPUESTA2 "defaultAnswer2"
#define DEFAULT_DIFICULTAD "#"


//constructores
prfacil::prfacil()
{
  this -> respuesta2 = DEFAULT_RESPUESTA2;
}
		
prfacil::prfacil(string pregunta, string respuesta1, string respuesta2, string dificultad,  bool leerBD): preguntas_respuestas(pregunta, respuesta1, dificultad, leerBD)
{
  this -> respuesta2 = respuesta2;
}

//destructor
 prfacil::~prfacil()
{
}

//constructor copia
prfacil::prfacil(const prfacil &pf): preguntas_respuestas(pf)
{
	this -> respuesta2 = pf.respuesta2;
}

//getter y setter
void prfacil::setRespuesta2(string RDos)
{
	this -> respuesta2 = RDos;
}

string prfacil::getRespuesta2() const
{
	return respuesta2;
}

//métodos

 void prfacil::sumarPunto(jugador jugador)
{
	jugador.setPuntuacion(jugador.getPuntuacion() + 1);
}

 void prfacil::prepararRespuestas()
{
	int i = 1;
	int igual = 0;
	int r;
	int random[2];

	//array de respuestas auxiliares 
	string respuestas[2];

	random[0] = -1;
	random[1] = -1;
	// random[2] = -1;
 	
	// Este while llena el array random con números aleatorios de 0 a 2, pero que no se repitan.
	while(i>=0)
	{
		igual = 0;
		r = rand() % 2;

		for(int j = 0; j<2; j++)
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
		
	this -> respuesta1 = respuestas[0];
	this -> respuesta2 = respuestas[1];
}

bool prfacil::operator=(const prfacil& pf)
{
	this -> respuesta2 = pf.respuesta2;
}

ostream& operator<<(ostream& out, const prfacil& preguntafacil)
{
	// prfacil* preguntafacil = dynamic_cast<prfacil*>(Pregunta);

	out << (preguntafacil).getPregunta() << endl;

	out << "a) ";
	if((preguntafacil).getRespuesta1()[0] == '#')
	{
		string aux = (preguntafacil).getRespuesta1();

		aux.erase(0, 1);

		out << aux << endl;
	} else
	{
		out << (preguntafacil).getRespuesta1() << endl;
	}

	out << "b) ";
	if(((preguntafacil).respuesta2)[0] == '#')
	{
		string aux = (preguntafacil).respuesta2;

		aux.erase(0, 1);

		out << aux << endl;
	} else
	{
		out << (preguntafacil).respuesta2 << endl;
	}

	return out;
}

istream& operator>>(istream& in, prfacil& preguntafacil)
{
	// prfacil* preguntafacil = dynamic_cast<prfacil*>(Pregunta);
	
	string temporal;
	cout << "Introduce la pregunta a insertar: "<< endl;
	in >> temporal;
	(preguntafacil).setPregunta(temporal);

	cout << "*La respuesta no debe contener la letra de la opcion (a o b) ni signos de puntuacion al inicio (salvo que se trate de un guion, por ser la respuesta un numero negativo)"<< endl;
	cout << "Introduce la respuesta correcta: "<< endl;
	in >> temporal;
	(preguntafacil).setRespuesta1(temporal);

	(preguntafacil).respuesta1 = '#' + (preguntafacil).respuesta1;

	cout << "Introduce otra respuesta (una incorrecta): "<< endl;
	in >> (preguntafacil).respuesta2;

	return in;
}