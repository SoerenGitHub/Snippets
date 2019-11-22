#include "Selectionsort.h"

template<class TSort, class T>
Selectionsort<TSort, T>::Selectionsort(vector<std::pair<TSort, T>*>* objects) : m_objects(objects){

}


template<class TSort, class T>
void Selectionsort<TSort, T>::swapT(pair<TSort, T>* left, pair<TSort, T>* right) {
	//vorrübergehend Daten von Speicherstelle right speichern
	pair<TSort, T> temp = *left;
	//an Speicherstelle left die Daten von Speicherstelle right einfügen
	*left = *right;
	//Temporärer Speicher an Speicherstelle right einfügen
	*right = temp;
}

//Gibt den kleinsten Wert zurück
template<class TSort, class T>
pair<TSort, T>* Selectionsort<TSort, T>::minT(int pointer, int min)
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

template<class TSort, class T>
void Selectionsort<TSort, T>::sort() {
	sort(0);
}

template<class TSort, class T>
void Selectionsort<TSort, T>::sort(int index)
{
	// Endkriterium
	if (index == m_objects->size())
		return;

	// Hole das kleinste Element und tausche es mit dem Pointer-Element
	swapT((*m_objects)[index], minT(index, index));
	
	// Rekursion: sortiere
	sort(index + 1);
}