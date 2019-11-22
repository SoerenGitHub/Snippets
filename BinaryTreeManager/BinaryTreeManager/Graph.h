#include <vector>
#ifndef GRAPH_H
#define GRAPH_H

using namespace std;

template <class Node>
class Graph
{
private:
	//Node and Node before
	vector<pair<Node,Node>> nodes;
public:
	Graph();
	//setzt den Startknoten
	int setFirstNode(Node node);
	//Gibt index zur�ck und f�gt Node hinzu
	int addNode(Node addedNode, Node edgeToNode);
	//erfolgreich gel�scht?
	bool deleteNode(Node node);
	//gibt Node �ber den Index zur�ck
	Node getNode(int index);
	//gibt den Index eines Nodes zur�ck
	int getIndex(Node node);
};
#endif

