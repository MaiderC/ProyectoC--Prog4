#include "../INCLUDES/data.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void guardarJugadores(t_jugador* listaJugadores, int numElem)
{
  FILE* fichero = fopen("./Data/jugador.dat", "wb"); 

  fputc(numElem, fichero);

  fwrite(listaJugadores, sizeof(t_jugador), numElem, fichero);

  fclose(fichero);
}

int numJugadoresTotal()
{
  int numElem;

  FILE* fichero = fopen("./Data/jugador.dat", "rb");

  if(fichero != NULL)
  {
    numElem = fgetc(fichero);

    fclose(fichero);
  }
  else
  {
    numElem = 0;
  }
  return numElem;
}

t_jugador* leerJugadores()
{
  t_jugador* listaJugadores = NULL;
  int numElem = 0;
  
  FILE* fichero = fopen("./Data/jugador.dat", "rb");

  if(fichero != NULL)
  {
    numElem = fgetc(fichero);

    listaJugadores = (t_jugador*) malloc(numElem * sizeof(t_jugador));

    fread(listaJugadores, sizeof(t_jugador), numElem, fichero);

      fclose(fichero);
  }
  
  return listaJugadores;
}

void guardarPreguntaRespuestas(t_pregunta_respuestas* PreguntasParaGuardar, int numNuevas)
{
  t_pregunta_respuestas* TodasPreguntas;
  int numPreguntas;

  numPreguntas = numNuevas + numPreguntasEnFichero();

  TodasPreguntas = leerPreguntasRespuestas();

  TodasPreguntas = (t_pregunta_respuestas*) realloc(TodasPreguntas, numPreguntas * sizeof(t_pregunta_respuestas));

  for(int i = 0; i < numNuevas; i++)
  {
    TodasPreguntas[numPreguntas - numNuevas + i] = PreguntasParaGuardar[i];
  }

  FILE* fichero = fopen("./Data/PreguntaRespuestas.dat", "wb");  

  fputc(numPreguntas, fichero);

  fwrite(TodasPreguntas, sizeof(t_pregunta_respuestas), numPreguntas, fichero);

  fclose(fichero);
}

int numPreguntasEnFichero()
{
  int numElem;

  FILE* fichero = fopen("./Data/PreguntaRespuestas.dat", "rb");

  if(fichero != NULL)
  {
    numElem = fgetc(fichero);
  } else
  {
    numElem = 0;
  }

  fclose(fichero);

  return numElem;
}

t_pregunta_respuestas* leerPreguntasRespuestas()
{
  t_pregunta_respuestas* PreguntasLeidas;
	int numElem = 0;
	
  FILE* fichero = fopen("./Data/PreguntaRespuestas.dat", "rb");

  PreguntasLeidas = (t_pregunta_respuestas*) malloc(sizeof(t_pregunta_respuestas));

  if(fichero != NULL)
  {
    numElem = fgetc(fichero);

    PreguntasLeidas = (t_pregunta_respuestas*) realloc(PreguntasLeidas, numElem * sizeof(t_pregunta_respuestas));

    fread(PreguntasLeidas, sizeof(t_pregunta_respuestas), numElem, fichero);
  }

  fclose(fichero);
  
  return PreguntasLeidas;
}