#include <iostream>
#include <assert.h>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "chapter.11.h"
#pragma warning (disable: 4018)
//
// 17.2
//

enum Type {
    X,
    O,
    Empty
};
struct Move {
    int row;
    int col;
    Type value;
};

bool CheckRow(Move m, vector<vector<Type>>& b) {
    for (size_t col = 0; col < b.size(); ++col) {
        if (b[m.row][col] != m.value) {
            return false;
        }
    }
    return true;
}

bool CheckCol(Move m, vector<vector<Type>>& b) {
    for (size_t row = 0; row < b.size(); ++row) {
        if (b[row][m.col] != m.value) {
            return false;
        }
    }
    return true;
}

bool MoveInMainDiagonal(Move m) {
    return m.row == m.col;
}

bool MoveInSecondaryDiagonal(Move m, int size) {
    return m.row == size - 1 - m.col;
}

bool CheckMainDiagonal(Move m, vector<vector<Type>>& b) {
    for (size_t row = 0; row < b.size(); ++row) {
        if (b[row][row] != m.value) {
            return false;
        }
    }
    return true;
}

bool CheckSecondaryDiagonal(Move m, vector<vector<Type>>& b) {
    for (size_t row = 0; row < b.size(); ++row) {
        if (b[b.size()-row-1][row] != m.value) {
            return false;
        }
    }
    return true;
}

bool IsWinningMove(Move m, vector<vector<Type>>& b) {
    assert(b.size() == b[0].size());
    assert(m.value != Empty);

    return (CheckRow(m, b) || CheckCol(m, b) ||
        (MoveInMainDiagonal(m) && CheckMainDiagonal(m, b)) ||
        (MoveInSecondaryDiagonal(m, b.size()) && CheckSecondaryDiagonal(m, b)));
    
}

//
//
// 17.3
int CountZerosBest(int num) {
    if (num < 0) return -1;
    int count = 0;
    for (int i = 5; num / i > 0; i *= 5) {
        count += num / i;
    }
    return count;
}

int CountFactorsOf5(int num) {
    int count = 0;
    while (num % 5 == 0) { // while still divisible by 5
        count++;
        num /= 5;
    }
    return count;
}

int CountZerosGood(int num) {
    if (num < 0) return -1;
    int count = 0;
    for (int i = 2; i <= num; ++i) {
        count += CountFactorsOf5(i);
    }
    return count;
}

//
// 17.4
//
int invert(int bit) { return 1^bit; }
int get_sign(int n) { return invert((n >> 31) & 1); }

int safe_max_opt(int a, int b) {
    int sa = get_sign(a);
    int sb = get_sign(b);
    int sd = get_sign(a - b);

    int use_sa = sa^sb;
    int s = (use_sa*sa) + (invert(use_sa) * sd);
    int inv_s = invert(s);

    return (a * s) + (b * inv_s);
}
//
// 17.6
//
int GetLeftEnd(vector<int> const& a) {
    for (int i = 1; i < a.size(); ++i) {
        if (a[i] < a[i-1]) {
            return i-1;
        }
    }
    return a.size() - 1;
}

int GetRightStart(vector<int> const& a) {
    for (int i = a.size() - 2; i >= 0; --i) {
        if (a[i] > a[i+1]) {
            return i+1;
        }
    }
    return 0;
}

void GetMinMaxInRange(vector<int> const& a, int start, int end, 
                      int& minI, int& maxI) {
    minI = start;
    maxI = start;

    for (int i = start; i <= end; ++i) {
        if (a[i] < a[minI]) {
            minI = i;
        }
        if (a[i] > a[maxI]) {
            maxI = i;
        }
    }
}
    
