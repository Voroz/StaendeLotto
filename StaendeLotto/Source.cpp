#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <sstream>
#include <vector>	// Använder bara för att göra användar input smidigare.


using namespace std;


struct Result{
	Result() :
		minResult(2147483647),
		maxResult(-2147483647),
		triesUntilMaxResult(0),
		averageResult(0){}
	Result(int min, int max, int triesUntilMax, int avg) :
		minResult(min),
		maxResult(max),
		triesUntilMaxResult(triesUntilMax),
		averageResult(avg){}

	int minResult;
	int maxResult;
	int triesUntilMaxResult;
	float averageResult;
};

template <size_t N>
int searchArray(int(&arr)[N], int number){
	for (int i = 0; i < N; i++){
		if (arr[i] == number){
			return i;
		}
	}
	return -1;
}

// Fyller i tal[…] med 7 OLIKA tal mellan 1 och 35
// Se till att talen i arrayen är utanför 1 till 35 vid initiering ifall vi ska få ett korrekt resultat.
void getLotto(int(&tal)[7]){
	for (auto &t : tal){
		int randNum = 1 + rand() % 35;
		while (searchArray(tal, randNum) != -1){
			randNum = 1 + rand() % 35;
		}
		t = randNum;
	}
}

template <size_t N>
int countOccurencesOf(int(&arr)[N], int number){
	int count = 0;
	for (int i = 0; i < N; i++){
		if (arr[i] == number){
			count++;
		}
	}
	return count;
}

Result lottoExperiment(int(&rad)[7], const int numWeeks){
	Result res;
	int sum = 0;

	for (int i = 0; i < numWeeks; i++) {
		int datorRad[7] = { 0 };
		getLotto((datorRad));
		int matches = 0;
		for (int j = 0; j < 7; j++){
			matches += countOccurencesOf(datorRad, rad[j]);
		}
		sum += matches;

		if (matches < res.minResult){
			res.minResult = matches;
		}
		if (matches > res.maxResult){
			res.maxResult = matches;
			res.triesUntilMaxResult = i + 1;
		}
	}
	res.averageResult = sum / numWeeks;

	return res;
}

vector<string> split(const string &str, char delim) {
	stringstream ss;
	ss.str(str);
	string item;
	vector<string> splitVec;
	while (getline(ss, item, delim)) {
		splitVec.push_back(item);
	}
	return splitVec;
}


void main(){
	srand(time(NULL));

	// Input 7 numbers and split into vector of strings.
	vector<string> splitStrings;
	string str = "";
	while (splitStrings.size() != 7){
		cout << "Enter \"lottorad\" (7 numbers separated by spaces): ";
		getline(cin, str);
		splitStrings = split(str, ' ');
	}
	
	// Convert to "rad" (array of ints)
	int rad[7] = { 0 };
	for (int i = 0; i < 7; i++){
		rad[i] = stoi(splitStrings[i]);
	}

	Result result = lottoExperiment(rad, 52);
	
	cout << "Result" << endl;
	cout << "min matches: " << result.minResult << endl;
	cout << "max matches: " << result.maxResult << endl;
	cout << "avg matches: " << result.averageResult << endl;
	cout << "tries for max result: " << result.triesUntilMaxResult << endl;
	while (1){

	}
}