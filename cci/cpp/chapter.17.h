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
