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
	//Gibt index zurück und fügt Node hinzu
	int addNode(Node addedNode, Node edgeToNode);
	//erfolgreich gelöscht?
	bool deleteNode(Node node);
	//gibt Node über den Index zurück
	Node getNode(int index);
	//gibt den Index eines Nodes zurück
	int getIndex(Node node);
};
#endif

