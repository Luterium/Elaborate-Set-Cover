#pragma once
#include <iostream>
#include <vector>

void trataInput();
using namespace std;

class Subset{
private:
    int subsetNumber;
	float weight;
	int currentSize;
	vector<int> elementos;

public:
	//Construtores
	Subset();
	Subset(float, int);

	//M�todos acessores

	void setWeight(float);
	float getWeight();
	void setCurrentSize(int);
	int getCurrentSize();
	void setSubsetNumber(int);
	int getSubsetNumber();
	void setElementos(vector<int>);
	vector<int> getElementos();

	// M�todos necess�rios
	void decrementSize();
	void incrementSize();
	void adicionaElemento(int);
	int returnElement(int);
	int returnElementSize();
	float returnCurrentWeight();
};
