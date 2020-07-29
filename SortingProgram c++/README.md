# C++ Sortierprogramm

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

Innerhalb der Main-Funktion muss Nun eine Liste erstellt werden. In C++ gibt es die Bibliothek “vector”, welche alle nötige Funktionen beinhaltet. Da wir zwei Datentypen für die Sortierung benötigen (Objekt welches sortiert werden soll, und sein Wert) müssen “pairs” benutzt werden.  
Inkludieren Sie also die Nötigen Bibliotheken und erstellen Sie einen Vector. Im Testprogramm soll nach der ID sortiert werden. Die ID ist vom Datentyp “int”, und das Objekt, welches Sortiert werden soll vom Datentyp Sample. Das Template muss also wie folgt definiert werden:

```c
#include  <iostream>
#include  <vector>
...
int  main()
{
   /*
   Vector von Pairs mit den Datentypen seiner Wahl definieren.
   Es soll in diesem Fall nach der ID von Sample sortiert werden.
   Die ID von Sample hat den Type Integer.
   Das Objekt Welches sortiert werden soll ist vom Type Sample.
   */
   vector<pair<int, Sample>*>* sortlistData = new  vector<pair<int, Sample>*>();
   ...

```

> **Wichtig:** Benutzen Sie Pointer für die Pairs.

Für die Sortierung der Liste ist es wichtig, dass Sie als Wert ihres Datentyps einen primitiven Datentypen verwenden.  
Füllen Sie nun die Liste. Hier ein Beispiel aus dem Testprogramm zum Hinzufügen von Objekten in die Liste:

```c
...
//Hier werden Beispielsweise einige Instancen des Typ Sample erstellt
//An dieser Stelle koennen aber auch beliebige Datentypen benutzt/erstellt werden.
//Natuerlich muss im vector der Pair ebenfalls angepasst sein.
Sample* s = new  Sample(integern, floatn, doublen, stringn);

/*
"s->getId()" ruft die ID der Instance auf, nach der sortiert werden soll.
"*s" ist der Type, welcher sortiert werden soll.
*/
sortlistData->push_back(new  pair<int, Sample>(s->getId(), *s));
...

```

Deklarieren und definieren Sie ein Objekt Selectionsort. Hier wieder ein Beispiel aus dem Testprogramm:

```c
    ...
   //Instance von Selectionsort erstellen, als Parameter Die Liste(Vector), welche Sortiert weden soll.
   //Logischerweise muessen hier die richtigen Datentypen angegeben werden...
   Selectionsort<int, Sample>* selectionsort = new  Selectionsort<int, Sample>(sortlistData);
   ...

```

Die Sortierung kann nun mit folgendem Beispiel gestartet werden:

```c
	...
	selectionsort->sort();
	...

```
