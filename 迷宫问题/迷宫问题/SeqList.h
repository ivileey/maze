#ifndef SEQLIST_H
#define SEQLIST_H
#include <iostream>
using namespace std;
#include <exception>
#include<stdexcept>
#include <windows.h>
template <class T>
class SeqList
{
protected:
    T *element;
    int length;


private:
    void init(T values[],int n);

public:
    int n;
    SeqList(int length=32);
    SeqList(int length,T x);
    SeqList(T values[],int n);
    ~SeqList();

    bool empty();
    int count();
    T get(int i);
    T& operator[](int i);
    friend ostream& operator<<(ostream& out,SeqList<T>& list)
   {
    out<<"(";
    if(list.n>0)
        cout<<list.element[0];
    for(int i=1;i<list.n;i++)
        out<<"'"<<list.element[i];
    out<<")"<<endl;
    return out;
}
    void printPrevious();
    void insert(int i,T x);
    virtual void insert(T x);
    T remove(int i);
    void removeAll();
    virtual int search(T key,int start=0);
    virtual void removeFirst(T key);

    SeqList(SeqList<T> &list);
    SeqList<T>& operator=(SeqList<T> &list);
    bool operator==(SeqList<T> &list);
    bool operator!=(SeqList<T> &list);
    bool operator+=(SeqList<T> &list);
    SeqList<T> operator+(SeqList<T> &list);
};

template <class T>
SeqList<T>::SeqList(int length)
{
    element=new T[length];
    length=length;
    n=0;
}
template <class T>
SeqList<T>::SeqList(int length,T x)
{
    element=new T[length];
    this->length=n=length;
    for(int i=0;i<n;i++)
        element[i]=x;
}
template <class T>
SeqList<T>::SeqList(T values[],int n)
{
    init(values,n);
}
template <class T>
void SeqList<T>::init(T values[],int n)
{
    this->length=n*2;
    this->n=n;
    this->element=new T[length];
    for(int i=0;i<n;i++)
        this->element[i]=values[i];
}
template <class T>
SeqList<T>::~SeqList()
{
    delete[]element;
}

template <class T>
bool SeqList<T>::empty()
{
    return n==0;
}
template <class T>
int SeqList<T>::count()
{
    return n;
}
template <class T>
T SeqList<T>::get(int i)
{
    return element[i];
}
template <class T>
T& SeqList<T>::operator[](int i)
{
    if(i>=0&&i<n)
        return element[i];
    else throw out_of_range("");
}

template <class T>
void SeqList<T>::printPrevious()
{
    for(int i=0;i<n;i++)
        cout<<element[n-i-1]<<endl;
}
template <class T>
void SeqList<T>::insert(int i,T x)
{
    if(i<0) i=0;
    if(i>n) i=n;
    T *ele=element;
    if(n==length)
    {
        length*=2;
        this->element=new T[length];
        for(int j=0;j<i;j++)
            element[j]=ele[j];
    }
    for(int j=n-1;j>=i;j--)
        element[j+1]=ele[j];
    if(ele!=element)
     delete []ele;
    element[i]=x;
    n++;
}
template <class T>
void SeqList<T>::insert(T x)
{
    insert(this->n,x);
}
template <class T>
T SeqList<T>::remove(int i)
{
    if(this->n>0&&i>=0&&i<n)
    {
        T old=this->element[i];
        for(int j=i;j<n-1;j++)
            element[j]=element[j+1];
        n--;
        return old;
    }
    throw out_of_range("");
}
template <class T>
void SeqList<T>::removeAll()
{
    this->n=0;
}
template <class T>
int SeqList<T>::search(T key,int start)
{
    for(int i=start;i<n;i++)
        if(this->element[i]==key)
            return i;
    return -1;
}
template <class T>
void SeqList<T>::removeFirst(T key)
{
    int i;
    for(i=0;i<n-1;i++)
    {
        if(element[i]==key)
        {
            element[i]=element[i+1];
            n--;
            break;
        }
    }
    if(this->element[n-1]==key)
        n--;
}
template <class T>
SeqList<T>::SeqList(SeqList<T> &list)
{
    this->init(list.element,list.n);
}
template <class T>
SeqList<T>&SeqList<T>::operator=(SeqList<T> &list)
{
    if(this->length<=list.n)
    {
        for(int i=0;i<this->n;i++)
            element[i]=list.element[i];
        return *this;
    }
    this->~SeqList();
    this->init(list.element,list.n);
    return *this;
}
template <class T>
bool SeqList<T>::operator==(SeqList<T> &list)
{
    if(this==&list||this->element==list.element)
        return true;
    if(this->n!=list.n)
        return false;
    for(int i=0;i<n;i++)
       if(element[i]!=list.element[i])
            return false;
    return true;
}
template <class T>
bool SeqList<T>::operator!=(SeqList<T> &list)
{
    return !(*this==list);
}
template <class T>
bool SeqList<T>::operator+=(SeqList &list)
{
    for(int i=0;i<list.n;i++)
        insert(list.element[i]);
}
template <class T>
SeqList<T> SeqList<T>::operator+(SeqList<T> &list)
{
    SeqList<T> seq;
    seq+=this;
    seq+=list;
    return seq;
}
#endif // SQELIST_H