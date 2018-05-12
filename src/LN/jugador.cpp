#include "../INCLUDES/jugador.h"
#include "../INCLUDES/data.h"
#include <iostream>

#define DEFAULT_NICK playerOne
#define DEFAULT_PUNTUACION 0

//contrsuctores
jugador::jugador ()
{
  this -> nick = DEFAULT_NICK;
  this -> puntuacion = DEFAULT_PUNTUACION;
}

jugador::jugador (string nick, int puntuacion)
{
  this -> nick = nick;
  this -> puntuacion = puntuacion;
}

//destructor
jugador::~jugador (string nick, int puntuacion)
{
  delete nick;
  delete puntuacion;
}

//constructor copia
jugador::jugador(const jugador &j)
{
  // this -> nick = new string;
  this -> nick = j.nick;
  this -> puntuacion = j.puntuacion;
}

//getters y setters
void jugador:: setNick(string nick)
{
  this -> nick = nick;
}
void jugador:: setPuntuacion(int puntuacion)
{
  this -> puntuacion = puntuacion;
}

string jugador:: getNick() const
{
  return nick;
}
int jugador:: getPuntuacion() const
{
  return puntuacion;
}

// jugador:: crearJugador(string Nick)
// {
// 	jugador Jugador= new jugador;
// 	strcpy(Jugador.nick, Nick);
// 	Jugador.puntuacion = 0;
// 	return Jugador;
// }

// sumar_puntos(jugador j, string dificultad) //se le pasará facil media o dificil
// {
//   //ver si viene de preguntas dificiles, medias o fáciles
//   if( dificultad="#")
//   {
//       j->puntuacion += 1;
//   }
//   else if (dificultad="##")
//   {
//       j->puntuacion += 2;
//   }
//   else  //dificultad ###
//   {
//       j->puntuacion += 3;
//   }
//   //-------------controlar si se ha metido algo que no sea 1# 2## o 3### ?????????????
// }


//prefiero no tocar nada de esto que la estoy liando:
jugador* actualizarPuntuacion(jugador* listaTodosJugadores, int* numTodos, jugador* listaJugadoresSesion, int numElem)
{
    int coincidencias = 0;
   
    if((*numTodos) == 0)
    {
      listaTodosJugadores = (jugador*) malloc(numElem * sizeof(jugador));
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
        
          listaTodosJugadores = (jugador*) realloc(listaTodosJugadores, (*numTodos) * sizeof(jugador));

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
          //listaJugadoresSesionNoFich = (jugador*)malloc((numElem - coincidencias) * sizeof(jugador)); //hueco para todos los pasados menos los que están en el fichero
          listaTodosJugadores = (jugador*) realloc(listaTodosJugadores, ((*numTodos) + numElem - coincidencias) * sizeof(jugador)); //guardaremos la lista de fichero y la de no en fichero, por lo que sumamos los tamaños
            
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
                        jugador* auxLista = (jugador*) malloc(numElem * sizeof(jugador));
                        int r2 = 0;
                       
                        for (int r1 = 0; r1 < numElem; ++i)
                        {
                            if(coincidencia == r1)
                              r2++;
                            auxLista[r1] = listaJugadoresSesion[r2];
                            r2++;
                        }
                        listaJugadoresSesion = (jugador*) realloc(listaJugadoresSesion, numElem * sizeof(jugador));
                       
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

bool operator<(const t_jugador& jugador)
{
  if(this->puntuacion < jugador.puntuacion)
  {
    return true;
  } else
  {
    return false;
  }
}

bool operator>(const t_jugador& jugador)
{
  if(this->puntuacion > jugador.puntuacion)
  {
    return true;
  } else
  {
    return false;
  }
}