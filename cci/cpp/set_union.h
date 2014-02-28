#pragma once

template<typename key, typename value>
class set_union {
    explicit set_union(vector<pair<key, value>> const& items) {
        for (auto const& p : items) {
            parent_[p.first] = p.second;
            rank_[p.first] = 0;
        }
    }

private:
    unordered_map<key, value> parent_;
    unordered_map<key, int> rank_;
};