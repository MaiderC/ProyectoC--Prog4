#include "prfacil.h"

#include <iostream>
using namespace std;

#include <stdlib.h>
#include <string.h>

#define DEFAULT_RESPUESTA2 defaultAnswer2
#define DEFAULT_DIFICULTAD #


//constructores
prfacil:: preguntas_respuestas()
{
  this -> Respuesta2 = DEFAULT_RESPUESTA2;
}
		
prfacil:: preguntas_respuestas(string pregunta, string Respuesta1, string Respuesta2, string dificultad)
{
  this -> Respuesta2 = Respuesta2;
}

//destructor
prfacil::~preguntas_respuestas()
{
  // delete pregunta;
  // delete Respuesta1;
  delete Respuesta2;
  // delete dificultad;
  preguntas_respuestas::~prfacil();
}

//constructor copia
prfacil::prfacil(const prfacil &pf)
{
	this -> Respuesta2 = pf.Respuesta2;
	//para los atributos que están en la madre
	preguntas_respuestas :: preguntas_respuestas(pf);
}

//getter y setter
void prfacil::setRespuesta2(string RDos)
{
	this -> RDos = Respuesta2;
}

string prfacil::getRespuesta2() const
{
	return Respuesta2;
}

//métodos

virtual void sumarPunto(jugador jugador)
{
	jugador.puntuacion =+ 1;
}

virtual void prepararRespuestas(preguntas_respuestas pregunta, string facil)
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

	respuestas[random[0]] = this -> Respuesta1;
	respuestas[random[1]] = this->Respuesta2;
		
	this->Respuesta1 = respuestas[0];
	this->Respuesta2 = respuestas[1];
}