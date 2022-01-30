//MODULO JUEGO
#ifndef juego_h
#define juego_h
#include "tablero.h"//Biblioteca para acceder al modulo tablero

//Lista que guarda el nombre de un sudoku y los puntos de este
typedef struct {
	std::string nombreFichero; //String que guarda el nombre, se pone el std:: ya que no se ha usado el using namespace std;
	int puntos;
}tSudoku;

//Lista del juego que tiene una lista con el nombre del sudoku a jugar y sus puntos
//El tablero para jugar, y un bool que cambia si el tablero esta rellenado a true, ya que este se inicilizara con false
typedef struct {
	tSudoku sudoku;
	tTablero tablero;
	bool relleno;
}tJuego;

//Llamadas a funciones
void iniciaJuego(tJuego & juego, const tSudoku & sudoku);
void mostrarJuego(const tJuego & juego);
bool cargaJuego(tJuego & juego, const tSudoku & sudoku);
int jugarUnSudoku(const tSudoku & sudoku);

void elegirOpcion(tJuego & juego, bool & abortar);
void resetJuego(tJuego & juego);
#endif
