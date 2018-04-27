#ifndef PREGUNTAS_RESPUESTAS_H
#define PREGUNTAS_RESPUESTAS_H

typedef struct
{
	char Pregunta[250 + 1];
	char Respuesta1[1 + 250 + 1];
	char Respuesta2[250 + 1];
	char Respuesta3[250 + 1];

} t_pregunta_respuestas;

void prepararRespuestas(t_pregunta_respuestas* pregunta);

#endif