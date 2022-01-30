//Juego de las siste y media

#include <iostream>
#include <fstream> 
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string> 
using namespace std;

const int HUMANO = 1;
const int MAQUINA = 2;
const int MAX_CARTAS = 40;

typedef int tCartasPorAparecer[MAX_CARTAS];
typedef int tArray[MAX_CARTAS];
typedef struct {
	int contador;
	tArray datos;
}tConjuntoCartas;


//Version 1
double modoA(ifstream & fich_entrada, int numCartas);
double modoBhumano(ifstream & fich_entrada, int numCartas);
double modoBmaquina(ifstream &fich_entrada, int numCartas, double puntosHumano);
int determinaGanador(double puntosHumano, double puntosMaquina);
int generarMaxCartas();
void jugarModoA(int opcion, int numCartas, double & ganador, double & puntosHumano, double & puntosMaquina, string & nom_fich);
void jugarModoB(int opcion, int numCartas, double & ganador, double & puntosHumano, double & puntosMaquina, string & nom_fich);

//Version 2 
void jugarModoC(int opcion, double & ganador, double & puntosHumano, double & puntosMaquina, string & nom_fich, tCartasPorAparecer cartas, double &puntos);
void modoChumano(ifstream & fich_entrada, tCartasPorAparecer cartas, double & puntos);
void modoCmaquina(ifstream & fich_entrada, tCartasPorAparecer cartas, double puntosHumano, double & puntos);
bool esProbablePasarse(double puntosMaquina, const tCartasPorAparecer cartas);
void iniciarPorAparecer(tCartasPorAparecer & cartas);


//Version 3
void jugarModoD(double & ganador, int & num_partida, double & puntosHumano, double & puntosMaquina, double & puntos, tCartasPorAparecer cartas);
void barajar(tConjuntoCartas &mazo);
void inicializa(tConjuntoCartas & cartas);
void crearMazo(tConjuntoCartas &mazo);
void cargarMazo(tConjuntoCartas & mazo);
void sacar(tConjuntoCartas & cartas, int & carta);
void incluir(tConjuntoCartas & cartas, int carta);
void modoDhumano(tConjuntoCartas &mazo, tCartasPorAparecer cartas, tConjuntoCartas& cartasHumano, double& puntos);
void modoDmaquina(tConjuntoCartas& mazo, tCartasPorAparecer cartas, double puntosHumano, tConjuntoCartas& cartasMaquina, double& puntos);
int determinaGanadorModoD(double puntosHumano, double puntosMaquina, tConjuntoCartas cartasHumano, tConjuntoCartas cartasMaquina);
void guardarResultado(tConjuntoCartas cartashumano, tConjuntoCartas cartasMaquina, double puntosHumano, double puntosMaquina, int ganador, int num_partida);

////////////////////////////////////////////

int leerOpcion()
{
	int opcion;
	cout << "" << endl;
	cout << "MENU DEL JUEGO\n" << endl;
	cout << "1-Modo A" << endl;
	cout << "2-Modo B" << endl;
	cout << "3-Modo C" << endl;
	cout << "4-Modo D" << endl;
	cout << "0-Salir\n" << endl;
	cin >> opcion;
	return opcion;
}


int menu()
{
	int opcion;
	opcion = leerOpcion();
	while (opcion < 0 || opcion > 4)
	{
		cout << "Opcion erronea\n" << endl;
		opcion = leerOpcion();
	}
	return opcion;
}


int main()
{
	cout << "JUEGO DE LAS SIETE Y MEDIA" << endl;
	bool fin = true;
	int num_partida = 0;
	while (fin)
	{
		int opcion = menu();
		int numCartas = generarMaxCartas();
		double ganador = 0;
		double puntos = 0;
		
		double puntosHumano = 0;
		double puntosMaquina = 0;
		string nom_fich;
		tCartasPorAparecer cartas;

		if (opcion == 1)
		{
			jugarModoA(opcion, numCartas, ganador, puntosHumano, puntosMaquina, nom_fich);
		}
		else if (opcion == 2)
		{
			jugarModoB(opcion, numCartas, ganador, puntosHumano, puntosMaquina, nom_fich);
		}
		else if (opcion == 3)
		{
			jugarModoC(opcion, ganador, puntosHumano, puntosMaquina, nom_fich, cartas, puntos);
		}
		else if (opcion == 4)
		{
			jugarModoD(ganador, num_partida, puntosHumano, puntosMaquina, puntos, cartas);
		}
		else
		{
			fin = false;
		}
	}
	return 0;
}

////////////////////////////////////////////

