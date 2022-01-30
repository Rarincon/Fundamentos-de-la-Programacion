//tablero.cpp

#include "tablero.h" //Tiene acceso al modulo de tablero

using namespace std;

//Funcion que se encarga de iniciar todas las casillas, mediantes dos bucles FOR, recorriendo asi toda la matriz
//En cada casilla llama a un a funcion del modulo casilla, que ponia el estdao de esa casilla a vacia, el numero de elemtos al maximo
//y todo el array de boleanos a true
void iniciaTablero(tTablero tablero)
{
	for (int fila = 0; fila < DIMENSION; ++fila)
		for (int columna = 0; columna < DIMENSION; ++columna) {
			iniciaCasilla(tablero[fila][columna]);
		}
}

//Funcion booleana que devuelve true si se ha podido cargar el sudoku, seleccionado en un a funcion superior,
//en el tablero, en  caso contrario devolveria false
//Esta funcion va leyendo de un fichero y va escribiendo y asignadno a las casillas leidas el estado fija
bool cargarTablero(string nombreFichero, tTablero tablero)
{
	fstream tab;
	char c;
	bool ok = false;
	iniciaTablero(tablero); //LLamada a la funcion de iniciar
	tab.open(nombreFichero); //Abre el fichero
	if (tab.is_open())
	{
		ok = true;
		for (int fila = 0; fila < DIMENSION && !tab.eof(); fila++) { //Bucle que acaba cuando la fila tiene el valor de la dimension o no ay mas elementos en el fichero
			for (int columna = 0; columna < DIMENSION && !tab.eof(); columna++) { //Bucle que acaba cuando la columna tiene el valor de la dimension o no ay mas elementos en el ficheros
				tab.get(c);
				rellenaCasilla(tablero[fila][columna], c, true); //Rellena las casillas asugnando el valor de fijas, por el TRUE de la funcion
				if (esFija(tablero[fila][columna])) //Para todas aquellas casillas rellenadas que sean fijas 
					borrarPosibles(tablero, fila, columna); //borrará el elemento/numero del conjunto del resto de casillas, pues este ya se ha usado
			}
			tab.get(c); //Para los saltos de linea, este es el elemento basura
		}		
	}
	else {//Si no se ha podido abrir el fichero se mostrará este mensaje por pantalla
		cout << "No se ha podido abrir el fichero del sudoku\n" << endl;
		system("pause");
	}
	tab.close(); //Cierra el fichero
	return ok;
}

//Funcion que va dibujar el tablero del sudoku por pantalla,
//Cada casilla la rellenara con un color pues esto ya habia sido fijado por una funcion anterior, que es la de dibujaCasilla
void dibujarTablero(const tTablero tablero)
{
	int cont = 0;
	cout << " 012 345 678 " << endl;
	for (int fila = 0; fila < DIMENSION; fila++) {
		if (fila % 3 == 0) //Cada vez que una fila sea multiplo de 3 escribirá por pantalla esta ralla
			cout << "-------------" << endl;
		for (int col = 0; col < DIMENSION; col++) {
			if (col % 3 == 0) //Cada vez que una columna sea multiplo de 3 escribirá por pantalla esta barra
				cout << "|";
			dibujaCasilla(tablero[fila][col]);
			if (col == 8) //Al final del tablero en cada fila escribirá un número para que sea mas comoda la eleccion de la casilla para el jugador
			{
				cout << "|" << " " << cont;
				cont++;
			}
		}
		cout << endl;
	}
	cout << "-------------" << endl;
}

//Esta funcion devuelve un true si se ha podido escribir el numero sellecionado por el jugador
//E caso contrario devuelve un falses
bool ponerNum(tTablero tablero, int fila, int col, int c) //Recibe el tablero, la fila, la columna y el numero
{
	bool ok = false;
	char aux = '0' + c;//Transforma el entero en un char, y mas adelante en otra funcion hará la inversa

	if (perteneceC(tablero[fila][col], c)) //Si el numero se encuntra entre los posibles de la casilla lo escribirá
	{
		rellenaCasilla(tablero[fila][col], aux);
		borrarPosibles(tablero, fila, col); //Borrará ese numero del resto de casillas de su submatriz, columna y fila
		ok = true;
	}
	return ok; //Devuleve si ha sido posible realizar la funcion deseada
}

//Muy similar a la funcion de ponerNum, realizando su funcion a la inversa
bool borrarNum(tTablero tablero, int fila, int col)
{
	bool ok = false;
	if (esRellenada(tablero[fila][col])) //Comprueba que la casilla a borrar, no sea una fija o este vacia
	{
		borrarCasilla(tablero[fila][col]); //"Borra" la casilla poniendo su estado a vacia
		annadirPosibles(tablero, fila, col); //Restablece el numero borrado en el resto de casillas de su submatriz, fila y columna
		ok = true; 
	}
	return ok;
}

