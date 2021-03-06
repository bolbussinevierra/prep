#pragma once

struct Item {
    int weight;
    int value;
};
#pragma region print_solution
/*
Recreate the decisions made for the knapsack 01 problem
*/
void PrintKnapsack(int C, vvi const& table, vector<Item> const& items) {        
    cout << "Printing Optimal Knapsack:" << endl;
    int c = C, i = items.size();
    while(c > 0 && i > 0) {
        if (table[c][i] != table[c][i-1]) {
            cout << "{w: " << items[i-1].weight <<", v:" 
                    << items[i-1].value << "} ";
            c -= items[i-1].weight;
        }
        i--;
    }
}
#pragma endregion

/*
    Solves the 0-1 Knapsack problem, no repeats
    ---------------------------------------------
    Given weights and values of n items, put these items in a knapsack of capacity W 
    to get the maximum total value in the knapsack. In other words, given two integer 
    arrays val[0..n-1] and wt[0..n-1] which represent values and weights associated 
    with n items respectively. Also given an integer W which represents knapsack 
    capacity, find out the maximum value subset of val[] such that sum of the weights 
    of this subset is smaller than or equal to W. You cannot break an item, either pick
    the complete item, or don�t pick it (0-1 property).
*/
void Knapsack0_1NoRepeats(int C, vector<Item> const& items) {
    vvi table(C+1, vi(items.size()+1));
    for (int c = 0; c <= C; ++c) {
        for (int i = 0; i <= items.size(); ++i) {
            if (c == 0 || i == 0) {
                table[c][i] = 0;
            }
            else {
                if (items[i-1].weight > c)  // items are zero indexed (1st item at 0)
                    table[c][i] = table[c][i-1];
                else 
                    table[c][i] = max(table[c-items[i-1].weight][i-1]+items[i-1].value,
                                  table[c][i-1]);
            }
        }
    }
    cout << "Knapsack0_1NoRepeats(" << C << ")=" << table[C][items.size()] << endl;
    PrintKnapsack(C, table, items); cout << endl;
}
/*
Solves Knapsack problem via dp allowing for duplicate items
*/
#pragma region print_solution
void PrintKnapsack(int C, vi const& R, vector<Item> const& items) {
    if  (C == 0 || R[C] == numeric_limits<int>::min()) {
        cout << "Printing Optimal Knapsack:" << endl;
        return;
    }
    PrintKnapsack(C - items[R[C]].weight, R, items);
    cout << "{w:" << items[R[C]].weight << ", v:" << items[R[C]].value << "} ";
}
#pragma endregion

void KnapsackRepeats(int C, vector<Item> const& items) {
    vi table(C+1, 0); // DP table;
    vi R(C+1, numeric_limits<int>::min()); // item picked for each C. So we can generate solution

    for (int c = 1; c <= C; ++c) {
        table[c] = table[c-1]; // Best value as at least this much if new items not added
        for (int i = 0; i < items.size(); ++i) {
            if (items[i].weight <= c) {
                int temp = table[c - items[i].weight] + items[i].value;
                if (temp > table[c]) {
                    table[c] = temp;
                    R[c] = i;
                }
            }
        }
    }

    cout << "KnapsacksRepeats(" << C << ")=" << table[C] << endl;
    PrintKnapsack(C, R, items); cout << endl;
}
#pragma region print_solution
void PrintSelection(int C, vi const& R, vi const& items) {
    if (C==0 || R[C] == -1) {
        cout << "Selected coins:\n";
    }
    else {
        PrintSelection(C-items[R[C]], R, items);
        cout << items[R[C]] << " ";
    }
}
#pragma endregion

