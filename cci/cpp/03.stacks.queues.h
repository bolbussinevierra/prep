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
        _CombineStacks();
        m_remove.pop();
    }                                                                                                                                                                       

    T Peek() {
        _CombineStacks();
        return m_remove.top();
    }
                  
    void Add(T t){                                                                                                                                                                                                                                             
        m_add.push(t) 
    }


private:
    void _CombineStacks(){
        if (m_remove.empty())
        {
            while (!m_add.empty())
                m_remove.push(m_add.pop())
        }
    }
    stack<T> m_add;
    stack<T> m_remove; 
};