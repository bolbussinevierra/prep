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

