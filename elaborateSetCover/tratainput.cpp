#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "subconjunto.h"
#include <queue>
#define EPS 0.001

using namespace std;

bool comparaFloats(float i, float j){
    if(i > j-EPS && i < j+EPS)
        return true;
    return false;
}

void DesceHeap(vector <Subset>& Subsets, int i, vector <int>& subsetsIndexes){
    unsigned int leftChild, rightChild;
    Subset aux;
    int menor;
    leftChild  = 2*i+1;
    while(leftChild < Subsets.size()){
        leftChild  = 2*i+1;
        rightChild = 2*i+2;

        if((rightChild < Subsets.size()) && ((Subsets[i].returnCurrentWeight() > Subsets[rightChild].returnCurrentWeight()+EPS) ||
                                             (comparaFloats(Subsets[i].returnCurrentWeight(),Subsets[rightChild].returnCurrentWeight())
                                              && Subsets[i].getCurrentSize() < Subsets[rightChild].getCurrentSize())))
             menor = rightChild;
        else menor = i;

        if((leftChild < Subsets.size()) && ((Subsets[menor].returnCurrentWeight() > Subsets[leftChild].returnCurrentWeight()+EPS) ||
                                            (comparaFloats(Subsets[menor].returnCurrentWeight(),Subsets[leftChild].returnCurrentWeight())
                                             && Subsets[menor].getCurrentSize() < Subsets[leftChild].getCurrentSize())))
            menor = leftChild;

        if (menor == i){
            break;
        }
        else{
            aux = Subsets[menor];
            Subsets[menor] = Subsets[i];
            Subsets[i] = aux;

            subsetsIndexes[Subsets[i].getSubsetNumber()]     = i;
            subsetsIndexes[Subsets[menor].getSubsetNumber()] = menor;
            i = menor;
        }
    }
    return;
}

void Heapify(vector <Subset>& Subsets, vector <int>& subsetsIndexes){
    for(int i = floor(Subsets.size())/2; i >= 0; i--){
        DesceHeap(Subsets, i, subsetsIndexes);
    }
}

void betterCoverElements(vector <Subset>& Subsets, vector <int>& subsetsIndexes, vector <bool>& elementosCobertos, int& elementosDescobertosSize, vector < vector <int> >& elementos){
    int cZI = Subsets[0].getSubsetNumber();
    vector<bool> changedSubsets(Subsets.size(), false);
    priority_queue<int> changedSubsetsQueue;

    for(unsigned int i = 0; i < Subsets[subsetsIndexes[cZI]].getElementos().size(); i++){
        int y = Subsets[subsetsIndexes[cZI]].getElementos().at(i);
        if(!elementosCobertos[y]){
            elementosCobertos[y] = true;
            elementosDescobertosSize--;
            for(unsigned int j = 0; j < elementos[y].size() ; j++){
                int z = subsetsIndexes[elementos[y].at(j)];
                Subsets[z].decrementSize();
                if(!changedSubsets[z]){
                    changedSubsets[z] = true;
                	changedSubsetsQueue.push(z);
                }
            }
        }
    }

    while(!changedSubsetsQueue.empty()){
    	int auxPos = changedSubsetsQueue.top();
    	changedSubsetsQueue.pop();
    	DesceHeap(Subsets, auxPos, subsetsIndexes);
    }
}

void coverElements(vector <Subset>& Subsets, vector <int>& subsetsIndexes, vector <bool>& elementosCobertos, int& elementosDescobertosSize, vector < vector <int> >& elementos){
    int cZI = Subsets[0].getSubsetNumber();

    for(unsigned int i = 0; i < Subsets[subsetsIndexes[cZI]].getElementos().size(); i++){
        if(!elementosCobertos[Subsets[subsetsIndexes[cZI]].getElementos().at(i)]){
            elementosCobertos[Subsets[subsetsIndexes[cZI]].getElementos().at(i)] = true;
            elementosDescobertosSize--;
            for(unsigned int j = 0; j < elementos[Subsets[subsetsIndexes[cZI]].getElementos().at(i)].size() ; j++){
                Subsets[subsetsIndexes[elementos[Subsets[subsetsIndexes[cZI]].getElementos().at(i)].at(j)]].decrementSize();
                DesceHeap(Subsets, subsetsIndexes[elementos[Subsets[subsetsIndexes[cZI]].getElementos().at(i)].at(j)], subsetsIndexes);
            }
        }
    }
}

void trataInput(char inputName[]){
    int n, m, auxWeight, auxQtdSubsets, auxSubset;
    int totalWeight = 0;
    ifstream inputSCP;
    inputSCP.open(inputName);
    inputSCP >> n >> m;
    fstream costLog;
    costLog.open("costLogComum.txt", std::fstream::in | std::fstream::out | std::fstream::app);

    int elementosDescobertosSize = n;
    vector <Subset> Subsets(m);
    vector <int> subsetsIndexes(m);
    vector < vector <int> > elementos(n);
    vector <bool> elementosCobertos(n, false);
    vector <int> subconjuntosEscolhidos;



    for(int i = 0; i < m; i++){
        inputSCP >> auxWeight;
        Subsets[i].setWeight(auxWeight);
        Subsets[i].setSubsetNumber(i);
        subsetsIndexes[i] = i;
    }

    for (int i = 0; i < n; i++){
        inputSCP >> auxQtdSubsets;
        for(int j = 0; j < auxQtdSubsets; j++){
            inputSCP >> auxSubset;
            elementos[i].push_back(auxSubset-1);
            Subsets[auxSubset-1].incrementSize();
            Subsets[auxSubset-1].adicionaElemento(i);
        }
    }
    Heapify(Subsets, subsetsIndexes);
    while(elementosDescobertosSize){
        totalWeight += Subsets[0].getWeight();
        subconjuntosEscolhidos.push_back(Subsets[0].getSubsetNumber());
        betterCoverElements(Subsets, subsetsIndexes, elementosCobertos, elementosDescobertosSize, elementos);
    }
    cout << "Total cover cost: " << totalWeight << endl;
    costLog << totalWeight << endl;
   /* for(unsigned int i = 0; i < subconjuntosEscolhidos.size(); i++){
        cout << subconjuntosEscolhidos[i]+1 << " ";
    }*/

    inputSCP.close();
}
