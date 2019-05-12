#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "BipGraph.h"

/***************Structs/Typedefs************/
typedef struct Graph* TPGraph;
typedef struct Edge* TPEdge;
typedef struct Node* TPNode;
typedef struct ZList* TPZList;


//Knotenstruktur
typedef struct Node{
	int id;
	void* value;
	TPEdge edges;
	TPNode next;
}TNode;

//Kantenstruktur
typedef struct Edge{
	int id;
	void* value;
	TPNode start;
	TPNode end;
	TPZList next;
}TEdge;

//Zeigerverwaltung
typedef struct ZList{
	void* listelem;
	TPZList next;
}TZList;

//Graphenstruktur
typedef struct Graph{
	TPNode nodes;
	TPEdge edges;
}TGraph;

/************intern***************/
/*
	cutString
		Funktion:
			Entfernt alle char's bis zum Trennzeichen ':'
		Rückgabewerte:
			1 = erfolgreich entfernt
			0 = fehler
		Parameter:
			String = String der beschnitten werden soll
*/
int cutString(char* string){
	int i;
	int length = strlen(string);
	int find = 0;
	for(i = 0; i < length; i++){
		if(string[i] == ':' && find == 0){
			find = i+1;
		}
		if(find != 0){
			string[i-find] = string[i];
			string[i] = 0;
		}
	}
	if(find == 0){
		return 0;
	}else{
		return 1;
	}
}
/*
	getString
		Funktion:
			Gibt den String bis zu einer bestimmten Position zurück
		Rückgabewerte:
			NULL = Fehler 
			alles andere = String
		Parameter:
			String = String von dem ein Teil zurückgegeben werden soll
			position = Position bis zu dem der String zurückgegeben werden soll
*/
char* getString(char* string, int position){
	char* newstring = malloc(sizeof(char));
	for(int i = 0; i < position; i++){
		newstring[i] = string[i];
	}
	return newstring;
}
/*
	stringToInt
		Funktion:
			Wandelt einen String in eine Ganzzahl
		Rückgabewerte:
			Ganzzahl
		Parameter:
			number = Nummer als String
			length = länge der Nummer
*/
int stringToInt(char* number, int numlength){
	int length = numlength;
	int val = 0;
	for(int i = 0; length != 0; i++){
		if(length == 1){
			val = val + (number[i] - '0');
			
		}else{
			val = val + ((number[i] - '0')*(pow(10, (length-1))));
		}
		length = length - 1;
	}
	return val;
}
/*
	getStringlength
		Funktion:
			Gibt die Länge eines Strings bis zum nächsten Trennzeichen ':' zurück
		Rückgabewerte:
			Länge
		Parameter:
			String = String dessen Länge des nächster Teil zurückgegeben werden soll
*/
int getStringlength(char* String){
	int i;
	for(i = 0; String[i] != ':'; i++);
	return i;
}
/*
	getNodeWithID
		Funktion:
			Gibt einen pointer auf einen Node zurück über die ID
		Rückgabewerte:
			NULL = Node existiert nicht
			alles andere = Pointer auf Node
		Parameter:
			id = ID des Knotens
			graph = void-Pointer auf einen Graphen
*/
TPNode getNodeWithID(int id, void* graph){
	TPNode n = (TPNode)(((TPGraph) graph)->nodes);
	while(n){
		//id stimmt überein
		if((n-> id) == id){
			return n;
		}
		//nächsten Node untersuchen
		n = n->next;
	}
	return NULL;
}

/*
	getEdgeWithID
		Funktion:
			Gibt einen pointer auf eine Kante zurück über die ID
		Rückgabewerte:
			NULL = Edge existiert nicht
			alles andere = Pointer auf Edge
		Parameter:
			id = ID der Kante
			graph = void-Pointer auf einen Graphen
*/
TPEdge getEdgeWithID(int id, void* graph){
	TPEdge e = (TPEdge)(((TPGraph) graph)->edges);
	while(e){
		//id stimmt überein
		if((e-> id) == id){
			return e;
		}
		//nächsten Node untersuchen
		e = (TPEdge)(e->next->listelem);
	}
	return NULL;
}

/************Graph***************/

