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
		//H�here Werte
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

		//Kleineren Wert setzen
		void setLeftNode(Node* node) {
			m_left = node;
		}

		//H�heren Wert setzen
		void setRightNode(Node* node) {
			m_right = node;
		}

		//Kleineren Wert zur�ckgeben
		Node* getLeftNode(){
			return m_left;
		}

		//H�heren Wert zur�ckgeben
		Node* getRightNode(){
			return m_right;
		}

		//Instance-Pointer zur�ckgeben
		Nodedata* getData() {
			return m_data;
		}

		//Wert zur�ckgeben
		Value getValue() {
			return m_value;
		}
};
#endif

