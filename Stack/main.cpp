/*
 * File: main.cpp
 * --------------
 * Blank C++ project configured to use Stanford cslib and Qt
 */

#include "console.h"
#include "simpio.h"
#include "OurStack.h"
using namespace std;

int main()
{
    OurStack<int> ourstack;
    cout<<"请输入一个ourstack:";
    cin>>ourstack;
    cout<<"您输入的ourstack为:"<<ourstack<<endl;
    cout<<"ourstack.peek()="<<ourstack.peek()<<endl;
    cout<<"ourstack.pop()"<<ourstack.pop()<<endl;
    int value;
    cout<<"请输入push的值：";
    cin>>value;
    ourstack.push(value);
    cout<<"ourstack.push(value)="<<ourstack<<endl;

    OurStack<int> ourstack1;
    cout<<"请再输入一个ourstack1:";
    cin>>ourstack1;
    if(ourstack == ourstack1)
        cout<<"ourstack == ourstack1"<<endl;
    if(ourstack.equals(ourstack1))
        cout<<"ourstack equal to ourstack1"<<endl;

    return 0;
}








