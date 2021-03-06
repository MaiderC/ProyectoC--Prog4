#include "DBConnector.h"
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

 DBConnector::DBConnector(string dbFile)
  {
    //int result = sqlite3_open("test.sqlite", &db);
    int result = sqlite3_open(dbFile.c_str(), &db);
  
    ofstream ofs("./Data/loggers.txt", ios_base::app);
    //Si la BD no se ha podido abrir, muestra un mensaje
    if (result != SQLITE_OK)
    {
      ofs << "Error opening database" << endl;
    }
    ofs.close();
  }

 DBConnector::~DBConnector() 
  {
  	ofstream ofs("./Data/loggers.txt", ios_base::app);
    int result = sqlite3_close(db);
    if (result != SQLITE_OK)
    {
       ofs << "Error closing database" <<  endl;
       ofs << sqlite3_errmsg(db) <<  endl;
    }	
    ofs.close();
  }

  //CREATE TABLE:
  int DBConnector::create_table_Jugadores () 
  {
    ofstream ofs("./Data/loggers.txt", ios_base::app);

  	char existe[] = "SELECT name FROM sqlite_master WHERE type='table' AND  name = 'Jugadores'"; //SELECT para que solo cree la tabla si no existía
  	sqlite3_stmt *stmt_ex; 
  	int result;
  	int creada = sqlite3_prepare_v2(db, existe, -1, &stmt_ex, NULL);
  	creada = sqlite3_step(stmt_ex);//no va
  	
  	if(creada != 100)//Da 100 cuando la tabla existe y 101 cuando no (en realidad no sé por qué, pero funciona)
  	{
	  	 sqlite3_stmt *stmt; 
	  	 char sql[] = "CREATE TABLE Jugadores("
	  	 				"NICK text primary key not null,"
	  	 				"PUNTUACION int not null);";

	  	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
	  	if (result != SQLITE_OK)//Para continuar, el resultado debe ser SQLITE_OK, cualquier otro resultado será un error por no haberse procesado la select
	    {
	       ofs << "Error Creating table Jugadores" <<  endl;   
	      sqlite3_finalize(stmt);   
	       ofs << sqlite3_errmsg(db) <<  endl; //Devuelve el error interno de la BBDD (db) como resultado de la última operación sobre ella.
	    }
		
		result = sqlite3_step(stmt);
	    
	    result = sqlite3_finalize(stmt);
	    if (result != SQLITE_OK) 
	    {
	       ofs << "Error finalizing statement (CREATE)" <<  endl;
	       ofs << sqlite3_errmsg(db) <<  endl;
	    }
	}
	else
	{
		 ofs << "LA TABLA EXISTE, creada = " << creada <<  endl;
		result = SQLITE_OK;
	}
	//--Finalizar el statement stmt_ex
  	result = sqlite3_finalize(stmt_ex);
    if (result != SQLITE_OK) 
    {
       ofs << "Error finalizing statement" <<  endl;
       ofs << sqlite3_errmsg(db) <<  endl;
    }
    //---
    ofs.close();
	return result;
  }

  int DBConnector::create_table_Preguntas () 
  {
  	ofstream ofs("./Data/loggers.txt", ios_base::app);
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
	       ofs << "Error Creating table PREGUNTAS" <<  endl;   
	      sqlite3_finalize(stmt);   
	       ofs << sqlite3_errmsg(db) <<  endl; //Devuelve el error interno de la BBDD (db) como resultado de la última operación sobre ella.
	    }
		
		result = sqlite3_step(stmt);
	    
	    result = sqlite3_finalize(stmt);
	    if (result != SQLITE_OK) 
	    {
	       ofs << "Error finalizing statement (CREATE)" <<  endl;
	       ofs << sqlite3_errmsg(db) <<  endl;
	    }
	}
	else
	{
		 ofs << "LA TABLA EXISTE, creada = " << creada <<  endl;
		result = SQLITE_OK;
	}
	//--Finalizar el statement stmt_ex
  	result = sqlite3_finalize(stmt_ex);
    if (result != SQLITE_OK) 
    {
       ofs << "Error finalizing statement" <<  endl;
       ofs << sqlite3_errmsg(db) <<  endl;
    }
    //---
    ofs.close();
	return result;
  }

  //Para INSERT, UPDATE y DELETE, ver si el jugador existe:
  int DBConnector::Jugador_existe(jugador jug)
  {
  	vector<jugador> Jugadores;

  	leer_Jugadores(Jugadores);

  	for(int i=0; i<Jugadores.size(); i++)
  	{
  		if(jug.getNick() == Jugadores[i].getNick())
  			return 1;
  	}

  	return 0;
  }

  int DBConnector::Pregunta_existe(preguntas_respuestas* p)
  {
  	vector<preguntas_respuestas*> Preguntas;
  	leer_Preguntas(Preguntas);

  	for(int i=0; i<Preguntas.size(); i++)
  	{
  		if(p->getID() == Preguntas[i]->getID())
  			return 1;
  	}
  	return 0;
  }

  //INSERT:
  int DBConnector::insert_Jugador (jugador jugadorInsertar)
  {
  	ofstream ofs("./Data/loggers.txt", ios_base::app);
  	if(Jugador_existe(jugadorInsertar) == 0)
  	{ //el jugador no existe, lo podemos insertar
	  	sqlite3_stmt *stmt;
	  	char sql[] = "insert into Jugadores (NICK, PUNTUACION) values (?, 0)";
	    
	    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
	    if (result != SQLITE_OK) 
	    {
	       ofs << "Error preparing statement (INSERT)" <<  endl;
	       ofs << sqlite3_errmsg(db) <<  endl;
	       ofs.close();
	      return result;
	    }
	     string nick= jugadorInsertar.getNick();
	    //Le pasamos el nick al statement
	    result = sqlite3_bind_text(stmt, 1, nick.c_str(), nick.length(), SQLITE_TRANSIENT);

	    if (result != SQLITE_OK)
	    {
	       ofs << "Error binding parameters" <<  endl;
	       ofs << sqlite3_errmsg(db) <<  endl;
	      sqlite3_finalize(stmt);
	       ofs.close();
	      return result;
	    }

	    //Ejecutamos el INSERT
	    result = sqlite3_step(stmt);
	    if (result != SQLITE_DONE) 
	    {
	       ofs << "Error inserting new data into Jugadores table" <<  endl;
	      sqlite3_finalize(stmt);
	       ofs.close();
	      return result;
	    }

	    result = sqlite3_finalize(stmt);
	    if (result != SQLITE_OK) 
	    {
	       ofs << "Error finalizing statement (INSERT)" <<  endl;
	       ofs << sqlite3_errmsg(db) <<  endl;
	    }
	    ofs.close();
		return result;
	}
	else
	{
		 ofs << "El jugador ya existe - si quieres cambiar algo, UPDATE" <<  endl;	
		 ofs.close();
		return 0;	
	}
}

