#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>

using namespace std;

class jugador
{
	private:

		string nick;
		int puntuacion;

	public:

	//constructores
	jugador();
	jugador(string nick, int puntuacion);

	//destructor
	~jugador();

	//constructor copia
	jugador(const jugador &j);

	//getters y setters
	void setNick (string nick);
	void setPuntuacion(int punt);

	string getNick() const;
	int getPuntuacion() const;

	//metodos
	
	// void sumar_puntos(jugador j, string dificultad);
	// int existeJugador(jugador* listaJugadores, char* Nick); 

	//Sobrecarga de operadores
	bool operator==(const jugador& jug);
	bool operator<(const jugador& jug);
	bool operator>(const jugador& jug);
	bool operator!=(const jugador& jug);
	bool operator=(const jugador& jug);
	
	// Sobrecarga E/S
	friend ostream& operator<<(ostream& out, const jugador& jug);
	friend istream& operator>>(istream& in, jugador& jug);

};

#endif