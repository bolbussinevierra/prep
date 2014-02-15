#pragma once
class BigInt {
public:
    explicit BigInt(int capacity) : sign_(1), digits_(capacity) {}
    explicit BigInt(string const& s) : sign_(s[0] == '-' ? -1 : 1),
        digits_(s.size() - (s[0] == '-')) {
            for (int i = s.size() - 1, j = 0; i >= (sign_ == -1 ? 1 : 0); --i, ++j) {
                if (isdigit(s[i])) 
                    digits_[j] = s[i] - '0';
            }
    }
    BigInt operator*(BigInt const& n) const {
        BigInt result (digits_.size() + n.digits_.size());
        result.sign_ = sign_ * n.sign_;
        int i = 0, j = 0;
        for (i = 0; i < n.digits_.size(); ++i) {
            if (n.digits_[i]) {
                int carry = 0;
                for (j = 0; j < digits_.size() || carry; ++j) {
                    int n_digit = result.digits_[i + j] +
                        (j < digits_.size() ? n.digits_[i]*digits_[j]:0) +
                        carry;
                    result.digits_[i + j] = n_digit % 10;
                    carry = n_digit / 10;
                }
            }
        }
        // if one number is 0, the result size should be 0
        if ((digits_.size() == 1 && digits_.front() == 0) ||
            (n.digits_.size() == 1 && n.digits_.front() == 0)) {
                result.sign_ = 1, result.digits_.resize(1);
        } else {
            result.digits_.resize(i + j - 1);
        }
        return result;
    }

    string to_string() {
        string out(sign_ == -1 ? digits_.size() + 1 : digits_.size(), '0') ;
        
        if (sign_ == -1) 
            out[0] = '-';

        int at = sign_ == -1 ? 1 : 0;
        for (int i = digits_.size() - 1; i >= 0; --i) 
            out[at++] = digits_[i] + '0';    

        return out;
    }
private:
    int sign_;
    vector<int> digits_;
};
