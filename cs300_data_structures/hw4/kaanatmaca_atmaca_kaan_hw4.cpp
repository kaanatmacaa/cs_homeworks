#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "sort.h"
#include <chrono>
#include <unordered_map>

using namespace std;

//KAAN ATMACA'S CS300 HW4

struct Contact { //template type for each contract in file
	string fullname; //name surname
	string name, surname;
	long long phoneNum;
	string city;

	//OPERTORS for contract
	bool operator< (Contact& rhs) {
		if (fullname < rhs.fullname) return true;
		return false;
	}
	bool operator>(Contact& rhs) {
		if (fullname > rhs.fullname) return true;
		return false;
	}
	bool operator>(string& rhs) {
		if (fullname > rhs) return true;
		return false;
	}
	bool operator<(string& rhs) {
		if (fullname < rhs) return true;
		return false;
	}
	bool operator<= (Contact& rhs) {
		if (fullname <= rhs.fullname) return true;
		return false;
	}
	bool operator==(string& rhs) {
		if (fullname.find(rhs) != string::npos && (name.find(rhs) == 0  ||fullname.find(rhs) == 0)) return true;
		return false;
	}
};

ostream& operator<<(ostream& os, Contact& obj) { //cout 
	string s;
	s = obj.fullname ;
	transform(s.begin(), s.end(), s.begin(), ::toupper);
	os << s << +" +" << obj.phoneNum << " " << obj.city << endl;
	return os;
}

void speedup(unordered_map<string, long long>& dict) { //calculating ratios of speeds of various algorithms using unorderedmap
	cout << endl;
	cout << "SpeedUp between Search Algorithms" << endl;
	cout << "======================================" << endl;

	double div; 
	div = float(dict["sequentialSearch"]) / float(dict["binarySearch"]);
	cout << "(Sequential Search/ Binary Search) SpeedUp = " << div << endl << endl;

	cout << "SpeedUps between Sorting Algorithms" << endl;
	cout << "======================================" << endl;
	div = float(dict["insertion"]) / float(dict["quick"]);
	cout << "(Insertion Sort/ Quick Sort) SpeedUp = " << div << endl;
	div = float(dict["merge"]) / float(dict["quick"]);
	cout << "(Merge Sort/ Quick Sort) SpeedUp = " << div << endl;
	div = float(dict["heap"]) / float(dict["quick"]);
	cout << "(Heap Sort/ Quick Sort) SpeedUp = " << div << endl;
}

void searching(vector<Contact>& sortedVector, string searchedItem, unordered_map<string, long long>& dict) { //binary and sequential search 
	cout << "Searching for " << searchedItem << endl;
	cout << "======================================" << endl;
	int f;
	transform(searchedItem.begin(), searchedItem.end(), searchedItem.begin(), ::toupper);
	cout << "Search results for Binary Search:" << endl;
	auto start1 = chrono::high_resolution_clock::now();
	int n = sortedVector.size();
	bool ch = false;
	f = binarySearch(sortedVector, 0, n - 1, searchedItem, ch); //binary search
	auto end1 = chrono::high_resolution_clock::now();
	long long timer1 = (std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1).count());
	if (f == -1) {
		transform(searchedItem.begin(), searchedItem.end(), searchedItem.begin(), ::toupper);
		cout << searchedItem << " does NOT exist in the dataset" << endl;
	}
	else {
		//int st = f; ANOTHER WAY TO SOLVE: INSTEAD DOING ITERATIVE IN BINARY, DELETE ONE LINE UNDER
		//for (int i = f; 0 <= i; i--) { //finding the smallest index of element
		//	if (sortedVector[i] == searchedItem) {
		//		st = i;
		//	}
		//	else break;
		//}
		//for (int i = st; i < sortedVector.size(); i++) {
		for (int i = f; i < sortedVector.size(); i++) {
			if (sortedVector[i] == searchedItem) cout << sortedVector[i];
			else break;
		}
	}
	cout << endl;
	cout << "Binary Search Time: " << timer1 << " Nanoseconds" << endl << endl;

	cout << "Search results for Sequential Search:" << endl;
	auto start2 = chrono::high_resolution_clock::now();
	f = sequentialSearch(sortedVector, searchedItem); //sequential search
	auto end2 = chrono::high_resolution_clock::now();
	long long timer2 = (std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2).count());
	if (f == -1) {
		transform(searchedItem.begin(), searchedItem.end(), searchedItem.begin(), ::toupper);
		cout << searchedItem << " does NOT exist in the dataset" << endl;
	}
	else {
		for (int i = f; i < sortedVector.size(); i++) {
			if (sortedVector[i] == searchedItem) cout << sortedVector[i];
			else break;
		}
	}
	cout << endl;
	cout << "Sequential Search Time: " << timer2 << " Nanoseconds" << endl;
    
	//adding calculated times to unordered_map
	dict["binarySearch"] = timer1; 
	dict["sequentialSearch"] = timer2;
}

