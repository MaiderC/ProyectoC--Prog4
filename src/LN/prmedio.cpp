#include "prmedio.h"

// using namespace std;


#define DEFAULT_RESPUESTA2 defaultAnswer2
#define DEFAULT_RESPUESTA3 defaultAnswer3
#define DEFAULT_DIFICULTAD ##


//constructores
prmedio:: preguntas_respuestas()
{
  this -> respuesta2 = DEFAULT_RESPUESTA2;
  this -> respuesta3 = DEFAULT_RESPUESTA3;
}
		
prmedio:: preguntas_respuestas(string pregunta, string respuesta1, string respuesta2, string respuesta3, string dificultad)
{
  this -> respuesta2 = respuesta2;
  this -> respuesta3 = respuesta3;
}

//destructor
 prmedio::~preguntas_respuestas()
{
  // delete pregunta;
  // delete Respuesta1;
  delete respuesta2;
  delete respuesta3;
  // delete dificultad;
  // preguntas_respuestas::~prmedio();
}

//constructor copia
prmedio::prmedio(const prmedio &pm): preguntas_respuestas(pm)
{
	this -> respuesta2 = pm.respuesta2;
	this -> respuesta3 = pm.respuesta3;
	//para los atributos que están en la madre
	// preguntas_respuestas :: prmedio();
}

//getter y setter
void prmedio::void setRespuesta3(string RTres)
{
	this -> respuesta3 = RTres;
}

string prmedio::void getRespuesta3() const
{
	return respuesta3;
}

//metodos

 void sumarPunto(jugador jugador)
{
	jugador.puntuacion =+ 2;
}

 void prepararRespuestas(pregunta_respuestas pregunta, string medio)
{
	int i = 2;
	int igual = 0;
	int r;
	int random[3];
	//array de respuestas auxiliares 
	string respuestas[3];

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

	respuestas[random[0]] = this -> respuesta1;
	respuestas[random[1]] = this->respuesta2;
	respuestas[random[2]] = this->respuesta3;
	
	this->respuesta1 = respuestas[0];
	this->respuesta2 = respuestas[1];
	this->respuesta3 = respuestas[2];

	
}

bool operator=(const prmedio& pm)
{
	this -> respuesta2 = pm.respuesta2;
	this -> respuesta3 = pm.respuesta3;
}
