#include "DBConnector.h"
#include "utilidades.h"

 DBConnector::DBConnector(std::string dbFile)
  {
    //int result = sqlite3_open("test.sqlite", &db);
    int result = sqlite3_open(dbFile.c_str(), &db);
    //Si la BD no se ha podido abrir, muestra un mensaje
    if (result != SQLITE_OK)
    {
      std::cout << "Error opening database" << std::endl;
    }
  }

 DBConnector::~DBConnector() 
  {
    int result = sqlite3_close(db);
    if (result != SQLITE_OK)
    {
      std::cout << "Error closing database" << std::endl;
      std::cout << sqlite3_errmsg(db) << std::endl;
    }	
  }

  //CREATE TABLE:
  int DBConnector::create_table_Jugadores () 
  {
  	char existe[] = "SELECT name FROM sqlite_master WHERE type='table' AND  name = 'Jugadores'"; //SELECT para que solo cree la tabla si no existía
  	sqlite3_stmt *stmt_ex; 
  	int result;
  	int creada = sqlite3_prepare_v2(db, existe, -1, &stmt_ex, NULL);
  	creada = sqlite3_step(stmt_ex);//no va
  	
  	if(creada != 100)//Da 100 cuando la tabla existe y 101 cuando no (en realidad no sé por qué, pero funciona)
  	{
  		 std::cout << "LA TABLA NO EXISTE, creada = " << creada << std::endl;
	  	 sqlite3_stmt *stmt; 
	  	 char sql[] = "CREATE TABLE Jugadores("
	  	 				"NICK text primary key not null,"
	  	 				"PUNTUACION int not null);";

	  	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	  	if (result != SQLITE_OK)//Para continuar, el resultado debe ser SQLITE_OK, cualquier otro resultado será un error por no haberse procesado la select
	    {
	      std::cout << "Error Creating table Jugadores" << std::endl;   
	      sqlite3_finalize(stmt);   
	      std::cout << sqlite3_errmsg(db) << std::endl; //Devuelve el error interno de la BBDD (db) como resultado de la última operación sobre ella.
	    }
		
		result = sqlite3_step(stmt);
	    std::cout << "-----------" << std::endl;
	    
	    result = sqlite3_finalize(stmt);
	    if (result != SQLITE_OK) 
	    {
	      std::cout << "Error finalizing statement (CREATE)" << std::endl;
	      std::cout << sqlite3_errmsg(db) << std::endl;
	    }
	}
	else
	{
		std::cout << "LA TABLA EXISTE, creada = " << creada << std::endl;
		result = SQLITE_OK;
	}
	//--Finalizar el statement stmt_ex
  	result = sqlite3_finalize(stmt_ex);
    if (result != SQLITE_OK) 
    {
      std::cout << "Error finalizing statement" << std::endl;
      std::cout << sqlite3_errmsg(db) << std::endl;
    }
    //---
	return result;
  }

  int DBConnector::create_table_Preguntas () 
  {
  	char existe[] = "SELECT name FROM sqlite_master WHERE type='table' AND  name = 'Preguntas'"; //SELECT para que solo cree la tabla si no existía
  	sqlite3_stmt *stmt_ex; 
  	int result;
  	int creada = sqlite3_prepare_v2(db, existe, -1, &stmt_ex, NULL);
  	creada = sqlite3_step(stmt_ex);//no va
  	
  	if(creada != 100)//Da 100 cuando la tabla existe y 101 cuando no (en realidad no sé por qué, pero funciona)
  	{
	  	 sqlite3_stmt *stmt; 
	  	 char sql[] = "CREATE TABLE Preguntas("
	  	 				"ID int primary key not null,"
	  	 				"PREGUNTA text not null,"
	  	 				"R1 text not null,"
	  	 				"R2 text not null,"
	  	 				"R3 text," //Será null en preguntas fáciles
	  	 				"R4 text,"	//Será null en preguntas medias
	  	 				"DIFICULTAD text not null);";

	  	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	  	if (result != SQLITE_OK)//Para continuar, el resultado debe ser SQLITE_OK, cualquier otro resultado será un error por no haberse procesado la select
	    {
	      std::cout << "Error Creating table PREGUNTAS" << std::endl;   
	      sqlite3_finalize(stmt);   
	      std::cout << sqlite3_errmsg(db) << std::endl; //Devuelve el error interno de la BBDD (db) como resultado de la última operación sobre ella.
	    }
		
		result = sqlite3_step(stmt);
	    std::cout << "-----------" << std::endl;
	    
	    result = sqlite3_finalize(stmt);
	    if (result != SQLITE_OK) 
	    {
	      std::cout << "Error finalizing statement (CREATE)" << std::endl;
	      std::cout << sqlite3_errmsg(db) << std::endl;
	    }
	}
	else
	{
		std::cout << "LA TABLA EXISTE, creada = " << creada << std::endl;
		result = SQLITE_OK;
	}
	//--Finalizar el statement stmt_ex
  	result = sqlite3_finalize(stmt_ex);
    if (result != SQLITE_OK) 
    {
      std::cout << "Error finalizing statement" << std::endl;
      std::cout << sqlite3_errmsg(db) << std::endl;
    }
    //---
	return result;
  }

  //Para INSERT, UPDATE y DELETE, ver si el jugador existe:
  int DBConnector::Jugador_existe(jugador jugador)
  {
  	int sizeTotalJugadores;
  	canjuGadores(&sizeTotalJugadores);

  	jugador * Jugadores;
  	Jugadores = new jugador [sizeTotalJugadores];
  	leer_Jugadores(Jugadores);

  	for(int i=0; i<sizeTotalJugadores; i++)
  	{
  		if(jugador.nick == Jugadores[i].nick)
  			return 1;
  	}

  	return 0;
  }

  int DBConnector::Pregunta_existe(Preguntas_Respuestas p)
  {
  	int sizeTotalPreguntas;
  	cant_Preguntas(&sizeTotalJugadores);

  	Preguntas_Respuestas * Preguntas;
  	Preguntas = new Preguntas_Respuestas [sizeTotalPreguntas];
  	leer_Preguntas(Preguntas);

  	for(int i=0; i<sizeTotalPreguntas; i++)
  	{
  		if(p.ID == Preguntas[i].ID)
  			return 1;
  	}
  	return 0;
  }

  //INSERT:
  int DBConnector::insert_jugador (jugador jugadorInsertar)
  {
  	if(Jugador_existe(jugadorInsertar) == 0)
  	{ //el jugador no existe, lo podemos insertar
	  	sqlite3_stmt *stmt;
	  	char sql[] = "insert into Jugadores (NICK, PUNTUACION) values (?, 0)";
	    
	    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
	    if (result != SQLITE_OK) 
	    {
	      std::cout << "Error preparing statement (INSERT)" << std::endl;
	      std::cout << sqlite3_errmsg(db) << std::endl;
	      return result;
	    }
	    std::string nick= jugadorInsertar.getNick();
	    //Le pasamos el nick al statement
	    result = sqlite3_bind_text(stmt, 1, nick.c_str(), nick.length(), SQLITE_STATIC);

	    if (result != SQLITE_OK)
	    {
	      std::cout << "Error binding parameters" << std::endl;
	      std::cout << sqlite3_errmsg(db) << std::endl;
	      sqlite3_finalize(stmt);
	      return result;
	    }

	    //Ejecutamos el INSERT
	    result = sqlite3_step(stmt);
	    if (result != SQLITE_DONE) 
	    {
	      std::cout << "Error inserting new data into Jugadores table" << std::endl;
	      sqlite3_finalize(stmt);
	      return result;
	    }

	    result = sqlite3_finalize(stmt);
	    if (result != SQLITE_OK) 
	    {
	      std::cout << "Error finalizing statement (INSERT)" << std::endl;
	      std::cout << sqlite3_errmsg(db) << std::endl;
	    }
		return result;
	}
	else
	{
		std::cout << "El jugador ya existe - si quieres cambiar algo, UPDATE" << std::endl;	
		return 0;	
	}
}

