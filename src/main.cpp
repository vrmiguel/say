#include "include/saylib.h"
#include <iostream>
#include <cstdlib>
#include <limits>

int main()
{
//    for(int i = 0; i < 200000; i++)
//    {
//        std::cout << Say(i).get_name() << '\n';
//    }
    std::cout << Say(std::numeric_limits<int64_t>::min()).get_name() << '\n';

    return  0;
}
