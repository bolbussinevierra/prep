#pragma once
BEGIN_NAMESPACE(epi_5)
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


//
// 5.7
//
string ConvertBase(const string& s, int b1, int b2) {
    bool neg = s.front() == '-';
    int num = 0;
    for (int i = (neg ? 1 : 0); i < s.size(); ++i) {
        num *= b1;
        num += isdigit(s[i]) ? s[i] - '0' : s[i] - 'A' + 10;
    }
    string ans;
    while (num) {
        int r = num % b2;
        ans.push_back(r >= 10 ? 'A' + (r - 10) : '0' + r); 
        num /= b2;
    }
    if (ans.empty()) 
        ans.push_back('0');

    if (neg)
        ans.push_back('-');

    reverse(ans.begin(), ans.end());
    return ans;
}
//
// 5.8
//
int ColIDToBase26(const string& col) {
    int num = 0;
    for (const char& c : col) 
        num = num * 26 + (c - 'A' + 1);
    return num;
}

END_NAMESPACE