int DBConnector::insert_Pregunta (Pregunta_Respuestas PreguntaInsertar)
  {
  	if(Pregunta_existe(PreguntaInsertar) == 0)
  	{ 
	  	sqlite3_stmt *stmt;
	  	char sql[] = "insert into Preguntas (ID, PREGUNTA, R1, R2, R3, R4, DIFICULTAD) values (?, ?, ?, ?, ?, ?, ?)";
	    
	    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
	    if (result != SQLITE_OK) 
	    {
	      std::cout << "Error preparing statement (INSERT)" << std::endl;
	      std::cout << sqlite3_errmsg(db) << std::endl;
	      return result;
	    }

	    //ATRIBUTOS QUE TENDRÁN TODAS:

	    	//ID

	    	result = sqlite3_bind_int(stmt, 1, PreguntaInsertar.getID());
	    	if (result != SQLITE_OK)
		    {
		      std::cout << "Error binding parameters" << std::endl;
		      std::cout << sqlite3_errmsg(db) << std::endl;
		      sqlite3_finalize(stmt);
		      return result;
		    }

		    //PREGUNTA
		    std::string pregunta = PreguntaInsertar.getPregunta();
	
		    result = sqlite3_bind_text(stmt, 2, pregunta.c_str(), pregunta.length(), SQLITE_STATIC);
		    if (result != SQLITE_OK)
		    {
		      std::cout << "Error binding parameters" << std::endl;
		      std::cout << sqlite3_errmsg(db) << std::endl;
		      sqlite3_finalize(stmt);
		      return result;
		    }


		    //R1:
		    std::string r1 = PreguntaInsertar.getRespuesta1();
	
		    result = sqlite3_bind_text(stmt, 3, r1.c_str(), r1.length(), SQLITE_STATIC);
		    if (result != SQLITE_OK)
		    {
		      std::cout << "Error binding parameters" << std::endl;
		      std::cout << sqlite3_errmsg(db) << std::endl;
		      sqlite3_finalize(stmt);
		      return result;
		    }

		    //R2:
		    std::string r2 = PreguntaInsertar.getRespuesta2();

		    result = sqlite3_bind_text(stmt, 4, r2.c_str(), r2.length(), SQLITE_STATIC);
		    if (result != SQLITE_OK)
		    {
		      std::cout << "Error binding parameters" << std::endl;
		      std::cout << sqlite3_errmsg(db) << std::endl;
		      sqlite3_finalize(stmt);
		      return result;
		    }

		    //SOLO EN MEDIA O DIFÍCIL
		    //R3:
		    if (PreguntaInsertar.getDificultad() != "#")
		    {
			    std::string r3 = PreguntaInsertar.getRespuesta3();
			    
			    result = sqlite3_bind_text(stmt, 5, r3.c_str(), r3.length(), SQLITE_STATIC);
			    if (result != SQLITE_OK)
			    {
			      std::cout << "Error binding parameters" << std::endl;
			      std::cout << sqlite3_errmsg(db) << std::endl;
			      sqlite3_finalize(stmt);
			      return result;
			    }
		    }
		    else
		    {
		    	//NULL
		    	// result = sqlite3_bind_text(stmt, 5, NULL, NULL, SQLITE_STATIC);
			    // if (result != SQLITE_OK)
			    // {
			    //   std::cout << "Error binding parameters" << std::endl;
			    //   std::cout << sqlite3_errmsg(db) << std::endl;
			    //   sqlite3_finalize(stmt);
			    //   return result;
			    // }
		    }

		    //SOLO EN DIFÍCIL
		    //R4:
		    if (PreguntaInsertar.getDificultad() == "###")
		    {
			    std::string r4 = PreguntaInsertar.getRespuesta4();
			    
			    result = sqlite3_bind_text(stmt, 6, r4.c_str(), r4.length(), SQLITE_STATIC);
			    if (result != SQLITE_OK)
			    {
			      std::cout << "Error binding parameters" << std::endl;
			      std::cout << sqlite3_errmsg(db) << std::endl;
			      sqlite3_finalize(stmt);
			      return result;
			    }
		    }
		    else
		    {
		    	//NULL
		    	// result = sqlite3_bind_text(stmt, 5, NULL, NULL, SQLITE_STATIC);
			    // if (result != SQLITE_OK)
			    // {
			    //   std::cout << "Error binding parameters" << std::endl;
			    //   std::cout << sqlite3_errmsg(db) << std::endl;
			    //   sqlite3_finalize(stmt);
			    //   return result;
			    // }
		    }

		    //DIFICULTAD
		    std::string dificultad = PreguntaInsertar.getDificultad();
	
		    result = sqlite3_bind_text(stmt, 7, dificultad.c_str(), dificultad.length(), SQLITE_STATIC);
		    if (result != SQLITE_OK)
		    {
		      std::cout << "Error binding parameters" << std::endl;
		      std::cout << sqlite3_errmsg(db) << std::endl;
		      sqlite3_finalize(stmt);
		      return result;
		    }
		   
	    //Ejecutamos el INSERT
	    result = sqlite3_step(stmt);
	    if (result != SQLITE_DONE) 
	    {
	      std::cout << "Error inserting new data into preguntas table" << std::endl;
	      sqlite3_finalize(stmt);
	      return result;
	    }

	    result = sqlite3_finalize(stmt);
	    if (result != SQLITE_OK) 
	    {
	      std::cout << "Error finalizing statement (INSERT)" << std::endl;
	      std::cout << sqlite3_errmsg(db) << std::endl;
	    }
		return result;
	}
	else
	{
		std::cout << "La pregunta ya existe - si quieres cambiar algo, UPDATE" << std::endl;	
		return 0;	
	}
}


