#ifndef SEQSTACK_H_INCLUDED
#define SEQSTACK_H_INCLUDED
#include "SeqList.h"
template <class T>
class SeqStack
{
private:
    SeqList<T> list;
public:
    SeqStack(){}
    ~SeqStack(){}
    bool empty()
    {
        return this->list.empty();
    }
    void push(T x)    //入栈
    {
        this->list.insert(x);
    }
    T pop()
    {
        if(!empty())
            return this->list.remove(list.count()-1);
        throw logic_error("空栈，不能执行出栈操作");
    }
    T get()
    {
        if(!empty())
            return this->list.get(list.count()-1);
        throw logic_error("空栈,不能获得栈顶元素");
    }

};


#endif // SEQSTACK_H_INCLUDED