void *createGraph(){
	TPGraph graph;
	graph = (TPGraph)malloc(sizeof(TGraph));
	graph->nodes = NULL;
	graph->edges = NULL;
	//wenn erstellt
	if(graph){
		return (void*)graph;
	}else{
		//wenn nicht erstellt
		return NULL;
	}
}
int deleteGraph(void* graph){
	int n = getFirstNode(graph);
	//alle Nodes mit ihren kanten entfernen
	while(n > 0){
		deleteNode(graph, n);
		n = getNextNode(graph, n);
	}
	if(((TPGraph)graph)->nodes != NULL || ((TPGraph)graph)->edges != NULL){
		return 0;
	}else{
		free((TPGraph)graph);
		return 1;
	}
	return 0;
}
int getFirstNode(void *graph){
	TPGraph g = (TPGraph)graph;
	//wenn die Liste leer ist
	if(!(g->nodes)){		
		return 0;	
	//wenn ein Node eingetragen ist
	}else{
		return (((TPNode)(g->nodes))->id);	
	}
}
int getNextNode(void* graph, int idnode){
	TPNode n = (TPNode)(((TPGraph)graph)->nodes);
	while(1){
		//ist die Liste leer?
		if(!n){
			return -1;
		//wenn id übereinstimmt
		}else if(n->id == idnode){
			//ist ein nächster knoten eingetragen?
			if(!(n->next)){
				return 0;
			}else{
				//id-Rückgabe des nächsten Nodes
				return ((TPNode)(n->next))->id;
			}
		//wenn nicht übereinstimmt untersuche den nächsten Node
		}else if(n->next){
			n = (TPNode)(n->next);
		}else{
			//wenn kein nächster Node vorhanden ist = abbrechen
			break;
		}
	}
	//id existiert nicht in der Liste
	return -1;
}
int nodeExist(void *graph, int id){
	TPNode n = (TPNode)(((TPGraph) graph)->nodes);
	int exist = 0;
	//solange ein node(nicht NULL) und noch nicht gefunden
	while(n && exist == 0){
		//id stimmt überein
		if((n-> id) == id){
			exist = 1;
		}
		//nächsten Node untersuchen
		n = n->next;
	}
	return exist;
}
int getFirstEdge(void* graph){
	TPEdge e = ((TPGraph)graph)->edges;
	if(e == NULL){
		return 0;
	}else{
		return ((TPGraph)graph)->edges->id;
	}
}
int getNextEdge(int idedge, void* graph){
	TPEdge e = getEdgeWithID(idedge, graph);
	if(e == NULL){
		return (-1);
	}else if((e->next->listelem) == NULL){
		return 0;
	}else{
		return ((TPEdge)(e->next->listelem))->id;
	}
}
/************Node***************/

int createNode(void *graph, int id, void* value){
	//ist die ID negativ?
	if(id < 1){
		return (-1);
	//existier die NodeID bereits?
	}else if(nodeExist(graph, id) == 0){
			//erstellen eines Nodes
			TPNode node;
			node = (TPNode)malloc(sizeof(TNode));
			//wenn erstellen fehlgeschlagen
			if(!node) return (-2);
			node->id = id;
			node->value = value;
			node->edges = NULL;
			node->next = (TPNode)((TPGraph)graph)->nodes;
			((TPGraph)graph)->nodes = node;
			return id;
	//existiert also
	}else{
		return 0;
	}
	//Fehlgeschlagen
	return (-2);
}
int deleteNode(void* graph, int id){
	TPNode l = NULL;
	TPNode n = (TPNode)(((TPGraph) graph)->nodes);
	//solange ein node(nicht NULL) und noch nicht gefunden
	while(n){
		//id stimmt überein
		if((n->id) == id){
			if(n->edges != NULL){
				//alle ein und ausgehenden Edges entfernen
				int ein = getFirstEdgeIn(n->id, graph);
				int eout = getFirstEdgeOut(n->id, graph);
				while(ein > 0){
					TPEdge e = getEdgeWithID(ein, graph);
					ein = getNextEdgeIn(n->id, ein, graph);
					deleteEdge(e->id, graph);
				}
				while(eout > 0){
					TPEdge e = getEdgeWithID(eout, graph);
					eout = getNextEdgeOut(n->id, eout, graph);
					deleteEdge(e->id, graph);
				}
			}
			if(l != NULL){
				l->next = n->next;
			}else{
				((TPGraph)graph)->nodes = NULL;
			}
		
			free(n);
			return 1;
		}
		//nächsten Node untersuchen
		l = n;
		n = n->next;
	}
	return 0;
}
int changeNodeID(int id, int newid, void* graph){
	//ist die ID negativ?
	if(newid < 1){
		return (-1);
	}else{
		TPNode n = getNodeWithID(id, graph);
		if(n == NULL){
			return 0;
		}else{
			n->id = newid;
			
			return 1;
		}
	}
}
int changeNodeValue(int id, void* value, void* graph){
	TPNode n = getNodeWithID(id, graph);
	//wenn node nicht existiert
	if(n == NULL){
		return 0;
	}else{
		n->value = value;
		
		return 1;
	}
}
void* getNodeValue(int id, void* graph){
	TPNode n = getNodeWithID(id, graph);
	if(n==NULL){
		return NULL;
	}else{
		return n->value;
	}
}

