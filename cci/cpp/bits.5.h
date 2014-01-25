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
//
// 5.2
//
string ToBinary(double num) {
    if (num > 1 || num < 0) 
        return "ERROR";

    string binary(".");
    while (num > 0) {
        if (binary.size() >= 32) 
            return "ERROR";
        
        num *= 2;
        if (num >= 1)
            binary.append("1");
        else
            binary.append("0");
 
        num -= (int) num; // no-op for the case where num < 1
    }
    return binary;
}
//
// 5.3
//
int GetNextLargestInteger(int n) {
    // calculate the number of 1 and 0's 
    int n_temp = n;
    int count_0 = 0;
    int count_1 = 0;

    // count all the trailing zeros
    while (((n_temp & 1) == 0) && (n_temp != 0)) {
        count_0++;
        n_temp >>= 1;
    }

    // count the trailing ones
    while ((n_temp & 1) == 1) {
        count_1++;
        n_temp >>= 1;
    }

    // if all the zeros in the number trail all the ones in the same number
    // (1111110000000), then there is no way to get a bigger number with the same
    // number of ones (since we need to find a "non-trailing zero" to flip (i.e a
    // zero that has 1's to the right of it. This will also cover the 11111111111
    // case
    // Also: if the number is 0, it has no ones so we cant find a bigger number with
    // the same number of 1
    if (count_0 + count_1 == 31 || count_0 + count_1 == 0)
        return -1;

    // find the position of the right most non-trailing 0
    int pos_non_trailing_0 = count_0 + count_1;

    // turn on this zero to a one
    n |= (1 << pos_non_trailing_0);

    // clear out all the bits to the right of pos_non_trailing_zero. We need to make
    // the appropriate a mask of the form 111111111110000000000 where the left 0 is
    // at pos-1
    int clear_right_mask = (1 << pos_non_trailing_0); // 000000001000000000
    clear_right_mask -= 1;                             // 000000000111111111
    clear_right_mask = ~clear_right_mask;               // 111111111000000000 
    n &= clear_right_mask; 

    // add count_1-1 ones back
    n |= (1 << (count_1-1))-1;
    return n;
}

int GetPreviousSmallestInteger(int n) {
    int n_temp = n;
    int count_1 = 0;
    int count_0 = 0;

    // count the trailing 1's
    while ((n_temp & 1) == 1) {
        count_1++;
        n_temp >>= 1;
    }

    // if n_temp is zero, we will not be able to find a non-trailing 1 (i.e a 1 with
    // 0's to the right of it)
    if (n_temp == 0) return -1;

    // count the following zero's
    while (((n_temp & 1) == 0) && (n_temp != 0)) {
        count_0++;
        n_temp >>= 1;
    }

    // find the position of the right most non-trailing 1
    int pos_non_trailing_1 = count_0 + count_1;

    // flip this 1 to a zero
    n &= ~(1 << pos_non_trailing_1); // ~(0000000000010000000000)

    // clear all bits at p-1 down to 0
    n &= (~0) << pos_non_trailing_1;

    // now we need to insert count_1+1 ones immediately to the right of p
    int mask_insert_ones = (1 << (count_1+1))-1; // 0000000000111111111
    n |= mask_insert_ones << (count_0 -1); // // - 1 accounts for the fact that we added a 1
    return n;
}

//
// 5.5
// 
int BitSwapsRequired(int a, int b) {
    int count = 0;
    // n & (n - 1) clears the most significant bit
    for (int n = a^b; n != 0; n = n & (n - 1))
        count++;
    return count;
}
int BitSwapsRequired2(int a, int b) {
    int count = 0;
    for (int n = a^b; n != 0; n >>= 1) 
        count += n & 1;
    return count;
}
//
// 5.6
//
//  generates oxAA AA AA AA AA 
//             "1010 1010 1010 1010 1010 1010 1010 1010"
int _MaskForEvenBits() { 
    int all_ones = ~0;
    int pos = 0;
    while (pos < 32) {
        if (pos % 2 == 0) 
            all_ones &= ~(1 << pos);
        pos++;
    }
    return all_ones;
}
// generates 0101 0101 0101 0101 0101 0101 0101 0101 (ox55555555)
int _MaskForOddBits() {
    int all_ones = ~0;
    int pos = 0;
    while (pos < 32) {
        if (pos % 2 == 1)
            all_ones &= ~(1 << pos);
        pos++;
    }
    return all_ones;
}

int SwapBits(int n) {
    return ( ((n & _MaskForEvenBits()) >> 1) | ((n & _MaskForOddBits()) << 1) ); 
}
int SwapBits2(int n) {
    return ( ((n & 0xAAAAAAAA) >> 1) | ((n & 0x55555555) << 1) ); 
}
//
// 5.7
//
typedef bitset<3> ThreeBitInt;
int _FindMissingInteger(vector<ThreeBitInt> const& input, int column) {
    if (column >= 3) return 0;

    // reserve to minize resize cost
    vector<ThreeBitInt> one_bits; one_bits.reserve(input.size() / 2); 
    vector<ThreeBitInt> zero_bits; zero_bits.reserve(input.size() / 2); 


    for(ThreeBitInt t : input) {
        if (t[column] == 0) 
            zero_bits.push_back(t);
        else
            one_bits.push_back(t);
    }

    if (zero_bits.size() <= one_bits.size()) {
        int v = _FindMissingInteger(zero_bits, column + 1);
        return (v << 1) | 0;
    }
    else {
        int v = _FindMissingInteger(one_bits, column + 1);
        return (v << 1) | 1;
    }
}

int FindMissingInteger(vector<ThreeBitInt> const& input) {
    return _FindMissingInteger(input, 0);
}