//UPDATE:
int DBConnector::update_Jugador(jugador jugadorModificar)//Pasar el jugador completo
{
	if(Jugador_existe(jugadorModificar) == 1) //El jugador existe, lo podemos modificar
  	{ 
		sqlite3_stmt *stmt;
		char sql[] = "update Jugadores set PUNTUACION = ? where NICK = ?";
	    
	    std::string nick = jugadorModificar.getNick();
	    int puntuacion = jugadorModificar.getPuntuacion();
	    //Preparar el statement:
	    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
	    if (result != SQLITE_OK) 
	    {
	      std::cout << "Error preparing statement (INSERT)" << std::endl;
	      std::cout << sqlite3_errmsg(db) << std::endl;
	      return result;
	    }

	    //Juntar los parámetros con el statement
	     //Le pasamos el puntuacion al statement
	    result = sqlite3_bind_int(stmt, 1, puntuacion);
	    if (result != SQLITE_OK)
	    {
	      std::cout << "Error binding parameters" << std::endl;
	      sqlite3_finalize(stmt);
	      std::cout << sqlite3_errmsg(db) << std::endl;
	      return result;
	    }
	     //Le pasamos el nick al statement
	    result = sqlite3_bind_text(stmt, 2, nick.c_str(), nick.length(), SQLITE_STATIC);

	    if (result != SQLITE_OK)
	    {
	      std::cout << "Error binding parameters" << std::endl;
	      sqlite3_finalize(stmt);
	      std::cout << sqlite3_errmsg(db) << std::endl;
	      return result;
	    }

	     //Ejecutamos el UPDATE
	    result = sqlite3_step(stmt);
	    if (result != SQLITE_DONE) 
	    {
	      std::cout << "Error inserting new data into Jufgadores table" << std::endl;
	      sqlite3_finalize(stmt);
	      return result;
	    }

	    result = sqlite3_finalize(stmt);
	    if (result != SQLITE_OK) 
	    {
	      std::cout << "Error finalizing statement (UPDATE)" << std::endl;
	      std::cout << sqlite3_errmsg(db) << std::endl;
	    }
		return result;
	}
	else
	{
		return 0;
	}
}

