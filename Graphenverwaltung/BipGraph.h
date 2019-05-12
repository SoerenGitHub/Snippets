/*********WICHTIG!*************
	Alle ID's müssen Positiv sein ( 1 aufwärts), andernfalls ist dies keine gültige ID.
*/

#ifndef BipGraph_H
#define BipGraph_H

/*
Speicherstruktur der Attribute.
Benutzen Sie diese Struktur um Attribute von Edges und Nodes zu definieren und
das Abspeichern eines Graphens zu ermöglichen.
 */
typedef struct SaveList* TPSaveList;

// id = ID des Edges oder Nodes, attr = vorgegebenes Attribut (int oder String) in form eines Void-Pointers.
// next = Nächstes Element in der Liste

//Wichtig! Das letzte Element in dieser Liste muss NULL sein!
typedef struct SaveList{
	int id;
	void* attr;
	TPSaveList next;
}TSaveList;


/*
	createGraph
		Funktion:
			Erstellt einen Graphen
		Rückgabewerte:
			NULL = fehlgeschlagen
			sonst Pointer auf den Graphen
*/
void *createGraph();
/*
	deleteGraph
		Funktion:
			Entfernt einen Graphen
		Rückgabewerte:
			0 = Löschen fehlgeschlagen
			1 = erfolgreich gelöscht
		Parameter:
			graph = void-Pointer auf einen Graphen
*/
int deleteGraph(void* graph);
/*
	nodeExist
		Funktion:
			Prüft ob ein Node Existiert
		Rückgabewerte:
			0 = Node existiert nicht
			1 = 	Node existiert
		Parameter:
			id = ID des Knotens
			graph = void-Pointer auf einen Graphen
*/
int nodeExist(void* graph, int id);
/*
	createNode
		Funktion:
			Erstellt einen Knoten
		Rückgabewerte:
			-2 = konnte nicht erstellt werden
			-1 = keine gültige ID
			0 = ID existiert bereits
			alles größer 0 = ID des neuen Knotens		
		Parameter:
			id = ID des zu erstellenden Knotens
			graph = void-Pointer auf einen Graphen
			value = void-pointer auf Wert des Knotens
*/
int createNode(void* graph, int id, void* value);
/*
	deleteNode
		Funktion:
			Entfernt einen Knoten
		Rückgabewerte:
			1 = erfolgreich gelöscht
			0 = Knoten existiert nicht
		Parameter:
			id = ID eines Knotens
			graph = void-Pointer auf einen Graphen
*/
int deleteNode(void* graph, int id);
/*
	getFirstNode
		Funktion:
			Gibt die ID des ersten Knotens zurück
		Rückgabewerte:
			0 = keine Knoten vorhanden
			alles andere = ID des Knotens
		Parameter:
			graph = void-Pointer auf einen Graphen
*/
int getFirstNode(void* graph);
/*
	getNextNode
		Funktion:
			Gibt die ID des nächsten Knoten zurück
		Rückgabewerte:
		   -1 = angegebene Knoten existiert nicht
			0 = kein nächster Knoten vorhanden
			alles größer 0 = ID des nächsten Knotens
		Parameter:
			graph = void-Pointer auf einen Graphen
			idnode = ID eines Knotens dessen nächsten Knoten man erhalten möchte
*/
int getNextNode(void* graph, int idnode);
/*
	changeNodeID
		Funktion:
			Verändert die ID eines Knotens
		Rückgabewerte:
			-1 = keine gültige ID
			0 = Knoten existiert nicht
			1 = erfolgreich geändert
		Parameter:
			id = ID eines Knotens
			newid = neue ID des Knotens
			graph = void-Pointer auf einen Graphen
*/
int changeNodeID(int id, int newid, void* graph);
/*
	changeNodeValue
		Funktion:
			Verändert den Namen eines Knotens
		Rückgabewerte:
			0 = Knoten existiert nicht
			1 = erfolgreich geändert
		Parameter:
			id = ID eines Knotens
			graph = void-Pointer auf einen Graphen
			value = void-Pointer auf Wert des Knotens
*/
int changeNodeValue(int id, void* value, void* graph);
/*
	getNodeValue
		Funktion:
			Gibt den Wert eines Knotens zurück
		Rückgabewerte:
			NULL = Knoten existiert nicht
			alles andere = Wert
		Parameter:
			id = ID eines Knotens
			graph = void-Pointer auf einen Graphen
*/
void* getNodeValue(int id, void* graph);
/*
	edgeExist
		Funktion:
			Prüft ob ein Edge Existiert
		Rückgabewerte:
			0 = Edge existiert nicht
			1 = 	Edge existiert
		Parameter:
			id = ID der Kante
			graph = void-Pointer auf einen Graphen
			nodeid = id eines knotens
*/
int edgeExist(void* graph, int id);
/*
	createEdge
		Funktion:
			Erstellt eine Kante
		Rückgabewerte:
			-4 = konnte kante konnte nicht erstellt werden
			-3 = keine gültige ID
			-2 = fromnode existiert nicht
			-1 = tonode existiert nicht
			0 = ID existiert bereits
			alles größer 0 = ID der Kante	
		Parameter:
			id = ID der Kante
			value = Int-Wert der Kante als void-Pointer
			fromnode = Der Startknoten
			tonode = Der Endknoten
			(Kante verläuft von dem Start- zu dem Endknoten)
			graph = void-Pointer auf einen Graphen
*/
int createEdge(int id, void* value, int fromnode, int tonode, void* graph);
/*
	getEdgeValue
		Funktion:
			Gibt den Wert einer Kante zurück
		Rückgabewerte:
			NULL = Kante existiert nicht
			alles andere = pointer auf den Wert
		Parameter:
			id = ID einee Kante
			graph = void-Pointer auf einen Graphen
*/
void* getEdgeValue(int id, void* graph);
/*
	getFirstEdgeIn
		Funktion:
			Gibt die ID der ersten einlaufenden Kante zurück
		Rückgabewerte:
		   -1 = Knoten existiert nicht
			0 = keine Kante vorhanden
			alles andere = ID der Kante
		Parameter:
			id = ID eines Knotens
			graph = void-Pointer auf einen Graphen
*/
int getFirstEdgeIn(int id, void* graph);
/*
	getNextEdgeIn
		Funktion:
			Gibt die ID der nächsten einlaufenden Kante zurück
		Rückgabewerte:
		   -3 = angegebene Kante ist keine einlaufende Kante zu dem von Ihnen angegebenen Knoten
		   -2 = angegebene Knoten existiert nicht
		   -1 = angegebene Kante existiert nicht
			0 = keine nächste Kante vorhanden
			alles größer 0 = ID des nächsten Knotens
		Parameter:
			idedge = ID einer Kante dessen nächsten Kante man erhalten möchte
			idnode = ID des Knotens
			graph = void-Pointer auf einen Graphen
*/
int getNextEdgeIn(int idnode, int idedge, void* graph);
/*
	getFirstEdgeOut
		Funktion:
			Gibt die ID der ersten auslaufenden Kante zurück
		Rückgabewerte:
		   -1 = Knoten existiert nicht
			0 = keine Kante vorhanden
			alles andere = ID der Kante
		Parameter:
			id = ID eines Knotens
			graph = void-Pointer auf einen Graphen
*/
int getFirstEdgeOut(int id, void* graph);
/*
	getNextEdgeOut
		Funktion:
			Gibt die ID der nächsten auslaufenden Kante zurück
		Rückgabewerte:
		   -3 = angegebene Kante ist keine auslaufende Kante zu dem von Ihnen angegebenen Knoten
		   -2 = angegebene Knoten existiert nicht
		   -1 = angegebene Kante existiert nicht
			0 = keine nächste Kante vorhanden
			alles größer 0 = ID des nächsten Knotens
		Parameter:
			idedge = ID einer Kante dessen nächsten Kante man erhalten möchte
			idnode = ID des Knotens
			graph = void-Pointer auf einen Graphen
*/
int getNextEdgeOut(int idnode, int idedge, void* graph);
/*
	getEdgeStartNode
		Funktion:
			Gibt die ID des Knotens zurück von dem die Kante kommt.
		Rückgabewerte:
			0 = Kante existiert nicht
			alles größer 0 = id des Knotens
		Parameter:
			id = ID der Kante
			graph = void-Pointer auf einen Graphen
*/
int getEdgeStartNode(int id, void* graph);
/*
	getEdgeEndNode
		Funktion:
			Gibt die ID des Knotens zurück zu dem die Kante zeigt.
		Rückgabewerte:
			0 = Kante existiert nicht
			alles größer 0 = id des Knotens
		Parameter:
			id = ID der Kante
			graph = void-Pointer auf einen Graphen
*/
int getEdgeEndNode(int id, void* graph);
/*
	deleteEdge
		Funktion:
			Entfernt einer Kante
		Rückgabewerte:
			1 = erfolgreich gelöscht
			0 = Edge existiert nicht
		Parameter:
			id = ID einer Kante
			graph = void-Pointer auf einen Graphen
*/
int deleteEdge(int id, void* graph);
/*
	getFirstEdge
		Funktion:
			Gibt die ID der ersten Kante zurück
		Rückgabewerte:
			0 = keine Kante vorhanden
			alles andere = ID der Kante
		Parameter:
			graph = void-Pointer auf einen Graphen
*/
int getFirstEdge(void* graph);
/*
	getNextEdge
		Funktion:
			Gibt die ID der nächsten Kante zurück
		Rückgabewerte:
		   -1 = angegebene Kante existiert nicht
			0 = keine nächste Kante vorhanden
			alles größer 0 = ID des nächsten Knotens
		Parameter:
			idedge = ID einer Kante dessen nächsten Kante man erhalten möchte
			graph = void-Pointer auf einen Graphen
*/
int getNextEdge(int idedge, void* graph);
/*
	changeEdgeValue
		Funktion:
			Verändert den Wert einer Kante
		Rückgabewerte:
			0 = Kante existiert nicht
			1 = erfolgreich geändert
		Parameter:
			id = ID einer Kante
			graph = void-Pointer auf einen Graphen
			value = Wert der Kante
*/
int changeEdgeValue(int id, void* value, void* graph);
/*
	changeEdgeID
		Funktion:
			Verändert die ID einer Kante
		Rückgabewerte:
			-1 = keine gültige ID
			0 = Kante existiert nicht
			1 = erfolgreich geändert
		Parameter:
			id = ID einer Kante
			newid = neue ID der Kante
			graph = void-Pointer auf einen Graphen
*/
int changeEdgeID(int id, int newid, void* graph);
/*
	saveGraph
		Funktion:
			Persistente Speicherung als Text-Datei
		Rückgabewerte:
			1 = erfolgreich gespeichert
			0 = Fehler beim öffnen der Datei
		   -1 = Fehler in der Speicherstruktur Vorgang abgebrochen
		Parameter:
			path = Pfad und Dateiname zB. "C:/Users/soere/Desktop/TEST/Test.txt"
			graph = void-Pointer auf einen Graphen
			edgeattr = Liste aller Edges, attr von SaveList muss ein int sein!
			nodeattr = Liste aller Nodes, attr von SaveList muss ein char* sein!
*/
int saveGraph(TPSaveList edgeattr, TPSaveList nodeattr, char* path, void* graph);
/*
	loadGraph
		Funktion:
			Laden der persistente Speicherung als Text-Datei
		Rückgabewerte:
			1 = erfolgreich geladen
			0 = Fehler beim öffnen der Datei
		Parameter:
			path = Pfad und Dateiname zB. "C:/Users/soere/Desktop/TEST/Test.txt"
*/
void* loadGraph(char* path);

#endif