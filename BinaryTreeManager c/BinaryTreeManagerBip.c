#include "BinaryTreeManagerBip.h"

/***************Structs/Typedefs************/
typedef struct Graph* TPGraph;
typedef struct Node* TPNode;


//Knotenstruktur
typedef struct Node{
	void* _object;
	void* _value;
	TPNode _last;
	TPNode _right;
	TPNode _left;
}TNode;

//Graphenstruktur
typedef struct Graph{
	TPNode _rootnode;
    void* (*biggerValue)(void*, void*);
	bool (*equalValues)(void*, void*);
}TGraph;

//Listenstruktur
typedef struct List{
    //Anzahl an vorelementen
    int _size;
    //Objekt
	void* _listelem;
    //Folgeelement
	TPList _next;
}TList;

/************Functions***************/

/************Intern***************/

//Gibt den richtigen Folgepointer zurück:
// -> right, wenn höher; left, wenn niedriger;
TPNode determineNextPosition(TPNode node, TPNode rootnode, TPGraph graph) {
	if (graph->biggerValue((void*)node->_value, (void*)rootnode->_value) == node->_value) {
		return rootnode->_right;
	}
	else {
		return rootnode->_left;
	}
}

//Setzt ein Node an die richtige Stelle im Graphen.
bool determineNodePosition(TPNode node, TPNode rootnode, TPGraph graph) {
	//Nächste Position ermitteln.
	TPNode nextposition = determineNextPosition(node, rootnode, graph);
	//Wenn der nächste Platz nicht frei ist, such weiter.
	if (nextposition != NULL) {
		determineNodePosition(node, nextposition, graph);
	}
	else {
		//Freier Platz gefunden. Platz belegen.
		if (graph->biggerValue((void*)node->_value, (void*)rootnode->_value) == node->_value && 
			rootnode->_object != node->_object) {
			rootnode->_right = node;
			node->_last = rootnode;
		}
		else if(rootnode->_object != node->_object) {
			rootnode->_left = node;
			node->_last = rootnode;
		}else{
			//Objekt ist bereits eingetragen
			return false;
		}
		return true;
	}
}

void deleteNodesImmediate(TPGraph graph, TPNode rootnode){
	if(rootnode != NULL){
		deleteNodesImmediate(graph, rootnode->_left);
		deleteNodesImmediate(graph, rootnode->_right);
		free((TPNode)rootnode);
	}
}

TPNode createNode(void* object, void* value){
	TPNode node = (TPNode)malloc(sizeof(TNode));
	node->_object = object;
	node->_value = value;
	node->_last = NULL;
	node->_left = NULL;
	node->_right = NULL;
	return node;
}

void printGraphLoop(TPGraph graph, TPNode rootnode, void (*printObject)(void*, int), int level){
	
	//Ausgabe des eigenen Wertes
	if(rootnode != NULL){
		printObject(rootnode->_object, level);
		//Folgeknoten ausgeben
		printGraphLoop(graph, rootnode->_left, printObject,level + 1);
		printGraphLoop(graph, rootnode->_right, printObject,level + 1);
	}else{
		printObject(NULL, level+1);
	}
	
}

//Bestimmt Left-/RightEdges
void determineEdges(TPNode deletenode, TPNode remembernode, TPGraph graph){
	if(remembernode != NULL && deletenode != NULL){
		if(remembernode->_last != NULL){
			if(remembernode->_last->_left == remembernode){
				remembernode->_last->_left = NULL;
			}
			if(remembernode->_last->_right == remembernode){
				remembernode->_last->_right = NULL;
			}
		}
		//remembernode Vorgänger anpassen
		if(deletenode->_last == NULL){
			remembernode->_last = NULL;
		}else{
			remembernode->_last = deletenode->_last;
			if(deletenode->_last != NULL && deletenode->_last->_right == deletenode){
				deletenode->_last->_right = remembernode;
			}else if(deletenode->_last != NULL && deletenode->_last->_left == deletenode){
				deletenode->_last->_left = remembernode;
			}
		}

		//remembernode Nachfolger merken
		TPNode rememberright = remembernode->_right;
		TPNode rememberleft = remembernode->_left;

		//deletenode Nachfolger neu bestimmen
		if(deletenode->_right != remembernode){
			remembernode->_right = deletenode->_right;
		}else{
			remembernode->_right = NULL;
		}
		if(deletenode->_left != remembernode){
			remembernode->_left = deletenode->_left;
		}else{
			remembernode->_left = NULL;
		}

		//remembernode Nachfolger neue Position bestimmen
		if(rememberleft != NULL && graph->_rootnode != NULL){
			determineNodePosition(rememberleft, graph->_rootnode, graph);
		}
		if(rememberright != NULL && graph->_rootnode != NULL){
			determineNodePosition(rememberright, graph->_rootnode, graph);
		}
	}else if(remembernode == NULL && deletenode != NULL){
		if(deletenode->_last != NULL && deletenode->_last->_right == deletenode){
			deletenode->_last->_right = NULL;
		}else if(deletenode->_last != NULL){
			deletenode->_last->_left = NULL;
		}
	}
}

