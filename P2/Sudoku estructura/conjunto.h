//MODULO CONJUNTO
#ifndef conjunto_h
#define conjunto_h
#include <iostream> //Biblioteca para poder escribir por pantalla

int const DIMENSION = 9;//Una constante de enteros, que no puede ser modificada, excepto donde se declara

typedef bool tElementos[DIMENSION];//Array de booleanos, de tamaño la dimension, que es 9
//Lista que engloba el array de booleanos y una variable de enteros
typedef struct {
	int nElemns; //Sera nuestro "contador", para saber cuantos true hay en el array
	tElementos elementos;//Cada true es un numero que se encuentra en el conjunto
}tConjunto;

//Llamadas a las funciones, cuando el programa llama a una de estas funciones viene al modulo y luego pasa al cpp
void cjto_vacio(tConjunto & c);
void cjto_lleno(tConjunto & c);
bool pertenece(const tConjunto & c, int e);
void annadeElemento(tConjunto & c, int e);
void borraElemento(tConjunto & c, int e);
int numElems(const tConjunto & c);
bool esUnitario(const tConjunto & c, int & e);
void mostrar(const tConjunto & c);
#endif
