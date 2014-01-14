#include <iostream>
#include <unordered_map>
using namespace std;

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