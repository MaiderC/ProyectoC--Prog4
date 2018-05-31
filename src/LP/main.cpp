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
void menuAdmin();
void menuJugador();
void individual();
void multijugador();
void ranking();
void acabar();
void RealizarPreguntasMultijugador(vector<jugador> multijugadores, int cantPreg);
int elegirDificultad();

vector<preguntas_respuestas> preguntasSalidas; // Lista de las preguntas que ya han salido en la ejecución del juego
vector<preguntas_respuestas> listaTodasPreguntas; // Lista de todas las preguntas de la base de datos
vector<jugador> listaTodosJugadores; // Lista de todos los jugadores de la base de datos
jugador jugadorPrincipal; // Jugador que inicia la partida

int main(int argc, char** argv)
{
	DBConnector BD ("./Data/BD.sqlite");
	BD.leer_Jugadores(listaTodosJugadores);

  	BD.leer_Preguntas(listaTodasPreguntas);

  	if(argc == 2)
  	{
		int admin;
		admin = (argv[1] == "admin");

		if (admin == 0)
		{
			menuAdmin();
		}
  	}
  	else //es un jugador
  	{
  		if(listaTodasPreguntas.size() == 0)
  		{
  			utilidades::mostrarMensaje("No hay preguntas en el sistema :(");
  		}
  		else
  		{
	  		//Antes de mostrar el menu, como es la primera vez, hacemos que se identifique
	  		string nick;
	  		utilidades::recogerString(nick);

	 		jugadorPrincipal jugador(nick, 0);

	 		utilidades::mostrarMensaje("Hola "); utilidades::mostrarMensaje(nick); utilidades::mostrarMensaje("!");
	    	menuJugador();
		}
  	}

  	return 0;
}

 void menuAdmin()
 {
 	utilidades::mostrarMensaje("Hola, administrador");

 	do
 	{
	 	int opcionMenu = 0;
	 	int opcionSeguir;

	 	 utilidades::mostrarMensaje("Estas son las acciones que puedes realizar:");
	 	 utilidades::mostrarMensaje("\t1- Añadir preguntas fáciles");
	 	 utilidades::mostrarMensaje("\t2- Añadir preguntas de dificultad media")
	 	 utilidades::mostrarMensaje("\t3- Añadir preguntas dificiles");
	 	 utilidades::mostrarMensaje("\t4- Borrar preguntas");
	 	 utilidades::mostrarMensaje("\t5- Salir")
	 	 utilidades::mostrarMensaje("Inserta el número de la acción que deseas realizar: ");

	  	utilidades::recogerInt(opcionMenu);

	  	while(opcionMenu < 1 || opcionMenu > 5)
	 	{
	 	 	utilidades::mostrarMensaje("\nLa opcion introducida no es valida. Por favor, intentalo de nuevo:  ");
	 	 	utilidades::recogerInt(opcionMenu);
	 	}

	  	switch(opcionMenu)
	  	{
	  		case 1:
	  			do
	  			{
	  				opcionSeguir = 0;
		  			int cant_p = 0; //cantidad de preguntas que va a insertar el administrador

					utilidades::mostrarMensaje("Indica la cantidad de preguntas que deseas introducir: ");
		    		utilidades::recogerInt(cant_p); //en recoger int, añadir mensajes de error si no es un int
		   
				    while(cant_p <= 0)
				    {
				    	utilidades::mostrarMensaje("El numero de preguntas debe ser superior a 0. Por favor, indica de nuevo la cantidad: ");
				    	utilidades::recogerInt(cant_p);
				    }

				    prfacil preg_r prfacil();

				    for (int i = 0; i < cant_p; i++)
				    {
				    	utilidades::recogerPregunta(preg_r);
				    	BD.insert_Pregunta(preg_r);
				    }

				    utilidades::mostrarMensaje("¿Quieres seguir introduciendo preguntas?");
			 		utilidades::mostrarMensaje("1.- Si");
			 		utilidades::mostrarMensaje("2.- No");
			 		utilidades::recogerInt(opcionSeguir);

				}while(opcionSeguir != 2);
				break;

			case 2:
	  			do
	  			{
	  				opcionSeguir = 0;
		  			int cant_p = 0; //cantidad de preguntas que va a insertar el administrador

					utilidades::mostrarMensaje("Indica la cantidad de preguntas que deseas introducir: ");
		    		utilidades::recogerInt(cant_p); //en recoger int, añadir mensajes de error si no es un int
		   
				    while(cant_p <= 0)
				    {
				    	utilidades::mostrarMensaje("El numero de preguntas debe ser superior a 0. Por favor, indica de nuevo la cantidad: ");
				    	utilidades::recogerInt(cant_p);
				    }

				    prmedio preg_r prmedio();

				    for (int i = 0; i < cant_p; i++)
				    {
				    	utilidades::recogerPregunta(preg_r);
				    	DBConnector::insert_Pregunta(preg_r);
				    }

				    utilidades::mostrarMensaje("¿Quieres seguir introduciendo preguntas?");
			 		utilidades::mostrarMensaje("1.- Si");
			 		utilidades::mostrarMensaje("2.- No");
			 		utilidades::recogerInt(opcionSeguir);

				}while(opcionSeguir != 2);
				break;

			case 3:
	  			do
	  			{
	  				opcionSeguir = 0;
		  			int cant_p = 0; //cantidad de preguntas que va a insertar el administrador

					utilidades::mostrarMensaje("Indica la cantidad de preguntas que deseas introducir: ");
		    		utilidades::recogerInt(cant_p); //en recoger int, añadir mensajes de error si no es un int
		   
				    while(cant_p <= 0)
				    {
				    	utilidades::mostrarMensaje("El numero de preguntas debe ser superior a 0. Por favor, indica de nuevo la cantidad: ");
				    	utilidades::recogerInt(cant_p);
				    }

				    prdificil preg_r prdificil();

				    for (int i = 0; i < cant_p; i++)
				    {
				    	utilidades::recogerPregunta(preg_r);
				    	DBConnector::insert_Pregunta(preg_r);
				    }

				    utilidades::mostrarMensaje("¿Quieres seguir introduciendo preguntas?");
			 		utilidades::mostrarMensaje("1.- Si");
			 		utilidades::mostrarMensaje("2.- No");
			 		utilidades::recogerInt(opcionSeguir);

				}while(opcionSeguir != 2);
				break;

			case 4:
				do
				{
					int opcionEliminar = 0;
					utilidades::mostrarTodasPreguntas(listaTodasPreguntas);
					utilidades::mostrarMensaje("¿Que pregunta quieres eliminar?");
					utilidades::recogerInt(opcionEliminar);

					BD.delete_Pregunta(listaTodasPreguntas[opcionEliminar-1]);
					listaTodasPreguntas.erase(opcionEliminar-1);

					utilidades::mostrarMensaje("¿Quieres seguir eliminando preguntas?");
			 		utilidades::mostrarMensaje("1.- Si");
			 		utilidades::mostrarMensaje("2.- No");
			 		utilidades::recogerInt(opcionEliminar);
				}while(opcionEliminar != 2);
				break;

			case 5:
				utilidades::mostrarMensaje("Modo administrador cerrado finalizado.");
				acaba();
				break;

			default:
				break;
	  	}
	}while(opcionMenu != 5)
 }

 void menuJugador()
 {
 	int opcionMenu;
	
 	 utilidades::mostrarMensaje("\n\n----MENU----\n"); 
 	 utilidades::mostrarMensaje("Por favor, elije una de las siguientes opciones:");
 	 utilidades::mostrarMensaje("\t 1.- Jugar partida individual");
 	 utilidades::mostrarMensaje("\t 2.- Jugar partida multijugador");
 	 utilidades::mostrarMensaje("\t 3.- Ver ranking");
 	 utilidades::mostrarMensaje("\t 4.- Salir");
 	 utilidades::mostrarMensaje("Indica el numero de la opcion que quieres elegir: ");

  	utilidades::recogerInt(opcionMenu);

	while(!(opcionMenu>0 && opcionMenu<5))
  	{
  		utilidades::mostrarMensaje("Opcion no valida. Por favor, indica el numero de la opcion que quieres elegir: "); 
  		utilidades::recogerInt(opcionMenu);
  	}

  	switch(opcionMenu)
  	{
  		case 1: 
	  		utilidades::mostrarMensaje("Has elegido la opcion numero 1: JUGAR PARTIDA INDIVIDUAL");
	  		individual();
	  		break;

  		case 2:
	  		utilidades::mostrarMensaje("Has elegido la opcion numero 2: JUGAR PARTIDA MULTIJUGADOR");
	  		multijugador();
	  		break;

  		case 3:
	  		utilidades::mostrarMensaje("Has elegido la opcion numero 3: VER RANKING"); 
	  		ranking();
	  		break;

  		case 4:
	  		utilidades::mostrarMensaje("Gracias por jugar ¡Vuelve pronto!"); 
	  		acabar();
	  		exit(0);
	  		break;

  		default:
  			break;
  	} 
 }

 int elegirDificultad()
 {
 	int opcionDificultad;

 	utilidades::mostrarMensaje("El juego permite jugar con diferentes niveles de dificultad:")
 	utilidades::mostrarMensaje("\t1.- Facil");
 	utilidades::mostrarMensaje("\t2.- Medio");
 	utilidades::mostrarMensaje("\t3.- Dificil");
 	utilidades::mostrarMensaje("\t4.- Mixto");

 	do
 	{
 		utilidades::mostrarMensaje("Elije con qué nivel de dificultad quieres jugar (opciones validas: 1, 2, 3 o 4): ")
 		utilidades::recogerInt(opcionDificultad);
 	}while(opcionDificultad < 1 || opcionDificultad > 4);

 	return opcionDificultad;
 }

 void individual()
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

 	opcionDificultad = elegirDificultad();

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

 	utilidades::mostrarMensaje("¿Cuantas preguntas deseas que se te realicen?");
 	utilidades::recogerInt(cant_preguntas);

 	cantidadPreguntasValida = operaciones::maxPreguntas(cant_preguntas, PreguntasSeleccionadas.size());
 	
 	while(cant_preguntas<0 || cantidadPreguntasValida == 0)
 	{
		utilidades::mostrarMensaje("El numero de preguntas no es valido, debe ser mayor que 0 y menor o igual al total de preguntas disponibles.");
		utilidades::mostrarMensaje("Numero de preguntas disponibles:");
		utilidades::mostrarInt(PreguntasSeleccionadas.size());

		utilidades::mostrarMensaje("Por favor, introduce otro numero:");
 		utilidades::recogerInt(cant_preguntas);
 		cantidadPreguntasValida = operaciones::maxPreguntas(cant_preguntas, PreguntasSeleccionadas.size());
 	}

 	for(int i = 0; i < cant_preguntas; i++)
 	{
 		 pregunta = operaciones::generarPregunta(PreguntasSeleccionadas, preguntasSalidas);
		 utilidades::mostrarPregunta(pregunta);
		 respValida = utilidades::recogerOpcionRespuesta(respuesta, pregunta.getDificultad());

		 if(pregunta.getDificultad() == "#")
		 {
		 	prfacil* preguntaAux = dynamic_cast<prfacil*> (pregunta);
		 } else if(pregunta.getDificultad() == "##")
		 {
		 	prmedio* preguntaAux = dynamic_cast<prmedio*> (pregunta);
		 } else if(pregunta.getDificultad() == "###")
		 {
		 	prdificil* preguntaAux = dynamic_cast<prdificil*> (pregunta);
		 }

		 while(respValida == -1)
		 {
		 	 respValida = utilidades::recogerOpcionRespuesta(respuesta, preguntaAux.getDificultad());
		 }

		switch (respuesta)
		{
			case 'a':
				respCorrecta = operaciones::comprobarRespuesta(preguntaAux.getRespuesta1());
				break;

			case 'b':
				respCorrecta = operaciones::comprobarRespuesta(preguntaAux.getRespuesta2());
				break;

			case 'c':
				respCorrecta = operaciones::comprobarRespuesta(preguntaAux.getRespuesta3());
				break;

			case 'd':
				respCorrecta = operaciones::comprobarRespuesta(preguntaAux.getRespuesta4());
		}
				
		 if(respCorrecta == 1)
		 {
		 	utilidades::mostrarMensaje("Respuesta correcta");
		 	pregunta.sumarPunto(jugadorPrincipal);
		 }
		 else
		 {
		 	utilidades::mostrarMensaje("Respuesta incorrecta");
		 }
	 }

	 utilidades::mostrarMensaje("---Fin de la partida---");
	 utilidades::mostrarMensaje("Deseas volver a jugar o regresar al menu?");
	 utilidades::mostrarMensaje("1.- Volver a jugar");
	 utilidades::mostrarMensaje("2.- Volver al menu");
	 utilidades::mostrarMensaje("Introduce la opcion deseada:");
	 utilidades::recogerInt(opcionRepetir);

	 listaTodosJugadores = actualizarPuntuacion(listaTodosJugadores, jugadorPrincipal);
	 jugadorPrincipal.setPuntuacion(0);

	 while(opcionRepetir != 1 && opcionRepetir != 2)
	 {
	 	 utilidades::mostrarMensaje("\nLa opcion introducida no es valida. Por favor, intentalo de nuevo:  ");
	 	 utilidades::recogerInt(opcionRepetir);
	 }

	 if(opcionRepetir == 1)
	 {
	 	individual();
	 }
	 else
	 {
	 	menuJugador();
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

 	opcionDificultad = elegirDificultad();

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

	utilidades::mostrarMensaje("¿Cuantos jugadores van a jugar?");
 	utilidades::recogerInt(cantJugadores);

 	cantidadPreguntasValida = operaciones::maxPreguntas(cantJugadores, PreguntasSeleccionadas.size());
 	while(cantJugadores<2 ||  cantidadPreguntasValida == 0)
 	{
 		utilidades::mostrarMensaje("El numero introducido es incorrecto (o por ser inferior a 2 o por exceder la cantidad de preguntas disponibles. \n");
 		utilidades::mostrarMensaje("\nPor favor, intoduce cuantos jugadores van a jugar: \t");
 		utilidades::recogerInt(cantJugadores);
 		cantidadPreguntasValida = operaciones::maxPreguntas(cantJugadores, PreguntasSeleccionadas.size());
 	}

 	//El primer jugador es el actual 
 	multijugadores.push_back(jugadorPrincipal);
 	multijugadores[0].setPuntuacion(0);

 	utilidades::mostrarMensaje("Introduce los nombres de los jugadores contra los que vas a jugar:");
 	for (int i = 1; i < multijugadores.size(); i++)
 	{
 		utilidades::mostrarMensaje("J");utilidades::mostrarInt(i);utilidades::mostrarMensaje(": "); //Para que aparezca como JX: 
 		utilidades::recogerString(NickAux);
 		jugador aux (NickAux);
 		multijugadores.push_back(aux);
 		multijugadores[i].setPuntuacion(0);
 	}

 	utilidades::mostrarMensaje("¿Cuantas preguntas deseas que se le realicen a cada jugador?\t");
 	utilidades::recogerInt(cantPreg);
 	cantidadPreguntasValida = operaciones::maxPreguntas(multijugadores.size()*cantPreg, PreguntasSeleccionadas.size());

	while(cantPreg<1 || cantidadPreguntasValida == 0)
 	{
 		utilidades::mostrarMensaje("El numero introducido es incorrecto (o por ser inferior a 1 o por exceder la cantidad de preguntas disponibles para la cantidad de jugadores elegida.");
 		utilidades::mostrarMensaje("Por favor, intoduce cuantas preguntas deseas que se le realicen a cada jugador:");
 		utilidades::recogerInt(cantPreg);
 		cantidadPreguntasValida = operaciones::maxPreguntas(multijugadores.size()*cantPreg, PreguntasSeleccionadas.size());
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
	 		opcionDesempatar = utilidades::mensajeEmpate(empatados);
	 		
	 		if(opcionDesempatar == 1)
	 		{
	 			//Realizamos una sola pregunta entre los jugadores que han empatado para ver si asi deshacen el empate
		 		RealizarPreguntasMultijugador(empatados, 1);
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
	 			utilidades::mensajeGanador(multijugadores[i]);
	 		}
	 		listaTodosJugadores = actualizarPuntuacion(listaTodosJugadores, multijugadores);
	 	}

	 //Volver al menu o volver a jugar
	 utilidades::mostrarMensaje("Fin de la partida.");
	 utilidades::mostrarMensaje("¿Deseas volver a jugar o regresar al menu?");
	 utilidades::mostrarMensaje("1.- Volver a jugar");
	 utilidades::mostrarMensaje("2.- Volver al menu");
	 utilidades::mostrarMensaje("Introduce la opcion deseada:  ");
	 utilidades::recogerInt(opcionRepetir);

	 while(opcionRepetir != 1 && opcionRepetir != 2)
	 {
	 	 utilidades::mostrarMensaje("\nLa opcion introducida no es valida. Por favor, intentalo de nuevo:  ");
	 	 utilidades::recogerInt(opcionRepetir);
	 }

	 if(opcionRepetir == 1)
	 {
	 	multijugador();
	 }
	 else
	 {
	 	menuJugador();
	 }
 }

 void RealizarPreguntasMultijugador(vector<jugador> multijugadores, int cantPreg)
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
 			utilidades::mostrarMensaje("\nPregunta para el jugador #" + (j+1) + "->" + multijugadores[j].nick);

 			//Preparar la pregunta aleatoria para el jugador
 			pregunta = operaciones::generarPregunta(listaTodasPreguntas, preguntasSalidas);

			utilidades::mostrarPregunta(pregunta);
			respValida = utilidades::recogerOpcionRespuesta(respuesta, pregunta.getDificultad());

			while(respValida == -1)
			{
				respValida = utilidades::recogerOpcionRespuesta(respuesta, pregunta.getDificultad());
			}
			
			if(pregunta.getDificultad() == "#")
			{
				prfacil* preguntaAux = dynamic_cast<prfacil*> (pregunta);
			} else if(pregunta.getDificultad() == "##")
			{
				prmedio* preguntaAux = dynamic_cast<prmedio*> (pregunta);
			} else if(pregunta.getDificultad() == "###")
			{
				prdificil* preguntaAux = dynamic_cast<prdificil*> (pregunta);
			}

			switch (respuesta)
			{
			case 'a':
				correcta = operaciones::comprobarRespuesta(preguntaAux.getRespuesta1());
				break;

			case 'b':
				correcta = operaciones::comprobarRespuesta(preguntaAux.getRespuesta2());
				break;

			case 'c':
				correcta = operaciones::comprobarRespuesta(preguntaAux.getRespuesta3());
				break;

			case 'd':
				correcta = operaciones::comprobarRespuesta(preguntaAux.getRespuesta4());
				break;
			}

			if(correcta == 1)
			{
			 	utilidades::mostrarMensaje("Respuesta correcta");
			 	pregunta.sumarPunto(multijugadores[j]);
			}
			else
			{
			 	utilidades::mostrarMensaje("Respuesta incorrecta");
			}
 		}
 	}

 }

  void ranking()
 {
 	operaciones::ordenarJugadores(listaTodosJugadores);

 	utilidades::mostrarMensaje("\nRANKING DE JUGADORES");
 	for(int i = 0; i < listaTodosJugadores.size(); i++)
 	{
 		utilidades::mostrarMensaje((i+1) + ".-");
 		utilidades::mostrarPuntuacion(listaTodosJugadores[i]);
 	}
 		utilidades::mostrarMensaje("\n");
	 menuJugador();
 }

 void acabar() //metodo para liberar recursos
 {
 	delete preguntasSalidas;
 	delete listaTodasPreguntas;

 	operaciones::guardarJugadores(listaTodosJugadores);

 	delete listaTodosJugadores;

 	delete BD;
 }