int DBConnector::insert_Pregunta (preguntas_respuestas* PreguntaInsertar)
{
	ofstream ofs("./Data/loggers.txt", ios_base::app);
  	if(Pregunta_existe(PreguntaInsertar) == 0)
  	{ 
	  	sqlite3_stmt *stmt;
	  	char sql[] = "insert into Preguntas (ID, PREGUNTA, R1, R2, R3, R4, DIFICULTAD) values (?, ?, ?, ?, ?, ?, ?)";
	    
	    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	    if (result != SQLITE_OK) 
	    {
	       ofs << "Error preparing statement (INSERT)" <<  endl;
	       ofs << sqlite3_errmsg(db) <<  endl;
	       ofs.close();
	      return result;
	    }
		
	   if (PreguntaInsertar->getDificultad()=="#")
	    {
	    	prfacil* p = dynamic_cast<prfacil*>(PreguntaInsertar);

	    	//ID
	    	result = sqlite3_bind_int(stmt, 1, ((*p)).getID());
	    	if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		      ofs.close();
		      return result;
		    }

		    //PREGUNTA
		     string pregunta = (*p).getPregunta();
	
		    result = sqlite3_bind_text(stmt, 2, pregunta.c_str(), pregunta.length(), SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		      ofs.close();
		      return result;
		    }


		    //R1:
		     string r1 = (*p).getRespuesta1();
	
		    result = sqlite3_bind_text(stmt, 3, r1.c_str(), r1.length(), SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		      ofs.close();
		      return result;
		    }

		    //R2:
		     string r2 = (*p).getRespuesta2();

		    result = sqlite3_bind_text(stmt, 4, r2.c_str(), r2.length(), SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		      ofs.close();
		      return result;
		    }

			//R3 NULL
	    	result = sqlite3_bind_text(stmt, 5,  NULL, 0, SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		      ofs.close();
		      return result;
		    }

		    //R4 NULL
	    	result = sqlite3_bind_text(stmt, 5,  NULL, 0, SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		      ofs.close();
		      return result;
		    }
		     //DIFICULTAD
		     string dificultad = (*p).getDificultad();
	
		     result = sqlite3_bind_text(stmt, 7, dificultad.c_str(), dificultad.length(), SQLITE_TRANSIENT);
			
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		      ofs.close();
		      return result;
		    }

	    }
	    else if(PreguntaInsertar->getDificultad()=="##")
	    {
	    	prmedio* p = dynamic_cast<prmedio*>(PreguntaInsertar);

	    	//ID
	    	result = sqlite3_bind_int(stmt, 1, (*p).getID());
	    	if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		      ofs.close();
		      return result;
		    }

		    //PREGUNTA
		     string pregunta = (*p).getPregunta();
	
		    result = sqlite3_bind_text(stmt, 2, pregunta.c_str(), pregunta.length(), SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		      ofs.close();
		      return result;
		    }

		    //R1:
		     string r1 = (*p).getRespuesta1();
	
		    result = sqlite3_bind_text(stmt, 3, r1.c_str(), r1.length(), SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		      ofs.close();
		      return result;
		    }

		    //R2:
		     string r2 = (*p).getRespuesta2();

		    result = sqlite3_bind_text(stmt, 4, r2.c_str(), r2.length(), SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		      ofs.close();
		      return result;
		    }

		    //R3:
		    string r3 = (*p).getRespuesta3();
			    
		    result = sqlite3_bind_text(stmt, 5, r3.c_str(), r3.length(), SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		      ofs.close();
		      return result;
		    }

		    //R4 NULL
	    	result = sqlite3_bind_text(stmt, 6, NULL, 0, SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		      ofs.close();
		      return result;
		    }

		    //DIFICULTAD
		     string dificultad = (*p).getDificultad();
	
		    result = sqlite3_bind_text(stmt, 7, dificultad.c_str(), dificultad.length(), SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		      ofs.close();
		      return result;
		    }

	    }
	    else
	    {
	    	
	    	prdificil* p = dynamic_cast<prdificil*>(PreguntaInsertar);

	    	//ID
	    	result = sqlite3_bind_int(stmt, 1, (*p).getID());
	    	if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		      return result;
		    }

		    //PREGUNTA
		     string pregunta = (*p).getPregunta();
	
		    result = sqlite3_bind_text(stmt, 2, pregunta.c_str(), pregunta.length(), SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		      return result;
		    }

		    //R1:
		     string r1 = (*p).getRespuesta1();
	
		    result = sqlite3_bind_text(stmt, 3, r1.c_str(), r1.length(), SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		      return result;
		    }

		    //R2:
		     string r2 = (*p).getRespuesta2();

		    result = sqlite3_bind_text(stmt, 4, r2.c_str(), r2.length(), SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		      ofs.close();
		      return result;
		    }

		    //R3:
		    string r3 = (*p).getRespuesta3();
			    
		    result = sqlite3_bind_text(stmt, 5, r3.c_str(), r3.length(), SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		      ofs.close();
		      return result;
		    }

		    //R4:
		     string r4 = (*p).getRespuesta4();
			    
		    result = sqlite3_bind_text(stmt, 6, r4.c_str(), r4.length(), SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		      ofs.close();
		      return result;
		    }
		    
		    //DIFICULTAD
		     string dificultad = (*p).getDificultad();
	
		    result = sqlite3_bind_text(stmt, 7, dificultad.c_str(), dificultad.length(), SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		      ofs.close();
		      return result;
		    }
	    }
		   
	    //Ejecutamos el INSERT
	    result = sqlite3_step(stmt);
	    if (result != SQLITE_DONE) 
	    {
	       ofs << "Error inserting new data into preguntas table" <<  endl;
	      sqlite3_finalize(stmt);
	      ofs.close();
	      return result;
	    }

	    result = sqlite3_finalize(stmt);
	    if (result != SQLITE_OK) 
	    {
	       ofs << "Error finalizing statement (INSERT)" <<  endl;
	       ofs << sqlite3_errmsg(db) <<  endl;
	    }
	    ofs.close();
		return result;
	}
	else
	{
		 ofs << "La pregunta ya existe - si quieres cambiar algo, UPDATE" <<  endl;	
		 ofs.close();
		return 0;	
	}
}


