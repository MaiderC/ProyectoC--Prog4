#include "preguntas_respuestas.h"
#include <iostream>
#include <string.h>
#include "jugador.h"

using namespace std;

#define DEFAULT_PREGUNTA "defaultQuestion"
#define DEFAULT_RESPUESTA "defaultAnswer1"
#define DEFAULT_DIFICULTAD "#"

//esto es para q haga una vez el inicio del contador
int preguntas_respuestas::cont = 0;

//constructores
preguntas_respuestas:: preguntas_respuestas()
{
  this -> pregunta = DEFAULT_PREGUNTA;
  this -> respuesta1 = DEFAULT_RESPUESTA;
  this -> dificultad = DEFAULT_DIFICULTAD;
  this -> id = cont;
}
		
preguntas_respuestas:: preguntas_respuestas(string pregunta, string respuesta1, int ID, bool leerBD)
{
  this -> pregunta = pregunta;
  this -> respuesta1 = respuesta1;

  if(leerBD)
  {
    this->id = ID;
  }
  else
  {
     this -> id = cont;
     this -> cont ++;
  }
}

//destructor
 preguntas_respuestas::~preguntas_respuestas()
{
}
//constructor copia
preguntas_respuestas::preguntas_respuestas(const preguntas_respuestas &p_r)
{
  this -> id = p_r.id;
  this -> dificultad = p_r.dificultad;
  this -> pregunta = p_r.pregunta;
  this -> respuesta1 = p_r.respuesta1;
}

//getters y setters
void preguntas_respuestas:: setPregunta(string pregunta)
{
  this -> pregunta = pregunta;
}
void preguntas_respuestas:: setRespuesta1(string RUno)
{
  this -> respuesta1 = RUno;
}
void preguntas_respuestas:: setDificultad(string dificultad)
{
  this -> dificultad = dificultad;
}

void preguntas_respuestas:: setCont (int cont)
{
  this -> cont = cont;
}

void preguntas_respuestas:: setID(int ID)
{
  this -> id = ID;
}

string preguntas_respuestas:: getPregunta() const
{
  return pregunta;
}
string preguntas_respuestas:: getRespuesta1() const
{
  return respuesta1;
}
string preguntas_respuestas:: getDificultad() const
{
  return dificultad;
}
int preguntas_respuestas:: getCont () const
{
  return cont;
}

int preguntas_respuestas:: getID () const
{
  return id;
}

//sobrecarga de operador =
preguntas_respuestas& preguntas_respuestas::operator=(const preguntas_respuestas& p_r)
{
  this -> id = p_r.id;
  this -> dificultad = p_r.dificultad;
  this -> pregunta = p_r.pregunta;
  this -> respuesta1 = p_r.respuesta1;
}

void preguntas_respuestas::sumarPunto(jugador jugador)
{
}

void preguntas_respuestas::prepararRespuestas()
{
}