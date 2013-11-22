#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <windows.h>
using namespace std;

class Scanner {
public:
    Scanner():
        totalCount(60000),
        missingValue(17869),
        handedOutCount(-1) {}

    bool HasInt() {
        //printf("totalCount = {%d}, handedCount = {%d}\n", totalCount, handedOutCount); 
        return (totalCount > handedOutCount);
    }

    int getNext() {
        handedOutCount++;
        if (handedOutCount == missingValue) {
            printf("GetNext = skipping {%d}\n", handedOutCount);
            handedOutCount++;
        }
        return handedOutCount;
    }

    int totalCount;
    int missingValue;
    int handedOutCount;
};

//
// 10.3 (10 MB case)
//
// 10MB is 2^23 bytes
void FindNumber() {
    int bitVectSize = (1 << 20); // 2^20 BITS (2^17 bytes)
    int countBlocks = (1 << 12);  // 2^32 / 2^20
    vector<int> blocks(countBlocks); // space so far 2^2 * 2^12 = 2^14
    vector<BYTE> bitVect(bitVectSize/8);

    Scanner s;
    while (s.HasInt()) {
        blocks[s.getNext() / bitVectSize]++;
    }

    // each block should have a count of bitVectSize
    int startingVal = -1;
    int endingVal = 0;
    for (int i = 0; i < countBlocks; ++i) {
        if (blocks[i] < bitVectSize) {
            startingVal = i * bitVectSize;
            endingVal = startingVal + bitVectSize;
            break;
        }
    }
    Scanner s2;
    while (s2.HasInt()) {
        int n = s2.getNext();
        if ((n >= startingVal) && (n < endingVal)) {
            // we subtract startingVal because the bit vector is tracking 
            // bitVect numbers starting from starting val+1.
            bitVect[(n - startingVal) / 8] |= 1 << ((n - startingVal) % 8);
        }
    }

    // now we go through and look for the first one that was missing
    for (int i = 0; i < bitVectSize/8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if ((bitVect[i] & (1 << j)) == 0) {
                printf("Missing Number! = %d\n", i * 8 + j + startingVal);
                return;
            };
        }
    }
}

//
// 10.4
//
vector<int> _getArray() {
    vector<int> arr(32000);
    for (size_t i = 0; i < arr.size(); ++i) {
        // make 1423 a duplicate
        arr[i] = ((i == 1423) ? arr[i-1] : i + 1);
    }
    return arr;
}
void CheckDuplicates(vector<int>& arr) {
    assert(arr.size() == 32000);
    vector<BYTE> set(arr.size());

    for (size_t i = 0; i < arr.size(); ++i) {
        int n = arr[i] - 1; // arr has values 1+1 but bitset tracks 0+
        if ((set[n/8] & 1 << (n%8)) != 0) {
            printf("%d is a duplicate! \n", n+1);
        }
        else {
            set[n/8] |= 1 << (n%8);
        }
    }
}





    
