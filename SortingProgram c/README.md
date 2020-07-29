# C Sortierprogramm

Erstellen Sie ein beliebigen Datentypen. Im Testprogramm ist beispielsweise der Datentyp TSample erstellt worden und hat folgende Struktur:

```c
//Beispielstruktur
typedef  struct Sample{
   int _id;
   float _pieces;
   double _size;
}TSample;

```

Wenn Sie als Wert des selbstdefinierten Datentypen einen primitiven Datentypen benutzen, definieren Sie über der Main-Funktion den Datentyp Ihres Wertes. Im Testprogramm soll nach der ID sortiert werden. Die ID ist vom Datentyp “int”, deswegen:

```c
DEFINE_UNKNOWNTYPE(int)

```

Falls sie **keinen** primitiven Datentypen als Wert Ihres selbstdefinierten Datentypen benutzen, müssen Sie zunächst folgende Funktion implementieren:

```c
void* biggerValue(void* valuex, void* valuey)

```

Diese Funktion bekommt zwei Werte als void* übergeben und soll den höheren Wert zurückgeben.  
Innerhalb der Main-Funktion muss Nun eine Liste erstellt werden. Da es in C per se keine Liste gibt, ist diese mit in Selectionsort Bibliothek enthalten und wird wie folgt deklariert/definiert:

```c
int  main()
{
   //Liste definieren.
   TPList sortlistData = newList();
   ...

```

Diese Liste bietet folgende Funktionen:

```c
TPList  newList();
bool  push(TPList*  list, void*  object, void*  value);
bool  pop(TPList*  list);
void*  getObject(int  index, TPList  list);
int  size(TPList  list);

```

> Falls die Anwendung der Funktionen unklar sind: Alle Funktionen sind umfangreich dokumentiert und Aufgabe, Rückgabewert und Parametererklärungen der Funktionen finden Sie in der Header-Datei.

Hier ein kleines Beispiel aus dem Testprogramm zum hinzufügen eines TSamples in die Liste:

```c
...
//Hier werden Beispielsweise einige Instancen des Typ Sample erstellt
//An dieser Stelle können aber auch beliebige Datentypen benutzt/erstellt werden.
TPSample sample = newSample(integern, floatn, doublen);

//erstellter Sample zur Liste hinzufügen
push(&sortlistData, (void*)sample, (void*)*getID(sample));
...

```

Nach dem Füllen der Liste kann nun die Sortierung stattfinden.

```c
sort(sortlistData, biggerValue);

```
