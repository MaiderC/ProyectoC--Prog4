#include "utilidades.h"
#include "../LN/jugador.h"
#include "../LN/operaciones.h"
#include "../LD/DBConnector.h"
#include "../LN/preguntas_respuestas.h"
#include "../LN/prfacil.h"
#include "../LN/prmedio.h"
#include "../LN/prdificil.h"
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;
using namespace utilidades;
using namespace operaciones;

//Declaracion de MeTODOS
void menuAdmin(DBConnector BD);
void menuJugador(DBConnector BD);
void individual(DBConnector BD);
void multijugador(DBConnector BD);
void ranking(DBConnector BD);
void acabar(DBConnector BD);
void RealizarPreguntasMultijugador(vector<jugador> multijugadores, int cantPreg);
int elegirDificultad();

vector<preguntas_respuestas*> preguntasSalidas; // Lista de las preguntas que ya han salido en la ejecucion del juego
vector<preguntas_respuestas*> listaTodasPreguntas; // Lista de todas las preguntas de la base de datos
vector<jugador> listaTodosJugadores; // Lista de todos los jugadores de la base de datos
jugador jugadorPrincipal; // Jugador que inicia la partida


int main(int argc, char** argv)
{
	DBConnector BD("./Data/BD.sqlite");
	BD.create_table_Jugadores();
	BD.create_table_Preguntas();
	BD.leer_Jugadores(listaTodosJugadores);

  	BD.leer_Preguntas(listaTodasPreguntas);
  	siguienteID(listaTodasPreguntas);

  	if(argc == 2)
  	{
		if (strcmp(argv[1],"admin")==0)
		{
			menuAdmin(BD);
		}
  	}
  	else //es un jugador
  	{
  		if(listaTodasPreguntas.size() == 0)
  		{
  			mostrarMensaje("No hay preguntas en el sistema :(");
  		}
  		else
  		{
	  		//Antes de mostrar el menu, como es la primera vez, hacemos que se identifique
	  		string nick;
	  		mostrarMensaje("Introduce tu NICK:");
	  		recogerString(nick);

	 		jugador jugadorPrincipal (nick, 0);

	 		mostrarMensaje("Hola "); mostrarMensaje(nick); mostrarMensaje("!");
	    	menuJugador(BD);
		}
  	}

  	return 0;
}

 void menuAdmin(DBConnector BD)
 {
 	mostrarMensaje("Hola, administrador");
	
	int opcionMenu = 0;
	int opcionSeguir;
	int opcionEliminar;

 	do
 	{

	 	 mostrarMensaje("Estas son las acciones que puedes realizar:");
	 	 mostrarMensaje("\t1- Insertar preguntas faciles");
	 	 mostrarMensaje("\t2- Insertar preguntas de dificultad media");
	 	 mostrarMensaje("\t3- Insertar preguntas dificiles");
	 	 mostrarMensaje("\t4- Borrar preguntas");
	 	 mostrarMensaje("\t5- Salir");
	 	 mostrarMensaje("Inserta el numero de la accion que deseas realizar: ");

	  	recogerInt(opcionMenu);

	  	while(opcionMenu < 1 || opcionMenu > 5)
	 	{
	 	 	mostrarMensaje("\nLa opcion introducida no es valida. Por favor, intentalo de nuevo:  ");
	 	 	recogerInt(opcionMenu);
	 	}

	  	switch(opcionMenu)
	  	{
	  		case 1:
	  			do
	  			{
	  				opcionSeguir = 0;
		  			int cant_p = 0; //cantidad de preguntas que va a insertar el administrador

					mostrarMensaje("Indica la cantidad de preguntas que deseas introducir: ");
		    		recogerInt(cant_p); //en recoger int, añadir mensajes de error si no es un int
		   
				    while(cant_p <= 0)
				    {
				    	mostrarMensaje("El numero de preguntas debe ser superior a 0. Por favor, indica de nuevo la cantidad: ");
				    	recogerInt(cant_p);
				    }

				    prfacil* preg_r;

				    for (int i = 0; i < cant_p; i++)
				    {
				    	preg_r = new prfacil();
				    	recogerPregunta(preg_r);
				    	BD.insert_Pregunta(preg_r);
				    	listaTodasPreguntas.push_back(preg_r);
				    }

				    mostrarMensaje("¿Quieres seguir introduciendo preguntas?");
			 		mostrarMensaje("1.- Si");
			 		mostrarMensaje("2.- No");
			 		recogerInt(opcionSeguir);

				}
				while(opcionSeguir != 2);
				break;

			case 2:
	  			do
	  			{
	  				opcionSeguir = 0;
		  			int cant_p = 0; //cantidad de preguntas que va a insertar el administrador

					mostrarMensaje("Indica la cantidad de preguntas que deseas introducir: ");
		    		recogerInt(cant_p); //en recoger int, añadir mensajes de error si no es un int
		   
				    while(cant_p <= 0)
				    {
				    	mostrarMensaje("El numero de preguntas debe ser superior a 0. Por favor, indica de nuevo la cantidad: ");
				    	recogerInt(cant_p);
				    }

				    prmedio* preg_r;

				    for (int i = 0; i < cant_p; i++)
				    {
				    	preg_r = new prmedio();
				    	recogerPregunta(preg_r);
				    	BD.insert_Pregunta(preg_r);
				    	listaTodasPreguntas.push_back(preg_r);
				    }

				    mostrarMensaje("¿Quieres seguir introduciendo preguntas?");
			 		mostrarMensaje("1.- Si");
			 		mostrarMensaje("2.- No");
			 		recogerInt(opcionSeguir);

				}while(opcionSeguir != 2);
				break;

			case 3:
	  			do
	  			{
	  				opcionSeguir = 0;
		  			int cant_p = 0; //cantidad de preguntas que va a insertar el administrador

					mostrarMensaje("Indica la cantidad de preguntas que deseas introducir: ");
		    		recogerInt(cant_p); //en recoger int, añadir mensajes de error si no es un int
		   
				    while(cant_p <= 0)
				    {
				    	mostrarMensaje("El numero de preguntas debe ser superior a 0. Por favor, indica de nuevo la cantidad: ");
				    	recogerInt(cant_p);
				    }

				    prdificil* preg_r;

				    for (int i = 0; i < cant_p; i++)
				    {
				    	preg_r = new prdificil();
				    	recogerPregunta(preg_r);
				    	BD.insert_Pregunta(preg_r);
				    	listaTodasPreguntas.push_back(preg_r);
				    }

				    mostrarMensaje("¿Quieres seguir introduciendo preguntas?");
			 		mostrarMensaje("1.- Si");
			 		mostrarMensaje("2.- No");
			 		recogerInt(opcionSeguir);

				}while(opcionSeguir != 2);
				break;

			case 4:

				
					opcionEliminar = 0;
				do
				{
					if(listaTodasPreguntas.size() == 0)
			  		{
			  			mostrarMensaje("No hay preguntas en el sistema :(");
			  		} else
			  		{
						mostrarTodasPreguntas(listaTodasPreguntas);
						mostrarMensaje("¿Que pregunta quieres eliminar?");
						recogerInt(opcionEliminar);

						BD.delete_Pregunta(listaTodasPreguntas[opcionEliminar-1]);
						listaTodasPreguntas.erase(listaTodasPreguntas.begin() + opcionEliminar-1);

						mostrarMensaje("¿Quieres seguir eliminando preguntas?");
						mostrarMensaje("1.- Si");
						mostrarMensaje("Inserta 1 para Si, cualquier otro caracter para No.");
						recogerInt(opcionEliminar);
					}
				}while(opcionEliminar == 1 );
				break;

			case 5:
				
					mostrarMensaje("Modo administrador finalizado.");
					acabar(BD);
					break;

			default:
				break;
	  	}
	}
	while(opcionMenu != 5);
 }

 void menuJugador(DBConnector BD)
 {
 	int opcionMenu;
	
 	 mostrarMensaje("\n\n----MENU----\n"); 
 	 mostrarMensaje("Por favor, elije una de las siguientes opciones:");
 	 mostrarMensaje("\t 1.- Jugar partida individual");
 	 mostrarMensaje("\t 2.- Jugar partida multijugador");
 	 mostrarMensaje("\t 3.- Ver ranking");
 	 mostrarMensaje("\t 4.- Salir");
 	 mostrarMensaje("Indica el numero de la opcion que quieres elegir: ");

  	recogerInt(opcionMenu);

	while(!(opcionMenu>0 && opcionMenu<5))
  	{
  		mostrarMensaje("Opcion no valida. Por favor, indica el numero de la opcion que quieres elegir: "); 
  		recogerInt(opcionMenu);
  	}

  	switch(opcionMenu)
  	{
  		case 1: 
	  		mostrarMensaje("Has elegido la opcion numero 1: JUGAR PARTIDA INDIVIDUAL");
	  		individual(BD);
	  		break;

  		case 2:
	  		mostrarMensaje("Has elegido la opcion numero 2: JUGAR PARTIDA MULTIJUGADOR");
	  		multijugador(BD);
	  		break;

  		case 3:
	  		mostrarMensaje("Has elegido la opcion numero 3: VER RANKING"); 
	  		ranking(BD);
	  		break;

  		case 4:
	  		mostrarMensaje("Gracias por jugar ¡Vuelve pronto!"); 
	  		acabar(BD);
	  		exit(0);
	  		break;

  		default:
  			break;
  	} 
 }

 int elegirDificultad()
 {
 	int opcionDificultad;

 	mostrarMensaje("El juego permite jugar con diferentes niveles de dificultad:");
 	mostrarMensaje("\t1.- Facil");
 	mostrarMensaje("\t2.- Medio");
 	mostrarMensaje("\t3.- Dificil");
 	mostrarMensaje("\t4.- Mixto");

 	do
 	{
 		mostrarMensaje("Elije con que nivel de dificultad quieres jugar (opciones validas: 1, 2, 3 o 4): ");
 		recogerInt(opcionDificultad);
 	}
 	while(opcionDificultad < 1 || opcionDificultad > 4);

 	return opcionDificultad;
 }

 void individual(DBConnector BD)
 {
 	int opcionDificultad;
 	int cant_preguntas;
 	int max_preguntas; //Leer las preguntas, meterlas en un array y contar la cantidad de posiciones de ese array
 	vector<preguntas_respuestas*> PreguntasSeleccionadas;
 	preguntas_respuestas* pregunta;
 	int random; //variable en la que guardaremos el numero aleatorio para elegir una pregunta aleatoria
 	int repetida = 0; //Variable para ver si en cada momento la pregunta elegida aleatoriamente es i no alguna que ya ha salido
 	int cantidadPreguntasValida = 0; //Variable para ver si se ha pasado o no con la cantidad de preguntas
 	int cont = 0;
 	int respValida = -1;
 	int respCorrecta;
 	char respuesta;

 	int opcionRepetir; //Para la eleccion del final: repetir o no la partida

 	opcionDificultad = elegirDificultad();

 	if(opcionDificultad == 1)
 	{
 		for(int i = 0; i < listaTodasPreguntas.size(); i++)
 		{
 			if(listaTodasPreguntas[i]->getDificultad() == "#")
 				PreguntasSeleccionadas.push_back(listaTodasPreguntas[i]);
 		}
 	}

 	if(opcionDificultad == 2)
 	{
 		for(int i = 0; i < listaTodasPreguntas.size(); i++)
 		{
 			if(listaTodasPreguntas[i]->getDificultad() == "##")
 				PreguntasSeleccionadas.push_back(listaTodasPreguntas[i]);
 		}
 	}

 	if(opcionDificultad == 3)
 	{
 		for(int i = 0; i < listaTodasPreguntas.size(); i++)
 		{
 			if(listaTodasPreguntas[i]->getDificultad() == "###")
 				PreguntasSeleccionadas.push_back(listaTodasPreguntas[i]);
 		}
 	}

 	if(opcionDificultad == 4)
 	{
 		for (int i = 0; i < listaTodasPreguntas.size(); i++)
 		{
 			if(listaTodasPreguntas[i]->getDificultad() == "#")
 			{
 				prfacil* preguntaAux = dynamic_cast<prfacil*> (listaTodasPreguntas[i]);
 				prfacil* preguntaCopiar = new prfacil(preguntaAux->getPregunta(), preguntaAux->getRespuesta1(), preguntaAux->getRespuesta2(), preguntaAux->getID(), true);
 				PreguntasSeleccionadas.push_back(preguntaCopiar);

 			} else if(listaTodasPreguntas[i]->getDificultad() == "##")
 			{
 				prmedio* preguntaAux = dynamic_cast<prmedio*> (listaTodasPreguntas[i]);
 				prmedio* preguntaCopiar = new prmedio(preguntaAux->getPregunta(), preguntaAux->getRespuesta1(), preguntaAux->getRespuesta2(), preguntaAux->getRespuesta3(), preguntaAux->getID(), true);
 				PreguntasSeleccionadas.push_back(preguntaCopiar);

 			} else if(listaTodasPreguntas[i]->getDificultad() == "###")
 			{
 				prdificil* preguntaAux = dynamic_cast<prdificil*> (listaTodasPreguntas[i]);
 				prdificil* preguntaCopiar = new prdificil(preguntaAux->getPregunta(), preguntaAux->getRespuesta1(), preguntaAux->getRespuesta2(), preguntaAux->getRespuesta3(), preguntaAux->getRespuesta4(),preguntaAux->getID(), true);
 				PreguntasSeleccionadas.push_back(preguntaCopiar);
 			}
 		}
 	}

 	mostrarMensaje("¿Cuantas preguntas deseas que se te realicen?");
 	recogerInt(cant_preguntas);

 	cantidadPreguntasValida = maxPreguntas(cant_preguntas, PreguntasSeleccionadas.size());
 	
 	while(cant_preguntas<0 || cantidadPreguntasValida == 0)
 	{
		mostrarMensaje("El numero de preguntas no es valido, debe ser mayor que 0 y menor o igual al total de preguntas disponibles.");
		mostrarMensaje("Numero de preguntas disponibles:");
		mostrarInt(PreguntasSeleccionadas.size());

		mostrarMensaje("Por favor, introduce otro numero:");
 		recogerInt(cant_preguntas);
 		cantidadPreguntasValida = maxPreguntas(cant_preguntas, PreguntasSeleccionadas.size());
 	}

 	for(int i = 0; i < cant_preguntas; i++)
 	{
 		 pregunta = generarPregunta(PreguntasSeleccionadas, preguntasSalidas);
		 

		 if((*pregunta).getDificultad() == "#")
		 {
		 	prfacil* preguntaAux = dynamic_cast<prfacil*> (pregunta);
		 	mostrarPregunta(*preguntaAux);
			respuesta = recogerOpcionRespuesta(respValida, (*pregunta).getDificultad());

		 	while(respValida == -1)
			{
		 		respuesta = recogerOpcionRespuesta(respValida, preguntaAux->getDificultad());
		 	}

			switch (respuesta)
			{
				case 'a':
					respCorrecta = comprobarRespuesta(preguntaAux->getRespuesta1());
					break;

				case 'b':
					respCorrecta = comprobarRespuesta(preguntaAux->getRespuesta2());
					break;
			}
		 } 

		 else if((*pregunta).getDificultad() == "##")
		 {
		 	prmedio* preguntaAux = dynamic_cast<prmedio*> (pregunta);

			mostrarPregunta(*preguntaAux);
			respuesta = recogerOpcionRespuesta(respValida, (*pregunta).getDificultad());

		 	while(respValida == -1)
			{
		 		respuesta = recogerOpcionRespuesta(respValida, preguntaAux->getDificultad());
		 	}

			switch (respuesta)
			{
				case 'a':
					respCorrecta = comprobarRespuesta(preguntaAux->getRespuesta1());
					break;

				case 'b':
					respCorrecta = comprobarRespuesta(preguntaAux->getRespuesta2());
					break;

				case 'c':
					respCorrecta = comprobarRespuesta(preguntaAux->getRespuesta3());
					break;
			}
		 } 

		 else if((*pregunta).getDificultad() == "###")
		 {
		 	prdificil* preguntaAux = dynamic_cast<prdificil*> (pregunta);

		 	mostrarPregunta(*preguntaAux);
			respuesta = recogerOpcionRespuesta(respValida, (*pregunta).getDificultad());

		 	while(respValida == -1)
			{
		 		respuesta = recogerOpcionRespuesta(respValida, preguntaAux->getDificultad());
		 	}

			switch (respuesta)
			{
				case 'a':
					respCorrecta = comprobarRespuesta(preguntaAux->getRespuesta1());
					break;

				case 'b':
					respCorrecta = comprobarRespuesta(preguntaAux->getRespuesta2());
					break;

				case 'c':
					respCorrecta = comprobarRespuesta(preguntaAux->getRespuesta3());
					break;

				case 'd':
					respCorrecta = comprobarRespuesta(preguntaAux->getRespuesta4());
			}
		 }
				
		 if(respCorrecta == 1)
		 {
		 	mostrarMensaje("Respuesta correcta");
		 	(*pregunta).sumarPunto(jugadorPrincipal);
		 }
		 else
		 {
		 	mostrarMensaje("Respuesta incorrecta");
		 }
	 }

	 mostrarMensaje("---Fin de la partida---");
	 mostrarMensaje("Deseas volver a jugar o regresar al menu?");
	 mostrarMensaje("1.- Volver a jugar");
	 mostrarMensaje("2.- Volver al menu");
	 mostrarMensaje("Introduce la opcion deseada:");
	 recogerInt(opcionRepetir);

	 listaTodosJugadores = actualizarPuntuacion(listaTodosJugadores, jugadorPrincipal);
	 jugadorPrincipal.setPuntuacion(0);

	 while(opcionRepetir != 1 && opcionRepetir != 2)
	 {
	 	 mostrarMensaje("\nLa opcion introducida no es valida. Por favor, intentalo de nuevo:  ");
	 	 recogerInt(opcionRepetir);
	 }

	 if(opcionRepetir == 1)
	 {
	 	individual(BD);
	 }
	 else
	 {
	 	menuJugador(BD);
	 }
 }

