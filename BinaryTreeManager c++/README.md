# C++ Binärer Baum

Erstellen Sie ein beliebigen Datentypen. Im Testprogramm ist beispielsweise die Klasse Sample erstellt worden und hat folgende Struktur:

```c
class  Sample
{
   private:
   	int m_id;
   	float m_pieces;
   	double m_size;
   	string m_name;
   public:
   	Sample(int  id, float  pieces, double  size, string  name);
   	int  getId();
   	float  getPieces();
   	double  getSize();
   	string  getName();
};

```

Erstellen Sie ein Objekt vom Type “Graph”. Im Testprogramm soll nach der ID in den Binären Baum einsortiert werden. Die ID ist vom Datentyp “int”, und das Objekt, welches hinzugefügt werden soll vom Datentyp Sample. Das Template muss also wie folgt definiert werden:

```c
//Graph erstellen
//In diesem Fall soll der Binaere Baum mit Type Sample gefuellt werden.
//Als Wert benutze ich die ID -> Integer. Natuerlich kann hier jeder primitiver Type benutzt werden.
Graph<Sample, int>* g = new  Graph<Sample, int>();

```

Zum hinzufügen von Knoten innerhalb des Graphens wird die Funktion “addNode” benutzt. diese gibt “true” zurück, wenn der Knoten erfolgreich hinzugefügt wurde. Beispiel:

```c
//Hier werden Beispielsweise einige Instancen des Typ Sample erstellt
//An dieser Stelle koennen aber auch beliebige Datentypen benutzt/erstellt werden.
//Natuerlich muss im Graph ebenfalls angepasst sein.
Sample* s = new  Sample(integern, floatn, doublen, stringn);

/*
"s->getId()" ruft die ID der Instance auf, nach der im Baum einsortiert werden soll.
"*s" ist der Type, welcher im Binaeren Baum hinzugefuegt werden soll.
Wenn erfolgreich -> true;
*/
if (g->addNode(s, s->getId())) {
	cout << "Sample wurde hinzugefuegt!" << endl;
}
else {
	cout << "Sample wurde NICHT hinzugefuegt!" << endl;
}

```

Benutzen Sie die Funktion "printGraph, um die Struktur des Graphens auszugeben.

```c
cout << "Hier, die Ausgabe des erstellten Binaeren Baumes:" << endl;
g->printGraph();

```

Suchen Sie einen Knoten mit:

```c
vector<Sample*>* searchlist = g->searchNode(val);

```

Um einen Knoten wieder zu Entfernen, benutzen Sie die Funktion “deleteNode”. Der Rückgabewert gibt “true” zurück, wenn der Löschvorgang erfolgreich war. Hier ein Beispiel aus dem Testprogramm:

```c
//Loeschen des ausgewaehlten Samples. True, wenn erfolgreich geloescht.
if (g->deleteNode((*searchlist)[delid], val)) {
	cout << "Sample wurde entfernt!" << endl;
}
else {
	cout << "Sample wurde NICHT entfernt!" << endl;
}

```

Soll ein Graph wieder entfernt werden, und der Speicher wieder freigegeben werden, machen Sie folgendes:

```c
//Loeschen des Graphens
delete g;

```

**Gleiche Schlüsselwerte:**  
Das Eintragen von Objekten mit gleichem Schlüsselwert ist möglich, wenn die Speicheradresse des Objektes, welches hinzugefügt werden soll, nicht bereits im Graphen existiert.
