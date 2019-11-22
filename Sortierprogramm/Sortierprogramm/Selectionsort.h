#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H
#include <vector>
#include <iostream>
using namespace std;

template <class TSort, class T>
class Selectionsort {
	private:
		//zu sortierende Liste(Vector)
		vector<pair<TSort, T>*>* m_objects;
		//vertauschen der Objekte in der Liste(Vector)
		void swapT(pair<TSort, T>* left, pair<TSort, T>* right);
		/*Kleinstes Objekt in der Liste(Vector) finden.
		* pointer = aktuelle Position der Sortierung (als Index) in der Liste(Vector).
		* min =  kleinstes in der Rekursion bekannte Objekt (als Index) in der Liste(Vector).
		*/
		pair<TSort, T>* minT(int pointer, int min);
		//überladene Methode für das Starten der Sortierung (Selectionsort)
		void sort(int index);
	public:
		/*Übergabe der zu sortierenden Liste(Vector) "objects".
		* TSort = (optimalerweise primitiver) Datentyp, welcher für die Sortierung benutzt wird.
		* T = zu sortierender Datentyp.
		*/
		Selectionsort(vector<pair<TSort, T>*>* objects);
		void sort();
};

/*Auf Grund des verwendens von Templates ist es zu Laufzeitfehlern gekommen.
* Die gesamte Problematik ist hier beschrieben: www.example.de
* Folglich folgender Include.
*/
//#include "Selectionsort.cpp"

#endif

