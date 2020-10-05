#ifndef __SAYLIB_H_
#define __SAYLIB_H_

#include <vector>
#include <cstdint>
#include <string>

class Say{
    std::vector<int> chunks;
    bool is_positive;
    void get_chunks(uint64_t);
public:
    Say(int64_t);
    std::string get_name();
};

#endif
