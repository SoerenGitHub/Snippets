#ifndef SELECTIONSORT_T
#define SELECTIONSORT_T
#include <vector>
#include <iostream>
using namespace std;

template <class TSort, class T>
class Selectionsort {
	private:
		//zu sortierende Liste(Vector)
		vector<pair<TSort, T>*>* m_objects;
		//vertauschen der Objekte in der Liste(Vector)
		void swapT(pair<TSort, T>* left, pair<TSort, T>* right) {
			//vorruebergehend Daten von Speicherstelle right speichern
			pair<TSort, T> temp = *left;
			//an Speicherstelle left die Daten von Speicherstelle right einf�gen
			*left = *right;
			//Temporaerer Speicher an Speicherstelle right einf�gen
			*right = temp;
		}

		/*Kleinstes Objekt in der Liste(Vector) finden.
		* pointer = aktuelle Position der Sortierung (als Index) in der Liste(Vector).
		* min =  kleinstes in der Rekursion bekannte Objekt (als Index) in der Liste(Vector).
		*/
		pair<TSort, T>* minT(int pointer, int min)
		{
			//Endkriterium
			if (pointer == m_objects->size()) {
				return (*m_objects)[min];
			}

			//kleiner?
			if ((*m_objects)[pointer]->first <= (*m_objects)[min]->first) {
				min = pointer;
			}

			// Rekursion: finde kleinstes Element
			return minT(pointer + 1, min);
		}

		//ueberladene Methode fuer das Starten der Sortierung (Selectionsort)
		void sort(int index)
		{
			// Endkriterium
			if (index == m_objects->size())
				return;

			// Hole das kleinste Element und tausche es mit dem Pointer-Element
			swapT((*m_objects)[index], minT(index, index));

			// Rekursion: sortiere
			sort(index + 1);
		}

	public:
		/*Uebergabe der zu sortierenden Liste(Vector) "objects".
		* TSort = (primitiver) Datentyp, welcher fuer die Sortierung benutzt wird.
		* T = zu sortierender Datentyp.
		*/
		Selectionsort(vector<std::pair<TSort, T>*>* objects) : m_objects(objects) {

		}

		void sort() {
			sort(0);
		}
};

#endif

