#include "operaciones.h"
#include "preguntas_respuestas.h"
#include "prfacil.h"
#include "prmedio.h"
#include "prdificil.h"
#include "jugador.h"
#include <vector>
#include <iostream>
#include <string.h>
#include "../LD/DBConnector.h"

using namespace std;

namespace operaciones
{

	void siguienteID(const vector<preguntas_respuestas*>& listaTodasRespuestas)
	{
		int cont = 0;
		preguntas_respuestas* p_r;

		for (int i = 0; i < listaTodasRespuestas.size(); i++)
		{
			if(cont < listaTodasRespuestas[i]->getID())
			{
				cont = listaTodasRespuestas[i]->getID();
			}
		}

		p_r->setCont(cont);
	}

	preguntas_respuestas* generarPregunta(const vector<preguntas_respuestas*>& listaTodasPreguntas, vector<preguntas_respuestas*>& preguntasSalidas)
	{
		int random = 0;
		preguntas_respuestas* pregunta;
		int repetida = 0;
		int cont = 0;
		int MAX_INTENTOS = 20;

		if(preguntasSalidas.size() == 0)
		{
			repetida = 0;

			random = rand() % listaTodasPreguntas.size(); //genera un número aleatorio entre 0 y sizeTotalPreguntas-1
			pregunta = listaTodasPreguntas[random];

			preguntasSalidas.push_back(pregunta);
		}
		else
		{
			 	do
			 	{
				 		repetida = 0;
				 		random = rand() % listaTodasPreguntas.size(); //Genera un número aleatorio entre 0 y sizeTotalPreguntas-1

				 		pregunta = listaTodasPreguntas[random];
				 		
					 		for(int j = 0; j < preguntasSalidas.size(); j++)
					 		{
					 			//si son iguales, será 0
					 			if(pregunta->getID() == preguntasSalidas[j]->getID())
					 			{
					 				repetida = 1; //si son iguales, será 1
					 			}
					 		}
				 	cont++;
			 	}
			 	while(repetida == 1 && cont < MAX_INTENTOS); //Hará esto hasta que encuentre una pregunta no repetida o agote la cantidad de intentos
			
			 	preguntasSalidas.push_back(pregunta);
		}

		 pregunta->prepararRespuestas();

		 return pregunta;
	}

	//Verificar si la respuesta elegida es la correcta
	//(ver si la respuesta a la que se le ha asignado el valor de la letra que se ha elegido empieza por punto)
	int comprobarRespuesta(const string& respuesta)
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

	int maxPreguntas(const int& cantPreguntas, const int& sizeTotalPreguntas)
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

	 void ordenarJugadores(vector<jugador>& jugadoresLeidos)
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

	int maxPuntuacion(const vector<jugador>& jugadores)
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

	vector<jugador> actualizarPuntuacion(vector<jugador>& listaTodosJugadores, vector<jugador>& listaJugadoresSesion)
	{
	    int coincidencias = 0;
	   
	    if(listaTodosJugadores.size() == 0)
	    {
	        return listaJugadoresSesion;
	    }
	    else
	    {
	      for(int i = 0; i < listaTodosJugadores.size(); i++)
	      {
	        for(int j = 0; j < listaJugadoresSesion.size(); j++)
	        {
	          if(listaTodosJugadores[i].getNick() == listaJugadoresSesion[j].getNick())
	          {
	            listaTodosJugadores[i].setPuntuacion(listaJugadoresSesion[j].getPuntuacion() + listaTodosJugadores[i].getPuntuacion());
	            listaJugadoresSesion.erase(listaJugadoresSesion.begin()+j, listaJugadoresSesion.begin()+j);
	          }
	        }
	      }
	    }

	    for(int i = 0; i < listaJugadoresSesion.size(); i++)
	    {
	      	listaTodosJugadores.push_back(listaJugadoresSesion[i]);
	      	listaJugadoresSesion.erase(listaJugadoresSesion.begin()+i, listaJugadoresSesion.begin()+i);
	    }

	    return listaTodosJugadores;
	}

	vector<jugador> actualizarPuntuacion(vector<jugador>& listaTodosJugadores, jugador jugadorPrincipal)
	{
	  for(int i = 0; i < listaTodosJugadores.size(); i++)
	  {
	    if(jugadorPrincipal.getNick() == listaTodosJugadores[i].getNick())
	    {
	     listaTodosJugadores[i].setPuntuacion(listaTodosJugadores[i].getPuntuacion() + jugadorPrincipal.getPuntuacion());
	    }
	    else
	    {
	      listaTodosJugadores.push_back(jugadorPrincipal);
	    }
	  }

	  return listaTodosJugadores;
	}

	void guardarJugadores(const vector<jugador>& ListaTodosJugadores, DBConnector BD)
	{
		int result;
		for (int i = 0; i < ListaTodosJugadores.size(); ++i)
		{
			result = BD.update_Jugador(ListaTodosJugadores[i]);
			if (result == 0)
			{
				//No ha podido hacer update porque no existe el jugador; hacemos insert:
				result = BD.insert_Jugador(ListaTodosJugadores[i]);
			}
		}
	}
}