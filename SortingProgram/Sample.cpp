#include "Sample.h"

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