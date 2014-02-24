#pragma once
//------------------------------------------------------------------------------------
// QuickSort and MergeSort implementations
//------------------------------------------------------------------------------------
template <class T>
int _qs_partition(T array[], int left, int right) {
    // generate a radom int in [l,r] and use its value as the pivot. Move the
    // pivot to the left to get it out of the way
    random_device rd;
    default_random_engine e(rd());
    uniform_int_distribution<int> dist(left, right);
    int random_pivot = dist(e);

    _swap(&array[left], &array[random_pivot]);
    T p = array[left];
    int cache = left;
    
    left++; // skip over the pivot
    while (left <= right) { 
        while (left <= right && array[left] <= p) 
            left++;

        while (left <= right && array[right] > p) 
            right--;
        
        if (left <= right) {
            _swap(&array[left], &array[right]);
            left++;
            right--;
        }
    }
    // restore the pivot to its correct position (before the right half
    // of partition)
    _swap(&array[cache], &array[right]);
    return right;
}

template<class T>
void _quicksort(T array[], int left, int right) {
    if (left < right) {
        int p = _qs_partition(array, left, right);
        _quicksort(array, left, p-1);
        _quicksort(array, p+1, right);
    }
}

template<class T>
void _merge(T array[], int left, int mid, int right) {
    int leftLen = (mid - left) + 1; // [left, mid] 
    int rightLen = (right - mid);    // [mid+1, right]
    vector<T> leftSide(&array[left], &array[left]+leftLen); // cache the left hand side
    vector<T> rightSide(&array[mid+1], &array[mid+1]+rightLen); // cache the right hand side
    
    size_t iWrite = left;
    size_t iLeft = 0;
    size_t iRight = 0;

    while (iLeft < leftSide.size() && iRight < rightSide.size()) {
        if (leftSide[iLeft] < rightSide[iRight]) {
            array[iWrite++] = leftSide[iLeft++];
        }
        else {
            array[iWrite++] = rightSide[iRight++];
        }
    }

    // copy any remainders
    while (iLeft < leftSide.size()) {
        array[iWrite++] = leftSide[iLeft++];
    }

    while (iRight < rightSide.size()) {
        array[iWrite++] = rightSide[iRight++];
    }
}
template<class T>
void _mergesort(T array[], int left, int right) {
    if (left < right) {
        int mid = (left + right)/2;
        _mergesort(array, left, mid);
        _mergesort(array, mid+1, right);
        _merge(array, left, mid, right);
    }
}
//-----------------------------------------------------------------------------
// INSERTION SORT
//-----------------------------------------------------------------------------
template<class T>
void insertion_sort(vector<T>& arr) {
    for (int i = 1; i < arr.size(); ++i) 
        for (int j = i; j >= 1; --j)
            if (arr[j-1] > arr[j]) 
                swap(arr[j-1], arr[j]);
}


//------------------------------------------------------------------------------------
string SortChars(string& s) {
    char* key = new char[s.size()]; 
    s.copy(key, s.size());
    key[s.size()] = '\0';

    _quicksort(key, 0, s.size()-1);
    
    string value(key, s.size());
    return value;
}

//
// 11.1
//
void MergeSorted(int a[], int countA, int b[], int countB) {
    _P(a, countA);
    _P(b, countB);
    
    int ia = countA - 1;
    int ib = countB - 1;
    int iwrite = countA + countB - 1;

    while ((ia >= 0) && (ib >= 0)) {
        if (a[ia] > b[ib]) {
            a[iwrite--] = a[ia--];
        } 
        else {
            a[iwrite--] = b[ib--];
        }
    }

    // copy over any remaining b's. Note that we do not need to copy
    // remaining a's as they are already in place
    while (ib >=0) {
        a[iwrite--] = b[ib--];
    }

    _P(a, countA + countB);
}

//
// 11.2
//
void GroupAnagrams(vector<string>& list) {
    unordered_map<string, vector<string>> hashSet;
    for (size_t i = 0; i < list.size(); ++i) {
        string key = SortChars(list[i]);
        hashSet[key].push_back(list[i]);
    }
    list.clear();
    for(auto iter = hashSet.begin(); iter != hashSet.end(); ++iter) {
        list.insert(list.end(), iter->second.begin(), iter->second.end());
    }
}

