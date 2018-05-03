#include "prdificil.h"

// #include <iostream>
// using namespace std;

#include <stdlib.h>
#include <string.h>



#define DEFAULT_RESPUESTA2 defaultAnswer2
#define DEFAULT_RESPUESTA3 defaultAnswer3
#define DEFAULT_RESPUESTA4 defaultAnswer4
#define DEFAULT_DIFICULTAD ###


//constructores
prdificil:: preguntas_respuestas()
{
  this -> pregunta = DEFAULT_PREGUNTA;
  this -> Respuesta1 = DEFAULT_RESPUESTA;
  this -> Respuesta2 = DEFAULT_RESPUESTA2;
  this -> Respuesta3 = DEFAULT_RESPUESTA3;
  this -> Respuesta4 = DEFAULT_RESPUESTA4;
  this -> dificultad = DEFAULT_DIFICULTAD;
}
		
prdificil:: preguntas_respuestas(string pregunta, string Respuesta1, string Respuesta2, string Respuesta3, string Respuesta4 string dificultad)
{
  this -> pregunta = pregunta;
  this -> Respuesta1 = Respuesta1;
  this -> Respuesta2 = Respuesta2;
  this -> Respuesta3 = Respuesta3;
  this -> dificultad = dificultad;
}

//destructor
~prdificil::preguntas_respuestas()
{
  // delete pregunta;
  // delete Respuesta1;
  // delete Respuesta2;
  // delete Respuesta3;
  delete Respuesta4;
  // delete dificultad;
   preguntas_respuestas::~prdificil();
}

//getter y setter
void prdificil::void setRespuesta4(string RCuatro)
{
	this -> RCuatro = Respuesta4;
}

//constructor copia
prdificil(const prdificil &pd)
{
	this -> Respuesta4 = new string;
	//para los atributos que están en la madre
	preguntas_respuestas :: prdificil();
}

void prdificil::void getRespuesta4() const
{
	return Respuesta4;
}

//metodos 

virtual void sumarPunto(jugador jugador)
{
	jugador.puntuacion =+ 3;
}

virtual void prepararRespuestas(pregunta_respuestas pregunta, string dificil)
{
	char respuestas[4][252];
	int i = 3;
	int igual = 0;
	int r;
	int random[4];

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

	strcpy(respuestas[random[0]], (*pregunta).Respuesta1);
	strcpy(respuestas[random[1]], (*pregunta).Respuesta2);
	strcpy(respuestas[random[2]], (*pregunta).Respuesta3);
	strcpy(respuestas[random[3]], (*pregunta).Respuesta4);


	strcpy((*pregunta).Respuesta1, respuestas[0]);
	strcpy((*pregunta).Respuesta2, respuestas[1]);
	strcpy((*pregunta).Respuesta3, respuestas[2]);
	strcpy((*pregunta).Respuesta4, respuestas[3]);

}