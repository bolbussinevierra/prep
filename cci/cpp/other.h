#include <iostream>
#include <unordered_map>
using namespace std;

typedef unordered_map<string, string> TranslationTable;

void GetTranslationTable(TranslationTable& dict) {
    dict["a"] = "t1";
    dict["b"] = "t2";
    dict["ab"] = "t3";
}
