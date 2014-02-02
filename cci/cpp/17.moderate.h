#pragma once

//
// 17.1
//
// tuple is just an experimental extravagance here to make for each output 
// printfing, nothing more
tuple<int, int> swap_opt(int a , int b) {
    a = a^b;
    b = a^b;
    a = a^b;
    return make_tuple(a, b);
}

tuple<int, int> swap_opt2(int a, int b) {
    a = a - b; // diff
    b = b + a; // b + diff (=a)
    a = b - a; // a - diff (=b)
    return make_tuple(a, b);
}

//
// 17.2
//

enum Type {
    X,
    O,
    Empty
};
struct Move {
    int row;
    int col;
    Type value;
};

bool CheckRow(Move m, vector<vector<Type>>& b) {
    for (size_t col = 0; col < b.size(); ++col) {
        if (b[m.row][col] != m.value) {
            return false;
        }
    }
    return true;
}

bool CheckCol(Move m, vector<vector<Type>>& b) {
    for (size_t row = 0; row < b.size(); ++row) {
        if (b[row][m.col] != m.value) {
            return false;
        }
    }
    return true;
}

bool MoveInMainDiagonal(Move m) {
    return m.row == m.col;
}

bool MoveInSecondaryDiagonal(Move m, int size) {
    return m.row == size - 1 - m.col;
}

bool CheckMainDiagonal(Move m, vector<vector<Type>>& b) {
    for (size_t row = 0; row < b.size(); ++row) {
        if (b[row][row] != m.value) {
            return false;
        }
    }
    return true;
}

bool CheckSecondaryDiagonal(Move m, vector<vector<Type>>& b) {
    for (size_t row = 0; row < b.size(); ++row) {
        if (b[b.size()-row-1][row] != m.value) {
            return false;
        }
    }
    return true;
}

bool IsWinningMove(Move m, vector<vector<Type>>& b) {
    assert(b.size() == b[0].size());
    assert(m.value != Empty);

    return (CheckRow(m, b) || CheckCol(m, b) ||
        (MoveInMainDiagonal(m) && CheckMainDiagonal(m, b)) ||
        (MoveInSecondaryDiagonal(m, b.size()) && CheckSecondaryDiagonal(m, b)));
    
}

//
// 17.3
// 
int CountZerosBest(int num) {
    if (num < 0) return -1;
    int count = 0;
    for (int i = 5; num / i > 0; i *= 5) {
        count += num / i;
    }
    return count;
}

int CountFactorsOf5(int num) {
    int count = 0;
    while (num % 5 == 0) { // while still divisible by 5
        count++;
        num /= 5;
    }
    return count;
}

int CountZerosGood(int num) {
    if (num < 0) return -1;
    int count = 0;
    for (int i = 2; i <= num; ++i) {
        count += CountFactorsOf5(i);
    }
    return count;
}

//
// 17.4
//
int invert(int bit) { return 1^bit; }
int get_sign(int n) { return invert((n >> 31) & 1); }

int safe_max_opt(int a, int b) {
    int sa = get_sign(a);
    int sb = get_sign(b);
    int sd = get_sign(a - b);

    int use_sa = sa^sb;
    int s = (use_sa*sa) + (invert(use_sa) * sd);
    int inv_s = invert(s);

    return (a * s) + (b * inv_s);
}
//
// 17.5
//
struct Result {
    int hits;
    int pseudo_hits;
};
Result NullResult = {-1, -1};

