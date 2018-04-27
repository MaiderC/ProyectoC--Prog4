#include "../INCLUDES/jugador.h"
#include "../INCLUDES/preguntas_respuestas.h"
#include "../INCLUDES/utilidades.h"
#include "../INCLUDES/data.h"
#include "../INCLUDES/operaciones.h"
#include <string.h>

//Declaracion de MeTODOS
void menuAdmin();
void menuJugador();
void individual();
void multijugador();
void ranking();
void acabar();
void RealizarPreguntasMultijugador(t_jugador* multijugadores, int cantPreg, int cantJugadores);

//Tamaños de las listas
int sizeTotalPreguntas; //igualarlo a un metodo de data que cuente la cantidad de preguntas en el fichero (lo mimso que leer pero con un contador en el while)
int sizePreguntasSalidas = 0; //Empezara siendo 0 y lo incrementaremos cada vez que se haga una nueva pregunta

t_pregunta_respuestas* preguntasSalidas;
//Lista de todas las preguntas
t_pregunta_respuestas* arrPreg;

t_jugador* listaTodosJugadores;
int* numJugadores;

//Jugador que inicia la partida
t_jugador jugadorPrincipal;

int main(int argc, char** argv)
{
	numJugadores = (int*) malloc(sizeof(int));
	(*numJugadores) = numJugadoresTotal();
	listaTodosJugadores = leerJugadores();

  sizeTotalPreguntas = numPreguntasEnFichero(); 
  arrPreg = (t_pregunta_respuestas*) malloc (sizeof(t_pregunta_respuestas) * sizeTotalPreguntas);
  arrPreg = leerPreguntasRespuestas();
  preguntasSalidas = (t_pregunta_respuestas*) malloc (sizeof(t_pregunta_respuestas));

  if(argc == 2)
  {
  	//Para comparar los strings, usamos strcmp
	int admin;
	admin=strcmp(argv[1],"admin");

		if (admin==0)
		{
			menuAdmin();
		}	
  }
  else //es un jugador
  {
  	if(sizeTotalPreguntas == 0)
  	{
  		mostrarMensaje("No hay preguntas en el sistema :(");
  	}
  	else
  	{
	  	//Antes de mostrar el menu, como es la primera vez, hacemos que se identifique
	  	char* nick;
	  	recogerNick(&nick);
	 	jugadorPrincipal = crearJugador(nick);
	 	mostrarMensaje("Hola "); mostrarMensaje(nick); mostrarMensaje("!");
	    menuJugador();
	    //asignarle nick al jugador
	}
  }

  return 0;
}

 void menuAdmin()
 {
 	 mostrarMensaje("Hola, administrador\n"); 

  	//Todo ira dentro de un do-while, ya que al menos una vez se realizara y segun lo el valor que le de a la variable "opcion" saldra o no del bucle
  	int opcion=0;

   do
  	{
	  	int cant_p=0;//cantidad de preguntas que va a insertar el administrador
	  	int MAX_PREG = 250;
	  	int MAX_RESP = 200;

		mostrarMensaje("Indica la cantidad de preguntas que deseas introducir:  ");
	    recogerInt(&cant_p); //en recoger int, añadir mensajes de error si no es un int
	   
	    while(cant_p<=0)
	    {
	    	mostrarMensaje("El numero de preguntas debe ser superior a 0. Por favor, intentalo de nuevo: \n");
	    	recogerInt(&cant_p); 
	    }

	    t_pregunta_respuestas preg_r[cant_p]; //array de preguntas_respuestas

	    for (int i=0; i<cant_p; i++)
	    {
	    	 char* pregunta;
	    	 char* r1;
	    	 char* correcta;//variable auxiliar para guardar la respuesta correcta con un punto por delante en la structura
	    	 char* r2;
	    	 char* r3;

	    	mostrarMensaje("Introduce la pregunta a insertar: ");
	    	recogerString(&pregunta, MAX_PREG);

	    		
	    	 mostrarMensaje("\n*La respuesta no debe contener la letra de la opcion (a, b, c) ni signos de puntuacion al inicio (salvo que se trate de un guion, por ser la respuesta un numero negativo)");
	    	 mostrarMensaje("\nIntroduce la respuesta correcta: ");
	    	 recogerString(&correcta, MAX_RESP);

	    	 //Hacemos un malloc para que el array tenga tandos caracteres como la respuesta correcta +1, para el punto y para el \0
	    	 r1=(char*)malloc((strlen(correcta)+2)*sizeof(char*));

	    	 r1[0]='#'; //Le ponemos a r1 el .
	    	 r1[1]='\0'; //Para convertir la cadena de caracteres en String, le ponemos el 0 (o \0)
	    	 //Ponerle el punto delante a la respuesta correcta
	    	 strcat(r1,correcta); 
	    	 
	    	 mostrarMensaje("\nIntroduce otra respuesta (una incorrecta): ");
	    	 recogerString(&r2, MAX_RESP);
	    	 mostrarMensaje("\nIntroduce otra respuesta (una incorrecta): ");
	    	 recogerString(&r3, MAX_RESP);
	    	 
	    	 strcpy(preg_r[i].Pregunta, pregunta);
	    	 strcpy(preg_r[i].Respuesta1,  r1);
	    	 strcpy(preg_r[i].Respuesta2,  r2);
	    	 strcpy(preg_r[i].Respuesta3, r3);

	    	 free(r1);
	    	 r1=NULL;
	    }
	    guardarPreguntaRespuestas(preg_r, cant_p);

	    mostrarMensaje("\n Quieres seguir introduciendo preguntas?\n");
 		mostrarMensaje("\t1.- Si\n");
 		mostrarMensaje("\t2.- No\n");
 		recogerInt(&opcion);

	}while (opcion!=2);
 }

 void menuJugador()
 {
 	int opcion;
	
 	 mostrarMensaje("\n\n\n----MENU----\n"); 
 	 mostrarMensaje("Por favor, elije una de las siguientes opciones:\n"); 
 	 mostrarMensaje("\t 1.- Jugar partida individual\n"); 
 	 mostrarMensaje("\t 2.- Jugar partida multijugador\n"); 
 	 mostrarMensaje("\t 3.- Ver ranking\n"); 
 	 mostrarMensaje("\t 4.- Salir \n"); 
 	 mostrarMensaje("Indica el numero de la opcion que quieres elegir\n"); 
 
  	recogerInt (&opcion);

	while(!(opcion>0 && opcion<5))
  	{
  		mostrarMensaje("Opcion no valida. Por favor, indica el numero de la opcion que quieres elegir\n"); 
  		recogerInt (&opcion);
  	}

  	switch(opcion)
  	{
  		case 1: 
  		mostrarMensaje("Has elegido la opcion numero 1: JUGAR PARTIDA INDIVIDUAL \n"); 
  		individual();
  		break;

  		case 2:
  		mostrarMensaje("Has elegido la opcion numero 2: JUGAR PARTIDA MULTIJUGADOR \n"); 
  		multijugador();
  		break;

  		case 3:
  		mostrarMensaje("Has elegido la opcion numero 3: VER RANKING\n"); 
  		ranking();
  		break;

  		case 4:
  		mostrarMensaje("Gracias por jugar ¡Vuelve pronto!\n"); 
  		acabar();
  		exit(0);

  		break;

  		default:
  		break;
  	} 
 }

 void individual()
 {
 	int cant_preguntas;
 	int max_preguntas;//Leer las preguntas, meterlas en un array y contar la cantidad de posiciones de ese array
 	//t_pregunta_respuestas* arrPreg; //todas las preguntas guardadas en el fichero
 	t_pregunta_respuestas* aux; //Este es un array auxiliar para poder ir añadiendo las preguntas que vayan saliendo
 	t_pregunta_respuestas pregunta;
 	int random;//variable en la que guardaremos el numero aleatorio para elegir una pregunta aleatoria
 	int repetida = 0; //Variable para ver si en cada momento la pregunta elegida aleatoriamente es i no alguna que ya ha salido
 	int cantidadPreguntasValida = 0; //Variable para ver si se ha pasado o no con la cantidad de preguntas
 	int cont=0;
 	int respValida=-1;
 	int respCorrecta;
 	char respuesta;

 	int opcion; //Para la eleccion del final

 	mostrarMensaje("\n Cuantas preguntas deseas que se te realicen?\t");
 	recogerInt(&cant_preguntas);

 	cantidadPreguntasValida = maxPreguntas (cant_preguntas, sizeTotalPreguntas);
 	
 	while(cant_preguntas<0 || cantidadPreguntasValida == 0)
 	{
		mostrarMensaje("El numero de preguntas no es valido (porque es muy elevado o porque no es mayor a 0)\n Por favor, introduce otro numero: \t");
 		recogerInt(&cant_preguntas);
 		cantidadPreguntasValida = maxPreguntas (cant_preguntas, sizeTotalPreguntas);
 	}

 	for(int i=0; i<cant_preguntas; i++)
 	{
 		 pregunta = generarPregunta (arrPreg, &preguntasSalidas, &sizePreguntasSalidas, sizeTotalPreguntas);
		 mostrarPregunta(pregunta);
		 mostrarRespuestas(pregunta);
		 respValida = recogerRespuesta(&respuesta);

		 while(respValida == -1)
		 {
		 	 respValida = recogerRespuesta(&respuesta);
		 }
	 //LLAMAR AL MeTODO DE OPERACIONES QUE COMPRUEBA SI LA RESPUESTA ES CORRECTA O NO
		switch (respuesta)
		{
			case 'a':
				respCorrecta = comprobarRespuesta(pregunta.Respuesta1);
			break;

			case 'b':
				respCorrecta = comprobarRespuesta(pregunta.Respuesta2);
			break;

			case 'c':
				respCorrecta = comprobarRespuesta(pregunta.Respuesta3);
			break;
		}
				
		 if(respCorrecta == 1)
		 {
		 	mostrarMensaje("Respuesta correcta\n");
		 	sumarPunto(&jugadorPrincipal);
		 }
		 else
		 {
		 	mostrarMensaje("Respuesta incorrecta\n");
		 }
	 }
	 mostrarMensaje("\n ---Fin de la partida---\n  Deseas volver a jugar o regresar al menu?");
	 mostrarMensaje("\n1.- Volver a jugar\n");
	 mostrarMensaje("\n2.- Volver al menu\n");
	 mostrarMensaje("\nIntroduce la opcion deseada:  ");
	 recogerInt (&opcion);

	 listaTodosJugadores = actualizarPuntuacion(listaTodosJugadores, numJugadores, &jugadorPrincipal, 1);
	 jugadorPrincipal.puntuacion = 0;

	 while(opcion != 1 && opcion != 2)
	 {
	 	 mostrarMensaje("\nLa opcion introducida no es valida. Por favor, intentalo de nuevo:  ");
	 	 recogerInt (&opcion);
	 }

	 if(opcion == 1)
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
 	int cantJugadores;
 	int cantPreg;

 	int cantidadPreguntasValida;
 	int sizeEmpatados=0;
 	int puntMaxima;
 	int opcion; 

 	char* aux;

 	mostrarMensaje("\n Cuantos jugadores van a jugar?\t");
 	recogerInt(&cantJugadores);

 	cantidadPreguntasValida = maxPreguntas (cantJugadores, sizeTotalPreguntas);
 	while(cantJugadores<2 ||  cantidadPreguntasValida == 0)
 	{
 		mostrarMensaje("El numero introducido es incorrecto (o por ser inferior a 2 o por exceder la cantidad de preguntas disponibles. \n");
 		mostrarMensaje("\nPor favor, intoduce cuantos jugadores van a jugar: \t");
 		recogerInt(&cantJugadores);
 		cantidadPreguntasValida = maxPreguntas (cantJugadores, sizeTotalPreguntas);
 	}
 	//ARRAY CON LOS JUGADORES DE ESTA PARTIDA: Lo creamos aqui para poder hacerlo estatico, ya que aqui ya sabemos la cantidad de jugadores
 	t_jugador multijugadores[cantJugadores];

 	//El primer jugador es el actual 
 	strcpy(multijugadores[0].nick, jugadorPrincipal.nick);
 	multijugadores[0].puntuacion = 0;

 	mostrarMensaje("Introduce los nombres de los jugadores contra los que vas a jugar:");
 	for (int i = 1; i < cantJugadores; ++i) //Empezamos el bucle desde 1 porque el 0 ya lo hemos cubierto
 	{
 		mostrarMensaje("\n\nJ");mostrarInt(i+1);mostrarMensaje(":  "); //Para que aparezca como JX: 
 		recogerNick (&aux);
 		multijugadores[i]= crearJugador(aux);
 		multijugadores[i].puntuacion =0;
 	}

 	mostrarMensaje(" Cuantas preguntas deseas que se le realicen a cada jugador?\t");
 	recogerInt(&cantPreg);
 	cantidadPreguntasValida = maxPreguntas (cantJugadores*cantPreg, sizeTotalPreguntas);

	while(cantPreg<1 || cantidadPreguntasValida == 0)
 	{
 		mostrarMensaje("El numero introducido es incorrecto (o por ser inferior a 1 o por exceder la cantidad de preguntas disponibles para la cantidad de jugadores elegida. \n");
 		mostrarMensaje("Por favor, intoduce cuantas preguntas deseas que se le realicen a cada jugador: \t");
 		recogerInt(&cantPreg);
 		cantidadPreguntasValida = maxPreguntas (cantJugadores*cantPreg, sizeTotalPreguntas);
 	}

 	RealizarPreguntasMultijugador(multijugadores, cantPreg, cantJugadores);
 	//Comprobar si se han producido empates. Solo se desharan los empates si se dan entre quienes hayan ganado
 	
	 do
	 {
	 	sizeEmpatados = 0;
	 	puntMaxima = maxPuntuacion(multijugadores, cantJugadores);

	 	for(int i=0; i<cantJugadores; i++)
	 	{
	 		if(multijugadores[i].puntuacion == puntMaxima)
	 		{
	 			sizeEmpatados++;
	 		}
	 	}

	 	if(sizeEmpatados > 1)
	 	{
	 		//si hay empate, damos la opcion de desempatar opcion de desmpatar
	 		//1.- Recoger los jugadores que han empatado 
	 		t_jugador empatados[sizeEmpatados];
	 		int c = 0;
	 		//De todos los jugadores, metemos en el array los que hayan empatado como ganadores
	 		for(int i=0; i<cantJugadores; i++)
	 		{
	 			if(multijugadores[i].puntuacion == puntMaxima)
				{
					empatados[c] = multijugadores[i];
					c++;
				}
	 		}
	 		mensajeEmpate(empatados, sizeEmpatados, &opcion);
	 		
	 		if(opcion ==1)
	 		{
	 			//Realizamos una sola pregunta entre los jugadores que han empatado para ver si asi deshacen el empate
		 		RealizarPreguntasMultijugador(empatados, 1, sizeEmpatados);
		 		c=0;
		 		for (int i = 0; i < cantJugadores; ++i)
		 		{
		 			if(strcmp(multijugadores[i].nick, empatados[c].nick)==0)
		 			{
		 				multijugadores[i].puntuacion = empatados[c].puntuacion;
		 				c++;
		 			}
		 		}
	 		}
	 		else
	 		{
	 			sizeEmpatados = 1;
	 		}
	 	}	 	
	 }
	 while(sizeEmpatados != 1);//No hay empate
	 //Si habia empate, ya se ha resuelto si asi se ha querido. 
	 //Si no se resolvio, se mostrara un mensaje de ganador por cada uno. Por lo tanto, lo hacemos en un for:
	 	for(int i=0; i<cantJugadores; i++)
	 	{
	 		if(multijugadores[i].puntuacion == puntMaxima)
	 		{
	 			mensajeGanador(multijugadores[i]);
	 		}
	 		listaTodosJugadores = actualizarPuntuacion(listaTodosJugadores, numJugadores, &multijugadores[i], 1);
	 	}

	  for (int i=0; i<cantJugadores; i++)
	 {
	 	multijugadores[i].puntuacion = 0;
	 }

	 //Volver al menu o volver a jugar
	 mostrarMensaje("Fin de la partida\n  Deseas volver a jugar o regresar al menu?\n");
	 mostrarMensaje("1.- Volver a jugar\n");
	 mostrarMensaje("2.- Volver al menu\n");
	 mostrarMensaje("Introduce la opcion deseada:  ");
	 recogerInt (&opcion);

	 while(opcion != 1 && opcion != 2)
	 {
	 	 mostrarMensaje("\nLa opcion introducida no es valida. Por favor, intentalo de nuevo:  ");
	 	 recogerInt (&opcion);
	 }

	 if(opcion == 1)
	 {
	 	multijugador();
	 }
	 else
	 {
	 	menuJugador();
	 }
 }

 void RealizarPreguntasMultijugador(t_jugador* multijugadores, int cantPreg, int cantJugadores)
 {
 	int cont=0;
 	int respValida=-1;
 	int random;//variable en la que guardaremos el numero aleatorio para elegir una pregunta aleatoria
 	int repetida = 0; //Variable para ver si en cada momento la pregunta elegida aleatoriamente es i no alguna que ya ha salido
 	t_pregunta_respuestas pregunta;
 	char respuesta;
 	int correcta=0;

 	for(int i=0; i<cantPreg; i++)
 	{
 		for(int j=0; j<cantJugadores; j++)
 		{
 			mostrarMensaje("\nPregunta para el jugador #");mostrarInt(j+1);mostrarMensaje("->"); mostrarMensaje(multijugadores[j].nick);
 			//Preparar la pregunta aleatoria para el jugador
 			pregunta = generarPregunta (arrPreg, &preguntasSalidas, &sizePreguntasSalidas, sizeTotalPreguntas);

			 mostrarPregunta(pregunta);
			 mostrarRespuestas(pregunta);
			 respValida = recogerRespuesta(&respuesta);

			 while(respValida == -1)
			 {
			 	 respValida = recogerRespuesta(&respuesta);
			 }
			
			switch (respuesta)
			{
			case 'a':
				correcta = comprobarRespuesta(pregunta.Respuesta1);
			break;

			case 'b':
				correcta = comprobarRespuesta(pregunta.Respuesta2);
			break;

			case 'c':
				correcta = comprobarRespuesta(pregunta.Respuesta3);
			break;
			}

		if(correcta == 1)
		 {
		 	mostrarMensaje("Respuesta correcta\n");
		 	sumarPunto(&multijugadores[j]);
		 }
		 else
		 {
		 	mostrarMensaje("Respuesta incorrecta\n");
		 }
 		}
 	}

 }

  void ranking()
 {
 	ordenarJugadores(listaTodosJugadores, (*numJugadores));

 	mostrarMensaje("\n\nRANKING DE JUGADORES");
 	for(int i=0; i < (*numJugadores); i++)
 	{
 		mostrarMensaje("\n");
 		mostrarInt(i+1);
 		mostrarMensaje(".-");
 		mostrarPuntuacion(listaTodosJugadores[i]);
 	}
 		mostrarMensaje("\n\n");
	 menuJugador();
 }

 void acabar()//metodo para liberar recursos
 {
 	free(preguntasSalidas);
 	preguntasSalidas = NULL;
 	
 	free(arrPreg);
 	arrPreg = NULL;

 	guardarJugadores(listaTodosJugadores, (*numJugadores));

 	free(listaTodosJugadores);
 	listaTodosJugadores = NULL;
 }