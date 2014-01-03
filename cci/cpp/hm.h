#include <vector>
#include <list>
using namespace std;

// using djb2
unsigned long get_hash(string const& s) {
    unsigned long key = 997;
    for (char const& c : s) {
        key = (key * 101) + c;
    }
    return key;
}

unsigned long get_hash(unsigned int i) {
    return i;
}


template <typename key, typename value> 
struct map_base
{
    void insert(key const& k, value const& v) {
        int index;
        value ignore;
        if (find_index(k, index, ignore)) {
            // object with this key already exists, overwrite it
            entry overwrite(k,v);
            put_at(index, overwrite);
        }
        else {
            // insert a new entry
            entry new_entry(k, v);
            put(new_entry);
        }
    }

    bool find(key const& k, value& result) const {
        int index;
        return find_index(k, index, result);
    }

    int size() { return m_used; }
    bool empty() { return 0 == size(); }
    
    virtual void print() = 0;

protected:
    struct entry {
        key k;
        value val;
        bool empty;

        entry(key const& k, value const& v):k(k), val(v), empty(false) {}
        entry():empty(true) {}
        
        void print() {
            if (empty) {
                cout << "empty";
            } 
            else {
                cout << "key:" << k << " value:" << val;
            }
        }
    };

    map_base():m_used(0) {}
    ~map_base() {}
    static const int initial_capacity = 31;
    unsigned int m_used;

    void __debug_print_collision(entry const& e1, entry const& e2) {
        if (get_hash(e1.k) == get_hash(e2.k)) {
            cout << "key=" << e1.k << " hash collided with key=" << e2.k << endl;
        }
    }

private: // overrides to allow for template methods
    virtual void put_at(int index, entry const& entry) = 0;
    virtual void put(entry const& entry) = 0;
    virtual int get_index_for_hash(long key) const = 0;
    virtual bool find_index(key const& k, int& index, value& val) const = 0;
};

/*
 * MAP_OA: Uses open addressing / linear probbing for collision detection
 */

template<typename key, typename value>
class map_oa : public map_base<key, value> { 
public:
    map_oa():m_table(initial_capacity) {};
    
    virtual void print() {
        for (int i = 0; i < m_table.size(); ++i) {
            cout << "[" << i << "] ";
            m_table[i].print();
            cout << endl;
        }
    }

private:
    int get_index_for_hash(long key) const {
        return key % m_table.size();
    }

    void put_at(int index, entry const& entry) {
        m_table[index] = entry;
    }
    
    void put(entry const& entry) {    
        if (m_used == m_table.size()) {
            grow(); // double the size of the table and rehash all items
        }
        
        // calculate the index 
        int index = get_index_for_hash(get_hash(entry.k));
   
        while(!m_table[index].empty) {
            __debug_print_collision(entry, m_table[index]);
            index = (index+1) % m_table.size();
        }
        m_table[index] = entry;
        m_used++;
    }

    void grow() {
        cout << ">>> GROWING (x2)" << endl;

        // copy all the current entries
        int current_size = m_table.size();
        vector<entry> current(m_table.begin(), m_table.end());
        
        // clear the current table and double it in size
        m_table.clear();
        m_table.resize(current_size << 1); 

        // re-insert all the values into the new table. We set m_used to 0
        // since insert will increment it for each insert
        m_used = 0;
        for (entry const& e : current) {
            insert(e.k, e.val);
        }
    }

    virtual bool find_index(key const& k, int& index, value& val) const {
        int i = get_index_for_hash(get_hash(k));
        int count_checked = 0;
        while (count_checked++ < m_used && !m_table[i].empty && m_table[i].k != k)
        {
            i = (i+1) % m_table.size();
        }
        if (!m_table[i].empty && m_table[i].k == k) {
            index = i;
            val = m_table[i].val;
            return true;
        }
        else {
            return false;
        }
    }

    vector<entry> m_table; 
};

/*
 * MAP_CH: Uses chaining probbing for collision detection
 */

//template <typename key, typename value>
//class map_ch : public my_map { // uses chaining for collision mitigation
//
//private:
//    vector<list<pair<key, value>>> m_table(capacity);
//
//};