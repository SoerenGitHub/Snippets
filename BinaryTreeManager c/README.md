# C Binärer Baum

Erstellen Sie ein beliebigen Datentypen. Im Testprogramm ist beispielsweise die Klasse TSample erstellt worden und hat folgende Struktur:

```c
//Beispielstruktur
   typedef  struct Sample{
   int _id;
   float _pieces;
   double _size;
}TSample;

```

Implementieren Sie eine Funktion “printObject” mit folgenden Parametern:

-   Datentyp: void* - Dieser Parameter ist eine Instance Ihres selbstdefinierten Datentyps als void*.
-   Datentyp: int - Dieser Parameter gibt das Level des Knotens im Graphen an und ist für die Einrückung notwendig.

Die Funktion “printObject” hat lediglich die Aufgabe ein einzelnes Objekt in der Konsole mit der richtigen Einrückung anzuzeigen.  
Hier ein Beispiel aus dem Testprogramm, wo lediglich die ID des Objektes in der Konsole ausgegeben werden soll:

```c
void  printObject(void* object, int  level){
	if(object != NULL){
		for(int i = 0; i < level; i++){
			printf("\t");
		}
		const  int d = ((TPSample)object)->_id;
		printf("node=%d\n", d);
	}else{
		for(int i = 0; i < level-1; i++){
			printf("\t");
		}
		printf("node=NULL\n");
	}
}

```

Wenn Sie als Wert des selbstdefinierten Datentypen einen primitiven Datentypen benutzen, definieren Sie über der Main-Funktion den Datentyp Ihres Wertes. Im Testprogramm sollen die Objekte, die hinzugefügt werden nach der ID im Binären Baum eingefügt werden. Die ID ist vom Datentyp “int”, deswegen:

```c
DEFINE_UNKNOWNTYPE(int)

```

Falls sie **keinen** primitiven Datentypen als Wert Ihres selbstdefinierten Datentypen benutzen, müssen Sie zunächst folgende Funktionen implementieren:

```c
void* biggerValue(void* valuex, void* valuey);
bool equalValues(void* valuex, void* valuey);

```

-   “biggerValue” bekommt zwei Werte als void* übergeben und soll den höheren Wert zurückgeben.
-   “equalValues” bekommt zwei Werte als void* übergeben und soll true zurück geben, wenn die Werte gleich sind.  
    Zum erstellen eines Graphen wird folgende Funktion benutzt:

```c
//Erstellen eines Graphen
void* graph = createGraph(biggerValue, equalValues);

```

Als Parameter werden die bereits definierten Funktionen übergeben.  
Nun kann der Graph mit der Funktion “addNode” gefüllt werden. Bei erfolgreichem hinzufügen des Objektes wird “true” zurückgegeben.

```c
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

```

> Falls die Anwendung der Funktionen unklar sind: Alle Funktionen sind umfangreich dokumentiert und Aufgabe, Rückgabewert und Parametererklärungen der Funktionen finden Sie in der Header-Datei.

Soll ein Node oder sogar der komplette Graph entfernt werden, benutzen Sie die Funktion “deleteNode”/“deleteGraph”. Auch hier wird als Rückgabewert “true” bei erfolgreichen Löschen zurückgegeben.

```c
bool  deleteNode(void*  graph, void*  object, void*  value);
bool  deleteGraph(void*  graph);

```

Weil gleiche Wert zugelassen werden wird bei der suche jedes Objekt zurückgegeben, welches den gesuchten Wert hat. Die gefundenen Objekte werden als Liste zurückgegeben. Die in “BinaryTreeManagerBip” enthaltene Liste bietet folgende Funktionen:

```c
TPList newList(); 
bool push(TPList* list,  
void* object,  void* value); 
bool pop(TPList* list);  
void* getObject(int index, TPList list);  
int  size(TPList list);
void*  getNext(TPList  list);

```

> Falls die Anwendung der Funktionen unklar sind: Alle Funktionen sind umfangreich dokumentiert und Aufgabe, Rückgabewert und Parametererklärungen der Funktionen finden Sie in der Header-Datei.

Hier ein Beispiel der Suche aus dem Testprogramm:

```c
//Suche durchführen
TPList searchlist = searchNode(graph, (void*)&val);

```

Um eine Ausgabe in der Konsole des Binären Baumes zu bekommen, benutzen Sie die Funktion “printGraph”:

```c
//Ausgabe des Graphens mit Einrückung
printf("Hier, die Ausgabe des Binaeren Baumes:\n");
printGraph(graph, printObject);

```

**Gleiche Schlüsselwerte:**  
Das Eintragen von Objekten mit gleichem Schlüsselwert ist möglich, wenn die Speicheradresse des Objektes, welches hinzugefügt werden soll, nicht bereits im Graphen existiert.
