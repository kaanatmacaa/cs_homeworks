#include "BinarySearchTree.h"
#include "AvlTree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>

using namespace std;
//KAAN ATMACA'S PROGRAM 
//CS300 DATA STRUCTURES - HW2 

struct Item {  //item struct for each item in section
	Item() {}
	Item(string t) : title(t) {}
	Item(string t, string i) : title(t), info(i) {}
	string title;
	string info;

	bool operator>(const Item& rhs) { // if(one>two)
		if (this->title > rhs.title) {
			return true;
		}
		return false;
	}

	bool operator<(const Item& rhs) { 
		if (this->title < rhs.title) {
			return true;
		}
		return false;
	}

	Item& operator=(const Item& rhs) { 
		this->title = rhs.title;
		this->info = rhs.info;
		return *this;
	}

	friend ostream& operator<<(ostream& os, const Item& ct);
	
};

struct Section { //a section struct which will be implemented as type to bst 
	Section() {}
	Section(string n) : title(n) {}
	string title; 
	BinarySearchTree<Item> items; //the items as bst

	bool operator>(const Section &rhs) {
		if (this->title > rhs.title) {
			return true;
		}
		return false;
	}

	bool operator<(const Section &rhs) {
		if (this->title < rhs.title) {
			return true;
		}
		return false;
	}

	//Section& operator=(const Section& rhs) {
	//	this->title = rhs.title;
	//	this->items = rhs.items; 
	//	return *this;
	//}
	
	bool operator==(Section& rhs) {
		if (this->title == rhs.title) return true;
		return false;
	}
	
	friend ostream& operator<<(ostream& os, const Section& ct);
	friend bool operator==(Section& lhs, Section& rhs);
};

struct SectionAvl { //a struct section which will be the type of avl tree
	SectionAvl() {}
	SectionAvl(string n) : title(n) {}
	string title;
	AvlTree<Item> items; //the avl tree for each sections items

	bool operator>(const SectionAvl& rhs) {
		if (this->title > rhs.title) {
			return true;
		}
		return false;
	}

	bool operator<(const SectionAvl& rhs) {
		if (this->title < rhs.title) {
			return true;
		}
		return false;
	}

	bool operator==(SectionAvl& rhs) {
		if (this->title == rhs.title) return true;
		return false;
	}

	friend ostream& operator<<(ostream& os, const SectionAvl& ct);
	friend bool operator==(SectionAvl& lhs, SectionAvl& rhs);
};

ostream& operator<<(ostream& os, const Section& ct){ 
	os << ct.title; 
	return os;
}

ostream& operator<<(ostream& os, const Item& ct) {
	os << ct.title;
	return os;
}

ostream& operator<<(ostream& os, const SectionAvl& ct) {
	os << ct.title;
	return os;
}

bool operator==(Section &lhs, Section &rhs) {
	if (lhs.title == rhs.title) return true;
	return false;
}

bool operator==(SectionAvl& lhs, SectionAvl& rhs) {
	if (lhs.title == rhs.title) return true;
	return false;
}

int inputCheck(string &n) { //input check for string entries in cin menu
	int x;
	if (n.length() == 1)
		if (isdigit(n[0])) {
			x = stoi(n);
			if (x > 0 || x < 8) return x;
		}
		else {
			while (true) {
				cout << "Invalid Input." << endl;
				cout << "Input: ";
				cin >> n;
				cout << endl;
				if (n.length() == 1)
					if (isdigit(n[0])) {
						x = stoi(n);
						if (x > 0 || x < 8) return x;
					}
			}
		}
}

bool checkIfExistSec(BinarySearchTree<Section>& ntbook, string secName) { //checking if section exists
	if (ntbook.find(secName).title == secName)return true;
	return false;
}

bool checkIfItemExist( BinarySearchTree<Section>& ntbook, string secName, string titleName) {//checking if item exists in avl section
	if (ntbook.find(secName).items.find(titleName).title == titleName) return true;
	return false;
}

