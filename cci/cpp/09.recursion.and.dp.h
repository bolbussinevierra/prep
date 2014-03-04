#pragma once

//
// 9.1
// DP runs in linear order! 
int steps[3] = {1, 2, 3};
int WaysDP(int n) {
    
    vi table(n+1, 0);
    table[0] = 1;

    for (int i = 1; i <= n; ++i) 
        for (int k = 0; k < AS(steps); ++k) // this is a constant factor (3)!
            if (i - steps[k] >= 0) 
                table[i] += table[i - steps[k]];

    return table[n];
}

/// INEFFICIENT!!! Needs to be memoized! better implementation is 
/// to do a bottom up recursive implementation of this 0(3N)
int WaysExponential(int n) {
    if (n < 0) {
        return 0;
    } 
    // This took a while to get why its true. Can also list ALL the base cases
    // instead of this. Read this is having been the "steps remaining equalled
    // the number of steps that were to be taken" hence 0
    else if (n == 0) {
        return 1; 
    }
    else {
        return WaysExponential(n - 1) + WaysExponential(n - 2) + WaysExponential(n - 3);
    }
}

//
// 9.2
//
int compute_paths(int width, int height) {
    // BTB - ** IMPORTANT **
    // [0][0] is not involved in the math which is why we allocate width+1
    // height+1
    vector<vi> result(width+1, vi(height+1));

    // initialize [1,0] to [width,0] = 1
    for (int x = 1; x <= width; ++x) {
        result[x][0] = 1;
    }
    // initialize [0, 1] to [0, height,] to 1
    for (int y = 1; y <= height; ++y) {
        result[0][y] = 1;
    }

    // calculate all other values from adjacent values
    for (int x = 1; x <= width; ++x) {
        for (int y = 1; y <= height; ++y) {
            result[x][y] = result[x][y-1] + result[x-1][y];
        }
    }
    return result[width][height];
}

//
// 9.2 follow up
//
bool operator<(POINT const& a, POINT const& b){
    return (a.x < b.x) && (a.y < b.y);
}

bool CanMoveTo(int x, int y) {
    if ((x == 2) && (y <= 2)) { return false; } else { return true; }
}


//
// SEE OTHER.H VERSION FOR A BETTER VERSION OF THIS!!!
//
bool FindPathTo(int ex, int ey, vector<POINT>& path, map<POINT, bool>& cache) {
    POINT p = {ex, ey};
    bool success = false;

    std::map<POINT,bool>::iterator it = cache.find(p);
    if (cache.end() != it)
    {
        success = it->second;
    }
    else if ((ex == 0) && (ey == 0)) { // we have confirmed all the way back!
        success = true;
    }
    else {
        if ((ex >= 1) && CanMoveTo(ex-1, ey)) {
            success = FindPathTo(ex-1, ey, path, cache);
        }
        if (!success && (ey >= 1) && CanMoveTo(ex, ey-1)) {
            success = FindPathTo(ex, ey-1, path, cache);
        }
    }

    if (success) {
        printf("Next = (%d, %d)\n", p.x, p.y);
        path.push_back(p); // we have confirmed that this is not a dead end
    }
    cache.insert(pair<POINT, bool>(p, success));
    return success;
}

bool FindPathTo(int ex, int ey) {
    vector<POINT> path;
    map<POINT, bool> cache;
    return FindPathTo(ex, ey, path, cache);
}

//
// 9.3
//
int _MagicIndexUnique(vi const& v, int start, int end) {
    if (start > end) return -1;

    int mid = (start + end) / 2;

    if (v[mid] == mid) 
        return mid;
    else if (v[mid] > mid) 
        return _MagicIndexUnique(v, start, mid-1);
    else 
        return _MagicIndexUnique(v, mid+1, end);
}

int MagicIndexUnique(vi const& v) {
    return _MagicIndexUnique(v, 0, v.size() - 1);
}

int _MagicIndexDuplicates(vi const& v, int start, int end) {
    if (start > end) return -1;

    int mid = (start + end)/2;
 
    if (v[mid] == mid) 
        return mid;
    
    int left = _MagicIndexDuplicates(v, start, min(mid-1, v[mid]));
    if (left != -1) return left;

    int right = _MagicIndexDuplicates(v, max(mid+1, v[mid]), end);
    return right;
}

