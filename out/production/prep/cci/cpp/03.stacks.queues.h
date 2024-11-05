#pragma once

//
// 3.4
//
#define FROM 0
#define MID  1
#define TO   2
int _pop_and_get(stack<int>& s) {
    int n = s.top();
    s.pop();
    return n;
}
void _SolveHanoi(int n, array<stack<int>, 3>& pegs, int from, int to, int mid) {
    if (n > 0) {
        _SolveHanoi(n-1, pegs, from, mid, to);
        int disk = _pop_and_get(pegs[from]);
        pegs[to].push(disk);
        printf("Moving disk=%d from peg=%d to peg=%d \n", disk, from, to);
        _SolveHanoi(n-1, pegs, mid, to, from);        
    }
}
void SolveHanoi(int n) {
    array<stack<int>, 3> pegs;
    for (int i = n; i >= 1; --i) 
        pegs[FROM].push(i);
    return _SolveHanoi(n, pegs, FROM, TO, MID);
}
//
// 3.6
//
template<class T>
class myq {
public:
    myq() { }
    ~myq() { }

    int Size() { return m_add.size() + m_remove.size(); }
    
    void Remove() {
        _InvertAdds();
        m_remove.pop();
    }                                                                                                                                                                       

    T Peek() {
        _InvertAdds();
        return m_remove.top();
    }
                  
    void Add(T t){                                                                                                                                                                                                                                             
        m_add.push(t) 
    }


private:
    void _InvertAdds(){
        if (m_remove.empty())
        {
            while (!m_add.empty())
                m_remove.push(m_add.pop())
        }
    }
    stack<T> m_add;
    stack<T> m_remove; 
};

BEGIN_NAMESPACE(epi_8)
template<typename T>
class Queue {
public:
    explicit Queue(size_t cap):data_(cap), head_(0), tail_(0), count_(0) {}
    void push(const T& x) {
        if (count_ == data_.size()) {
            // rearrange the elements to get the head at front
            rotate(data_.begin(), data_.begin()+head_, data_.end());
            data_.resize(data_.size() << 1);
            head_ = 0, tail_ = count_;
        }
        data_[tail_] = x;
        tail_ = (tail_ + 1) % data_.size();
        count_++;
    }
    T pop() {
        if(count_) {
            --count_;
            T ret = data_[head_];
            head_ = (head_ + 1) % data_.size();
            return ret;
        }
        throw length_error("empty queue");
    }
    size_t size() const { return count_; }
    
private:
    // head always points to the oldest element (next out) and tail
    // always points to the next empty slot to be used on push
    size_t head_, tail_, count_;
    vector<T> data_;
};

int RPN_Eval(string const& s) {
    stack<int> eval_stack;
    stringstream ss(s);
    string symbol;

    while (getline(ss, symbol, ',')) {
        if (symbol == "+" || symbol == "-" || symbol == "*" || symbol == "/") {
            int y = eval_stack.top();
            eval_stack.pop();
            int x = eval_stack.top();
            eval_stack.pop();

            switch (symbol.front()) {
            case '+':
                eval_stack.emplace(x + y);
                break;
            case '-':
                eval_stack.emplace(x - y);
                break;
            case '*':
                eval_stack.emplace(x * y);
                break;
            case '/':
                eval_stack.emplace(x / y);
                break;
            }
        } else {
            eval_stack.emplace(stoi(symbol));
        }
    }
    return eval_stack.top();
}

END_NAMESPACE