int getFirstEdgeIn(int id, void* graph){
	TPNode n = getNodeWithID(id, graph);
	if(n==NULL){
		return (-1);
	}else if(n->edges == NULL){
		return 0;
	}else{
		TPEdge e = n->edges;
		while(e){
			//ist das ende der kante in der liste des Knotens die knotenid?
			if(e->end->id == id){
				return e->id;
			}else{
				//1.next -> Liste des Graphens, 
				//2.next -> Liste der auslaufenden Kanten,
				//3.next -> Liste der einlaufenden Kanten	
				e = (TPEdge)(e->next->next->listelem);
			}
		}
		return 0;
	}
}

int getNextEdgeIn(int idnode, int idedge, void* graph){
	TPEdge e = getEdgeWithID(idedge, graph);
	TPNode n = getNodeWithID(idnode, graph);
	
	if(n==NULL){
		return (-2);
	}
	if(e==NULL){
		return (-1);
	}else if(e->end != n){
		return (-3);
	//1.next -> Liste des Graphens, 
	//2.next -> Liste der auslaufenden Kanten,
	//3.next -> Liste der einlaufenden Kanten	
	//Wenn keine weiteren einlaufenden Kanten vorhanden
	}else if((e->next->next->next->listelem) == NULL){
		return 0;
	}else{
		TPEdge nexte = (TPEdge)(e->next->next->next->listelem);
		while(nexte){
			//ist das ende der kante in der liste des Knotens die knotenid?
			if(nexte->end->id == idnode){
				return nexte->id;
			}else{
				//1.next -> Liste des Graphens, 
				//2.next -> Liste der auslaufenden Kanten,
				//3.next -> Liste der einlaufenden Kanten	
				if(((TPEdge)(nexte->next->next->listelem)) == NULL){
					return 0;
				}
				nexte = (TPEdge)(nexte->next->next->listelem);
			}
		}
	}
	return 0;
}

int getFirstEdgeOut(int id, void* graph){
	TPNode n = getNodeWithID(id, graph);
	if(n==NULL){
		return (-1);
	}else if(n->edges == NULL){
		return 0;
	}else{
		TPEdge e = n->edges;
		while(e){
			//ist das ende der kante in der liste des Knotens die knotenid?
			if(e->start->id == id){
				return e->id;
			}else{
				//1.next -> Liste des Graphens, 
				//2.next -> Liste der auslaufenden Kanten,
				//3.next -> Liste der einlaufenden Kanten	
				e = (TPEdge)(e->next->next->next->listelem);
			}
		}
		return 0;
	}
}

int getNextEdgeOut(int idnode, int idedge, void* graph){
	TPEdge e = getEdgeWithID(idedge, graph);
	TPNode n = getNodeWithID(idnode, graph);
	
	if(n==NULL){
		return (-2);
	}
	if(e==NULL){
		return (-1);
	}else if(e->start != n){
		return (-3);
	//1.next -> Liste des Graphens, 
	//2.next -> Liste der auslaufenden Kanten,
	//3.next -> Liste der einlaufenden Kanten	
	//Wenn keine weiteren auslaufenden Kanten vorhanden
	}else if((e->next->next->listelem) == NULL){
		return 0;
	}else{		
		TPEdge nexte = (TPEdge)(e->next->next->listelem);
		while(nexte){
			//ist das ende der kante in der liste des Knotens die knotenid?
			if(nexte->start->id == idnode){
				return nexte->id;
			}else{
				//1.next -> Liste des Graphens, 
				//2.next -> Liste der auslaufenden Kanten,
				//3.next -> Liste der einlaufenden Kanten	
				if(((TPEdge)(nexte->next->next->next->listelem)) == NULL){
					return 0;
				}
				nexte = (TPEdge)(nexte->next->next->next->listelem);
			}
		}
	}
	return 0;
}

/************Edge***************/

int edgeExist(void* graph, int id){
	TPEdge e = (TPEdge)(((TPGraph) graph)->edges);
	int exist = 0;
	//solange ein edge nicht NULL und noch nicht gefunden
	while(e && exist == 0){
		//id stimmt überein
		if((e-> id) == id){
			exist = 1;
		}
		//nächsten Node untersuchen
		e = (TPEdge)(e->next->listelem);
	}
	return exist;
}

