#include <iostream>
#include "Graph.t"
#include "Node.t"

int main()
{
    string rootnode = "root";
    string vier = "vier";
    string drei = "drei";
    string achtzehn = "achtzehn";
    string elf = "elf";
    string zwanzig = "zwanzig";

    Graph<string, int>* g = new Graph<string, int>(&rootnode, 10);

    Node<string, int>* v = (Node<string, int>*)g->addNode(&vier, 4);
    Node<string, int>* d = (Node<string, int>*)g->addNode(&drei, 3);
    Node<string, int>* a = (Node<string, int>*)g->addNode(&achtzehn, 18);
    Node<string, int>* e = (Node<string, int>*)g->addNode(&elf, 11);
    Node<string, int>* z = (Node<string, int>*)g->addNode(&zwanzig, 20);

}