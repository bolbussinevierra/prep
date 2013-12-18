#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

//
// 18.1
//
int _badd(int a, int b) {
    if (0==b) return a;
    int result = a ^ b; // adding without carrying
    int carry = (a & b) << 1; // carrying without adding
    return _badd(result, carry);
}

int _badd_iterative(int a, int b) {
    
    int result = a ^ b;
    int carry = (a & b) << 1;

    while (carry != 0) {
        int r1 = result ^ carry;
        carry = (result & carry) << 1;
        result = r1;
    }
    return result;
}

int badd(int a, int b) {
    cout << "a=" << a << endl;
    cout << "b=" << b << endl;
    int result = _badd_iterative(a, b);
    cout << "result=" << result << endl;
    return result;
}                                                                                                                                                                                                                                                          
//
// 18.2
//
struct Card { 
    int suite;
    int value;
};
int random(int low, int high) {
    /* initialize random seed: */
    srand (time(NULL));
    int range = high - low;
    return low + (rand() % (range+1));
}

void PrintCards(vector<Card> const& cards) {
    for (int i = 0; i < cards.size(); ++i) {
        cout << cards[i].value << " ";
    }
    cout << endl;
}

void ShuffleDeck_Mine(vector<Card>& cards) {
    PrintCards(cards);
    int last = cards.size() - 1;
    for (int i = 0; i < cards.size(); ++i) {
        int k = random(0, last); 
        _swap(&cards[k], &cards[last]);
        last--;
    }
    PrintCards(cards);
}


void ShuffleDeck_CCI(vector<Card>& cards) {
    PrintCards(cards);
    for (int i = 0; i < cards.size(); ++i) {
        int k = random(0,i); // NOTE: upper range is i and not end of the array! i.e increasing range
        _swap(&cards[i], &cards[k]);
    }
    PrintCards(cards);
}

//
// 18.3
//
void PickM_MineBetter(vector<int>& n, int m) {
    // Think of this as picking from a bag where the partition [last, n]
    // will contain that items that have ALREADY BEEN picked are in hand
    int last = n.size() - 1;
    for (int i = 0; i < m; ++i) {
        int k = random(0, last);
        _swap(&n[k], &n[last]);
        last--;
    }
    // last is at -1 off of the start of set m after the above look so we need
    // to bump it forward 1
    for (int i = last+1; i < n.size(); ++i) {
        cout << n[i] << " ";
    }
}

void PickM_CCI(vector<int> const&n, int m) {
    vector<int> vm(m);
    for (int i = 0; i < m; ++i) {
        vm[i] = n[i];
    }
    
    for (int i = m; i < n.size(); ++i) {
        int k = random(0, i);
        if (k < m) {
            vm[i] = n[k];
        }
    }

    for (int i = 0; i < vm.size(); ++i) {
        cout << vm[i] << " ";
    }

}
//
// 18.4
//
int _CountTwos(int n) {
    int count = 0;
    while (n > 0) {
        if (n % 10 == 2) {
            count++;
        }
        n /= 10;
    }
    return count;
}

int CountTwosBruteForce(int n) {
    int count = 0;
    for (int i=2; i <=n; ++i) {
        count += _CountTwos(i);
    }
    return count; 
}
//
// 18.5
//
int MinDist(string const& a, string const& b, vector<string> const& words) {
    int min = INT_MAX;
    int w1_pos = -1;
    int w2_pos = -1;
    for (int i = 0; i < words.size(); ++i) {
        if (0 == _stricmp(a.c_str(), words[i].c_str())) {
            w1_pos = i;
            if (w2_pos != -1) {
                int distance = w1_pos - w2_pos;
                if (min > distance) {
                    min = distance;
                }
            }
        } else if (0 == _stricmp(b.c_str(), words[i].c_str())) {
            w2_pos = i;
            if (w1_pos != -1) {
                int distance = w2_pos - w1_pos;
                if (min > distance) {
                    min = distance;
                }
            }
        }
    }
    return min;
}
//
// 18.6
//
int _partition(vector<int>& a, int left, int right) {
    // use the middle element as the pivot. Move it to the left
    // end to get it out of the way. Well remember to move it back
    // at the end
    int m = (left + right) / 2;
    _swap(&a[left], &a[m]);
    int p = a[left];
    int cache = left;
    
    left++; // skip over the pivot
    while (left <= right) {
        while (a[left] <= p) left++;
        while (a[right] > p) right--;
        if (left <= right) {
            _swap(&a[left], &a[right]);
            left++;
            right--;
        }
    }
    // restore the pivot to its correct position (before the right half
    // of partition)
    _swap(&a[cache], &a[right]);
    return right;
}

int _get_index_of_nth(vector<int>& a, int n, int left, int right) {
    int pivot_index = _partition(a, left, right);
    if (pivot_index == n - 1) { // note that n is 1 indexed but a is 0 indexed
        return pivot_index;
    } 
    else if (pivot_index > n - 1) {
        return _get_index_of_nth(a, n, left, pivot_index-1);
    }
    else {
        return _get_index_of_nth(a, (n - pivot_index - 1), pivot_index+1, right);
    }
}

void _test_print_nth(vector<int>& a, int n) {
    cout << n << " smallest=" << a[_get_index_of_nth(a, n, 0, a.size()-1)];
    cout << endl;
}

