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

void PrintJumps(HRESULT hr, list<int> const& lst) {
    cout << "PATH_EXISTS=" << (SUCCEEDED(hr) ? "Yes" : "No") << endl;
    cout << "#Jumps=" << lst.size()-1 << endl;
    for (int i : lst) {
        cout << i << " ";
    }
    cout << endl;
}
typedef vector<vector<int>> IntTable2D;
typedef vector<vector<bool>> BoolTable2D;

template <typename t>
void Print(char* tag, vector<t> const& items) {
    cout << tag << ": ";
    for (t const& i : items) {
        cout << i << " ";
    }
    cout << endl;
}

template <typename t>
void Print(char* tag, vector<int> const& indexes, vector<t> const& indexed) {
    cout << tag << ": ";
    for (int i : indexes) {
        cout << indexed[i] << " ";
    }
    cout << endl;
}