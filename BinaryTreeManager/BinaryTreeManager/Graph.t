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

		//gibt den richtigen folgepointer zur�ck:
		//right, wenn h�her; left, wenn niedriger;
		Node<Nodedata, Value>* determineNextPosition(Node<Nodedata, Value>* node, Node<Nodedata, Value>* rootnode) {
			if (node->getValue() > rootnode->getValue()) {
				cout << "Node = " << node->getValue() << " nach Rechts" << endl;
				return rootnode->getRightNode();
			}
			else {
				cout << "Node = " << node->getValue() << " nach Links" << endl;
				return rootnode->getLeftNode();
			}
		}

		//Setzt ein Node an die richtige Stelle im Graphen.
		void determineNodePosition(Node<Nodedata, Value>* node, Node<Nodedata, Value>* rootnode) {
			Node<Nodedata, Value>* nextposition = determineNextPosition(node, rootnode);
			if (nextposition != NULL) {
				determineNodePosition(node, nextposition);
			}
			else {
				if (node->getValue() > rootnode->getValue()) {
					rootnode->setRightNode(node);
				}
				else {
					rootnode->setLeftNode(node);
				}
			}

		}

	public:
		//Initialisieren
		Graph(Nodedata* rootnode, Value value) {
			_rootnode = new Node<Nodedata, Value>(rootnode, value);
		}

		//F�gt ein Node hinzu
		Node<Nodedata, Value>* addNode(Nodedata* node, Value value) {
			Node<Nodedata, Value>* nodex = new Node<Nodedata, Value>(node, value);
			determineNodePosition(nodex, _rootnode);
			return nodex;
		}

		//L�scht ein Node und gibt "true" zur�ck, wenn erfolgreich
		/*bool deleteNode(Nodedata* node) {

		}

		//Suche von Nodes
		vector<Nodedata> searchNode(Value)
		//gibt Node �ber den Index zur�ck
		Nodedata getNode(int index);
		//gibt den Index eines Nodes zur�ck
		int getIndex(Nodedata node);
		//gibt die Struktur des Graphens in der Console aus.
		void printGraph();*/
};
#endif

