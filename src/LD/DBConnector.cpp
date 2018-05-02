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

  //INSERT:
  int DBConnector::inserjuGador (jugador jugadorInsertar)
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
	    std::string nick= jugadorInsertar.nick;
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
		std::cout << "El jugador ya existe - si quieres cambiar algo, INSERT" << std::endl;	
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
	    
	    std::string nick = jugadorModificar.nick;
	    int puntuacion = jugadorModificar.puntuacion;
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

//DELETE:
int DBConnector::delete_Jugador(jugador jugadorBorrar)
{
	if(Jugador_existe(jugadorBorrar) == 1) //El jugador existe, lo podemos modificar
  	{ 
		sqlite3_stmt *stmt;
		char sql[] = "DELETE from Jugadores where NICK = ?";

		std::string nick = jugadorBorrar.nick;
	    
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

//SELECT
int DBConnector::leer_Jugadores(jugador* listaTodosJugadores)
{
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

    //Variables en las que recogeremos los atributos de cada jugador
    int puntuacion;
  	char nick[200];
  	std::cout << "Antes del Do" << std::endl; 
  
    do
    {
      result = sqlite3_step(stmt);
      if (result == SQLITE_ROW) 
      {
      	//Leer el nick y la puntuacion de la linea del SELECT
      	std::cout << "EMPIEZA A LEER" << std::endl; 
       	strcpy(nick, (char*)sqlite3_column_text(stmt, 0));
       	std::cout << "sTRCPY HECHO" << std::endl; 
      	puntuacion = sqlite3_column_int(stmt, 1);

      	std::cout << "nick: "<< nick << "puntuación " <<  puntuacion << std::endl; 
  
      	//Crear un jugador con esos atributos
      	jugador jugador;
      
      	
      	jugador.puntuacion = puntuacion;
      	jugador.nick = nick;
      	std::cout << "nick: "<< jugador.nick <<  std::endl; 
      	//Meterlo en la lista
      	std::cout << "Cont: "<< cont << std::endl; 
      	listaTodosJugadores[cont] = jugador;
      	cont++;

		std::cout << "Cont: "<< cont << std::endl; 
  
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

//DROP TABLE:
int DBConnector::drop_Jugadores ()
{
	sqlite3_stmt *stmt;
	char sql[] = "DROP TABLE if exists Jugadores";
    
    //Preparar el statement:
    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
    if (result != SQLITE_OK) 
    {
      std::cout << "Error preparing statement (INSERT)" << std::endl;
      std::cout << sqlite3_errmsg(db) << std::endl;
      return result;
    }

     //Ejecutamos el DROP
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) 
    {
      std::cout << "Error DROPING Jugadores"<< std::endl;
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