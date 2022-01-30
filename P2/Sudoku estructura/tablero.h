//MODULO TABLERO
#ifndef tablero_h
#define tablero_h
#include <fstream>//Biblioteca para poder cargar datos de in fichero
#include "casilla.h"//Biblioteca para acceder al modulo de casilla,
//y este accede a conjunto, luego es una cadena

typedef tCasilla tTablero[DIMENSION][DIMENSION]; // Creacion de una matriz cuadrada, en cada casilla tiene la lista de casilla

//Llamada a funciones
void iniciaTablero(tTablero tablero);
bool cargarTablero(std::string nombreFichero, tTablero tablero);
void dibujarTablero(const tTablero tablero);
bool ponerNum(tTablero tablero, int fila, int col, int c);
bool borrarNum(tTablero tablero, int fila, int col);
bool tableroLleno(const tTablero tablero);
void mostrarPosibles(const tTablero tablero, int fila, int col);
void rellenarSimples(tTablero tablero);

//Funciones auxiliares, que no estaban en el enunciado
void annadirPosibles(tTablero tablero, int fila, int col);
bool revisaV(tTablero tablero, int fila, int numero);
bool revisaH(tTablero tablero, int col, int numero);
void borrarPosibles(tTablero tablero, int fila, int col);
void actualizarTablero(tTablero tablero, int opcion);
#endif

