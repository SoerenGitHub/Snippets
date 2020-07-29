/******************************Beispiel Objekt******************************/
#include "Sample.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Beispielstruktur
typedef struct Sample{
	int _id;
    float _pieces;
    double _size;
}TSample;

void printObject(void* object, int level){
    
    if(object != NULL){
		for(int i = 0; i < level; i++){
			printf("\t");
		} 
        const int d = ((TPSample)object)->_id;
        printf("node=%d\n", d);
    }else{
		for(int i = 0; i < level-1; i++){
			printf("\t");
		} 
        printf("node=NULL\n");
    }
}

int* getID(TPSample sample){
    if(sample){
        return &sample->_id;
    }else{
        return NULL;
    }
}

float* getPieces(TPSample sample){
    if(sample){
        return &sample->_pieces;
    }else{
        return NULL;
    }
}

double* getSize(TPSample sample){
    if(sample){
        return &sample->_size;
    }else{
        return NULL;
    }
}

TPSample newSample(int id, float pieces, double size){
    TPSample sample = (TPSample)malloc(sizeof(TSample));
    sample->_id = id;
    sample->_pieces = pieces;
    sample->_size = size;
}