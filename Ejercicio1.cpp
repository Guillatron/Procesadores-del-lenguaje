/*
Dada una maquina de estados, desarrollar una matriz de estados que permita
	- Analizar la validez de una cadena de texto
	- Dar todas las posibles cadenas de texto validas con limitaciones:
		--Deben salir un numero maximo de cadenas 
		--Deben tener como maximo un numero de caracteres
*/

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>	//Si no tienes windows yo comentaría esto
#include <list>
#include <set>

using namespace std;

//El orden de las letras representa el orden de las columnas de la matriz
string alfabeto = "ab";
set<int> finales{ 0 };	//Identificador de los estados finales

//(ab)* en este caso
int matriz[2][2] = { {1,-1} ,
					{-1, 0} };

//La clase almacena una cadena de la maquina y el estado en el que se encuentra
class Estado {
public:
	string cadena;
	int estado;

	Estado() {
		cadena = "";
		estado = 0;
	}

	Estado(string strInicial, int nEstado) {
		cadena = strInicial;
		estado = nEstado;
	}
};

//Se usa para calcular el indice de una letra en el alfabeto
//para obtener la columna de la matriz 
int findChar(char a) {
	for (int i = 0; i < alfabeto.size(); i++)
		if (a == alfabeto[i]) return i;
	return -1;
}


//Devuelve si la string responde al automata correctamente
bool valido(string palabra) {
	int nEstadoActual = 0;
	for (int i = 0; i < palabra.size(); i++) {
		if ( (nEstadoActual= matriz[nEstadoActual][findChar(palabra[i])]) == -1)
			return false;

	}
	return finales.find(nEstadoActual) != finales.end();
}


//Devuelve la lista de cadenas de acuerdo a los limites establecidos
list<string> cadenasPosibles(int nMaxCaracteres, int nMaxCadenas) {
	list<string> resultantes;	//Almacenará las cadenas resultantes
	list<Estado*> potenciales;	//Almacena las cadenas que pueden resultar en una cadena valida
	potenciales.push_back(new Estado());	//La primera cadena posible es "" en el estado 0

	while (potenciales.size() > 0 && resultantes.size() <= nMaxCadenas) {
		Estado* actual = potenciales.front();
		//Se comprueba si la string potencial es valida
		if (valido(actual->cadena) && actual->cadena.size()<nMaxCaracteres) resultantes.push_back(actual->cadena);	

		//Se crean cadenas a partir de una potencial, mirando las 
		for (int i = 0; i < alfabeto.size() && resultantes.size() <= nMaxCadenas; i++) {
			if (matriz[actual->estado][i] != -1){
				if (size(actual->cadena) < nMaxCaracteres) {
					potenciales.push_back(new Estado( actual->cadena + alfabeto[i], matriz[actual->estado][i]));
				}
			}
		}
		potenciales.pop_front();	//Una vez se ha desarrollado la cadena a todas sus posibles se deja de considerar
	}
	return resultantes;
}



int main() {
	list<string> cadenas = cadenasPosibles(10000,200);
	for (auto c : cadenas) cout << c << endl;
	_getch();
	return 0;
}
