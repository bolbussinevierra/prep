#pragma once
namespace epi_5 {
/*
5.6 Implement string/integer inter-conversation functions. Use the following function signatures. string IntToString(int x) and int StringToInt(String s)
*/
string IntToString(int num) {
    bool is_negative = (num < 0);
    if (is_negative)
        num = -num;
    string s;
    while(num) {
        s.push_back('0' + num%10);
        num /= 10;
    }
    if (s.empty())
        s.push_back('0'); // num is zero
    if (is_negative)
        s.push_back('-');
    reverse(s.begin(), s.end());
    return s;
}


int StringToInt(string const& s) {
    if (s == "-") 
        throw invalid_argument("illegal input");

    bool is_neg = s[0] == '-';
    int num = 0;
    for (int i = (is_neg ? 1 : 0); i < s.size(); ++i) {
        if (isdigit(s[i])) {
            num = num * 10 + (s[i] - '0');
        } else {
            throw invalid_argument("illegal input");
        }
    }
    return is_neg ? -num : num; 
}

}