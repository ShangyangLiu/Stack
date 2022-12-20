#ifndef OURSTACK_H
#define OURSTACK_H

#include <string>
#include <iostream>
#include <sstream>
#include "error.h"
using namespace std;


template <typename ValueType>
class OurStack
{
public:
    OurStack();
    ~OurStack();

    OurStack(const OurStack<ValueType>& ourstack);
    OurStack& operator= (const OurStack<ValueType>& ourstack);

    void clear();
    bool equals(const OurStack<ValueType>& ourstack) const;
    bool isEmpty() const;
    const ValueType peek() const;
    ValueType pop();
    void push(const ValueType& value);
    int size() const;
    string toString() const;

    bool operator==(const OurStack& ourstack) const;
    bool operator!=(const OurStack& ourstack) const;

    template <typename T>
    friend ostream& operator<<(ostream& out,const OurStack<T>& stack);

    template <typename T>
    friend istream& operator>>(istream& cin,OurStack<T>& stack);

private:
    ValueType* elements;
    int capacity;
    int numItems;
    static const int INITIAL_CAPACITY = 10;
    void expand();
};


template <typename ValueType>
OurStack<ValueType>:: OurStack()
{
    elements = new ValueType[INITIAL_CAPACITY];
    capacity = INITIAL_CAPACITY;
    numItems = 0;
}


template <typename ValueType>
OurStack<ValueType>:: ~OurStack()
{
    delete[] elements;
}

template <typename ValueType>
OurStack<ValueType>:: OurStack(const OurStack<ValueType>& ourstack)
{
     elements = new ValueType[ourstack.capacity];
     for(int i = 0; i< ourstack.numItems; i++)
     {
         elements[i] = ourstack.elements[i];
     }
     capacity = ourstack.capacity;
     numItems = ourstack.numItems;
}

template <typename ValueType>
OurStack<ValueType>& OurStack<ValueType>:: operator= (const OurStack<ValueType>& ourstack)
{
    if(capacity > ourstack.numItems)
    {
        for(int i = 0; i< ourstack.numItems;i++)
        {
            elements[i] = ourstack.elements[i];
        }
        numItems = ourstack.numItems;
    }
    else
    {
        delete[] elements;
        capacity = max(INITIAL_CAPACITY, ourstack.numItems *2);
        elements = new ValueType[capacity];
        for(int i = 0; i< ourstack.numItems;i++)
        {
            elements[i] = ourstack.elements[i];
        }
        numItems = ourstack.numItems;
    }
}

template <typename ValueType>
void OurStack<ValueType>::push(const ValueType& value)
{
    if(numItems == capacity)
    {
        expand();
    }
    elements[numItems++] = value;
}

template <typename ValueType>
const ValueType OurStack<ValueType>::peek() const
{
    if(isEmpty())
    {
        error("OurStack::peek: Attempting to peek at an empty stack");
    }
    else
        return elements[numItems-1];
}

template <typename ValueType>
ValueType OurStack<ValueType>::pop()
{
    if(isEmpty())
    {
        error("OurStack::pop: Attempting to pop at an empty stack");
    }
    else
        return elements[--numItems];
}

template <typename ValueType>
int OurStack<ValueType>::size() const
{
    return numItems;
}

template <typename ValueType>
void OurStack<ValueType>::clear()
{
    numItems = 0;
}

template <typename ValueType>
bool OurStack<ValueType>::equals(const OurStack<ValueType>& ourstack) const
{
    if(numItems != ourstack.numItems)
        return false;
    else
        for(int i = 0; i < numItems; i++)
        {
            if(elements[i] != ourstack.elements[i])
                return false;
        }
    return true;
}

template <typename ValueType>
bool OurStack<ValueType>::isEmpty() const
{
    return numItems == 0;
}

template <typename ValueType>
bool OurStack<ValueType>::operator==(const OurStack& ourstack) const
{
    return equals(ourstack);
}

template <typename ValueType>
bool OurStack<ValueType>::operator!=(const OurStack& ourstack) const
{
    return !equals(ourstack);
}

template <typename ValueType>
string OurStack<ValueType>::toString() const
{
    ostringstream os;
    os << *this;
    return os.str();
}

template <typename ValueType>
ostream& operator<<(ostream& out,const OurStack<ValueType>& stack)
{
    out<<"{";
    for(int i = 0; i<stack.numItems-1;i++)
    {
        out<<stack.elements[i]<<" , ";
    }
    out<<stack.elements[stack.numItems-1]<<"}";
    return out;
}

template <typename ValueType>
istream& operator>>(istream& cin,OurStack<ValueType>& stack)
{
   char ch='\0';
   cin>>ch;
   if(ch != '{'){
       cin.setstate(ios::failbit);
       return cin;
   }
   stack.clear();
   cin>>ch;
   if (ch!='}')
   {
       cin.unget();
       while (true)
       {
           ValueType elem;
           if (!(cin>>elem))
           {
               cin.setstate(ios_base::failbit);
               return cin;
           }
           stack.push(elem);
           cin>>ch;
           if (ch=='}')
           {
               break;
           }
           if (ch!=','){
               cin.setstate(ios_base::failbit);
               return cin;
           }
       }
   }
   return cin;
}

template <typename ValueType>
void OurStack<ValueType>::expand()
{
    ValueType* temp = new ValueType[2*capacity];
    for(int i = 0; i < numItems; i++)
    {
        temp[i] = elements[i];
    }
    delete[] elements;
    elements = temp;
    capacity = capacity * 2;
}

#endif // OURSTACK_H
