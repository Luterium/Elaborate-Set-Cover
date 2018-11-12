#pragma once
#include <iostream>
#include <vector>

void trataInput();
using namespace std;

class Subset{
private:
	float weight;
	int currentSize;
	vector<int> elementos;

public:
	//Construtores
	Subset();
	Subset(float, int);

	//Métodos acessores

	void setWeight(float);
	float getWeight();
	void setCurrentSize(int);
	int getCurrentSize();
	void setElementos(vector<int>);
	vector<int> getElementos();

	// Métodos necessários
	void decrementSize();
	void incrementSize();
	void adicionaElemento(int);
	int returnElement(int);
	int returnElementSize();
};
