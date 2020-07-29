#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H
#include <stdlib.h>
#include "Selectionsort.h"
#include <stdio.h>

/***************Structs/Typedefs************/

//Listenstruktur
typedef struct List{
    //Anzahl an vorelementen
    int _size;
    //Wert eines Objektes
    void* _value;
    //Objekt
	void* _listelem;
    //Folgeelement
	TPList _next;
}TList;

/************intern***************/
/************List***************/
/*
	getElem
		Funktion:
			Gibt ein Element in der Liste zurück
		Rückgabewerte:
            Listen-Element
		Parameter:
			list = Liste in der alle Objekte enthalten sind und in dem ein Element zurückgegeben werden soll
            index = Stelle in der Liste, die zurückgegeben werden soll
*/
TPList getElem(int index, TPList list){
    TPList listelem = list;
    for(int i = 0; listelem != NULL && i < index; i++){
        listelem = listelem->_next;
    }
    return listelem;
}
/************Selectionsort***************/
/*
	swapT
		Funktion:
			Vertauschen der Objekte in der Liste(Vector)
		Parameter:
			left, right = Listenelemente, die vertauscht werden sollen
*/
void swapT(TPList left, TPList right) {
	//vorrübergehend Daten von Speicherstelle right speichern
    TList temp = *left;
	//an Speicherstelle left die Daten von Speicherstelle right einfügen
    left->_listelem = right->_listelem;
    left->_value = right->_value;
	//Temporärer Speicher an Speicherstelle right einfügen
    right->_listelem = temp._listelem;
    right->_value = temp._value;

}
/*
	minT
		Funktion:
			Findet das kleinste Element in der Liste
		Rückgabewerte:
            Listen-Element
		Parameter:
			list = Liste in der alle Objekte enthalten sind und das in dem das kleinste Element gefunden werden soll
            pointer = aktuelle Position der Sortierung  in der Liste.
            min =  kleinstes in der Rekursion bekannte Objekt (als Index) in der Liste.
*/
TPList minT(int pointer, int min, TPList list, void* (*biggerValue)(void*, void*))
{
    if(list != NULL){
        //Endkriterium
        if (pointer == list->_size) {
            return getElem(min, list);
        }
        //neues Objekt mit kleineren Wert?
        void* elempointer = (void*)&getElem(pointer, list)->_value;
        void* elemmin = (void*)&getElem(min, list)->_value;
        if (elemmin != NULL && elempointer != NULL){
            void* elembigger = biggerValue(elempointer, elemmin);
            if(elembigger != NULL && elembigger == elemmin){
                min = pointer;
            }
        }
        // Rekursion: finde kleinstes Element
        return minT(pointer + 1, min, list, biggerValue);
    }
	return NULL;
}
/*
	sort
		Funktion:
			Überladene Methode für das Starten der Sortierung (Selectionsort)
		Parameter:
            index = Merker auf den Index, bis zu dem bereits die Liste Sortiert ist
			list = Liste in der alle Objekte enthalten sind und in dem die Sortierung stattfinden soll
            biggerValue= Funktion, welche zwei Werte als void* entgegen nimmt und den größeren zurück gibt
*/
void sortRekursion(int index, TPList list, void* (*biggerValue)(void*, void*))
{
	// Endkriterium
	if (list && index == list->_size || !list) return;
	// Hole das kleinste Element und tausche es mit dem Pointer-Element
    TPList elem = getElem(index, list);
    TPList minelem = minT(index, index, list, biggerValue);
    if(elem && minelem) swapT(elem, minelem);
	// Rekursion: sortiere
	sortRekursion(index + 1, list, biggerValue);
}

/************public***************/
/************Selectionsort***************/
void sort(TPList list, void* (*biggerValue)(void*, void*)) {
	sortRekursion(0, list, biggerValue);
}

/************List***************/
bool push(TPList* list, void* object, void* value)
{
    //Liste erstellen
	TPList e;
	e = (TPList)malloc(sizeof(TList));
    //Erstellt?
	if (!e) return false;
    //Struktur definieren
	e->_listelem = object;
	e->_next = *list;
    e->_value = value;
	if(&(*list)->_size != NULL){
		e->_size = (*list)->_size+1;
	}else{
		e->_size = 1;
	}
    //neues Startelement festlegen	
	*list = e;
	return true;
}

bool pop(TPList* list)
{
	TPList e;
    //ist das Element != NULL => abbrechen
	if(!*list) return false;
    //Element bestimmen
	e = *list;
    //Startpunkt um eine Position zurücksetzen
	*list = (*list)->_next;
    //Speicher freigeben
	free(e);
	return true;
}

void* getObject(int index, TPList list){
    TPList listelem = list;
    for(int i = 0; listelem != NULL && i < index; i++){
        listelem = listelem->_next;
    }
    return listelem->_listelem;
}

TPList newList(){
    TPList list = NULL;
    return list;
}

int size(TPList list){
    return list->_size;
}

#endif