void GetSortRange(vector<int> const& a) {
    assert(a.size() > 1);

    int el = GetLeftEnd(a);
    int sr = GetRightStart(a);

    if (el == a.size() - 1) return; // sorted
   
    int minI = -1;
    int maxI = -1;
    GetMinMaxInRange(a, el+1, sr-1, minI, maxI);
    cout << "middle_min=" << a[minI] << " middle_max=" << a[maxI] << endl;

    // adjust the left;
    int i=0;
    for (i = el; i >=0; --i) {
        if (a[i] <= a[minI]) {
            minI = i+1;
            break;
        }
    }
    if (i == -1) minI=0;

    // adjust the right
    for (i = sr; i < a.size(); ++i) {
        if (a[i] >= a[maxI]) {
            maxI = i-1;
            break;
        }
    }
    if (i == a.size()) maxI = a.size() - 1;

    cout << "m=" << minI << " n=" << maxI << endl;
}
//
// 17.8
//
void PrintMaxSumBest(vector<int> const& v) {
    int bestStart = -1;
    int bestEnd = -1;
    int bestSum = 0;
    int sum = 0;
    int leastNegativeItem = -1; // if v is all negative, best sum is this item

    for (size_t i=0; i < v.size(); ++i) {
        if (sum == 0) bestStart = i;
        sum += v[i];
        if ((v[i] < 0) && 
            (leastNegativeItem < 0 || v[leastNegativeItem] < v[i])) {
            leastNegativeItem = i;
        }
        if (bestSum < sum) {
            bestSum = sum;
            bestEnd = i;
        }
        else if (sum < 0) {
            sum = 0;
        }
    }
    if ((bestSum == 0) && (leastNegativeItem != -1)) {
        cout << "v contained all negative items. best sum =" 
             << v[leastNegativeItem] << endl;
    }
    else {
        cout << "BestSum=" << bestSum << " start=" << bestStart 
             << " end=" << bestEnd << endl;
    }
}
int _SumRange(vector<int> const& v, int start, int end) {
    int sum = 0;
    for (int i = start; i <= end; ++i) {
        sum += v[i];
    }
    return sum;
}

void PrintMaxSumNaive(vector<int> const& v) {
    int bestStart = -1;
    int bestEnd = -1;
    int bestSum = INT_MIN;

    for (int i = 0; i < v.size(); ++i) {
        for (int j = i; j >= 0; --j) {
            int sum = _SumRange(v, j, i);
            if (sum > bestSum) {
                bestSum = sum;
                bestStart = j;
                bestEnd = i;
            }
        }
    }

    cout << "BestSum=" << bestSum << " start=" << bestStart << " end=" << bestEnd << endl;
}

//
// 17.9
// 
map<string, int> ft;
void Trim(string& w) {
}

void SetupFrequencyTable(vector<string>& book) {
    for (int i = 0; i < book.size(); ++i) {
        string word(book[i]);
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        Trim(word);
        ft[word]++;
    }
}

int LookupWord(string& w) {
    if (w.empty()) return -1;
    if (ft.empty()) return -1;

    string lookup(w);
    std::transform(w.begin(), w.end(), lookup.begin(), ::tolower);
    Trim(lookup);

    map<string, int>::iterator iter = ft.find(lookup);
    if (iter == ft.end()) {
        return 0;
    }
    else {
        return ft[lookup];
    }
}

//
// 17.12
//
// This is order N if there are no duplicates. If there are duplicates
// then it goes up linearly by a factor related to the number of duplicates
void CorrectWithoutDuplicateLogic_PrintPairSum_O_N_withHash(vector<int>& v, int sum) {
    unordered_map<int, int> hm;
    for (int i = 0; i < v.size(); ++i) {
        int complement = sum - v[i]; // can overflow. Be ready to address that
        unordered_map<int, int>::iterator it = hm.find(complement);
        if (it != hm.end()) {
            int duplicates = it->second;
            while (duplicates > 0) {
                cout << "{" << v[i] << "," << complement << "}" << endl;
                duplicates--;
            }
        }
        hm[v[i]]++;
    }
}
//
// if we need to print duplicates for the numbers, we would need to do a a 
// binary search on the remaining right hand side modified to take a hash set
// for items already found
//
void Correct_PrintPairSum_O_NLogN_InPlace_NoDuplicates(int a[], int len, int sum) {
    // sort the array nlogn
    _mergesort(a, 0, len-1);

    int start = 0;
    int end = len - 1;

    while (start < end) {
        int pairSum = a[start] + a[end];

        if (sum == pairSum) {
            cout << "{" << a[start] << "," << a[end] << "}" << endl;
            start++;
            end--;
        }
        else if (pairSum < sum) {
            start++;
        }
        else {
            end--;
        }
    }
}

