#include <vector>
#include "Node.t"
#ifndef GRAPH_T
#define GRAPH_T


template <class Nodedata, class Value>
class Graph
{
	private:
		//Root Node
		Node<Nodedata, Value>* _rootnode;

		//Gibt den richtigen Folgepointer zurück:
		// -> right, wenn höher; left, wenn niedriger;
		Node<Nodedata, Value>* determineNextPosition(Node<Nodedata, Value>* node, Node<Nodedata, Value>* rootnode) {
			if (node->getValue() > rootnode->getValue()) {
				return rootnode->getRightNode();
			}else if(node->getValue() == rootnode->getValue() && node->getData() == rootnode->getData()){
				//Gleicher Schlüsselwert und Objektadresse. Folglich soll kein Eintrag stattfinden.
				return NULL;
			}
			else {
				return rootnode->getLeftNode();
			}
		}

		//Setzt ein Node an die richtige Stelle im Graphen.
		bool determineNodePosition(Node<Nodedata, Value>* node, Node<Nodedata, Value>* rootnode) {
			//Nächste Position ermitteln.
			Node<Nodedata, Value>* nextposition = determineNextPosition(node, rootnode);
			//Wenn der nächste Platz nicht frei ist, such weiter.
			if (nextposition != NULL) {
				determineNodePosition(node, nextposition);
			}
			else {
				//Gleicher Schlüsselwert und Objektadresse. Folglich soll kein Eintrag stattfinden.
				if(rootnode->getValue() == node->getValue() && rootnode->getData() == node->getData()){
					return false;
				}
				//Freier Platz gefunden. Platz belegen.
				if (node->getValue() > rootnode->getValue()) {
					rootnode->setRightNode(node);
				}
				else {
					rootnode->setLeftNode(node);
				}
			}
			return true;
		}

		//Bestimmt Left-/RightEdges
		void determineEdges(Node<Nodedata,Value>* deletenode, Node<Nodedata,Value>* remembernode, Node<Nodedata,Value>* remembernodelast){
			if(remembernode != NULL){
				if(remembernode->getRightNode() != NULL && remembernodelast != NULL){
					remembernodelast->setLeftNode(remembernode->getRightNode());
				}else if(remembernodelast != NULL){
					remembernodelast->setLeftNode(NULL);
				}
				if(deletenode->getRightNode() != remembernode && deletenode->getRightNode() !=  NULL){
					remembernode->setRightNode(deletenode->getRightNode());
				}
				if(deletenode->getLeftNode() != remembernode){
					remembernode->setLeftNode(deletenode->getLeftNode());
				}
			}
		}

	public:
		//Initialisieren
		Graph() {
			_rootnode = NULL;
		}

		//Speicher freigeben
		~Graph(){
			if(_rootnode != NULL){
				_rootnode->deleteNodeTree();
				delete _rootnode;
			}
		}

		//Fügt ein Node bei return=true hinzu. True = erfolgreich, False = identischer Eintrag.
		bool addNode(Nodedata* node, Value value) {
			Node<Nodedata, Value>* nodex = new Node<Nodedata, Value>(node, value);
			if(_rootnode == NULL){
				_rootnode = nodex;
				return true;
			}else{
				return determineNodePosition(nodex, _rootnode);
			}
		}

		//Löscht ein Node und gibt "true" zurück, wenn erfolgreich
		bool deleteNode(Nodedata* node, Value value) {
			if(_rootnode != NULL){
				Node<Nodedata,Value>* lastnode = NULL;
				//Suche beim Startknoten starten
				Node<Nodedata,Value>* deletenode = _rootnode;
				//true, wenn zu löschender Node nicht gefunden wurde.
				bool finish = false;
				while(!finish){
					//Wenn Node gefunden
					if (deletenode->getValue() == value && deletenode->getData() == node) {
						//Node welcher den zu löschenden Node ersetzt
						Node<Nodedata, Value>* remembernode = NULL;
						//Vorgänger von remembernode
						Node<Nodedata, Value>* remembernodelast = NULL;
						//Wenn es einen RightNode gibt
						if(deletenode->getRightNode() != NULL){
							// Setze diesen als remembernode.
							remembernode = deletenode->getRightNode();
							//Gehe nun so weit wie möglich nach Links.
							while(remembernode->getLeftNode() != NULL){
								remembernodelast = remembernode;
								remembernode = remembernode->getLeftNode();
							}
						//Wenn es rechts nicht weiter geht nehme LeftNode
						}else if(deletenode->getLeftNode() != NULL){
							remembernode = deletenode->getLeftNode();
						}
					
						//Wenn es einen Vorgänger vom zu löschenden Node gibt,
						if(lastnode != NULL){
							//passe die Edges an.
							determineEdges(deletenode, remembernode, remembernodelast);
							if(lastnode->getRightNode() == deletenode){
								lastnode->setRightNode(remembernode);
							}else{
								lastnode->setLeftNode(remembernode);
							}
						}else{
							determineEdges(deletenode, remembernode, remembernodelast);
							_rootnode = remembernode;
						}
						//Speicher frei geben
						delete deletenode;
						//Feedback
						return true;
					}

					//Suche nach deletenode
					if (deletenode->getValue() < value) {
						lastnode = deletenode;
						deletenode = deletenode->getRightNode();
					}
					else {
						lastnode = deletenode;
						deletenode = deletenode->getLeftNode();
					}

					//Wenn nicht gefunden
					if (deletenode == NULL) {
						finish = true;
					}
				}
			}
			return false;
		}

		//Suche nach Node
		vector<Nodedata*>* searchNode(Value value){
			vector<Nodedata*>* nodedata = new vector<Nodedata*>();

			if(_rootnode != NULL){
				Node<Nodedata,Value>* n = _rootnode;
				bool finish = false;
				while(!finish){
					if (n->getValue() == value) {
						nodedata->push_back(n->getData());
					}

					if (n->getValue() < value) {
						n = n->getRightNode();
					}
					else {
						n = n->getLeftNode();
					}

					if (n == NULL) {
						finish = true;
					}
				}
			}
			
			return nodedata;
		}

		//gibt die Struktur des Graphens in der Console aus.
		void printGraph() {
			if(_rootnode != NULL){
				_rootnode->printNodeTree(0);
			}
		}
};
#endif

