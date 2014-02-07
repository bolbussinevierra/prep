#pragma once

// ---------------------------------------------------------------------
typedef unordered_map<string, string> TranslationTable;
void GetTranslationTable(TranslationTable& dict) {
    dict["a"] = "t1";
    dict["aa"] = "t2";
    dict["ab"] = "t3";
    dict["b"] = "t4";
    dict["abc"] = "t5";
}

void AddTranslation(string const& token, TranslationTable const& t, string& out) {
    string const& trans = t.find(token)->second;
    out.append(" ");
    out.append(trans);
}
void AddLiteral(string const& token, string& out) {
    out.append(" ");
    out.append(token);
}

HRESULT Transliterate(string const& in, string& out) {
    if (in.empty()) return S_OK;

    TranslationTable table;
    GetTranslationTable(table);

    int ts = 0;
    int te = 0;
    int const k_last = in.size() - 1;
    while (te <= k_last) {
        int token_length = te-ts+1;
        string token = in.substr(ts, token_length);
        if (table.find(token) != table.end()) { // found a translation!
            // If we are the end, translate this token and we are done. Else, 
            // keep going greedily and see we can to see if it we can match an even 
            // longer translation
            if (te == k_last) { 
                // we have reached the end. Output this last translation and we are done
                AddTranslation(token, table, out);
                return S_OK;
            }
            else {
                te++;
            }
        }
        else {
            // we are either at a single character we cannot translate of have gone one past
            // the longest matching translation. print it out
            if (token_length > 1) {
                token_length--; // back up one
                token = in.substr(ts, token_length);
                AddTranslation(token, table, out);
                te = ts+token_length; // one past the end of previous token
                ts = te;
            }
            else {
                // token is a single character we cannot translate;
                AddLiteral(token, out);
                te++;
                ts = te;
            }
        }
    }
    return S_OK;
}
// -----------------------------------------------------------------------------------
// FINDING A WORD IN A MATRIX. PATH CAN MOVE ANY DIRECTION BUT CANNOT REUSE AN ELEMENT
// (LETTER COORDINATE M(i,j)) in the path

// We use dfs
int dr[] = {1, 1,1,-1,-1,-1, 0, 0 }; // 3 in row above, 3 row below, 2  same row;
int dc[] = {-1,0,1,-1, 0, 1, -1, 1}; 
static_assert(AS(dr) == AS(dc), "dr and dc should always be same size");
int const k_count_adjacent = AS(dr);

bool WithinBounds(int x, int size) { return x >=0 && x < size; }

void dfs_find(int char_at, string const& w, int row, int col, 
             vvc const& table, vvbool& visited, vector<Point>& path) {
    if (!WithinBounds(row, table.size()) || !WithinBounds(col, table[0].size()))
        return;
  
    if (visited[row][col])   // do not re-use a grid in the same path
        return;
    else 
        visited[row][col]=true;

    // else keep going in dfs manner if we are not at the end of the word
    if (table[row][col] == w[char_at]) {
        path[char_at] = make_pair(row, col);

        if (char_at == w.size() - 1) {
            for_each(path.begin(), path.end(), Print);
            cout << endl;
        }
        else {
            for (int adj = 0; adj < k_count_adjacent; ++adj) 
                dfs_find(char_at+1, w, row+dr[adj], col+dc[adj], table, visited, path); 
        }
    }
}