//UPDATE:
int DBConnector::update_Jugador(jugador jugadorModificar)//Pasar el jugador completo
{
	ofstream ofs("./Data/loggers.txt", ios_base::app);
	if(Jugador_existe(jugadorModificar) == 1) //El jugador existe, lo podemos modificar
  	{ 
		sqlite3_stmt *stmt;
		char sql[] = "update Jugadores set PUNTUACION = ? where NICK = ?";
	    
	     string nick = jugadorModificar.getNick();
	    int puntuacion = jugadorModificar.getPuntuacion();
	    //Preparar el statement:
	    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
	    if (result != SQLITE_OK) 
	    {
	       ofs << "Error preparing statement (INSERT)" <<  endl;
	       ofs << sqlite3_errmsg(db) <<  endl;
	       ofs.close();
	      return result;
	    }

	    //Juntar los parámetros con el statement
	     //Le pasamos el puntuacion al statement
	    result = sqlite3_bind_int(stmt, 1, puntuacion);
	    if (result != SQLITE_OK)
	    {
	       ofs << "Error binding parameters" <<  endl;
	      sqlite3_finalize(stmt);
	       ofs << sqlite3_errmsg(db) <<  endl;
	       ofs.close();
	      return result;
	    }
	     //Le pasamos el nick al statement
	    result = sqlite3_bind_text(stmt, 2, nick.c_str(), nick.length(), SQLITE_TRANSIENT);

	    if (result != SQLITE_OK)
	    {
	       ofs << "Error binding parameters" <<  endl;
	      sqlite3_finalize(stmt);
	       ofs << sqlite3_errmsg(db) <<  endl;
	         ofs.close();
	      return result;
	    }

	     //Ejecutamos el UPDATE
	    result = sqlite3_step(stmt);
	    if (result != SQLITE_DONE) 
	    {
	       ofs << "Error inserting new data into Jufgadores table" <<  endl;
	      sqlite3_finalize(stmt);
	        ofs.close();
	      return result;
	    }

	    result = sqlite3_finalize(stmt);
	    if (result != SQLITE_OK) 
	    {
	       ofs << "Error finalizing statement (UPDATE)" <<  endl;
	       ofs << sqlite3_errmsg(db) <<  endl;
	    }
	      ofs.close();
		return result;
	}
	else
	{
		 ofs.close();
		return 0;
	}
}

