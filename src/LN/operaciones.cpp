#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <operaciones.h>
#include <jugador.h>
#include <prfacil.h>
#include <prmedio.h>
#include <prdificil.h>

preguntas_respuestas operaciones::generarPregunta(const vector<preguntas_respuestas>& listaTodasPreguntas, vector<preguntas_respuestas>& preguntasSalidas)
{
	int random = 0;
	preguntas_respuestas pregunta;
	int repetida = 0;
	int cont = 0;
	int MAX_INTENTOS = 20;

	if(preguntasSalidas.size() == 0)
	{
		repetida = 0;

		random = rand() % sizeTotalPreguntas; //genera un número aleatorio entre 0 y sizeTotalPreguntas-1
		pregunta(listaTodasPreguntas[random]);

		preguntasSalidas.push_back(pregunta);
	}
	else
	{
		 	do
		 	{
			 		repetida = 0;
			 		random = rand() % sizeTotalPreguntas; //Genera un número aleatorio entre 0 y sizeTotalPreguntas-1

			 		pregunta(listaTodasPreguntas[random]);
			 		
				 		for(int j = 0; j < preguntasSalidas.size(); j++)
				 		{
				 			//si son iguales, será 0
				 			if(pregunta.getPregunta() == preguntasSalidas[j].getPregunta())
				 			{
				 				repetida = 1; //si son iguales, será 1
				 			}
				 		}
			 	cont++;
		 	}
		 	while(repetida == 1 && cont < MAX_INTENTOS); //Hará esto hasta que encuentre una pregunta no repetida o agote la cantidad de intentos
		
		 	preguntasSalidas.push_back(pregunta);
	}

	 pregunta.prepararRespuestas();

	 return pregunta;
}

//Verificar si la respuesta elegida es la correcta
//(ver si la respuesta a la que se le ha asignado el valor de la letra que se ha elegido empieza por punto)
int operaciones::comprobarRespuesta(const string& respuesta)
{
	int correcto;

	//si correcto es 1, ha contestado bien

	if ((respuesta.c_str())[0] == '#')
	{
		correcto = 1;
	}
	else
	{
		correcto = 0;
	}

	return correcto;
}

int operaciones::maxPreguntas(const int& cantPreguntas, const int& sizeTotalPreguntas)
{	
	int valido;	//si es 1 es válido, si es 0 no lo es.

	if(sizeTotalPreguntas < cantPreguntas)
	{
		valido = 0;
	}
	else
	{
		valido = 1;
	}

	return valido;
}

 void operaciones::ordenarJugadores(vector<jugador>& jugadoresLeidos)
 {
 	jugador temp; //variable auxiliar

 	// recorrer todos los elementos del array
   for(int i = 0; i < jugadoresLeidos.size(); i++) 
   { 
      //comparar cada elemento con todos los demás
      for(int j = 0; j < jugadoresLeidos.size()-i; j++)
      {
        if(jugadoresLeidos[j] < jugadoresLeidos[j+1])
         {
            temp = jugadoresLeidos[j];
            jugadoresLeidos[j] = jugadoresLeidos[j+1];
            jugadoresLeidos[j+1] = temp;
         }
      }
 	}
}

int operaciones::maxPuntuacion(const vector<jugador>& jugadores)
{
	int max = jugadores[0].getPuntuacion();

	for(int i = 0; i < jugadores.size(); i++)
	{
		if(max < jugadores[i].getPuntuacion())
		{
			max = jugadores[i].getPuntuacion();
		}
	}
	
	return max;
}