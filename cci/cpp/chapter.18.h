#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <deque>
#include "heap.h"
#include "trie.h"
#pragma once
//
// 18.1
//
int _badd(int a, int b) {
    if (0==b) return a;
    int result = a ^ b; // adding without carrying
    int carry = (a & b) << 1; // carrying without adding
    return _badd(result, carry);
}

int _badd_iterative(int a, int b) {
    
    int result = a ^ b;
    int carry = (a & b) << 1;

    while (carry != 0) {
        int r1 = result ^ carry;
        carry = (result & carry) << 1;
        result = r1;
    }
    return result;
}

int badd(int a, int b) {
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    int result = _badd_iterative(a, b);
    cout << "result=" << result << endl;
    return result;
}                                                                                                                                                                                                                                                          
//
// 18.2
//
struct Card { 
    int suite;
    int value;
};
int random(int low, int high) {
    /* initialize random seed: */
    srand (time(NULL));
    int range = high - low;
    return low + (rand() % (range+1));
}

void PrintCards(vector<Card> const& cards) {
    for (int i = 0; i < cards.size(); ++i) {
        cout << cards[i].value << " ";
    }
    cout << endl;
}

void ShuffleDeck_Mine(vector<Card>& cards) {
    PrintCards(cards);
    int last = cards.size() - 1;
    for (int i = 0; i < cards.size(); ++i) {
        int k = random(0, last); 
        _swap(&cards[k], &cards[last]);
        last--;
    }
    PrintCards(cards);
}


void ShuffleDeck_CCI(vector<Card>& cards) {
    PrintCards(cards);
    for (int i = 0; i < cards.size(); ++i) {
        int k = random(0,i); // NOTE: upper range is i and not end of the array! i.e increasing range
        _swap(&cards[i], &cards[k]);
    }
    PrintCards(cards);
}

//
// 18.3
//
void PickM_MineBetter(vector<int>& n, int m) {
    // Think of this as picking from a bag where the partition [last, n]
    // will contain that items that have ALREADY BEEN picked are in hand
    int last = n.size() - 1;
    for (int i = 0; i < m; ++i) {
        int k = random(0, last);
        _swap(&n[k], &n[last]);
        last--;
    }
    // last is at -1 off of the start of set m after the above look so we need
    // to bump it forward 1
    for (int i = last+1; i < n.size(); ++i) {
        cout << n[i] << " ";
    }
}

void PickM_CCI(vector<int> const&n, int m) {
    vector<int> vm(m);
    for (int i = 0; i < m; ++i) {
        vm[i] = n[i];
    }
    
    for (int i = m; i < n.size(); ++i) {
        int k = random(0, i);
        if (k < m) {
            vm[i] = n[k];
        }
    }

    for (int i = 0; i < vm.size(); ++i) {
        cout << vm[i] << " ";
    }

}
//
// 18.4
//
int _CountTwos(int n) {
    int count = 0;
    while (n > 0) {
        if (n % 10 == 2) {
            count++;
        }
        n /= 10;
    }
    return count;
}

int CountTwosBruteForce(int n) {
    int count = 0;
    for (int i=2; i <=n; ++i) {
        count += _CountTwos(i);
    }
    return count; 
}
//
// 18.5
//
int MinDist(string const& a, string const& b, vector<string> const& words) {
    int min = INT_MAX;
    int w1_pos = -1;
    int w2_pos = -1;
    for (int i = 0; i < words.size(); ++i) {
        if (0 == _stricmp(a.c_str(), words[i].c_str())) {
            w1_pos = i;
            if (w2_pos != -1) {
                int distance = w1_pos - w2_pos;
                if (min > distance) {
                    min = distance;
                }
            }
        } else if (0 == _stricmp(b.c_str(), words[i].c_str())) {
            w2_pos = i;
            if (w1_pos != -1) {
                int distance = w2_pos - w1_pos;
                if (min > distance) {
                    min = distance;
                }
            }
        }
    }
    return min;
}
//
// 18.6
//
int _partition(vector<int>& a, int left, int right) {
    // use the middle element as the pivot. Move it to the left
    // end to get it out of the way. Well remember to move it back
    // at the end
    int m = (left + right) / 2;
    _swap(&a[left], &a[m]);
    int p = a[left];
    int cache = left;
    
    left++; // skip over the pivot
    while (left <= right) {
        while (a[left] <= p) left++;
        while (a[right] > p) right--;
        if (left <= right) {
            _swap(&a[left], &a[right]);
            left++;
            right--;
        }
    }
    // restore the pivot to its correct position (before the right half
    // of partition)
    _swap(&a[cache], &a[right]);
    return right;
}