int DBConnector::update_Pregunta(preguntas_respuestas* preguntaModificar)
{
	ofstream ofs("./Data/loggers.txt", ios_base::app);
	if(Pregunta_existe(preguntaModificar) == 1) 
  	{ 
		sqlite3_stmt *stmt;
		char sql[] = "update Preguntas set PREGUNTA = ?, R1 = ?, R2 = ?, R3 = ?, R4 = ?, DIFICULTAD = ? where ID = ?";
	  	int result;
		
	   if (preguntaModificar->getDificultad()=="###")
	    {
	    	prdificil* p = dynamic_cast<prdificil*>(preguntaModificar);

	    	 string pregunta = (*p).getPregunta();
		     string r1 = (*p).getRespuesta1();
		     string r2 = (*p).getRespuesta2();
		     string r3 = (*p).getRespuesta3();
		     string r4 = (*p).getRespuesta4();
		     string dificultad = (*p).getDificultad();
		     int ID = (*p).getID();

		     //Preparar el statement:
	   	//ATRIBUTOS QUE TENDRÁN TODAS:

	    	//ID

	    	int result = sqlite3_bind_int(stmt, 7, ID);
	    	if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		        ofs.close();
		      return result;
		    }

		    //PREGUNTA
	
		    result = sqlite3_bind_text(stmt, 1, pregunta.c_str(), pregunta.length(), SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		        ofs.close();
		      return result;
		    }

		    //R1:
	
		    result = sqlite3_bind_text(stmt, 2, r1.c_str(), r1.length(), SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		        ofs.close();
		      return result;
		    }

		    //R2:

		    result = sqlite3_bind_text(stmt, 3, r2.c_str(), r2.length(), SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		        ofs.close();
		      return result;
		    }

		    //SOLO EN MEDIA O DIFÍCIL
		    //R3:
		    
			    result = sqlite3_bind_text(stmt, 4, r3.c_str(), r3.length(), SQLITE_TRANSIENT);
			    if (result != SQLITE_OK)
			    {
			       ofs << "Error binding parameters" <<  endl;
			       ofs << sqlite3_errmsg(db) <<  endl;
			      sqlite3_finalize(stmt);
			        ofs.close();
			      return result;
			    }		   

		    //SOLO EN DIFÍCIL
		    //R4:
		   
			    //Es dificil
			    result = sqlite3_bind_text(stmt, 5, r4.c_str(), r4.length(), SQLITE_TRANSIENT);
			    if (result != SQLITE_OK)
			    {
			       ofs << "Error binding parameters" <<  endl;
			       ofs << sqlite3_errmsg(db) <<  endl;
			      sqlite3_finalize(stmt);
			        ofs.close();
			      return result;
			    }

		    //DIFICULTAD
	
		    result = sqlite3_bind_text(stmt, 6, dificultad.c_str(), dificultad.length(), SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		        ofs.close();
		      return result;
		    }

		    //ID

	    	result = sqlite3_bind_int(stmt, 7, ID);
	    	if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		        ofs.close();
		      return result;
		    }

	    }
	    else if(preguntaModificar->getDificultad()=="##")
	    {
	    	 prmedio* p = dynamic_cast<prmedio*>(preguntaModificar);
	    	 string pregunta = (*p).getPregunta();
		     string r1 = (*p).getRespuesta1();
		     string r2 = (*p).getRespuesta2();
		     string r3 = (*p).getRespuesta3();
		     string dificultad = (*p).getDificultad();
		     int ID = (*p).getID();

		     //Preparar el statement:
	   	//ATRIBUTOS QUE TENDRÁN TODAS:

	    	//ID

	    	result = sqlite3_bind_int(stmt, 7, ID);
	    	if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		        ofs.close();
		      return result;
		    }

		    //PREGUNTA
	
		    result = sqlite3_bind_text(stmt, 1, pregunta.c_str(), pregunta.length(), SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		        ofs.close();
		      return result;
		    }

		    //R1:
	
		    result = sqlite3_bind_text(stmt, 2, r1.c_str(), r1.length(), SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		        ofs.close();
		      return result;
		    }

		    //R2:

		    result = sqlite3_bind_text(stmt, 3, r2.c_str(), r2.length(), SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		        ofs.close();
		      return result;
		    }

		    //SOLO EN MEDIA O DIFÍCIL
		    //R3:
			    result = sqlite3_bind_text(stmt, 4, r3.c_str(), r3.length(), SQLITE_TRANSIENT);
			    if (result != SQLITE_OK)
			    {
			       ofs << "Error binding parameters" <<  endl;
			       ofs << sqlite3_errmsg(db) <<  endl;
			      sqlite3_finalize(stmt);
			        ofs.close();
			      return result;
			    }
		   

		    //SOLO EN DIFÍCIL
		    //R4:
		    	// Es media o facil, no tiene R4
		    	//NULL
		    	result = sqlite3_bind_text(stmt, 5, NULL, 0, SQLITE_TRANSIENT);
			    if (result != SQLITE_OK)
			    {
			       ofs << "Error binding parameters" <<  endl;
			       ofs << sqlite3_errmsg(db) <<  endl;
			      sqlite3_finalize(stmt);
			        ofs.close();
			      return result;
			    }
		    

		    //DIFICULTAD
	
		    result = sqlite3_bind_text(stmt, 6, dificultad.c_str(), dificultad.length(), SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		        ofs.close();
		      return result;
		    }

		    //ID

	    	result = sqlite3_bind_int(stmt, 7, ID);
	    	if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		        ofs.close();
		      return result;
		    }

	    }
	    else
	    {
	    	prfacil* p = dynamic_cast<prfacil*>(preguntaModificar);

	    	 string pregunta = (*p).getPregunta();
		     string r1 = (*p).getRespuesta1();
		     string r2 = (*p).getRespuesta2();
		     string dificultad = (*p).getDificultad();
	    	 int ID = (*p).getID();

	    	 //Preparar el statement:
	   	//ATRIBUTOS QUE TENDRÁN TODAS:

	    	//ID

	    	result = sqlite3_bind_int(stmt, 7, ID);
	    	if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		        ofs.close();
		      return result;
		    }

		    //PREGUNTA
	
		    result = sqlite3_bind_text(stmt, 1, pregunta.c_str(), pregunta.length(), SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		        ofs.close();
		      return result;
		    }

		    //R1:
	
		    result = sqlite3_bind_text(stmt, 2, r1.c_str(), r1.length(), SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		        ofs.close();
		      return result;
		    }

		    //R2:

		    result = sqlite3_bind_text(stmt, 3, r2.c_str(), r2.length(), SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		        ofs.close();
		      return result;
		    }

		    //SOLO EN MEDIA O DIFÍCIL
		    //R3:
		    
		    	//NULL -> si es facil, le metemos NULL en r3
		    	result = sqlite3_bind_text(stmt, 5, NULL, 0, SQLITE_TRANSIENT);
			    if (result != SQLITE_OK)
			    {
			       ofs << "Error binding parameters" <<  endl;
			       ofs << sqlite3_errmsg(db) <<  endl;
			      sqlite3_finalize(stmt);
			        ofs.close();
			      return result;
			    }
		    

		    //SOLO EN DIFÍCIL
		    //R4:
		    	// Es media o facil, no tiene R4
		    	//NULL
		    	result = sqlite3_bind_text(stmt, 5, NULL, 0, SQLITE_TRANSIENT);
			    if (result != SQLITE_OK)
			    {
			       ofs << "Error binding parameters" <<  endl;
			       ofs << sqlite3_errmsg(db) <<  endl;
			      sqlite3_finalize(stmt);
			        ofs.close();
			      return result;
			    }
		    

		    //DIFICULTAD
	
		    result = sqlite3_bind_text(stmt, 6, dificultad.c_str(), dificultad.length(), SQLITE_TRANSIENT);
		    if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		        ofs.close();
		      return result;
		    }

		    //ID

	    	result = sqlite3_bind_int(stmt, 7, ID);
	    	if (result != SQLITE_OK)
		    {
		       ofs << "Error binding parameters" <<  endl;
		       ofs << sqlite3_errmsg(db) <<  endl;
		      sqlite3_finalize(stmt);
		        ofs.close();
		      return result;
		    }

	    }
	     //Ejecutamos el UPDATE
	    result = sqlite3_step(stmt);
	    if (result != SQLITE_DONE) 
	    {
	      ofs << "Error inserting new data into Preguntas table" <<  endl;
	      sqlite3_finalize(stmt);
	        ofs.close();
	      return result;
	    }

	    result = sqlite3_finalize(stmt);
	    if (result != SQLITE_OK) 
	    {
	       ofs << "Error finalizing statement (DELETE)" <<  endl;
	       ofs << sqlite3_errmsg(db) <<  endl;
	    }
	      ofs.close();
		return result;
	}
	else
	{
		  ofs.close();
		return 0;
	}
}