void PrintLetterPaths(string const& w, vvc const& table) {
    if (w.empty()) return;
 
    int rows = table.size();
    int cols = table[0].size();

    string lower_w(w.size(), 0);
    std::transform(w.begin(), w.end(), lower_w.begin(), ::tolower);

    for(int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (table[i][j] == *lower_w.begin()) {
                vector<Point> path(lower_w.size());
                vvbool visited(rows, vector<bool>(cols, false));
                dfs_find(0, lower_w, i, j, table, visited, path);
            }
        }
    }
}
// ---------------------------------------------------------------------
// GIVEN A TABLE CHECK IF IT CONTAINS A WORD IN ANY ORIENTATION. AN GRID
// BOX CAN BE REUSED (IE CYCLES ARE ALLOWED)
struct track {
    bool match;
    Point previous;
};
static track const k_null = {false, make_pair(-1,-1)};
typedef vector<vector<track>> TrackTable;
bool NeighborIsSet(vector<TrackTable> const& dp, int nbor_char, int row, int col, 
                 Point& prev) {
    
    int const k_rows = dp[0].size();
    int const k_cols = dp[0][0].size();

    for (int adj = 0; adj < k_count_adjacent; ++adj) {
        int nbor_row = row+dr[adj];
        int nbor_col = col+dc[adj];
        if (WithinBounds(nbor_row, k_rows) && WithinBounds(nbor_col, k_cols)) {
            if (dp[nbor_char][nbor_row][nbor_col].match) {
                prev = make_pair(nbor_row, nbor_col);
                return true;
            }
        }
    }
    return false;
}
void PrintPath(vector<TrackTable>const& table, vvc const& char_grid, 
              int pos, int row, int col) {
    if (pos == -1) return;
    PrintPath(table, char_grid, pos-1, 
             table[pos][row][col].previous.first, // backpointer previous row
             table[pos][row][col].previous.second); // backpointer previous col
    cout << "[" << row << "," << col << "]" ;
}
void ContainsWordDP(string const& w, vvc const& char_grid) {
    // table[pos][row][col].match = true if char_grid[row][col] == w_pos and
    //                             table[pos-1][x][y].match == true
    //                             where char_grid [x][y] is a valid neighbor of
    //                             char_grid[row][col]. (There are 8 max poosible neighbors)
    // return true if table[w.size() - 1][i][j] is true for any valid i,j
    //
    int const k_rows = char_grid.size();
    int const k_cols = char_grid[0].size();
    string lower_w(w.size(), 0);
    std::transform(w.begin(), w.end(), lower_w.begin(), ::tolower);

    vector<TrackTable> table(lower_w.size(), TrackTable(k_rows, vector<track>(k_cols, k_null)));

    for (int pos = 0; pos < lower_w.size(); ++pos) {
        for (int row = 0; row < k_rows; ++row) {
            for (int col = 0; col < k_cols; ++col) {
                bool set_on = char_grid[row][col] == lower_w[pos]; 
                if (pos > 0 && set_on) {
                    Point prev;
                    set_on = NeighborIsSet(table, pos-1, row, col, prev);
                    if (set_on) {
                        table[pos][row][col].previous = prev;
                    }
                }
                table[pos][row][col].match = set_on;
            }
        }
    }

    // now find every instance that matches and print its path
    for (int row = 0; row < k_rows; ++row) {
        for (int col = 0; col < k_cols; ++col) {
            if (table[w.size()-1][row][col].match) {
                PrintPath(table, char_grid, w.size()-1, row, col);
                cout << endl;
            }
        }
    }
}

/* 
    Given a list of integers, find a number that does not have a pair
    1 2 1 3 5 -3 -2 6 2 -3 5 -2
    Here 3 does not have the pair (6 does not have one either)
*/

void PrintNumberMissingPair(vi const& v) {
    unordered_set<int> set;
    for (int a : v) {
        // Toggle Insert and Remove. Whatever is less was missing a pair
        if (set.find(a) != set.end())
            set.erase(a);
        else 
            set.insert(a);
    }
    cout << *set.begin() << " is missing a pair" << endl;
}

 /*
    Given a M * N array, find one path from a cell to another cell. Rules
    1) Only up and right traversal is allowed
    2) Some cells could be marked as “Walls”. There’s no path through
    through those cells

    SAME AS CCI 9.2

    */
Point Up(Point const& p) { return make_pair(p.first - 1, p.second); }
Point Right(Point const& p) { return make_pair(p.first, p.second + 1); }
int Row(Point const& p) { return p.first; }
int Col(Point const& p) { return p.second; }

bool IsWall(Point const& p) { 
    Point walls[] = {
        make_pair(0,4),
    };
    for(Point w : walls) 
        if (w == p) 
            return true;

    return false;
}

// specialize hash for Point
namespace std {
    template<>
    class hash<Point> {
    public:
        size_t operator()(Point const& p) const {
            size_t h = hash<int>()(p.first ^ hash<int>()(p.second));
            //cout << "hash(Point(" << p.first << "," << p.second << ")) is " << h 
            //    << endl;
            return h;
        }
    };
};

typedef unordered_map<Point, bool> PathCache;


