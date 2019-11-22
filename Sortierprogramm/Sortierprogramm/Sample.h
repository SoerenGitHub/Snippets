#ifndef SAMPLE_H
#define SAMPLE_H
//Beispiel Model zum Testen des sortierens
class Sample
{
private:
	int m_id;
	float m_pieces;
	double m_size;
public:
	Sample(int id, float pieces, double size);
	int getId();
	float getPieces();
	double getSize();
};
#endif