//DELETE:
int DBConnector::delete_Jugador(jugador jugadorBorrar)
{
	ofstream ofs("./Data/loggers.txt", ios_base::app);
	if(Jugador_existe(jugadorBorrar) == 1) //El jugador existe, lo podemos modificar
  	{ 
		sqlite3_stmt *stmt;
		char sql[] = "DELETE from Jugadores where NICK = ?";

		 string nick = jugadorBorrar.getNick();
	    
	    //Preparar el statement:
	    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
	    if (result != SQLITE_OK) 
	    {
	       ofs << "Error preparing statement (INSERT)" <<  endl;
	       ofs << sqlite3_errmsg(db) <<  endl;
	         ofs.close();
	      return result;
	    }

	    //Juntar los parámetros con el statement
	     //Le pasamos el nick al statement
	    result = sqlite3_bind_text(stmt, 1, nick.c_str(), nick.length(), SQLITE_TRANSIENT);
	    if (result != SQLITE_OK)
	    {
	      ofs << "Error binding parameters" <<  endl;
	      sqlite3_finalize(stmt);
	      ofs << sqlite3_errmsg(db) <<  endl;
	        ofs.close();
	      return result;
	    }

	     //Ejecutamos el DELETE
	    result = sqlite3_step(stmt);
	    if (result != SQLITE_DONE) 
	    {
	      ofs << "Error DELETING the player with nick " << nick <<  endl;
	      sqlite3_finalize(stmt);
	        ofs.close();
	      return result;
	    }

	    result = sqlite3_finalize(stmt);
	    if (result != SQLITE_OK) 
	    {
	       ofs << "Error finalizing statement (UPDATE)" <<  endl;
	       ofs << sqlite3_errmsg(db) <<  endl;
	    }
	      ofs.close();
		return result;
	}
	else
	{
		  ofs.close();
		return 0;
	}
}

