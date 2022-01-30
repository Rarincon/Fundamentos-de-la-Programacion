//juego.cpp
#include "juego.h"

using namespace std;

//Inicia el juego, agregando al juego que sudoku quiere, estableciendo que no se ha rellendado el sudoku
//e iniciando el tablero(funcion del mouduoo de tablero)
void iniciaJuego(tJuego & juego, const tSudoku & sudoku)
{
	juego.sudoku = sudoku;
	juego.relleno = false;
	iniciaTablero(juego.tablero);
}

//Muestra por pantalla el tablero, con las casillas rellenadas, fijas o vacias
void mostrarJuego(const tJuego & juego)
{
	dibujarTablero(juego.tablero);
}

//Se encarga de iniciar el juego, y de cargar en el tablero el sudoku seleccionado, de no ser asi, esta funcion devuelve un false
bool cargaJuego(tJuego & juego, const tSudoku & sudoku)
{
	iniciaJuego(juego, sudoku);
	return cargarTablero(juego.sudoku.nombreFichero, juego.tablero);
}

//Muestra por pantalla un menu con las opciones posibles
void elegirOpcion(tJuego & juego, bool & abortar)
{
	int opcion;
	cout << " 1. Ver posibles valores de una casilla vacia" << endl;
	cout << " 2. Colocar valor en una casilla" << endl;
	cout << " 3. Borrar valor de una casilla" << endl;
	cout << " 4. Reiniciar el tablero" << endl;
	cout << " 5. Autocompletar celdas simples" << endl;
	cout << " 0. Abortar la resolucion y volver al menu principal\n" << endl;
	cin >> opcion;
	while (opcion < 0 || opcion >5)//Condicion que si el valor de la opcion no esta entre el rango determinado se volvera a mostrar el menu
	{
		cout << "\nEsa opcion no es valida, vuelve a elegir: ";
		cin >> opcion;
	}
	if (opcion == 0)//Si la opcion es 0 se acabara el juego, pues se ha rendido el jugador y no recibira puntos
		abortar = true;
	else if (opcion == 4)//Si la opcion es 4 reseteará todas las casillas y el tablero, al inicia del juego
		resetJuego(juego);
	else				//Si no es ninguna de las opciones anteriores, pasará a la funcion de actualizar el tablero, que esta en el modulo tablero
		actualizarTablero(juego.tablero, opcion);
	if (tableroLleno(juego.tablero) == true) //Si el tablero esta relleno cambiará a true el valor de juego.relleno, acabando asi la partidas
		juego.relleno = true;
}

//Se encarga de devolver los puntos del sudoku si ha sido rellenado, sino devuelve un cero
int jugarUnSudoku(const tSudoku & sudoku) 
{
	tJuego juego;
	bool abortar = false;
	if (cargaJuego(juego, sudoku))
	{
		while (juego.relleno == false && abortar == false) // Bucle del juego, hasta que el sudoku sea rellenado o se rinda el jugador
		{
			system("cls");
			mostrarJuego(juego);
			elegirOpcion(juego, abortar);
		}
		if (juego.relleno == true && abortar == false)//En funcion de si se ha rendido o ha sido rellernado devuelve una cosa u otra
			return sudoku.puntos;
		else
			return 0;
	}
	else {//En funcion de si se ha rendido o ha sido rellernado devuelve una cosa u otra
		return 0;
	}
}

//Se encarga de reiniciar el tablero del juego, reiniciadno todas los valores de las casillas como si estuvieran al inicia del juego
void resetJuego(tJuego &juego)
{
	iniciaTablero(juego.tablero);
	cargarTablero(juego.sudoku.nombreFichero, juego.tablero);
}
