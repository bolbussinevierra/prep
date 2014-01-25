#pragma once
//
// 7.4
//
int _negate(int a) {
    int negated_value = 0;
    int sign_delta = a < 0 ? 1 : -1;

    while (a != 0) {
        negated_value += sign_delta;
        a += sign_delta;
    }
    return negated_value;
}
int _abs(int a) {
    if (a < 0) 
        return _negate(a);
    else
        return a;
}

int minus(int a, int b) {
    return a + _negate(b);
}
int multiply(int a, int b) {
    if (a < b) 
        return multiply(b, a);

    int sum = 0;
    for (int i = _abs(b); i >= 1; --i) 
        sum += a;

    if (b < 0) 
        sum = _negate(sum);
    
    return sum;
}

int divide(int a, int b) {
    if (b == 0) {
        cout << "cannot divide by 0" << endl;
        return numeric_limits<int>::min();
    }

    int abs_a = _abs(a);
    int abs_b = _abs(b);
    
    // we are solving for x in a = xb;

    int product = 0;
    int x = 0;
    while (product + abs_b <= abs_a) { // do not exceed a
        product += abs_b;
        x++;
    }

    // if both a and b have the same sign, we return x otherwise we will return 
    // negated value of x
    if (a == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
        return x;
    else 
        return _negate(x);
}
        