int MagicIndexDuplicates(vi const& v) {
    return _MagicIndexDuplicates(v, 0, v.size() - 1);
}

//
// 9.4
//
void Subsets(vi& items, int start, vector<vi>& sets) {
    if(start == items.size()){
        vi empty;
        sets.push_back(empty);
    } else {
        Subsets(items, start+1, sets); // get the rest of the sets
        int count_previous_sets = sets.size();
        for (int i = 0; i < count_previous_sets; ++i) {
            vi cloneSet(sets[i]); // clone the previous set
            cloneSet.push_back(items[start]);   // add the new item
            sets.push_back(cloneSet);           // add the expanded-clone set to list
        }
    }
}
void PrintSets(vector<vi>& sets) {
    for (vi const& set : sets) {
        if (set.empty()) 
            cout << "<empty> ";
        else 
            for_each (set.begin(), set.end(), [](int n) { cout << n << " "; });
            
        cout << endl;
    }
}

void MapBinaryToSet(int binSet, vi& items, vi& set) {
    for (size_t i = 0; i < items.size(); ++i) {
        if ((1 << i) & binSet) {
            set.push_back(items[i]);
        }
    }
}

void SubsetsBinary(vi& items, vector<vi>& sets) {
    assert(32 >= items.size()); // limited by size of integer .. can use long (or long ass int array)
    int maxSets = (1 << items.size());  // 2^(n)

    for (int i = 0; i < maxSets; ++i) {
        vi newSet; // empty set added when i == 0 (empty newSet)
        MapBinaryToSet(i, items, newSet);
        sets.push_back(newSet);
    }
}

namespace epi_5 {    
    // generate a powerset using binary approaches and otherwise
    typedef unsigned long long ull;
    void SubsetsBinary(vector<int> const& set) {
        ull powerset_size = (1ULL << set.size());
        for (ull i = 0; i < powerset_size; ++i) {
            ull set_mask = i;
            while (set_mask) {
                // isolate the 1-LSB (all other bits are zeroed)
                ull lsb = set_mask & ~(set_mask - 1);
                // get the index of the bit
                int idx = 0;
                ull lsb_shift = (lsb >> 1);
                while (lsb_shift) {
                    lsb_shift >>= 1;
                    idx++;
                }
                assert(idx == Log2(lsb));

                // print the value
                cout << set[idx];
                
                // clear the least significant bit that we just processed
                set_mask &= (set_mask - 1);

                // if there are still 1 bits remaining ...
                if (set_mask)
                    cout << " ";
            }
            cout << endl;
        }
        printf("Items=[%d], Subsets=[%d]\n", set.size(), powerset_size);
    }

    
    void _SubsetRecursive(vector<int> const& v, int idx, vector<int>& subset)
    {
        if (!subset.empty()) 
            for_each(subset.begin(), subset.end(), [](int n){ cout << n << " "; });
        if (!subset.empty()) cout << endl;
            
        for (int i = idx; i < v.size(); ++i) {
            subset.push_back(v[i]);
            _SubsetRecursive(v, i+1, subset);
            subset.pop_back();
        }
    }
    // generate a powerset using recursion
    void SubsetRecursive(vector<int> const& v) {
        vector<int> subset;
        return _SubsetRecursive(v, 0, subset);
    }
}

void SubsetsBinary(int arr[], int length) {
    vi items(arr, arr+length);
    vector<vi> sets;
    SubsetsBinary(items, sets);
    PrintSets(sets);
    printf("Items=[%d], Subsets=[%d]\n", length, sets.size());
}

void SubsetsIterative(int arr[], int length) {
    vector<vi> sets;
    vi empty;
    sets.push_back(empty);
    
    for (int i = 0; i < length; ++i) {
        size_t existingSets = sets.size();
        for (size_t v = 0; v < existingSets; ++v) {
            vi newSet(sets[v]);
            newSet.push_back(arr[i]);
            sets.push_back(newSet);
        }
    }

    PrintSets(sets);
    printf("Items=[%d], Subsets=[%d]\n", length, sets.size());
}

