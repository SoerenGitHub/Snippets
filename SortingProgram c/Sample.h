/******************************Beispiel Objekt******************************/
typedef struct Sample* TPSample;
/*
	getID
		Funktion:
			Gibt die ID zurück
		Rückgabewerte:
			ID
		Parameter:
			sample = Sample Objekt von dem die ID abgefragt werden soll
*/
int* getID(TPSample sample);
/*
	getPieces
		Funktion:
			Gibt die Stückzahl zurück
		Rückgabewerte:
			Stückzahl
		Parameter:
			sample = Sample Objekt von dem die ID abgefragt werden soll
*/
float* getPieces(TPSample sample);
/*
	getSize
		Funktion:
			Gibt die Größe zurück
		Rückgabewerte:
			Größe
		Parameter:
			sample = Sample Objekt von dem die ID abgefragt werden soll
*/
double* getSize(TPSample sample);
/*
	newSample
		Funktion:
			Erstellt eine Instance vom Type TSample
		Rückgabewerte:
			TPSample
*/
TPSample newSample(int id, float pieces, double size);