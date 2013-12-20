#include <iostream>
#include <unordered_map>
#include <assert.h>;
#include <WinError.h>
#pragma once

using namespace std;

class TrieNode {
public:
    explicit TrieNode(char c, bool is_end=false)
        :letter(c), is_end(is_end) { }
    
    bool IsChild(char c) {
        return adjacent.end() != adjacent.find(c);
    }
    
    void Print() {
        cout << letter;
        if (is_end) {
            cout << endl;    
        }
        
        for (auto it = adjacent.begin(); it != adjacent.end(); ++it) {
            it->second->Print();
        }
        
    }
           
    void Insert(char c) {
        adjacent[c] = new TrieNode(c);
    }
    TrieNode* Get(char c) { return adjacent[c]; }

    ~TrieNode() {
        for (auto it = adjacent.begin(); it != adjacent.end(); ++it) {
            delete it->second;
        }
    }

public:
    char letter;
    bool is_end;
private:
    unordered_map<char, TrieNode*> adjacent;
};

class Trie {
public:
    Trie() { root.reset(new TrieNode(' ')); }
    
    void Print() { root->Print(); }
    void Insert(string const& w) {
        TrieNode * current = root.get();
        for (char const &c : w) {
            if (!current->IsChild(c)) {
                current->Insert(c);
            }
            current = current->Get(c);
        }
        current->is_end = true; 
    }

    bool Contains(string const& w) {
        TrieNode* current = root.get();
        for (char const& c : w) {
            if (!current->IsChild(c)) {
                return false;
            }
            current = current->Get(c);
        }
        return current->is_end;
    }

    bool IsSubstring(string const& w) {
        TrieNode* current(root.get());
        for (char const& c : w) {
            if (!current->IsChild(c)) {
                return false;
            }
            current = current->Get(c);
        }
        return true;
    }

    void GetAllPrefixes(string const& w, vector<string>& prefixes) {
        TrieNode* current = root.get();
        string prefix;
        for (char const& c : w) {
            if (!current->IsChild(c)) {
                return;
            }
            current = current->Get(c);
            prefix.push_back(c);

            // we do not want a word to be a prefix of itself
            if (current->is_end && prefix != w) {
                prefixes.push_back(prefix);
            }
            
        }
    }

private:
    unique_ptr<TrieNode> root;
};

