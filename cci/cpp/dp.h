#include <iostream>
#include <vector>
#pragma once
using namespace std;

struct Item {
    int weight;
    int value;
};
/*
Solves Knapsack problem with a dynamic problem allowing for duplicate
items
*/
void PrintKnapsack(int C, vector<int> const& R, vector<Item> const& items) {
    if  (C==0 || R[C] == -1) {
        cout << "Printing Optimal Knapsack:" << endl;
        return;
    }
    PrintKnapsack(C - items[R[C]].weight, R, items);
    cout << "{w:" << items[R[C]].weight << " ,v:" << items[R[C]].value << "} ";
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