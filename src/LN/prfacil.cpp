#include "prfacil.h"

// #include <iostream>
// using namespace std;


#define DEFAULT_RESPUESTA2 defaultAnswer2
#define DEFAULT_DIFICULTAD #


//constructores
prfacil::preguntas_respuestas()
{
  this -> respuesta2 = DEFAULT_RESPUESTA2;
}
		
prfacil::preguntas_respuestas(string pregunta, string respuesta1, string respuesta2, string dificultad): preguntas_respuestas(pregunta, respuesta1, dificultad)
{
  this -> respuesta2 = respuesta2;
}

//destructor
 prfacil::~preguntas_respuestas()
{
   delete respuesta2;
}

//constructor copia
prfacil::prfacil(const prfacil &pf): preguntas_respuestas(pf)
{
	this -> respuesta2 = pf.respuesta2;
}

//getter y setter
void prfacil::setRespuesta2(string RDos)
{
	this -> respuesta2 = RDos;
}

string prfacil::getRespuesta2() const
{
	return respuesta2;
}

//métodos

 void prfacil::sumarPunto(jugador jugador)
{
	jugador.puntuacion =+ 1;
}

 void prfacil::prepararRespuestas(preguntas_respuestas pregunta, string facil)
{
	int i = 1;
	int igual = 0;
	int r;
	int random[2];

	//array de respuestas auxiliares 
	string respuestas[2];

	random[0] = -1;
	random[1] = -1;
	// random[2] = -1;
 	
	// Este while llena el array random con números aleatorios de 0 a 2, pero que no se repitan.
	while(i>=0)
	{
		igual = 0;
		r = rand() % 2;

		for(int j = 0; j<2; j++)
		{
			if(r == random[j])
				igual = 1;
		}

		if(igual == 0)
		{
			random[i] = r;
			i--;
		}
	}

	respuestas[random[0]] = this -> respuesta1;
	respuestas[random[1]] = this -> respuesta2;
		
	this -> respuesta1 = respuestas[0];
	this -> respuesta2 = respuestas[1];
}

bool prfacil::operator=(const prfacil& pf)
{
	this -> respuesta2 = pf.respuesta2;
}

ostream& operator<<(ostream& out, const preguntas_respuestas& Pregunta)
{
	out << Pregunta.pregunta << endl;

	out << "a) ";
	if((Pregunta.respuesta1.c_str())[0] == '#')
	{
		string aux = Pregunta.respuesta1;

		aux.erase(0, 1);

		out << aux << endl;
	} else
	{
		out << Pregunta.respuesta1 << endl;
	}

	out << "b) ";
	if((Pregunta.respuesta2.c_str())[0] == '#')
	{
		string aux = Pregunta.respuesta2;

		aux.erase(0, 1);

		out << aux << endl;
	} else
	{
		out << Pregunta.respuesta2 << endl;
	}

	return out;
}

istream& operator>>(istream& in, preguntas_respuestas& Pregunta)
{
	mostrarMensaje("Introduce la pregunta a insertar: ");
	in >> Pregunta.pregunta;

	mostrarMensaje("*La respuesta no debe contener la letra de la opcion (a o b) ni signos de puntuacion al inicio (salvo que se trate de un guion, por ser la respuesta un numero negativo)");
	mostrarMensaje("Introduce la respuesta correcta: ");
	in >> Pregunta.Respuesta1;

	Pregunta.respuesta1 = '#' + Pregunta.respuesta1;

	mostrarMensaje("Introduce otra respuesta (una incorrecta): ");
	in >> Pregunta.respuesta2;

	return in;
}