void jugarModoA(int opcion, int numCartas, double & ganador, double & puntosHumano, double & puntosMaquina, string & nom_fich)
{
	ifstream fich_entrada;
	cout << " " << endl;
	cout << "Modo A\n" << endl;
	cout << "Introduce el nombre del fichero: " << endl;
	cin >> nom_fich;
	fich_entrada.open(nom_fich);
	if (fich_entrada.is_open())
	{
		ganador = modoA(fich_entrada, numCartas);
		if (ganador == 1)
		{
			cout << "\nEl ganador es el Humano" << endl;
		}
		else
		{
			cout << "\nEl ganador es la Maquina" << endl;
		}
	}
	else
	{
		cout << "Archivo erroneo" << endl;
		opcion = menu();
	}
	fich_entrada.close();
}


int generarMaxCartas()
{
	int num = 0;
	srand(time(NULL));
	num = 3 + rand() % (6 - 3);
	return num;
}


double modoA(ifstream & fich_entrada, int numCartas)
{
	double puntosHumano = 0;
	double puntosMaquina = 0;
	double puntosGanador = 0;
	double cartaJ = 0;
	double cartaM = 0;
	int contadorJ = 0;
	int contadorM = 0;

	cout << " " << endl;
	cout << "Archivo abierto";
	cout << " " << endl;
	while (contadorJ < numCartas)
	{
		fich_entrada >> cartaJ;
		if (cartaJ > 7)
		{
			puntosHumano = puntosHumano + 0.5;
		}
		else
		{
			puntosHumano = puntosHumano + cartaJ;
		}
		contadorJ++;
		cout << "Puntos del jugador: " << puntosHumano << endl;
		cout << " ";
	}
	cout << "" << endl;
	while (contadorM < numCartas)
	{
		fich_entrada >> cartaM;
		if (cartaM > 7)
		{
			puntosMaquina = puntosMaquina + 0.5;
		}
		else
		{
			puntosMaquina = puntosMaquina + cartaM;
		}
		contadorM++;
		cout << "Puntos del Maquina: " << puntosMaquina << endl;
		cout << " ";
	}
	puntosGanador = determinaGanador(puntosHumano, puntosMaquina);
	return puntosGanador;
}

///////////////

void jugarModoB(int opcion, int numCartas, double & ganador, double & puntosHumano, double & puntosMaquina, string & nom_fich)
{
	ifstream fich_entrada;
	cout << " " << endl;
	cout << "Modo B\n" << endl;
	cout << "Introduce el nombre del fichero: " << endl;
	cin >> nom_fich;
	fich_entrada.open(nom_fich);
	if (fich_entrada.is_open())
	{
		cout << " " << endl;
		cout << "Archivo abierto" << endl;
		cout << " " << endl;
		puntosHumano = modoBhumano(fich_entrada, numCartas);
		puntosMaquina = modoBmaquina(fich_entrada, numCartas, puntosHumano);
		cout << "Puntos del Jugador: " << puntosHumano << endl;
		cout << "Puntos de la maquina: " << puntosMaquina << endl;
		cout << " " << endl;
		ganador = determinaGanador(puntosHumano, puntosMaquina);
		if (ganador == 1)
		{
			cout << "\nEl ganador es el Humano" << endl;
		}
		else
		{
			cout << "\nEl ganador es la Maquina" << endl;
		}
	}
	else
	{
		cout << "Archivo erroneo" << endl;
		opcion = menu();
	}
	fich_entrada.close();
}


double modoBhumano(ifstream &fich_entrada, int numCartas)
{
	cout << "Turno del jugador" << endl;
	cout << " " << endl;
	double puntos = 0;
	double carta;
	int contador = 0;
	bool plantarse = false;
	int opcion;
	while (contador < numCartas && !plantarse && puntos <= 7.5)
	{
		fich_entrada >> carta;
		cout << "La carta es : " << carta << endl;
		if (carta > 7)
		{
			puntos = puntos + 0.5;
		}
		else
		{
			puntos = puntos + carta;
		}
		cout << "Los puntos son: " << puntos << endl;
		cout << " " << endl;
		cout << "Quieres seguir robando?" << endl;
		cout << " " << endl;
		cout << " 1- Si " << endl;
		cout << " 2- No " << endl;
		do
		{
			cin >> opcion;
		} while (opcion < 1 || opcion > 2);
		if (opcion == 1)
		{
			contador++;
		}
		else
		{
			plantarse = true;
		}
	}
	return puntos;
}