void sorting(vector<Contact>& insertVector, vector<Contact>& quickVector,
vector<Contact>& mergeVector, vector<Contact>& heapVector, unordered_map<string, long long> &dict) { //sorting vector in 4 different sort algorithms
	cout << "Sorting the vector copies" << endl;
	cout << "======================================" << endl;
	auto start2 = chrono::high_resolution_clock::now();
	quicksort(quickVector); //quick sort
	auto end2 = chrono::high_resolution_clock::now();
	long long timer2 = (std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2).count());
	cout << "Quick Sort Time: " << timer2 << " Nanoseconds" << endl;

	auto start1 = chrono::high_resolution_clock::now();
	InsertionSort(insertVector); //insert sort
	auto end1 = chrono::high_resolution_clock::now();
	long long timer1 = (std::chrono::duration_cast<std::chrono::nanoseconds>(end1 - start1).count());
	cout << "Insertion Sort Time: " << timer1 << " Nanoseconds" << endl;
	
	
	auto start3 = chrono::high_resolution_clock::now();
	mergeSort(mergeVector); //merge sort 
	auto end3 = chrono::high_resolution_clock::now();
	long long timer3 = (std::chrono::duration_cast<std::chrono::nanoseconds>(end3 - start3).count());
	cout << "Merge Sort Time: " << timer3 << " Nanoseconds" << endl;
 
	auto start4 = chrono::high_resolution_clock::now();
	heapSort(heapVector); //heap sort
	auto end4 = chrono::high_resolution_clock::now();
	long long timer4 = (std::chrono::duration_cast<std::chrono::nanoseconds>(end4 - start4).count());
	cout << "Heap Sort Time: " << timer4 << " Nanoseconds" << endl;
	cout << endl;

	//adding calculated times to unordered_map
	dict["quick"] = timer2;
	dict["insertion"] = timer1;
	dict["merge"] = timer3;
	dict["heap"] = timer4;
}

string readFile(vector<Contact> &insertVector, vector<Contact>& quickVector,
	vector<Contact>& mergeVector, vector<Contact>& heapVector){ //reading file and pushing into each vector
	string fileName, s;
	string name, surname, fullname, city;
	long long num;
	Contact c;
	ifstream in;
	cout << "Please enter the contact file name:" << endl;
	cin >> fileName;
	in.open(fileName.c_str());
	while (getline(in, s)) {
		istringstream iss(s);
		iss >> name >> surname >> num >> city; 
		transform(name.begin(), name.end(), name.begin(), ::toupper);
		transform(surname.begin(), surname.end(), surname.begin(), ::toupper); 
		c.name = name;
		c.surname = surname;
		c.phoneNum = num;
		c.city = city;
		fullname= name + " " + surname;
		transform(fullname.begin(), fullname.end(), fullname.begin(), ::toupper);
		c.fullname = fullname;
		insertVector.push_back(c);
		quickVector.push_back(c);
		mergeVector.push_back(c);
		heapVector.push_back(c);
	}
	string searchedContact;
	cout << "Please enter the word to be queried :" << endl ;
	cin.ignore();
	getline(cin, searchedContact);
	
	cout << endl;
	//transform(searchedContact.begin(), searchedContact.end(), searchedContact.begin(), ::toupper);
	return searchedContact;
}

int main() {
	vector<Contact> insertVector;
	vector<Contact> quickVector;
	vector<Contact> mergeVector;
	vector<Contact> heapVector;
	unordered_map<string, long long> dict;
	string contact; 
	
	contact = readFile(insertVector, quickVector, mergeVector, heapVector);
	sorting(insertVector, quickVector, mergeVector, heapVector, dict);
	searching(insertVector, contact, dict);
	speedup(dict);

	return 0;
}