#pragma once

template<typename T>
class union_find {
public:
    explicit union_find(vector<T> const& items) {
        for (auto const& p : items) {
            parent_[p] = p; // every item is its own set
            rank_[p] = 1; // every item is a one node tree
        }
    }

    void join(T const& set_1, T const& set_2) {
        if (rank_[set_1] > rank_[set_2]) {
            parent_[set_2] = set_1;
        }
        else if (rank_[set_1] < rank_[set_2]) {
            parent_[set_1] = set_2;
        }
        else {
            parent_[set_1] = set_2;
            ++rank_[set_2];
        }
    }

    T find(T const& set) {
        T curr = set;
        while (parent_[curr] != curr){
            curr = parent_[curr];
        }
        return curr;
    }

    union_find& operator=(union_find const&) = delete;
    union_find(union_find const&) = delete;

private:
    unordered_map<T, T> parent_;
    unordered_map<T, int> rank_;
};