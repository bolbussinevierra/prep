#include <vector>
#include <list>
#include <tuple>
using namespace std;

unsigned int get_key(string const& s) {
    unsigned int key = 997;
    for (char const& c : s) {
        key = key * 101 + c;
    }
    return key;
}

unsigned int get_key(unsigned int i) {
    return i;
}


template <typename key, typename value> 
struct my_map
{
    virtual ~my_map() {}

    void insert(key const& k, value const& v) {
        int index;
        if (find_index(k, index)) {
            // object with this key already exists, overwrite it
            entry overwrite(k,v);
            put_at(index, entry);
        }
        else {
            entry new(k, v);
            put(new);
        }
    }

    bool find(key const& k, value& result) const {
        int index;
        if (find_index(k, index)) {
            get_at(index, k, result);
            return true;
        }
        return false;
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
        entry():k(0), deleted(true) {}
        
        void print() {
            if (empty) {
                cout << "empty";
            } 
            else {
                cout << "key:" << k << " value:" << val;
            }
        }
    };

    my_map():m_used(0) {}
    static const int initial_capacity = 31;
    unsigned int m_used;

private: // overrides to allow for template methods
    virtual void put_at(int index, entry const& entry) = 0;
    virtual void put(entry const& entry) = 0;
    virtual void get_at(int index, key const& k, value& val) = 0;
    virtual int hash(int key) const = 0;
    virtual bool find_index(key const& k, int& index) const = 0;
};

template<typename key, typename value>
class map_oa : public my_map<key, value> { // uses open addressing / linear probing for collision mitigation
public:
    map_oa():m_table(initial_capacity) {};
    
    virtual bool find(key const& k, value& result) {
        return false;
    }

    virtual void print() {
        for (int i = 0; i < m_table.size(); ++i) {
            cout << "[" << i << "] ";
            m_table[i].print();
            cout << endl;
        }
    }
private:
    int hash(int key) const {
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
        index = hash(get_key(entry.k));
   
        while(!m_table[index].empty) {
            index = (index+1) % m_table.size();
        }
        m_table[index] = entry;
        m_used++;
    }

    void grow() {

    }

    virtual void get_at(int index, key const& k, value& val) {
        val = m_table[index].val;
    }

    virtual bool find_index(key const& k, int& index) const {
        int i = hash(get_key(k));
        int count_checked = 0;
        while (count_checked++ < m_used && !m_table[i].empty && m_table[i].k != k)
        {
            i = (i+1) % m_table.size();
        }
        if (!m_table[i].empty && m_table[i].k == k) {
            index = i;
            return true;
        }
        else {
            return false;
        }
    }

    vector<entry> m_table; 
};

//template <typename key, typename value>
//class map_ch : public my_map { // uses chaining for collision mitigation
//
//private:
//    vector<list<pair<key, value>>> m_table(capacity);
//
//};