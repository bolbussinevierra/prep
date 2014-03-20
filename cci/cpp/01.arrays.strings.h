#pragma once

void _PrintMatrix(int **m, int n)
{   
    for(int i  =  0; i < n; ++i)
    {
        cout<< "\n";
        for(int j  =  0;  j < n;  ++j)
        {
            printf("%d ",m[i][j]);
            //cout <<  m[i][j];
        }
    }
    cout << "\n-------------------------" << endl;
}

void _FillMatrix(int **m, int n)
{
    for(int i = 0; i < n; ++i)
    {
        m[i] = new int[n];
    }

    int value = 1;
    for(int i  =  0; i < n; ++i)
    {
        for(int j  =  0;  j < n;  ++j)
        {
            m[i][j] = value++;
        }
    }

}
//
// helpers
//



bool IsUniqueChars(char * str)
{
    if (str == nullptr) return true;
    int length = strlen(str);
    
    // must contain a duplicated if longer than 256. A single character or
    // empty string is vacuously unique
    if (length > 256) return false;
    if (length <= 1) return true;

    // bit vector for ascii (256 chars max)
    byte set[32] = {0}; // 256 / 8

    for (int i = 0; i < length; ++i)
    {
        int bit_group = (str[i] - '\0') / 8;
        int bit_pos = (str[i] - '\0') % 8;

        int set_check = set[bit_group];
        if ((set_check & (1 << bit_pos)) > 0)
        {
            return false;
        }
        set[bit_group] = set_check | (1 << bit_pos);
    }
    return true;
}
//
// 1.6
//
void RotateMatrix90(int ** m, int n)
{
    _PrintMatrix(m, n);
    for (int layer = 0; layer < n/2; ++layer)
    {
        int start = layer;
        int end = n - 1 - layer;
        for (int i = start; i < end; ++i)
        {
            int offset = i - start;
            int top = m[start][i];
            m[start][i] = m[end - offset][start];
            m[end - offset][start] = m[end][end - offset];
            m[end][end - offset] = m[i][end];
            m[i][end] = top;
        }
    }
    _PrintMatrix(m, n);
}

bool IsPermutation(string const& a, string const& b) {
    // ASSUMPTION: CASE IS SIGNIFICANT
    if (a.size() != b.size()) return false;

    string a_sorted = a;
    string b_sorted = b;

    std::sort(a_sorted.begin(), a_sorted.end());
    std::sort(b_sorted.begin(), b_sorted.end());

    return a_sorted == b_sorted;
}


BEGIN_NAMESPACE(epi_6)
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
        BigInt result(digits_.size() + n.digits_.size());
        result.sign_ = sign_ * n.sign_;
        int i = 0, j = 0;
        for (i = 0; i < n.digits_.size(); ++i) {
            if (n.digits_[i]) {
                int carry = 0;
                for (j = 0; j < digits_.size() || carry; ++j) {
                    int n_digit = result.digits_[i + j] +
                        (j < digits_.size() ? n.digits_[i] * digits_[j] : 0) +
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
        string out(sign_ == -1 ? digits_.size() + 1 : digits_.size(), '0');

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

void PrintMatrixLayerClockwise(vvi const& A, int offset) {
    // last value in an oddsize matrix?
    if (offset == A.size() - 1 - offset) {
        cout << A[offset][offset];
        return;
    }

    // print right stopping short of last value in row
    for (int col = offset; col < A.size() - 1 - offset; ++col) {
        cout << A[offset][col] << " ";
    }

    // print down stopping short of last value in col
    for (int row = offset; row < A.size() - 1 - offset; ++row) {
        cout << A[row][A.size() - 1 - offset] << " ";
    }

    // print left stopping short of first value in row
    for (int col = A.size() - 1 - offset; col > offset; --col) {
        cout << A[A.size() - 1 - offset][col] << " ";
    }

    // print up stopping short of first value in column 
    for (int row = A.size() - 1 - offset; row > offset; --row) {
        cout << A[row][offset] << " ";
    }
}

void PrintMatrixSpiral(vvi const& A) {
    // make sure you use "0.5 *" in ceil to make sure its working with 
    // a double (if you do / 2 it will work with int down casts and will 
    // not ceil up
    for (int offset = 0; offset < ceil(0.5 * A.size()); ++offset) {
        PrintMatrixLayerClockwise(A, offset);
    }
}

//
// 6.12
// 
vi NextPermutation(vector<int> p) {
    int furthest_larger = -1;
    // for each i down from the second last, find one with a larger element to its
    // right, and get the largest element to the right that we can find for that i
    int i = p.size() - 2;
    for ( ; i >= 0; --i) {
        for (int j = i + 1; j < p.size(); ++j) {
            if (p[j] > p[i]) {
                furthest_larger = j;
            }
        }
        if (furthest_larger != -1) {
            break;
        }
    }

    if (furthest_larger == -1)
        return {};

    // swap the position of the two and then reserve the elements at i+1 to end to
    // get the lowest lexicographic permutation of those elements
    swap(p[i], p[furthest_larger]);
    reverse(begin(p) + i + 1, end(p));
    return p;
}

END_NAMESPACE