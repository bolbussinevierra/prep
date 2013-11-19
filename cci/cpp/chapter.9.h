#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

//
// 9.1
//
int ways(int n) {
    if (n < 0) {
        return 0;
    } 
    // This took a while to get why its true. Can also list ALL the base cases
    // instead of this. Read this is having been the "steps remaining equalled
    // the number of steps that were to be taken" hence 0
    else if (n == 0) {
        return 1; 
    }
    else {
        return ways(n - 1) + ways(n - 2) + ways(n - 3);
    }
}

//
// 9.2
//
int compute_paths(int width, int height) {
    // BTB - ** IMPORTANT **
    // [0][0] is not involved in the math which is why we allocate width+1
    // height+1
    vector<vector<int>> result(width+1, vector<int>(height+1));

    // initialize [1,0] to [width,0] = 1
    for (int x = 1; x <= width; ++x) {
        result[x][0] = 1;
    }
    // initialize [0, 1] to [0, height,] to 1
    for (int y = 1; y <= height; ++y) {
        result[0][y] = 1;
    }

    // calculate all other values from adjacent values
    for (int x = 1; x <= width; ++x) {
        for (int y = 1; y <= height; ++y) {
            result[x][y] = result[x][y-1] + result[x-1][y];
        }
    }
    return result[width][height];
}

//
// 9.2 follow up
//
bool operator<(POINT const& a, POINT const& b){
    return (a.x < b.x) && (a.y < b.y);
}

bool CanMoveTo(int x, int y) {
    if ((x == 2) && (y <= 2)) { return false; } else { return true; }
}


bool FindPathTo(int ex, int ey, vector<POINT>& path, map<POINT, bool>& cache) {
    POINT p = {ex, ey};
    bool success = false;

    std::map<POINT,bool>::iterator it = cache.find(p);
    if (cache.end() != it)
    {
        success = it->second;
    }
    else if ((ex == 0) && (ey == 0)) { // we have confirmed all the way back!
        success = true;
    }
    else {
        if ((ex >= 1) && CanMoveTo(ex-1, ey)) {
            success = FindPathTo(ex-1, ey, path, cache);
        }
        if (!success && (ey >= 1) && CanMoveTo(ex, ey-1)) {
            success = FindPathTo(ex, ey-1, path, cache);
        }
    }

    if (success) {
        printf("Next = (%d, %d)\n", p.x, p.y);
        path.push_back(p); // we have confirmed that this is not a dead end
    }
    cache.insert(pair<POINT, bool>(p, success));
    return success;
}

bool FindPathTo(int ex, int ey) {
    vector<POINT> path;
    map<POINT, bool> cache;
    return FindPathTo(ex, ey, path, cache);
}

//
// 9.3
//
void Subsets(vector<int>& items, int start, vector<vector<int>>& sets) {
    if(start == items.size()){
        vector<int> empty;
        sets.push_back(empty);
    } else {
        Subsets(items, start+1, sets); // get the rest of the sets
        size_t existingSets = sets.size();
        for (size_t i = 0; i < existingSets; ++i) {
            vector<int> cloneSet(sets[i]); // clone the previous et
            cloneSet.push_back(items[start]);   // add the new item
            sets.push_back(cloneSet);           // add the cloned and expanded set to list
        }
    }
}
void PrintSets(vector<vector<int>>& sets) {
    for (size_t i = 0; i < sets.size(); ++i) {
        vector<int> set = sets[i];
        if (set.empty()) {
            printf("<empty> ");
        }
        else {
            for (size_t j = 0; j < set.size(); ++j) {
                printf("%d ", set[j]);
            }
        }
        printf("\n");
    }
}

void MapBinaryToSet(int binSet, vector<int>& items, vector<int>& set) {
    for (size_t i = 0; i < items.size(); ++i) {
        if ((1 << i) & binSet) {
            set.push_back(items[i]);
        }
    }
}

void SubsetsBinary(vector<int>& items, vector<vector<int>>& sets) {
    assert(32 >= items.size()); // limited by size of integer .. can use long (or long ass int array)
    int maxSets = (1 << items.size());  // 2^(n)

    for (int i = 0; i < maxSets; ++i) {
        vector<int> newSet; // empty set added when i == 0 (empty newSet)
        MapBinaryToSet(i, items, newSet);
        sets.push_back(newSet);
    }
}

