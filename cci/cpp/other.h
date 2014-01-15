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