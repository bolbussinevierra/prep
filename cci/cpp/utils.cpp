#include "stdafx.h"

void tabout(int value) {
    for (int i = 1; i <= value; ++i)
        cout << "    ";
}

void Print(Point const& p) {
    cout << "[" << p.first << "," << p.second << "]" << endl;
}
