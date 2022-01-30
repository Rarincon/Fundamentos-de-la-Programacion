//ListaSudokus.cpp
#include "ListaSudokus.h" //Biblioteca para acceder al modulo ListaSudokus

using namespace std;

//VERSIÓN 1 

//Recibe un lista de sudokus y la inicializa, poniendo el contador a 0, pues aun no hay sudokus
void creaListaVacia(tListaSudokus & lista)
{
	lista.cont = 0;
}

//Funcion booleana que devuelve true(a traves del ok) si se han podido cargar los sudokus de un fichero a la lista de Sudokus, sino devulve false
bool cargar(tListaSudokus & lista)
{
	bool ok = false;
	fstream fichero;
	creaListaVacia(lista);
	fichero.open("listaSudokus.txt"); //Abre un fichero
	if (fichero.is_open()) { //Comprueba que se ha podido abrir
		ok = true;
		for (int i = 0; i < MAX_SUDOKUS && fichero >> lista.tabla_sudoku[i].nombreFichero >> lista.tabla_sudoku[i].puntos; i++)
		{
			//Se pone ahi el paso del fichero a la lista, por si en el fichero hay una linea en la que no hay nada,
			//ya se habria puesto un espacio a la hora de guardar la listaSudokus
			//incrementando asi el contador al cargar otra vez
			//De esta forma leerá del fichero hasta que no haya mas palabras o numeros, o se se llene la lista de sudokus
			//Va pasando el nombre y los puntos a la lista, incremenetando el contador

			lista.cont++;
		}
	}
	else { //Si no se ha podido abrir el fichero mostrará un mensaje por pantalla
		cout << "No se ha podido abrir el fichero de la lista de sudokus\n" << endl;
		system("pause");
	}
	fichero.close(); //Cierra el fichero
	return ok;
}

//Muestra por pantalla en un a coordenada determinada( por el setw() ) los nombres de los sudokus y los puntos
void mostrar(const tListaSudokus & lista)
{
	int cont = 1;
	cout << setw(10) << "Niveles" << setw(30) << "Sudokus" << setw(45) << "Puntos" << endl;
	for (int i = 0; i < lista.cont; i++) {
		cout << setw(10) << "Nivel " << cont << setw(30) << lista.tabla_sudoku[i].nombreFichero << setw(45) << lista.tabla_sudoku[i].puntos << endl;
		cont++;
	}
}

//Esta funcion te da escoger de entre todos los sudokus existentes mostrardos por pantallas
void elegirSudoku(tSudoku & sudoku, const tListaSudokus & lista)
{
	int i;
	cout << "\nElige uno\n" << endl;
	cin >> i;
	while (i<1 || i>lista.cont) {
		cout << "Ese sudoku no es valido, vuelve a introducir" << endl;
		cin >> i;
	}
	sudoku.nombreFichero = lista.tabla_sudoku[i - 1].nombreFichero;
	sudoku.puntos = lista.tabla_sudoku[i - 1].puntos;
}


//VERSION 2

//Esta funcion se encarga de escribir en un fichero la lista de sudokus con los puntos de cada uno
bool guardar(const tListaSudokus & lista) {
	ofstream f;
	bool ok = false;
	f.open("listaSudokus.txt"); //Abre un fichero con ese nombre, o lo crea si no existe
	if (f.is_open()) {//Comprueba que se ha podido abrir
		ok = true;
		for (int i = 0; i < lista.cont; i++) { //Va escribiendo en el fichero todos los sudokus que esten en la lista
			f << lista.tabla_sudoku[i].nombreFichero << " " << to_string(lista.tabla_sudoku[i].puntos) << endl;
		}
	}
	else {//Si no se ha podido abrir el fichero se mostrará este mensaje por pantalla
		cout << "No se ha podido abrir el fichero de la lista de sudokus para guardarlo\n" << endl;
		system("pause");
	}
	f.close(); //Cierra el fichero
	return ok;
}

//Esta funcion agrega un sudoku nuevo a la lista de sudokus
//Para ello comprueba que no haya un sudoku con el mismo nombre
bool registrarSudoku(tListaSudokus & lista) {
	tSudoku sudoku;
	bool ok = false;
	int puntos = 0;
	string nom_fichero;
	cout << "Introduce el nombre del sudoku: " << endl;
	cin >> nom_fichero;
	cout << "Introduce los puntos del sudoku: " << endl;
	cin >> puntos;
	if (lista.cont != MAX_SUDOKUS) { //Comprueba que la lista no este llena
		if (buscarFichero(lista, nom_fichero) == true) { //Comprueba si no hay un sudoku igual
			sudoku.nombreFichero = nom_fichero+".txt"; //Agrega el sudoku a la lista, poniendole el .txt
			sudoku.puntos = puntos;
			ordenarLista(lista, sudoku);  //Ordena los sudokus por puntos
			ok = guardar(lista); //Devuelve un true si se ha podido guardar la nueva lista en el fichero txts
		}
		else { //Muetra por pantalla el mensaje si el sudoku a añadir ya está en la lista 
			cout << "Ese sudoku ya se encuentra en la lista" << endl;
			system("pause");
		}
	}
	else { //Muetra por pantalla si la lista ya está llena
		cout << "Lista llena" << endl;
		system("pause");
	}
	return ok;
}

//Comprueba si el nombre del sudoku a añadir no existe ya 
bool buscarFichero(const tListaSudokus & lista, string nombreFich) {
	bool ok = true;
	nombreFich += ".txt";
	for (int i = 0; i < lista.cont && ok == true; i++)
		if (nombreFich == lista.tabla_sudoku[i].nombreFichero)
			ok = false;
	return ok;
}

//Busca la posicion del nuevo sudoku en la la lista de sudokus, y devuelve la posicion
int buscarPos(const tListaSudokus & lista, const tSudoku &sudoku)
{
	bool encontrado = false;
	int pos = 0;
	while (encontrado == false && pos < lista.cont) {
		if (sudoku.puntos <= lista.tabla_sudoku[pos].puntos) {
			encontrado = true;
		}
		else
			pos++;
	}
	return pos;
}

//Se encarga de ordenar por puntos la lista de sudokus, ya que se habra añadido uno nuevo y habrá que ponerlo en su sitio
void ordenarLista(tListaSudokus &lista, const tSudoku &sudoku) 
{
	int pos = buscarPos(lista, sudoku);//Llamada a otra funcion para buscar la posicion del nuevo sudoku
	desplazar(lista, pos); //Desplaza aquello sudokus de la lista para hacer hueco al nuevo
	lista.tabla_sudoku[pos].nombreFichero = sudoku.nombreFichero; //Inserta el nuevo sudoku en la lista
	lista.tabla_sudoku[pos].puntos = sudoku.puntos;
	lista.cont++; //Incrementa en contador de sudokus
}

//Desplaza los sudokus hacia la derecha del aray de la tablaSudokus desde una posicion determnida para hacer hueco a un nuevo sudoku
void desplazar(tListaSudokus &lista, int pos)
{
	for (int i = lista.cont; i > pos; i--) {
		lista.tabla_sudoku[i].nombreFichero = lista.tabla_sudoku[i - 1].nombreFichero;
		lista.tabla_sudoku[i].puntos = lista.tabla_sudoku[i - 1].puntos;
	}
}
