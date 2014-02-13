#pragma once

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

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<vector<bool>> vvbool;
typedef vector<vector<char>> vvc;
typedef pair<int, int> Point;
typedef pair<double, double> DoublePoint;


template <typename t>
void Print(char* tag, vector<t> const& items) {
    cout << tag << ": ";
    for (t const& i : items) {
        cout << i << " ";
    }
    cout << endl;
}

template <typename t>
void Print(char* tag, vi const& indexes, vector<t> const& indexed) {
    cout << tag << ": ";
    for (int i : indexes) {
        cout << indexed[i] << " ";
    }
    cout << endl;
}

template <class T>
void _swap(T* a, T* b) {
    T temp = *a;
    *a = *b;
    *b = temp;
}

template <typename t, size_t dim_cols>
void Make2DVector(t array[][dim_cols], size_t rows, size_t cols, vector<vector<t>>& grid){
    vector<vector<t>> grid_local(rows, vector<t>(cols));
    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            grid_local[row][col] = array[row][col];
        }
    }
    grid_local.swap(grid);
}

struct PrintScope {
    int indent;
    char* message;
    char* opt;
    static void _print_indent(int indent) {
        for (int i = 0; i < indent; ++i) {
            cout << " ";
        }
    }
    PrintScope(int indent, char*message, char* opt=" "):indent(indent),message(message), opt(opt) {
        _print_indent(indent);
        cout << "Entering " << message;
        if (!isspace(opt[0])) {
            cout << opt ;
        } 
        cout << endl;
    }
    ~PrintScope() {
        _print_indent(indent);
        cout << "Leaving " << message;
        if (!isspace(opt[0])) {
            cout << opt ;
        } 
        cout << endl;
    }

    static void PrintRecursionTree(int indent, int f, int l) {
        _print_indent(indent);
        cout << "f=" << f << " l=" << l << endl;
    }
};


/*
    DECLARATIONS
*/
void tabout(int value);
void Print(Point const& p); 
void _P(int a[], int len_a, char* title);
void _P(int a[], int len_a);
void rotate(int a[], int len, int rot_count);
void PrintVector(vector<string>& p, char* title);
int Min3(int a, int b, int c); 
int Log2(unsigned long long val);