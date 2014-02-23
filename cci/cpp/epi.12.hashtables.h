#pragma once

namespace epi_12 {
const uint PRIME_MOD = 10007;
const uint HASH_BASE = 101;
//
// 12.1 - rolling hash for strings
// 
template <typename T>
T _modpow(T base, T exp, T modulus) {
    base %= modulus;
    T result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % modulus;
        base = (base * base) % modulus;
        exp >>= 1;
    }
    return result;
}
template <typename T>
T _modpow2(T base, T exp, T modulus) {
    base %= modulus;
    T result = 1;
    for (uint i = 1; i <= exp; ++i) {
        result *= base;
        result %= modulus;
    }
    return result;
}

uint get_hash(string const& s) {
    uint val = 0;
    for (char c : s) {
        val = (val * HASH_BASE) + c;
        val %= PRIME_MOD;
    }
    return val; 
}
// TODO: Look into rabin-karp algorithm!
uint roll_hash_broken(string const& s, char n) {
    uint add_char = ((get_hash(s) * HASH_BASE) + n) % PRIME_MOD;
    printf("%u == %d\n", add_char, get_hash(s + string(1, n)));
    uint size = s.size() + 1;
    uint rem_char = (s[0] * _modpow(HASH_BASE, size-1, PRIME_MOD));
    return (add_char - rem_char) % PRIME_MOD;
}

//
// 12.14
// 
pair<int, int> FindSmallestSubArrayCoveringSubset(
    vector<string> const& A, vector<string> const& Q) {
    unordered_set<string> dict(Q.cbegin(), Q.cend());
    unordered_map<string, int> count_Q;

    int l = 0, r = 0;
    pair<int, int> res(-1, -1);
    while (r < static_cast<int>(A.size())) {
        // keep moving r until it reaches end or count_Q has |Q| items
        while (r < static_cast<int>(A.size()) && count_Q.size() < Q.size()) {
            if (dict.find(A[r]) != dict.end()) {
                ++count_Q[A[r]];
            }
            ++r;
        }

        if (count_Q.size() == Q.size() && // found |Q| keywords
            (res == make_pair(-1, -1) || r - 1 - l < res.second - res.first)) {
            res = make_pair(l, r - 1);
        }

        // keep moving l until it reaches end or count_Q has less |Q| items
        while (l < r && count_Q.size() == Q.size()) {
            if (dict.find(A[l]) != dict.end()) {
                auto it = count_Q.find(A[l]);
                if (-- (it->second) == 0) {
                    count_Q.erase(it);
                    // at this point we know that L (which was still at 0 before this
                    // while loop was entered) has been brought up as much as possible 
                    // without violating the invariant (count_Q.size() == Q.size()) so we
                    // can tighten res (e.g [0. 5] => [3, 5]
                    if (res == make_pair(-1, -1) || r - 1 - l < res.second - res.first) {
                        res = make_pair(l, r -1);
                    }
                }
            }
            ++l;
        }
    }
    return res;
}

pair<int, int> FindSmallestSubArrayCoveringSubset_Streaming(
    istringstream& sin, vector<string> const& Q) {
    list<int> loc; // tracks the last occurence (index) of each string in Q
    unordered_map<string, list<int>::iterator> dict;
    for (const string& s : Q) 
        dict.emplace(s, loc.end());

    pair<int, int> res(-1, -1);
    int idx = 0;
    string s;
    while (sin >> s) {
        auto it = dict.find(s);
        if (it != dict.end()) { 
            if (it->second != loc.end()) {
                loc.erase(it->second);
            }
            loc.emplace_back(idx); // keep the later elements last. front always has the earliest element
            it->second = --loc.end(); // update the dict. Order is not changed here
        }

        if (loc.size() == Q.size() && // found |Q| keywords
            (res == make_pair(-1, -1) || idx - loc.front() < res.second - res.first)) {
                res = make_pair(loc.front(), idx);
        }
        ++idx;
    }
    return res;
}

}