int _get_index_of_nth(vector<int>& a, int n, int left, int right) {
    int pivot_index = _partition(a, left, right);

    int left_size = pivot_index - left + 1;
    if (left_size == n) { // pivot is the right 
        return pivot_index;
    } 
    else if (left_size > n) {
        return _get_index_of_nth(a, n, left, pivot_index-1);
    }
    else {
        return _get_index_of_nth(a, n - left_size, pivot_index+1, right);
    }
}

void _test_print_nth(vector<int>& a, int n) {
    cout << n << " smallest=" << a[_get_index_of_nth(a, n, 0, a.size()-1)];
    cout << endl;
}

void print_n_smallest(vector<int>& a, int n) {
    if (n <= 0) return;

    int nth = _get_index_of_nth(a, n, 0, a.size() -1);
    cout << n << " smallest:";
    for (int i = 0; i <= nth; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
}
//
// 18.7
//
bool _IsLonger(string const& lhs, string const& rhs) {
    return lhs.size() > rhs.size();
}

void _MakeDict(vector<string> const&  words, unordered_set<string>& dict) {
    for (int i = 0; i < words.size(); ++i) {
        string s;
        s.resize(words[i].size());
        std::transform(words[i].begin(), words[i].end(), s.begin(), ::tolower);
        dict.insert(s);
    }
}

bool _InDict(string const& w, unordered_set<string> const& dict) {
    string s;
    s.resize(w.size());
    std::transform(w.begin(), w.end(), s.begin(), ::tolower);
    return dict.end() != dict.find(s);
}

void _PrintWords(string const& w, vector<int> const& prev, int end_pos) {
    if (end_pos == -1) {
        cout << "Words=";
        return;
    }
    int start_pos = prev[end_pos];
    int end_of_prev_words = start_pos - 1;
    _PrintWords(w, prev, end_of_prev_words);
    cout << w.substr(start_pos, end_pos-start_pos+1) << " ";
}

bool _CanBreakWord(string const& w, unordered_set<string> const& dict) {
    // t[i] is true IFF w.subst(0,i) can be broken up into words that
    // are in dict
    vector<bool> t(w.size()+1, false);
    vector<int> prev(w.size()+1, -1); // so we can regenerate solution
                                    // prev[i] = j means word ending at position i
                                    // started at j

    for (int i = 1; i <= w.size(); ++i) {
        // note that we don't allow a word to claim to  be a compoundword
        // of itself
        string prefix = w.substr(0, i);
        if (!t[i] && (prefix != w) && _InDict(prefix, dict)) {
            prev[i-1] = 0;
            t[i] = true;
        }
        if (i == w.size() && t[i]) {
            cout << w << " Resolves! \n";
            _PrintWords(w, prev, w.size()-1);
            return true;
        }

        if (t[i]) {
            for (int j = i+1; j <= w.size(); ++j) {
                if (!t[j] && _InDict(w.substr(i, j-i), dict)) {
                    prev[(i+(j-i))-1]=i;
                    t[j] = true;
                }
                if (j == w.size() && t[j]) {
                    cout << w << " Resolves! \n";
                    _PrintWords(w, prev, w.size()-1);
                    return true;
                }
            }
        }
    }
    return false;
}
// O(|a|*|w|^2)
string LongestCompoundWord_DP(vector<string>& a) {
    std::sort(a.begin(), a.end(), _IsLonger);
    
    unordered_set<string> dict;
    _MakeDict(a, dict);

    for (string &s : a) {
        if (_CanBreakWord(s, dict)) {
            return s;
        }
    }
    return "";
}
// O(kN)
struct WordTracker {
    string word;
    vector<string> sub_words; // confirmed subwords
    string remainder_suffix; // candidate suffix portions not yet processed
    explicit WordTracker(string const& s):word(s) {}
    WordTracker() {}
    void swap(WordTracker& rhs) {
        word.swap(rhs.word);
        sub_words.swap(rhs.sub_words);
        remainder_suffix.swap(rhs.remainder_suffix);
    }
};

string LongestCompoundWord_Trie(vector<string>& a) {
    // Create a Trie and insert all the words into it
    Trie trie;
    for (string &s : a) {
        trie.Insert(s);
    }
 
    // for each word qeuee it up for processing together with its valid suffices.
    // This takes O(|a| * k) where k is the maximum number of valid words in a compound word
    deque<WordTracker> queue;
    for (string &s : a) {
        vector<string> prefixes;
        trie.GetAllPrefixes(s, prefixes);
        for (string &p: prefixes) {
            WordTracker wt(s); 
            wt.sub_words.push_back(p);
            wt.remainder_suffix = s.substr(p.size());
            queue.push_back(wt);
        }
    }

    // process the queue by trying to reduce all suffices down to nothing.
    // this should be O(|w|*|max # sub_words|)
    WordTracker longest_word;
    while (!queue.empty()) {
        WordTracker& wt = queue.front();
        if (trie.Contains(wt.remainder_suffix)) {
            if (longest_word.word.empty() || (longest_word.word.size() < wt.word.size())) {
                wt.sub_words.push_back(wt.remainder_suffix); // remainder suffix is a valid word
                longest_word.swap(wt);
            }
        }
        else { // reduce the suffix down even further
            vector<string> prefixes;
            trie.GetAllPrefixes(wt.remainder_suffix, prefixes);
            for (string& p: prefixes) {
                WordTracker wt_next(wt.word);
                // get the already identified subwords and add the new one and then
                // reduce the remainder suffix down by the new prefix
                wt_next.sub_words.swap(wt.sub_words);
                wt_next.sub_words.push_back(p);
                wt_next.remainder_suffix = wt.remainder_suffix.substr(p.size());
                queue.push_back(wt_next);
            }
        }
        queue.pop_front();
    }
    cout << "\nLongestWord (Trie) =" << longest_word.word << endl;
    cout << "Words=";
    for (string s : longest_word.sub_words) {
        cout << s << " ";
    }
    cout << endl;
    return longest_word.word;
}
//
// MEMOIZATION APPROACH
//
bool _CanBreakWord(string const& s, unordered_set<string> const& dict, 
                   unordered_map<string, bool>& memo, bool original_word=false) {
    if (memo.end() != memo.find(s)) {
        return memo[s];
    }
    else if (_InDict(s, dict) && !original_word) {
        return true;
    }
    else {
        for (int i = 1; i < s.size(); ++i) {
            string left = s.substr(0,i);
            string right = s.substr(i);
            if (_InDict(left, dict) && _CanBreakWord(right, dict, memo)) {
                return true;
            }
        }
    }
    memo[s] = false;
    return false;
}

string LongestCompoundWord_Memo(vector<string>& a) {
    std::sort(a.begin(), a.end(), _IsLonger);

    unordered_set<string> dict;
    _MakeDict(a, dict);

    unordered_map<string, bool> memo;
    for (string &s: a) {
        if (_CanBreakWord(s, dict, memo, true)) {
            cout << s << " Resolves! (Memo Approach) \n";
            return s;
        }
    }
    return "";
}
//
// 18.8
//
void SearchStringIn(string const& s, vector<string> const& t) {
    if (t.empty()) return;

    Trie trie;
    for (int i = 0; i < s.length(); ++i) {
        trie.Insert(s.substr(i));
    }

    // check if any of them are substrings of any prefix
    for (string const& p : t) {
        if (trie.IsSubstring(p)) {
            cout << p << " is in " << s << endl;
        }
        else {
            cout << p << " is NOT in " << s << endl;
        }
    }
}
//
// 18.9
//
void test_heap(vector<int>const & v) {
    /*unique_ptr<heap> max_h(new max_heap());
    max_h->make_heap(v);
    max_h->insert(60);
    cout << "-----" << endl;
    max_h->print_tree();
    max_h->extract_top();
    cout << "-----" << endl;
    max_h->print_tree();
    *///static_cast<max_heap*>(max_h.get())->sort();
    cout << "-----" << endl;
    unique_ptr<heap> min_h(new min_heap());
    min_h->make_heap(v);
    min_h->insert(-60);
    cout << "-----" << endl;
    min_h->print_tree();
    min_h->extract_top();
    cout << "-----" << endl;
    min_h->print_tree();
    //static_cast<min_heap*>(min_h.get())->sort();
}


