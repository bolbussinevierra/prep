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

void ShuffleDeck(vector<Card>& cards) {
    PrintCards(cards);
    for (int i = 0; i < cards.size(); ++i) {
        _swap(&cards[i], &cards[random(0,i)]);
    }
    PrintCards(cards);
}
