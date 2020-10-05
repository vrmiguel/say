#include "include/saylib.h"
#include <iostream>
#include <cstdlib>
#include <limits>

int main()
{
    for(int i = 0; i < 200000; i++)
    {
        std::cout << "Say(" << i << "): " << Say(i).get_name() << '\n';
    }
    return  0;
}
