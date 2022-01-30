//casilla.cpp

//Bibliotecas para usar determinadas funciones y comandos
#include "casilla.h" //Tiene acceso al modulo casilla.h


using namespace std;


//Pone un casilla a su estado inicial, con todos los valores de los numeros posibles, e indica que esta vacia
void iniciaCasilla(tCasilla & casilla)
{
	casilla.estado = vacia;
	cjto_lleno(casilla.posibles);
}


//Se encarga de de rellenar el estado de la casilla en funcion de los valores que recifa, si es fija, recibe un true
//Sino es true y el valor de char es vacio le asigna el estadfo vacio
//El ultimo caso, es que reciba un false y un char con valores entonces asigna a un casilla el estado de rellenada y le da un valor la variable numero de casilla 
void rellenaCasilla(tCasilla & casilla, char c, bool esfija)
{
	if (c == ' ')
	{
		casilla.estado = vacia;
	}
	else
	{
		if (esfija)
		{
			casilla.estado = fija;
		}
		else casilla.estado = rellenada;
		casilla.numero = c - '0';
	}
}


//Se encarga de darle un color a una posicion del tablero en funcion de estado
void dibujaCasilla(const tCasilla & casilla)
{
	int color = 0;
	if (casilla.estado == fija) //Color azul
	{
		color = 1;//Asigna un valor a la variable
		colorFondo(color);//Llama a la variable para modificar el color de salida de una casilla
		cout << casilla.numero;//Muestra un numero en esa casilla
		color = 0;
		colorFondo(color);
		//Vuelve a poner el valor de inicio 
		//Para que la siguiente casilla y las siguientes se dibujen en negro
		//Hasta que se quiera cambiar de color, entonces otra funcion llamaria a esta	
	}
	else if (casilla.estado == rellenada) //Color rojo
	{
		color = 4;
		colorFondo(color);
		cout << casilla.numero;
		color = 0;
		colorFondo(color);
	}
	else
		cout << " ";
	color = 0; //Color negro
}


//Esta funcion se encarga de revisar si una casilla tiene un unico valor
//Para ello llam a un afuncion del modulo conjunto.cpp
//Esta funcion nos devuelve true si solo hay un valor, y ademas nos modifica la variable numero
//Asignando a esta varibale el unico numero posible
//La funcion es simple es un paso intermedio entre el tablero y el conjunto, que tambien devuelve true o false
//En funcion de si solo hay un valor para una casilla y devuelve dicho valor
bool esSimple(const tCasilla & casilla, int & numero)
{
	bool ok = false;
	if (casilla.estado == vacia && esUnitario(casilla.posibles, numero) == true)
	{
		ok = true;
	}
	return ok;
}


//Funcion que modifica el color de salida a la hora de escribir en el panel  de comandos, donde se encontrara nuestro sudoku
void colorFondo(int color)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}


//Se encarga de comprobar si el estado de una casilla es vacia, en ese caso la funcion devuelve true, sino false
bool esVacia(const tCasilla & casilla)
{
	bool ok = false;
	if (casilla.estado == vacia)
		ok = true;
	return ok;
}


//Se encarga de comprobar si el estado de una casilla es rellenada, en ese caso la funcion devuelve true, sino false
bool esRellenada(const tCasilla & casilla)
{
	bool ok = false;
	if (casilla.estado == rellenada)
		ok = true;
	return ok;
}


//Se encarga de comprobar si el estado de una casilla es fija, en ese caso la funcion devuelve true, sino false
bool esFija(const tCasilla & casilla)
{
	bool ok = false;
	if (casilla.estado == fija)
		ok = true;
	return ok;
}

//Se encarga de mostrar por pantalla, llamando a un funcion de conjunto, todos los valores posbles de una casilla
//Si no tiene valores posibles escribe por pantala que no tiene ningun valor posible    
void mostrarPosibles(const tCasilla & casilla)
{
	if (numElems(casilla.posibles) == 0)
		cout << "No se puede poner ningun numero" << endl;
	else
		mostrar(casilla.posibles);
}

//Se encarga de añadir numeros posbles a un casilla, siempre que dicho valor no se encuentre ya en conjunto de posbles
//Por ejemplo si perteneciera y lo añade, el valor del contador aumentaria,
//pero no añadiria ningun numero ya que este ya se encontraba en el conjunto, y se produciria un error mas adelante
void annadirPosibles(tCasilla & casilla, int numero)
{
	if (!pertenece(casilla.posibles, numero))
		annadeElemento(casilla.posibles, numero);
}


//Se encarga de borrar numeros posbles a un casilla, siempre que dicho valor se encuentre ya en conjunto de posbles
//Por ejemplo si no perteneciera y lo borra, el valor del contador disminuiria,
//pero no borraria ningun numero ya que este ya no se encontraba en el conjunto, y se produciria un error mas adelante
void borrarPosibles(tCasilla &casilla, int numero)
{
	if (pertenece(casilla.posibles, numero))
		borraElemento(casilla.posibles, numero);
}

//Se encarga de "borrar" un casilla, asignandole el estado en vacia
//Asi al escribir por pantalla mas adelante no pondria nada en su coordenada/casilla, solo un espacio en blanco
void borrarCasilla(tCasilla &casilla)
{
	casilla.estado = vacia;
}


//Devulve el valor booleano de true o false, que le duvuelve la funcion pertenece de c
//Esta funcion esta para no saltar del tablero al modulo conjunto sin pasar por casilla
bool perteneceC(tCasilla& casilla, int numero)
{
	return pertenece(casilla.posibles, numero);
}