int DBConnector::update_Jugador(Pregunta_Respuestas preguntaModificar)
{
	if(Pregunta_existe(preguntaModificar) == 1) 
  	{ 
		sqlite3_stmt *stmt;
		char sql[] = "update Preguntas set PREGUNTA = ?, R1 = ?, R2 = ?, R3 = ?, R4 = ?, DIFICULTAD = ? where ID = ?";
	    
	    std::string pregunta = preguntaModificar.getPregunta();
	    std::string r1 = preguntaModificar.getRespuesta1();
	    std::string r2 = preguntaModificar.getRespuesta2();
	    std::string r3 = preguntaModificar.getRespuesta3();
	    std::string r4 = preguntaModificar.getRespuesta4();
	    std::string dificultad = preguntaModificar.getDificultad();
	    int ID = preguntaModificar.ID;

	    //Preparar el statement:
	   	//ATRIBUTOS QUE TENDRÁN TODAS:

	    	//ID

	    	result = sqlite3_bind_int(stmt, 7, ID);
	    	if (result != SQLITE_OK)
		    {
		      std::cout << "Error binding parameters" << std::endl;
		      std::cout << sqlite3_errmsg(db) << std::endl;
		      sqlite3_finalize(stmt);
		      return result;
		    }

		    //PREGUNTA
	
		    result = sqlite3_bind_text(stmt, 1, pregunta.c_str(), pregunta.length(), SQLITE_STATIC);
		    if (result != SQLITE_OK)
		    {
		      std::cout << "Error binding parameters" << std::endl;
		      std::cout << sqlite3_errmsg(db) << std::endl;
		      sqlite3_finalize(stmt);
		      return result;
		    }

		    //R1:
	
		    result = sqlite3_bind_text(stmt, 2, r1.c_str(), r1.length(), SQLITE_STATIC);
		    if (result != SQLITE_OK)
		    {
		      std::cout << "Error binding parameters" << std::endl;
		      std::cout << sqlite3_errmsg(db) << std::endl;
		      sqlite3_finalize(stmt);
		      return result;
		    }

		    //R2:

		    result = sqlite3_bind_text(stmt, 3, r2.c_str(), r2.length(), SQLITE_STATIC);
		    if (result != SQLITE_OK)
		    {
		      std::cout << "Error binding parameters" << std::endl;
		      std::cout << sqlite3_errmsg(db) << std::endl;
		      sqlite3_finalize(stmt);
		      return result;
		    }

		    //SOLO EN MEDIA O DIFÍCIL
		    //R3:
		    if (dificultad != "#")
		    {
			    
			    result = sqlite3_bind_text(stmt, 4, r3.c_str(), r3.length(), SQLITE_STATIC);
			    if (result != SQLITE_OK)
			    {
			      std::cout << "Error binding parameters" << std::endl;
			      std::cout << sqlite3_errmsg(db) << std::endl;
			      sqlite3_finalize(stmt);
			      return result;
			    }
		    }
		    else
		    {
		    	//NULL -> si es facil, le metemos NULL en r3
		    	result = sqlite3_bind_text(stmt, 5, NULL, 0, SQLITE_STATIC);
			    if (result != SQLITE_OK)
			    {
			      std::cout << "Error binding parameters" << std::endl;
			      std::cout << sqlite3_errmsg(db) << std::endl;
			      sqlite3_finalize(stmt);
			      return result;
			    }
		    }

		    //SOLO EN DIFÍCIL
		    //R4:
		    if (dificultad == "###")
		    {
			    //Es dificil
			    result = sqlite3_bind_text(stmt, 5, r4.c_str(), r4.length(), SQLITE_STATIC);
			    if (result != SQLITE_OK)
			    {
			      std::cout << "Error binding parameters" << std::endl;
			      std::cout << sqlite3_errmsg(db) << std::endl;
			      sqlite3_finalize(stmt);
			      return result;
			    }
		    }
		    else
		    {
		    	// Es media o facil, no tiene R4
		    	//NULL
		    	result = sqlite3_bind_text(stmt, 5, NULL, 0, SQLITE_STATIC);
			    if (result != SQLITE_OK)
			    {
			      std::cout << "Error binding parameters" << std::endl;
			      std::cout << sqlite3_errmsg(db) << std::endl;
			      sqlite3_finalize(stmt);
			      return result;
			    }
		    }

		    //DIFICULTAD
	
		    result = sqlite3_bind_text(stmt, 6, dificultad.c_str(), dificultad.length(), SQLITE_STATIC);
		    if (result != SQLITE_OK)
		    {
		      std::cout << "Error binding parameters" << std::endl;
		      std::cout << sqlite3_errmsg(db) << std::endl;
		      sqlite3_finalize(stmt);
		      return result;
		    }

		    //ID

	    	result = sqlite3_bind_int(stmt, 7, ID);
	    	if (result != SQLITE_OK)
		    {
		      std::cout << "Error binding parameters" << std::endl;
		      std::cout << sqlite3_errmsg(db) << std::endl;
		      sqlite3_finalize(stmt);
		      return result;
		    }

	     //Ejecutamos el UPDATE
	    result = sqlite3_step(stmt);
	    if (result != SQLITE_DONE) 
	    {
	      std::cout << "Error inserting new data into Preguntas table" << std::endl;
	      sqlite3_finalize(stmt);
	      return result;
	    }

	    result = sqlite3_finalize(stmt);
	    if (result != SQLITE_OK) 
	    {
	      std::cout << "Error finalizing statement (DELETE)" << std::endl;
	      std::cout << sqlite3_errmsg(db) << std::endl;
	    }
		return result;
	}
	else
	{
		return 0;
	}
}