double modoBmaquina(ifstream &fich_entrada, int numCartas, double puntosHumano)
{
	cout << "Turno de la maquina" << endl;
	cout << " " << endl;
	double puntos = 0;
	int cartas;
	int carta;
	int contador = 0;
	bool plantarse = false;
	int opcion;

	while (contador < numCartas && !plantarse)
	{
		fich_entrada >> carta;
		cout << "La carta es : " << carta << endl;
		if (carta > 7)
		{
			puntos = puntos + 0.5;
		}
		else
		{
			puntos = puntos + carta;
		}
		cout << "Los puntos de la maquina son: " << puntos << endl;
		cout << " " << endl;
		if (puntos > puntosHumano || puntos == 7.5)
		{
			plantarse = true;
		}
		else
		{
			contador++;
		}

	}
	return puntos;
}


int determinaGanador(double puntosHumano, double puntosMaquina)
{
	int ganador = 0;
	if (puntosHumano <= 7.5 && puntosMaquina <= 7.5)
	{
		if (puntosHumano > puntosMaquina) {
			ganador = HUMANO;
			cout << "\nPuntos del ganador: " << puntosHumano << endl;
			cout << " " << endl;
		}
		else if (puntosHumano < puntosMaquina)
		{
			ganador = MAQUINA;
			cout << "\nPuntos del ganador: " << puntosMaquina << endl;
			cout << " " << endl;
		}
		else
		{
			srand(time(NULL));
			ganador = 1 + rand() % (3 - 1);
			if (ganador == HUMANO)
			{
				cout << "\nPuntos del ganador: " << puntosHumano << endl;
				cout << " " << endl;
			}
			else
			{
				cout << "\nPuntos del ganador: " << puntosMaquina << endl;
				cout << " " << endl;
			}
		}
	}
	else if (puntosHumano <= 7.5 && puntosMaquina > 7.5)
	{
		ganador = HUMANO;
		cout << "\nPuntos del ganador: " << puntosHumano << endl;
	}
	else
	{
		ganador = MAQUINA;;
		cout << "\nPuntos del ganador: " << puntosMaquina << endl;
	}
	return ganador;
}


////////////////////////////////////////////

void jugarModoC(int opcion, double & ganador, double & puntosHumano, double & puntosMaquina, string & nom_fich, tCartasPorAparecer cartas, double &puntos)
{
	ifstream fich_entrada;
	cout << " " << endl;
	cout << "Modo C\n" << endl;
	cout << "Introduce el nombre del fichero: " << endl;
	cin >> nom_fich;
	fich_entrada.open(nom_fich);
	if (fich_entrada.is_open())
	{
		cout << " " << endl;
		cout << "Archivo abierto" << endl;
		cout << " " << endl;
		modoChumano(fich_entrada, cartas, puntos);
		puntosHumano = puntos;
		modoCmaquina(fich_entrada, cartas, puntosHumano, puntos);
		puntosMaquina = puntos;
		ganador = determinaGanador(puntosHumano, puntosMaquina);
		if (ganador == 1)
		{
			cout << "\nEl ganador es el Humano" << endl;;
		}
		else
		{
			cout << "\nEl ganador es la Maquina" << endl;
		}
	}
	else
	{
		cout << "Archivo erroneo" << endl;
		opcion = menu();
	}
	fich_entrada.close();
}


void iniciarPorAparecer(tCartasPorAparecer & cartas)
{
	cartas[0] = 12;
	for (int i = 1; i <= 7; i++)
		cartas[i] = 4;
}


bool esProbablePasarse(double puntosMaquina, const tCartasPorAparecer cartas)
{
	double cartas_restantes, cartas_posibles, probabilidad;
	cartas_restantes = 0;
	bool es_probable_pasarse = false;
	for (int i = 0; i <= 7; i++)
	{
		cartas_restantes = cartas_restantes + cartas[i];
	}
	cartas_posibles = 0;
	for (int j = 0; j <= 7.5 - puntosMaquina; j++)
	{
		cartas_posibles = cartas_posibles + cartas[j];
	}
	probabilidad = cartas_posibles / cartas_restantes;
	cout << "La probabilidad de no pasarse es de: " << probabilidad << " % " << endl;

	if (probabilidad < 0.51)
	{
		es_probable_pasarse = true;
	}
	return es_probable_pasarse;
}