int createEdge(int id, void* value, int fromnode, int tonode, void* graph){
	if(id<1){
		return (-3);
	}else if(edgeExist(graph, id) > 0){
		return 0;
	}else if(nodeExist(graph, fromnode)==0){
		return (-2);
	}else if(nodeExist(graph, tonode)==0){
		return (-1);
	}else{
		TPEdge edge;
		edge = (TPEdge)malloc(sizeof(TEdge));
		//wenn erstellen fehlgeschlagen
		if(!edge) return (-4);
		edge->id = id;
		edge->value = value;
		edge->start = getNodeWithID(fromnode, graph);
		edge->end = getNodeWithID(tonode, graph);
		
		//Liste für tonode (einlaufende Kanten)
		TPZList listtonode = (TPZList)malloc(sizeof(TZList));
		listtonode->listelem = (void*)((TPNode)edge->end)->edges;
		listtonode->next = NULL;
		((TPNode)edge->end)->edges = edge;
		
		//Liste für fromnode (auslaufende Kanten)
		TPZList listfromnode = (TPZList)malloc(sizeof(TZList));
		listfromnode->listelem = (void*)((TPNode)edge->start)->edges;
		listfromnode->next = listtonode;
		((TPNode)edge->start)->edges = edge;
		
		//Liste des Graphen
		TPZList listgraph = (TPZList)malloc(sizeof(TZList));
		listgraph->listelem = (void*)((TPGraph)graph)->edges;
		listgraph->next = listfromnode;
		((TPGraph)graph)->edges = edge;
		
		edge->next = listgraph;
		
		return id;
	}
}

void* getEdgeValue(int id, void* graph){
	TPEdge e = getEdgeWithID(id, graph);
	if(e == NULL){
		return NULL;
	}else{
		return e->value;
	}
}

int changeEdgeValue(int id, void* value, void* graph){
	TPEdge e = getEdgeWithID(id, graph);
	if(e == NULL){
		return  0;
	}else{
		e->value = value;
	
		return 1;
	}
}

int getEdgeStartNode(int id, void* graph){
	TPEdge e = getEdgeWithID(id, graph);
	
	if(e == NULL){
		return 0;
	}else{
		return e->start->id;
	}
}

int getEdgeEndNode(int id, void* graph){
	TPEdge e = getEdgeWithID(id, graph);
	
	if(e == NULL){
		return 0;
	}else{
		return e->end->id;
	}
}

int deleteEdge(int id, void* graph){
	TPEdge e = getEdgeWithID(id, graph);
	
	if(e == NULL){
		return 0;
	}else{
		//Liste der Kanten vom Graphen aktualisieren
		int egraphlast = 0;
		int egraph = getFirstEdge(graph);
		while(egraph > 0){
			if(egraph == id){
				if(egraphlast == 0){
					((TPGraph)graph)->edges = (TPEdge)(e->next->listelem);
				}else{
					TPEdge lastedge = getEdgeWithID(egraphlast, graph);
					lastedge->next->listelem = e->next->listelem;
				}
				break;
			}else{
				egraphlast = egraph;
				egraph = getNextEdge(egraph, graph);
			}
		}
		//Liste der auslaufenden Kanten aktualisieren
		int estartlast = 0;
		int estart = getFirstEdgeOut(e->start->id, graph);
		while(estart > 0){
			if(estart == id){
				if(estartlast == 0){
					e->start->edges = (TPEdge)(e->next->next->listelem);
				}else{
					TPEdge lastedge = getEdgeWithID(estartlast, graph);
					lastedge->next->next->listelem = e->next->next->listelem;
				}
				break;
			}else{
				estartlast = estart;
				estart = getNextEdgeOut(e->start->id, estart, graph);
			}
		}
		//Liste der einlaufenden Kanten aktualisieren
		int eendlast = 0;
		int eend = getFirstEdgeIn(e->end->id, graph);
		while(eend > 0){
			if(eend == id){
				if(eendlast == 0){
					e->end->edges = (TPEdge)(e->next->next->next->listelem);
				}else{
					TPEdge lastedge = getEdgeWithID(eendlast, graph);
					lastedge->next->next->next->listelem = e->next->next->next->listelem;
				}
				break;
			}else{
				eendlast = eend;
				eend = getNextEdgeIn(e->end->id, eend, graph);
			}
		}
		free(e);
		
		return 1;
	}
}

