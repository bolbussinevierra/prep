#pragma once

BEGIN_NAMESPACE(epi_12)

const uint PRIME_MOD = 10007;
const uint HASH_BASE = 101;
//
// 12.1 - rolling hash for strings
// 
template <typename T>
T _modpow(T base, T exp, T modulus) {
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

uint roll_hash(string const& s, char n) {
    int update_hash = get_hash(s);
    // remove the first charater
    update_hash -= (s[0] * _modpow2(HASH_BASE, s.size() - 1, PRIME_MOD)) % PRIME_MOD;
    
    if (update_hash < 0) 
        update_hash += PRIME_MOD;

    // add the new character
    update_hash = ((update_hash * HASH_BASE) + n) % PRIME_MOD;
    return update_hash;
}

int RabinKarp(string const& text, string const& pattern) {
    if (pattern.size() > text.size()) {
        return -1; // pattern cannot be a substring of text
    }

    int text_hash = 0, pattern_hash = 0;
    text_hash = get_hash(text.substr(0, pattern.size()));
    pattern_hash = get_hash(pattern);

    for (int i = pattern.size(); i < text.size(); ++i) {
        if (text_hash == pattern_hash && 
            (0 == text.compare(i - pattern.size(), pattern.size(), pattern))) {
            return i - pattern.size(); // found a match at this location
        }

        // use rolling hash to computer the new hash code
        text_hash = roll_hash(text.substr(i - pattern.size(), pattern.size()), text[i]);
    }

    // try to match pattern and text[text.size() - pattern.size():  text.size() - 1]
    if (text_hash == pattern_hash && 
        (0 == text.compare(text.size() - pattern.size(), pattern.size(), pattern))) {
        return text.size() - pattern.size(); // found a match at this location
    }
    return -1; // pattern is not a substring of text
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

pair<int, int> FindSmallestSubArraySequentiallyCoveringSubset(
    vector<string> const& A,
    vector<string> const& subset) {
    unordered_map<string, int> reverse_subset_index;
    vi last_pos_for(subset.size(), -1);
    vi covering_distance_for(subset.size(), numeric_limits<int>::max());

    for (int i = 0; i < subset.size(); ++i)
        reverse_subset_index[subset[i]] = i;

    pair<int, int> res(-1, A.size()); // default value
    for (int i = 0; i < A.size(); ++i) {
        auto it = reverse_subset_index.find(A[i]); // is this one of the subset items?
        if (it != reverse_subset_index.end()) {
            int pos = it->second;
            if (pos == 0) { // first item in the subset
                covering_distance_for[0] = 1;
            } else if (covering_distance_for[pos - 1] != numeric_limits<int>::max()) {
                covering_distance_for[pos] = covering_distance_for[pos - 1] + (i - last_pos_for[pos - 1]);
            }
            last_pos_for[pos] = i;

            if (pos == subset.size() - 1 &&   // last item has been covered? 
                covering_distance_for.back() < res.second - res.first + 1) { // smaller covering set
                res = { i - covering_distance_for.back() + 1, i };
            }
        }
    }
    return res;
}

END_NAMESPACE