//DELETE:
int DBConnector::delete_Jugador(jugador jugadorBorrar)
{
	if(Jugador_existe(jugadorBorrar) == 1) //El jugador existe, lo podemos modificar
  	{ 
		sqlite3_stmt *stmt;
		char sql[] = "DELETE from Jugadores where NICK = ?";

		std::string nick = jugadorBorrar.getNick();
	    
	    //Preparar el statement:
	    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
	    if (result != SQLITE_OK) 
	    {
	      std::cout << "Error preparing statement (INSERT)" << std::endl;
	      std::cout << sqlite3_errmsg(db) << std::endl;
	      return result;
	    }

	    //Juntar los parámetros con el statement
	     //Le pasamos el nick al statement
	    result = sqlite3_bind_text(stmt, 1, nick.c_str(), nick.length(), SQLITE_STATIC);
	    if (result != SQLITE_OK)
	    {
	      std::cout << "Error binding parameters" << std::endl;
	      sqlite3_finalize(stmt);
	      std::cout << sqlite3_errmsg(db) << std::endl;
	      return result;
	    }

	     //Ejecutamos el DELETE
	    result = sqlite3_step(stmt);
	    if (result != SQLITE_DONE) 
	    {
	      std::cout << "Error DELETING the player with nick " << nick << std::endl;
	      sqlite3_finalize(stmt);
	      return result;
	    }

	    result = sqlite3_finalize(stmt);
	    if (result != SQLITE_OK) 
	    {
	      std::cout << "Error finalizing statement (UPDATE)" << std::endl;
	      std::cout << sqlite3_errmsg(db) << std::endl;
	    }
		return result;
	}
	else
	{
		return 0;
	}
}

