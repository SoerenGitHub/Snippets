#include "Selectionsort.t"
#include <iostream>
#include "Sample.h"
#include <vector>

using namespace std;

/*******************************************Testprogramm*******************************************/
//Dies ist ein Testprogramm, welche die Funktion demonstrieren soll. Deswegen gibt es keinerlei Sicherheitsabfragen bei der Eingabe.
int main()
{
	/*
	Vector von Pairs mit den Datentypen seiner Wahl definieren.
	Es soll in diesem Fall nach der ID von Sample sortiert werden.
	Die ID von Sample hat den Type Integer.
	Das Objekt Welches sortiert werden soll ist vom Type Sample.
	*/
	vector<pair<int, Sample>*>* sortlistData = new vector<pair<int, Sample>*>();



	string message = "ja";
	
	//Beliebig viele Datentypen erstellen
	while (message == "ja") {

		int integern;
		float floatn;
		double doublen;
		string stringn;

		//Die Eingabe der Werte soll durch den Benutzter erfolgen.
		cout << "Objekt erstellen:" << endl;
		cout << " Geben Sie einen Integer ein." << endl;
		cin >> integern;

		cout << " Geben Sie einen Float ein." << endl;
		cin >> floatn;

		cout << " Geben Sie einen Double ein." << endl;
		cin >> doublen;

		cout << " Geben Sie einen String ein." << endl;
		cin >> stringn;


		//Hier werden Beispielsweise einige Instancen des Typ Sample erstellt
		//An dieser Stelle koennen aber auch beliebige Datentypen benutzt/erstellt werden.
		//Natuerlich muss im vector der Pair ebenfalls angepasst sein.
		Sample* s = new Sample(integern, floatn, doublen, stringn);

		/*
		"s->getId()" ruft die ID der Instance auf, nach der sortiert werden soll.
		"*s" ist der Type, welcher sortiert werden soll.
		*/
		sortlistData->push_back(new pair<int, Sample>(s->getId(), *s));

		cout << "Wollen Sie einen weiteren Sample hinzufuegen? (ja/nein)" << endl;
		cin >> message;
	}


	//Hier eine Ausgabe der unsortierten Liste(Vector)
    cout << endl << "Sortierliste vorher:" << endl;
	for(std::pair<int, Sample>* var : *sortlistData)
	{
		cout << "id: " << var->second.getId() << endl;
	}

	//Instance von Selectionsort erstellen, als Parameter Die Liste(Vector), welche Sortiert weden soll.
	//Logischerweise muessen hier die richtigen Datentypen angegeben werden...
	Selectionsort<int, Sample>* selectionsort = new Selectionsort<int, Sample>(sortlistData);
	//Um die Sortierung zu starten
	selectionsort->sort();

	//Ausgabe der Liste(Vector) nach der Sortierung
	cout << "Sortierliste nachher:" << endl;
	for (pair<int, Sample>* var : *sortlistData)
	{
		cout << "id: " << var->second.getId() << endl;
	}
}