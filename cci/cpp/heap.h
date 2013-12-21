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

private:
    virtual void heapify_up(int high) = 0;   // after adding item
    virtual void heapify_down(int low, int high) = 0; // after removing item
    
protected:
    vector<int> items;
};

class MinHeap : public heap {
};

class MaxHeap : public heap {
    
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
};
