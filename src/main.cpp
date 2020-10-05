#include "include/saylib.h"
#include <iostream>
#include <cstdlib>

int main()
{
    for(unsigned long int i = 0; i < 200000; i++)
    {
        std::cout << Say(i).annotate() << '\n';
    }
    return  0;
}