int DBConnector::delete_Pregunta(Preguntas_Respuestas preguntaBorrar)
{
	if(Jugador_existe(preguntaBorrar) == 1) 
  	{ 
		sqlite3_stmt *stmt;
		char sql[] = "DELETE from Preguntas where ID = ?";

		int ID = preguntaBorrar.getID();
	    
	    //Preparar el statement:
	    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
	    if (result != SQLITE_OK) 
	    {
	      std::cout << "Error preparing statement (DELETE)" << std::endl;
	      std::cout << sqlite3_errmsg(db) << std::endl;
	      return result;
	    }

	    //Juntar los parámetros con el statement
	    result = sqlite3_bind_int(stmt, 1, ID);
	    if (result != SQLITE_OK)
	    {
	      std::cout << "Error binding parameters" << std::endl;
	      sqlite3_finalize(stmt);
	      std::cout << sqlite3_errmsg(db) << std::endl;
	      return result;
	    }

	     //Ejecutamos el DELETE
	    result = sqlite3_step(stmt);
	    if (result != SQLITE_DONE) 
	    {
	      std::cout << "Error DELETING the question with ID " << ID << std::endl;
	      sqlite3_finalize(stmt);
	      return result;
	    }

	    result = sqlite3_finalize(stmt);
	    if (result != SQLITE_OK) 
	    {
	      std::cout << "Error finalizing statement (DELETE)" << std::endl;
	      std::cout << sqlite3_errmsg(db) << std::endl;
	    }
		return result;
	}
	else
	{
		return 0;
	}
}

