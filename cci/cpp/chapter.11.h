#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <windows.h>
using namespace std;
//
//
//
void _P(int a[], int lenA) {
    for (int i = 0; i < lenA; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

template <class T>
void _swap(T* a, T* b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}

template <class T>
int _qs_partition(T array[], int left, int right) {
    T pivot = array[(left + right)/2];
    while (left <= right) {
        while (array[left] < pivot) {
            left++;
        }
        while (array[right] > pivot) {
            right--;
        }

        if (left <= right) {
            _swap(&array[left], &array[right]);
            left++; 
            right--;
        }
    }
    return left;
}

template<class T>
void _quicksort(T array[], int left, int right) {
    int pivotPoint = _qs_partition(array, left, right);
    if (pivotPoint-1 > left) {
        _quicksort(array, left, pivotPoint-1);
    }
    if (right > pivotPoint) {
        _quicksort(array, pivotPoint, right);
    }
}
template<class T>
void _merge(T array[], int left, int mid, int right) {
    int leftLen = (mid - left) + 1; // [left, mid] 
    int rightLen = (right - mid);    // [mid+1, right]
    vector<T> leftSide(&array[left], &array[left]+leftLen); // cache the left hand side
    vector<T> rightSide(&array[mid+1], &array[mid+1]+rightLen); // cache the right hand side
    
    size_t iWrite = left;
    size_t iLeft = 0;
    size_t iRight = 0;

    while (iLeft < leftSide.size() && iRight < rightSide.size()) {
        if (leftSide[iLeft] < rightSide[iRight]) {
            array[iWrite++] = leftSide[iLeft++];
        }
        else {
            array[iWrite++] = rightSide[iRight++];
        }
    }

    // copy any remainders
    while (iLeft < leftSide.size()) {
        array[iWrite++] = leftSide[iLeft++];
    }

    while (iRight < rightSide.size()) {
        array[iWrite++] = rightSide[iRight++];
    }
}
template<class T>
void _mergesort(T array[], int left, int right) {
    if (left < right) {
        int mid = (left + right)/2;
        _mergesort(array, left, mid);
        _mergesort(array, mid+1, right);
        _merge(array, left, mid, right);
    }
}

string SortChars(string& s) {
    char* key = new char[s.size()]; 
    s.copy(key, s.size());
    key[s.size()] = '\0';

    _quicksort(key, 0, s.size()-1);
    
    string value(key, s.size());
    return value;
}

void GroupAnagrams(vector<string>& list) {
    map<string, vector<string>> hashSet;
    for (size_t i = 0; i < list.size(); ++i) {
        string key = SortChars(list[i]);
        hashSet[key].push_back(list[i]);
    }
    map<string, vector<string>>::iterator iter;
    list.clear();
    for(iter = hashSet.begin(); iter != hashSet.end(); ++iter) {
        list.insert(list.end(), iter->second.begin(), iter->second.end());
    }
}
//
// 11.1
//
void MergeSorted(int a[], int countA, int b[], int countB) {
    _P(a, countA);
    _P(b, countB);
    
    int ia = countA - 1;
    int ib = countB - 1;
    int iwrite = countA + countB - 1;

    while ((ia >= 0) && (ib >= 0)) {
        if (a[ia] > b[ib]) {
            a[iwrite--] = a[ia--];
        } 
        else {
            a[iwrite--] = b[ib--];
        }
    }

    // copy over any remaining b's. Note that we do not need to copy
    // remaining a's as they are already in place
    while (ib >=0) {
        a[iwrite--] = b[ib--];
    }

    _P(a, countA + countB);
}