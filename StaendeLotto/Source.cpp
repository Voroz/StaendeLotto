#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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

// Doesn't count negative values.
template <size_t N>
int* countOccurences(int(&arr)[N], int maxVal){
	static int occArr[maxVal + 1] = { 0 };
	for (int i = 0; i < N; i++) {
		if (arr[i] <= maxVal) {
			occArr[arr[i]]++;
		}
	}
	return occArr;
}

// Arrays of same length
template <size_t N>
int* matchingArr(int(&arr1)[N], int(&arr2)[N], int numberToMatch){
	static bool arrMatch[N] = { 0 };
	for (int i = 0; i < N; i++){
		if (arr1[i] == arr2[i] == numberToMatch){
			arrMatch[i]++;
		}
	}
	return arrMatch;
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


// Skriver ut en lottorad
void main(){
	srand(time(NULL));

	int rad[7] = { 1, 5, 7, 10, 2, 25, 31 };
	Result result = lottoExperiment(rad, 52);
	cout << "Result" << endl;
	cout << "min matches: " << result.minResult << endl;
	cout << "max matches: " << result.maxResult << endl;
	cout << "avg matches: " << result.averageResult << endl;
	cout << "tries for max result: " << result.triesUntilMaxResult << endl;
	while (1){

	}
}