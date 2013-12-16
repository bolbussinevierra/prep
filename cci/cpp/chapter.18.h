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
void PickM_MineBeter(vector<int>& n, int m) {
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