int DBConnector::delete_Pregunta(preguntas_respuestas* preguntaBorrar)
{
	ofstream ofs("./Data/loggers.txt", ios_base::app);
	if(Pregunta_existe(preguntaBorrar) == 1) 
  	{ 
		sqlite3_stmt *stmt;
		char sql[] = "DELETE from Preguntas where ID = ?";

		int ID = preguntaBorrar->getID();
	    
	    //Preparar el statement:
	    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
	    if (result != SQLITE_OK) 
	    {
	       ofs << "Error preparing statement (DELETE)" <<  endl;
	       ofs << sqlite3_errmsg(db) <<  endl;
	         ofs.close();
	      return result;
	    }

	    //Juntar los parámetros con el statement
	    result = sqlite3_bind_int(stmt, 1, ID);
	    if (result != SQLITE_OK)
	    {
	      ofs << "Error binding parameters" <<  endl;
	      sqlite3_finalize(stmt);
	       ofs << sqlite3_errmsg(db) <<  endl;
	         ofs.close();
	      return result;
	    }

	     //Ejecutamos el DELETE
	    result = sqlite3_step(stmt);
	    if (result != SQLITE_DONE) 
	    {
	      ofs << "Error DELETING the question with ID " << ID <<  endl;
	      sqlite3_finalize(stmt);
	      return result;
	    }

	    result = sqlite3_finalize(stmt);
	    if (result != SQLITE_OK) 
	    {
	       ofs << "Error finalizing statement (DELETE)" <<  endl;
	       ofs << sqlite3_errmsg(db) <<  endl;
	    }
	      ofs.close();
		return result;
	}
	else
	{
		  ofs.close();
		return 0;
	}
}

