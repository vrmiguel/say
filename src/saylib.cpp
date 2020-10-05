#include <iostream>
#include "include/saylib.h"
#include <array>

using std::vector;
using std::string;
using std::array;

//! Use constexpr here when C++20 is available.
static const array<string, 4> scales = {"", "thousand", "million", "billion"};
static const array<string, 10> digits_text = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
static const array<string, 10> decimals_text = {"and ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen","eighteen","nineteen"};



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
    string res;
    //! num/10 == first digit of num
    switch(num/10)
    {
    case 9:
        res = "ninety";
        break;
    case 8:
        res = "eighty";
        break;
    case 7:
        res = "seventy";
        break;
    case 6:
        res = "sixty";
        break;
    case 5:
        res = "fifty";
        break;
    case 4:
        res = "fourty";
        break;
    case 3:
        res = "thirty";
        break;
    case 2:
        res = "twenty";
        break;
    case 1:
        return decimals_text[num%10]; //! In this case, we already checked the last digit.
        break;  //! Unneeded break?
    default: break;
    }

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
