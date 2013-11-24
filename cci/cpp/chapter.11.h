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