//
// 11.3
//
int search(int a[], int lookup, int left, int right) {
    if (left > right) return -1;

    int mid = (left + right)/2;
    if (a[mid] == lookup) return mid;

    // check if left is properly ordered. if yes and lookup is on left, search
    // left else go right
    if (a[left] < a[mid]) {
        //if (lookup >= a[left] && lookup <= a[mid]) {
        if (lookup < a[mid]) 
            return search(a, lookup, left, mid-1);
        else 
            return search(a, lookup, mid+1, right);
    }
    else if(a[mid] < a[left]) { // right hand side is proper
        //if (lookup >= a[mid] && lookup <= a[right]) {
        if (lookup > a[mid]) 
            return search(a, lookup, mid+1, right);
        else 
            return search(a, lookup, left, mid-1);
    }
    else if (a[mid] == a[left]) {
        if (a[mid] != a[right]) {
            return search(a, lookup, mid+1, right);
        }
        else { // have to search both sides
            int result = search(a, lookup, left, mid-1);
            if (result == -1) {
                return search(a, lookup, mid+1, right);
            }
            else {
                return result;
            }
        }
    }
    return -1;
}

//
// 11.5
//
bool IsEmpty(char* s) {
    return !s || 0==strlen(s);
}

int FindString(char* s[], char* target, int first, int last) {
    if (last < first) return -1;

    int mid = (first + last)/2;
    if (IsEmpty(s[mid])) {
        int left = mid-1;
        int right = mid+1;
     
        while (true) {
            if (left >= first && !IsEmpty(s[left])) {
                mid = left;
                break;
            }
            else if (right <= last && !IsEmpty(s[right])) {
                mid = right;
                break;
            }
            else if (left < first && right > last) {
                return -1;
            }
            left--;
            right++;
        }
    }

    if (strcmp(s[mid], target) == 0) {
        return mid;
    }
    else if (strcmp(s[mid], target) < 0) {
        return FindString(s, target, mid+1, last);
    }
    else {
        return FindString(s, target, first, mid-1);
    }
}

int FindString(char* s[], int len, char* target) {
    if (len <= 0 || !target || IsEmpty(target)) {
        return -1;
    }
    return FindString(s, target, 0, len-1);
}

//
// 11.6
// 
struct Location {
    int row;
    int col;
};

bool SearchGrid(int m[][5], int target, int width, int height, Location* l) {
    if (! (width > 0 && height > 0)) return false;

    // start at bottom left
    int col = 0;
    int row = height - 1;

    while (col < width && row >=0) {
        if (m[row][col]==target) {
            (*l).row = row;
            (*l).col = col;
            return true;
        }
        else if (m[row][col] < target) {
            col++;
        }
        else {
            row--;
        }
    }
    return false;
}

// "BINARY-SEARCH" solution for this - T(n) = T(n/2) + c lg n. Solution for this ends
// up as O(n) 
#pragma region helpers
bool _InBoundsOf(Point a, vvi const& grid) {
    return ((a.first >= 0 && a.second >= 0) &&
            (a.first < grid.size() && a.second < grid[0].size()));
}

bool _IsBefore(Point a, Point b) {
    return a.first <= b.first && a.second <= b.second;
}

Point _GetAverage(Point low, Point high) {
    return make_pair((low.first + high.first)/2, (low.second + high.second)/2);
}
bool _IsNullPoint(Point a) { return a == make_pair(-1, -1); }
Point _NullPoint() { return make_pair(-1, -1); }

// forward declaration
Point _PartitionAndSearch(vvi const& grid, Point origin, Point dest, Point pivot, int target);
#pragma endregion