//Funcion que devulve true si todo el tablero del sudoku se ha rellenad, entonces finalizara el juego, sino false
bool tableroLleno(const tTablero tablero)
{
	bool ok = true;
	for (int fila = 0; fila < DIMENSION && ok == true; fila++) //Revisa todas las filas y columnas
		for (int columna = 0; columna < DIMENSION && ok == true; columna++)
		{
			if (esVacia(tablero[fila][columna])) //Si hay alguna casilla con estado vacia es que no se ha completado el sudoku
			{
				ok = false;
			}
		}
	return ok;
}

//Se encarga de mostrar por pantalla todos los numeros posibes de aquella casilla que se vacia
//Sino se mostrará el mensaje de debajo
void mostrarPosibles(const tTablero tablero, int fila, int col)
{
	if (esVacia(tablero[fila][col])) //tablero[fila][col].estado == vacia)
		mostrarPosibles(tablero[fila][col]);
	else
		cout << "Esa casilla ya esta siendo utilizada" << endl;	
}

//Se encarga de rellenar todas aquellas casilla que solo tengan un unico valor posible
void rellenarSimples(tTablero tablero) //Hay que usar el unitario
{
	int numero = 0;
	char c;
	for (int fila = 0; fila < DIMENSION; ++fila)
		for (int columna = 0; columna < DIMENSION; ++columna)
			if (esSimple(tablero[fila][columna], numero)) //Revisa si la casilla solo tiene un valor, de ser asi, modifica la variable numero, con el numero que és
			{
				c = numero + '0'; //transforma en char
				rellenaCasilla(tablero[fila][columna], c); //Dentro de esta funcion se transforma el char en un int
				borrarPosibles(tablero, fila, columna);
			}
}


//Esta funcion recible el tablero, la fila y la columna, que tod ello findica una casilla,y a partir de esta casilla 
//irá borrando el numero del resto de casillas de su fila, columna y submatriz, siempre y cuando dichos valores no hayan sido ya borrados
//Esto ultima se encarga de hacerlo una condicion de una funcion de casilla
void borrarPosibles(tTablero tablero, int fila, int col)
{
	int numero = tablero[fila][col].numero;
	for (int i = 0; i < DIMENSION; i++)
	{
		if (!esFija(tablero[i][col])) { //Esta condicion se podria ahorrar, pero si la casilla no es fija irá borrando por filas los valores del resto de casillas de su columna
			borrarPosibles(tablero[i][col], numero);
		}
	}
	for (int j = 0; j < DIMENSION; j++) { //Irá borrando por columnas los valores del resto de casillas de su fila
		if (!esFija(tablero[fila][j])) {
			borrarPosibles(tablero[fila][j], numero);
		}
	}
	for (int i = (fila / 3) * 3; i < ((fila / 3) * 3) + 3; i++) { //Borrará el numero las casillas de su submatriz
		for (int j = (col / 3) * 3; j < ((col / 3) * 3) + 3; j++) {
			if (!esFija(tablero[i][j])) {
				borrarPosibles(tablero[i][j], numero);
			}
		}
	}
	annadirPosibles(tablero[fila][col], numero);//Restaurá el valor posible de la propia casilla, pues este habia sido borrado en el proceso anterior
												 //y no puede una casilla tener un valor, pero que este no esté en su conjuto de posibles
}

//Similar a la funcion de borrar posibles, pues hace lo contraio
void annadirPosibles(tTablero tablero, int fila, int col)
{
	int numero = tablero[fila][col].numero;
	for (int i = 0; i < DIMENSION; i++) //Irá añadiendo por filas los valores del resto de casillas de su columna
	{
		if (!esFija(tablero[i][col])) {
			bool annadir = revisaV(tablero, i, numero); //Llama a una funcion que le indica si podra añadir a un casilla un valor que habia sido borrado
			if (annadir == true)
				annadirPosibles(tablero[i][col], numero); //Restaura el valor al conjunto de posibles de una casilla
		}
	}
	for (int j = 0; j < DIMENSION; j++) { //Irá añadiendo por columnas los valores del resto de casillas de su fila
		if (!esFija(tablero[fila][j])) {
			bool annadir = revisaH(tablero, j, numero); //LLamada funcion que le indica si podra añadir a un casilla un valor que habia sido borrado
			if (annadir == true)
				annadirPosibles(tablero[fila][j], numero); //Restaura el valor al conjunto de posibles de una casilla
		}
	}
	for (int i = (fila / 3) * 3; i < ((fila / 3) * 3) + 3; i++) {  //Añadirá el numero las casillas de su submatriz
		for (int j = (col / 3) * 3; j < ((col / 3) * 3) + 3; j++) {
			if (!esFija(tablero[i][j])) {
				bool annadir = revisaV(tablero, i, numero);
				if (annadir == true)
					annadir = revisaH(tablero, j, numero); //Vuelve a revisar si es posble annadir el numero
				if (annadir == true)
					annadirPosibles(tablero[i][j], numero); //Restaura el valor al conjunto de posibles de una casilla, si la condicion previa se ha cumplido
			}
		}
	}
}

