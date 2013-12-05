#include <iostream>
#include <assert.h>

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