Point SearchGridBinary(vvi const& grid, Point origin, Point dest, int target) {
    if (!_InBoundsOf(origin, grid) || !_InBoundsOf(dest, grid)) 
        return _NullPoint();

    if (grid[origin.first][origin.second] == target)
        return origin;
    else { 
        if (!_IsBefore(origin, dest))
            return _NullPoint();
    }
    /* set start to the start of diagonal and end to the end of the diagonal. Since 
     * the grid may not be square, the end of the diagonal may not equal dest */
    Point start = origin;
    int diag_dist = min(dest.first - origin.first, dest.second - origin.second);
    Point end = make_pair(start.first+diag_dist, start.second+diag_dist); 

    Point mid = make_pair(0,0);
    while(_IsBefore(start, end)) {
        mid = _GetAverage(start, end);
        if (target == grid[mid.first][mid.second])
            return mid;
        else if (target > grid[mid.first][mid.second]) {
            start.first = mid.first + 1;
            start.second = mid.second + 1;
        }
        else {
            end.first = mid.first - 1;
            end.second = mid.second - 1;
        }
    }
    return _PartitionAndSearch(grid, origin, dest, start, target);
}

Point _PartitionAndSearch(vvi const& grid, Point origin, Point dest, Point pivot,
                        int target) {
    Point lower_left_origin = make_pair(pivot.first, origin.second);
    Point lower_left_dest = make_pair(dest.first, pivot.second - 1);
    Point upper_right_origin = make_pair(origin.first, pivot.second);
    Point upper_right_dest = make_pair(pivot.first - 1, dest.second);

    Point lower_left = SearchGridBinary(grid, lower_left_origin, lower_left_dest, target);
    if (lower_left == _NullPoint()) {
        return SearchGridBinary(grid, upper_right_origin, upper_right_dest, target);
    }
    return lower_left;
}

      
//
// 11.7
//
struct htwt {
    int height;
    int weight;

    void print() {
        printf("{h:%d, w:%d} ",height, weight);
    }
};

bool operator>=(htwt lhs, htwt rhs) {
    return lhs.weight >= rhs.weight;
}

template <class t>
void printpath(vector<t>& v, vi path, int end)
{
    if(end > -1) {
        printpath(v, path, path[end]);
        v[end].print();
    }
}

template <class t>
void LIS(vector<t>& a) {
    vi DP(a.size());
    vi prev(a.size());
    int maxSeen=0;
    int bestEnd=0;

    for (size_t i = 0; i < a.size(); ++i) {
        DP[i] = 1;
        prev[i] = -1;

        for (int j = i-1; j >=0; --j) {
            if ((DP[j]+1 > DP[i]) && (a[i] >= a[j])) {
                DP[i] = DP[j]+1;
                prev[i] = j;
            }

            // maxSeen?
            if (DP[i] > maxSeen) {
                bestEnd = i;
                maxSeen = DP[i];
            }
        }
    }

    // print results max seen and previous
    printf("LIS = %d\n", maxSeen);
    printpath(a, prev, bestEnd);
    printf("\n");
}

bool HeightSorter(htwt a, htwt b) {
    return a.height < b.height;
}

void BuildCircusTower(vector<htwt>& v) {
    // sort the list by height and then get the longest increasing subsequence
    // by weight   
    sort(v.begin(), v.end(), HeightSorter); 
    LIS(v);  
}

//
// 11.8
//
class RankNode {
private:
    int m_left_size;
    unique_ptr<RankNode> m_left;
    unique_ptr<RankNode> m_right;
    int m_data;
public:
    RankNode(int data):m_data(data), m_left_size(0) {}

    void Insert(int number) {
        if (number <= m_data) {
            if (m_left.get()) m_left->Insert(number);
            else m_left.reset(new RankNode(number));
            m_left_size++;
        }
        else {
            if (m_right.get()) m_right->Insert(number);
            else m_right.reset(new RankNode(number));
        }
    }

    int GetRank(int number) {
        if (number == m_data) {
            return m_left_size;
        }
        else if (number <= m_data) {
            if (!m_left.get()) return -1;
            return m_left->GetRank(number);
        }
        else {
            if (!m_right.get()) return -1;
            return 1 + m_left_size + m_right->GetRank(number);
        }
    }
};

class Rank {
private:
    unique_ptr<RankNode> m_root;
public:
    void Track(int number) {
        if (!m_root.get()) {
            m_root.reset(new RankNode(number));
        } 
        else {
            m_root->Insert(number);
        }
    }

    int GetRank(int number) {
        if (!m_root.get()) return -1;
        return m_root->GetRank(number);
    }
};

