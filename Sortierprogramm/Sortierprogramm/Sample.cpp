#include "Sample.h"

Sample::Sample(int id, float pieces, double size) : m_id(id), m_pieces(pieces), m_size(size) {

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