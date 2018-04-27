#ifndef JUGADOR_H
#define JUGADOR_H

typedef struct
{
	char nick[50];
	int puntuacion;

} t_jugador;

t_jugador crearJugador(char* Nick);
void sumarPunto(t_jugador* Jugador);
int existeJugador(t_jugador* listaJugadores, char* Nick); // No creo que este deba estar aquí...
t_jugador* actualizarPuntuacion(t_jugador* listaTodosJugadores, int* numTodos, t_jugador* listaJugadoresSesion, int numElem);

#endif