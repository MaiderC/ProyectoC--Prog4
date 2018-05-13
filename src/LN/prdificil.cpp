#include "prdificil.h"

// #include <iostream>
// using namespace std;

#define DEFAULT_RESPUESTA2 defaultAnswer2
#define DEFAULT_RESPUESTA3 defaultAnswer3
#define DEFAULT_RESPUESTA4 defaultAnswer4
#define DEFAULT_DIFICULTAD ###

//constructores
prdificil:: preguntas_respuestas()
{
  this -> respuesta2 = DEFAULT_RESPUESTA2;
  this -> respuesta3 = DEFAULT_RESPUESTA3;
  this -> respuesta4 = DEFAULT_RESPUESTA4;
}
		
prdificil:: preguntas_respuestas(string pregunta, string respuesta1, string respuesta2, string respuesta3, string respuesta4, string dificultad): preguntas_respuestas(pregunta, respuesta1, dificultad)
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
void prdificil::void setRespuesta4(string RCuatro)
{
	this -> respuesta4 = RCuatro;
}

string prdificil::void getRespuesta4() const
{
	return respuesta4;
}

//metodos 

 void sumarPunto(jugador jugador)
{
	jugador.puntuacion =+ 3;
}

 void prepararRespuestas(pregunta_respuestas pregunta, string dificil)
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
	respuestas[random[1]] = this->respuesta2;
	respuestas[random[2]] = this -> respuesta3;
	respuestas[random[3]] = this->respuesta4;
		
	this->respuesta1 = respuestas[0];
	this->respuesta2 = respuestas[1];
	this->respuesta3 = respuestas[2];
	this->respuesta4 = respuestas[3];
}

//sobrecarga de operador =
bool operator=(const prdificil& pd)
{
	this -> respuesta2 = pd.respuesta2;
	this -> respuesta3 = pd.respuesta3;
	this -> respuesta4 = pd.respuesta4;
}