bool checkIfItemExistAvl(AvlTree<SectionAvl>& avbook, string secName, string titleName) { //checking if item exists in avl section
	if (avbook.find(secName).items.find(titleName).title == titleName) return true;
	return false;
}

void displayBstItems( BinarySearchTree<Section>& ntbook, const string& secName) { //prints bst inorder
	if (ntbook.find(secName).items.isEmpty()) {
		cout << endl;
		cout << "*****" << endl;
		cout << "*****" << endl;
	}
	else {
		cout << endl;
		cout << "*****" << endl;
		ntbook.find(secName).items.printTree(); //when empty dont write empty
		cout << "*****" << endl;
	}
}

void displayAvlItems(AvlTree<SectionAvl>& avbook, const string& secName) { //prints avl inorder
	if (avbook.find(secName).items.isEmpty()) {
		cout << endl;
		cout << "*****" << endl;
		cout << "*****" << endl;
	}
	else {
		cout << endl;
		cout << "*****" << endl;
		avbook.find(secName).items.printTree(); //when empty dont write empty
		cout << "*****" << endl;
	}
}

void displayItemInfo( BinarySearchTree<Section>& ntbook, AvlTree<SectionAvl>& avbook, const string& secName) { //displays the item info and checks if exists
	string itemTitle;
	cout << "Enter the title of the item: ";
	cin.ignore();
	getline(cin, itemTitle);
	bool chk1, chk2;
	
	auto start = std::chrono::high_resolution_clock::now();
	chk1 = checkIfItemExistAvl(avbook, secName, itemTitle);
	if (chk1) avbook.find(secName).items.find(itemTitle).info;
	auto end = std::chrono::high_resolution_clock::now();
	long long timer = (end - start).count() / 1000.0;
	cout << "[AVL] Elapsed time: " << timer << " microseconds" << endl;

	auto start1 = std::chrono::high_resolution_clock::now();
	chk2 = checkIfItemExist(ntbook, secName, itemTitle);
	if (chk1) ntbook.find(secName).items.find(itemTitle).info;
	auto end1 = std::chrono::high_resolution_clock::now();
	long long timer1 = (end1 - start1).count() / 1000.0;
	cout << "[BST] Elapsed time: " << timer1 << " microseconds" << endl;

	if(!chk1) cout << "Invalid title." << endl;	
	else cout << ntbook.find(secName).items.find(itemTitle).info << endl;
}

void addItem(BinarySearchTree<Section>& ntbook, AvlTree<SectionAvl>& avbook, const string& secName) { //adds item to given section
	string itemName;
	cout << "Enter a title for the item: ";
	cin.ignore();
	getline(cin, itemName);
	if(checkIfItemExist(ntbook, secName, itemName)) 
	cout << "Item \"" << itemName << "\" already exists in the \"" << secName << "\"." << endl;
	else {
		string response;
		Item item;
		cout << "Enter a description for the item: ";
		cin.ignore();
		getline(cin, response);
		item.title = itemName;
		item.info = response; 
		auto startAvl = std::chrono::high_resolution_clock::now();
		avbook.find(secName).items.insert(item);
		auto endAvl = std::chrono::high_resolution_clock::now();
		long long timerAvl = (endAvl - startAvl).count() / 1000.0;
		cout << "[AVL] Elapsed time: " << timerAvl << " microseconds" << endl;

		auto startBst = std::chrono::high_resolution_clock::now();
		ntbook.find(secName).items.insert(item);
		auto endBst = std::chrono::high_resolution_clock::now();
		long long timerBst = (endBst - startBst).count() / 1000.0;
		cout << "[BST] Elapsed time: " << timerBst << " microseconds" << endl;
		
		cout << "The new item \"" << item.title << "\" has been inserted." << endl;
	}
}

