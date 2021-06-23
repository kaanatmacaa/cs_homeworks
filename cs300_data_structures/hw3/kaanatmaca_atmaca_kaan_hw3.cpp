#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include "hash.h"
using namespace std;

//Kaan ATMACA'S CS300 HW3

struct Series { //type for hash
public:
	Series() {}
	Series(string n) {
		name = n;
	}
	Series(string n, double d) {
		name = n;
		sup = d;
	}
	bool operator==(const Series& rhs) const {
		return (this->name == rhs.name);
	}
	bool operator!=(const Series& rhs) const {
		return (this->name != rhs.name);
	}
	const Series& operator=(const Series& rhs) {
		this->name = rhs.getName();
		this->sup = rhs.getSup();
		return *this;
	}
	string getName() const {
		return name;
	}
	double getSup() const {
		return sup;
	}

private:
	string name;
	double sup;
};

bool operator==(string lhs, Series rhs) {
	if (lhs == rhs.getName()) return true;
	return false;
}

ostream& operator<<(ostream& os, Series serie) {
	os << serie.getName();
	return os;
}

int myHash(const Series& serie, int tableSize) { //calls myHash
	return(myHash(serie.getName(), tableSize));
}

void outputFile(HashTable<Series>& lookupTable, HashTable<Series>& tableTwo, vector<string> & permutations, double confidence) { //creates ostream file 
	ofstream out;
	string fileName = "results.txt";
	out.open(fileName.c_str());
	double confValue;
	int plc;
	string serieName1, serieName2, seriesName;
	bool ch1, ch2;
	double d;
	sort(permutations.begin(), permutations.end());
	int total = 0;
	for (int i = 0; i < permutations.size(); i++) {
		plc = permutations[i].find(";");
		serieName1 = permutations[i].substr(0, plc);
		serieName2 = permutations[i].substr(plc + 1, permutations[i].length() - (plc + 1));
		seriesName = permutations[i];

		Series serie1(serieName1);
		Series serie2(serieName2);
		Series series(seriesName);

		serie1 = lookupTable.find(serie1);
		series = tableTwo.find(series);

		if (serie1.getSup() >= 0 && series.getSup() >= 0) { //if permution found return in ostream
			confValue = series.getSup() / serie1.getSup();
			if (confValue >= confidence) {
				total++;
				out << serie1.getName() << ";" << serie2.getName() << ";"; 
				d = (round(confValue * 100.0) / 100);
				if (d == 1) out << "1.00" << endl;
				else out << d << endl;
				
			}
		}

	}
	//	ch1 = false;
	//	ch2 = false;
	//	for (int j = 0; j < items.size(); j++) {
	//		if (items[j].getName() == serieName1) {
	//			serie1 = items[j];
	//			ch1 = true;
	//		}
	//		else if (items[j].getName() == serieName2) {
	//			serie2 = items[j];
	//			ch2 = true;
	//		}
	//	}
	//	if (ch1 && ch2) {
	//		serie1 = lookupTable.find(serie1);
	//	}
	//}
	if (total == 0) cout << "There is no rule for the given support and confidence values." << endl;
	else cout << total << " rules are written to results.txt" << endl;
}

vector<string> findPermutations(const vector<Series>& pairs) { //finding all possible permutations
	vector<string> permutations;
	string item;
	for (int i = 0; i < pairs.size(); i++) {
		for (int j = 0; j < pairs.size(); j++) {
			if (pairs[i] != pairs[j]) {
				if (pairs[i].getName().find(pairs[j].getName()) == string::npos && string::npos == pairs[j].getName().find(pairs[i].getName())) { //if ! left and right has the same name
					item = pairs[i].getName() + ";" + pairs[j].getName();
					permutations.push_back(item);
				}
			}
		}
	}
	return permutations;
}

