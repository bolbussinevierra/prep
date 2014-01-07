#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <hash_set>
#include "utils.h"

#pragma once
using namespace std;

struct Item {
    int weight;
    int value;
};
/*
Recreate the decisions made for the knapsack 01 problem
*/
void PrintKnapsack(
    int C, 
    vector<vector<int>> const& dp,
    vector<Item> const& items) 
{        
    cout << "Printing Optimal Knapsack:" << endl;
    int c = C, i = items.size();
    while(c > 0 && i > 0) {
        if (dp[c][i] != dp[c][i-1]) {
            cout << "{w: " << items[i-1].weight <<", v:" 
                    << items[i-1].value << "} ";
            c -= items[i-1].weight;
        }
        i--;
    }
}


/*
    Solves the 0-1 Knapsack problem, no repeats
*/
void Knapsack0_1NoRepeats(int C, vector<Item> const& items) {
    vector<vector<int>> dp(C+1, vector<int>(items.size()+1));
    for (int c = 0; c <= C; ++c) {
        for (int i = 0; i <= items.size(); ++i) {
            if (c == 0 || i == 0) {
                dp[c][i] = 0;
            }
            else {
                if (items[i-1].weight > c) {
                    dp[c][i] = dp[c][i-1];
                }
                else {
                    dp[c][i] = max(dp[c-items[i-1].weight][i-1]+items[i-1].value,
                                  dp[c][i-1]);

                }
            }
        }
    }
    cout << "Knapsack0_1NoRepeats(" << C << ")=" << dp[C][items.size()] << endl;
    PrintKnapsack(C, dp, items); cout << endl;
}
/*
Solves Knapsack problem with a dynamic problem allowing for duplicate
items
*/
void PrintKnapsack(int C, vector<int> const& R, vector<Item> const& items) {
    //for (int i = 0; i < R.size(); ++i) {
    //    cout << R[i] << " ";
    //}
    //cout << endl;

    if  (C == 0 || R[C] == INT_MIN) {
        cout << "Printing Optimal Knapsack:" << endl;
        return;
    }
    PrintKnapsack(C - items[R[C]].weight, R, items);
    cout << "{w:" << items[R[C]].weight << ", v:" << items[R[C]].value << "} ";
}
void KnapsackRepeats(int C, vector<Item> const& items) {
    vector<int> dp(C+1, 0); // DP table;
    vector<int> R(C+1, INT_MIN); // item picked for each C. So we can generate solution

    for (int c = 1; c <= C; ++c) {
        dp[c] = dp[c-1]; // Best value as at least this much if new items not added
        for (int i = 0; i < items.size(); ++i) {
            if (items[i].weight <= c) {
                int temp = dp[c - items[i].weight] + items[i].value;
                if (temp > dp[c]) {
                    dp[c] = temp;
                    R[c] = i;
                }
            }
        }
    }

    cout << "KnapsacksRepeats(" << C << ")=" << dp[C] << endl;
    PrintKnapsack(C, R, items); cout << endl;
}

void PrintSelection(int C, vector<int> const& R, vector<int> const& items) {
    if (C==0 || R[C] == -1) {
        cout << "Selected coins:\n";
    }
    else {
        PrintSelection(C-items[R[C]], R, items);
        cout << items[R[C]] << " ";
    }
}
/*
 -MAKING CHANGE-
*/
void MakingChangeLimitedCoins(
    int C, vector<int> const& coins, vector<int> const& limits) {

    assert(C >= 0);
    assert(coins.size() == limits.size());
    vector<bool> is_possible(C+1, false);
    vector<int> dp(C+1, -1);
    vector<int> R(C+1, -1); //record of coin used for weight each change sum
                            // so result can be reconstructed
    // need to track how many coins we have used up in getting to a particular
    // sum state. 
    vector<vector<int>> track(C+1, vector<int>(limits.size()));

    dp[0] = 0;
    is_possible[0] = true;
    track[0].assign(limits.begin(), limits.end());
    for (int c = 0; c <= C; ++c) {
        for (int i = 0; i < coins.size(); ++i) {
            if (is_possible[c]) {
                if (track[c][i] > 0 ) { // we have not used up all of i
                    int next_sum = c+coins[i];
                    if (next_sum <= C) {
                        is_possible[next_sum] = true;
                        if (-1 == dp[next_sum] ||
                            dp[c]+1 < dp[next_sum]) 
                        {
                            dp[next_sum] = dp[c]+1;
                            R[next_sum] = i;
                            track[next_sum].assign(track[c].begin(), track[c].end());
                            track[next_sum][i]--;
                        }
                    }
                }
            }
        }
    }
    if (is_possible[C]) {
        cout << "MakingChangeLimitedCoins(" << C << ")=" << dp[C] << endl;
        PrintSelection(C, R, coins); cout << endl;
    }
    else {
        cout << "MakingChangeLimitedCoins(" << C << ")=Not possible! \n";
    }
}

