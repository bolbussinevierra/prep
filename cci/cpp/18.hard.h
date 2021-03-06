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
        printf("(%d, %d)", a, b);
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
    srand (time(nullptr));
    int range = high - low;
    return low + (rand() % (range+1));
}

void PrintCards(vector<Card> const& cards) {
    for (int i = 0; i < cards.size(); ++i) {
        cout << cards[i].value << " ";
    }
    cout << endl;
}

// simulates a real life scenario of picking a random permutation with fair
// probabilities
void ShuffleDeck_Mine(vector<Card>& cards) {
    PrintCards(cards);
    int last = cards.size() - 1;
    for (int i = 0; i < cards.size(); ++i) { // as many items are they are
        int k = random(0, last);             // pick a random one from remaining
        _swap(&cards[k], &cards[last]);      // swap it with the last
        last--;                               // declare the last "dead"
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
void PickM_MineBetter(vi& n, int m) {
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

void PickM_CCI(vi const&n, int m) {
    vi vm(m);
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
// count using recursion in order of length of number (LogN)
typedef unordered_map<int, int> Cache184;
// take n = 413 as example
int _CountTwosMemoized(int n, Cache184& cache) {
    if (n < 2) // base case
        return 0;
    else if (cache.find(n) != cache.end()) 
        return cache[n];
    
    int result = 0;
    int power_10 = 1;
    while (power_10 * 10 < n) 
        power_10 *= 10;

    // power_10 = 100
    int most_significant_digit = n / power_10; // 4
    int remainder = n % power_10; // 13

    // count # of 2 at the MSD position. eg its 200-299
    if (most_significant_digit > 2)
        result += power_10;
    if (most_significant_digit == 2)
        // if n is 213, count 200-213 which is remained + 1 (14)
        result += remainder + 1;

    // count #2 in the remainder:
    // count recursively the # of 2's from 1 to 100 and then multiply by MSB
    // this gets the # of 2 in 1 to 100. multiply by msb accounts for the number
    // of times that range repeats
    result += most_significant_digit * _CountTwosMemoized(power_10, cache);
    result += _CountTwosMemoized(remainder, cache);
    
    cache[n] = result;
    return result;
}
int CountTwosMemoized(int n) {
    Cache184 cache;
    return _CountTwosMemoized(n, cache);
}

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
    int min = numeric_limits<int>::max();
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
int _partition(vi& a, int left, int right) {
    // generate a radom int in [l,r] and use its value as the pivot. Move the
    // pivot to the left to get it out of the way
    random_device rd;
    default_random_engine e(rd());
    uniform_int_distribution<int> dist(left, right);
    int random_pivot = dist(e);

    _swap(&a[left], &a[random_pivot]);
    int p = a[left];
    int cache = left;
    
    left++; // skip over the pivot
    while (left <= right) {
        while (left <= right && a[left] <= p) left++;
        while (left <= right && a[right] > p) right--;
        if (left <= right) {
            _swap(&a[left], &a[right]);
            left++;
            right--;
        }
    }
    // restore the pivot to its correct position (before the right half
    // of partition)
    _swap(&a[cache], &a[right]); // could also swap with (left - 1);
    return right;
}

int _GetIndexOfNthSmallest(vi& a, int n) {
    int l = 0, r = a.size() - 1;
    while (l <= r) {
        int p = _partition(a, l, r);
        if (p == n - 1) 
            return a[p];
        else if (p > n - 1)
            r = p - 1;
        else 
            l = p + 1;
    }
    throw invalid_argument("n is larger than items in array");
}
BEGIN_NAMESPACE(deprecated)
int _GetIndexOfNthSmallestRecursive(vi& a, int n, int left, int right) {
    int pivot_index = _partition(a, left, right);

    int left_size = pivot_index - left + 1;
    if (left_size == n)  // pivot is the nth number
        return pivot_index;
    else if (left_size > n)
        return _GetIndexOfNthSmallestRecursive(a, n, left, pivot_index-1);
    else
        // if going right make sure we adjust rank
        return _GetIndexOfNthSmallestRecursive(a, n - left_size, pivot_index+1, right);
}
END_NAMESPACE

void _test_print_nth(vi& a, int n) {
    cout << n << " smallest=" << a[_GetIndexOfNthSmallest(a, n)];
    cout << endl;
}

void print_n_smallest(vi a, int n) {
    if (n <= 0) return;

    int nth = _GetIndexOfNthSmallest(a, n);
    cout << n << " smallest:";
    for (int i = 0; i <= nth; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
}

BEGIN_NAMESPACE(epi_11)
//
// 11.13
// 
int _PartitionDecreasing(vi& a, int l, int r) {
    random_device rd;
    default_random_engine e(rd());
    uniform_int_distribution<int> dist(l, r);
    int random_pivot = dist(e);

    swap(a[l] ,a[random_pivot]);
    
    int p = a[l];
    int cache = l;
    l++; // skip the pivot
    
    while (l <= r) {
        while (l <= r && a[l] >= p) l++;
        while (l <= r && a[r] < p ) r--;
        if (l <= r) {
            swap(a[l], a[r]);
            l++, r--;
        }
    }
    swap(a[cache], a[r]);
    return r;
}
void PrintKthLargest(vi && a, int k) {
    int l = 0, r = a.size() - 1;
    while (l <= r) {
        int p = _PartitionDecreasing(a, l, r);
        if ( p == k - 1) {
            printf("%d Largest=%d\n", k, a[p]);
            return;
        } 
        else if (p > k - 1) {
            r = p - 1;
        } 
        else { 
            l = p + 1;
        }
    }
    
}
END_NAMESPACE

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

void _PrintWords(string const& w, vi const& prev, int end_pos) {
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
    vi prev(w.size()+1, -1); // so we can regenerate solution
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
string LongestCompoundWord_DP(vector<string> a) {
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
    void print() {
        cout << "{ " << word << " {";
        for_each(sub_words.begin(), sub_words.end(), [](string s) { cout << s << ", "; });
        cout << "}, ";
        cout << remainder_suffix << "}\n";
    }    
};

string LongestCompoundWord_Trie(vector<string> a) {
    // Create a Trie and insert all the words into it
    Trie trie;
    for (string &s : a) {
        trie.Insert(s);
    }
 
    // for each word qeuee it up for processing together with its valid suffices.
    // This takes O(|a| * k) where k is the maximum number of valid words in a compound word
    queue<WordTracker> queue; 
    for (string &s : a) {
        vector<string> prefixes;
        trie.GetAllPrefixes(s, prefixes);
        for (string &p: prefixes) {
            WordTracker wt(s); 
            wt.sub_words.push_back(p);
            wt.remainder_suffix = s.substr(p.size());
            queue.push(wt); /* debug ->*/ wt.print();
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
                wt_next.sub_words = wt.sub_words;
                wt_next.sub_words.push_back(p);
                wt_next.remainder_suffix = wt.remainder_suffix.substr(p.size());
                queue.push(wt_next);
            }
        }
        queue.pop();
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

string LongestCompoundWord_Memo(vector<string> a) {
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

    // insert all the suffices of s into a trie
    Trie trie;
    for (int i = 0; i < s.length(); ++i) {
        trie.Insert(s.substr(i));
    }

    // check if any of the strings in p is a PREFIX of any of the SUFFIXES
    // that have been added to the trie
    for (string const& p : t) {
        if (trie.IsPrefix(p)) {
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
double GetMedian(heap* maxh, heap* minh) {
    if (maxh->empty()) return 0;
    if (maxh->size() == minh->size()) {
        return ((double) maxh->peek_top() + (double) minh->peek_top()) / 2.0;
    }
    else {
        return maxh->peek_top();
    }
}

void TrackNumber(int num, heap* maxh, heap* minh) {
/* Note - always keep maxh at least as big as minh and at most
   only one item larger */
    if (maxh->empty()) {
        maxh->insert(num);
    }
    else if (maxh->size() == minh->size()) {
        if (num <= GetMedian(maxh, minh)) {
            maxh->insert(num);
        }
        else {
            int min_top = minh->extract_top();
            maxh->insert(min_top);
            minh->insert(num);
        }
    }
    else { // maxh heap is always the larger one if they are arent equal but 
           // keep it no more than one item larger
        if (num <= GetMedian(maxh, minh)) {
            int max_top = maxh->extract_top();
            minh->insert(max_top);
            maxh->insert(num);
        }
        else {
            minh->insert(num);
        }
    }
}

void OnlineMedianAlgorithm() {
    unique_ptr<heap> maxh(new max_heap());
    unique_ptr<heap> minh(new min_heap());
    for (int i = 1; i <= 10; ++i) {
        TrackNumber(i, maxh.get(), minh.get());
        cout << " added: " << i << endl;
        cout << "median: " << GetMedian(maxh.get(), minh.get()) << endl;
    }
};

BEGIN_NAMESPACE(epi_10)
void OnlineMedian(istringstream&& sin) {
    priority_queue<int, vi, less<int>> low_max_heap;
    priority_queue<int, vi, greater<int>> high_min_heap;

    int x;
    while (sin >> x) {
        if (!low_max_heap.empty() && (x > low_max_heap.top())) 
            high_min_heap.push(x);
        else 
            low_max_heap.push(x);

        // rebalance
        if (low_max_heap.size() > high_min_heap.size() + 1)  {
            high_min_heap.push(low_max_heap.top());
            low_max_heap.pop();
        }
        else if (high_min_heap.size() > low_max_heap.size() + 1) {
            low_max_heap.push(high_min_heap.top());
            high_min_heap.pop();
        }

        // get median
        if (low_max_heap.size() == high_min_heap.size()) {
            cout << 0.5 * (high_min_heap.top() + low_max_heap.top()) << endl;
        } else {
            cout << (high_min_heap.size() > low_max_heap.size() ? 
                high_min_heap.top() : low_max_heap.top()) << endl;
        }


    }

}

END_NAMESPACE

//
// 18.10
//
typedef unordered_set<string> hash_map;
bool _visited(string const& s, hash_map const& hm) {
    return hm.end() != hm.find(s); 
}

bool _in_dict(string const& s, hash_map const& dict) {
    return dict.end() != dict.find(s);
}

hash_map _get_dict() {
    hash_map dict;
    dict.insert("DAMP");
    dict.insert("CAMP");
    dict.insert("LAMP");
    dict.insert("LIMP");
    dict.insert("LIME");
    dict.insert("MIME");
    dict.insert("LIKE");
    return dict;
}
vector<string> GetAdjacentWords(string const& w) {
    vector<string> adjacent_words;
    for (int i = 0; i < w.length(); ++i) {
        string t(w);
        for (char c = 'A'; c <= 'Z'; ++c) {
            if (w[i] != c) {
                t[i] = c;
                adjacent_words.push_back(t);
            }
        }
    }
    return adjacent_words;
}
void _unpack_path(unordered_map<string, string> const& prev, list<string>& path, string const& end) {
    path.push_front(end);
    auto it = prev.find(end);
    while (it->second != "") {
        path.push_front(it->second);
        it = prev.find(it->second);
    }
}
string MakeUpper(string const& w) {
    string start(w.size(), ' ');
    std::transform(w.begin(), w.end(), start.begin(), ::toupper);
    return start;
}

HRESULT CalculateTransform(string const& w1, string const& w2, hash_map const& dict, 
                         list<string>& path) {
    if ((w1.length() != w2.length()) || w1.empty() || dict.empty()) {
        return E_UNEXPECTED;
    }

    if (w1 == w2) {
        path.push_back(w1);
        return S_OK; // no work to do
    }

    string start = MakeUpper(w1);
    string end = MakeUpper(w2);
    
    queue<string> bfs; 
    bfs.push(start);
    
    hash_map visited;
    visited.insert(start);

    unordered_map<string, string> prev;
    prev[start] = "";

    while (!bfs.empty()) {
        for (string const& s : GetAdjacentWords(bfs.front())) {
            if (s == end) {
                prev[s] = bfs.front();
                _unpack_path(prev, path, s);
                return S_OK;
            }
            else if (_in_dict(s, dict) && !_visited(s, visited)) {
                visited.insert(s);
                bfs.push(s);
                prev[s] = bfs.front();
            }
        }
        bfs.pop();
    }
    return E_FAIL;
}


HRESULT CalculateTransform(string const& w1, string const& w2, list<string>& path) {
    hash_map dict = _get_dict();
    return CalculateTransform(w1, w2, dict, path);
}

//
// 18.11
//
struct result {
    int tlr;
    int tlc;
    int size;
};

typedef vector<vi> square;
struct square_data {
    int br;
    int bd;
};
typedef vector<vector<square_data>> processed_square;
typedef processed_square PS;
#define BLACK 0

void ProcessSquare(square const& m, PS& pm) {
    for (int r = m.size() - 1; r >= 0; --r) {
        for (int c = m.size() - 1; c >= 0; --c) {
            int br = 0;
            int bd = 0;
            if (m[r][c] == BLACK) {
                br++;
                bd++;
                if (c+1 < pm.size()) {
                    br += pm[r][c+1].br;
                }
                if (r+1 < pm.size()) {
                    bd += pm[r+1][c].bd;
                }
            }
            square_data data = {br, bd};
            pm[r][c] = data;
        }
    }
}

bool IsSquare(int r, int c, PS const& pm, int size) {
    square_data tl = pm[r][c];
    square_data tr = pm[r][c+size-1];
    square_data bl = pm[r+size-1][c];

    if (tl.br < size || tl.bd < size) return false;
    if (tr.bd < size || bl.br < size ) return false;
    return true;
}
bool FoundSquare(PS const& pm, int size, result& res) {
    // number of sub squares of size s  is count_squares
    // in each dimension (s across and s down)
    int count_squares = pm.size() - size + 1; 
    for (int r = 0; r < count_squares; ++r) {
        for (int c = 0; c < count_squares; ++c) {
            if (IsSquare(r, c, pm, size)) {
                res.tlr = r;
                res.tlc = c;
                res.size = size;
                return true;
            }
        }
    }
    return false;
}

bool GetSquare(square const& m, result& res) {
    PS pm(m.size(), vector<square_data>(m[0].size()));
    ProcessSquare(m, pm);
    for (int square_len = m.size(); square_len > 0; --square_len) {
        if (FoundSquare(pm, square_len, res)) {
            return true;
        }
    }
    return false;
}
//
// 18.12
//
void Clear(vi& k) {
    for (int &i : k) i = 0; 
}

int Kadane(vi const& k, int &first, int& last) {
    int max_sum = numeric_limits<int>::min();
    int sum = 0;
    int local_start = 0;
    last = -1; // will be useful in flagging all negative case

    for (int i = 0; i < k.size(); ++i) {
        sum += k[i];

        // make sure we check negative case first!
        if (sum < 0) {
            sum = 0;
            local_start = i+1;
        }
        else if (sum > max_sum) {
            max_sum = sum;
            first = local_start;
            last = i;
        }
        
    }

    // found at least one non-negative value
    if (last != -1) {
        return max_sum;
    }

    // else we have hit the all negative case. Find the largest negative
    // number
    int largest_negative = k[0];
    first = last = 0;
    for (int i = 1; i < k.size(); ++i) {
        if (k[i] > largest_negative) {
            largest_negative = k[i];
            first = last = i;
        }
    }
    return largest_negative;
}

int Kadane2D(vvi const& m, Rect& result) {
    assert(!m.empty() && !m[0].empty());

    int max_sum = numeric_limits<int>::min();
    int const c_rows = m.size();
    int const c_cols = m[0].size();
    vi k(c_rows);
    
    for (int left = 0; left < c_cols; ++left) {
        Clear(k);
        for (int right = left; right < c_cols; ++right) {
            
            for (int i = 0; i < c_rows; ++i) {
                k[i] += m[i][right];
            }
            int row_start = 0, row_last = 0;
            int sum = Kadane(k, row_start, row_last);

            if (sum > max_sum) {
                max_sum = sum;
                result.t = row_start;
                result.b = row_last;
                result.l = left;
                result.r = right;
            }
        }
    }
    return max_sum;
}

BEGIN_NAMESPACE(epi_15)
//
// 15.5
// 
int Kadane_CircularArray(vi A) { // pass by value since we are going to need a copy anyway
    // max sum array is max of the non-circular max_sum and the circular
    // maximum sum
    // step 1 - get the maximum sum non-circular array sum
    int first = 0, last = 0;
    int non_circular_sum = Kadane(A, first, last);

    // now for the circular case. First note that the a circular sum implies a 
    // non-circular "exemption list" of elements that do not participate in the circular array. 
    // Finding the elements that would be left out is equivalent to finding the subset of the array
    // Once we find these elements, we can subtract them from the total sum of the array to find
    // the sum of the circular bit
    int total_array_sum = accumulate(begin(A), end(A), 0); // get total sum of array
    for_each(begin(A), end(A), [](int& val) { val *= -1; }); // negate all the elements

    // find the max sum array of negated elements
    int negated_excluded_sum = Kadane(A, first, last);
    // need to re-negate the excluded sum to get actual value before its elements were negated
    int circular_sum = total_array_sum -(-negated_excluded_sum);
    
    printf("non_circular_sum:%d, circular_sum:%d \n", non_circular_sum, circular_sum);
    return max(non_circular_sum, circular_sum);
}

END_NAMESPACE
BEGIN_NAMESPACE(epi_17)
//
// epi 17.9
//
// WORKS BUT NOT REALLY THE QUESTION THE BOOK ASKED!
// BOOK CAN GROUP DIGITS TOGETHER. THIS SOLUTION TREATS
// EACH DIGITS SEPARATELY SO THERE MUST BE AN OPERATOR
// BETWEEN EACH TWO DIGITS
typedef vector<vector<pair<int, string>>> Sol;
bool CanSat(int k, vi const& d, int first, int last, Sol& s) {
    if (first == last)
        return d[first] == k;

    for (int i = 0; i <= k; ++i) {
        for (int m = first; m < last; ++m) {
            if (i != 0 && k % i == 0 && CanSat(i, d, first, m, s) && CanSat(k / i, d, m + 1, last, s)) {
                s[first][last] = { m, "x" };
                return true;
            }
            if (CanSat(i, d, first, m, s) && CanSat(k - i, d, m + 1, last, s)) {
                s[first][last] = { m, "+" };
                return true;
            }
        }
    }
    return false;
}

string GetSolution(vi const& d, Sol& s, int first, int last) {
    if (first == last)
        return to_string(d[first]);
    else {
        auto result = s[first][last];
        string left_part = GetSolution(d, s, first, result.first);
        string right_part = GetSolution(d, s, result.first + 1, last);
        return left_part + " " + result.second + " " + right_part;
    }
}

bool CanSat(int k, vi const& d) {
    Sol s(d.size(), vector<pair<int, string>>(d.size(), { -1, "" }));
    if (CanSat(k, d, 0, d.size() - 1, s)) {
        cout << GetSolution(d, s, 0, d.size() - 1); 
        return true;
    }
    return false;
}

END_NAMESPACE