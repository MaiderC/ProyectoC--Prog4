#include "prfacil.h"
#include "preguntas_respuestas.h"
#include <iostream>
#include <string.h>
#include "jugador.h"

using namespace std;

#define DEFAULT_RESPUESTA2 "defaultAnswer2"
#define DEFAULT_DIFICULTAD "#"

prfacil::prfacil()
{
  this -> respuesta2 = DEFAULT_RESPUESTA2;
}
		
prfacil::prfacil(string pregunta, string respuesta1, string respuesta2, int ID, bool leerBD): preguntas_respuestas(pregunta, respuesta1, ID, leerBD)
{
  this -> respuesta2 = respuesta2;
  this -> dificultad = "#";
}

prfacil::~prfacil()
{

}

prfacil::prfacil(const prfacil &pf): preguntas_respuestas(pf)
{
	this -> respuesta2 = pf.respuesta2;
}

void prfacil::setRespuesta2(string RDos)
{
	this -> respuesta2 = RDos;
}

string prfacil::getRespuesta2() const
{
	return respuesta2;
}

void prfacil::sumarPunto(jugador& jugador)
{
	jugador.setPuntuacion(jugador.getPuntuacion() + 1);
}

void prfacil::prepararRespuestas()
{
	int i = 1;
	int igual = 0;
	int r;
	int random[2];

	string respuestas[2];

	random[0] = -1;
	random[1] = -1;
 	
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

prfacil& prfacil::operator=(const prfacil& pf)
{
	this -> id = pf.id;
	this -> dificultad = pf.dificultad;
	this -> pregunta = pf.pregunta;
	this -> respuesta1 = pf.respuesta1;
	this -> respuesta2 = pf.respuesta2;

	return *this;
}

ostream& operator<<(ostream& out, const prfacil& preguntafacil)
{
	out << (preguntafacil).getPregunta() << endl;
	out << "a) ";
	
	if((preguntafacil).getRespuesta1()[0] == '#')
	{
		string aux = (preguntafacil).getRespuesta1();

		aux.erase(0, 1);

		out << aux << endl;
	} 
	else
	{
		out << (preguntafacil).getRespuesta1() << endl;
	}

	out << "b) ";
	if(((preguntafacil).respuesta2)[0] == '#')
	{
		string aux = (preguntafacil).respuesta2;

		aux.erase(0, 1);

		out << aux << endl;
	} 
	else
	{
		out << (preguntafacil).respuesta2 << endl;
	}

	return out;
}

istream& operator>>(istream& in, prfacil& preguntafacil)
{
	string pregunta;
	string r1;
	string r2;

	cout << "Introduce la pregunta a insertar: "<< endl;
	getline(in, pregunta);

	while(pregunta.length() == 0)
	{
		cout << "No has introducido nada. Introduce la pregunta a insertar: "<< endl;
		getline(in, pregunta);
	}

	preguntafacil.setPregunta(pregunta);

	cout << "*La respuesta no debe contener la letra de la opcion (a o b) ni signos de puntuacion al inicio (salvo que se trate de un guion, por ser la respuesta un numero negativo)"<< endl;
	cout << "Introduce la respuesta correcta: "<< endl;
	getline(in, r1);

	while(r1.length() == 0)
	{
		cout << " No has introducido nada. Introduce la respuesta a insertar: "<< endl;
		getline(in, r1);
	}

	r1 = '#' + r1;
	preguntafacil.setRespuesta1(r1);

	cout << "Introduce otra respuesta (una incorrecta): "<< endl;
	getline(in, r2);

	while(r2.length() == 0)
	{
		cout << " No has introducido nada. Introduce la respuesta a insertar: "<< endl;
		getline(in, r2);
	}

	preguntafacil.setRespuesta2(r2);
	
	preguntafacil.setID((preguntafacil.getID()+1));
	preguntafacil.setCont(preguntafacil.getID());

	preguntafacil.setDificultad("#");

	return in;
}