bool FindPath(Point const& s, Point const& e, list<Point>& path, PathCache& c) {
    bool success = false;
    if (c.find(s) != c.end()) {
        success = c[s];
    } 
    else if (s == e) {
        success = true;
    }
    else {
        if (Row(s) > Row(e) && !IsWall(Up(s))) 
            success = FindPath(Up(s), e, path, c);

        if (!success && Col(s) < Col(e) && !IsWall(Right(s))) 
            success = FindPath(Right(s), e, path, c);
    }

    if (success) 
        path.push_front(s); // instead of push_back because we will be pushing in reverse order

    c[s] = success;
    return success;
}

bool FindPath(Point const& s, Point const& e, list<Point>& path) {
    PathCache c;
    return FindPath(s, e, path, c);
}

/*
How would you clone a doubly linked list which has Next and Random
pointer. Next points to the next node whereas the Random node points to
any random node
*/
struct Link {
    int data;
    shared_ptr<Link> next;
    weak_ptr<Link> random;
};

shared_ptr<Link> CopyList_O_1_Space_O_N_Speed(Link* original) {
    if (!original) return nullptr;
    // 1st Pass:
    // make new nodes and interleave them between the nodes of the original list
    // by changing the next pointers ie:
    //      [1]->[copy of 1]->[2]->[copy of 2]->[3]->[copy of 3] ....
    // during this pass, we will also set the data of new nodes to match the old node
    // being copied.
    Link* node = original;
    while (node) {
        shared_ptr<Link> new_node = make_shared<Link>();
        new_node->data = node->data;
        new_node->next = node->next;
        node->next = new_node;
        node = node->next->next.get(); // skipping the "copy of" node just inserted
    }

    // 2nd Pass:
    // now go through and set the random ptr of the new nodes correctly.
    // i refers to a node on the original list and j the matching node on the new
    // list
    shared_ptr<Link> new_head = original->next; // i.e "copy of 1" is head of new list
    for (Link *i = original; i; i=i->next->next.get()) {
        Link *j = i->next.get(); // new nodes interleave original nodes
        j->random = i->random.lock()->next;
    }

    // 3rd Pass:
    // Restore the original list
    Link* new_node = new_head.get();
    node = original;
    while (node) {
        node->next = new_node->next;
        
        if (node->next)
            new_node->next = node->next->next;

        node = node->next.get();
        new_node = new_node->next.get();
    }

    return new_head;
}

shared_ptr<Link> CopyList_O_N_Space_O_N_Speed(Link* head) {
    if (!head) return nullptr;
    // create new nodes and make them all the old nodes to a hash map
    unordered_map<Link*, shared_ptr<Link>> node_map;
    for (Link * current = head; current; current = current->next.get()) {
        shared_ptr<Link> node = make_shared<Link>();
        node->data = current->data;
        node_map[current] = node;
    }

    // next pass, copy over the next and random pointer
    for (Link* current = head; current; current = current->next.get()) {
        shared_ptr<Link> node = node_map[current];
        node->next = node_map[current->next.get()];
        node->random = node_map[current->random.lock().get()];
    }
    return node_map[head]; // head of the new list
}

void PrintList(Link* head) {
    for (Link * current = head; current; current = current->next.get()) {
        cout << current->data << "[n:";
        if (current->next) 
            cout << current->next->data;
        else 
            cout << "_";
        cout << " r:";
        if (current->random.lock()) 
            cout << current->random.lock()->data;
        else 
            cout << "_";

        cout << "] ";
    }
    cout << endl;
}

shared_ptr<Link> MakeLinkList(vi const& v) {
    vector<shared_ptr<Link>> nodes;
    for (int a : v) {
        shared_ptr<Link> node = make_shared<Link>();
        node->data = a;
        nodes.push_back(node);
    }
    // create next and random links
    for (int i = 0; i < nodes.size(); ++i) {
        if (i+1 < nodes.size()) 
            nodes[i]->next = nodes[i+1];

        int r = rand() % nodes.size();
        nodes[i]->random = nodes[r];
    }

    return nodes[0];
};

/*
    Given a Matix (two dim array) where each element[i][j] is greater
    than or equal to element[i-1][j-1] how would you efficiently count the
    number of negatives.
 */
