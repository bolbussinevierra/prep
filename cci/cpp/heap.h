#include <vector>
#include <assert.h>
#pragma once
using namespace std;

class heap {
public:
    explicit heap(int size = 20) { 
        items.reserve(size); 
    }
    ~heap() {}
    
    void insert(int i) {
        items.push_back(i);
        heapify_up(items.size() - 1);
    }

    void make_heap(vector<int> const& v) {
        items.assign(v.begin(), v.end());

        // start at the last possible parent and heapify_down
        int last_leaf = items.size() - 1;
        for (int p = parent(last_leaf); p >= 0; --p) {
            heapify_down(p, last_leaf);
        }
        print_tree();
    }

    int peek_top() {
        assert(!items.empty());
        return items[0];
    }

    int extract_top() {
        assert(!items.empty());
        int top = peek_top();
        items[0]=items[items.size()-1];
        items.pop_back();
        heapify_down(0, items.size()-1);
        return top;   
    }

    void print() {
        for(int i : items) {
            cout << i << " ";
        }
        cout << endl;
    }

    void print_tree(int root = 0, int indent = 0) {
        if (root >= items.size()) return;
        
        print_tree(right(root), indent + 1);
        for (int i = 0; i <= indent; ++i) {
            cout << "  ";
        }
        cout << root << endl;
        print_tree(left(root), indent + 1);
    }

private:
    virtual void heapify_up(int current) = 0;   // after adding item
    virtual void heapify_down(int current, int last) = 0; // after removing item
    
protected:
    int parent(int i) { 
        assert(i > 0);
        return (i - 1)/2; 
    }
    
    int left(int i) {
        assert(i >= 0);
        return (2*i) + 1;
    }
    
    int right(int i) {
        assert(i >= 0); 
        return (2*i) + 2;
    }
    
    vector<int> items;
};

class min_heap : public heap {
};

class max_heap : public heap {  
public:
    void sort() {
        if (items.size() <= 1) return;
        int high = items.size()-1;
        while (high > 0) {
            // swap the back item with the front
            _swap(&items[0], &items[high]);
            high--;
            // restore heap property for remaining items
            heapify_down(0, high);
        }
        print();
    }

private:
    void heapify_up(int current) {
        int p = parent(current);
        while (p >= 0) {
            if (items[current] > items[p]) {
                _swap(&items[current], &items[p]);
                current = p;
                p = parent(current);
            }
            else {
                break;
            }
        }
    }

    void heapify_down(int current, int last) {
        if (current >= last) return;      // got to the end
        if (left(current) > last) return; // current has no children

        int largest = current;
        int l = left(current);
        if (items[l] > items[current]) {
            largest = l;
        }
        
        int r = right(current);
        if ((r <= last) && (items[r] > items[largest])) {
            largest = r;
        }
        
        // if the largest node was not the root, swap its value with the root
        // and recurse down the child that was the largest
        if (largest != current) {
            _swap(&items[current], &items[largest]);
            heapify_down(largest, last);
        }
    }        
};