void Subsets(int arr[], int length) {
    vi items(arr, arr+length);
    vector<vi> sets;
    Subsets(items, 0, sets);
    PrintSets(sets);
    printf("Items=[%d], Subsets=[%d]\n", length, sets.size());
}

//
// 9.5
//
void Combine(string& s, char c, int at, string& out) {
    size_t from = 0;
    size_t to = 0;
    while (to < s.size() + 1) {
        if (to == at) {
            out[to++] = c;
        }
        else {
            out[to++] = s[from++];
        }
    }
}

void Expand(string& s, char c, vector<string>& out) {
    size_t newLen = s.size() + 1;
    for (size_t at = 0; at < newLen; ++at) {
        string newS;
        newS.resize(newLen);
        Combine(s, c, at, newS);
        out.push_back(newS);
    }
}

void GetPermutations(string& s, size_t start, vector<string>& perms){
    assert(start < s.length());
    if (start == s.length() - 1) {
        string newP;
        newP.push_back(s[start]);
        perms.push_back(newP);
    }
    else {
        vector<string> otherPerms;
        GetPermutations(s, start+1, otherPerms);
        for (string& previous_string : otherPerms) {
            Expand(previous_string, s[start], perms);
        }
    }
}

void GetPermutationsIter(string& s, vector<string>& out) {
    for(size_t start=0; start < s.size(); ++start) {
        if (start == 0) {
            string newP;
            newP.push_back(s[start]);
            out.push_back(newP);
        }
        else {
            vector<string> newPerms;
            for (size_t i=0; i < out.size(); ++i) {
                Expand(out[i], s[start], newPerms);
            }
            out.swap(newPerms);
        }
    }
}

void GetPermutations(string& s) {
    vector<string> perms;
    GetPermutations(s, 0, perms);
    PrintVector(perms, "Permutations");
}

void GetPermutationsIter(string& s) {
    vector<string> perms;
    GetPermutationsIter(s, perms);
    PrintVector(perms, "Permutations");
}

//
// 9.6
//

struct trace {
    int _depth;
    const char * _title;
    int _lr;
    int _rr;
    const char * _s;
    int _ct;
    void print() {
        printf("depth:%d, title=%s | lr=%d, rr=%d, ct=%d, s=%s \n",
            _depth, _title, _lr, _rr, _ct, _s);
    }
    void set(int depth, char* title, int lr, int rr, int ct, const char*s){
        _depth = depth;
        _title = title;
        _lr = lr;
        _rr=rr;
        _ct = ct;
        _s = s;
    }
};

int combo_num = 0;
void PrintParen(int leftRem, int rightRem, string& str, int count) {             
    if (leftRem == 0 && rightRem == 0) {
        printf("%d:%s \n", ++combo_num, str.c_str());
    }
    else {
        if (leftRem > 0) {
            str[count] = '(';
            PrintParen(leftRem-1, rightRem, str, count+1);
        }
        if (rightRem > leftRem) {
            str[count] = ')';
            PrintParen(leftRem, rightRem-1, str, count+1);
        }
    }
}

void PrintParens(int count) {
    string str;
    str.resize(count*2);
    combo_num = 0;
    PrintParen(count, count, str, 0);
}

//
// 9.7
//
bool PaintFill(
    int ** screen, int width, int height, int x, int y, int oColor, int nColor) {
    if (x >= width || y >= height || x < 0 || y < 0) return false;
    int color = screen[x][y];
    if (color == oColor) {
        screen[x][y] = nColor;
        PaintFill(screen, width, height, x+1, y, oColor, nColor);
        PaintFill(screen, width, height, x-1, y, oColor, nColor);
        PaintFill(screen, width, height, x, y-1, oColor, nColor);
        PaintFill(screen, width, height, x, y+1, oColor, nColor);
    }
    return true;
}

//
// 9.8
//
int CountWaysToMakeChangeDP_SpaceOptimized(int n, vi const& coins)
{
    // in this case, we take each coin in turn and add to all cells that are less
    // than the value of the coin. Needs only O(N) space
    vi table(n+1, 0);
    table[0] = 1;
    for (int m = 0; m < coins.size(); ++m)
        for (int k=coins[m]; k <= n; ++k)
            table[k] += table[k-coins[m]];
                
    return table[n];
}