void multijugador(DBConnector BD)
 {
 	int opcionDificultad;
 	int cantJugadores;
 	int cantPreg;
 	vector<preguntas_respuestas*> PreguntasSeleccionadas;
 	vector<jugador> multijugadores;
 	vector<jugador> empatados;
 	int cantidadPreguntasValida;
 	int puntMaxima;
 	int opcionDesempatar;
 	int opcionRepetir;

 	string NickAux;

 	opcionDificultad = elegirDificultad();

 	if(opcionDificultad == 1)
 	{
 		for(int i = 0; i < listaTodasPreguntas.size(); i++)
 		{
 			if(listaTodasPreguntas[i]->getDificultad() == "#")
 				PreguntasSeleccionadas.push_back(listaTodasPreguntas[i]);
 		}
 	}

 	if(opcionDificultad == 2)
 	{
 		for(int i = 0; i < listaTodasPreguntas.size(); i++)
 		{
 			if(listaTodasPreguntas[i]->getDificultad() == "##")
 				PreguntasSeleccionadas.push_back(listaTodasPreguntas[i]);
 		}
 	}

 	if(opcionDificultad == 3)
 	{
 		for(int i = 0; i < listaTodasPreguntas.size(); i++)
 		{
 			if(listaTodasPreguntas[i]->getDificultad() == "###")
 				PreguntasSeleccionadas.push_back(listaTodasPreguntas[i]);
 		}
 	}

 	if(opcionDificultad == 4)
 	{
 		for (int i = 0; i < listaTodasPreguntas.size(); i++)
 		{
 			if(listaTodasPreguntas[i]->getDificultad() == "#")
 			{
 				prfacil* preguntaAux = dynamic_cast<prfacil*> (listaTodasPreguntas[i]);
 				prfacil* preguntaCopiar = new prfacil(preguntaAux->getPregunta(), preguntaAux->getRespuesta1(), preguntaAux->getRespuesta2(), preguntaAux->getID(), true);
 				PreguntasSeleccionadas.push_back(preguntaCopiar);

 			} else if(listaTodasPreguntas[i]->getDificultad() == "##")
 			{
 				prmedio* preguntaAux = dynamic_cast<prmedio*> (listaTodasPreguntas[i]);
 				prmedio* preguntaCopiar = new prmedio(preguntaAux->getPregunta(), preguntaAux->getRespuesta1(), preguntaAux->getRespuesta2(), preguntaAux->getRespuesta3(), preguntaAux->getID(), true);
 				PreguntasSeleccionadas.push_back(preguntaCopiar);

 			} else if(listaTodasPreguntas[i]->getDificultad() == "###")
 			{
 				prdificil* preguntaAux = dynamic_cast<prdificil*> (listaTodasPreguntas[i]);
 				prdificil* preguntaCopiar = new prdificil(preguntaAux->getPregunta(), preguntaAux->getRespuesta1(), preguntaAux->getRespuesta2(), preguntaAux->getRespuesta3(), preguntaAux->getRespuesta4(),preguntaAux->getID(), true);
 				PreguntasSeleccionadas.push_back(preguntaCopiar);
 			}
 		}
 	}

	mostrarMensaje("¿Cuantos jugadores van a jugar?");
 	recogerInt(cantJugadores);

 	cantidadPreguntasValida = maxPreguntas(cantJugadores, PreguntasSeleccionadas.size());
 	while(cantJugadores<2 ||  cantidadPreguntasValida == 0)
 	{
 		mostrarMensaje("El numero introducido es incorrecto (o por ser inferior a 2 o por exceder la cantidad de preguntas disponibles. \n");
 		mostrarMensaje("\nPor favor, intoduce cuantos jugadores van a jugar: \t");
 		recogerInt(cantJugadores);
 		cantidadPreguntasValida = maxPreguntas(cantJugadores, PreguntasSeleccionadas.size());
 	}

 	//El primer jugador es el actual 
 	multijugadores.push_back(jugadorPrincipal);
 	multijugadores[0].setPuntuacion(0);

 	mostrarMensaje("Introduce los nombres de los jugadores contra los que vas a jugar:");
 	for (int i = 1; i < multijugadores.size(); i++)
 	{
 		string a;
 		a = "J";
 		a += to_string(i) + ": ";
 		mostrarMensaje(a); //Para que aparezca como JX: 
 		mostrarMensaje("Introduce el NICK:");
 		recogerString(NickAux);
 		jugador* aux = new jugador(NickAux,0);
 		multijugadores.push_back(aux);
 	}

 	mostrarMensaje("¿Cuantas preguntas deseas que se le realicen a cada jugador?\t");
 	recogerInt(cantPreg);
 	cantidadPreguntasValida = maxPreguntas(multijugadores.size()*cantPreg, PreguntasSeleccionadas.size());

	while(cantPreg<1 || cantidadPreguntasValida == 0)
 	{
 		mostrarMensaje("El numero introducido es incorrecto (o por ser inferior a 1 o por exceder la cantidad de preguntas disponibles para la cantidad de jugadores elegida.");
 		mostrarMensaje("Por favor, intoduce cuantas preguntas deseas que se le realicen a cada jugador:");
 		recogerInt(cantPreg);
 		cantidadPreguntasValida = maxPreguntas(multijugadores.size()*cantPreg, PreguntasSeleccionadas.size());
 	}

 	RealizarPreguntasMultijugador(multijugadores, cantPreg);
 	
	 do
	 {
	 	empatados.clear();
	 	puntMaxima = maxPuntuacion(multijugadores);

	 	for(int i = 0; i < multijugadores.size(); i++)
	 	{
	 		if(multijugadores[i].getPuntuacion() == puntMaxima)
	 		{
	 			empatados.push_back(multijugadores[i]);
	 		}
	 	}

	 	if(empatados.size() > 1)
	 	{
	 		opcionDesempatar = mensajeEmpate(empatados);
	 		
	 		if(opcionDesempatar == 1)
	 		{
	 			//Realizamos una sola pregunta entre los jugadores que han empatado para ver si asi deshacen el empate
		 		RealizarPreguntasMultijugador(empatados, 1);
		 		int c = 0;
		 		for (int i = 0; i < multijugadores.size(); ++i)
		 		{
		 			if(multijugadores[i].getNick() == empatados[c].getNick())
		 			{
		 				multijugadores[i].setPuntuacion(empatados[c].getPuntuacion());
		 				c++;
		 			}
		 		}
	 		}
	 	}	 	
	 }
	 while(empatados.size() != 1);//No hay empate
	 //Si habia empate, ya se ha resuelto si asi se ha querido. 
	 //Si no se resolvio, se mostrara un mensaje de ganador por cada uno. Por lo tanto, lo hacemos en un for:
	 	for(int i = 0; i < multijugadores.size(); i++)
	 	{
	 		if(multijugadores[i].getPuntuacion() == puntMaxima)
	 		{
	 			mensajeGanador(multijugadores[i]);
	 		}
	 		listaTodosJugadores = actualizarPuntuacion(listaTodosJugadores, multijugadores);
	 	}

	 //Volver al menu o volver a jugar
	 mostrarMensaje("Fin de la partida.");
	 mostrarMensaje("¿Deseas volver a jugar o regresar al menu?");
	 mostrarMensaje("1.- Volver a jugar");
	 mostrarMensaje("2.- Volver al menu");
	 mostrarMensaje("Introduce la opcion deseada:  ");
	 recogerInt(opcionRepetir);

	 while(opcionRepetir != 1 && opcionRepetir != 2)
	 {
	 	 mostrarMensaje("\nLa opcion introducida no es valida. Por favor, intentalo de nuevo:  ");
	 	 recogerInt(opcionRepetir);
	 }

	 if(opcionRepetir == 1)
	 {
	 	multijugador(BD);
	 }
	 else
	 {
	 	menuJugador(BD);
	 }
 }

 void RealizarPreguntasMultijugador(vector<jugador> multijugadores, int cantPreg)
 {
 	int cont = 0;
 	int respValida = -1;
 	int random;//variable en la que guardaremos el numero aleatorio para elegir una pregunta aleatoria
 	int repetida = 0; //Variable para ver si en cada momento la pregunta elegida aleatoriamente es i no alguna que ya ha salido
 	preguntas_respuestas* pregunta;
 	char respuesta;
 	int respCorrecta;

 	int correcta = 0;

 	for(int i = 0; i < cantPreg; i++)
 	{
 		for(int j = 0; j < multijugadores.size(); j++)
 		{
 			string msj1 = "\nPregunta para el jugador #";
			string msj2 = to_string(j+1);
			msj1 = msj1 + msj2 + "->" + multijugadores[j].getNick();

 			mostrarMensaje(msj1);

 			//Preparar la pregunta aleatoria para el jugador
 			pregunta = generarPregunta(listaTodasPreguntas, preguntasSalidas);

			while(respValida == -1)
			{
				respuesta = recogerOpcionRespuesta(respValida, pregunta->getDificultad());
			}
			
		 if((*pregunta).getDificultad() == "#")
		 {
		 	prfacil* preguntaAux = dynamic_cast<prfacil*> (pregunta);

		 	mostrarPregunta(*preguntaAux);
			respuesta = recogerOpcionRespuesta(respValida, (*pregunta).getDificultad());
		 	
		 	while(respValida == -1)
			{
		 		respuesta = recogerOpcionRespuesta(respValida, preguntaAux->getDificultad());
		 	}

			switch (respuesta)
			{
				case 'a':
					respCorrecta = comprobarRespuesta(preguntaAux->getRespuesta1());
					break;

				case 'b':
					respCorrecta = comprobarRespuesta(preguntaAux->getRespuesta2());
					break;
			}
		 } 

		 else if((*pregunta).getDificultad() == "##")
		 {
		 	prmedio* preguntaAux = dynamic_cast<prmedio*> (pregunta);

		 	mostrarPregunta(*preguntaAux);
			respuesta = recogerOpcionRespuesta(respValida, (*pregunta).getDificultad());

		 	while(respValida == -1)
			{
		 		respuesta = recogerOpcionRespuesta(respValida, preguntaAux->getDificultad());
		 	}

			switch (respuesta)
			{
				case 'a':
					respCorrecta = comprobarRespuesta(preguntaAux->getRespuesta1());
					break;

				case 'b':
					respCorrecta = comprobarRespuesta(preguntaAux->getRespuesta2());
					break;

				case 'c':
					respCorrecta = comprobarRespuesta(preguntaAux->getRespuesta3());
					break;
			}
		 } 

		 else if((*pregunta).getDificultad() == "###")
		 {
		 	prdificil* preguntaAux = dynamic_cast<prdificil*> (pregunta);

		 	mostrarPregunta(*preguntaAux);
			respuesta = recogerOpcionRespuesta(respValida, (*pregunta).getDificultad());

		 	while(respValida == -1)
			{
		 		respuesta = recogerOpcionRespuesta(respValida, preguntaAux->getDificultad());
		 	}

			switch (respuesta)
			{
				case 'a':
					respCorrecta = comprobarRespuesta(preguntaAux->getRespuesta1());
					break;

				case 'b':
					respCorrecta = comprobarRespuesta(preguntaAux->getRespuesta2());
					break;

				case 'c':
					respCorrecta = comprobarRespuesta(preguntaAux->getRespuesta3());
					break;

				case 'd':
					respCorrecta = comprobarRespuesta(preguntaAux->getRespuesta4());
			}
		 }

			if(correcta == 1)
			{
			 	mostrarMensaje("Respuesta correcta");
			 	(*pregunta).sumarPunto(multijugadores[j]);
			}
			else
			{
			 	mostrarMensaje("Respuesta incorrecta");
			}
 		}
 	}

 }

  void ranking(DBConnector BD)
 {
 	ordenarJugadores(listaTodosJugadores);

 	mostrarMensaje("\nRANKING DE JUGADORES");
 	for(int i = 0; i < listaTodosJugadores.size(); i++)
 	{
 		mostrarMensaje((i+1) + ".-");
 		mostrarPuntuacion(listaTodosJugadores[i]);
 	}
 		mostrarMensaje("\n");
	 menuJugador(BD);
 }

 void acabar(DBConnector BD) //metodo para liberar recursos
 {
 	guardarJugadores(listaTodosJugadores, BD);
 }