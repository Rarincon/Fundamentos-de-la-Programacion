//MODULO JUGADOR
#ifndef jugador_h
#define jugador_h
#include <string> //biblioteca parar usar strings
#include "checkML.h" //biblioteca que revisa si se ha quedado memoria sin liberar

//Lista que contiene un string y un entero para cada jugador
typedef struct {
	std::string identificador; //Nombre del jugador
	int puntuacion; //Los puntos que contiene este
}tJugador;

typedef tJugador * tJugadorPtr; //Puntero de la lista de jugador

//Llamada a funciones
std::string toString(tJugadorPtr jugador);
void modificarJugador(tJugadorPtr & jugador, int puntos);
bool operator<(const tJugador & opIzq, const tJugador & opDer);
bool menor(const tJugadorPtr & j1, const tJugadorPtr & j2);

void annadirJugador(tJugadorPtr & jugador, std::string newjugador);
bool mayor(const tJugadorPtr & j1, const tJugadorPtr & j2);
std::string toString2(tJugadorPtr jugador);//Es duplicado, del primer string, pero realiza una funcion un poco distinta
//para una posible visualizacion por pantalla distinta de la normal

#endif
