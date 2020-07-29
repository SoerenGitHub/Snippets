/*******************************************Testprogramm*******************************************/
//Dies ist ein Testprogramm, welche die Funktion demonstrieren soll. Deswegen gibt es keinerlei Sicherheitsabfragen bei der Eingabe.
#include <string.h>
#include "BinaryTreeManagerBip.h"
#include "Sample.h"

DEFINE_UNKNOWNTYPE(int);

int main()
{

    //Erstellen eines Graphen
    void* graph = createGraph(biggerValue, equalValues);

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
		//Natürlich muss im Graph ebenfalls angepasst sein.
		TPSample node = newSample(integern, floatn, doublen);

		/*
		"s->getId()" ruft die ID der Instance auf, nach der im Baum einsortiert werden soll.
		"*s" ist der Type, welcher im Binären Baum hinzugefügt werden soll.
		Wenn erfolgreich -> true;
		*/
		if (addNode(graph, (void*)node, (void*)getID(node))) {
			printf("Sample wurde hinzugefuegt!\n");
		}
		else {
			printf("Sample wurde NICHT hinzugefuegt!\n");
		}

		printf("Wollen Sie einen weiteren Sample hinzufuegen? (j/n)\n");
		scanf(" %c", &message);
	}

    printf("Hier, die Ausgabe des erstellten Binaeren Baumes:\n");
    printGraph(graph, printObject);

    message = 'j';

	//Beliebig viele Suchen
	while (message == 'j') {
		int val;
		printf("Geben Sie eine ID(Integer) ein, die Sie suchen.\n");
		scanf("%d",&val); 

		//Suche durchführen
		TPList searchlist = searchNode(graph, (void*)&val);

		//Ausgabe in Console
		printf("Folgende Samples wurden gefunden:\n");
		while(searchlist != NULL) {
			printObject(getObject(0,searchlist), 0);
            searchlist = getNext(searchlist);
		}

		printf("Eine weitere Suche durchfuehren? (j/n)");
		scanf(" %c", &message);
	}

    message = 'j';


	//Beliebig viele Löschungen
	while (message == 'j') {
		int val;
		printf("Geben Sie eine ID(Integer) ein, die Sie loeschen moechten.\n");
		scanf("%d",&val); 

		//Weil Doppelte Werte erlaubt sind, ist ein Node nur mit Wert und Objekt Eindeutig identifizierbar.
		//Für das Testprogramm benutze ich deswegen unperformanterweise die Suche um das Objekt herauszufinden,
		// welches der Benutzer auch wirklich löschen möchte.
		TPList searchlist = searchNode(graph, (void*)&val);

		//Wenn die Suche nicht nur ein ergebnis zurückgibt
		if (size(searchlist) > 1) {
			printf("Es wurden mehrere Samples gefunden:\n");
			for (unsigned int i = 0; searchlist != NULL; i++) {
				//DELETEID definieren
				printf("DELETEID: %d\n", i);
				printObject(getObject(0, searchlist), 0);
                searchlist = getNext(searchlist);
			}

			int delid;

			printf("Geben Sie eine DELETEID(Integer) an, welches Sample geloescht werden soll.\n");
			scanf("%d",&delid); 

            searchlist = searchNode(graph, (void*)&val);
            
			void* object = getObject(delid,searchlist);

			if(object != NULL){
				//Löschen des ausgewählten Samples. True, wenn erfolgreich gelöscht.
				if (deleteNode(graph, object, (void*)&val)) {
					printf("Sample wurde entfernt!\n");
				}
				else {
					printf("Sample wurde NICHT entfernt!\n");
				}
			}else {
				printf("Sample wurde NICHT entfernt! Grund: Null\n");
			}
			

		}//Fall: Objekt ist Einzigartig -> Löschen
		else if (size(searchlist) == 1) {
			if (deleteNode(graph, getObject(0,searchlist), (void*)&val)) {
				printf("Sample wurde entfernt!\n");
			}
			else {
				printf("Sample wurde NICHT entfernt!\n");
			}
		}//Wenn das Objekt nicht existiert.
		else {
			printf("Sample wurde NICHT entfernt!\n");
		}

		//Ausgabe des Graphens mit Einrückung
		printf("Hier, die Ausgabe des Binaeren Baumes:\n");
        printGraph(graph, printObject);

		printf("Eine weitere Loeschung durchfuehren? (j/n)\n");
		scanf(" %c", &message);
	}

    if(deleteGraph(graph)){
        printf("Graph geloescht\n");
    }
}