/************public***************/

/************Graph***************/

void *createGraph(void* (*biggerValue)(void*, void*), bool (*equalValues)(void*, void*)){
	TPGraph graph;
	graph = (TPGraph)malloc(sizeof(TGraph));
	graph->_rootnode = NULL;
	graph->biggerValue = biggerValue;
	graph->equalValues = equalValues;
	//wenn erstellt
	if(graph){
		return (void*)graph;
	}else{
		//wenn nicht erstellt
		return NULL;
	}
}

bool deleteGraph(void* graph){
	if(graph != NULL){
		deleteNodesImmediate(graph, ((TPGraph)graph)->_rootnode);
		free((TPGraph)graph);
		return true;
	}
	return false;
}

//Fügt ein Node bei return=true hinzu. True = erfolgreich, False = identischer Eintrag.
bool addNode(void* graph, void* object, void* value) {
	if(graph == NULL || object == NULL){
		return false;
	}
	
	TPNode node = createNode(object, value);

	if(((TPGraph)graph)->_rootnode == NULL){
		((TPGraph)graph)->_rootnode = node;
		return true;
	}else{
		return determineNodePosition(node, ((TPGraph)graph)->_rootnode, ((TPGraph)graph));
	}
}

TPList searchNode(void* graph, void* value){
	if(graph != NULL && ((TPGraph)graph)->_rootnode != NULL){
		TPList list = newList();
		TPNode node = ((TPGraph)graph)->_rootnode;
		bool finish = false;
		while(!finish){
			if (((TPGraph)graph)->equalValues(node->_value, value)) {
				push(&list, node->_object);
			}
			if (((TPGraph)graph)->biggerValue(value, node->_value) == value) {
				node = node->_right;
			}
			else {
				node = node->_left;
			}
			if (node == NULL) {
				finish = true;
			}
		}
		return list;
	}
	return NULL;
}

//Löscht ein Node und gibt "true" zurück, wenn erfolgreich
bool deleteNode(void* graph, void* object, void* value) {
	TPGraph graphc = (TPGraph)graph;
	if(graphc->_rootnode != NULL){
		//Suche beim Startknoten starten
		TPNode deletenode = graphc->_rootnode;
		//true, wenn zu löschender Node nicht gefunden wurde.
		bool finish = false;
		while(!finish){
			//Wenn Node gefunden
			if (graphc->equalValues(deletenode->_value, value) && deletenode->_object == object) {
				//Node welcher den zu löschenden Node ersetzt
				TPNode remembernode = NULL;
				//Wenn es einen RightNode gibt
				if(deletenode->_right != NULL){
					// Setze diesen als remembernode.
					remembernode = deletenode->_right;
					//Gehe nun so weit wie möglich nach Links.
					while(remembernode->_left != NULL){
						remembernode = remembernode->_left;
					}
				//Wenn es rechts nicht weiter geht nehme LeftNode
				}else if(deletenode->_left != NULL){
					remembernode = deletenode->_left;
				}
			
				//Wenn es einen Vorgänger vom zu löschenden Node gibt,
				if(deletenode->_last != NULL){
					//passe die Edges an.
					determineEdges(deletenode, remembernode, graph);
				}else{
					determineEdges(deletenode, remembernode, graph);
					graphc->_rootnode = remembernode;
				}
				//Speicher frei geben
				free(deletenode);
				//Feedback
				return true;
			}
			//Suche nach deletenode
			if (graphc->biggerValue(value, deletenode->_value) == value) {
				deletenode = deletenode->_right;
			}
			else {
				deletenode = deletenode->_left;
			}
			//Wenn nicht gefunden
			if (deletenode == NULL) {
				finish = true;
			}
		}
	}
	return false;
}


//gibt die Struktur des Graphens in der Console aus.
void printGraph(void* graph, void (*printObject)(void*, int)) {
	printGraphLoop((TPGraph)graph, ((TPGraph)graph)->_rootnode, printObject, 0);
}

/************List***************/
bool push(TPList* list, void* listelem)
{
    //Liste erstellen
	TPList e;
	e = (TPList)malloc(sizeof(TList));
    //Erstellt?
	if (!e) return false;
    //Struktur definieren
	e->_listelem = listelem;
	e->_next = *list;
	if(&(*list)->_size != NULL){
		e->_size = (*list)->_size+1;
	}else{
		e->_size = 1;
	}
    //neues Startelement festlegen	
	*list = e;
	return true;
}

bool pop(TPList* list)
{
	TPList e;
    //ist das Element != NULL => abbrechen
	if(!*list) return false;
    //Element bestimmen
	e = *list;
    //Startpunkt um eine Position zurücksetzen
	*list = (*list)->_next;
    //Speicher freigeben
	free(e);
	return true;
}

void* getObject(int index, TPList list){
    TPList listelem = list;
    for(int i = 0; listelem != NULL && i < index; i++){
        listelem = listelem->_next;
    }
    return listelem->_listelem;
}

TPList newList(){
    TPList list = NULL;
    return list;
}

int size(TPList list){
    return list->_size;
}

void* getNext(TPList list){
	return (list->_next);
}