//SELECT
int DBConnector::leer_Jugadores(vector <jugador> listaTodosJugadores)
{
	//int cont = 0;
	sqlite3_stmt *stmt; 
	char sql[] = "select NICK, PUNTUACION from Jugadores";
   
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
    if (result != SQLITE_OK)
    {
      std::cout << "Error preparing statement (SELECT)" << std::endl;      
      std::cout << sqlite3_errmsg(db) << std::endl;
      return result;
    }

    //Variables en las que recogeremos los atributos de cada jugador
    int puntuacion;
  	char nick[200];
  
    do
    {
      result = sqlite3_step(stmt);
      if (result == SQLITE_ROW) 
      {
      	//Leer el nick y la puntuacion de la linea del SELECT
       	strcpy(nick, (char*)sqlite3_column_text(stmt, 0));
      	puntuacion = sqlite3_column_int(stmt, 1);
  
      	//Crear un jugador con esos atributos
      	jugador jugador = new jugador( nick, puntuacion);
    	
    	listaTodosJugadores.pus_back (jugador);
      	// listaTodosJugadores[cont] = jugador;
      	// cont++;
      }
    } while (result == SQLITE_ROW);

    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) 
    {
      std::cout << "Error finalizing statement (SELECT)" << std::endl;
      std::cout << sqlite3_errmsg(db) << std::endl;
      return result;
    }
    return SQLITE_OK;
}

int DBConnector::cant_Jugadores(int* sizeTotalJugadores)
{
	* sizeTotalJugadores = 0;
	int cont = 0;
	sqlite3_stmt *stmt; 
	char sql[] = "select NICK, PUNTUACION from Jugadores";
   
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
    if (result != SQLITE_OK)
    {
      std::cout << "Error preparing statement (SELECT)" << std::endl;      
      std::cout << sqlite3_errmsg(db) << std::endl;
      return result;
    }
  
    do
    {
      result = sqlite3_step(stmt);
      if (result == SQLITE_ROW) 
      {
		*sizeTotalJugadores = *sizeTotalJugadores + 1;  
      }
    } while (result == SQLITE_ROW);

    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) 
    {
      std::cout << "Error finalizing statement (SELECT)" << std::endl;
      std::cout << sqlite3_errmsg(db) << std::endl;
      return result;
    }
    return SQLITE_OK;
}

int DBConnector::leer_Preguntas(vector <Pregunta_respuestas> listaTodoasPreguntas)
{
	int cont = 0;
	sqlite3_stmt *stmt; 
	char sql[] = "select ID, PREGUNTA, R1, R2, R3, R4, DIFICULTAD from Preguntas";
   
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
    if (result != SQLITE_OK)
    {
      std::cout << "Error preparing statement (SELECT)" << std::endl;      
      std::cout << sqlite3_errmsg(db) << std::endl;
      return result;
    }
 	//Variables a recoger
 	int ID;
 	char pregunta[500];
 	char r1[500];
 	char r2[500];
 	char r3[500];
 	char r4[500];
 	char dificultad[3];
    do
    {
      result = sqlite3_step(stmt);
      if (result == SQLITE_ROW) 
      { 

      	ID = sqlite3_column_int(stmt, 0);
      	p.setID (ID);

       	strcpy(preguta, (char*)sqlite3_column_text(stmt, 1));   
       	p.setPregunta(pregunta);

       	strcpy(r1, (char*)sqlite3_column_text(stmt, 2));
       	p.setRespuesta1 (r1);

       	strcpy(r2, (char*)sqlite3_column_text(stmt, 3));
       	p.setRespuesta2 (r2);
      	//Leemos dificultad antes que R3 y R4 ya que depende de este atributo si tiene o no estos dos
      	strcpy(dificultad, (char*)sqlite3_column_text(stmt, 6));
      	p.setDificultad(dificultad);

      	if(strcmp(dificultad, "###") == 0)
      	{
      		//Es dificil
      		strcpy(r3, (char*)sqlite3_column_text(stmt, 4));
      		p.SetRespuesta3 ( r3 );
       		strcpy(r4, (char*)sqlite3_column_text(stmt, 5));
       		p.setRespuesta4 (r4);

       		//Creamos una Pregunta_respuestas con estos atributos:
      		Preguntas_Respuestas p = new (pregunta,r1, r2, r3, r4, dificultad, true);//el ultimo es true para no darle el ID
      		p.setID (ID);
      	}
      	else if(strcmp(dificultad, "##") == 0)
      	{
      		//Es media
      		p.SetRespuesta3 ( r3 );
      		Preguntas_Respuestas p = new (pregunta,r1, r2, r3, dificultad, true);//el ultimo es true para no darle el ID
      		p.setID (ID);
      	}
      	else
      	{
      		Preguntas_Respuestas p = new (pregunta,r1, r2, dificultad, true);//el ultimo es true para no darle el ID
      		p.setID (ID);
      	}
      	// listaTodasPreguntas[cont] = p;
      	// cont++;  
      	listaTodasPreguntas.pus_back(p);
      }
    } while (result == SQLITE_ROW);

    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) 
    {
      std::cout << "Error finalizing statement (SELECT)" << std::endl;
      std::cout << sqlite3_errmsg(db) << std::endl;
      return result;
    }
    return SQLITE_OK;
}

