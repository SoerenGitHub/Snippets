#include "Sample.h"
#include <iostream>

Sample::Sample(int id, float pieces, double size, string name) : m_id(id), m_pieces(pieces), m_size(size), m_name(name) {

}

int Sample::getId() {
	return m_id;
}

float Sample::getPieces() {
	return m_pieces;
}

double Sample::getSize() {
	return m_size;
}

string Sample::getName() {
	return m_name;
}

void Sample::print() {
	cout << "Sample:" << endl;
	cout << " ID(Integer): " << m_id << endl;
	cout << " Pieces(Float): " << m_pieces << endl;
	cout << " Size(Double): " << m_size << endl;
	cout << " Name(String): " << m_name << endl;
}