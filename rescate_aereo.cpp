/*
* @author PinkOBoy
*/
#include <iostream>
#include <vector>
using namespace std;

// - TIPOS PERSONALIZADOS -----------------------------------------------
// - DEFINED TYPES

struct tIntervalo {
	int inicio;	// Posicion de inicio del intervalo // Starting position of the segment
	int fin;	// Posicion de fin del intervalo // Ending position of the segment
};

// - PROTOTIPOS ---------------------------------------------------------
// - PROTOTYPES

/* PRECONDITION:
* 
*	0 < v.size()
* ^
*	EXISTE e : 0 <= e < v.size() : v[e] > altura
*/
tIntervalo resolver(
	const vector<int>& edificios,	// Alturas de los edificios // Buildings' height
	int altura						// Altura de vuelo del transbordador // Aircraft's flight height
); // return {a, b};
/* POSTCONDITION: 
* 
*	MAX b - a : 0 <= a <= b < v.size() :
*		(PARA_TODO w : a <= w <= b : v[w] > altura)
*/

// - MAIN ----------------------------------------------------------------

void solve() {
	// read solution
	int n, h;
	cin >> n >> h;

	vector<int> v(n);
	for (int i = 0; i < n; ++i)
		cin >> v[i];

	// compute solution
	tIntervalo sol = resolver(v, h);

	// write solution
	cout << sol.inicio << ' ' << sol.fin << endl;
}

int main() {
	int c;
	cin >> c;

	for (int i = 0; i < c; ++i)
		solve();

	return 0;
}

// - IMPLEMENTACION -----------------------------------------------------
// - IMPLEMENTATION

/* COMPLEJIDAD DEL ALGORITMO // COMPLEXITY OF THE ALGORITHM
* 
* - SPANISH -------------------------------------------------------------
* Todas las instrucciones ejecutadas tienen un coste de eficiencia constante.
* Existe un bucle en el algoritmo que ejecuta cierta cantidadd de instrucciones
* sobre todos los elementos del vector.
* 
* Definiendo:
* 
*	n ::= numero de elementos del vector = edificios.size()
* 
* Podemos afirmar que la complejidad de nuestro algoritmo sera de:
* 
*	O(n)
* 
* - ENGLISH -------------------------------------------------------------
* Every executed instruction has a costant efficiency cost. A loop exists in the
* algorithm which executes certain amount of instructions on every vector's
* element.
* 
* By defining:
* 
*	n ::= amount of elements of the vector = edificios.size()
* 
* We can affirm the complexity of our algorithm is:
* 
*	O(n)
*/

tIntervalo resolver(
	const vector<int>& edificios,
	int altura
) {
	tIntervalo sol = { 1, -1 }; // Default distance = -2
	int headCurrentSegment = 0;

	/* FUNCION DE COTA
	* fc(x) = edificios.size() - i
	*/
	
	for (int i = 0; i < edificios.size(); ++i) {

		// Si el transporte se puede ocultar tras el edificio
		// If the aircraft can hide behind the building
		
		if (edificios[i] > altura) {

			// Si es el segmento mas largo encontrado
			// If it is the longest segment found

			if (i - headCurrentSegment > sol.fin - sol.inicio) {
				sol.inicio = headCurrentSegment;
				sol.fin = i;
			}
		}

		/*
		* Si no se puede ocultar, el segmento anterior queda
		* cerrado y ya marcado como el mas largo, en caso de
		* serlo.
		*
		* Ponemos el valor de inicio del segmento a la siguiente
		* posicion por analizar.
		*/
		/*
		* If it cannot hide, the segment ends and gets marked as
		* the longest, if it actually is.
		*
		* We assign the next position to analyze to the head of
		* the current segment
		*/

		else
			headCurrentSegment = i + 1;
	}

	/* INVARIANTE
	*	0 <= i <= v.size()
	* ^
	*	-1 <= sol.inicio <= sol.fin <= i
	* ^
	*	0 <= headCurrentSegment
	* ^
	*	PARA_TODO e : headCurrentSegment <= e <= i : v[e] > altura
	*/

	return sol;
}