//SELECT
int DBConnector::leer_Jugadores(vector <jugador>& listaTodosJugadores)
{
	ofstream ofs("./Data/loggers.txt", ios_base::app);
	//int cont = 0;
	sqlite3_stmt *stmt; 
	char sql[] = "select NICK, PUNTUACION from Jugadores";
   
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
    if (result != SQLITE_OK)
    {
    	  ofs.close();
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
      	jugador jug (nick, puntuacion);
    	
    	listaTodosJugadores.push_back (jug);
      	// listaTodosJugadores[cont] = jugador;
      	// cont++;
      }
    } while (result == SQLITE_ROW);

    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) 
    {
    	  ofs.close();
      return result;
    }
      ofs.close();
    return SQLITE_OK;
}

int DBConnector::leer_Preguntas(vector <preguntas_respuestas*>& listaTodasPreguntas)
{
	ofstream ofs("./Data/loggers.txt", ios_base::app);
	int cont = 0;
	sqlite3_stmt *stmt; 
	char sql[] = "select ID, PREGUNTA, R1, R2, R3, R4, DIFICULTAD from Preguntas";
   
    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;
    if (result != SQLITE_OK)
    {
       ofs << "Error preparing statement (SELECT)" <<  endl;      
       ofs << sqlite3_errmsg(db) <<  endl;
         ofs.close();
      return result;
    }
 	//Variables a recoger
 	int ID = 0;
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
      	// preguntas_respuestas p;

      	ID = sqlite3_column_int(stmt, 0);

       	strcpy(pregunta, (char*)sqlite3_column_text(stmt, 1));   
       	strcpy(r1, (char*)sqlite3_column_text(stmt, 2));
       	strcpy(r2, (char*)sqlite3_column_text(stmt, 3));
      	//Leemos dificultad antes que R3 y R4 ya que depende de este atributo si tiene o no estos dos
      	strcpy(dificultad, (char*)sqlite3_column_text(stmt, 6));

      	if(strcmp(dificultad, "###") == 0)
      	{
      		//Es dificil
      		strcpy(r3, (char*)sqlite3_column_text(stmt, 4));
       		strcpy(r4, (char*)sqlite3_column_text(stmt, 5));

       		//Creamos una Pregunta_respuestas con estos atributos:
      		prdificil* p = new prdificil(pregunta,r1, r2, r3, r4, ID, true);//el ultimo es true para no darle el ID
      		listaTodasPreguntas.push_back(p);
      		
      	}
      	else if(strcmp(dificultad, "##") == 0)
      	{
      		//Es media
      		strcpy(r3, (char*)sqlite3_column_text(stmt, 4));
      		prmedio* p = new prmedio (pregunta,r1, r2, r3, ID, true);//el ultimo es true para no darle el ID
      	 	listaTodasPreguntas.push_back(p);

      	}
      	else
      	{
      		prfacil* p = new prfacil(pregunta,r1, r2, ID, true);//el ultimo es true para no darle el ID
      		p->setID (ID);
           	listaTodasPreguntas.push_back(p);

      	}
      	// listaTodasPreguntas[cont] = p;
      	// cont++;  
      	// listaTodasPreguntas.push_back(p);
      }
    } while (result == SQLITE_ROW);

    result = sqlite3_finalize(stmt);
    if (result != SQLITE_OK) 
    {
       ofs << "Error finalizing statement (SELECT)" <<  endl;
       ofs << sqlite3_errmsg(db) <<  endl;
         ofs.close();
      return result;
    }
      ofs.close();
    return SQLITE_OK;
}


