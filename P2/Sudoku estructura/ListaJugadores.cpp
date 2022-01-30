//ListaJugadores.cpp

#include "ListaJugadores.h" //Acceso al modulo de ListaJugadores
#include "checkML.h" //Acceso al detector de fugas de memoria

using namespace std;

//Al crear una nueva lista como no hay nigun jugador pone el contador a cero
//Y crea un array dinamico con el puntero de jugador, de tamaño MAX_JUGADORES
//Asigan a la variable tam, el tamaño del array dinamico
void creaListaVacia(tListaJugadores & lista)
{
	lista.jugador = new tJugadorPtr[MAX_JUGADORES];
	lista.cont = 0;
	lista.tam = MAX_JUGADORES;
}


//Funcion booleana que devuelve true(a traves del ok) si se han podido cargar los jugadores de un fichero a la lista de Jugadores, sino devuelve false
bool cargar(tListaJugadores & lista) {
	int punt, i = 0;
	string id;
	ifstream f;
	bool ok = false;
	creaListaVacia(lista);
	f.open("listaJugadores.txt");  //Abre un fichero
	if (f.is_open()) {  //Comprueba que se ha podido abrir
		ok = true;
		while (f >> id >> punt) {
			if (lista.cont == lista.tam) //Si el array dinamico no tiene mas tamaño. se ampliara el tamaño de este, con una funcion ampliar
				ampliar(lista);
			lista.jugador[i] = new tJugador; //Crea un puntero para cada jugador, al ir insertandolos en la lista del array dinamico
			lista.jugador[i]->identificador = id; //Va insertando en la lista el nombre del jugador y los puntos
			lista.jugador[i]->puntuacion = punt;
			lista.cont++;
			i++;
		}
	}
	else {//Si no se ha podido abrir el fichero se mostrará este mensaje por pantalla
		cout << "No se ha podido abrir el fichero de los jugadores\n" << endl;
		system("pause");
	}
	f.close(); //Cierra el fichero
	return ok;
}

//Muestra por pantalla en un a coordenada determinada( por el setw() ) los nombres de los jugadores y los puntos
void mostrar(const tListaJugadores & lista) {
	cout << setw(10) << "Jugadores" << " " << setw(20) << "Puntos" << endl;
	for (int i = 0; i < lista.cont; i++) {
		cout << setw(10) << toString(lista.jugador[i]) << " " << setw(20) << toString2(lista.jugador[i]) << endl;
	}
}

//Esta funcion se encarga de escribir en un fichero la lista de jugadores con los puntos de cada uno
bool guardar(const tListaJugadores & lista) {
	ofstream f; //Para ficheros de salida
	bool ok = false;
	f.open("listaJugadores.txt"); //Abre un fichero con ese nombre, o lo crea si no existe
	if (f.is_open()) { //Comprueba que se ha podido abrir
		ok = true;
		for (int i = 0; i < lista.cont; i++) { //Va escribiendo en el fichero todos los jugadores que esten en la lista
			f << lista.jugador[i]->identificador << " " << lista.jugador[i]->puntuacion << endl;
		}
	}
	else {//Si no se ha podido abrir el fichero se mostrará este mensaje por pantalla
		cout << "No se ha podido abrir el fichero de la lista de jugadores para guardarlo\n" << endl;
		system("pause");
	}
	f.close(); //Cierra el fichero
	return ok;
}

//Esta funcion se encarga de puntuar al jugador que ha rellenado el sudoku con los puntos que corresponden al sudoku completado
//Para ello recibe una varibale con los puntos a sumar a un jugador
void puntuarJugador(tListaJugadores & lista, int puntos) {
	string id;
	int pos;
	cout << "Introduce el identificador: " << endl;
	cin.ignore();
	getline(cin, id);
	if (!buscar(lista, id, 0, lista.cont - 1, pos)) { //Busca si el jugador insertado existe ya en la lista, de no ser asi lo inserta
		if (lista.cont == lista.tam) //Si el array dinamico no tiene mas tamaño. se ampliara el tamaño de este, con una funcion ampliar
			ampliar(lista);
		annadirJugador(lista.jugador[lista.cont], id); //añade al jugador nuevo
		pos = lista.cont;
		lista.cont++; //aumenta el contador de jugadores en la lista
		modificarJugador(lista.jugador[pos], puntos); //Modifica los puntos del jugador con los de la varible puntos
		ordena(lista); //Ordena la lista despues de haber añadido un jugador
	}
	else
		modificarJugador(lista.jugador[pos], puntos);//Si la busqueda a sido true, en esa funcion se ha modificado la variable pos, indicando la posicion del jugador deseado
													//Modifica los puntos del jugador con los de la varible puntos
}


