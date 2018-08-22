#include <iostream>
using namespace std;
extern "C"
void add_func(int a,int b)
{
    cout<<"the result: "<<a+b<<endl;
}
