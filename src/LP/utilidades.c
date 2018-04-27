#include "../INCLUDES/utilidades.h"

void mostrarMensaje(char* str)
{
	printf("%s",str );
}

void mostrarInt(int i)
{
	printf("%i",i );
}

//--Compilan, pero habra que probarlos cuando sus clases esten hechas
void mostrarPregunta(t_pregunta_respuestas preg)
{
	printf("\n%s\n", preg.Pregunta);
}

void mostrarRespuestas(t_pregunta_respuestas preg)
{
	printf("a) ");
	if(preg.Respuesta1[0] == '#')
	{
		for(int i = 1; i < strlen(preg.Respuesta1); i++)
		{
			putchar(preg.Respuesta1[i]);
		}
		printf("\n");
	} else
	{
		printf("%s\n", preg.Respuesta1 );
	}

	printf("b) ");
	if(preg.Respuesta2[0] == '#')
	{
		for(int i = 1; i < strlen(preg.Respuesta2); i++)
		{
			putchar(preg.Respuesta2[i]);
		}
		printf("\n");
	} else
	{
		printf("%s\n", preg.Respuesta2);
	}

	printf("c) ");
	if(preg.Respuesta3[0] == '#')
	{
		for(int i = 1; i < strlen(preg.Respuesta3); i++)
		{
			putchar(preg.Respuesta3[i]);
		}
		printf("\n");
	} else
	{
		printf("%s\n", preg.Respuesta3);
	}
	printf("Indica la repuesta que consideras correcta (a, b o c):  ");
}

void mostrarPuntuacion(t_jugador jugador)
{
	printf("%s : %i puntos\n", jugador.nick, jugador.puntuacion );
}
void mensajeGanador(t_jugador ganador) //A este metodo se le llamara antes de actualizar las puntuaciones, con lo que la puntuación sera la acumulada en esa partida
{
	printf("El jugador ganador de esta partida ha sido %s con %i puntos. Enhorabuena! \n", ganador.nick, ganador.puntuacion );
}

void mensajeEmpate(t_jugador* empatados, int sizeEmpatados, int *opcion)//Recibe una lista con los jugadores que han empatado
{
	char* nicks_empate;

	printf("\nSe ha producido un empate entre %i jugadores con %i puntos ", sizeEmpatados , empatados[0].puntuacion);

	for(int i=0; i < sizeEmpatados; i++ )
	{
		printf("%s\n", empatados[i].nick);
	}
	printf("Si deseas desempatar pulsa 1\nSi deseas finalizar la partida con empate pulsa 2\n");
	recogerInt(opcion);
}
//-----------------------------------------------------------------

// Al usar los siguientes metodos, como parametro pasar &variable--------------
void recogerString (char** punt_string, int max_long)
{
	char str[max_long];
	char str_sin_salto_linea[max_long];
	fgets(str, max_long, stdin);

	clear_if_needed(str);
	sscanf(str, "%[^\n]", str_sin_salto_linea); //eliminar el \n final
	
	//reservar solo el espacio necesario para el string
    (*punt_string) = (char *)malloc((strlen(str_sin_salto_linea)) * sizeof(char)); //El último espacio sera para el \0
    strcpy((*punt_string), str_sin_salto_linea );
}

void recogerNick (char** punt_nick)
{
	printf("\n Indica el nick del jugador: \n");
	recogerString(punt_nick, 20);//los nicks tendran un maximo de 20 caracteres
}

void recogerInt (int* punt_numero)
{
	char str[1000];
	fgets(str, 1000, stdin);
	clear_if_needed(str);
	sscanf(str, "%d", punt_numero); //eliminar el \n final
}


/*
El metodo recibe la variable en la que guardaremos el resultado introducido por el usuario (a, b o c, ya que todas las preguntas tendran tres opciones)
Devolverá un int indicando si la opción introducida concuerda con alguna de las tres letras (0: si es una respuesta posible, -1: si es una respuesta no posible)
*/
int recogerRespuesta (char* respuesta) 
{
	int error=0;
	char str[1000];
	fgets(str, 1000, stdin);
	clear_if_needed(str);
	sscanf(str, "%c", respuesta);
	
	if((*respuesta)!='a' && (*respuesta)!='b' && (*respuesta)!='c') 
	{
		printf("La respuesta no es valida. Por favor, introduce una opción valida (a, b o c) \n");
		error=-1;
	}
	return error;
}

//-----------------------------

/**
	Esta funcion elimina los caracteres pendientes si es necesario
	Se usa junto con fgets para leer la entrada hasta cierta longitud
*/
void clear_if_needed(char *str)
{
	if (str[strlen(str) - 1] != '\n')
	{
		int c;    
    	while ( (c = getchar()) != EOF && c != '\n');//Como leemos de teclado, usamos getchar (de fichero fgetc)
    }
}