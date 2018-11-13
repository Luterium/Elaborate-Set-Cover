#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "subconjunto.h"

using namespace std;

void startaIndexes(vector <int>& indexes, int m){
    for(int i = 0; i < m; i++){
        indexes[i] = i;
    }
}

void Heapify(vector <Subset>& Subsets, int i, vector <int>& subsetsIndexes){
    unsigned int leftChild, rightChild;
    Subset aux;
    int menor;
    leftChild  = 2*i+1;
    rightChild = 2*i+2;
    //cout << "Pai: " << Subsets[i].returnCurrentWeight() << endl << "Filho ESQ: "<< Subsets[leftChild].returnCurrentWeight() << endl << "Filho DIR: " << Subsets[rightChild].returnCurrentWeight() ;

    if((leftChild <= Subsets.size()-1 ) && (Subsets[i].returnCurrentWeight() > Subsets[leftChild].returnCurrentWeight()))
        menor = leftChild;
    else
        menor = i;
    if((rightChild <= Subsets.size()-1) && (Subsets[menor].returnCurrentWeight() > Subsets[rightChild].returnCurrentWeight()))
        menor = rightChild;

    if (menor != i){
        aux = Subsets[menor];
        Subsets[menor] = Subsets[i];
        Subsets[i] = aux;

        subsetsIndexes[Subsets[i].getSubsetNumber()]     = menor;
        subsetsIndexes[Subsets[menor].getSubsetNumber()] = i;
        Heapify(Subsets, menor, subsetsIndexes);
    }
    /*cout << endl << menor << "      " << Subsets[menor].returnCurrentWeight() << endl << endl;
    cout << Subsets[rightChild].getWeight() << Subsets[rightChild].getCurrentSize() << endl;*/
    return;
}

void BuildHeap(vector <Subset>& Subsets, vector <int>& subsetsIndexes){
    for(int i = floor(Subsets.size())/4; i > 0; i--){
        Heapify(Subsets, i, subsetsIndexes);
    }
}

void trataInput(){
    int n, m, auxWeight, auxQtdElementos, auxElemento;
    float totalWeight = 0;
    ifstream inputSCP;
    inputSCP.open("scp.txt");
    inputSCP >> n >> m;

    vector <Subset> Subsets(m);
    vector <int> subsetsIndexes(m);
    vector < vector <int> > elementos(n);
    vector <bool> elementosCobertos(n, false);
    vector <bool> elementosCobertosSize(n, false);


    for(int i = 0; i < m; i++){
        inputSCP >> auxWeight;
        Subsets[i].setWeight(auxWeight);
        Subsets[i].setSubsetNumber(i);
    }

    for (int i = 0; i < n; i++){
        inputSCP >> auxQtdElementos;
        for(int j = 0; j < auxQtdElementos; j++){
            inputSCP >> auxElemento;
            elementos[i].push_back(auxElemento-1);
            Subsets[auxElemento-1].incrementSize();
            Subsets[auxElemento-1].adicionaElemento(i);
        }
    }
    startaIndexes(subsetsIndexes, m);
    BuildHeap(Subsets, subsetsIndexes);
/*
    while(elementosCobertos.size())
    workMatrix(matrizElementos, elementosCobertos, Subsets, m, n, returnIndiceMin(Subsets, m, totalWeight))*/

    //cout << "Total cover cost: " << totalWeight << endl << endl;

    inputSCP.close();
}
