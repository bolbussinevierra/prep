#include <iostream>
#include <unordered_map>
using namespace std;

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
             CharTable2D const& table, BoolTable2D& visited, vector<Point>& path) {
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

void PrintLetterPaths(string const& w, CharTable2D const& table) {
    if (w.empty()) return;
 
    int rows = table.size();
    int cols = table[0].size();

    string lower_w(w.size(), 0);
    std::transform(w.begin(), w.end(), lower_w.begin(), ::tolower);

    for(int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (table[i][j] == *lower_w.begin()) {
                vector<Point> path(lower_w.size());
                BoolTable2D visited(rows, vector<bool>(cols, false));
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
                  string const& w, Point& prev) {
    
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
void PrintPath(vector<TrackTable>const& dp, CharTable2D const& table, 
              int pos, int row, int col) {
    if (pos == -1) return;
    PrintPath(dp, table, pos-1, 
             dp[pos][row][col].previous.first, // backpointer previous row
             dp[pos][row][col].previous.second); // backpointer previous col
    cout << "[" << row << "," << col << "]" ;
}
void ContainsWordDP(string const& w, CharTable2D const& table) {
    // dp[pos][row][col] = true if table[row][col] == w_pos and
    //                             table[pos-1][x][y] == true
    //                             where table [x][y] is a valid neighbor of
    //                             table[row][col]. (There are 8 max poosible neighbors)
    // return true if dp[w.size() - 1][i][j] is true for any valid i,j
    //
    int const k_rows = table.size();
    int const k_cols = table[0].size();
    string lower_w(w.size(), 0);
    std::transform(w.begin(), w.end(), lower_w.begin(), ::tolower);

    vector<TrackTable> dp(lower_w.size(), TrackTable(k_rows, vector<track>(k_cols, k_null)));

    for (int pos = 0; pos < lower_w.size(); ++pos) {
        for (int row = 0; row < k_rows; ++row) {
            for (int col = 0; col < k_cols; ++col) {
                bool set_on = table[row][col] == lower_w[pos]; 
                if (pos > 0 && set_on) {
                    Point prev;
                    set_on = NeighborIsSet(dp, pos-1, row, col, lower_w, prev);
                    if (set_on) {
                        dp[pos][row][col].previous = prev;
                    }
                }
                dp[pos][row][col].match = set_on;
            }
        }
    }

    // now find every instance that matches and print its path
    for (int row = 0; row < k_rows; ++row) {
        for (int col = 0; col < k_cols; ++col) {
            if (dp[w.size()-1][row][col].match) {
                PrintPath(dp, table, w.size()-1, row, col);
                cout << endl;
            }
        }
    }
}