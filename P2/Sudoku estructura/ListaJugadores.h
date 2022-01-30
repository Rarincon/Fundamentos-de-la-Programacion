//MODULO LISTAJUGADORES
#ifndef ListaJugadores_h
#define ListaJugadores_h
#include "jugador.h" //biblioteca para acceder al modulo de jugador
#include <iostream> //biblioteca parar poder mostrar y escribir por pantalla
#include <iomanip> //biblioteca para poder especirficar unas coordenadas en la pantalla (setw())
#include <fstream> //biblioteca para poder leer y escribir en un fichero
#include "checkML.h" //Acceso al detector de fugas de memoria

const int MAX_JUGADORES = 5; //Una constante de enteros, que no puede ser modificada, excepto donde se declara
//Se utilizara para dar un tamaña inicial a un array dinamico, pero luego su tamaño podra aumentar

//Lista con un contador y el array dinamico de jugadores, el contador indica cuanto jugadores hay
//y el tamño, el tamaño del array dinamico
typedef struct
{
	tJugadorPtr* jugador; //Llamada al puntero de jugador
	int cont;
	int tam;
}tListaJugadores;

void creaListaVacia(tListaJugadores & lista);
bool cargar(tListaJugadores & lista);
void mostrar(const tListaJugadores & lista);
bool guardar(const tListaJugadores & lista);
void puntuarJugador(tListaJugadores & lista, int puntos);
bool buscar(const tListaJugadores & lista, std::string id, int ini, int fin, int &pos);
tListaJugadores ordenarPorRanking(const tListaJugadores &lista);

tListaJugadores ordenarPorId(const tListaJugadores &lista);

//Version 3

void ampliar(tListaJugadores & lista);
void borrarListaJugadores(tListaJugadores & lista);

void hacercopia(const tListaJugadores & lista, tListaJugadores & copia);
void ordena(tListaJugadores & lista);

#endif 


//Mirar cuando liberar la memoria