#include "../INCLUDES/jugador.h"
#include "../INCLUDES/data.h"
#include <string.h>
#include <stdlib.h>

t_jugador crearJugador(char* Nick)
{
	t_jugador Jugador;
	strcpy(Jugador.nick, Nick);
	Jugador.puntuacion = 0;

	return Jugador;
}

void sumarPunto(t_jugador* Jugador)
{
	//(*(Jugador)).puntuacion += 1;
	Jugador->puntuacion += 1;
}

t_jugador* actualizarPuntuacion(t_jugador* listaTodosJugadores, int* numTodos, t_jugador* listaJugadoresSesion, int numElem)
{
    int coincidencias = 0;
   
    if((*numTodos) == 0)
    {
      listaTodosJugadores = (t_jugador*) malloc(numElem * sizeof(t_jugador));
      (*numTodos) = numElem;

      for (int i = 0; i < numElem; i++)
      {
        listaTodosJugadores[i] = listaJugadoresSesion[i];
      }

        return listaTodosJugadores;
    }
    else
    {
          for(int i = 0; i < (*numTodos); i++)
          {
                  for(int j = 0; j < numElem; j++)
                  {
                        if(strcmp((*(listaTodosJugadores + i)).nick, (*(listaJugadoresSesion + j)).nick) == 0)
                        {
                                coincidencias ++;
                        }
                  }
          }
    }
 
    if(coincidencias == 0)
    {
          //Todos los jugadores que han jugado ahora son nuevos -> no hay que actualizar puntuaciones:
                  //Hay que guardar todos los leídos tal cual
                  //Hay que guardar todos los pasados tal cual
        
          listaTodosJugadores = (t_jugador*) realloc(listaTodosJugadores, (*numTodos) * sizeof(t_jugador));

          //Llenamos la lista a guardar con el resto de jugadores, los que se han pasado por parámetro
          for(int i=0; i<numElem; i++)
          {
                  listaTodosJugadores[i + (*numTodos)] = listaJugadoresSesion[i];//Metemos los jugadores a partir de la posicion de la que dejamos de meter en el otro for
          }
          (*numTodos) = numElem + (*numTodos);
          return listaTodosJugadores;
 
    }
    else
    {
          //Si hay coincidencias, tendremos que usar la lista listaJugadoresSesionNoFich, ya que estos se meterán tal cual, mientras a los demás se les actualizará la puntuacion en listaFich
          //La lista a guardar ahora será más pequeña (ya que algunos jugadores están en ambas listas)
          //Hacemos dos mallocs, de la lista a guardar y la de los que no están en el fichero:
          //listaJugadoresSesionNoFich = (t_jugador*)malloc((numElem - coincidencias) * sizeof(t_jugador)); //hueco para todos los pasados menos los que están en el fichero
          listaTodosJugadores = (t_jugador*) realloc(listaTodosJugadores, ((*numTodos) + numElem - coincidencias) * sizeof(t_jugador)); //guardaremos la lista de fichero y la de no en fichero, por lo que sumamos los tamaños
            
          //int cont_noFich = 0;
          int coincidencia = -1;
          //Actualizamos puntuaciones y llenamos la lista de jugadores noEnfich:
          for(int i = 0; i < (*numTodos); i++)
          {
                  for(int j = 0; j < numElem; j++)
                  {
                      if(strcmp((*(listaTodosJugadores + i)).nick, (*(listaJugadoresSesion + j)).nick) == 0)
                        {
                          coincidencia = j;
                        }
                  }
                              
                            if(coincidencia != -1)
                            {
                                (*(listaTodosJugadores + i)).puntuacion += (*(listaJugadoresSesion + coincidencia)).puntuacion;
                                // Aquí empieza la solución
                                numElem--;
                                if(numElem > 0)
                                {
                                  t_jugador* auxLista = (t_jugador*) malloc(numElem * sizeof(t_jugador));
                                  int r2 = 0;
                                  for (int r1 = 0; r1 < numElem; ++i)
                                  {
                                      if(coincidencia == r1)
                                        r2++;
                                      auxLista[r1] = listaJugadoresSesion[r2];
                                      r2++;
                                  }
                                  
                                  listaJugadoresSesion = (t_jugador*) realloc(listaJugadoresSesion, numElem * sizeof(t_jugador));
                                  for (int r = 0; r < numElem; r++)
                                  {
                                      listaJugadoresSesion[r] = auxLista[r];
                                  }

                                  free(auxLista);
                                  auxLista = NULL;
                                }
                            }
                              coincidencia = -1;
                                // La solución llega hasta aquí
          }
          //Teniendo las dos listas preparadas, las metemos en la lista a guardar:
 
                  //Lllenamos el resto de la lista con los jugadores no leídos
                  for(int i=0; i<numElem; i++)
                  {
                        listaTodosJugadores[i + (*numTodos)]=listaJugadoresSesion[i];//Metemos los jugadores a partir de la posicion de la que dejamos de meter en el otro for
                  }

                  return listaTodosJugadores;
    }
}