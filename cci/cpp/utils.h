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

struct rect2 { 
    int height; 
    int left; 
    int right; 
    int Area() { return height*(right-left); }
    void Print() {
        cout << "[area=" << Area() << 
               " h=" << height <<
               " r=" << right << " l=" << left << 
               endl;
    }
};
