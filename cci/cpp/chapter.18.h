#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

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

void _MakeDict(vector<string>& const words, unordered_set<string>& dict) {
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

string LongestCompoundWord_DP(vector<string>& a) {
    std::sort(a.begin(), a.end(), _IsLonger);
    
    unordered_set<string> dict;
    _MakeDict(a, dict);

    for (int i = 0; i < a.size(); ++i) {
        if (_CanBreakWord(a[i], dict)) {
            return a[i];
        }
    }
    return "";
}