void updateInfo(BinarySearchTree<Section>& ntbook, AvlTree<SectionAvl>& avbook,const string& secName) { //updates the info in section if it exists
	string itemTitle;
	cout << "Enter a title for the item: ";
	cin.ignore();
	getline(cin, itemTitle);
	bool chk1, chk2;
	string response;
	auto start = std::chrono::high_resolution_clock::now();
	chk1 = checkIfItemExistAvl(avbook, secName, itemTitle);
	auto end = std::chrono::high_resolution_clock::now();
	auto start1 = std::chrono::high_resolution_clock::now();
	chk1 = checkIfItemExist(ntbook, secName, itemTitle);
	auto end1 = std::chrono::high_resolution_clock::now();
	long long timer = (end - start).count() / 1000.0;
	cout << "[AVL] Elapsed time: " << timer << " microseconds" << endl;
	long long timer1 = (end1 - start1).count() / 1000.0;
	cout << "[BST] Elapsed time: " << timer1 << " microseconds" << endl;

	if (chk1)
	{
		cout << "Enter the new information: ";
		cin.ignore();
		getline(cin, response);
	}
	//auto start = std::chrono::high_resolution_clock::now();
	chk1 = checkIfItemExistAvl(avbook, secName, itemTitle);
	if (chk1)avbook.find(secName).items.find(itemTitle).info = response;	
	//auto end = std::chrono::high_resolution_clock::now();
	//long long timer = (end - start).count() / 1000.0;
	//cout << "[AVL] Elapsed time: " << timer << " microseconds" << endl;

	//auto start1 = std::chrono::high_resolution_clock::now();
	chk1 = checkIfItemExist(ntbook, secName, itemTitle);
	if (chk1)ntbook.find(secName).items.find(itemTitle).info = response;
	//auto end1 = std::chrono::high_resolution_clock::now();
	//long long timer1 = (end1 - start1).count() / 1000.0;
	//cout << "[BST] Elapsed time: " << timer1 << " microseconds" << endl;

	if (chk1) 
		cout << "The content " << itemTitle << " has been updated." << endl;
	else 
		cout << "Item \"" << itemTitle << "\" does not exist in the \"" << secName << "\"." << endl;
}

void delItem(BinarySearchTree<Section>& ntbook, AvlTree<SectionAvl>& avbook, const string& secName) { //deletes items if they exist in section
	string itemName;
	cout << "Enter a title for the item: ";
	cin.ignore();
	getline(cin, itemName);
	if (checkIfItemExist(ntbook, secName, itemName)) {
		auto startAvl = std::chrono::high_resolution_clock::now();
		avbook.find(secName).items.remove(itemName);
		auto endAvl = std::chrono::high_resolution_clock::now();
		long long timerAvl = (endAvl - startAvl).count() / 1000.0;
		cout << "[AVL] Elapsed time: " << timerAvl << " microseconds" << endl;

		auto startBst = std::chrono::high_resolution_clock::now();
		ntbook.find(secName).items.remove(itemName);
		auto endBst = std::chrono::high_resolution_clock::now();
		long long timerBst = (endBst - startBst).count() / 1000.0;
		cout << "[BST] Elapsed time: " << timerBst << " microseconds" << endl;

		cout << "The item \"" << itemName << "\" has been deleted." << endl;
	}
	else {
		cout << "Item \"" << itemName << "\" does not exist in the \"" << secName << "\"." << endl;
	}
}

void menuForSection(BinarySearchTree<Section>& ntbook, const string &secName, AvlTree<SectionAvl>& avbook){ //the main menu for one section in notebook
	int n ; 
	string number;
	cout << "Selected section -> "<< secName << endl;
	cout << "Please enter an input between [1 - 7]:" << endl;
	cout << "1- Display the items [AVL]" << endl;
	cout << "2- Display the items [BST]" << endl;
	cout << "3- Display the information of a item" << endl;
	cout << "4- Add new item" << endl;
	cout << "5- Update the information of a item" << endl;
	cout << "6- Delete an item" << endl;
	cout << "7- Return to main menu" << endl;
	cout << "Input: ";
	cin >> number;
	n = inputCheck(number);
	while (n != 7) {
		if (n == 1) displayAvlItems(avbook, secName);
		if (n == 2) displayBstItems(ntbook, secName); //why cant i do it the second time
		else if (n == 3) displayItemInfo(ntbook, avbook, secName);
		else if (n == 4) addItem(ntbook, avbook, secName);
		else if (n == 5) updateInfo(ntbook, avbook, secName);
		else if (n == 6) delItem(ntbook, avbook, secName);
		else if (n == 7) break;	
		cout << endl; 
		cout << "Input: ";
		cin >> number;
		n = inputCheck(number);
	}
	cout << endl;
}

