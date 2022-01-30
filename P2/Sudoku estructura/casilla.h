//MODULO CASILLA
#ifndef casilla_h
#define casilla_h
#include "conjunto.h" //con est biblioteca este modulo tiene acceso al de conjunto
#include <Windows.h> //biblioteca para modificar el color de salida por pantalla

typedef enum { vacia, fija, rellenada }tEstado;//Enumerado
//Lista con un valor numero entero, un enumerado y una lista
//Cada casilla del tablero tendra toda esta lista
typedef struct {
	tEstado estado; //Enumerado
	int numero; //numero de la posicion
	tConjunto posibles; //Lista con los valores posibles de la casilla
}tCasilla;

//Lllamadas a las funciones, para que cuando tenga que buscar una venga a este modulo y luego pase al cpp
void iniciaCasilla(tCasilla & casilla);
void rellenaCasilla(tCasilla & casilla, char c, bool esfija = false);
void dibujaCasilla(const tCasilla & casilla);
bool esSimple(const tCasilla & casilla, int & numero);

void colorFondo(int color);
bool esVacia(const tCasilla & casilla);
bool esRellenada(const tCasilla & casilla);
bool esFija(const tCasilla & casilla);

void mostrarPosibles(const tCasilla & casilla);
void borrarCasilla(tCasilla &casilla);
void annadirPosibles(tCasilla & casilla, int numero);
void borrarPosibles(tCasilla &casilla, int numero);
bool perteneceC(tCasilla& casilla, int numero);
#endif