void MakingChangeInfiniteCoins(int C, vector<int> const& coins) {
    /*
    For us coins, the greedy algorithm always works (pick the biggest coin
    first and use that till you can't anymore and then move to the next)

    Also, coins always contain a denomination of 1 which guarantees that change
    can be made for any amount. However, here we implement a generic solution
    that does not assume change can be made since this might be useful for 
    other kinds of problems

    However, if we want a general solution that works on all kinds of
    denominations we need to use dynamic programming
    */
    assert(C >= 0);
    vector<bool> is_possible(C+1, false);
    vector<int> dp(C+1, -1);
    vector<int> R(C+1, -1); //record of coin used for weight each change sum
                            // so result can be reconstructed

    dp[0] = 0;
    is_possible[0] = true;
    for (int c = 0; c <= C; ++c) {
        for (int i = 0; i < coins.size(); ++i) {
            if (is_possible[c]) {
                if (c + coins[i] <= C) {
                    is_possible[c+coins[i]] = true;
                    if (-1 == dp[c+coins[i]] ||
                        dp[c]+1 < dp[c+coins[i]]) {
                            dp[c+coins[i]] = dp[c]+1;
                            R[c+coins[i]] = i;
                    }
                }
            }
        }
    }
    if (is_possible[C]) {
        cout << "MakingChangeInfiniteCoins(" << C << ")=" << dp[C] << endl;
        PrintSelection(C, R, coins); cout << endl;
    }
    else {
        cout << "MakingChangeInfiniteCoins(" << C << ")=Not possible! \n";
    }
}

/*
 -- BOX STACKING --
*/
struct Box {
    double h;
    double w;
    double l;
    double BaseArea() const { return w*l; }
    static bool Greater(Box const& a, Box const& b) {
        return a.BaseArea() > b.BaseArea();
    }

    void Print() const {
        cout << h << " x (" << w << " x " << l << ")\n";
    }
};
void AddRotations(vector<Box> const& in, vector<Box>& out) {
    out.reserve(in.size() * 3);
    for (int i = 0; i < in.size(); ++i) {
        out.push_back(in[i]);
        Box r;
        r.h = in[i].w;
        r.l = max(in[i].h, in[i].l);
        r.w = min(in[i].h, in[i].l);
        out.push_back(r);
        r.h = in[i].l;
        r.l = max(in[i].h, in[i].w);
        r.w = min(in[i].h, in[i].w);
        out.push_back(r);
    }
}
void PrintBoxStack(vector<int> const& prev, int bestEnd, vector<Box> const& b) {
    if (-1 == bestEnd) {
        return;
    }
    PrintBoxStack(prev, prev[bestEnd], b);
    b[bestEnd].Print();
}
void StackBoxes(vector<Box> const& b) {
    if (b.empty()) {
        cout << "Error! No boxes to stack \n";
        return;
    }

    vector<Box> rotB;
    AddRotations(b, rotB);

    // sort in decreasing order of base area. This guarantees all boxes that
    // *COULD* go ontop of a box at position i are at positions greater than i
    // Proof of this follows from contradiction: Assume that there is a box
    // that could go ontop of box at position i after sorting that occurs at 
    // a position less than i. Lets call this box J. That would mean box J
    // has a smaller w and l than box i. This would mean that it has a smaller
    // area than box i. However this contradicts that stated starting assumption
    // that both box i and j occur in order sorted in DECREASING order of area
    // where no box with a smaller area than box i can occur before it in the
    // order. QED
    std::sort(rotB.begin(), rotB.end(), Box::Greater);

    vector<double> dp(rotB.size()); 
    vector<int> prev(rotB.size(), -1);

    int bestEnd = -1;
    double maxSeen = 0;

    // Find the Longest Increasing Subsequence or a list of sorted in descending
    // order of base area
    for (int i = 0; i < rotB.size(); ++i) {
        dp[i] = rotB[i].h; // dp[i] is at least the height of the i-box in trivial case
        for (int j = i - 1; j >=0; --j) {
            if ((rotB[j].w > rotB[i].w) && 
                (rotB[j].l > rotB[i].l) &&
                (dp[j] + rotB[i].h > dp[i])) 
            {
                dp[i] = dp[j] + rotB[i].h;
                prev[i] = j;

                if (maxSeen < dp[i]) {
                    maxSeen = dp[i];
                    bestEnd = i;
                }
            }
        }
    }
    cout << "StackHeight=" << maxSeen << endl;
    PrintBoxStack(prev, bestEnd, rotB);
}
/*
 * LCS - LONGEST COMMON SUBSEQUENCE
 *
 */

