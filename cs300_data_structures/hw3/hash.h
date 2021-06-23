#ifndef _HASH_H
#define _HASH_H

#include <iostream>

using namespace std; 

template <class HashedObj>
class HashTable{
public:
	HashTable(const HashedObj& notFound,
		int size = 101);
	HashTable(const HashTable& rhs)
		: ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND),
		theLists(rhs.theLists) { }

	const HashedObj& find(const HashedObj& x) const;
	
	void makeEmpty();
	void insert(const HashedObj& x);
	void remove(const HashedObj& x);

	const HashTable<HashedObj>& operator=(const HashTable& rhs);

private:
	vector<vector<HashedObj> > theLists;
	const HashedObj ITEM_NOT_FOUND;
};

template <class HashedObj>
const HashTable<HashedObj>& HashTable<HashedObj>::operator=(const HashTable& rhs) {
	this->theLists = rhs.theLists;
	this->ITEM_NOT_FOUND = rhs.ITEM_NOT_FOUND;
	return *this;
}

bool isPrime(int n) {
	if (n == 2 || n == 3)
		return true;

	if (n == 1 || n % 2 == 0)
		return false;

	for (int i = 3; i * i <= n; i += 2)
		if (n % i == 0)
			return false;

	return true;
}

int nextPrime(int n) {
	if (n % 2 == 0)
		n++;

	for (; !isPrime(n); n += 2)
		;

	return n;
}

int myHash(int key, int tableSize) { //hashing for int key
	return  (key % tableSize);
}

int myHash(const string& key, int tableSize){ //hashing for string key
	int hashVal = 0;
	for (int i = 0; i < key.length(); i++)
		hashVal = 37 * hashVal + key[i];

	hashVal = hashVal % tableSize;

	if (hashVal < 0) //overflow may occur so we fix the negatives
		hashVal = hashVal + tableSize;

	return(hashVal);
}


template <class HashedObj>
HashTable<HashedObj>::HashTable(const HashedObj& notFound, int size)
	: ITEM_NOT_FOUND(notFound), theLists(nextPrime(size)){}


template <class HashedObj>
void HashTable<HashedObj>::makeEmpty(){ //makeing hash empty
	for (int i = 0; i < theLists.size(); i++)
		for (int j = 0; j < theLists[i].size(); j++) {
			theLists[i].pop_back();
		}
}

template <class HashedObj>
void HashTable<HashedObj>::insert(const HashedObj& x){ //inserting to hash with hashing
	int idx = myHash(x, theLists.size());
	theLists[idx].push_back(x);
}

template <class HashedObj>
void HashTable<HashedObj>::remove(const HashedObj& x){ //removing an HashedObj from hash
	int idx = myHash(x, theLists.size());
	int len = theLists[idx].size();
	HashedObj temp;
	bool check = false;
	int i;
	for (i = 0; i < len; i++)
		if (x == theLists[idx][i])
			break;

	if (i < len){	
		len = len - 1;
		for (int j = i; j < len; j++)
			theLists[idx][j] = theLists[idx][j+1];
		theLists[idx].pop_back();
	}
}

template <class HashedObj>
const HashedObj& HashTable<HashedObj>::find(const HashedObj& x) const{ //finding an HashedObj
	int idx = myHash(x, theLists.size());
	int len = theLists[idx].size();
	for (int i = 0; i < len; i++){
		if (x == theLists[idx][i])
			return theLists[idx][i];
	}
	return ITEM_NOT_FOUND;
}





#endif