#include "../INCLUDES/preguntas_respuestas.h"
#include <stdlib.h>
#include <string.h>

#define DEFAULT_PREGUNTA defaultQuestion
#define DEFAULT_RESPUESTA defaultAnswer1
#define DEFAULT_DIFICULTAD #

//constructores
preguntas_respuestas:: preguntas_respuestas()
{
  this -> pregunta = DEFAULT_PREGUNTA;
  this -> Respuesta1 = DEFAULT_RESPUESTA;
  this -> dificultad = DEFAULT_DIFICULTAD;
}
		
preguntas_respuestas:: preguntas_respuestas(string pregunta, string Respuesta1,string dificultad)
{
  this -> pregunta = pregunta;
  this -> Respuesta1 = Respuesta1;
  this -> dificultad = dificultad;
}

//destructor
virtual preguntas_respuestas::~preguntas_respuestas()
{
  delete pregunta;
  delete Respuesta1;
  delete dificultad;
}

//constructor copia
preguntas_respuestas::preguntas_respuestas(const preguntas_respuestas &p_r)
{
  this -> pregunta = p_r.pregunta;
  this -> Respuesta1 = p_r.Respuesta1;
  this -> dificultad = p_r.dificultad;
}

//getters y setters
void preguntas_respuestas:: setPregunta(string pregunta)
{
  this -> pregunta = pregunta;
}
void preguntas_respuestas:: setRespuesta1(string RUno)
{
  this -> Respuesta1 = RUno;
}
void preguntas_respuestas:: setDificultad(string dificultad)
{
  this -> dificultad = dificultad;
}

string preguntas_respuestas:: getPregunta() const
{
  return pregunta;
}
string preguntas_respuestas:: getRespuesta1() const
{
  return Respuesta1;
}
string preguntas_respuestas:: getDificultad() const
{
  return dificultad;
}

//metodos de clase madre sin implementación (métodos virtuales puros), pero sí la tendrán sus hijas
//es para hacer abstracta la clase madre
virtual void sumarPunto(jugador jugador) = 0;
virtual void prepararRespuestas() = 0;
