#include <iostream>
#include <vector>
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
