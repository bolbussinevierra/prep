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
// --------------------------------------------------------------
// 7.3
//
class Line {
public:
    Line(DoublePoint a, DoublePoint b):epsilon(0.000001){
        double delta_x = b.first - a.first;
        m_infinite_slope = (delta_x <= epsilon);

        if (!m_infinite_slope) {
            m_slope = (b.second - a.second)/delta_x;

            // we know y = (m_slope * x) + y_intercept. Thefore
            // y - (m_slope * x) = y_intercept
            m_y_intercept = a.second - (m_slope * a.first);
        }
        else {
            m_slope = numeric_limits<double>::max();
            m_y_intercept = numeric_limits<double>::max();
        }
    }

    bool operator==(Line const& rhs) const {
        return  (m_infinite_slope == rhs.m_infinite_slope) &&
                (abs(m_slope - rhs.m_slope) <= epsilon) &&
                (m_y_intercept - rhs.m_y_intercept <= epsilon);
    }

    bool intersects(Line const& other) const {
        return (*this == other) ||
              abs(m_slope - other.m_slope) > epsilon;
    }

private:
    const double epsilon;
    double m_slope;
    bool m_infinite_slope;
    double m_y_intercept;
};