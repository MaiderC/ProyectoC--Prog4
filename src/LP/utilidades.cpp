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
	void utilidades::mostrarMensaje(const string& str)
	{
		cout << str << endl;
	}

	void utilidades::mostrarInt(const int& i)
	{
		cout << i << endl;
	}

	void utilidades::mostrarPregunta(const preguntas_respuestas& Pregunta)
	{
		cout << Pregunta;
	}

	void utilidades::mostrarTodasPreguntas(const vector<preguntas_respuestas> TodasPreguntas)
	{
		for(int i = 0; i < TodasPreguntas.size(); i++)
		{
			cout << (i+1) << ".-";
			mostrarPregunta(TodasPreguntas[i]);
			cout << endl << endl;
		}
	}

		cout << "Indica la repuesta que consideras correcta (a, b o c):  "; //Ponerlo donde tenga que ir

	void utilidades::mostrarPuntuacion(const jugador& jugador)
	{
		cout << jugador.getNick() << ": " << jugador.getPuntuacion() << " puntos" << endl;
	}

	void utilidades::mensajeGanador(const jugador& ganador) //A este metodo se le llamara antes de actualizar las puntuaciones, con lo que la puntuación sera la acumulada en esa partida
	{
		cout << "El jugador ganador de esta partida ha sido " << ganador.getNick() << " con " << ganador.getPuntuacion() << " puntos. ¡Enhorabuena!" << endl;
	}

	int utilidades::mensajeEmpate(const vector<jugador>& empatados) //Recibe una lista con los jugadores que han empatado
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
		}while(opcion < 1 || opcion > 2)
	}

	//-----------------------------------------------------------------
	void utilidades::recogerString(string& string_recoger)
	{
		cin >> string_recoger;
	}

	void utilidades::recogerInt(int& numero_recoger)
	{
		cin >> numero_recoger;
	}

	int utilidades::recogerOpcionRespuesta(string& respuesta_recoger, string dificultad) 
	{
		int Dificultad = dificultad.size();
		int error = 0;
		
		recogerString(respuesta_recoger);

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

	void utilidades::recogerPregunta(preguntas_respuestas& Pregunta)
	{
		cin >> Pregunta;
	}
}