#include <iostream>
#include "include/saylib.h"
#include <array>

using std::vector;
using std::string;
using std::array;

//! Use constexpr here when C++20 is available.
static const array<string, 7>  scales = {"", "thousand", "million", "billion", "trillion", "quadrillion", "quintillion"}; //! Enough to describe std::numeric_limits<int64_t>::max()
static const array<string, 10> digits_text = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
static const array<string, 10> tenths_of_one_text = {"and ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen","eighteen","nineteen"};
static const array<string, 10>  tenths_text = {"", "", "twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety"};


Say::Say(int64_t in)
{
    is_positive = in > 0;
    chunks.reserve(10);
    if (!is_positive)
    {
        //! Use uint64_t to bypass the Say(std::numeric_limits<int64_t>::min()).get_name() cornercase
        uint64_t u_in = static_cast<int64_t>(-1) * in;
        get_chunks(u_in);
    } else {
        get_chunks(in);
    }
}

static inline string digit_to_string(int num)
{
    return digits_text[num];
}

static inline string hundreds(int num)
{
    if (num == 0) return "";
    if (num == 1) return "hundred ";
    return digit_to_string(num) +" hundreds ";
}

static inline string decimals(int num)
{    
    int div10 = num/10;
    if (div10 == 1)
    {
        return tenths_of_one_text[num%10];
    }
    string res = tenths_text[div10];

    //! Checking the second digit
    if (!res.empty() && (num % 10) > 0)
    {
        res += '-';
    }
    res += digit_to_string(num%10);
    return res;
}


static string process_chunk(int num)
{
    int first_digit = num/100;
    return hundreds(first_digit) + decimals(num - (first_digit * 100));
}

static inline string pluralize (int chunk, int i)
{
    if (scales[i].empty()) return "";
    return chunk > 1 ? scales[i] + "s " : scales[i];
}

string Say::get_name()
{
    int n = chunks.size();
    string res = is_positive ? "" : "minus ";
    for (int i = n ; i --> 0;)
    {
        if (chunks[i] == 0) { continue; }
        string aux = process_chunk(chunks[i]);
        //! We don't bound-check on `scales`, but it should be enough for the max values of int64_t, so I guess we're fine.
        res += aux + " " + pluralize(chunks[i], i) + " ";
    }
    return res;
}

void Say::get_chunks(uint64_t input)
{
    while (input >= 100)
    {
        chunks.push_back(input % 1000);
        input /= 1000;
    }
    if ((input % 1000) != 0)
    {
        chunks.push_back(input % 1000);
    }
}
