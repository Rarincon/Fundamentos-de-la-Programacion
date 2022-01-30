//conjunto.cpp

#include "conjunto.h" //biblioteca para poder accceder al modulo de conjunto

using namespace std;


//Se encarga de inicializar un conjunto al vacio, teniendo 0 elementos, ya que el contador esta a cero,
//y tosdos los valores del array booleano a false
void cjto_vacio(tConjunto & c)
{
	c.nElemns = 0;
	for (int i = 0; i < DIMENSION; i++) {
		c.elementos[i] = false;
	}
}


//Se encarga de inicializar un conjunto al lleno, teniendo el maximo de elementos, ya que el contador esta a al tope,
//que ews la dimension, y tosdos los valores del array booleano a false
void cjto_lleno(tConjunto & c)
{
	c.nElemns = DIMENSION;
	for (int i = 0; i < DIMENSION; i++) {
		c.elementos[i] = true;
	}
}


//Se encarga de compribar que en valor se encuentra en el conjunto, si esta devuelve true, sino false
//Ya que el array de booleanos empieza en el valor 0 y acaba en el 8, y los numero empiezan desde el 1 y acab en el 9,
//se tiene que restar uno a valor para saber si esta
bool pertenece(const tConjunto & c, int e)
{
	bool ok = false;
	ok = c.elementos[e - 1];
	return ok;
}


//Se encarga de añadir un numero al conjunto de posibles, poniendo su casilla en el array booleano a true
//y aumentando el numero de elementos
void annadeElemento(tConjunto & c, int e)
{
	c.elementos[e - 1] = true;
	c.nElemns++;
}


//Se encarga de borrar un numero al conjunto de posibles, poniendo su casilla en el array booleano a false
//y disminuyendo el numero de elementos
void borraElemento(tConjunto & c, int e)
{
	c.elementos[e - 1] = false;
	c.nElemns--;
}


//Esta funcion devuelve un entero, que es el numero de elementos en un cojunto
int numElems(const tConjunto & c)
{
	return c.nElemns;
}


//Esta funcion devuelve un true si el conjunto solo tiene un elemento, y ademas la variable "e" que recibe
//la modifica asignadola el valor unico que tiene el conjunto
//En caso de que hubiera mas de un elemento, devuelve false y a no hace nada mas
bool esUnitario(const tConjunto & c, int & e)
{
	bool ok = false;
	if (c.nElemns == 1)
	{
		ok = true;
		int i = 0;
		while (i < DIMENSION && c.elementos[i] == false)
			i++;
		e = i + 1;
	}
	return ok;
}


//Se encarga de mostrar por pantalla todos los numeros que se encuentren en el conjunto, sumado 1 a la casilla que este true
//del array booleano, ya que como dijimos el array empieza en el 0, y corresponde al numero 1 esa casilla
void mostrar(const tConjunto & c)
{
	cout << "Elementos: ";
	for (int i = 0; i < DIMENSION; i++)
	{
		if (c.elementos[i] == true)
		{
			int e = i + 1;
			cout << e << " ";
		}
	}
}