#include "utilidades.h"
#include "../LN/jugador.h"
#include <iostream>
#include <vector>
#include "../LN/preguntas_respuestas.h"
#include "../LN/prfacil.h"
#include "../LN/prmedio.h"
#include "../LN/prdificil.h"
#include <string.h>

using namespace std;

namespace utilidades
{
	void mostrarMensaje(const string& str)
	{
		cout << str << endl;
	}

	void mostrarInt(const int& i)
	{
		cout << i << endl;
	}

	void mostrarPregunta(const prfacil& Pregunta)
	{
		cout << Pregunta;
	}

	void mostrarPregunta(const prmedio& Pregunta)
	{
		cout << Pregunta;
	}

	void mostrarPregunta(const prdificil& Pregunta)
	{
		cout << Pregunta;
	}

	void mostrarTodasPreguntas(const vector<preguntas_respuestas> TodasPreguntas)
	{
		preguntas_respuestas* p;

		p = new preguntas_respuestas[TodasPreguntas.size()];

		for(int k = 0; k < TodasPreguntas.size(); k++)
		{
			p[k] = TodasPreguntas[k]; 
		}

		for(int i = 0; i < TodasPreguntas.size(); i++)
		{
			cout << (i+1) << ".-";

			if (p[i].getDificultad() == "#")
			{
				prfacil* preguntaAux = dynamic_cast<prfacil*> (p);
				mostrarPregunta(*preguntaAux);
			}
			else if (p[i].getDificultad() == "##")
			{
				prmedio* preguntaAux = dynamic_cast<prmedio*> (p);
				mostrarPregunta(*preguntaAux);
			}
			else if(p[i].getDificultad() == "###")
			{
				prdificil* preguntaAux = dynamic_cast<prdificil*> (p);
				mostrarPregunta(*preguntaAux);
			}
			cout << endl << endl;
		}
	}

	void mostrarPuntuacion(const jugador& jugador)
	{
		cout << jugador.getNick() << ": " << jugador.getPuntuacion() << " puntos" << endl;
	}

	void mensajeGanador(const jugador& ganador) //A este metodo se le llamara antes de actualizar las puntuaciones, con lo que la puntuación sera la acumulada en esa partida
	{
		cout << "El jugador ganador de esta partida ha sido " << ganador.getNick() << " con " << ganador.getPuntuacion() << " puntos. ¡Enhorabuena!" << endl;
	}

	int mensajeEmpate(const vector<jugador>& empatados) //Recibe una lista con los jugadores que han empatado
	{
		int opcion;

		cout << "Se ha producido un empate entre " << empatados.size() << " jugadores con " << empatados[0].getPuntuacion() << " puntos" << endl;

		for(int i = 0; i < empatados.size(); i++)
		{
			cout << empatados[i].getNick() << endl;
		}

		do
		{
			cout << "Si deseas desempatar pulsa 1" << endl;
			cout << "Si deseas finalizar la partida con empate, pulsa 2" << endl;
			recogerInt(opcion);
		}
		while(opcion < 1 || opcion > 2);
	}

	//-----------------------------------------------------------------
	void recogerString(string& string_recoger)
	{
		cin >> string_recoger;
	}

	void recogerInt(int& numero_recoger)
	{
		cin >> numero_recoger;
	}

	int recogerOpcionRespuesta(char& respuesta_recoger, string dificultad) 
	{
		int Dificultad = dificultad.size();
		int error = 0;
		
		cin >> respuesta_recoger;

		switch(Dificultad)
		{
			case 1:
				if(respuesta_recoger != 'a' && respuesta_recoger != 'b') 
				{
					cout << "La respuesta no es valida. Por favor, introduce una opción valida (a o b)" << endl;

					error = -1;
				}
				break;

			case 2:
				if(respuesta_recoger != 'a' && respuesta_recoger != 'b' && respuesta_recoger != 'c') 
				{
					cout << "La respuesta no es valida. Por favor, introduce una opción valida (a, b o c)" << endl;

					error = -1;
				}
				break;

			case 3:
				if(respuesta_recoger != 'a' && respuesta_recoger != 'b' && respuesta_recoger != 'c' && respuesta_recoger != 'd') 
				{
					cout << "La respuesta no es valida. Por favor, introduce una opción valida (a, b, c o d)" << endl;

					error = -1;
				}
				break;

			return error;
		}
	}

	void recogerPregunta(prfacil& Pregunta)
	{
		cin >> Pregunta;
	}

	void recogerPregunta(prmedio& Pregunta)
	{
		cin >> Pregunta;
	}

	void recogerPregunta(prdificil& Pregunta)
	{
		cin >> Pregunta;
	}
}