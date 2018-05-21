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

//Declaracion de MeTODOS
void menuAdmin();
void menuJugador();
void individual();
void multijugador();
void ranking();
void acabar();
void RealizarPreguntasMultijugador(vector<jugador> multijugadores, int cantPreg)
int elegirDificultad();

vector<preguntas_respuestas> preguntasSalidas; // Lista de las preguntas que ya han salido en la ejecución del juego
vector<preguntas_respuestas> listaTodasPreguntas; // Lista de todas las preguntas de la base de datos
vector<jugador> listaTodosJugadores; // Lista de todos los jugadores de la base de datos
jugador jugadorPrincipal; // Jugador que inicia la partida

int main(int argc, char** argv)
{
	DBConnector BD = new DBConnector("./Data/BD.sqlite");
	BD.leer_Jugadores(listaTodosJugadores);

  	BD.leer_Preguntas(listaTodasPreguntas);

  	if(argc == 2)
  	{
		int admin;
		admin = (argv[1] == "admin");

		if (admin == 0)
		{
			main::menuAdmin();
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
	  		recogerNick(nick);

	 		jugadorPrincipal = new jugador(nick, 0);

	 		mostrarMensaje("Hola "); mostrarMensaje(nick); mostrarMensaje("!");
	    	main::menuJugador();
		}
  	}

  	return 0;
}

 void menuAdmin()
 {
 	mostrarMensaje("Hola, administrador");

 	do
 	{
	 	int opcionMenu = 0;
	 	int opcionSeguir;

	 	 mostrarMensaje("Estas son las acciones que puedes realizar:");
	 	 mostrarMensaje("\t1- Añadir preguntas fáciles");
	 	 mostrarMensaje("\t2- Añadir preguntas de dificultad media")
	 	 mostrarMensaje("\t3- Añadir preguntas dificiles");
	 	 mostrarMensaje("\t4- Borrar preguntas");
	 	 mostrarMensaje("\t5- Salir")
	 	 mostrarMensaje("Inserta el número de la acción que deseas realizar: ");

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

				    prfacil preg_r = new prfacil();

				    for (int i = 0; i < cant_p; i++)
				    {
				    	recogerPregunta(preg_r);
				    	BD.insert_Pregunta(preg_r);
				    }

				    mostrarMensaje("¿Quieres seguir introduciendo preguntas?");
			 		mostrarMensaje("1.- Si");
			 		mostrarMensaje("2.- No");
			 		recogerInt(opcionSeguir);

				}while(opcionSeguir != 2);
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

				    prmedio preg_r = new prmedio();

				    for (int i = 0; i < cant_p; i++)
				    {
				    	recogerPregunta(preg_r);
				    	DBConnector::insert_Pregunta(preg_r);
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

				    prdificil preg_r = new prdificil();

				    for (int i = 0; i < cant_p; i++)
				    {
				    	recogerPregunta(preg_r);
				    	DBConnector::insert_Pregunta(preg_r);
				    }

				    mostrarMensaje("¿Quieres seguir introduciendo preguntas?");
			 		mostrarMensaje("1.- Si");
			 		mostrarMensaje("2.- No");
			 		recogerInt(opcionSeguir);

				}while(opcionSeguir != 2);
				break;

			case 4:
				do
				{
					int opcionEliminar = 0;
					mostrarTodasPreguntas(listaTodasPreguntas);
					mostrarMensaje("¿Que pregunta quieres eliminar?");
					recogerInt(opcionEliminar);

					BD.delete_Pregunta(listaTodasPreguntas[opcionEliminar-1]);
					listaTodasPreguntas.erase(opcionEliminar-1);

					mostrarMensaje("¿Quieres seguir eliminando preguntas?");
			 		mostrarMensaje("1.- Si");
			 		mostrarMensaje("2.- No");
			 		recogerInt(opcionEliminar);
				}while(opcionEliminar != 2);
				break;

			case 5:
				mostrarMensaje("Modo administrador cerrado finalizado.");
				main::acaba();
				break;

			default:
				break;
	  	}
	}while(opcionMenu != 5)
 }

 void menuJugador()
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
	  		main::individual();
	  		break;

  		case 2:
	  		mostrarMensaje("Has elegido la opcion numero 2: JUGAR PARTIDA MULTIJUGADOR");
	  		main::multijugador();
	  		break;

  		case 3:
	  		mostrarMensaje("Has elegido la opcion numero 3: VER RANKING"); 
	  		main::ranking();
	  		break;

  		case 4:
	  		mostrarMensaje("Gracias por jugar ¡Vuelve pronto!"); 
	  		main::acabar();
	  		exit(0);
	  		break;

  		default:
  			break;
  	} 
 }

 int main::elegirDificultad()
 {
 	int opcionDificultad;

 	mostrarMensaje("El juego permite jugar con diferentes niveles de dificultad:")
 	mostrarMensaje("\t1.- Facil");
 	mostrarMensaje("\t2.- Medio");
 	mostrarMensaje("\t3.- Dificil");
 	mostrarMensaje("\t4.- Mixto");

 	do
 	{
 		mostrarMensaje("Elije con qué nivel de dificultad quieres jugar (opciones validas: 1, 2, 3 o 4): ")
 		recogerInt(opcionDificultad);
 	}while(opcionDificultad < 1 || opcionDificultad > 4);

 	return opcionDificultad;
 }

 void main::individual()
 {
 	int opcionDificultad;
 	int cant_preguntas;
 	int max_preguntas; //Leer las preguntas, meterlas en un array y contar la cantidad de posiciones de ese array
 	vector<preguntas_respuestas> PreguntasSeleccionadas;
 	preguntas_respuestas pregunta;
 	int random; //variable en la que guardaremos el numero aleatorio para elegir una pregunta aleatoria
 	int repetida = 0; //Variable para ver si en cada momento la pregunta elegida aleatoriamente es i no alguna que ya ha salido
 	int cantidadPreguntasValida = 0; //Variable para ver si se ha pasado o no con la cantidad de preguntas
 	int cont = 0;
 	int respValida = -1;
 	int respCorrecta;
 	char respuesta;

 	int opcionRepetir; //Para la eleccion del final: repetir o no la partida

 	opcionDificultad = main::elegirDificultad();

 	if(opcionDificultad == 1)
 	{
 		for(int i = 0; i < listaTodasPreguntas.size(); i++)
 		{
 			if(listaTodasPreguntas[i].getDificultad == "#")
 				PreguntasSeleccionadas.push_back(listaTodasPreguntas[i]);
 		}
 	}

 	if(opcionDificultad == 2)
 	{
 		for(int i = 0; i < listaTodasPreguntas.size(); i++)
 		{
 			if(listaTodasPreguntas[i].getDificultad == "##")
 				PreguntasSeleccionadas.push_back(listaTodasPreguntas[i]);
 		}
 	}

 	if(dificopcionDificultadultad == 3)
 	{
 		for(int i = 0; i < listaTodasPreguntas.size(); i++)
 		{
 			if(listaTodasPreguntas[i].getDificultad == "###")
 				PreguntasSeleccionadas.push_back(listaTodasPreguntas[i]);
 		}
 	}

 	if(opcionDificultad == 4)
 	{
 		PreguntasSeleccionadas = listaTodasPreguntas;
 	}

 	mostrarMensaje("¿Cuantas preguntas deseas que se te realicen?");
 	recogerInt(cant_preguntas);

 	cantidadPreguntasValida = operaciones::maxPreguntas(cant_preguntas, PreguntasSeleccionadas.size());
 	
 	while(cant_preguntas<0 || cantidadPreguntasValida == 0)
 	{
		mostrarMensaje("El numero de preguntas no es valido, debe ser mayor que 0 y menor o igual al total de preguntas disponibles.");
		mostrarMensaje("Numero de preguntas disponibles:");
		mostrarInt(PreguntasSeleccionadas.size());

		mostrarMensaje("Por favor, introduce otro numero:");
 		recogerInt(cant_preguntas);
 		cantidadPreguntasValida = operaciones::maxPreguntas(cant_preguntas, PreguntasSeleccionadas.size());
 	}

 	for(int i = 0; i < cant_preguntas; i++)
 	{
 		 pregunta = operaciones::generarPregunta(PreguntasSeleccionadas, preguntasSalidas);
		 mostrarPregunta(pregunta);
		 respValida = recogerOpcionRespuesta(respuesta, pregunta.getDificultad());

		 while(respValida == -1)
		 {
		 	 respValida = recogerOpcionRespuesta(respuesta, pregunta.getDificultad());
		 }

		switch (respuesta)
		{
			case 'a':
				respCorrecta = operaciones::comprobarRespuesta(pregunta.getRespuesta1());
				break;

			case 'b':
				respCorrecta = operaciones::comprobarRespuesta(pregunta.getRespuesta2());
				break;

			case 'c':
				respCorrecta = operaciones::comprobarRespuesta(pregunta.getRespuesta3());
				break;

			case 'd':
				respCorrecta = operaciones::comprobarRespuesta(pregunta.getRespuesta4());
		}
				
		 if(respCorrecta == 1)
		 {
		 	mostrarMensaje("Respuesta correcta");
		 	pregunta.sumarPunto(jugadorPrincipal);
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
	 	main::individual();
	 }
	 else
	 {
	 	main::menuJugador();
	 }
 }

void multijugador()
 {
 	int opcionDificultad
 	int cantJugadores;
 	int cantPreg;
 	vector<preguntas_respuestas> PreguntasSeleccionadas;
 	vector<jugador> multijugadores;
 	vector<jugador> empatados;
 	int cantidadPreguntasValida;
 	int puntMaxima;
 	int opcionDesempatar;
 	int opcionRepetir;

 	string NickAux;

 	opcionDificultad = main::elegirDificultad();

 	if(opcionDificultad == 1)
 	{
 		for(int i = 0; i < listaTodasPreguntas.size(); i++)
 		{
 			if(listaTodasPreguntas[i].getDificultad == "#")
 				PreguntasSeleccionadas.push_back(listaTodasPreguntas[i]);
 		}
 	}

 	if(opcionDificultad == 2)
 	{
 		for(int i = 0; i < listaTodasPreguntas.size(); i++)
 		{
 			if(listaTodasPreguntas[i].getDificultad == "##")
 				PreguntasSeleccionadas.push_back(listaTodasPreguntas[i]);
 		}
 	}

 	if(dificopcionDificultadultad == 3)
 	{
 		for(int i = 0; i < listaTodasPreguntas.size(); i++)
 		{
 			if(listaTodasPreguntas[i].getDificultad == "###")
 				PreguntasSeleccionadas.push_back(listaTodasPreguntas[i]);
 		}
 	}

 	if(opcionDificultad == 4)
 	{
 		PreguntasSeleccionadas = listaTodasPreguntas;
 	}

	mostrarMensaje("¿Cuantos jugadores van a jugar?");
 	recogerInt(cantJugadores);

 	cantidadPreguntasValida = operaciones::maxPreguntas(cantJugadores, PreguntasSeleccionadas.size());
 	while(cantJugadores<2 ||  cantidadPreguntasValida == 0)
 	{
 		mostrarMensaje("El numero introducido es incorrecto (o por ser inferior a 2 o por exceder la cantidad de preguntas disponibles. \n");
 		mostrarMensaje("\nPor favor, intoduce cuantos jugadores van a jugar: \t");
 		recogerInt(cantJugadores);
 		cantidadPreguntasValida = operaciones::maxPreguntas(cantJugadores, PreguntasSeleccionadas.size());
 	}

 	//El primer jugador es el actual 
 	multijugadores.push_back(jugadorPrincipal);
 	multijugadores[0].setPuntuacion(0);

 	mostrarMensaje("Introduce los nombres de los jugadores contra los que vas a jugar:");
 	for (int i = 1; i < multijugadores.size(); i++)
 	{
 		mostrarMensaje("J");mostrarInt(i);mostrarMensaje(": "); //Para que aparezca como JX: 
 		recogerNick(NickAux);
 		multijugadores.push_back(new jugador(NickAux));
 		multijugadores[i].setPuntuacion(0);
 	}

 	mostrarMensaje("¿Cuantas preguntas deseas que se le realicen a cada jugador?\t");
 	recogerInt(cantPreg);
 	cantidadPreguntasValida = operaciones::maxPreguntas(multijugadores.size()*cantPreg, PreguntasSeleccionadas.size());

	while(cantPreg<1 || cantidadPreguntasValida == 0)
 	{
 		mostrarMensaje("El numero introducido es incorrecto (o por ser inferior a 1 o por exceder la cantidad de preguntas disponibles para la cantidad de jugadores elegida.");
 		mostrarMensaje("Por favor, intoduce cuantas preguntas deseas que se le realicen a cada jugador:");
 		recogerInt(cantPreg);
 		cantidadPreguntasValida = operaciones::maxPreguntas(multijugadores.size()*cantPreg, PreguntasSeleccionadas.size());
 	}

 	main::RealizarPreguntasMultijugador(multijugadores, cantPreg);
 	
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
		 		main::RealizarPreguntasMultijugador(empatados, 1);
		 		c = 0;
		 		for (int i = 0; i < multijugadores.size(); ++i)
		 		{
		 			if(multijugadores[i].getNick() == empatados[c].getNick())
		 			{
		 				multijugadores[i].setPuntuacion(empatados[c].gePuntuacion());
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
	 	main::multijugador();
	 }
	 else
	 {
	 	main::menuJugador();
	 }
 }

 void main::RealizarPreguntasMultijugador(vector<jugador> multijugadores, int cantPreg)
 {
 	int cont = 0;
 	int respValida = -1;
 	int random;//variable en la que guardaremos el numero aleatorio para elegir una pregunta aleatoria
 	int repetida = 0; //Variable para ver si en cada momento la pregunta elegida aleatoriamente es i no alguna que ya ha salido
 	preguntas_respuestas pregunta;
 	char respuesta;
 	int correcta = 0;

 	for(int i = 0; i < cantPreg; i++)
 	{
 		for(int j = 0; j < multijugadores.size(); j++)
 		{
 			mostrarMensaje("\nPregunta para el jugador #" + (j+1) + "->" + multijugadores[j].nick);

 			//Preparar la pregunta aleatoria para el jugador
 			pregunta = operaciones::generarPregunta(listaTodasPreguntas, preguntasSalidas);

			mostrarPregunta(pregunta);
			respValida = recogerOpcionRespuesta(respuesta, pregunta.getDificultad());

			while(respValida == -1)
			{
				respValida = recogerOpcionRespuesta(respuesta, pregunta.getDificultad());
			}
			
			switch (respuesta)
			{
			case 'a':
				correcta = operaciones::comprobarRespuesta(pregunta.getRespuesta1());
				break;

			case 'b':
				correcta = operaciones::comprobarRespuesta(pregunta.getRespuesta2());
				break;

			case 'c':
				correcta = operaciones::comprobarRespuesta(pregunta.getRespuesta3());
				break;

			case 'd':
				correcta = operaciones::comprobarRespuesta(pregunta.getRespuesta4());
				break;
			}

			if(correcta == 1)
			{
			 	mostrarMensaje("Respuesta correcta");
			 	pregunta.sumarPunto(multijugadores[j]);
			}
			else
			{
			 	mostrarMensaje("Respuesta incorrecta");
			}
 		}
 	}

 }

  void ranking()
 {
 	operaciones::ordenarJugadores(listaTodosJugadores);

 	mostrarMensaje("\nRANKING DE JUGADORES");
 	for(int i = 0; i < listaTodosJugadores.size(); i++)
 	{
 		mostrarMensaje((i+1) + ".-");
 		mostrarPuntuacion(listaTodosJugadores[i]);
 	}
 		mostrarMensaje("\n");
	 main::menuJugador();
 }

 void acabar() //metodo para liberar recursos
 {
 	delete preguntasSalidas;
 	delete listaTodasPreguntas;

 	operaciones::guardarJugadores(listaTodosJugadores);

 	delete listaTodosJugadores;

 	delete BD;
 }