int ModifiedBinSearch(int a[], int target, int start, int last) {
 
    if (start > last) return false;

    int mid = (start + last)/2;
    if (a[mid] == target) {
        // check immediate left and right for all dupes. Note that all dupes
        // of target MUST be bounded by start and last (proof - if this was 
        // not true, there was a dupe of target at start-1 or last+1. But
        // start-1 / last+1 was the mid in the the previous recursion stack 
        // and so we would have found it already so that cannot be true. Proof by
        // contradiction.
        int count = 1; 
        int left = mid - 1;
        int right = mid + 1;
        while (left >= start) {
            if (a[left]==target)  {
                count++;
            }
            left--;
        }
        while (right <= last) {
            if (a[right]==target) {
                count++;
            }
            right++;
        }
        return count;
    }
    else if (target < a[mid]) 
    {
        return ModifiedBinSearch(a, target, start, mid-1);
    }
    else {
        return ModifiedBinSearch(a, target, mid+1, last);
    }
}

void WorksButNah_PrintPairSum_O_NLogN_InPlace_HandlesDuplicates(
    int a[], int len, int sum) {
    
    // sort the array nlogn
    _mergesort(a, 0, len-1);

    for (int i = 0; i < len; ++i) {
        int complement = sum - a[i];
        int complements_count = ModifiedBinSearch(a, complement, i+1, len-1);
        for (int j = 1; j <=complements_count; ++j) {
            cout << "{" << a[i] << "," << complement << "}" << endl;
        }
    }
}

//
// 17.13
//
struct BiNode {
    BiNode* node1;
    BiNode* node2;
    int data;

    BiNode(int data):data(data), node1(nullptr), node2(nullptr) {}

    void Print() {
        _PrintInOrder();
        cout << endl;
    }

    static BiNode* MakeFromSortedArray(int a[], int first, int last) {
        if (first > last) return nullptr;

        int mid = (first + last)/2;
        BiNode* root = new BiNode(a[mid]);
        root->node1 = MakeFromSortedArray(a, first, mid-1);
        root->node2 = MakeFromSortedArray(a, mid+1, last);
        return root;
    }

private:
    void _PrintInOrder() {
        if (node1) node1->_PrintInOrder();
        cout << data << " " ;
        if (node2) node2->_PrintInOrder();
    }
};

void _PrintAsList(BiNode* first, BiNode* last) {
    cout << "List Forward:" << endl;
    while (first) {
        cout << first->data << " ";
        first = first->node2;
    }
    cout << endl;

    cout << "List Backward:" << endl;
    while (last) {
        cout << last->data << " ";
        last = last->node1;
    }
    cout << endl;
}

void BST2DLL(BiNode* root, BiNode *& head, BiNode *& tail) {
    if (!root) return;

    BiNode* lh = nullptr, *lt = nullptr;
    BiNode* rh = nullptr, *rt = nullptr;
    BST2DLL(root->node1, lh, lt);
    BST2DLL(root->node2, rh, rt);

    if (lh) {
        head = lh; 
        lt->node2 = root; // join left list to head. 
        root->node1 = lt;
        tail = root;            // root is now the last element
    }

    if (!head) { // left list was empty
        head = root;
        tail = root;
    }

    if (rh) {
        tail->node2 = rh;
        rh->node1 = tail;
        tail = rt;
    }
    return;
}

BiNode* DLL2BST(BiNode *& list, int start, int last) {
    if (start > last) return nullptr;

    int mid = (start+last)/2;
    BiNode* left = DLL2BST(list, start, mid-1);
    
    BiNode* root = list;
    root->node1 = left;
    list = list->node2;
    BiNode* right = DLL2BST(list, mid+1, last);
    
    root->node2 = right;
    return root;
}



        




