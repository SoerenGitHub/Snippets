#include <string>
#ifndef SAMPLE_H
#define SAMPLE_H

using namespace std;
//Beispiel Model zum Testen des Binären Baumes
class Sample
{
private:
	int m_id;
	float m_pieces;
	double m_size;
	string m_name;
public:
	Sample(int id, float pieces, double size, string name);
	int getId();
	float getPieces();
	double getSize();
	string getName();
	void print();
};
#endif