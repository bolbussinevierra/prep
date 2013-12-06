#include <iostream>
#include <assert.h>
#include <algorithm>
#include <string>

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
// then it goes up by a factor related to the number of duplicates
void PrintPairSum_O_N_withHash(vector<int>& v, int sum) {
    map<int, int> hm;
    for (int i = 0; i < v.size(); ++i) {
        int complement = sum - v[i]; // this can overflow. Be ready to address that
        map<int, int>::iterator it = hm.find(complement);
        if (it != hm.end()) {
            int duplicates = it->second;
            while (duplicates > 0) {
                cout << "{ " << v[i] << "," << complement << "}" << endl;
                duplicates--;
            }
        }
        hm[v[i]]++;
    }
}

        




