#include <stdbool.h>
/***************Structs/Typedefs************/
//Liste welche benutzt werden soll
typedef struct List* TPList;
/***********************Macros/***********************/
#define DEFINE_UNKNOWNTYPE(type)\
\
void* biggerValue(void* valuex, void* valuey){\
    type* a = (type*) valuex;\
    type* b = (type*) valuey;\
\
    if(*a < *b){\
        return b;\
    }else{\
        return a;\
    }\
}\
/***************Functions************/
/***************List************/
/*
	newList
		Funktion:
			Erstellt ein Objekt vom Type List
		Rückgabewerte:
            Objekt vom Type List
*/
TPList newList();
/*
	push
		Funktion:
			Fügt ein Objekt der Liste hinzu
		Rückgabewerte:
			true = erfolgreich hinzugefügt
            false = hinzufügen fehlgeschlagen
		Parameter:
			list = Liste in der alle Objekte enthalten sind und in dem das Objekt hinzugefügt werden soll
            object = Beliebiges Objekt als void*
            value = Beliebiger Wert mit primitiven Datentyp als void*
*/
bool push(TPList* list, void* object, void* value);
/*
	pop
		Funktion:
			Löscht ein Objekt in der Liste
		Rückgabewerte:
			true = erfolgreich gelöscht
            false = Löschen fehlgeschlagen
		Parameter:
			list = Liste in der alle Objekte enthalten sind und in dem das letzte Objekt gelöscht werden soll
*/
bool pop(TPList* list);
/*
	getObject
		Funktion:
			Gibt ein Objekt in der Liste zurück
		Rückgabewerte:
			Objekt in der Liste an stelle "index"
		Parameter:
			list = Liste in der alle Objekte enthalten sind und in dem ein Objekt wiedergegeben werden soll
            index = Stelle in der Liste, in der das Objekt zurückgegeben werden soll
*/
void* getObject(int index, TPList list);
/*
	size
		Funktion:
			Gibt die anzahl der Elemente in der Liste an
		Rückgabewerte:
			Anzahl an Elementen in der Liste
		Parameter:
			list = Liste in der alle Objekte enthalten sind und in welcher die Anzahl aller Elemente zurückgegeben werden soll
*/
int size(TPList list);
/***************Selectionsort************/
/*
	sort
		Funktion:
			Sortiert die definierte Liste mit Selectionsort
		Parameter:
			list = Liste in der alle Objekte enthalten sind und in dem die Sortierung stattfinden soll
            biggerValue= Funktion, welche zwei Werte als void* entgegen nimmt und den größeren zurück gibt
*/
void sort(TPList list, void* (*biggerValue)(void*, void*));