#include "Selectionsort.h"
#include "Sample.h"
#include <stdio.h>
#include <stdlib.h>
/*******************************************Testprogramm*******************************************/
//Dies ist ein Testprogramm, welche die Funktion demonstrieren soll. Deswegen gibt es keinerlei Sicherheitsabfragen bei der Eingabe.

//Definiert biggerValue. Kann aber ebenfalls auch selber definiert werden.
DEFINE_UNKNOWNTYPE(int)

int main()
{
	
	//Liste definieren.
	TPList sortlistData = newList();

	char message = 'j';
	
	//Beliebig viele Datentypen erstellen
	while (message == 'j') {

		int integern;
		float floatn;
		double doublen;

		//Die Eingabe der Werte soll durch den Benutzter erfolgen.
		printf("Objekt erstellen:\n");
		printf(" Geben Sie einen Integer ein.\n");
		scanf("%d",&integern); 

		printf(" Geben Sie einen Float ein.\n");
		scanf("%f",&floatn); 

		printf(" Geben Sie einen Double ein.\n");
		scanf("%lf",&doublen); 


		//Hier werden Beispielsweise einige Instancen des Typ Sample erstellt
		//An dieser Stelle können aber auch beliebige Datentypen benutzt/erstellt werden.
		TPSample sample = newSample(integern, floatn, doublen);

        //erstellter Sample zur Liste hinzufügen
		push(&sortlistData, (void*)sample, (void*)*getID(sample));

		printf("Wollen Sie einen weiteren Sample hinzufuegen? (j/n)\n");
		scanf(" %c", &message);
	}


	//Hier eine Ausgabe der unsortierten Liste
    printf("Unsortierte Liste:\n");
    for(int i = 0; i < size(sortlistData); i++){
        TPSample ausgabe = (TPSample)getObject(i, sortlistData);
        printf("ID=%d\n", *getID(ausgabe));
    }

	//Um die Sortierung zu starten
	sort(sortlistData, biggerValue);

	//Hier eine Ausgabe der Liste nach der Sortierung
    printf("Sortierte Liste:\n");
    for(int i = 0; i < size(sortlistData); i++){
        TPSample ausgabe = (TPSample)getObject(i, sortlistData);
        printf("ID=%d\n", *getID(ausgabe));
    }
}