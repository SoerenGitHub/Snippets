#ifndef NODE_T
#define NODE_T

#include <iostream>
using namespace std;

template <class Nodedata, class Value>
class Node
{
	private:
		//Kleinere Werte
		Node* m_left;
		//Höhere Werte
		Node* m_right;
		//Instance-Pointer
		Nodedata* m_data;
		//Wert
		Value m_value;
	public:
		//Initialisieren
		Node(Nodedata* data, Value value) : m_data(data), m_value(value) {
			m_right = NULL;
			m_left = NULL;
		}

		~Node(){
			//cout << m_value << " is dead!" << endl;
		}
		
		void deleteNodeTree(){
			if(m_left != NULL){
				m_left->deleteNodeTree();
				delete m_left;
			}
			if(m_right != NULL){
				m_right->deleteNodeTree();
				delete m_right;
			}
		}

		//Kleineren Wert setzen
		void setLeftNode(Node* node) {
			m_left = node;
		}

		//Höheren Wert setzen
		void setRightNode(Node* node) {
			m_right = node;
		}

		//Kleineren Wert zurückgeben
		Node* getLeftNode(){
			return m_left;
		}

		//Höheren Wert zurückgeben
		Node* getRightNode(){
			return m_right;
		}

		//Instance-Pointer zurückgeben
		Nodedata* getData() {
			return m_data;
		}

		//Wert zurückgeben
		Value getValue() {
			return m_value;
		}

		//Gibt den eigenen Wert und den Wert seiner Folgeknoten in der Console aus
		void printNodeTree(int level) {

			//Einrückung berechnen
			string breaks = "";
			for(int i = 0; i < level; i++){
				breaks += "\t";
			}

			//Ausgabe des eigenen Wertes
			cout << breaks << m_value << endl;

			//Folgeknoten ausgeben
			if(m_left != NULL){
				m_left->printNodeTree(level + 1);
			}else{
				cout << breaks << "\t -" << endl;
			}
			if (m_right != NULL){
				m_right->printNodeTree(level + 1);
			}else{
				cout << breaks << "\t -" << endl;
			}
		}

};
#endif