void modoChumano(ifstream & fich_entrada, tCartasPorAparecer cartas, double & puntos)
{
	int carta, opcion;
	bool plantarse = false;
	cout << "Turno del jugador\n" << endl;
	while (puntos < 7.5 && !plantarse)
	{
		fich_entrada >> carta;
		cout << "La carta es : " << carta << endl;
		if (carta > 7)
		{
			puntos = puntos + 0.5;
			cartas[0]--;
		}
		else
		{
			puntos = puntos + carta;
			cartas[carta]--;
		}
		cout << "Los puntos son: " << puntos << endl;
		cout << " " << endl;
		cout << "Quieres seguir robando?" << endl;
		cout << " " << endl;
		cout << " 1- Si " << endl;
		cout << " 2- No " << endl;
		do
		{
			cin >> opcion;
		} while (opcion < 1 || opcion > 2);
		if (opcion == 2)
		{
			plantarse = true;
		}
	}
}


void modoCmaquina(ifstream & fich_entrada, tCartasPorAparecer cartas, double puntosHumano, double & puntos)
{
	int carta;
	bool plantarse = false;
	puntos = 0;
	cout << "Turno de la maquina\n";
	while (puntos < 7.5 && !plantarse && puntos < puntosHumano)
	{
		fich_entrada >> carta;
		cout << "La carta es : " << carta << endl;
		if (carta > 7)
		{
			puntos = puntos + 0.5;
			cartas[0]--;
		}
		else
		{
			puntos = puntos + carta;
			cartas[carta]--;
		}
		cout << "Los puntos son: " << puntos << endl;
		cout << " " << endl;
		if (esProbablePasarse(puntos, cartas) || puntos >= 7.5)
		{
			plantarse = true;
		}
	}
}


///////////////////////////////////////////

void jugarModoD(double & ganador, int & num_partida, double & puntosHumano, double & puntosMaquina, double & puntos, tCartasPorAparecer cartas)
{
	num_partida++;
	cout << " " << endl;
	cout << "Modo D\n" << endl;
	tConjuntoCartas mazo;
	tConjuntoCartas cartasHumano;
	tConjuntoCartas cartasMaquina;
	inicializa(mazo);
	inicializa(cartasHumano);
	inicializa(cartasMaquina);
	modoDhumano(mazo, cartas, cartasHumano, puntos);
	puntosHumano = puntos;
	modoDmaquina(mazo, cartas, puntosHumano, cartasMaquina, puntos);
	puntosMaquina = puntos;
	ganador = determinaGanadorModoD(puntosHumano, puntosMaquina, cartasHumano, cartasMaquina);
	guardarResultado(cartasHumano, cartasMaquina, puntosHumano, puntosMaquina, ganador, num_partida);
	if (ganador == 1)
	{
		cout << "\nEl ganador es el Humano" << endl;
		cout << "Puntos del Humano: " << puntosHumano << endl;
	}
	else
	{
		cout << "\nEl ganador es la Maquina" << endl;
		cout << "Puntos de la Maquina: " << puntosMaquina << endl;
	}
}


void inicializa(tConjuntoCartas & cartas)
{
	for (int i = 0; i < MAX_CARTAS; i++)
	{
		cartas.datos[i] = 0;
	}
	cartas.contador = 0;
}


void crearMazo(tConjuntoCartas & mazo)
{
	cargarMazo(mazo);
	barajar(mazo);
}


void barajar(tConjuntoCartas & mazo)
{
	srand(time(NULL));

	int azar1, azar2, aux;

	for (int veces = 0; veces < 100; veces++) {
		azar1 = rand() % 40;
		azar2 = rand() % 40;
		aux = mazo.datos[azar1];
		mazo.datos[azar1] = mazo.datos[azar2];
		mazo.datos[azar2] = aux;
	}
}


void cargarMazo(tConjuntoCartas & mazo)
{
	for (int num = 0; num < 10; num++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (num < 7)
			{
				mazo.datos[4 * num + j] = num + 1;
			}
			else
			{
				mazo.datos[4 * num + j] = num + 3;
			}

		}
	}
	mazo.contador = MAX_CARTAS;
}
/*
for (int i = 0; i < 4/*lo vamos a repetir tos 4 veces, por los cuatro palos; i++) {
	for (int j = 1; j < 8; j++) //Estamos generando el mazo en orden, hasta el ocho por las cartas ya que luego tiene figuras
		mazo.lista[mazo.contador] = j; //tengo un struct de mazo
	mazo.contador++;
	for (int j = 10; j < 13; j++)
		mazo.lista[mazo.contador] = j;
	mazo.contador++;
}
random_shuffle(&(mazo, lista[0]), &(mazo, lista[mazo.contador - 1])))//barajea el array, lo desordena aleatoriamente (no he metido la biblioteca)
*/

void sacar(tConjuntoCartas & cartas, int & carta) 
{
	cartas.contador--;
	carta = cartas.datos[cartas.contador];
	cartas.datos[cartas.contador] = 0;
}