void displayBST(const BinarySearchTree<Section>& ntbook) { //displays bst
	if (ntbook.isEmpty()) {
		cout << endl;
		cout << "*****" << endl;
		cout << "*****"<< endl; ;
	}
	else {
		cout << endl;
		cout << "*****" << endl;
		ntbook.printTree();
		cout << "*****" << endl;
	}
}

void addSection(BinarySearchTree<Section>& ntbook, AvlTree<SectionAvl>& avbook) { //adds new section if it is not already existing
	string sectionName; 
	cout << "Enter a title for the section: ";
	cin.ignore();
	getline(cin, sectionName);
	if (checkIfExistSec(ntbook, sectionName))
		cout << "Section \"" << sectionName << "\" already exists." << endl;
	else {
		avbook.insert(sectionName);
		ntbook.insert(sectionName);
		cout << "The new section \"" << sectionName << "\" has been inserted" << endl;
	}
}

void delSection(BinarySearchTree<Section>& ntbook, AvlTree<SectionAvl>& avbook) { //deletes section from tree
	string sectionName;
	cout << "Enter a title for the section: ";
	cin.ignore();
	getline(cin, sectionName);

	if (checkIfExistSec(ntbook, sectionName)) {
		avbook.remove(sectionName);
		ntbook.remove(sectionName);
		
		cout << "Section \"" << sectionName << "\" has been deleted." << endl;
	}
	else {
		cout << "Section \"" << sectionName << "\" does not exists." << endl;
	}
}

void displayAVL(const AvlTree<SectionAvl>& avbook) { //prints avl trees sections
	if (avbook.isEmpty()) {
		cout << endl;
		cout << "*****" << endl;
		cout << "*****" <<endl ;
	}
	else {
		cout << endl;
		cout << "*****" << endl;
		avbook.printTree();
		cout << "*****" << endl;
	}
}

void printMenu() { //print main menu
	cout << "MENU" << endl;
	cout << "Please enter an input between [1 - 6]:" << endl;
	cout << "1- Display the sections [AVL]" << endl;
	cout << "2- Display the sections [BST]" << endl;
	cout << "3- Select a section" << endl;
	cout << "4- Add new section" << endl;
	cout << "5- Delete a section" << endl;
	cout << "6- Exit" << endl;
}

