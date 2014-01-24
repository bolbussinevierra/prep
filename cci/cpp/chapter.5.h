#include <iostream>
#include <assert.h>
int const k_pos_max = (sizeof(int) * CHAR_BIT) - 1;
//
// 5.1
//
int InsertBits(int into, int insert, uint i, uint j) {
    assert(i <= k_pos_max && j <= k_pos_max);
    // make the right side of the mask
    int all_ones = ~0;
    int right_mask = all_ones << (j+1); // all ones position j+1 (bits to preserve)
    int left_mask = (1 << i) - 1;    // shift 1 to position i then substract 1 to turn
                                   // set all bits [0, i-1] to 1 (digits to preserve)
    int mask = right_mask | left_mask;
    int into_masked = into & mask;
    int insert_shifted = insert << i;

    return into_masked | insert_shifted;
}

