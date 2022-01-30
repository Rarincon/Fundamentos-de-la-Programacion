//MODULO LISTASUDOKUS
#ifndef ListaSudokus_h
#define ListaSudokus_h
#include "juego.h"//Biblioteca para acceso al modulo juego
#include <iomanip>//Biblioteca para poder usar coordenadadas de colocacion en la pantalla a mostrar(los setw())
#include <string>//Biblioteca para poder leer palabras de un fichero

int const MAX_SUDOKUS = 20;//constante de un entero de valor 20 

typedef tSudoku tTablaSudoku[MAX_SUDOKUS];//Array de lista de sudokus de tamaño 20
//Lista con la tabla de sudokus, y un contador con la cantidad de sudokus que hay
typedef struct
{
	tTablaSudoku tabla_sudoku;
	int cont;
}tListaSudokus;

//Llamada a funciones
void creaListaVacia(tListaSudokus & lista);
bool cargar(tListaSudokus & lista);
void mostrar(const tListaSudokus & lista);
void elegirSudoku(tSudoku & sudoku, const tListaSudokus & lista);


//VERSION 2

bool guardar(const tListaSudokus & lista);
bool registrarSudoku(tListaSudokus & lista);
bool buscarFichero(const tListaSudokus & lista, std::string nombreFich);
int buscarPos(const tListaSudokus & lista, const tSudoku &sudoku);

void ordenarLista(tListaSudokus &lista, const tSudoku &sudoku);
void desplazar(tListaSudokus &lista, int pos);
#endif