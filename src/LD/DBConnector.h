#include "sqlite3.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "jugador.h"
#include "utilidades.h"

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
	int leer_Jugadores(jugador* listaTodosJugadores);
	int cant_Jugadores(int* sizeTotalJugadores);
	int drop_Jugadores ();

	//-----------------------------------

	//----------Pregunta_respuestas----------
	int create_table_Preguntas ();
  	int insert_Pregunta (jugador jugadorInsertar);
	int update_Pregunta(jugador jugadorModificar);
	int delete_Pregunta(jugador jugadorBorrar);
	int leer_Preguntas(jugador* listaTodosJugadores);
	int cant_Preguntas(int* sizeTotalJugadores);
	int drop_Preguntas ();
	
	//---------------------------------------

	
};