Point _binary_find(Point l, Point r, vvi const& m) {
    while (l.second < r.second) { // cols increase l to r
        // Point mid = make_pair((l.first + r.first)/2, (l.second + r.second)/2);
        // Note! rows decrease upwards, and columns increase going right
        Point mid = make_pair((l.first - (l.first-r.first)/2), 
                            (l.second + (r.second - l.second)/2));

        if (-1 == m[mid.first][mid.second]) {
            while (-1 == m[mid.first][mid.second]) { // in case there are duplicate -1's
                mid.first--; 
                mid.second++;
            }

            // mid has gone past the right most -1, back it up one
            return make_pair(mid.first+1, mid.second-1);
        }
        else if (-1 < m[mid.first][mid.second]) {
            r = make_pair(mid.first+1, mid.second-1);
        }
        else {
            l = make_pair(mid.first-1, mid.second+1);
        }
    }
    // if not found, the value we want is at end (or first) backed up one value
    // diagnonally
    assert(make_pair(l.first+1, l.second-1)==make_pair(r.first+1, r.second-1));
    return make_pair(r.first+1, r.second-1);
}

int _CountNegatives(Point const& beg, Point const& end, vvi const& m) {
    // if the value at begin is positive, there can be no negative numbers in that
    // diagonal
    if (0 <= m[beg.first][beg.second]) 
        return 0;
    // if value at end is negative, then all values in the diagonal must be negative
    if (0 > m[end.first][end.second]) 
        return end.second - beg.second + 1; // use cols as they increase beg->end

    // else, we know that value at begin is negative and the last value is postive. Use
    // binary search to locate the value of the least negative number by using -1 as
    // search key. Note that there might be duplicates so if we find -1, we will need
    // to make sure its the right most -1
    Point negative_end = _binary_find(beg, end, m);
    return negative_end.second - beg.second + 1; // use cols as they increase beg->end
}

int CountNegatives(vvi const& m) {
    if (0 == m.size() || 0 == m[0].size()) return 0;

    int const k_rows = m.size();
    int const k_cols = m[0].size();
    int negatives = 0;

    // check all the diagonals of the matrix, there are ROW+COL-1 diagonals in a matrix
    int count_diagnonals = k_rows+k_cols - 1;
    for (int d = 1; d <= count_diagnonals; ++d) {
        
        // START ROW of the diagonal goes row by row for the first "k_rows" diagnonals
        // and then is on the last row for all the other diagnonals
        // START COL of the diagonal is 0 for the first "k_rows" diagonals and then is
        // on (d-k_rows) column after that
        int sr = min(d-1, k_rows-1);
        int sc = max(0, d-k_rows);

        // END ROW of the diagonal is 0 for the first "k_cols" diagonals and then is
        // on (d-k_cols) rows after that
        // END COL of the diagnonal goes colum by column for the first "k_cols" diagnonals
        // and then is on the last column for the last of them
        int er = max(0, d-k_cols);
        int ec = min(d-1, k_cols-1);

        // count the negatives in each diagonal by using modified binary search
        // heuristic
        negatives += _CountNegatives(make_pair(sr, sc), make_pair(er, ec), m); 
    }
    return negatives;
}
/* design a stack with min */
template <typename T>
class stack_with_min {
public:
    void pop() {
        if (m_mins.top() == m_stack.top())
            m_mins.pop();
        return m_stack.pop();
    }

    T top() { return m_stack.top(); }
    bool empty() { return m_stack.empty(); }
    size_t size() { return m_stack.size(); }
    void push(T const& value) {
        if (m_mins.empty() || value <= m_mins.top())
            m_mins.push(value);
        return m_stack.push(value);
    }
    T min() { return m_mins.empty() ? numeric_limits<int>::max() : m_mins.top(); }

private:
    stack<T> m_stack;
    stack<T> m_mins;
};

/* Implement a function that can calculate the prime numbers upto number N */
/* Loose bound on performance is O(nlogn) (n/2 + n/3 + n/4 ...) = n(1/2 + 1/3 + ..) */
vi GetPrimesUpto(int num) {
    vector<bool> sieve(num+1, true);
    sieve[0] = false;
    sieve[1] = false;
    vi primes;
    for (int i = 2; i <= num; ++i) {
        if (sieve[i]) {
            primes.push_back(i);
            for (int j = i*i; j <= num; j += i) 
                sieve[j] = false;
        }
    }
    return primes;
}

/* Given a byte array, how would you eliminate duplicate entries */
void RemoveByteDuplicates(vector<byte>& v) {
    vector<byte> fixed;
    unordered_set<byte> set;
    for (byte b : v) {
        if (set.find(b) == set.end()) {
            fixed.push_back(b);
            set.insert(b);
        }
    }
    v.swap(fixed);
}