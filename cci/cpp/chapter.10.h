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
        handedOutCount(0) {}

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
int bitVectSize = (1 << 20); // 2^20 BITS (2^17 bytes)
int countBlocks = (1 << 12);  // 2^32 / 2^20
int* blocks = new int[countBlocks]; // space so far 2^2 * 2^12 = 2^14
BYTE* bitVect = new BYTE[bitVectSize/8]; // space so far = 2^14 + 2^17

void FindNumber() {
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



    
