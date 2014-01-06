#pragma once
typedef vector<vector<int>> matrix;
struct Rect { 
    int t; 
    int b; 
    int l; 
    int r; 
    int Area() { return (b-t+1)*(r-l+1); }
    void Print() {
        cout << "[area=" << Area() 
             << " t=" << t 
             << " b=" << b
             << " l=" << l
             << " r=" << r
             << "]"
             << endl;
    }
};
