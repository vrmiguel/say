#ifndef __SAYLIB_H_
#define __SAYLIB_H_

#include <vector>
#include <cstdint>
#include <string>

class Say{
    //! chunks can be a vector of uint16_t if space is a constraint.
    //! std::vector<int> chunks has shown to be faster in local tests.
    std::vector<int> chunks;
    bool is_positive;
    void get_chunks(uint64_t);
public:
    Say(int64_t);
    std::string get_name();
};

#endif
