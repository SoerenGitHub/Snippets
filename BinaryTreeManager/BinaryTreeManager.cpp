#include <iostream>
#include "Graph.t"
#include "Node.t"
#include "Sample.h"

/*************************************************TESTPROGRAMM*************************************************/
//Dies ist ein Testprogramm, welche die Funktion demonstrieren soll. Deswegen gibt es keinerlei Sicherheitsabfragen bei der Eingabe.

int main()
{
	//Graph erstellen
	//In diesem Fall soll der Binäre Baum mit Type Sample gefüllt werden.
	//Als Wert benutze ich die ID -> Integer. Natürlich kann hier jeder primitiver Type benutzt werden.
    Graph<Sample, int>* g = new Graph<Sample, int>();

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
		//An dieser Stelle können aber auch beliebige Datentypen benutzt/erstellt werden.
		//Natürlich muss im Graph ebenfalls angepasst sein.
		Sample* s = new Sample(integern, floatn, doublen, stringn);

		/*
		"s->getId()" ruft die ID der Instance auf, nach der im Baum einsortiert werden soll.
		"*s" ist der Type, welcher im Binären Baum hinzugefügt werden soll.
		Wenn erfolgreich -> true;
		*/
		if (g->addNode(s, s->getId())) {
			cout << "Sample wurde hinzugefuegt!" << endl;
		}
		else {
			cout << "Sample wurde NICHT hinzugefuegt!" << endl;
		}

		cout << "Wollen Sie einen weiteren Sample hinzufuegen? (ja/nein)" << endl;
		cin >> message;
	}

	cout << "Hier, die Ausgabe des erstellten Binaeren Baumes:" << endl;
	g->printGraph();

	message = "ja";

	//Beliebig viele Suchen
	while (message == "ja") {
		int val;
		cout << "Geben Sie eine ID(Integer) ein, die Sie suchen." << endl;
		cin >> val;

		//Suche durchführen
		vector<Sample*>* searchlist = g->searchNode(val);

		//Ausgabe in Console
		cout << "Folgende Samples wurden gefunden:" << endl;
		for (Sample* sample : *searchlist) {
			sample->print();
		}

		cout << "Eine weitere Suche durchfuehren? (ja/nein)" << endl;
		cin >> message;
	}

	message = "ja";

	//Beliebig viele Löschungen
	while (message == "ja") {
		int val;
		cout << "Geben Sie eine ID(Integer) ein, die Sie loeschen moechten." << endl;
		cin >> val;

		//Weil Doppelte Werte erlaubt sind, ist ein Node nur mit Wert und Objekt Eindeutig identifizierbar.
		//Für das Testprogramm benutze ich deswegen unperformanterweise die Suche um das Objekt herauszufinden,
		// welches der Benutzer auch wirklich löschen möchte.
		vector<Sample*>* searchlist = g->searchNode(val);

		//Wenn die Suche nicht nur ein ergebnis zurückgibt
		if (searchlist->size() > 1) {
			cout << "Es wurden mehrere Samples gefunden:" << endl;
			for (unsigned int i = 0; i < searchlist->size(); i++) {
				//DELETEID definieren
				cout << "DELETEID: " << i << endl;
				(*searchlist)[i]->print();
			}

			int delid;

			cout << "Geben Sie eine DELETEID(Integer) an, welches Sample geloescht werden soll." << endl;
			cin >> delid;

			//Löschen des ausgewählten Samples. True, wenn erfolgreich gelöscht.
			if (g->deleteNode((*searchlist)[delid], val)) {
				cout << "Sample wurde entfernt!" << endl;
			}
			else {
				cout << "Sample wurde NICHT entfernt!" << endl;
			}

		}//Fall: Objekt ist Einzigartig -> Löschen
		else if (searchlist->size() == 1) {
			if (g->deleteNode((*searchlist)[0], val)) {
				cout << "Sample wurde entfernt!" << endl;
			}
			else {
				cout << "Sample wurde NICHT entfernt!" << endl;
			}
		}//Wenn das Objekt nicht existiert.
		else {
			cout << "Sample wurde NICHT entfernt!" << endl;
		}

		//Ausgabe des Graphens mit Einrückung
		cout << "Hier, die Ausgabe des Binaeren Baumes:" << endl;
		g->printGraph();

		cout << "Eine weitere Loeschung durchfuehren? (ja/nein)" << endl;
		cin >> message;
	}

	//Löschen des Graphens
    delete g;

}