int CountWaysToMakeChangeDP(int n, vi const& coins) {
    //
    // We can build DP based on the counting classes:
    // ways = ways that include coin m + ways that dont include coin m
    //
    vvi table(n+1, vi(coins.size(), 0));

    // initialize
    for (int m = 0; m < coins.size(); ++m)
        table[0][m] = 1; // there 1 way is no change

    for (int i = 1; i <= n; ++i) {
        for (int m = 0; m < coins.size(); ++m) {
            int include_coin = (i - coins[m] >= 0) ? table[i-coins[m]][m] : 0;
            int exclude_coin = (m > 0) ? table[i][m-1] : 0;

            table[i][m] = include_coin + exclude_coin;
        }
    }
    return table[n][coins.size() - 1];
}

int _CountWaysToMakeChangeMemoized(int n, vi const& coins, 
                               int denom_index, vvi& cache) {
    if (denom_index == 0) // lowest value coin
        return 1;

    if (cache[n][denom_index] != -1) {
        // cout << n << ":" << coins[denom_index] << " from cache" << endl;
        return cache[n][denom_index];
    }
    
    int ways = 0;    
    for (int i = 0; coins[denom_index]*i <= n; ++i) 
        ways += _CountWaysToMakeChangeMemoized(n - i*coins[denom_index], coins,
                                            denom_index-1, cache);
    
    cache[n][denom_index] = ways;
    return ways;
}

int CountWaysToMakeChangeMemoized(int n, vi const& coins) {
    vvi cache(n+1, vi(coins.size(), -1));
    return _CountWaysToMakeChangeMemoized(n, coins, coins.size()-1, cache);
}

// tabout(indent); cout << " and " << n << " in 1s" << endl;
// if (denom != 1) tabout(indent); cout << " " << i*denom << " in " << denom;
// pre-ample - try to calculate the WAYS to make change. Note that if we did 
// this exactly how we count the ways to go up steps it would not work because
// it double counts combinations of change we consider the same. For example
// 1penny, 1 nickel is exactly the same as 1 nickel and I penny - this are not two
// ways to make change but rather just one way to make change. However if we were talking
// about going up the stairs (5 steps and then 1 step) would indeed be different from
// (1 step and then 5 steps)
int CountWaysToMakeChangeBroken(int n) {
    if (n < 0) {
        return 0;
    }
    else if (n == 0) {
        return 1;
    }
    else {
        return CountWaysToMakeChangeBroken(n - 25) + 
               CountWaysToMakeChangeBroken(n - 10) +
               CountWaysToMakeChangeBroken(n - 5) + 
               CountWaysToMakeChangeBroken(n - 1);
    }
}
//
// 9.9
//

bool _IsSafe(vi& row_set, int row, int col) {
    // check all the left columns to see if they have a queen on the same
    // row
    for (int col_prev = 0; col_prev < col; ++col_prev) {
        int row_in_col_prev = row_set[col_prev];
        if (row_in_col_prev == row) 
            return false;

        // check the diagnonals. If the distance between the columns 
        // equals the distance of rows (comparing existing queens with
        // the current protential queen)
        int dist_row = abs(row_in_col_prev - row);
        int dist_col = col - col_prev;
        if (dist_col == dist_row) 
            return false;
    }
    return true;
}

// rows[k] = i, means in column K, queen is at row i 
bool SolveQueensColByCol(vi& row_set, int col) {
    if (col >= row_set.size())
        return true;

    // consider this column and try placing this queen in all rows
    // of the column one by one
    for (int row = 0; row < row_set.size(); ++row) {
        if(_IsSafe(row_set, row, col)) {
            row_set[col] = row;    // place queen at this row in this col

            // recur and see if this leads to a solution
            if (SolveQueensColByCol(row_set, col+1))
                return true;

            // back track
            row_set[col] = 0;
        }
    }
    // no solution found at this level
    return false;
}

