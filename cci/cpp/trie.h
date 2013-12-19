#include <iostream>
#include <unordered_map>
#include <assert.h>;
#include <WinError.h>

using namespace std;

struct TrieNode {
    char letter;
    bool is_end;
    unordered_map<char, TrieNode*> adjacent;

    explicit TrieNode(char c, bool is_end=false)
        :letter(c), is_end(is_end) { }
};

class Trie {
public:
    Trie() { root.reset(new TrieNode(' ')); }
    

    void Insert(string const& w) {
        TrieNode * current = root.get();
        for (int i = 0; i < w.
    }
private:
    unique_ptr<TrieNode> root;
};
 