int changeEdgeID(int id, int newid, void* graph){
	//ist die ID negativ?
	if(newid < 1){
		return (-1);
	}else{
		TPEdge e = getEdgeWithID(id, graph);
		if(e == NULL){
			return 0;
		}else{
			e->id = newid;
			
			return 1;
		}
	}
}
/******************************************Persistente Speicherung*********************************************/
int saveGraph(TPSaveList edgeattr, TPSaveList nodeattr, char* path, void* graph){
	FILE *datei;
	datei = fopen (path, "w");
	
	if(datei == NULL){
		return 0;
	}
	TPEdge e = getEdgeWithID(getFirstEdge(graph), graph);
	TPNode n = getNodeWithID(getFirstNode(graph), graph);
	//Nodes abspeichern
	while(n != NULL){
		char id = n->id;
		// Attribut ermitteln
		char* value = NULL;
		TPSaveList  sln = nodeattr;
		
		//Attribut gefunden?
		int findn = 0;
		// Wenn ja, Schleife abbrechen
		while(sln != NULL && findn == 0){
			if(sln->id == n->id){
				value = (char*)(sln->attr);
				findn = 1;
			}
			sln = sln->next;
		}
		if(value == NULL){
			fclose (datei);
			return -1;
		}
		//2tes %d ist die länge des folgenden Strings
		fprintf (datei, "Node:%d:%d:%s\n", id, strlen(value), value);
		n = getNodeWithID(getNextNode(graph, (int)n->id), graph);
	}
	//Edges abspeichern
	while(e != NULL){
		int id = e->id;
		int fromnode = e->start->id;
		int tonode = e->end->id;
		
		int* value = NULL;
		TPSaveList  sle = edgeattr;
		
		//Attribut gefunden?
		int finde = 0;
		// Wenn ja, Schleife abbrechen
		while(sle != NULL && finde == 0){
			if(sle->id == e->id){
				value = (int*)(&(sle->attr));
				finde = 1;
			}
			sle = sle->next;
		}
		
		if(value == NULL){
			fclose (datei);
			return -1;
		}
		
		fprintf (datei, "Edge:%d:%d:%d:%d\n", id, fromnode, tonode, *value);
		e = getEdgeWithID(getNextEdge(e->id, graph), graph);
	}
	fclose (datei);
	return 1;
}
void* loadGraph(char* path){
	FILE *datei;
	datei = fopen (path, "r");
	if(datei == NULL){
		return NULL;
	}
	void* g = createGraph();
	int size = 0;
	int c;
	//Komplette Länge ermitteln
	while(!feof(datei)){
		c = fgetc(datei);
		size++;
    }
	
	datei = fopen (path, "r");
	char command[size+1];
	int i = 0;
	while(fscanf(datei, "%s",command) != EOF){
		if(command[0] == 'N' && command[1] == 'o' && command[2] == 'd' && command[3] == 'e'){
			if(cutString(command) == 1){
				int id = stringToInt(getString(command, 4), getStringlength(command));
				if(cutString(command) == 1){
					int valuesize = stringToInt(getString(command, 4), getStringlength(command));
					if(cutString(command) == 1){
						if(valuesize == strlen(command)){
							char* value = malloc(sizeof(char));
							value = command;
							if(createNode(g, id, (void*)value) <= 0){
								deleteGraph(g);
								return NULL;
							}
						}else{
							deleteGraph(g);
							return NULL;
						}
					}else{
						deleteGraph(g);
						return NULL;
					}
				}else{
					deleteGraph(g);
					return NULL;
				}
			}else{
				deleteGraph(g);
				return NULL;
			}
		}else if(command[0] == 'E' && command[1] == 'd' && command[2] == 'g' && command[3] == 'e'){
			if(cutString(command) == 1){
				int id = stringToInt(getString(command, 4), getStringlength(command));
				if(cutString(command) == 1){
					int fromnode = stringToInt(getString(command, 4), getStringlength(command));
					if(cutString(command) == 1){
						int tonode = stringToInt(getString(command, 4), getStringlength(command));
						if(cutString(command) == 1){
							int value = stringToInt(getString(command, 4), getStringlength(command));
							if(createEdge(id, (void*)(&value), fromnode, tonode, g) <= 0){
								deleteGraph(g);
								return NULL;
							}
						}else{
							deleteGraph(g);
							return NULL;
						}
					}else{
						deleteGraph(g);
						return NULL;
					}
				}else{
					deleteGraph(g);
					return NULL;
				}
			}else{
				deleteGraph(g);
				return NULL;
			}
		}else{
			deleteGraph(g);
			return NULL;
		}
	}
	
	fclose (datei);
	return g;
}