//DROP TABLE:
int DBConnector::drop_Jugadores ()
{
	ofstream ofs("./Data/loggers.txt", ios_base::app);
	sqlite3_stmt *stmt;
	char sql[] = "DROP TABLE if exists Jugadores";
    
    // //Preparar el statement:
    // int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
    // if (result != SQLITE_OK) 
    // {
    //    ofs << "Error preparing statement (INSERT)" <<  endl;
    //    ofs << sqlite3_errmsg(db) <<  endl;
    //    ofs.close();
    //   return result;
    // }

    //  //Ejecutamos el DROP
    int result = sqlite3_exec(db, sql, NULL, NULL, NULL);
    if (result != SQLITE_DONE) 
    {
       ofs << "Error DROPING Jugadores"<<  endl;
      sqlite3_finalize(stmt);
      return result;
    }
 //Esto solo habrá que hacerlo si hacemos prepare statement
    // result = sqlite3_finalize(stmt);
    // if (result != SQLITE_OK) 
    // {
    //    cout << "Error finalizing statement (UPDATE)" <<  endl;
    //    cout << sqlite3_errmsg(db) <<  endl;
    // }
	return result;
}

int DBConnector::drop_Preguntas ()
{
	ofstream ofs("./Data/loggers.txt", ios_base::app);
	sqlite3_stmt *stmt;
	char sql[] = "DROP TABLE if exists Preguntas";
    
    //Preparar el statement:
    // int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL) ;
    // if (result != SQLITE_OK) 
    // {
    //    cout << "Error preparing statement" <<  endl;
    //    cout << sqlite3_errmsg(db) <<  endl;
    //   return result;
    // }

    int result = sqlite3_exec(db, sql, NULL, NULL, NULL);
    if (result != SQLITE_DONE) 
    {
      ofs << "Error DROPING Preguntas"<<  endl;
      sqlite3_finalize(stmt);
      ofs.close();
      return result;
    }

    //Esto solo habrá que hacerlo si hacemos prepare statement
    // result = sqlite3_finalize(stmt);
    // if (result != SQLITE_OK) 
    // {
    //    cout << "Error finalizing statement " <<  endl;
    //    cout << sqlite3_errmsg(db) <<  endl;
    // }
	return result;
}