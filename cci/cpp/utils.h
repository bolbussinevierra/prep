#pragma once
typedef vector<vector<int>> matrix;
struct Rect { 
    int t; 
    int b; 
    int l; 
    int r; 
};

struct rect2 { 
    int height; 
    int left_col; 
    int right_col; 
    int Area() { return height*(right_col-left_col+1); }
    void Print() {
        cout << "[area=" << Area() 
             <<  " h=" << height 
             << " r=" << right_col << " l=" << left_col << "]"
             <<  endl;
    }
};