//Busca si el nombre del jugador se encuentra ya en la lista, de saer asi devuelve TRUE,
//y la posicion de la lista en la que se encuentra ese jugador
//Busqueda binaria recursiva
//si no encuntra al jugador volvera a llamerse a si misma hasta encontralo o hasta lleguar al tope 
bool buscar(const tListaJugadores & lista, string id, int ini, int fin, int &pos) {
	
	bool enc;
	if (ini <= fin)
	{
		int mitad = (ini + fin) / 2;
		if (id < lista.jugador[mitad]->identificador)
			enc = buscar(lista, id, ini, mitad - 1, pos);
		else if (lista.jugador[mitad]->identificador < id)
			enc = buscar(lista, id, mitad + 1, fin, pos);
		else {
			pos = mitad;
			enc = true;
		}
	}
	else {
		pos = ini;
		enc = false;
	}
	return enc;
}

// Utilizamos un Algoritmo de ordenacion por insercion de intercambio en las siguientes dos funciones

//Recibe una copia de la lista de jugadores original y la ordena por puntos, de mayor a menor
tListaJugadores ordenarPorRanking(const tListaJugadores &lista) {

	tJugadorPtr tmp; //Usa un puntero de jugador auxiliar, para la ordenacion
	int pos = 0;
	for (int i = 1; i < lista.cont; i++) {
		pos = i;
		while ((pos > 0) && (menor(lista.jugador[pos - 1], lista.jugador[pos]))) { //Algoritmo de ordenacion, llama a una funcion de jugador.cpp
			tmp =lista.jugador[pos];
			lista.jugador[pos] = lista.jugador[pos - 1];
			lista.jugador[pos - 1] = tmp;
			pos--;
		}
	}
	return lista;
}

//Recibe una copia de la lista de jugadores original y la ordena por identificador, de menor a mayor
tListaJugadores ordenarPorId(const tListaJugadores &lista) {
	
	tJugadorPtr tmp; //Usa un puntero de jugador auxiliar, para la ordenacion
	int pos = 0;
	for (int i = 1; i < lista.cont; i++) {
		pos = i;
		while ((pos > 0) && (mayor(lista.jugador[pos - 1], lista.jugador[pos]))) { //Algoritmo de ordenacion, llama a una funcion de jugador.cpp
			tmp = lista.jugador[pos];
			lista.jugador[pos] = lista.jugador[pos - 1];
			lista.jugador[pos - 1] = tmp;
			pos--;
		}
	}
	return lista;
}

//Ordena  por identificador modificando la lista original 
void ordena(tListaJugadores & lista)
{
	tJugadorPtr tmp;
	int pos;
	for (int i = 1; i < lista.cont; i++) {
		pos = i;
		while ((pos > 0) && (mayor(lista.jugador[pos - 1], lista.jugador[pos]))) { //Algoritmo de ordenacion, llama a una funcion de jugador.cpp
			tmp = lista.jugador[pos];
			lista.jugador[pos] = lista.jugador[pos - 1];
			lista.jugador[pos - 1] = tmp;
			pos--;
		}
	}
}

//VERSION 3

//Se encarga de ampliar el tamanño del array dinamico de la la lista de jugadores
//Para ello hace un nuevo array dinamico auxiliar y le pasa todos los valores de la lista antigua
//Borra el antiguo array dinamico y crea uno nuevo con el nuevo tamaño y le pasa al nuevo array dinamico todos los datos de la auxiliar
//Luego borra el auxiliar
void ampliar(tListaJugadores & lista)
{
	int tamAux = 2 * lista.tam;
	lista.tam = tamAux;
	tJugadorPtr *aux = new tJugadorPtr[tamAux];
	for (int i = 0; i < lista.cont; i++) {
		aux[i] = lista.jugador[i];
	}
	delete[] lista.jugador;
	lista.jugador = new tJugadorPtr[tamAux];
	for (int i = 0; i < lista.cont; i++) {
		lista.jugador[i] = aux[i];
	}
	delete[] aux;
}

//Se encarga de liberar la memoria, borrando todos los puntero de una lista
void borrarListaJugadores(tListaJugadores & lista) {
	for (int i = 0; i < lista.cont; i++) {
		delete lista.jugador[i];
	}
	lista.cont = 0;
	delete[] lista.jugador;
}	

//Recibe dos listas, la original y la copia, que inicialmente esta vacia, va copiando todos los valores de la lista original en la copia
//Creando para la copia punteros para  cada jugador, que guarde los valores, como la original
//Y si la copia necesita mas tamaño en su array dinamico lo ampliara como hicimos en la funcion de cargar
void hacercopia(const tListaJugadores & lista, tListaJugadores & copia)
{
	creaListaVacia(copia);
	for (int i = 0; i < lista.cont; i++) {
		if (copia.cont == copia.tam)
			ampliar(copia);
		copia.jugador[i] = new tJugador;
		copia.jugador[i]->identificador = lista.jugador[i]->identificador;
		copia.jugador[i]->puntuacion = lista.jugador[i]->puntuacion;
		copia.cont++;
	}
}