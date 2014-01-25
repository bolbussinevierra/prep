#pragma once
//
// 7.4
//
int _negate(int a) {
    int neg = 0;
    int sign_delta = a < 0 ? 1 : -1;

    while (a != 0) {
        neg += sign_delta;
        a += sign_delta;
    }
    return neg;
}