/************************************************************************************
 -MAKING CHANGE-
*/
void MakingChangeLimitedCoins(int C, vi const& coins, vi const& limits) {
    assert(C >= 0);
    assert(coins.size() == limits.size());
    vector<bool> is_possible(C+1, false);
    vi table(C+1, -1);
    vi R(C+1, -1); //record of coin used for weight each change sum
                            // so result can be reconstructed
    // need to track how many coins we have used up in getting to a particular
    // sum state. 
    vvi track(C+1, vi(limits.size()));

    table[0] = 0;
    is_possible[0] = true;
    track[0].assign(limits.begin(), limits.end());
    for (int c = 0; c <= C; ++c) {
        for (int i = 0; i < coins.size(); ++i) {
            if (is_possible[c]) {
                if (track[c][i] > 0 ) { // we have not used up all of i
                    int next_sum = c+coins[i];
                    if (next_sum <= C) {
                        is_possible[next_sum] = true;
                        if (-1 == table[next_sum] || table[c]+1 < table[next_sum]){
                            table[next_sum] = table[c]+1;
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
        cout << "MakingChangeLimitedCoins(" << C << ")=" << table[C] << endl;
        PrintSelection(C, R, coins); cout << endl;
    }
    else {
        cout << "MakingChangeLimitedCoins(" << C << ")=Not possible! \n";
    }
}
/*
 Given an infinite supply of coins of denomications 1 < v2 < v3 etc,
 Find the fewest number of coins needed to make change for an amout 
 */ 
void MakingChangeInfiniteCoins(int C, vi const& coins) {
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
    vector<bool> is_possible(C+1, false); // possible to make change for amount C
    vi table(C+1, -1); // fewest coins needed to make change for c
    vi R(C+1, -1); //record of coin used for weight each change sum
                            // so result can be reconstructed

    table[0] = 0;
    is_possible[0] = true;
    for (int c = 0; c <= C; ++c) {
        for (int i = 0; i < coins.size(); ++i) {
            if (is_possible[c]) {
                int next_sum = c + coins[i];
                if (next_sum <= C) {
                    is_possible[next_sum] = true;
                    if (-1 == table[next_sum] || table[c]+1 < table[next_sum]) {
                            table[next_sum] = table[c]+1;
                            R[next_sum] = i;
                    }
                }
            }
        }
    }
    if (is_possible[C]) {
        cout << "MakingChangeInfiniteCoins(" << C << ")=" << table[C] << endl;
        PrintSelection(C, R, coins); cout << endl;
    }
    else {
        cout << "MakingChangeInfiniteCoins(" << C << ")=Not possible! \n";
    }
}
/*************************************************************************************
 -- BOX STACKING --
 You are given a set of n types of rectangular 3-D boxes, where the i^th box has 
 height h(i), width w(i) and depth d(i) (all real numbers). You want to create a stack
 of boxes which is as tall as possible, but you can only stack a box on top of another
 box if the dimensions of the 2-D base of the lower box are each strictly larger than 
 those of the 2-D base of the higher box. Of course, you can rotate a box so that any 
 side functions as its base. It is also allowable to use multiple instances of the same
 type of box.
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

    bool CanPutUnder(Box const& top) {
        return w > top.w && l > top.l;
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
#pragma region print_solution
void PrintBoxStack(vi const& prev, int bestEnd, vector<Box> const& b) {
    if (-1 == bestEnd) {
        return;
    }
    PrintBoxStack(prev, prev[bestEnd], b);
    b[bestEnd].Print();
}
#pragma endregion

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

    vector<double> table(rotB.size()); 
    vi prev(rotB.size(), -1);

    int bestEnd = -1;
    double maxSeen = 0;

    // Find the Longest Increasing Subsequence or a list of sorted in descending
    // order of base area
    for (int i = 0; i < rotB.size(); ++i) {
        table[i] = rotB[i].h; // table[i] is at least the height of the i-box in trivial case
        for (int j = i - 1; j >=0; --j) {
            if (rotB[j].CanPutUnder(rotB[i]) &&
                (table[j] + rotB[i].h > table[i]))
            {
                table[i] = table[j] + rotB[i].h;
                prev[i] = j;

                if (maxSeen < table[i]) {
                    maxSeen = table[i];
                    bestEnd = i;
                }
            }
        }
    }
    cout << "StackHeight=" << maxSeen << endl;
    PrintBoxStack(prev, bestEnd, rotB);
}
/*************************************************************************************
 * LCS - LONGEST COMMON SUBSEQUENCE
 * ---------------------------------
 * LCS Problem Statement: Given two sequences, find the length of longest subsequence 
 * present in both of them. A subsequence is a sequence that appears in the same relative 
 * order, but not necessarily contiguous. For example, �abc�, �abg�, �bdf�, �aeg�, 
 * ��acefg�, .. etc are subsequences of �abcdefg�. So a string of length n has 2^n 
 * different possible subsequences.
 */

template <class t>
void PrintLCS(vvi const& table, int i, int j, vector<t> const& a, vector<t> const& b) {
    if (0 == i || 0 == j) {
        return;
    }
    else if (table[i][j] == table[i-1][j-1]+1 && a[i-1] == b[j-1]) {
        PrintLCS(table, i-1, j-1, a, b);
        cout << a[i-1];     // note that d[p][..] corresponds to item a[p-1]
    }
    else if (table[i][j] == table[i-1][j]) {
        PrintLCS(table, i-1, j, a, b);
    }
    else {
        PrintLCS(table, i, j-1, a, b);
    }
}

template <class t>
int _LCS(vector<t> const& a, vector<t> const& b) {
    
    vvi table(a.size()+1, vi(b.size()+1));

    for (int i = 0; i <= a.size(); ++i) {
        for (int j = 0; j <= b.size(); ++j) {
            if (0 == i || 0 == j) {
                table[i][j] = 0;
            }
            else if (a[i-1] == b[j-1]) {
                table[i][j] = table[i-1][j-1]+1;
            }
            else {
                table[i][j] = max(table[i-1][j], table[i][j-1]);
            }
        }
    }
    cout << "LCS=" << table[a.size()][b.size()] << endl;
    cout << "LCS contains:\n";
    PrintLCS(table, a.size(), b.size(), a, b);
    return table[a.size()][b.size()];
}
/*************************************************************************************
 *
 * EDIT DISTANCE
 * Problem: Given two strings of size m, n and set of operations replace (R), insert 
 * (I) and delete (D) all at equal cost. Find minimum number of edits (operations) 
 * required to convert one string into another.
 *
 */
#define INSERT_COST 1
#define DELETE_COST 1
#define REPLACE_COST 1
int min3(int a, int b, int c) { return min(min(a, b), c); }

void PrintEditGuide(vvi const& t, int i, int j, string const& a, string const& b){ 
    if (0==i || 0==j) {
        if (!(i == 0 && j == 0)) {
            
            int tmp = max(i, j);
            string start_msg = (i > j) ? "From a Delete[" : "Into a Insert[";
            string end_msg = (i > j) ? "]": "] from b";
            string const& c =  (i > j) ? a : b;
            
            cout << start_msg;

            for (int k = 1; k <= tmp; ++k) {
                cout << c[k-1];
            }
            cout << end_msg << endl;
        }
    } 
    else if (a[i-1] == b[j-1]) {
        PrintEditGuide(t, i-1, j-1, a, b);
        cout << "Match [" << a[i-1] << " with " << b[j-1] << "]\n";
    } 
    else if (t[i-1][j] + DELETE_COST == t[i][j]) {
        PrintEditGuide(t, i-1, j, a, b);
        cout << "Delete [" << a[i-1] << " from a]\n";
    } 
    else if (t[i][j-1] + INSERT_COST == t[i][j]) {
        PrintEditGuide(t, i, j-1, a, b);
        cout << "Insert [" << b[j-1] << " into a]\n";
    }
    else if (t[i-1][j-1] + REPLACE_COST == t[i][j]) {
        PrintEditGuide(t, i-1, j-1, a, b);
        cout << "Replace [" << a[i-1] << " in a with " << b[j-1] << " from b]\n";
    }
}

int GetEditDistance(string const&a, string const&b) {
    printf("a (len=%d): %s \n", a.size(), a.c_str());
    printf("b (len=%d): %s \n", b.size(), b.c_str());
    
    vvi t(a.size()+1, vi(b.size()+1));
    for (int i = 0; i <= a.size(); ++i) {
        for (int j = 0; j <= b.size(); ++j) {
            if (0==i || 0==j)
                t[i][j] = max(i, j);
            else if (a[i-1] == b[j-1]) // note that t[i][..] corresponds to a[i-1]
                t[i][j] = t[i-1][j-1];
            else 
                t[i][j] = min3(t[i-1][j] + DELETE_COST, // deleted last of a
                               t[i][j-1] + INSERT_COST, // inserted last of b into a
                               t[i-1][j-1] + REPLACE_COST); // replaced last of a with b
            
        }
    }
    cout << "edit_distance=" << t[a.size()][b.size()] << endl;
    PrintEditGuide(t, a.size(), b.size(), a, b);
    return t[a.size()][b.size()];
}
/*************************************************************************************
 BALANCED PARTITION
 ------------------
 Partition a set into two subsets such that the difference between sums of the two
 subsets is minimized
*/
void PrintS1(vvbool const& t, int bss, int bse, vi const& a, 
              hash_set<int>& s1) 
{
    if (0 == bss || 0 == bse) {
        cout << "s1=\""; 
        return;
    }
    else if (t[bss][bse-1])
        PrintS1(t, bss, bse-1, a, s1);
    else if (bss >= a[bse-1] && t[bss-a[bse-1]][bse-1]) {
        PrintS1(t, bss-a[bse-1], bse-1, a, s1);
        s1.insert(bse-1);
        cout << a[bse-1] << " ";
    }
    else
        assert(false);
}

int BalancedPartition(vi const& a) {
    int sum = accumulate(a.begin(), a.end(), 0);
    int half_sum = sum / 2;
    // t[i][j] is true if sum=i is possible considering the first j items
    vvbool t(half_sum+1, vector<bool>(a.size()+1));

    for (int i = 1; i <= half_sum; ++i) t[i][0] = false; // exclude t[0][0] which is true
    for (int i= 0; i <= a.size(); ++i) t[0][i] = true;

    int best_subset_sum = 0;
    int best_subset_end = 0;

    for (int i = 1; i <= half_sum; ++i) {
        for (int j = 1; j <= a.size(); ++j) {
            // dont include jth item, or include it (if its not too big)
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
    
    PrintS1(t, best_subset_sum, best_subset_end, a, s1); 
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
/*************************************************************************************
   LARGEST SUBMATRIX COMPOSED OF ALL 1's
   ---------------------------------------
   Given an M x N matrix of 0 and 1 find the largest submatrix (not neccesarily square)
   composed of all 1's
   solution inspired by: http://stackoverflow.com/questions/7770945/largest-rectangular-sub-matrix-with-the-same-number
*/
void CloseAllOpenRectanglesHigherThan(unordered_map<int, Rect>& rectangles, int right, 
                                   Rect& max_rect, int height) {
                       
    // for any given row we have only one rectangle of the given height
    // of max area open at one time
    for(auto it = rectangles.begin(); it != rectangles.end(); ) {
        if (it->first > height) {
            Rect& rect = it->second;
            if (rect.r == -1)  {
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

HRESULT LargestSubmatrixOfOnes(vvi const& v, Rect& result){

    vvi t(v.size(), vi(v[0].size()));

    // if v[i,j]=1, let t[i,j] represent the count of contigous 1's below (same column) t[i,j] upto 
    // and including it. so note that we are calculating bottom row up. if v[i,j]=0. then t[i,j]=0
    int const rows = v.size();
    int const cols = v[0].size();
    
    // bottom row is as it appears in v. The rest of the rows are calculated from those below
    // this step is O(N) where N is the number of entries in the matrix
    t[rows-1].assign(v[rows-1].begin(), v[rows-1].end());
    for (int row = rows - 2; row >= 0; --row) {
        for (int col = 0; col < cols; ++col) {
            if (1 == v[row][col]) 
                t[row][col] = t[row+1][col] + 1; // note that row below is (row+1)
            else 
                t[row][col] = 0;
        }
    }
        
    // Next step is to process all the possible rectangles. We already know the heights from the above
    // now we need to find the possible widths.
    unordered_map<int, Rect> rectangles; // we will only have 1 rectangle of a given height open at one time
    Rect max_rect = {-1};
    int final_col = cols-1;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int height = t[row][col];
            
            // we have run into a gap that cannot be expanded, resolve all the open
            // rectangles whose heights we now do know
            if (col > 0 && height == 0) 
                CloseAllOpenRectangles(rectangles, col-1, max_rect);
            
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
                if (previous_col >= 0) 
                    CloseAllOpenRectanglesHigherThan(rectangles, previous_col, max_rect, height);
            }
        }
        // At the end of each row (i.e right=final_col) close, all open rectangles
        CloseAllOpenRectangles(rectangles, final_col, max_rect); 
    }
    result = max_rect;
    return S_OK;
}
/**************************************************************************************
   LARGEST SQUARE SUBMATRIX COMPOSED OF ALL 1's
   ---------------------------------------
   Given an M x N matrix of 0 and 1 find the largest SQUARE submatrix composed of all 1's
*/
void CheckMax(int size, int bottom, int right, Rect& max) {
    Rect rect = {bottom-size+1, bottom, right-size+1, right};
    if (-1 == max.t || rect.Area() > max.Area()) {
        max = rect;
    }
}

HRESULT LargestSquareSubmatrixOfOnes(vvi const& v, Rect& result) {
    int const k_rows = v.size();
    int const k_cols = v[0].size();
    // t[i][j] is the size of the largest square of 1's whose bottom right corner
    // is v[i][j]
    vvi t(k_rows, vi(k_cols)); 

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
            else 
                t[row][col] = 0;
        }
    }
    result = max_square;
    return S_OK;
}
/*************************************************************************************
  MINIMUM JUMPS - GREEDY IS ACTUALLY BEST
  ---------------------------------------
  Given an array of integers where each element represents the max number of steps that
  can be made forward from that element. Write a function to return the minimum number
  of jumps to reach the end of the array (starting from the first element). If an element
  is 0, then cannot move through that element.
*/
HRESULT MinJumps_Greedy_Best_O_N(vi const& v, list<int>& jumps) {
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
        int max_child_range = 0; // largest reach we have seen a child offer
        int next_children_in_range = current + v[current]; // range of children we can cover in the next hop
        for (int next_child = unseen_pos; next_child <= next_children_in_range; ++next_child) {
            int child_range = next_child + v[next_child]; 
            if (child_range > max_child_range) {
                max_child_range = child_range;
                max_reaching_child = next_child;
            }
        }

        // if we have not moved, we have hit a dead end. we cannot proceed.
        if (max_reaching_child == current) {
            jumps.clear();
            return E_FAIL;
        }
        // we no longer need to consider elements in previous range since we already picked the optimum
        // choice from that range. This guarantees O(N) performance
        unseen_pos = next_children_in_range + 1; 
        current = max_reaching_child;
        jumps.push_back(current);
    }
    jumps.push_back(final);
    return S_OK;
}

HRESULT MinJumps_DP_NotIdeal_O_N2(vi const& v, list<int>& jumps) {
    if (v.empty()) return S_OK;
    if (v.size() == 1) {
        jumps.push_back(v[0]);
        return S_OK;
    }
    
    // t[i] represents the fewest jumps needed to get to i
    vi t(v.size(), numeric_limits<int>::max());
    vi prev(v.size(), -1);

    t[0] = 0;
    for (int i = 1; i < v.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (t[j] != numeric_limits<int>::max()) { // j is not already a dead-end
                if (i <= j+v[j] && t[i] > t[j] + 1) {
                    t[i] = t[j] + 1;
                    prev[i] = j;
                }
            }
        }
    }

    // check if a path exists
    int final = v.size() - 1;
    if (t[final] == numeric_limits<int>::max()) {
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
/************************************************************************************* 
 Longest Palindrome Subsequence 
 ------------------------------
 Given a sequence, find the length of the longest palindromic subsequence in it. For 
 example, if the given sequence is �BBABCBCAB�, then the output should be 7 as 
 �BABCBAB� is the longest palindromic subsequence in it. �BBBBB� and �BBCBB� are also 
 palindromic subsequences of the given sequence, but not the longest ones.
*/
#define CASE1 1
#define CASE2 2
#define CASE3 3
void _GetLPS(vvi const& back_trace, string const& s, string& lps) {
    int current = lps.size()-1;
    // get the last half of the palindrome (including the middle character if palindrome
    // is off odd size) from the backtrace table
    int i = 0, j = s.size() - 1;
    while (i <=j ) { 
        if (CASE1 == back_trace[i][j]) {
            lps[current--] = s[i];
            i++;
            j--;
        }
        else if (CASE2 == back_trace[i][j]) i++;
        else if (CASE3 == back_trace[i][j]) j--;
        else assert(false);
    }

    // fill in the first half. Since we filled in from the back, current 
    // is now pointing to the left most empty slot (looking at the string from left to right).
    // we can use this to know where to stop as we mirror the second half to create the first half
    // of the palindrom
    int leftmost_blank_slot = current;
    int mirroring_reader = lps.size() - 1;
    int writer = 0;
    while (writer <= leftmost_blank_slot) // writing up until where "current" stopped
        lps[writer++] = lps[mirroring_reader--];
    
}

int LongestPalindromeSubsequence(string const& s, string &lps) {
    if (s.empty()) return 0;
    if (s.size() == 1) {
        lps.push_back(s[0]);
        return 1;
    }

    vvi t(s.size(), vi(s.size()));

    // can use t above to reproduce this if memory is tight by essentially reproducing the 
    // logic used to create it but this is cleaner
    vvi back_pointer(s.size(), vi(s.size()));

    for (int gap=0; gap < s.size(); ++gap) {
        for (int i = 0; i < s.size()-gap; ++i) {
            int j = i+gap;
            if (i == j) {
                t[i][j] = 1; // single characters are palindromes
                back_pointer[i][j] = CASE1;
            }
            else if (s[i] == s[j]) {
                if (gap == 1) {
                    t[i][j] = 2; // two elements both the same
                    back_pointer[i][j] = CASE1;
                } 
                else {
                    t[i][j] = t[i+1][j-1] + 2;
                    back_pointer[i][j] = CASE1;
                }
            }
            else {
                t[i][j] = max(t[i+1][j], t[i][j-1]);
                back_pointer[i][j] = t[i][j] == t[i+1][j] ? CASE2 : CASE3;
            }
        }
    }
    lps.resize(t[0][s.size() - 1]);
    _GetLPS(back_pointer, s, lps);
    return t[0][s.size() - 1];        
}
/*************************************************************************************
 * MATRIX CHAIN MULTIPLICATION
 * Given a sequence of matrices, find the most efficient way to multiply these 
 * matrices together. The problem is not actually to perform the multiplications, 
 * but merely to decide in which order to perform the multiplications.
 * Given an array p[] which represents the chain of matrices such that the ith matrix 
 * Ai is of dimension p[i-1] x p[i]. We need to write a function MatrixChainOrder() 
 * that should return the minimum number of multiplications needed to multiply the chain.
 */
string _GetMatrix(vi const& p, int i) {
    ostringstream stream;
    stream << "[" << p[i-1] << "x" << p[i] << "]";
    return stream.str();
}

void _BuildSolution(vi const& p, vvi const& s, int i, int j, string& result) {
    if (i == j ) {
        result.assign(_GetMatrix(p, i));
        return;
    }

    string left, right; 
    // note k, the ideal midpoint point to split (left ... right) is s[i][j]
    _BuildSolution(p, s, i, s[i][j], left);
    _BuildSolution(p, s, s[i][j]+1, j, right);
    
    result.assign(left + " x " + right);
    
    // wrap all but the outermost level in parenthesis
    if (! (i == 1 && j == p.size() - 1)) {
        result.assign("(" + result + ")");
    }
    return;
}

int MatrixChainOrder(vi const& p, string& m_print, string& result) {
    if (2 >= p.size()) return 0; // need at least two matrices to multiply

    ostringstream stream;
    for (int i = 1; i < p.size(); ++i) {
        stream << _GetMatrix(p, i) << " ";
    }
    string stream_str(stream.str());
    m_print.swap(stream_str);

    /* 
     * t[i,j] = minimum number of scalar multiplications needed to compute the matrix 
     * A[i]A[i+1] .... A[j-1]A[j]" = A[i...j] where A[i] is p[i-1]xp[i]
     */
    int num_matrices = p.size() - 1;
    vvi t(num_matrices+1, vi(num_matrices+1));
    vvi solution(num_matrices+1, vi(num_matrices+1));

    // do make the dependency graph of the table work, we need to calculate m for all submatrices of length
    // l before we calculate the submatrics for l+1
    for (int gap=0; gap < num_matrices; ++gap) {
        for(int i = 1; i <= num_matrices-gap; i++) {
            int j = i+gap;
            if (i == j) // no cost to "multiply" one matrix (no multiplication to do)
                t[i][j] = 0;
            else {
                t[i][j] = numeric_limits<int>::max();
                for (int k=i; k <= j-1; ++k) {
                    // divide the matrices set into two at position k. Then the total
                    // number of multiplications is the the cost of resolving the 
                    // parenthesizations (i...k) and (k+1 .... j) plus the cost of 
                    // multiplying those two resulting matrices together
                    int count = t[i][k] + t[k+1][j] + p[i-1]*p[k]*p[j];
                    if (count < t[i][j]) {
                        t[i][j] = count;
                        solution[i][j]=k;
                    }
                }
            }
        }
    }
    _BuildSolution(p, solution, 1, num_matrices, result);
    return t[1][num_matrices];
}
/*************************************************************************************
 * Subset Sum problem
 * Is there an array of items that sums to the given sum?
 */
void _GetSubset(vvbool const& t, vi const& v, int items, int sum, vi& result) {
    if (0 == items) return;
    if (t[items-1][sum]) {
        _GetSubset(t, v, items-1, sum, result);
    }
    else {
        _GetSubset(t, v, items-1, sum-v[items-1], result);
        result.push_back(v[items-1]);
    }
}

// iterative implementation of the same function above done for educative purposes
// HOWEVER!!! THIS WILL GET THE ITEMS BACKWARDS. WOULD NEED TO USE A LIST FOR FORWARDS
// and do a push_front() to make this work
void _GetSubset(vvbool const& t, vi const& v, int sum, vi& result) {
    for (int i = v.size(); i >=1; --i) {
        if (! t[i-1][sum]) { // because of OR-ing order we need to check this is negative first
            result.push_back(v[i-1]);
            sum -= v[i-1];
        }
    }
}

bool SubsetWithSum(vi const& v, int sum, vi& result) {
    vvbool t(v.size()+1, vector<bool>(sum+1));

    for (int i = 0; i <= v.size(); ++i) {
        for (int s = 0; s <= sum; ++s) {
            if (0 == s)  // always true
                t[i][s] = true;
            else if (0 == i) // always false except the s == 0 case above
                t[i][s] = false;
            else if (s < v[i-1])  // v is zero indexed so item i is at index i-1
                t[i][s] = t[i-1][s]; // i-th element is too large to be included
            else 
                t[i][s] = t[i-1][s] || t[i-1][s-v[i-1]]; // v is zero indexed so item i is at index i - 1
        }
    }
    if (t[v.size()][sum]) {
        _GetSubset(t, v, v.size(), sum, result);
    }
    return t[v.size()][sum];
}

/*************************************************************************************
 
 DICE THROW PROBLEM - given N dice with M faces, how many ways are the to sum to 
 a value x

*/
int WaysToSumDiceTo(int sum_to, int dice_count, int face_count) {
    
    // sum_to is far too large to be summed even if all dice are rolled to max
    // face in one throw
    if (sum_to >= dice_count*face_count) 
        return (sum_to == dice_count*face_count ? 1: 0);

    // sum_to is far too small to allow the dice to all be thrown even if they all 
    // land on their smallest face
    if (sum_to <= dice_count) // smallest face is 1
        return (sum_to == dice_count ? 1 : 0);

    vvi table(dice_count+1, vi(sum_to+1, 0)); // initialize all values to 0

    // dice=1 case Initialize values we can get to in the single throw
    for (int s = 1; s <= sum_to && s <= face_count; ++s) 
        table[1][s] = 1;

    for (int d = 2; d <= dice_count; ++d) 
        for (int s = 1; s <= sum_to; ++s) 
            for (int k=1; k <= face_count && k <= s; ++k) 
                table[d][s] += table[d-1][s-k];

    return table[dice_count][sum_to];
}
/*************************************************************************************
    ROD CUTTING 
    ------------
    Given a rod of length n inches and an array of prices that contains prices of all 
    pieces of size smaller than n. Determine the maximum value obtainable by cutting 
    up the rod and selling the pieces. 
*/
int CutRod(vi const& p, vi& cuts) {
    if (p.empty()) return -1;
    
    int n = p.size();
    vi table(n+1, INT_MIN); // t[i] optimal price that can be obtained by cutting rod length i
    vi s(n+1, INT_MAX); // s[i] = j means best first cut to make for length i is at j
    
    table[0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            int rem = i-j; // remainder
            if (table[i] < p[j-1] + table[rem]) { // p is zero indexed
                table[i] = p[j-1] + table[rem];
                s[i] = j;
            }
        }
    }
    int len = n;
    while (len > 0) {
        cuts.push_back(s[len]);
        len -= s[len];
    }
    return table[n];
}

/*************************************************************************************
 *
 * BEST STRATEGY FOR THE GAME
 * Problem statement: Consider a row of n coins of values v1 . . . vn, where n is even
 * We play a game against an opponent by alternating turns. In each turn, a player 
 * selects either the first or last coin from the row, removes it from the row 
 * permanently, and receives the value of the coin. Determine the maximum possible 
 * amount of money we can definitely win if we move first.
 */


void GetMoves(vvi const& t, vi const& coins, vi& moves_player_one, vi& moves_player_two) {  
    int i = 0, j = coins.size() - 1;
    bool player_ones_turn = true;
    while (i <= j) {
        int picked_left = (i+1 <= j) ? t[i+1][j] : 0; // If current player takes coins[i], opponent gets this scenario ...
        int picked_right = (i <= j-1) ? t[i][j-1] : 0; // If current player takes coin[j], opponent gets this scenario
        vi& mover = player_ones_turn ? moves_player_one : moves_player_two;

        // current player will pick the value the leaves player_two with least favorable option for his
        // upcoming move (i.e the smallest coin)
        if (picked_left <= picked_right) { // opponent is left worse off if I take coin i
            mover.push_back(coins[i]);
            i++;
        } else { // opponent is left worse of if I take coin j
            mover.push_back(coins[j]);
            j--;
        }
        player_ones_turn = !player_ones_turn;
    }
}

int BestStrategyForGame(vi const& coins, vi& moves_player_one, 
                      vi& moves_player_two) {
    int n = coins.size();
    if (n % 2 != 0) return -1; // coins must be an even number (could alsdo do n & (n-1) != 0)

    vvi table(n, vi(n, 0));
 
    for (int gap = 0; gap < n; ++gap) {
        for (int i=0; i < n-gap; ++i) {
            int j = i+gap;
            int a = (i+2 <= j) ? table[i+2][j] : 0;
            int b = (i+1 <= j-1) ? table[i+1][j-1] : 0;
            int c = (i <= j-2) ? table[i][j-2] : 0;

            table[i][j] = max(coins[i] + min(a, b),
                             coins[j] + min(b, c));
        }
    }
    GetMoves(table, coins, moves_player_one,  moves_player_two);
    return table[0][n-1];
}
/*************************************************************************************
    NLOGN LONGEST INCREASING SUBSEQUENCE
    ------------
    Find and print the longest monotonically increasing subsequence in nlogn
*/
int _GetLowestHigherValue(vi const& v, vi const& indices, int l, int r, int target) {
    while (r - l > 1) {
        int mid = (l + r)/2;
        if (v[indices[mid]] >= target) 
            r = mid;
        else 
            l = mid;
    }
    return r;
}

tuple<int, vi> nlog_n_LongestIncreasingSubsequence(vi const& v) {
    if (v.empty()) return make_tuple(0, vi(0));

    vi tail_indices(v.size(), 0);
    vi prev_indices(v.size(), -1);
    
    prev_indices[0] = -1;
    int lis_len = 1; // invariant: always point to the the next empty location

    for (int i = 1; i < v.size(); ++i) {
        if (v[i] < v[tail_indices[0]]) 
            // new smallest value 
            tail_indices[0] = i;
        else if (v[i] > v[tail_indices[lis_len-1]]) {
            // clone and extend the largest subsequence
            prev_indices[i] = tail_indices[lis_len-1];
            tail_indices[lis_len++] = i;
        }
        else {
            // A[i] is a potential candidate for a future subsequence
            // it will take the last of the next tail value that is larger than it
            // (i.e ceil value)
            int pos = _GetLowestHigherValue(v, tail_indices, 0, lis_len-1, v[i]);
            prev_indices[i] = tail_indices[pos-1];
            tail_indices[pos] = i;
        }       
    }

    vi lis;
    int last = tail_indices[lis_len-1];
    while (last > -1) {
        lis.push_back(v[last]);
        last = prev_indices[last];
    }
    reverse(lis.begin(), lis.end());
    return make_tuple(lis_len, lis);
}