#include "Selectionsort.h"
#include "Selectionsort.cpp"
#include <iostream>
#include "Sample.h"
#include <vector>

using namespace std;

int main()
{
	/*
	Vector von Pairs mit den Datentypen seiner Wahl definieren.
	Es soll in diesem Fall nach der ID von Sample sortiert werden.
	Die ID von Sample hat den Type Integer.
	Das Objekt Welches sortiert werden soll ist vom Type Sample.
	*/
	vector<pair<int, Sample>*>* sortlistData = new vector<pair<int, Sample>*>();

	//Hier werden Beispielsweise einige Instancen des Typ Sample erstellt
	Sample* s1 = new Sample(3, 3.2f, 2.4, "y");
	Sample* s2 = new Sample(2, 3.6f, 4.1, "b");
	Sample* s3 = new Sample(1, 4.2f, 9.12, "c");
	Sample* s4 = new Sample(8, 3.2f, 1.1, "f");
	Sample* s5 = new Sample(7, 9.2f, 0.1, "z");
	Sample* s6 = new Sample(6, 13.2f, 7.5, "m");
	Sample* s7 = new Sample(9, 13.3f, 45.0, "o");
	Sample* s8 = new Sample(0, 3.21f, 13.12, "g");

	/*
	"sx->getId()" ruft die ID der Instance auf, nach der sortiert werden soll.
	"*sx" ist der Type, welcher sortiert werden soll.
	*/
	sortlistData->push_back(new pair<int, Sample>(s1->getId(), *s1));
	sortlistData->push_back(new pair<int, Sample>(s2->getId(), *s2));
	sortlistData->push_back(new pair<int, Sample>(s3->getId(), *s3));
	sortlistData->push_back(new pair<int, Sample>(s4->getId(), *s4));
	sortlistData->push_back(new pair<int, Sample>(s5->getId(), *s5));
	sortlistData->push_back(new pair<int, Sample>(s6->getId(), *s6));
	sortlistData->push_back(new pair<int, Sample>(s7->getId(), *s7));
	sortlistData->push_back(new pair<int, Sample>(s8->getId(), *s8));

	//Hier eine Ausgabe der unsortierten Liste(Vector)
    cout << "Sortierliste vorher:" << endl;
	for(std::pair<int, Sample>* var : *sortlistData)
	{
		cout << "id: " << var->second.getId() << endl;
	}

	//Instance von Selectionsort erstellen, als Parameter Die Liste(Vector), welche Sortiert weden soll.
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