namespace epi_10 {
//
// 10.1
//
vector<int> MergeArrays(vvi const& S) {
    auto comp = [] (ii const& lhs, ii const& rhs) { return lhs.first > rhs.first; };
    priority_queue<ii, vector<ii>, decltype(comp)> min_heap (comp);

    vi S_idx(S.size(), 0);

    // Every array in S puts its smallest element in heap
    for (int i = 0; i < S.size(); ++i) {
        if (S[i].size() > 0) {
            min_heap.emplace(S[i][0], i);
            S_idx[i] = 1;
        }
    }

    vi ret;
    while (!min_heap.empty()) {
        ii p = min_heap.top();
        ret.emplace_back(p.first);

        // add the smallest element into the heap if possible (just in 
        // case the next smallest element comes from this same file
        if (S_idx[p.second] < S[p.second].size()) {
            min_heap.emplace(S[p.second][S_idx[p.second]++], p.second);
        }
        min_heap.pop();
    }
    return ret;
}
//
// 10.2
//
vector<int> SortKIncreasingDescreasingArray(vi const& A) {
    // decompose A into a set of sorted arrays
    vvi S;
    bool is_increasing = true; // the trend that we are looking for
    int start_idx = 0;

    for (int i = 1; i < A.size(); ++i) {
        // have we found an i that breaks the trend? if yes, i will be +1 past
        // the last value in the previous trend we were looking for
        if ((A[i - 1] < A[i] && !is_increasing) ||
            (A[i - 1] >= A[i] && is_increasing)) {
            if (is_increasing) {
                S.emplace_back(A.begin() + start_idx, A.begin() + i);
            } else {
                S.emplace_back(A.rbegin() + A.size() - i,
                               A.rbegin() + A.size() - start_idx);
            }
            start_idx = i;
            is_increasing = !is_increasing; // invert the trend we are looking for
        }
    }
    
    if (start_idx < A.size()) {
        if (is_increasing) {
            S.emplace_back(A.begin() + start_idx, A.end());
        } else {
            S.emplace_back(A.rbegin(), A.rbegin() + A.size() - start_idx);
        }
    }

    // Just a place holder not real
    return MergeArrays(S);
}
//
// 10.5
// 
void FindKthLargestStream(istringstream&& sin, int k) {
    priority_queue<int, vi, greater<int>> min_heap;

    // for the first k elements, print the top
    int x;
    for (int i = 0; i < k && sin >> x; ++i) {
        min_heap.emplace(x);
        cout << min_heap.top() << endl;
    }

    while (sin >> x) {
        if (x > min_heap.top()) {
            min_heap.pop();
            min_heap.emplace(x);
        }
        cout << min_heap.top() << endl;
    }
}

//
// 10.6
// 
void ApproximateSort(istringstream&& sin, int k) {
    priority_queue<int, vi, greater<int>> min_heap;

    // first load up k elements 
    int x;
    for (int i = 0; i < k && sin >> x; ++i) 
        min_heap.push(x);

    // for every new number that comes in push it (to get to k+1, and then 
    // pop and print
    while (sin >> x) {
        min_heap.push(x);
        cout << min_heap.top() << endl;
        min_heap.pop();
    }

    // print all remaining elements
    while (!min_heap.empty()) {
        cout << min_heap.top() << endl;
        min_heap.pop();
    }
}

};

namespace epi_11 {
//
// 11.9
//
int _CompareDoubles(double a, double b) {
    double eps = numeric_limits<double>::epsilon();
    if (a < b - eps) return -1; // a is definitely smaller
    if (a > b + eps) return 1; // a is definitely larger
    return 0; // conclude equal
}

double SquareRoot_via_BinarySearch(double n) {
    double l = 0, r = 0;
    if (_CompareDoubles(n, 1.0) == -1) 
        l = n, r = 1.0;
    else
        l = 1.0, r = n;

    while (_CompareDoubles(l, r) == -1) {
        double m = l + (r - l)/2;
        double square_m = m * m;
        printf("(%f, %f)\n", m, square_m);
        if (_CompareDoubles(square_m, n) == 0) 
            return m;
        else if (_CompareDoubles(square_m, n) == -1) 
            l = m; // climb up
        else 
            r = m; // climb down
    }
    return l;
}

}