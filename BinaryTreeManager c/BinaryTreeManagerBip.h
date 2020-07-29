#ifndef BINARYTREEMANAGER_H
#define BINARYTREEMANAGER_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
\
bool equalValues(void* valuex, void* valuey){\
    type* obj = (type*) valuex;\
    type* val = (type*) valuey;\
\
    if(*obj == *val){\
        return true;\
    }\
    return false;\
}\


/***********************Structs/Typdefs***********************/
//Liste zum auswerten der Suche
typedef struct List* TPList;
/***********************Functions***********************/
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
bool push(TPList* list, void* object);
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
			list = Liste in der alle Objekte enthalten sind und in dem das letzte Objekt gelöscht werden soll
            index = Stelle in der Liste, in der das Objekt zurückgegeben werden soll
*/
void* getObject(int index, TPList list);
/*
	getNext
		Funktion:
			Gibt das nächste Objekt in der Liste zurück
		Rückgabewerte:
			Objekt in der Liste an nächster Stelle
		Parameter:
			list = Liste in der alle Objekte enthalten sind und in dem das nächste Element zurückgegeben werden soll
*/
void* getNext(TPList list);
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

/***********************Graph***********************/
/*
	createGraph
		Funktion:
			Erstellt einen Graphen
		Rückgabewerte:
			NULL = fehlgeschlagen
			sonst Pointer auf den Graphen
        Parameter:
			biggerValue = 	Funktion, welche zwei Werte der selbstbestimmten Objecte als void* entgegen nimmt
                        	und den höheren Wert zurück gibt.
			equalsValue = 	Funktion, welche zwei Werte der selbstbestimmten Objecte als void* entgegen nimmt
                        	und true zurück gibt, wenn die Werte gleich sind.
*/
void *createGraph();
/*
	deleteGraph
		Funktion:
			Entfernt einen Graphen
		Rückgabewerte:
			true = erfolgreich gelöscht
			false = Löschen fehlgeschlagen
		Parameter:
			graph = void-Pointer auf einen Graphen
*/
bool deleteGraph(void* graph);
/*
	addNode
		Funktion:
			Fügt ein Node dem Graphen hinzu
		Rückgabewerte:
			true = erfolgreich hinzugefügt
			false = Hinzufügen fehlgeschlagen
		Parameter:
			graph = void-Pointer auf einen Graphen
			object = void* auf das Objekt welches als Knoten hinzugefügt werden soll
			value = void* auf den Wert eines Objekts
*/
bool addNode(void* graph, void* object, void* value);
/*
	printGraph
		Funktion:
			gibt den Graphen in der Konsole aus
		Parameter:
			graph = void-Pointer auf einen Graphen
			printObject = 	Funktion, welche ein selbstbestimmtes Object als void* entgegen nimmt
                        	und das Objekt in der Konsole ausgibt.der Integer gibt das Level(Einrückung) an.
							WICHTIG: Die Funktion muss mit NULL umgehen können!
*/
void printGraph(void* graph, void (*printObject)(void*, int));
/*
	searchNode
		Funktion:
			sucht nach einem Objekt zu einem Wert
		Parameter:
			graph = void-Pointer auf einen Graphen
			value = void* auf den Wert eines Objekts
*/
TPList searchNode(void* graph, void* value);
/*
	deleteNode
		Funktion:
			gibt den Graphen in der Konsole aus
		Parameter:
			graph = void-Pointer auf einen Graphen
			object = void* auf das zu löschende Objekt
			value = void* auf den Wert eines Objekts
*/
bool deleteNode(void* graph, void* object, void* value);
#endif