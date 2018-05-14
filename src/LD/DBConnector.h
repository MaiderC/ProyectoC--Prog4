#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H
#include "sqlite3.h"
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include "../LN/jugador.h"
#include "../LN/preguntas_respuestas.h"
#include "../LN/prfacil.h"
#include "../LN/prmedio.h"
#include "../LN/prdificil.h"

using namespace std;

class DBConnector
{
	private:
 	 sqlite3 *db = NULL;

	public:
		DBConnector(std::string dbFile);
		~DBConnector();

	//---------------Jugador-----------

    int create_table_Jugadores ();
  	int insert_Jugador (jugador jugadorInsertar);
	int update_Jugador(jugador jugadorModificar);
	int delete_Jugador(jugador jugadorBorrar);
	int leer_Jugadores(vector <jugador>& listaTodosJugadores);
	int cant_Jugadores(int* sizeTotalJugadores);
	int drop_Jugadores ();
	int Jugador_existe(jugador jugador);

	//-----------------------------------

	//----------Pregunta_respuestas----------
	int create_table_Preguntas ();
  	int insert_Pregunta (preguntas_respuestas PreguntaInsertar);
	int update_Pregunta(preguntas_respuestas preguntaModificar);
	int delete_Pregunta(preguntas_respuestas preguntaBorrar);
	int leer_Preguntas(vector <preguntas_respuestas>& listaTodasPreguntas);
	int cant_Preguntas(int* sizeTotalJugadores);
	int drop_Preguntas ();
	int Pregunta_existe(preguntas_respuestas p);

	//---------------------------------------
};
#endif