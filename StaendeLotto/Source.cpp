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
		averageResult(0){		
		for (int i = 0; i < 8; i++){
			occurences[i] = 0;
		}
	}

	Result(int min, int max, int triesUntilMax, int avg) :
		minResult(min),
		maxResult(max),
		triesUntilMaxResult(triesUntilMax),
		averageResult(avg){
		for (int i = 0; i < 8; i++){
			occurences[i] = 0;
		}
	}

	int occurences[8];
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

long long int factorial(long long int number) {
	long long int temp;

	if (number <= 1) return 1;

	temp = number * factorial(number - 1);
	return temp;
}

double binomial(int n, int k, double chance){
	return ((factorial(n) / (factorial(n - k) * factorial(k))) * pow(chance, k) * pow(1-chance, n-k));
}

// Todo: Verkar som att vi får overflow här, samt så funkar den ej även för lägre nummer.
double probabilityLotto(long long int n, long long int k, long long int nrOfLegalNumbers){
	long long int combinations = factorial(n) / (factorial(n - k) * factorial(k));
	return (double) 1 / (combinations * factorial(k) * factorial(nrOfLegalNumbers - n) * (factorial(nrOfLegalNumbers - n) / factorial(nrOfLegalNumbers - n - (n - k)))) / factorial(nrOfLegalNumbers);
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
		res.occurences[matches]++;
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

string stringRepeat(string str, int amount){
	string repeatedStr = "";
	for (int i = 0; i < amount; i++){
		repeatedStr += str;
	}
	return repeatedStr;
}


void main(){
	srand(time(NULL));
	const int numWeeks = 7000000;

	while (1){
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

		Result result = lottoExperiment(rad, numWeeks);
	
		cout << "Result" << endl;
		cout << "min matches: " << result.minResult << endl;
		cout << "max matches: " << result.maxResult << endl;
		cout << "avg matches: " << result.averageResult << endl;
		cout << "tries for max result: " << result.triesUntilMaxResult << endl << endl;
		cout << "Occurences" << "                     " << "Actual" << endl;
		for (int i = 0; i <= 7; i++){
			string str;
			str += to_string(result.occurences[i]);
			str += stringRepeat(" ", 12 - str.length());
			str += to_string((double)result.occurences[i] / numWeeks * 100);
			str += "%";
			str += stringRepeat(" ", 28 - str.length());
			double actual = probabilityLotto(7, i, 35) * 100;
			str += to_string(actual);
			str += "%";
			cout << i << "  " << str << endl;
		}
	}
}