int get_code(char c) {
    switch(c) {
    case 'R': return 0;
    case 'G': return 1;
    case 'B': return 2;
    case 'Y': return 3;
    default: assert(false); return -1;
    }
}
#define MAX_COLORS 4
Result estimate(string guess, string solution){
    if (guess.size() != solution.size() || guess.size() != MAX_COLORS)
        return NullResult;
    vector<int> pseudo_hit_frequency(MAX_COLORS, 0);
    
    Result res = {0,0};
    for (int i = 0; i < guess.size(); ++i){
        if (guess[i] == solution[i])
            res.hits++;
        else 
            // if not a hit, track count of appearances in solution for tracking 
            // purposed of evaluating pseudo hits
            pseudo_hit_frequency[get_code(solution[i])]++;
    }

    // get the pseudo_hits
    for (int i = 0; i < guess.size(); ++i) {
        int code = get_code(guess[i]);
        if (code >=0 && pseudo_hit_frequency[code] > 0 && guess[i] != solution[i]) {
            res.pseudo_hits++;
            pseudo_hit_frequency[code]--;
        }
    }
    return res;
}
//
//
// 17.6
//
int GetLeftEnd(vector<int> const& a) {
    for (int i = 1; i < a.size(); ++i) {
        if (a[i] < a[i-1]) {
            return i-1;
        }
    }
    return a.size() - 1;
}

int GetRightStart(vector<int> const& a) {
    for (int i = a.size() - 2; i >= 0; --i) {
        if (a[i] > a[i+1]) {
            return i+1;
        }
    }
    return 0;
}

void GetMinMaxInRange(vector<int> const& a, int start, int end, 
                      int& minI, int& maxI) {
    minI = start;
    maxI = start;

    for (int i = start; i <= end; ++i) {
        if (a[i] < a[minI]) {
            minI = i;
        }
        if (a[i] > a[maxI]) {
            maxI = i;
        }
    }
}
    