void perDictToHash(const unordered_map<string, int>& dict, HashTable<Series>& table, int lines) { //turns unordered map into hashtable2 
	double supValue;
	Series serie;
	for (pair<string, int> element : dict) {
		supValue = (double)element.second / (double)lines;	
		Series serie(element.first, supValue);
		table.insert(serie);
	}
}

void dictToHash(const unordered_map<string, int>& dict, HashTable<Series>& table, double support, int lines, vector<Series> &items) { //turns unordered map into hashtable if new sup bigger or equall
	double supValue;
	Series serie;
	for (pair<string, int> element : dict){
		supValue = (double)element.second /(double)lines;
		if (supValue >= support) {
			Series serie(element.first, supValue);
			table.insert(serie);
			items.push_back(serie);
		}
	}
}

void readFilePermutations(unordered_map<string, int>& dictPermutations, const vector<string> &permutations, string fileName, int numOfLines) { //reading file and storing in unorderedmap and finding all possible permutations
	string s, word, pair;
	ifstream in;
	in.open(fileName.c_str());
	bool check;
	string found;
	int sizeOfPermutation;
	int total;
	while (getline(in, s)) {
		istringstream iss(s);
		vector<string> line;
		while (iss >> word) {
			line.push_back(word);
		}
		sort(line.begin(), line.end());
		for (int i = 0; i < permutations.size(); i++) { //for each permutation
			found = "";
			total = 0;
			sizeOfPermutation = 0;
			sizeOfPermutation = count(permutations[i].begin(), permutations[i].end(), ','); 
			sizeOfPermutation += 2; //the total count of words in one permutation
			check = true;
			for (int j = 0; j < line.size(); j++) {
				if (permutations[i].find(line[j]) != string::npos) {
					total++;
					found = permutations[i];
				}
			}
			if (sizeOfPermutation != total) check = false;
			if (check) {
				dictPermutations[found]++;
			}
		}
	}

	in.close();
}

void readFile(unordered_map<string, int> &dict, int &lines, string fileName) { //reading files and storing everyword in unorderedmap
	lines = 0; 
	string s, word;
	ifstream in;
	in.open(fileName.c_str());
	while (getline(in, s)) {
		istringstream iss(s);
		while (iss >> word) {
			dict[word]++;
		}
		lines++;
	}
	in.clear();
	in.seekg(0);
}

void readFilePairs(unordered_map<string, int>& dict, string fileName) { //reading file to store pairs in the same unorderedmap created before
	string s, word, pair;
	ifstream in;
	in.open(fileName.c_str());

	while (getline(in, s)) {
		istringstream iss(s);
		vector<string> line;
		while (iss >> word) {
			line.push_back(word);
		}
		for (int i = 0; i < line.size(); i++) {
			for (int j = i; j < line.size(); j++) {
				sort(line.begin(), line.end());
				if (line[i] != line[j]) {
					pair = line[i] + "," + line[j];
					dict[pair]++;
				}
			}
		}
	}
	in.clear();
	in.seekg(0);
}

int main() {
	string fileName;
	int numOfLines;

	cout << "Please enter the transaction file name: ";
	cin >> fileName;

	unordered_map<string, int> dict;
	Series serie;
	HashTable<Series> lookupTable(serie);
	readFile(dict, numOfLines, fileName);
	readFilePairs(dict, fileName);
	
	double support, confidence;
	cout << "Please enter support and confidence values between 0 and 1: ";
	cin >> support >> confidence;

	vector<Series> items;
	dictToHash(dict, lookupTable, support, numOfLines, items);
	vector<string> permutations = findPermutations(items);

	Series serie2;
	HashTable<Series> tableTwo(serie2);
	unordered_map<string, int> dictPermutations;
	readFilePermutations(dictPermutations, permutations, fileName, numOfLines);
	perDictToHash(dictPermutations, tableTwo, numOfLines);
	

	outputFile(lookupTable, tableTwo, permutations, confidence);

	tableTwo.makeEmpty();
	lookupTable.makeEmpty();
	
	return 0;
}