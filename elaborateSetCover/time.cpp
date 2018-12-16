#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <Windows.h>
using namespace std;

int main(int argc, char *argv[]){
	std::string auxInputName;
	ifstream inputName;
	inputName.open("testCases.txt");
	double timeSpent;
	struct timespec start, finish;

	while(!inputName.eof()){
		timeSpent = 0;
		std::stringstream stringBuilder;
		inputName >> auxInputName;
		stringBuilder << "main.exe setCoverTestCases/" << auxInputName;
		std::string completeString = stringBuilder.str();
		cout << endl << auxInputName << endl;
		clock_gettime(CLOCK_REALTIME, &start);
		int retCode = system(completeString.c_str());
		clock_gettime(CLOCK_REALTIME, &finish);
		timeSpent =  (finish.tv_sec - start.tv_sec);
		timeSpent += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
		cout << "Time spent: " << timeSpent << " seconds" << endl;
	}
	return 0;
}