void GetSortRange(vector<int> const& a) {
    assert(a.size() > 1);

    int el = GetLeftEnd(a);
    int sr = GetRightStart(a);

    if (el == a.size() - 1) return; // sorted
   
    int minI = -1;
    int maxI = -1;
    GetMinMaxInRange(a, el+1, sr-1, minI, maxI);
    cout << "middle_min=" << a[minI] << " middle_max=" << a[maxI] << endl;

    // adjust the left;
    int i=0;
    for (i = el; i >=0; --i) {
        if (a[i] <= a[minI]) {
            minI = i+1;
            break;
        }
    }
    if (i == -1) minI=0;

    // adjust the right
    for (i = sr; i < a.size(); ++i) {
        if (a[i] >= a[maxI]) {
            maxI = i-1;
            break;
        }
    }
    if (i == a.size()) maxI = a.size() - 1;

    cout << "m=" << minI << " n=" << maxI << endl;
}
//
// 17.7
//
string digits[] = {"One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten"};
string teens[] = {"Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
string tens[] = {"Ten", "Twenty", "Thirty", "Fourty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
string bigs[] = {"", "Thousand", "Million"};
string _NumToString100(int number) {
    string str = "";

    // convert hundreds place 
    if (number >= 100) {
        str += digits[number / 100 - 1] + " Hundred ";
        number %=100;
    }

    // convert tens place
    if (number >= 11 && number <= 19) 
        return str + teens[number - 11] + " ";
    else if (number == 10 || number >= 20){
        str += tens[number / 10 - 1] + " ";
        number %= 10;
    }

    // convert ones place
    if (number >= 1 && number <= 9) 
        str += digits[number - 1] + " ";

    return str;
}

string NumToString(int number) {
    if (number == 0)
        return "Zero";
    else if (number < 0)
        return "Negative " + NumToString(-1*number);

    int count = 0;
    string str = "";

    // limited to millions
    while (number > 0) {
        if (number % 1000 != 0) {
            str = _NumToString100(number % 1000) + bigs[count] + " " + str;
        }
        number /= 1000;
        count++;
    }
    return str;
}






//
// 17.8
//
void PrintMaxSumBest(vector<int> const& v) {
    int max_sum = numeric_limits<int>::min();
    int sum = 0;
    int local_start = 0;
    int first = 0;
    int last = -1; // will be useful in flagging all negative case

    for (int i = 0; i < v.size(); ++i) {
        sum += v[i];

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
        cout << "sum=" << max_sum << " start=" << first << " end=" << last << endl;
        return;
    }

    // else we have hit the all negative case. Find the largest negative
    // number
    int largest_negative = v[0];
    first = last = 0;
    for (int i = 1; i < v.size(); ++i) {
        if (v[i] > largest_negative) {
            largest_negative = v[i];
            first = last = i;
        }
    }
    cout << "v contained all negative items. best sum =" 
             << largest_negative << " at " << first << endl;
    
}

int _SumRange(vector<int> const& v, int start, int end) {
    int sum = 0;
    for (int i = start; i <= end; ++i) {
        sum += v[i];
    }
    return sum;
}

void PrintMaxSumNaive(vector<int> const& v) {
    int bestStart = -1;
    int bestEnd = -1;
    int bestSum = numeric_limits<int>::min();

    for (int i = 0; i < v.size(); ++i) {
        for (int j = i; j >= 0; --j) {
            int sum = _SumRange(v, j, i);
            if (sum > bestSum) {
                bestSum = sum;
                bestStart = j;
                bestEnd = i;
            }
        }
    }

    cout << "BestSum=" << bestSum << " start=" << bestStart << " end=" << bestEnd << endl;
}

//
// 17.9
// 
map<string, int> ft;
void Trim(string& /*w*/) {
}

void SetupFrequencyTable(vector<string>& book) {
    for (int i = 0; i < book.size(); ++i) {
        string word(book[i]);
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        Trim(word);
        ft[word]++;
    }
}

int LookupWord(string& w) {
    if (w.empty()) return -1;
    if (ft.empty()) return -1;

    string lookup(w);
    std::transform(w.begin(), w.end(), lookup.begin(), ::tolower);
    Trim(lookup);

    auto iter = ft.find(lookup);
    if (iter == ft.end()) {
        return 0;
    }
    else {
        return ft[lookup];
    }
}
//
// 17.11
//
int _rand5() { return rand() % 5; }

int rand7() {
    while (true) {
        int num = 5 * _rand5() + _rand5();
        while (num < 21)
            return num % 7;
    }
}
int rand7_cool() {
    int numspace[5][5] = {
        {0,1,2,3,4},
        {5,6,0,1,2},
        {3,4,5,6,0},
        {1,2,3,4,5},
        {6,0,0,0,0},
    };
    int result = 0;
    while (result == 0) {
        int i = _rand5();
        int j = _rand5();
        result = numspace[i][j];
    }
    return result;
}

//
// 17.12
//
// This is order N if there are no duplicates. If there are duplicates
// then it goes up linearly by a factor related to the number of duplicates
//
// ON THE QUESTION OF DUPLICATES: seems to only be relevant if we are asked
// for the INDEXES of pairs that contain values that add up to value. Should
// avoid the duplicate handling logic unless it makes sense. Space should be 
// the consideration
void PrintPairSum_O_N_UsesHashTable_HandlesDuplicates(vector<int>& v, int sum) {
    unordered_map<int, int> hm; // <complement, duplicate_count>
    for (int i = 0; i < v.size(); ++i) {
        int complement = sum - v[i]; // can overflow. Be ready to address that
        auto it = hm.find(complement);
        if (it != hm.end()) {
            int duplicates = it->second;
            while (duplicates > 0) {
                cout << "{" << v[i] << "," << complement << "}" << endl;
                duplicates--;
            }
        }
        hm[v[i]]++;
    }
}
//
// 
//
void PrintPairSum_O_NLogN_InPlace_NoDuplicates(int a[], int len, int sum) {
    // sort the array nlogn
    _mergesort(a, 0, len-1);

    int start = 0;
    int end = len - 1;

    while (start < end) {
        int pair_sum = a[start] + a[end];

        if (sum == pair_sum) {
            cout << "{" << a[start] << "," << a[end] << "}" << endl;
            // can probably be modified to handle duplicates here by incrementing
            // start and end separately
            start++;
            end--;
        }
        else if (pair_sum < sum) {
            // we need to see a large number to have a shot, therefore the only
            // way is to increase start (which goes onto a larger number
            start++;
        }
        else {
            // if we have already exceeded sum, we have to try smaller numbers
            // only way to do this is to decrement end
            end--;
        }
    }
}

int ModifiedBinSearch(int a[], int target, int start, int last) {
 
    if (start > last) return 0;

    int mid = (start + last)/2;
    if (a[mid] == target) {
        // check immediate left and right for all dupes. Note that all dupes
        // of target MUST be bounded by start and last (proof - if this was 
        // not true, there was a dupe of target at start-1 or last+1. But
        // start-1 / last+1 was the mid in the the previous recursion stack 
        // and so we would have found it already so that cannot be true. Proof by
        // contradiction.
        int count = 1; 
        int left = mid - 1;
        int right = mid + 1;
        while (left >= start) {
            if (a[left]==target)  {
                count++;
            }
            left--;
        }
        while (right <= last) {
            if (a[right]==target) {
                count++;
            }
            right++;
        }
        return count;
    }
    else if (target < a[mid]) 
    {
        return ModifiedBinSearch(a, target, start, mid-1);
    }
    else {
        return ModifiedBinSearch(a, target, mid+1, last);
    }
}

void PrintPairSum_O_NLogN_InPlace_HandlesDuplicates(
    int a[], int len, int sum) {
    
    // sort the array nlogn
    _mergesort(a, 0, len-1);

    for (int i = 0; i < len; ++i) {
        int complement = sum - a[i];
        int complements_count = ModifiedBinSearch(a, complement, i+1, len-1);
        for (int j = 1; j <=complements_count; ++j) {
            cout << "{" << a[i] << "," << complement << "}" << endl;
        }
    }
}

//
// 17.13
//
struct BiNode {
    BiNode* node1;
    BiNode* node2;
    int data;

    BiNode(int data):data(data), node1(nullptr), node2(nullptr) {}

    void Print() {
        _PrintInOrder();
        cout << endl;
    }

    static BiNode* MakeFromSortedArray(int a[], int first, int last) {
        if (first > last) return nullptr;

        int mid = (first + last)/2;
        BiNode* root = new BiNode(a[mid]);
        root->node1 = MakeFromSortedArray(a, first, mid-1);
        root->node2 = MakeFromSortedArray(a, mid+1, last);
        return root;
    }

private:
    void _PrintInOrder() {
        if (node1) node1->_PrintInOrder();
        cout << data << " " ;
        if (node2) node2->_PrintInOrder();
    }
};

void _PrintAsList(BiNode* first, BiNode* last) {
    cout << "List Forward:" << endl;
    while (first) {
        cout << first->data << " ";
        first = first->node2;
    }
    cout << endl;

    cout << "List Backward:" << endl;
    while (last) {
        cout << last->data << " ";
        last = last->node1;
    }
    cout << endl;
}

void BST2DLL(BiNode* root, BiNode *& head, BiNode *& tail) {
    if (!root) return;

    BiNode* lh = nullptr, *lt = nullptr;
    BiNode* rh = nullptr, *rt = nullptr;
    BST2DLL(root->node1, lh, lt);
    BST2DLL(root->node2, rh, rt);

    if (lh) {
        head = lh; 
        lt->node2 = root; // join left list to head. 
        root->node1 = lt;
        tail = root;            // root is now the last element
    }

    if (!head) { // left list was empty
        head = root;
        tail = root;
    }

    if (rh) {
        tail->node2 = rh;
        rh->node1 = tail;
        tail = rt;
    }
    return;
}

BiNode* DLL2BST(BiNode *& list, int start, int last) {
    if (start > last) return nullptr;

    int mid = (start+last)/2;
    BiNode* left = DLL2BST(list, start, mid-1);
    
    BiNode* root = list;
    root->node1 = left;
    list = list->node2;
    BiNode* right = DLL2BST(list, mid+1, last);
    
    root->node2 = right;
    return root;
}

//
// 17.14
//
string& MakeUpper(string &s) { 
    std::transform(s.begin(), s.end(), s.begin(), ::toupper); 
    return s;
}

void SetDict(Trie& dict) {
    dict.Insert("cat");
    dict.Insert("dog");
}

struct ParseResult { 
    int invalid; 
    string parsed; 
    ParseResult():invalid(numeric_limits<int>::max()) {}
    ParseResult(int invalid, string& parsed):invalid(invalid), parsed(parsed) {}
    static ParseResult& Min(ParseResult& lhs, ParseResult& rhs) {
        return lhs.invalid < rhs.invalid  ? lhs : rhs;
    }
    static void _PrintIndent(int indent) {
        for (int i = 0; i < indent; ++i) {
            cout << " ";
        }
    }
    void Print(char* c=" ", int indent=0) {
        
        if (!isspace(c[0])) {
            _PrintIndent(indent);
            cout << c << endl;
        }
        
        if (parsed.empty()) return;

        _PrintIndent(indent);
        cout << "inv:" << invalid << " parsed:" << parsed << endl;
    }
};

struct PrintScope {
    int indent;
    char* message;
    char* opt;
    static void _print_indent(int indent) {
        for (int i = 0; i < indent; ++i) {
            cout << " ";
        }
    }
    PrintScope(int indent, char*message, char* opt=" "):indent(indent),message(message), opt(opt) {
        _print_indent(indent);
        cout << "Entering " << message;
        if (!isspace(opt[0])) {
            cout << opt ;
        } 
        cout << endl;
    }
    ~PrintScope() {
        _print_indent(indent);
        cout << "Leaving " << message;
        if (!isspace(opt[0])) {
            cout << opt ;
        } 
        cout << endl;
    }

    static void PrintRecursionTree(int indent, int f, int l) {
        _print_indent(indent);
        cout << "f=" << f << " l=" << l << endl;
    }
};

typedef unordered_map<int, ParseResult> Cache;
ParseResult ParseWords(string const& w, int f, int l, Trie const& dict, Cache& cache, int indent=0) {
    if (l >= w.size()) {
        string parsed = "";
        if (f < w.size()) {
            string upper(w.substr(f));
            parsed.assign(MakeUpper(upper));
        }
        ParseResult tmp(l - f, parsed);
        return tmp;
    }

    if (cache.find(f) != cache.end()) {
        return cache[f];
    }

    string current_word = w.substr(f, l-f+1);
    bool valid_partial = dict.IsPrefix(current_word);
    bool valid_exact = valid_partial && dict.Contains(current_word);

    // jump past current word (insert space after current word) 
    ParseResult bestExact = ParseWords(w, l+1, l+1, dict, cache, indent+1);
    if (valid_exact) {
        string tmp(current_word + " " + bestExact.parsed);
        bestExact.parsed.swap(tmp);
    }
    else {
        bestExact.invalid += current_word.size();
        string tmp(MakeUpper(current_word) + " " + bestExact.parsed);
        bestExact.parsed.swap(tmp);
    }

    // extend current word using another letter
    ParseResult best;
    if (valid_partial) {
        ParseResult bestExtend = ParseWords(w, f, l+1, dict, cache, indent+1);
        best = ParseResult::Min(bestExact, bestExtend);
    }
    else {
        best = bestExact;
    }

    cache[f] = best;
    return best;
}

ParseResult ParseWords(string const& w) {
    Trie dict;
    SetDict(dict);
    Cache cache;
    ParseResult result = ParseWords(w, 0, 0, dict, cache);
    return result;
}

        