int DBConnector::cant_Preguntas(int* sizeTotalPreguntas)
{
	* sizeTotalPreguntas = 0;
	int cont = 0;
	sqlite3_stmt *stmt; 
	char sql[] = "select ID, PREGUNTA, R1, R2, R3, R4, DIFICULTAD from Preguntas";
   
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
    if (result != SQLITE_OK)
    {
      std::cout << "Error preparing statement (SELECT)" << std::endl;      
      std::cout << sqlite3_errmsg(db) << std::endl;
      return result;
    }
  
    do
    {
      result = sqlite3_step(stmt);
      if (result == SQLITE_ROW) 
      {
		*sizeTotalPreguntas = *sizeTotalPreguntas + 1;  
      }
    } while (result == SQLITE_ROW);

    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) 
    {
      std::cout << "Error finalizing statement (SELECT)" << std::endl;
      std::cout << sqlite3_errmsg(db) << std::endl;
      return result;
    }
    return SQLITE_OK;
}

//DROP TABLE:
int DBConnector::drop_Jugadores ()
{
	sqlite3_stmt *stmt;
	char sql[] = "DROP TABLE if exists Jugadores";
    
    //Preparar el statement:
    // int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
    // if (result != SQLITE_OK) 
    // {
    //   std::cout << "Error preparing statement (INSERT)" << std::endl;
    //   std::cout << sqlite3_errmsg(db) << std::endl;
    //   return result;
    // }

    //  //Ejecutamos el DROP
    result = sqlite3_exec(db, sql, NULL, NULL, NULL);
    if (result != SQLITE_DONE) 
    {
      std::cout << "Error DROPING Jugadores"<< std::endl;
      sqlite3_finalize(stmt);
      return result;
    }
 //Esto solo habrá que hacerlo si hacemos prepare statement
    // result = sqlite3_finalize(stmt);
    // if (result != SQLITE_OK) 
    // {
    //   std::cout << "Error finalizing statement (UPDATE)" << std::endl;
    //   std::cout << sqlite3_errmsg(db) << std::endl;
    // }
	return result;
}

int DBConnector::drop_Preguntas ()
{
	sqlite3_stmt *stmt;
	char sql[] = "DROP TABLE if exists Preguntas";
    
    //Preparar el statement:
    // int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
    // if (result != SQLITE_OK) 
    // {
    //   std::cout << "Error preparing statement" << std::endl;
    //   std::cout << sqlite3_errmsg(db) << std::endl;
    //   return result;
    // }

    result = sqlite3_exec(db, sql, NULL, NULL, NULL);
    if (result != SQLITE_DONE) 
    {
      std::cout << "Error DROPING Preguntas"<< std::endl;
      sqlite3_finalize(stmt);
      return result;
    }

    //Esto solo habrá que hacerlo si hacemos prepare statement
    // result = sqlite3_finalize(stmt);
    // if (result != SQLITE_OK) 
    // {
    //   std::cout << "Error finalizing statement " << std::endl;
    //   std::cout << sqlite3_errmsg(db) << std::endl;
    // }
	return result;
}