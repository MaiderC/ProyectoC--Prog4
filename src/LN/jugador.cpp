#include "jugador.h"
#include "../LD/DBConnector.h"

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

//sobrecarga de operadores
bool operator==(const jugador& jug)
{
  bool retorno;

  retorno=this -> puntuacion == jug.puntuacion;

  return retorno;
}

bool operator<(const jugador& jug)
{
  bool retorno;

  retorno=this -> puntuacion < jug.puntuacion;

  return retorno;
}

bool operator>(const jugador& jug)
{
  bool retorno;

  retorno=this -> puntuacion > jug.puntuacion;

  return retorno;
}

bool operator!=(const jugador& jug)
{
  bool retorno;

  retorno=this -> puntuacion != jug.puntuacion;

  return retorno;
}

bool operator=(const jugador& jug)
{
  this -> nick = j.nick;
  this -> puntuacion = j.puntuacion;
}

ostream& operator<<(ostream& out, const jugador& jugador)
{
  out << jugador.nick << ": "<< jugador.puntuacion << endl;

  return out;
}

istream& operator>>(istream& in, jugador& jugador)
{
  mostrarMensaje( "Indica el nick del jugador: ");

  in >> jugador.nick;
  
  return in;
}
