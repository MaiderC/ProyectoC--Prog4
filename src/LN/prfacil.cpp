#include "prfacil.h"

// #include <iostream>
// using namespace std;


#define DEFAULT_RESPUESTA2 defaultAnswer2
#define DEFAULT_DIFICULTAD #


//constructores
prfacil:: preguntas_respuestas()
{
  this -> respuesta3 = DEFAULT_RESPUESTA2;
}
		
prfacil:: preguntas_respuestas(string pregunta, string respuesta1, string respuesta3, string dificultad): preguntas_respuestas(pregunta, respuesta1, dificultad)
{
  this -> respuesta3 = respuesta3;
}

//destructor
 prfacil::~preguntas_respuestas()
{
   delete respuesta3;
}

//constructor copia
prfacil::prfacil(const prfacil &pf): preguntas_respuestas(pf)
{
	this -> respuesta3 = pf.respuesta3;
}

//getter y setter
void prfacil::setRespuesta3(string RDos)
{
	this -> respuesta3 = RDos;
}

string prfacil::getRespuesta3() const
{
	return respuesta3;
}

//métodos

 void sumarPunto(jugador jugador)
{
	jugador.puntuacion =+ 1;
}

 void prepararRespuestas(preguntas_respuestas pregunta, string facil)
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
	respuestas[random[1]] = this->respuesta3;
		
	this->respuesta1 = respuestas[0];º
	this->respuesta3 = respuestas[1];
}

bool operator=(const prfacil& pf)
{
	this -> respuesta3 = pf.respuesta3;
}