template <class t>
void PrintLCS(
    vector<vector<int>> const& dp, 
    int i, int j, 
    vector<t> const& a,
    vector<t> const& b) 
{
    if (0 == i || 0 == j) {
        return;
    }
    else if (dp[i][j] == dp[i-1][j-1]+1 && a[i-1] == b[j-1]) {
        PrintLCS(dp, i-1, j-1, a, b);
        cout << a[i-1];     // note that d[p][..] corresponds to item a[p-1]
    }
    else if (dp[i][j] == dp[i-1][j]) {
        PrintLCS(dp, i-1, j, a, b);
    }
    else {
        PrintLCS(dp, i, j-1, a, b);
    }
}

template <class t>
int _LCS(vector<t> const& a, vector<t> const& b) {
    
    vector<vector<int>> dp (a.size()+1, vector<int>(b.size()+1));

    for (int i = 0; i <= a.size(); ++i) {
        for (int j = 0; j <= b.size(); ++j) {
            if (0 == i || 0 == j) {
                dp[i][j] = 0;
            }
            else if (a[i-1] == b[j-1]) {
                dp[i][j] = dp[i-1][j-1]+1;
            }
            else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    cout << "LCS=" << dp[a.size()][b.size()] << endl;
    cout << "LCS contains:\n";
    PrintLCS(dp, a.size(), b.size(), a, b);
    return dp[a.size()][b.size()];
}

/*
 *
 * EDIT DISTANCE
 *
 */
#define INSERT_COST 1
#define DELETE_COST 1
#define REPLACE_COST 1
int min3(int a, int b, int c) { return min(min(a, b), c); }

typedef vector<vector<int>> table2d_t;

void print_edit_guide(
    table2d_t const& t, 
    int i, 
    int j, 
    string const& a, 
    string const& b) 
{
    if (0==i || 0==j) {
        if (!(i == 0 && j == 0)) {
            
            int tmp = max(i, j);
            string start_msg = (i > j) ? "From a Delete[" : "Into a Insert[";
            string end_msg = (i > j) ? "]": "] from b";
            string const& c =  (i > j) ? a : b;
            string const& n = (tmp == i) ? "a" : "b";
            
            cout << start_msg;

            for (int k = 1; k <= tmp; ++k) {
                cout << c[k-1];
            }
            cout << end_msg << endl;
        }
    } 
    else if (a[i-1] == b[j-1]) {
        print_edit_guide(t, i-1, j-1, a, b);
        cout << "Match [" << a[i-1] << " with " << b[j-1] << "]\n";
    } 
    else if (t[i-1][j] + DELETE_COST == t[i][j]) {
        print_edit_guide(t, i-1, j, a, b);
        cout << "Delete [" << a[i-1] << " from a]\n";
    } 
    else if (t[i][j-1] + INSERT_COST == t[i][j]) {
        print_edit_guide(t, i, j-1, a, b);
        cout << "Insert [" << b[j-1] << " into a]\n";
    }
    else if (t[i-1][j-1] + REPLACE_COST == t[i][j]) {
        print_edit_guide(t, i-1, j-1, a, b);
        cout << "Replace [" << a[i-1] << " in a with " << b[j-1] << " from b]\n";
    }
}

int get_edit_distance(string const&a, string const&b) {
    cout << "a (len=" << a.size() << "): " << a.c_str() << endl;
    cout << "b (len=" << b.size() << "): " << b.c_str() << endl;
    table2d_t t(a.size()+1, vector<int>(b.size()+1));
    for (int i = 0; i <= a.size(); ++i) {
        for (int j = 0; j <= b.size(); ++j) {
            if (0==i || 0==j) {
                t[i][j] = max(i, j);
            }
            else if (a[i-1] == b[j-1]) { // note that t[i][..] corresponds to a[i-1]
                t[i][j] = t[i-1][j-1];
            }
            else {
                t[i][j] = min3(t[i-1][j] + DELETE_COST, // deleted last of a
                               t[i][j-1] + INSERT_COST, // inserted last of b into a
                               t[i-1][j-1] + REPLACE_COST); // moved last of b into a
            }
        }
    }
    cout << "edit_distance=" << t[a.size()][b.size()] << endl;
    print_edit_guide(t, a.size(), b.size(), a, b);
    return t[a.size()][b.size()];
}

/*
 BALANCED PARTITION
*/
typedef vector<vector<bool>> ss_table;
void print_s1(ss_table const& t, int bss, int bse, vector<int> const& a, 
              hash_set<int>& s1) 
{
    if (0 == bss || 0 == bse) {
        cout << "s1=\""; 
        return;
    }
    else if (t[bss][bse-1]) {
        print_s1(t, bss, bse-1, a, s1);
    }
    else if (bss >= a[bse-1] && t[bss-a[bse-1]][bse-1]) {
        print_s1(t, bss-a[bse-1], bse-1, a, s1);
        s1.insert(bse-1);
        cout << a[bse-1] << " ";
    }
    else {
        assert(false);
    }
}

int balanced_partition(vector<int> const& a) {
    int sum = accumulate(a.begin(), a.end(), 0);
    int half_sum = sum / 2;
    ss_table t(half_sum+1, vector<bool>(a.size()+1));

    for (int i = 1; i <= half_sum; ++i) t[i][0] = false; // exclude t[0][0] which is true
    for (int i= 0; i <= a.size(); ++i) t[0][i] = true;

    int best_subset_sum = 0;
    int best_subset_end = 0;

    for (int i = 1; i <= half_sum; ++i) {
        for (int j = 1; j <= a.size(); ++j) {
            t[i][j] = t[i][j-1] || (i >= a[j-1] ? t[i-a[j-1]][j-1] : false );
            if (t[i][j] && (best_subset_sum < i)) {
                best_subset_sum = i;
                best_subset_end = j;
            }
        }
    }
    int min_diff = sum-2*(best_subset_sum);
    cout << "minimized_difference=" << min_diff << endl;
    hash_set<int> s1;
    
    print_s1(t, best_subset_sum, best_subset_end, a, s1); 
    cout << "\"" << endl;

    cout << "s2=\"";
    for (int i = 0; i < a.size(); ++i) {
        if (s1.end() == s1.find(i)) {
            cout << a[i] << " ";
        }
    }
    cout << "\"" << endl;

    return min_diff;
}

void CloseAllOpenRectanglesHigherThan(unordered_map<int, Rect>& rectangles, int right, 
                                   Rect& max_rect, int height) {
                       
    // for any given row we have only one rectangle of the given height
    // of max area open at one time
    for(auto it = rectangles.begin(); it != rectangles.end(); ) {
        if (it->first > height) {
            Rect& rect = it->second;
            if (rect.r = -1)  {
                rect.r = right;
            }
            if (-1 == max_rect.t || rect.Area() > max_rect.Area()) {
                max_rect = rect;
            }
            it = rectangles.erase(it);
        }
        else {
            ++it;
        }
    }
}

void CloseAllOpenRectangles(unordered_map<int, Rect>& rectangles, int right, 
                          Rect& max_rect){
    return CloseAllOpenRectanglesHigherThan(rectangles, right, max_rect, 0);
}

/* Largest submatrix composed of all 1's */
// solution inspired by: http://stackoverflow.com/questions/7770945/largest-rectangular-sub-matrix-with-the-same-number
HRESULT LargestSubmatrixOfOnes(matrix const& v, Rect& result){
    // PARAM CHECK

    matrix t(v.size(), vector<int>(v[0].size()));

    // if v[i,j]=1, let t[i,j] represent the count of contigous 1's below (same column) t[i,j] upto 
    // and including it. so note that we are calculating bottom row up. if v[i,j]=0. then t[i,j]=0
    int const rows = v.size();
    int const cols = v[0].size();
    
    // bottom row is as it appears in v. The rest of the rows are calculated from those below
    // this step is O(N) where N is the number of entries in the matrix
    t[rows-1].assign(v[rows-1].begin(), v[rows-1].end());
    for (int row = rows - 2; row >= 0; --row) {
        for (int col = 0; col < cols; ++col) {
            if (1 == v[row][col]) {
                t[row][col] = t[row+1][col] + 1; // note that row below is (row+1)
            } 
            else {
                t[row][col] = 0;
            }
        }
    }
        
    // Next step is to process all the possible rectangles. We already know the heights from the above
    // not we need to find the possible widths.
    unordered_map<int, Rect> rectangles; 
    Rect max_rect = {-1};
    int final_col = cols-1;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int height = t[row][col];
            
            // we have run into a gap that cannot be expanded. 
            if (col > 0 && height == 0) {
                CloseAllOpenRectangles(rectangles, col-1, max_rect);
            }

            // if a rectangle of this height does not exist yet, create it
            // then close all open rectangles that are higher since we now
            // now they cannot share a base with the rectangle we just created.
            // Note that at the first column, we cannot have any open rectangles
            if (height > 0) {
                if (rectangles.find(height) == rectangles.end()) {
                    Rect new_rect = { row, row+height-1,col, -1 }; 
                    rectangles.insert(make_pair(height, new_rect));
                }
                int previous_col = col-1;
                if (previous_col >= 0) {
                    CloseAllOpenRectanglesHigherThan(rectangles, previous_col, max_rect, height);
                }
            }
        }
        // At the end of each row (i.e right=final_col) close, all open rectangles
        CloseAllOpenRectangles(rectangles, final_col, max_rect); 
    }
    result = max_rect;
    return S_OK;
}

