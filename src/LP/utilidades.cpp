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

	void mostrarTodasPreguntas(const vector<preguntas_respuestas*> TodasPreguntas)
	{
		
		for(int i = 0; i < TodasPreguntas.size(); i++)
		{
			cout << (i+1) << ".-";

			if (TodasPreguntas[i]->getDificultad() == "#")
			{
				prfacil* preguntaAux = dynamic_cast<prfacil*> (TodasPreguntas[i]);
				mostrarPregunta(*preguntaAux);
			}
			else if (TodasPreguntas[i]->getDificultad() == "##")
			{
				prmedio* preguntaAux = dynamic_cast<prmedio*> (TodasPreguntas[i]);
				mostrarPregunta(*preguntaAux);
			}
			else if(TodasPreguntas[i]->getDificultad() == "###")
			{
				prdificil* preguntaAux = dynamic_cast<prdificil*> (TodasPreguntas[i]);
				mostrarPregunta(*preguntaAux);
			}
			cout << endl << endl;
		}
	}
	
	void mensajeGanador(const jugador& ganador) //A este metodo se le llamara antes de actualizar las puntuaciones, con lo que la puntuacion sera la acumulada en esa partida
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
		getline(cin, string_recoger);

		while(string_recoger.length() == 0)
		{
			cout << "por favor, introduce un texto: " << endl;
			getline(cin, string_recoger);
		}
	}

	void recogerInt(int& numero_recoger)
	{
		string aux;
		int intAux;
		int intTemp;

		getline(cin, aux);
		intAux = sscanf(aux.c_str(), "%d", &intTemp);

		while(intAux == 0)
		{
			mostrarMensaje("No has insertado un numero, vuelve a intentarlo: ");
			getline(cin, aux);
			intAux = sscanf(aux.c_str(), "%d", &intTemp);
		}

		numero_recoger = intTemp;
	}

	char recogerOpcionRespuesta(int& respValida, string dificultad)
	{
		int Dificultad = dificultad.length();
		string aux;
		char respuesta_recoger;
		
		getline(cin, aux);

		if(aux.length() == 1)
		{
			respValida = 0;

			sscanf(aux.c_str(), "%c", &respuesta_recoger);

			switch(Dificultad)
			{
				case 1:
					if(respuesta_recoger != 'a' && respuesta_recoger != 'b')
					{
						cout << "La respuesta no es valida. Por favor, introduce una opcion valida (a o b)" << endl;

						respValida = -1;
					}
					break;

				case 2:
					if(respuesta_recoger != 'a' && respuesta_recoger != 'b' && respuesta_recoger != 'c') 
					{
						cout << "La respuesta no es valida. Por favor, introduce una opcion valida (a, b o c)" << endl;

						respValida = -1;
					}
					break;

				case 3:
					if(respuesta_recoger != 'a' && respuesta_recoger != 'b' && respuesta_recoger != 'c' && respuesta_recoger != 'd') 
					{
						cout << "La respuesta no es valida. Por favor, introduce una opcion valida (a, b, c o d)" << endl;

						respValida = -1;
					}
					break;
			}
		} else
		{
			cout << "La respuesta no es valida, tiene que ser un caracter." << endl;
			respValida = -1;
		}

		return respuesta_recoger;
	}

	void recogerPregunta(prfacil* Pregunta)
	{
		cin >> (*Pregunta);
	}

	void recogerPregunta(prmedio* Pregunta)
	{
		cin >> (*Pregunta);
	}

	void recogerPregunta(prdificil* Pregunta)
	{
		cin >> (*Pregunta);
	}
}