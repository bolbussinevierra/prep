#pragma once

class heap {
public:
    explicit heap(int size = 20) { 
        items.reserve(size); 
    }
    virtual ~heap() {}

    bool empty() { return items.empty(); }

    void sort() {
        if (items.size() <= 1) return;
        for (int last = items.size()-1; last > 0; ) {
            // put the current largest priority item at the back by swapping it with the last item
            _swap(&items[0], &items[last]);
            last--; // take out the last position from the heap.

            // restore heap property for remaining items
            heapify_down(0, last);
        }
        print();
    }

    int size() { return items.size(); }

    void insert(int i) {
        items.push_back(i);
        heapify_up(items.size() - 1);
    }

    void make_heap(vi const& v) {
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
        for (int i = 1; i <= indent; ++i) {
            cout << "  ";
        }
        cout << items[root] << endl;
        print_tree(left(root), indent + 1);
    }

private:
    void heapify_up(int current) {
        int p = parent(current);
        while (p >= 0) {
            if (greater_priority(items[current], items[p])) {
                _swap(&items[current], &items[p]);
                current = p;
                p = parent(current);
            }
            else {
                break;
            }
        }
    }

protected:
    void heapify_down(int current, int last) {
        if (current >= last) return;      // got to the end
        if (left(current) > last) return; // current has no children

        int has_priority = current;
        int l = left(current);
        if (greater_priority(items[l],  items[current])) {
            has_priority = l;
        }
        
        int r = right(current);
        if ((r <= last) && greater_priority(items[r], items[has_priority])) {
            has_priority = r;
        }
        
        // if the highest priority node was not the root, swap its value with the root
        // and recurse down the child that had the priority
        if (has_priority != current) {
            _swap(&items[current], &items[has_priority]);
            heapify_down(has_priority, last);
        }
    }        
private:
    virtual bool greater_priority(int lhs, int rhs) = 0;
    
protected:
    int parent(int i) { 
        return (i - 1)/2; 
    }
    
    int left(int i) {
        return (2*i) + 1;
    }
    
    int right(int i) { 
        return (2*i) + 2;
    }
    
    vi items;
};

class min_heap : public heap {
private:
    bool greater_priority(int lhs, int rhs) { return lhs < rhs; }
};

class max_heap : public heap {  
private:
    bool greater_priority(int lhs, int rhs) { return lhs > rhs; }
};
