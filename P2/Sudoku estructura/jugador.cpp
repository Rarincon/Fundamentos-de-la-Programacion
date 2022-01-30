//jugador.cpp

#include "jugador.h" //Tiene acceso al modulo de jugador
#include "checkML.h" //Acceso al detector de fugas de memoria

using namespace std;

//Devuelve un string con el nombre de un jugador
string toString(tJugadorPtr jugador) {
	string texto;
	texto += jugador->identificador;
	return texto;
}

//Devuelve un string con los puntos de un jugador
string toString2(tJugadorPtr jugador)
{
	string texto;
	texto += to_string(jugador->puntuacion); //transforma un entero en un string
	return texto;
}


//Modifica los puntos de un jugador, sumandole a los puntos ya existentes el numero que contiene la variable puntos
void modificarJugador(tJugadorPtr & jugador, int puntos) { 
	jugador->puntuacion += puntos;
}

//Devuelde TRUE si se cumple la condicion, utlizado para la ordenacion
bool operator<(const tJugador & opIzq, const tJugador & opDer) {
	if (opIzq.puntuacion == opDer.puntuacion) return opIzq.identificador > opDer.identificador;
	else return opIzq.puntuacion < opDer.puntuacion;
}

//Comprueba si cual de los dos datos recibidos es menor, si se cumple la condicion devuelve true
//Si los puntos son iguales compara los identificadores
bool menor(const tJugadorPtr & j1, const tJugadorPtr & j2) {
	bool ok = false;
	if (j1->puntuacion < j2->puntuacion || (j1->puntuacion == j2->puntuacion && j2->identificador < j1->identificador))
		ok = true;
	return ok;
}

//Comprueba si cual de los dos datos recibidos es mayor, si se cumple la condicion devuelve true
//Si los identificadores son iguales compara los puntos
bool mayor(const tJugadorPtr & j1, const tJugadorPtr & j2)
{
	bool ok = false;
	if (j1->identificador > j2->identificador || (j1->identificador == j2->identificador && j2->puntuacion > j1->puntuacion))
		ok = true;
	return ok;
}

//Añade un nuevo jugador a la lista de jugador, poniendo sus puntos a cero
void annadirJugador(tJugadorPtr & jugador, string newjugador)
{
	jugador = new tJugador; //Crea un puntero para el nuevo jugador
	jugador->identificador = newjugador; //Añade al nuevo jugador
	jugador->puntuacion = 0; //Pone sus puntos a cero
}