//Se encarga de revisar si en una fila el numero indicado no se encuentra ya, si ese numero no esta en la toda la fila
//devuelve un true, asi la funcion de añadir podra restaurar ese numero en la casilla inicial
bool revisaV(tTablero tablero, int fila, int numero)
{
	bool annadir = true;
	for (int j = 0; j < DIMENSION && annadir == true; j++) {
		if (!esVacia(tablero[fila][j]) && tablero[fila][j].numero == numero)
			annadir = false;
	}
	return annadir;
}

//Se encarga de revisar si en una columna el numero indicado no se encuentra ya, si ese numero no esta en la toda la columna
//devuelve un true, asi la funcion de añadir podra restaurar ese numero en la casilla inicial
bool revisaH(tTablero tablero, int col, int numero)
{
	bool annadir = true;
	for (int i = 0; i < DIMENSION && annadir == true; i++) {
		if (!esVacia(tablero[i][col]) && tablero[i][col].numero == numero)
			annadir = false;
	}return annadir;
}

//Recibe el tablero, y una opcion que ha seleccionado el jugador
void actualizarTablero(tTablero tablero, int opcion)
{
	int x, y;
	int c;
	bool ok = true;
	if (opcion == 1) //Se encarga de mostrar los valores posibles de una casilla determinada
	{
		cout << "Que casilla?" << endl;
		cout << "Fila: ";
		cin >> x;
		cout << "Columna: ";
		cin >> y;
		if ((x <= 8 && x >= 0) && (y <= 8 && y >= 0)) { //Condicion de que la casilla seleccionada esta en el tablero, de no ser asi mostrará un mensaje por pantalla
			mostrarPosibles(tablero, x, y);
			cout << " " << endl;
		}
		else
			cout << "Esa casilla no es valida" << endl;
	}
	else if (opcion == 2) //Se encarga de poner un escribir un valor en una casilla determinada, si cumple las condiciones
	{
		cout << "Que casilla?" << endl;
		cout << "Fila: ";
		cin >> x;
		cout << "Columna: ";
		cin >> y;
		if ((x <= 8 && x >= 0) && (y <= 8 && y >= 0)) { //Condicion de que la casilla seleccionada esta en el tablero, de no ser asi mostrará un mensaje por pantalla
			if (esVacia(tablero[x][y])) {
				cout << "Que numero quieres poner?" << endl;
				cin >> c;
				if (c <= 9 && c >= 1) //Condicion de que el numero esta dentro del rangos
					ok = ponerNum(tablero, x, y, c); //Indica si el numero se ha podido insertar, de no ser asi mostrará un mensaje por pantalla
				else
					ok = false;
			}
			else
				cout << "Esa casilla ya tiene un numero" << endl;
			if (ok == false) {
				cout << "\nNo se puede colocar ese numero\n" << endl;
			}
		}
		else
			cout << "Esa casilla no es valida" << endl;
	}
	else if (opcion == 3) //Se encarga de "borrar" un valor en una casilla determinada, si cumple las condiciones
	{
		cout << "Que casilla?" << endl;
		cout << "Fila: ";
		cin >> x;
		cout << "Columna: ";
		cin >> y;
		if ((x <= 8 && x >= 0) && (y <= 8 && y >= 0)) { //Condicion de que la casilla seleccionada esta en el tablero, de no ser asi mostrará un mensaje por pantalla
			if (esFija(tablero[x][y]))
				cout << "No se puede eliminar ese numero" << endl;
			else
				ok = borrarNum(tablero, x, y); //Indica si el numero se ha podido "borrar", de no ser asi mostrará un mensaje por pantalla
			if (ok == false) {
				cout << "No se ha podido borrar el numero" << endl;
			}
		}
		else
			cout << "Esa casilla no es valida" << endl;
	}
	else //Esta opcion, si no se cumplen las anteriores, es la que se encarga de rellenar todas aquellas casillas que solo tengan un unico valor posible
	{
		rellenarSimples(tablero);
	}
	system("pause"); //Hace una pausa, antes de que se borre todo lo de la pantalla y lo vuelva a mostrar 
}