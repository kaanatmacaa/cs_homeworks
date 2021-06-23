#ifndef _SORT_H
#define _SORT_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

template <class Comparable>
int binarySearch(vector <Comparable>& arr, int l, int r, string x, bool &check){
	if (r >= l) {
		int mid = l + (r - l) / 2;
		if (arr[mid] == x) {  //element in middle
			//return mid; THIS IS ANOTHER SOLUTION WE DO SMALL ITERATIVE SEARCH IN MAIN
			check = true;
			int n;
			n = mid;
			for (int i = mid; 0 <= i ; i--) { //finding the smallest index of element
				if (arr[i] == x){
					n = i;	
				}
				else break;
			}
			return n;	
		}			
		if (arr[mid] > x)    
			return binarySearch(arr, l, mid - 1, x, check);//if element smaller
		return binarySearch(arr, mid + 1, r, x, check); // else the element bigger
	}
	if (check) return 0;
	return -1;
}


template <class Comparable>
int sequentialSearch( vector <Comparable>& arr, string x){ //sequential search
	int i;
	bool check = false;
	for (i = 0; i < arr.size(); i++)
		if (arr[i] == x) {
			check = true;
			return i;
		}
	if (check == true) return 0;
	return -1;
}

template <class Comparable>
void InsertionSort(vector <Comparable>& a) { //insertion sort
	int j;
	for (int p = 1; p < a.size(); p++) {
		Comparable tmp = a[p];
		for (j = p; j > 0 && tmp < a[j - 1]; j--)
			a[j] = a[j - 1];
		a[j] = tmp;
	}
}
	
inline int leftChild(int i) {
	return 2 * i + 1;
}

template <class Comparable>
void percDown(vector<Comparable>& a, int i, int n) {
	int child;
	Comparable tmp;
	for (tmp = a[i]; leftChild(i) < n; i = child) {
		child = leftChild(i);
		if (child != n - 1 && a[child] < a[child + 1])
			child++;
		if (a[child] > tmp)
			a[i] = a[child];
		else
			break;
	}
	a[i] = tmp;
}

template <class Comparable>
	void heapSort(vector<Comparable>& a) {
		for (int i = a.size() / 2; i >= 0; i--) //building heap
			percDown(a, i, a.size());
		for (int j = a.size() - 1; j > 0; j--) { //sorting heap
			swap(a[0], a[j]);    //swaping max to last position
			percDown(a, 0, j); //forming heap again
		}
	}


template <class Comparable>
void quicksort(vector<Comparable>& a) { //qucik sort
	quicksort(a, 0, a.size() - 1);
}

template <class Comparable>
void insertionSort(vector<Comparable>& a, int left, int right) { //insertion sort
	for (int p = left + 1; p <= right; p++) {
		Comparable tmp = a[p];
		int j;
		for (j = p; j > left && tmp < a[j - 1]; j--)
			a[j] = a[j - 1];
		a[j] = tmp;
	}
}

template <class Comparable>
const Comparable& median3(vector<Comparable>& a, int left, int right) { //med3
	int center = (left + right) / 2;
	if (a[center] < a[left])
		swap(a[left], a[center]);
	if (a[right] < a[left])
		swap(a[left], a[right]);
	if (a[right] < a[center])
		swap(a[center], a[right]);
	swap(a[center], a[right - 1]);
	return a[right - 1];
}

template <class Comparable>
void quicksort(vector<Comparable>& a, int left, int right) { //inner quick sort
	if (left + 10 <= right) { //if more then 10
		Comparable pivot = median3(a, left, right);
		int i = left, j = right - 1;
		for (; ; ) {
			while (a[++i] < pivot) {}
			while (pivot < a[--j]) {}
			if (i < j) {
				Comparable tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;
			}		
			else
				break;
		}
		Comparable tmp = a[i]; //pivot
		a[i] = a[right - 1];
		a[right - 1] = tmp;
		
		quicksort(a, left, i - 1);       // sorting smaller values
		quicksort(a, i + 1, right);    //sorting larger values
	} 
	else  //insertion sort if less than 10
		insertionSort(a, left, right);
}


template <class Comparable>
void merge(vector<Comparable>& arr, int start, int mid, int end){ //merging
	int start2 = mid + 1;
	if (arr[mid] <= arr[start2]) {
		return;
	}
	while (start <= mid && start2 <= end) {
		if (arr[start] <= arr[start2]) {
			start++;
		}
		else {
			Comparable value = arr[start2];
			int index = start2;
			while (index != start) {
				arr[index] = arr[index - 1];
				index--;
			}
			arr[start] = value;
			start++;
			mid++;
			start2++;
		}
	}
}

template <class Comparable>
void mergeSort(vector<Comparable>& arr, int l, int r){ //inner mergesort recursive
	if (l < r) {
		int m = l + (r - l) / 2;
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

template <class Comparable>
void mergeSort(vector<Comparable>& a) { //merge
	mergeSort(a, 0, a.size() - 1);
}


#endif 