int Min3(int a, int b, int c) { return min(min(a,b), c); }

void CheckMax(int size, int bottom, int right, Rect& max) {
    Rect rect = {bottom-size+1, bottom, right-size+1, right};
    if (-1 == max.t || rect.Area() > max.Area()) {
        max = rect;
    }
}

HRESULT LargestSquareSubmatrixOfOnes(matrix const& v, Rect& result) {
    int const k_rows = v.size();
    int const k_cols = v[0].size();
    matrix t(k_rows, vector<int>(k_cols));

    // copy first row and first col as is
    t[0].assign(v[0].begin(), v[0].end());
    for (int row = 0; row < k_rows; ++row) {
        t[row][0] = v[row][0];
    }

    Rect max_square = {-1};
    for (int row = 1; row < k_rows; ++row) {
        for (int col = 1; col < k_cols; ++col) {
            if (v[row][col] == 1) {
                t[row][col] = Min3(t[row-1][col], t[row][col-1], t[row-1][col-1]) + 1;
                CheckMax(t[row][col], row, col, max_square);
            }
            else {
                t[row][col] = 0;
            }
        }
    }
    result = max_square;
    return S_OK;
}
//
// MINIMUM JUMPS - GREEDY IS ACTUALLY BEST
//
HRESULT MinJumps_Greedy_Best_O_N(vector<int> const& v, list<int>& jumps) {
    if (v.empty()) return S_OK;
    if (v.size() == 1) {
        jumps.push_back(v[0]);
        return S_OK;
    }
    
    int current = 0;
    int final = v.size() - 1;
    jumps.push_back(0);
    int unseen_pos = 1; // allows us to not revisit any values we have already seen. Guarantees O(N)
    while (current + v[current] < final) { // if we cant reach end in one hop
        int max_reaching_child = current; // so we can tell if we were able to move forward
        int max_child_range = 0;
        int next_in_range = current + v[current];
        for (int next_child = unseen_pos; next_child <= next_in_range; ++next_child) {
            int child_range = next_child + v[next_child];
            if (child_range > max_child_range) {
                max_child_range = child_range;
                max_reaching_child = next_child;
            }
        }

        // still on the same end? dead end
        if (max_reaching_child == current) {
            jumps.clear();
            return E_FAIL;
        }
        // we no longer need to consider elements in previous range since we already picked the optimum
        // choice from that range
        unseen_pos = next_in_range + 1;
        current = max_reaching_child;
        jumps.push_back(current);
    }
    jumps.push_back(final);
    return S_OK;
}

HRESULT MinJumps_DP_NotIdeal_O_N2(vector<int> const& v, list<int>& jumps) {
    if (v.empty()) return S_OK;
    if (v.size() == 1) {
        jumps.push_back(v[0]);
        return S_OK;
    }
    
    // t[i] represents the fewest jumps needed to get to i
    vector<int> t(v.size(), INT_MAX);
    vector<int> prev(v.size(), -1);

    t[0] = 0;
    for (int i = 1; i < v.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (t[j] != INT_MAX) { // j is not already a dead-end
                if (i <= j+v[j] && t[i] > t[j] + 1) {
                    t[i] = t[j] + 1;
                    prev[i] = j;
                }
            }
        }
    }

    // check if a path exists
    int final = v.size() - 1;
    if (t[final] == INT_MAX) {
        return E_FAIL;
    }

    jumps.push_front(final);
    int p = prev[final];
    while (p != -1) {
        jumps.push_front(p);
        p = prev[p];
    }
    return S_OK;
}
