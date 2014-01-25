#pragma once

//
// helpers
//

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