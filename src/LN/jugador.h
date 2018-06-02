#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
#include <string.h>

using namespace std;

class jugador
{
	private:

		string nick;
		int puntuacion;

	public:

	jugador();
	jugador(string nick, int puntuacion);

	~jugador();

	jugador(const jugador &j);

	void setNick (string nick);
	void setPuntuacion(int puntuacion);

	string getNick() const;
	int getPuntuacion() const;

	bool operator==(const jugador& jug);
	bool operator<(const jugador& jug);
	bool operator>(const jugador& jug);
	bool operator!=(const jugador& jug);
	bool operator=(const jugador& jug);
	
	friend ostream& operator<<(ostream& out, const jugador& jug);
	friend istream& operator>>(istream& in, jugador& jug);
};

#endif