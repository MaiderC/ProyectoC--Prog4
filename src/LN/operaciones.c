#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../INCLUDES/operaciones.h"

t_pregunta_respuestas generarPregunta (t_pregunta_respuestas *arrPreg, t_pregunta_respuestas* *preguntasSalidas, int* sizePreguntasSalidas, int sizeTotalPreguntas)
{
	int random = 0;
	t_pregunta_respuestas pregunta;
	int repetida = 0;
	int cont = 0;
	int MAX_INTENTOS = 20;
	t_pregunta_respuestas *aux;

	if(*sizePreguntasSalidas == 0)
	{
		repetida = 0;
		random = rand() %(sizeTotalPreguntas); //genera un número aleatorio entre 0 y sizeTotalPreguntas-1
		pregunta = arrPreg[random];
		t_pregunta_respuestas aux [1];
		aux[0] = pregunta;
		free(*preguntasSalidas);
		*preguntasSalidas = NULL;
		*preguntasSalidas = (t_pregunta_respuestas*) malloc (sizeof(t_pregunta_respuestas));
		(*preguntasSalidas)[0] = pregunta;
	}
	else
	{
		
		 	do
		 	{
			 		repetida = 0;
			 		random = rand() %(sizeTotalPreguntas); //genera un número aleatorio entre 0 y sizeTotalPreguntas-1
			 		pregunta = arrPreg[random];
			 		
				 		for(int j = 0; j < *sizePreguntasSalidas; j++)
				 		{
				 			
				 			//si son iguales, será 0
				 			if(strcmp (pregunta.Pregunta, (*preguntasSalidas)[j].Pregunta) == 0)
				 			{
				 				repetida = 1; //si son iguales, será 1
				 			}
				 		}
				 	
			 	cont++;
		 	}
		 	while(repetida == 1 && cont < MAX_INTENTOS); //Hará esto hasta que encuentre una pregunta no repetida o agote la cantidad de intentos

		 
		 aux = (t_pregunta_respuestas*) malloc ((*sizePreguntasSalidas+1) * sizeof(t_pregunta_respuestas));
		 //creamos espacio para las preguntas ya salidas +1 (la nueva)
		
		//metemos todas las preguntas del array de los ya salidos en la variable auxiliar
		 for (int i=0; i<(*sizePreguntasSalidas); i++)
		 {
		 	strcpy(aux[i].Pregunta,(*preguntasSalidas)[i].Pregunta);
		 	
		 }
		 aux[*sizePreguntasSalidas] = pregunta;//Añadimos la pregunta en la variable auxiliar
		
		 free (*preguntasSalidas);
		 *preguntasSalidas = NULL;
		 //Hacemos malloc de preguntasSalidas otra vez para darles espacio para un hueco más
		  *preguntasSalidas = (t_pregunta_respuestas*) malloc ((*sizePreguntasSalidas+1) * sizeof(t_pregunta_respuestas));
		
		 for (int i = 0; i<(*sizePreguntasSalidas+1); i++)
		 {
		 	(*preguntasSalidas )[i] = aux[i]; 
		 }
	}
	
	 //nos libramos de aux porque ya no nos hace falta
	 free(aux);
	 aux = NULL;
	 prepararRespuestas(&pregunta);
	 
	 *sizePreguntasSalidas +=1;
	 return pregunta;
}

//Verificar si la respuesta elegida es la correcta
//(ver si la respuesta a la que se le ha asignado el valor de la letra que se ha elegido empieza por punto)
int comprobarRespuesta(char* respuesta) 
{
	int correcto;

	//si correcto es 1, ha contestado bien

	if (respuesta[0] =='#')
	{
		correcto =1;
	}
	else
	{
		correcto =0;
	}

	return correcto;
}

//leer todas las preguntas ver cuántas hay del fichero
//lo que hay del fichero pasar a array
//comparar lo del parám con la cantidad de preguntas
//para que no me pida más preguntas de las que hay
//CUANDO ES MULTIJGADOR LO MANDAMOS a cantpreguntas la cantpreguntas * el numdejugadores
int maxPreguntas (int cantPreguntas, int sizeTotalPreguntas) 
{	
	int valido;	//si es 1 es válido, si es 0 no lo es.
	int size;

	size = sizeTotalPreguntas;

	if(size < cantPreguntas)
	{
		valido =0;
	}
	else
	{
		valido =1;
	}

	return valido;
}

 void ordenarJugadores(t_jugador* jugadoresLeidos, int size)
 {
 	t_jugador temp; //variable auxiliar

 	// recorrer todos los elementos del array
   for(int i = 0; i < size-1; i++) 
   { 
      //comparar cada elemento con todos los demás
      for(int j = 0; j < size-1-i; j++)
      {
        if(jugadoresLeidos[j].puntuacion < jugadoresLeidos[j+1].puntuacion)
         {
            temp = jugadoresLeidos[j];
            jugadoresLeidos[j] = jugadoresLeidos[j+1];
            jugadoresLeidos[j+1] = temp;	
         }		
      }
 	}
}

int maxPuntuacion(t_jugador* jugadores, int sizeJugadores)
{
	int max =jugadores[0].puntuacion;

	for(int i=0; i < sizeJugadores; i++)
	{
		if(max < jugadores[i].puntuacion)
		{
			max = jugadores[i].puntuacion;
		}
	}
	return max;
}