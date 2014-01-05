#pragma once
typedef vector<vector<int>> matrix;
struct Rect { 
    int t; 
    int b; 
    int l; 
    int r; 
    void Print() {
        cout << "[area=" << (b-t)*(r-l) << 
               " r=" << r << " l=" << l << 
               " t=" << t << " b=" << b << 
               endl;
    }
};