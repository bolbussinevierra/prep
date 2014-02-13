#include "stdafx.h"

void tabout(int value) {
    for (int i = 1; i <= value; ++i)
        cout << "    ";
}

void Print(Point const& p) {
    cout << "[" << p.first << "," << p.second << "]" << endl;
}

void _P(int a[], int len_a, char* title) {
    printf("%s:", title);
    for (int i = 0; i < len_a; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void _P(int a[], int len_a) {
    for (int i = 0; i < len_a; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

void rotate(int a[], int len, int rot_count) {
    if (rot_count == 0) return;
    _P(a, len, "bef_rotate");
    vi temp(len);
    for (int i = 0; i < len; ++i) {
        int newPos = (i + rot_count) % len;
        if (newPos < 0) {
            newPos = len + newPos; // if rot_count was negative, make it positive
        }
        temp[newPos] = a[i]; // mod can handle negative math
    }
    copy(temp.begin(), temp.end(), a);
    _P(a, len, "aft_rotate");
    return;
}

void PrintVector(vector<string>& p, char* title) {
    for (size_t i = 0; i < p.size(); ++i) {
        printf("%s\n", p[i].c_str());
    }
    printf("%s=[%d]\n", title, p.size());
}
int Min3(int a, int b, int c) { return min(min(a,b), c); }

int Log2(unsigned long long val) {
    return log(val) / log(2);
}