void DrawBoard(vi& row_set) {
    int n = row_set.size();
    for (int i = n-1; i >= 0; --i) { 
        for (int k = 0; k < n; ++k) {
            if (row_set[k] == i) {
                cout << setw(2) << "Q" ;
            }
            else {
                cout << setw(2) << "_";
            }
        }
        cout << endl;
    }
}

typedef unordered_map<string, int> CountCache;
//
// 9.10
// 
// let f(expr, result, s, e) be the count of ways to parenthesize expr
// starting at position s and ending at position e such that it evaluates
// to result
int _f(string const& expr, bool result, int s, int e, CountCache& cache) {
    string key = "s:" + to_string(s) + "e:" + to_string(e) + "r:" + to_string(result);
    if (cache.find(key) != cache.end())
        return cache[key];

    // are we at the end? Note that we would always end (and start) with a literal
    // in a properfly formed epxression
    if (s == e) {
        if ((expr[s] == '1' && result) ||
            (expr[s] == '0' && !result)) {
            return 1;
        } 
        else {
            return 0;
        }
    }

    int c = 0;
    // look for the next operator. Note that operators have to be 2 characters
    // apart since we cannot have two operators next to each other
    if (result) {
        for (int i = s+1; i <= e; i += 2) {
            char op = expr[i];
            if (op == '&') {
                c += _f(expr, true, s, i-1, cache) * _f(expr, true, i+1, e, cache);
            }
            else if (op == '|') {
                c += _f(expr, true, s, i-1, cache) * _f(expr, true, i+1, e, cache);
                c += _f(expr, false, s, i-1, cache) * _f(expr, true, i+1, e, cache);
                c += _f(expr, true, s, i-1, cache) * _f(expr, false, i+1, e, cache);
            }
            else if (op == '^') {
                c += _f(expr, true, s, i-1, cache) * _f(expr, false, i+1, e, cache);
                c += _f(expr, false, s, i-1, cache) * _f(expr, true, i+1, e, cache);
            }
        }
    }
    else {
        for (int i = s+1; i <= e; i += 2) {
            char op = expr[i];
            if (op == '&') {
                c += _f(expr, false, s, i-1, cache) * _f(expr, false, i+1, e, cache);
                c += _f(expr, false, s, i-1, cache) * _f(expr, true, i+1, e, cache);
                c += _f(expr, true, s, i-1, cache) * _f(expr, false, i+1, e, cache);
            }
            else if (op == '|') {
                c += _f(expr, false, s, i-1, cache) * _f(expr, false, i+1, e, cache);
            }
            else if (op == '^') {
                c += _f(expr, true, s, i-1, cache) * _f(expr, true, i+1, e, cache);
                c += _f(expr, false, s, i-1, cache) * _f(expr, false, i+1, e, cache);
            }
        }
    }
    cache[key] = c;
    return c;
}

int f(string const& expr, bool result, int s, int e) {
    CountCache cache;
    return _f(expr, result, s, e, cache);
}

namespace epi_15 {
template <typename T>
int Merge(vector<T>& A, int start, int mid, int end) {
    vector<T> sorted_A;
    int left_start = start, right_start = mid, inver_count = 0;

    while (left_start < mid && right_start < end) {
        if (A[left_start] <= A[right_start]) {
            sorted_A.emplace_back(A[left_start++]);
        } else {
            // A[left_start:mid - 1] will be the inversions
            inver_count += mid - left_start;
            sorted_A.emplace_back(A[right_start++]);
        }
    }
    copy(A.begin() + left_start,  A.begin() + mid, back_inserter(sorted_A));
    copy(A.begin() + right_start, A.begin() + end, back_inserter(sorted_A));

    // Updated A with sorted_A
    copy(sorted_A.begin(), sorted_A.end(), A.begin() + start);
    return inver_count;
}

template <typename T>
int CountInversionsHelper(vector<T>& A, int start, int end) {
    if (end - start <= 1) {
        return 0;
    }

    int mid = start + ((end - start) >> 1);
    return CountInversionsHelper(A, start, mid) +
           CountInversionsHelper(A, mid, end) + Merge(A, start, mid, end);
}
template <typename T>
int CountInversions(vector<T> A) {
    return CountInversionsHelper(A, 0, A.size());
}

}