//MODULO MAIN (PRINCIPAL)
#include "ListaSudokus.h" //Acceso al modulo de listaSudokus que tiene acceso al resto de modulos, como una cadena
#include "ListaJugadores.h" //Acceso al modulo de listaJugadores que tiene acceso al de jugador
#include "checkML.h" //Acceso al detector de fugas de memoria

using namespace std;

//Funciones que se encuentran debajo del main y asi tiene acceso a estas la funcion main()
int menu();
int leerOpcion();
int volverJugar();

void opcion1(const tListaSudokus & lista, tListaJugadores & jugadores, int &opcion);
void opcion2(const tListaJugadores & jugadores);
void opcion3(const tListaJugadores & jugadores);
void opcion4(tListaSudokus & lista);

int main() 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	int opcion;
	bool ok = true;
	tListaSudokus lista;
	tListaJugadores jugadores;

	if (cargar(lista) && cargar(jugadores)) //Si se carga la lista de sudokus y jugadores se podra elegir una opcion del menu, sino acabará el programa
	{
		ordena(jugadores);  //Ordena la lista por si estuviera desordenada
		opcion = menu(); //Llama al menu, y devuelve un entero
		system("cls"); //Limpia la pantalla mostrada al jugador
		while (opcion != 0) //Bucle que finaliza al indicar que se acaba el juego, poniendo un 0 en la varible opcion
		{
			if (opcion == 1) //Opcion de jugar un sudoku
			{
				opcion1(lista, jugadores, opcion);
			}
			else if (opcion == 2) //Opcion para ver los jugadores ordenados por el nombre
			{
				opcion2(jugadores);
			}
			else if (opcion == 3)  //Opcion para ver los jugadores ordenados por el puntos
			{
				opcion3(jugadores);
			}
			else //Opcion que registra un sudoku
			{
				opcion4(lista);
			}

			system("cls");
			if (opcion != 0) { //Si opcion es distinta de 0 mostrará el menu, la opcion solo puede haber cambiado despues de haber jugado un sudoku previamente
				opcion = menu();
				system("cls");
			}
		}

	}
	ok = guardar(jugadores); //Guarda en un fichero la nueva lista de jugadores
	if (ok == false){ //Si no se ha podido guardar lo muestra por pantalla
		cout << "\nNo se ha podido guardar el jugador" << endl;
		system("pause");
	}
	borrarListaJugadores(jugadores);
	return 0;
}

//Muestra un menu y devuelve un entero indicando la opcion seleccionada
int menu()
{
	int opcion;
	cout << "1.- Jugar " << endl;
	cout << "2.- Ver jugadores ordenados por identificador" << endl;
	cout << "3.- Ver jugadores ordenados por puntos " << endl;
	cout << "4.- Incorporar sudoku " << endl;
	cout << "0.- Salir\n " << endl;
	opcion = leerOpcion();

	return opcion;
}

//Esta funcion se encarga de revisar el valor de selecion se encrentre entre un rango determindo
//Si no es asi mostrará un mensaje por pantalla y te pedirá que vuelvas a introducir tu selecion
int leerOpcion()
{
	int opcion;
	cin >> opcion;
	while (opcion < 0 || opcion>4)
	{
		cout << "\nTe has equivocado, vuelve a introducir" << endl;
		cin >> opcion;
	}
	return opcion;
}

//Menu auxiliar que indica si quiere el jugador seguir jugando, de tal modo que si es 1, volvera al menu inicial
//sino se acabará el programa
int volverJugar()
{
	int opcion;
	cout << "\nQuieres volver a jugar?" << endl;
	cout << "1.- Volver a menu" << endl;
	cout << "0.- Salir\n " << endl;
	cin >> opcion;
	while (opcion < 0 || opcion>1) { //si la opcion no esta entre un rango determinado mostrará un mensaje por pantalla y te pedira otra vez la opcion
		cout << "Opcion erronea, vuelve a introducir : " << endl;
		cin >> opcion;
	}
	return opcion;
}

//Hace todas las funciones de la opcion 1
void opcion1(const tListaSudokus & lista, tListaJugadores & jugadores, int &opcion)
{
	int puntos;
	tSudoku sudoku;
	system("cls");
	mostrar(lista); //Muestra por pantalla todos los sudokus
	elegirSudoku(sudoku, lista);  //Te pide que elijas uno de ellos
	system("cls");
	puntos = jugarUnSudoku(sudoku); //Llamada a la funcion de jugar que devuelve los puntos del sudoku en funcion de si se ha rellenado o abortado
	system("cls");
	cout << "\nHas obtenido " << puntos << " punto(s)" << endl;  //Muestra por pantalla los puntos obtenidos
	puntuarJugador(jugadores, puntos); //Modifica los puntos del jugador
	opcion = volverJugar(); //Llama al menu auxiliar
}

//Hace todas las funciones de la opcion 2
void opcion2(const tListaJugadores & jugadores)
{
	system("cls");
	tListaJugadores porId; //Nueva lista para la ordenacion por nombre
	hacercopia(jugadores, porId); //Hace un a copia de la lista original
	mostrar(ordenarPorId(jugadores)); //Muestra los jugadores
	borrarListaJugadores(porId); //borra la copia de la lista original, para liberar memoria
	system("pause");
}

//Hace todas las funciones de la opcion 3
void opcion3(const tListaJugadores & jugadores)
{
	system("cls");
	tListaJugadores porRanking; //Nueva lista para la ordenacion por puntos
	hacercopia(jugadores, porRanking); //Hace un a copia de la lista original
	mostrar(ordenarPorRanking(porRanking)); //Muestra los jugadores
	borrarListaJugadores(porRanking); //borra la copia de la lista original, para liberar memoria
	system("pause");
}

//Hace todas las funciones de la opcion 4
void opcion4(tListaSudokus & lista) 
{
	if (registrarSudoku(lista) == true) {//Si se guarda lo indica, sino tambien ya que lo hace otra funcion
		cout << "Registrado" << endl;
		system("pause");
	}
}