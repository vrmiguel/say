#include <iostream>
#include "include/saylib.h"
#include <array>

using std::vector;
using std::string;
using std::array;

//! Use constexpr here when C++20 is available.
static const array<string, 4>  scales = {"", "thousand", "million", "billion"};
static const array<string, 10> digits_text = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
static const array<string, 10> tenths_of_one_text = {"and ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen","eighteen","nineteen"};
static const array<string, 10>  tenths_text = {"", "", "twenty", "thirty", "fourty", "fifty", "sixty", "seventy", "eighty", "ninety"};


Say::Say(int64_t in)
{
    is_positive = in > 0;
    if (!is_positive)
    {
        in = -in;   //! Make it positive.
    }
    chunks.reserve(10);
    get_chunks(in);
}

static inline string digit_to_string(int num)
{
    if (num <= 10 && num >= 0)
    {
        return digits_text[num];
    } else {
        return ""; //! Should be unreachable
    }
}

static inline string hundreds(int num)
{
    if (num == 0) return "";
    if (num == 1) return "hundred ";
    return digit_to_string(num) +" hundreds ";
}

static inline string decimals(int num)
{
    //! num/10 == first digit of num
    int div10;
    div10 = num/10;
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

string Say::annotate()
{
    int n = chunks.size();
    string res;
    for (int i = n ; i --> 0;)
    {
        if (chunks[i] == 0)
        {
            //n++;
            continue;
        }
        string aux = process_chunk(chunks[i]);
        //! TODO: this blows if if i > scales[i].size()
        res += aux + " " + scales[i] + " ";
    }
    return res;
}

void Say::get_chunks(int64_t input)
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
