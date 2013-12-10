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

    if  (C == 0 || R[C] == -1) {
        cout << "Printing Optimal Knapsack:" << endl;
        return;
    }
    PrintKnapsack(C - items[R[C]].weight, R, items);
    cout << "{w:" << items[R[C]].weight << ", v:" << items[R[C]].value << "} ";
}

void KnapsackRepeats(int C, vector<Item> const& items) {
    vector<int> DP(C+1, 0); // DP table;
    vector<int> R(C+1, -1); // item picked for each C. So we can generate solution

    DP[0] = 0;
    for (int c = 1; c <= C; ++c) {
        DP[c] = DP[c-1]; // Best value as at least this much if new items not added
        for (int i = 0; i < items.size(); ++i) {
            if (items[i].weight <= c) {
                int temp = DP[c - items[i].weight] + items[i].value;
                if (temp > DP[c]) {
                    DP[c] = temp;
                    R[c] = i;
                }
            }
        }
    }

    cout << "KnapsacksRepeats(" << C << ")=" << DP[C] << endl;
    PrintKnapsack(C, R, items); cout << endl;
}