#pragma once
#include <iostream>
#define STACK_ALLOC_ERROR 0x01
#define STACK_EMPTY_ERROR 0x02
#define STACK_OVERFLOW 0x04
#define STACK_OTHER_ERROR 0xFF
template<class T> class Stack;
class StackException
{
public:
    StackException( int errCode = STACK_OTHER_ERROR) { mErrCode = errCode; }
    const char* getReason();
private:
    int mErrCode;
};
inline const char* StackException::getReason()
{
    switch(mErrCode)
    {
    case STACK_ALLOC_ERROR: return "ERROR: allocating memory error\n";
    case STACK_EMPTY_ERROR: return "ERROR: improper STACK size\n";
    case STACK_OVERFLOW: return "ERROR: Stack full\n";
    default: return "other ERROR\n";
    }
}
template<class T> class StackItem
{
private:
    T mKey;
    StackItem<T>* pNext;
    StackItem( T key, StackItem<T>* pNext );
public:
    virtual ~StackItem();
    T getKey() const;
    StackItem<T>* getNext() const;
    void setKey( T key );
    void setNext( StackItem<T>* pNext );

    friend class Stack<T>; // zaprzyjaznic WSZYSTKIE metody klasy stack
};

template<class T> StackItem<T>::StackItem( T key, StackItem<T>* pNext )
{
    setKey(key);
    setNext(pNext);
}
template<class T> StackItem<T>::~StackItem()
{
   // delete pNext;
}
template<class T> T StackItem<T>::getKey() const
{
    return mKey;
}
template<class T> StackItem<T>* StackItem<T>::getNext() const
{
    return pNext;
}
template<class T> void StackItem<T>::setKey( T key )
{
    this->mKey = key;
}
template<class T> void StackItem<T>::setNext(StackItem<T>* pNext)
{
    this->pNext = pNext;
} 
template<class T> class Stack
{
private:
    StackItem<T>* m_pHead;
public:
    Stack();
    virtual ~Stack();
    void push( T key );
    T pop();
    T top() const;
    void del();
    bool isEmpty() const;
};

template<class T> Stack<T>::Stack()
{
    m_pHead = NULL;
}
template<class T> Stack<T>::~Stack()
{
    while(!isEmpty())
        del();
}
template<class T> void Stack<T>::push(T key)
{
    StackItem<T>* sItem = new(std::nothrow) StackItem<T>(key, m_pHead);
    if( !sItem )
        throw StackException(STACK_ALLOC_ERROR);
    m_pHead = sItem;
}
template<class T> T Stack<T>::pop()
{
    if(isEmpty())
        throw StackException(STACK_EMPTY_ERROR);
    T x = top();
    del();
    return x;
}
template<class T> T Stack<T>::top() const
{
    if(!isEmpty())
        return m_pHead->getKey();
    throw StackException(STACK_EMPTY_ERROR);
    return 0;
}
template<class T> void Stack<T>::del()
{
    if(isEmpty())
        throw StackException(STACK_EMPTY_ERROR);
    StackItem<T>* p = m_pHead;
    m_pHead = p->getNext();
    //free(p);
    delete p;
}
template<class T> bool Stack<T>::isEmpty() const
{
    return m_pHead == nullptr;
}
//zmianne statyczne trzeba zainicjowac w cpp
//int Stack::Number_of_stacks = 0
//funkcje tez moga byc statyczne ale moga uzywac tylko zmiennych statycznych
//inijcowanie sta³ej sk³adowej const
// C() : c( 0 ) { x = 0; }//w konstruktorze sta³a c i zmienna x
// wskaznik na funkcje klasy
// typedef void ( S::*PtrtoMem) (int)
// dynamic_cast rzutuje na klasê pochodn¹ np. // moze dac blad jesli sie nie da
// reinterpret_cast mozna np. rzutowac adres na liczbe // ale trzeba potem wrocic
// zmienne automatyczne
// alternattywna pêtla for (for const char* s : tablica) tak jak w pythonie
// explicit to pamiêtasz
// CComplex& operator = ( const CComplex& z ) = delete // zabrania kopiowania
// static const mo¿na deklarowaæ w klasie w przeciwieñstwie do linii 123

// FIFO obiektowo
//bez remove
//bez printa jesli jest operator wyjœcia
