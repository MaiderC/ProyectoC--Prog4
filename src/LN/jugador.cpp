#include "jugador.h"
#include <iostream>
#include <string.h>

using namespace std;

#define DEFAULT_NICK "playerOne"
#define DEFAULT_PUNTUACION 0

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

jugador::~jugador ()
{
  
}

jugador::jugador(const jugador &j)
{
  this -> nick = j.nick;
  this -> puntuacion = j.puntuacion;
}

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

bool jugador:: operator==(const jugador& jug)
{
  bool retorno;

  retorno=this -> puntuacion == jug.puntuacion;

  return retorno;
}

bool jugador::operator<(const jugador& jug)
{
  bool retorno;

  retorno=this -> puntuacion < jug.puntuacion;

  return retorno;
}

bool jugador::operator>(const jugador& jug)
{
  bool retorno;

  retorno=this -> puntuacion > jug.puntuacion;

  return retorno;
}

bool jugador::operator!=(const jugador& jug)
{
  bool retorno;

  retorno=this -> puntuacion != jug.puntuacion;

  return retorno;
}

bool jugador::operator=(const jugador& jug)
{
  this -> nick = jug.nick;
  this -> puntuacion = jug.puntuacion;
}

ostream& operator<< (ostream& out, const jugador& jug)
{
  out << jug.nick << ": "<< jug.puntuacion << endl;

  return out;
}

istream& operator>>(istream& in, jugador& jug)
{
  cout << "Indica el nick del jugador: ";

  in >> jug.nick;
  
  return in;
}