void readFile(BinarySearchTree<Section> & ntbook, AvlTree<SectionAvl> & avbook) { //reads file and creates the trees
	cout << "Welcome to the the Notes" << endl << endl;
	ifstream in;
	string fileName = "data.txt";
	in.open(fileName.c_str());
	string s, word, sectionTitle, sectionInfo;	
	int place;
	Section* sec = new Section; //section for bst
	SectionAvl* secAvl = new SectionAvl; //section for avl
	Item* item = new Item; //item for bst
	Item* itemAvl = new Item; //item for avl
	string theTitle="";  
	long long itemsTimeBst = 0, itemsTimeAvl = 0; //this will be added each time to find total time of insertion for trees
	while (getline(in, s)) {
		istringstream iss(s);
		if (s[0] != '-') {
			if (theTitle != "") {
				sec->title = theTitle;
				secAvl->title = theTitle;
				auto start = std::chrono::high_resolution_clock::now();
				avbook.insert(*secAvl);
				auto endAvl = std::chrono::high_resolution_clock::now();

				auto startBst = std::chrono::high_resolution_clock::now();
				ntbook.insert(*sec);
				auto endBst = std::chrono::high_resolution_clock::now();

				long long timerAvl = (endAvl - start).count() / 1000.0; //total time of adding section
				timerAvl += itemsTimeAvl; //total time of adding each item to that section is added
				cout << "Section \"" << secAvl->title << "\" has been inserted into the AVL notebook." << endl;
				cout << "[AVL] Elapsed time: " << timerAvl << " microseconds" << endl;
				long long timerBst =(endBst - startBst) .count() / 1000.0; //total time of adding section to bst
				timerBst += itemsTimeBst; //total time of adding to items to bst items
				cout << "Section \"" << sec->title << "\" has been inserted into the BST notebook." << endl;
				cout << "[BST] Elapsed time: " << timerBst << " microseconds" << endl;
				cout << endl;
				long long itemsTimeBst = 0, itemsTimeAvl = 0; //we reset the total time for items
			}
			theTitle = s;
			sec = new Section; //create new section for bst
			secAvl = new SectionAvl; //create new section for avl
		}
		else { //inserting items
			place = s.rfind("-");
			sectionTitle = s.substr(1, place - 1);
			sectionInfo = s.substr(place + 1);
			item->title = sectionTitle;
			item->info = sectionInfo;
			itemAvl->title = sectionTitle;
			itemAvl->info = sectionInfo;
			auto bst = std::chrono::high_resolution_clock::now();
			sec->items.insert(*item); //inserting to sections bst tree
			auto bst2 = std::chrono::high_resolution_clock::now();
			itemsTimeBst += (bst2 - bst).count() / 1000.0;

			auto avl = std::chrono::high_resolution_clock::now();
			secAvl->items.insert(*itemAvl); //inserting to sections avl tree
			auto avl2 = std::chrono::high_resolution_clock::now();
			itemsTimeAvl += (avl2 - avl).count() / 1000.0;
		}
	}
	//after inserting all the last sections arent still added so we add them here
	sec->title = theTitle;
	secAvl->title = theTitle;

	auto start = std::chrono::high_resolution_clock::now();
	avbook.insert(*secAvl);
	auto endAvl = std::chrono::high_resolution_clock::now();
	long long timerAvl = (endAvl - start).count() / 1000.0;
	timerAvl += itemsTimeAvl;

	auto startBst = std::chrono::high_resolution_clock::now();
	ntbook.insert(*sec);
	auto endBst = std::chrono::high_resolution_clock::now();
	long long timerBst = (endBst - startBst).count() / 1000.0;
	timerBst += itemsTimeBst;
	
	cout << "Section \"" << sec->title << "\" has been inserted into the AVL notebook." << endl;
	cout << "[AVL] Elapsed time: " << timerAvl << " microseconds" << endl;
	cout << "Section \"" << sec->title << "\" has been inserted into the BST notebook." << endl;
	cout << "[BST] Elapsed time: " << timerBst << " microseconds" << endl;
	cout << endl;
}

int main() {
	int n = 0;
	string number;
	string secName;
	BinarySearchTree<Section> ntbook; //creating empty notebook with bst
	AvlTree<SectionAvl> avbook; //creating empty notebook with avl 
	readFile(ntbook, avbook); //reading section by section
	printMenu();
	cout << "Input: ";
	cin >> number;
	n = inputCheck(number);
	while(n!=6) {	//main menus functions to go to
		if (n == 1) displayAVL(avbook);
		else if (n == 2) displayBST(ntbook);
		else if (n == 4) addSection(ntbook, avbook);
		else if (n == 5) delSection(ntbook, avbook);
		else if (n == 3) {
			cout << "Enter the title of the section: ";
			cin >> secName;
			if (checkIfExistSec(ntbook, secName)) { //create a check if exist for avltree
				cout << endl;
				menuForSection(ntbook, secName, avbook); 
				printMenu();
			}
			else cout << "Invalid title!" << endl<< endl;	
		}
		if(n!=3) cout << endl;
		
		cout << "Input: ";
		cin >> number;
		n = inputCheck(number);
		if (n == 6) break;
	} 
	avbook.makeEmpty();
	ntbook.makeEmpty();
	return 0; 
}