void SubsetsBinary(int arr[], int length) {
    vector<int> items(arr, arr+length);
    vector<vector<int>> sets;
    SubsetsBinary(items, sets);
    PrintSets(sets);
    printf("Items=[%d], Subsets=[%d]\n", length, sets.size());
}

void SubsetsIterative(int arr[], int length) {
    vector<vector<int>> sets;
    vector<int> empty;
    sets.push_back(empty);
    
    for (int i = 0; i < length; ++i) {
        size_t existingSets = sets.size();
        for (size_t v = 0; v < existingSets; ++v) {
            vector<int> newSet(sets[v]);
            newSet.push_back(arr[i]);
            sets.push_back(newSet);
        }
    }

    PrintSets(sets);
    printf("Items=[%d], Subsets=[%d]\n", length, sets.size());
}

void Subsets(int arr[], int length) {
    vector<int> items(arr, arr+length);
    vector<vector<int>> sets;
    Subsets(items, 0, sets);
    PrintSets(sets);
    printf("Items=[%d], Subsets=[%d]\n", length, sets.size());
}

//
// 9.5
//
void PrintVector(vector<string>& p, char* title) {
    for (size_t i = 0; i < p.size(); ++i) {
        printf("%s\n", p[i].c_str());
    }
    printf("%s=[%d]\n", title, p.size());
}

void Combine(string& s, char c, int at, string& out) {
    size_t from = 0;
    size_t to = 0;
    while (to < s.size() + 1) {
        if (to == at) {
            out[to++] = c;
        }
        else {
            out[to++] = s[from++];
        }
    }
}

void Expand(string& s, char c, vector<string>& out) {
    size_t newLen = s.size() + 1;
    for (size_t at = 0; at < newLen; ++at) {
        string newS;
        newS.resize(newLen);
        Combine(s, c, at, newS);
        out.push_back(newS);
    }
}

void GetPermutations(string& s, size_t start, vector<string>& perms){
    assert(start < s.length());
    if (start == s.length() - 1) {
        string newP;
        newP.push_back(s[start]);
        perms.push_back(newP);
    }
    else {
        vector<string> otherPerms;
        GetPermutations(s, start+1, otherPerms);
        for (size_t i = 0; i < otherPerms.size(); ++i) {
            Expand(otherPerms[i], s[start], perms);
        }
    }
}

void GetPermutationsIter(string& s, vector<string>& out) {
    for(size_t start=0; start < s.size(); ++start) {
        if (start == 0) {
            string newP;
            newP.push_back(s[start]);
            out.push_back(newP);
        }
        else {
            vector<string> newPerms;
            for (size_t i=0; i < out.size(); ++i) {
                Expand(out[i], s[start], newPerms);
            }
            out.swap(newPerms);
        }
    }
}

void GetPermutations(string& s) {
    vector<string> perms;
    GetPermutations(s, 0, perms);
    PrintVector(perms, "Permutations");
}

void GetPermutationsIter(string& s) {
    vector<string> perms;
    GetPermutationsIter(s, perms);
    PrintVector(perms, "Permutations");
}

//
// 9.6
//

struct trace {
    int _depth;
    const char * _title;
    int _lr;
    int _rr;
    const char * _s;
    int _ct;
    void print() {
        printf("depth:%d, title=%s | lr=%d, rr=%d, ct=%d, s=%s \n",
            _depth, _title, _lr, _rr, _ct, _s);
    }
    void set(int depth, char* title, int lr, int rr, int ct, const char*s){
        _depth = depth;
        _title = title;
        _lr = lr;
        _rr=rr;
        _ct = ct;
        _s = s;
    }
};

int combo_num = 0;
void PrintParen(int leftRem, int rightRem, string& str, int count) {             
    if (leftRem == 0 && rightRem == 0) {
        printf("%d:%s \n", ++combo_num, str.c_str());
    }
    else {
        if (leftRem > 0) {
            str[count] = '(';
            PrintParen(leftRem-1, rightRem, str, count+1);
        }
        if (rightRem > leftRem) {
            str[count] = ')';
            PrintParen(leftRem, rightRem-1, str, count+1);
        }
    }
}

void PrintParens(int count) {
    string str;
    str.resize(count*2);
    combo_num = 0;
    PrintParen(count, count, str, 0);
}