void incluir(tConjuntoCartas & cartas, int carta)
{
	
	cartas.datos[cartas.contador] = carta;
	cartas.contador++;
}


void modoDhumano(tConjuntoCartas &mazo, tCartasPorAparecer cartas, tConjuntoCartas& cartasHumano, double& puntos)
{

	int carta = 0;
	int	opcion;
	bool plantarse = false;
	cout << "Turno del jugador\n" << endl;
	crearMazo(mazo);
	while (puntos < 7.5 && !plantarse)
	{
		sacar(mazo, carta);
		incluir(cartasHumano, carta);
		cout << "\nLa carta es : " << carta << endl;
		if (carta > 7)
		{
			puntos = puntos + 0.5;
			cartas[0]--;
		}
		else
		{
			puntos = puntos + carta;
			cartas[carta]--;
		}
		cout << "Los puntos son: " << puntos << endl;
		cout << " " << endl;
		cout << "Quieres seguir robando?" << endl;
		cout << " " << endl;
		cout << " 1- Si " << endl;
		cout << " 2- No " << endl;
		do
		{
			cin >> opcion;
			cout << " ";
		} while (opcion < 1 || opcion > 2);
		if (opcion == 2)
		{
			plantarse = true;
		}

	}
}


void modoDmaquina(tConjuntoCartas& mazo, tCartasPorAparecer cartas, double puntosHumano, tConjuntoCartas& cartasMaquina, double& puntos)
{
	int carta=0;
	bool plantarse = false;
	puntos = 0;
	cout << "Turno de la maquina\n";
	if (puntosHumano < 8)
	{
		while (puntos < 7.5 && !plantarse && puntos < puntosHumano)
		{
			sacar(mazo, carta);
			incluir(cartasMaquina, carta);
			cout << "La carta es : " << carta << endl;
			if (carta > 7)
			{
				puntos = puntos + 0.5;
				cartas[0]--;
			}
			else
			{
				puntos = puntos + carta;
				cartas[carta]--;
			}
			cout << "Los puntos son: " << puntos << endl;
			cout << " " << endl;
			if (esProbablePasarse(puntos, cartas) || puntos >= 7.5)
			{
				plantarse = true;
			}
		}
	}
}


void guardarResultado(tConjuntoCartas cartasHumano, tConjuntoCartas cartasMaquina, double puntosHumano, double puntosMaquina, int ganador, int num_partida)
{
	string nom_fich;
	string texto;
	ofstream fichero;
	nom_fich = "Partida " + to_string(num_partida) + ".txt";
	texto = "Numero de partida: " + to_string(num_partida) + "\nGanador: ";
	if (ganador == HUMANO)
	{
		texto += "Humano";
	}
	else
	{
		texto += "Maquina";
	}
	texto += "\nPuntuacionde del Humano: " + to_string(puntosHumano) + "\nCartas del Humano: ";
	for (int i = 0; i < cartasHumano.contador; i++)
	{
		texto += to_string(cartasHumano.datos[i]) + " ";
	}
	texto += "\nPuntuacionde de la Maquina: " + to_string(puntosMaquina) + "\nCartas de la Maquina: ";
	for (int i = 0; i < cartasMaquina.contador; i++)
	{
		texto += to_string(cartasMaquina.datos[i]) + " ";
	}
	fichero.open(nom_fich);
	if (fichero.is_open())
	{
		fichero << texto;
		fichero.close();
	}
	else
	{
		cout << "Fichero no abierto" << endl;
	}
}


int determinaGanadorModoD(double puntosHumano, double puntosMaquina, tConjuntoCartas cartasHumano, tConjuntoCartas cartasMaquina)
{
	int ganador = 0;
	if (puntosHumano <= 7.5 && puntosMaquina <= 7.5)
	{
		if (puntosHumano > puntosMaquina)
		{
			ganador = HUMANO;
		}
		else if (puntosHumano < puntosMaquina)
		{
			ganador = MAQUINA;
		}
		else
		{
			if (cartasHumano.contador < cartasMaquina.contador)
			{
				ganador = HUMANO;
			}
			else if (cartasHumano.contador > cartasMaquina.contador)
			{
				ganador = MAQUINA;
			}
			else
			{
				srand(time(NULL));
				ganador = 1 + rand() % (3 - 1);
			}
		}
	}
	else if (puntosHumano <= 7.5 && puntosMaquina > 7.5)
	{
		ganador = HUMANO;
	}
	else
	{
		ganador = MAQUINA;
		cout << "El humano se ha pasado" << endl;
	}
	return ganador;
}