#include <iostream>
#include "include/saylib.h"

using std::vector;
using std::string;

static const vector<string> scales = {"", "thousand", "million", "billion"};


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

string digit_to_string(int num)
{
    switch (num)
    {
    case 9:
        return "nine";
    case 8:
        return "eight";
    case 7:
        return "seven";
    case 6:
        return "six";
    case 5:
        return "five";
    case 4:
        return "four";
    case 3:
        return "three";
    case 2:
        return "two";
    case 1:
        return "one";
    default: return "";
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
        switch (num%10)
        {
        case 0:
            res = "and ten";
            break;
        case 1:
            res = "eleven";
            break;
        case 2:
            res = "twelve";
            break;
        case 3:
            res = "thirteen";
            break;
        case 4:
            res = "fourteen";
            break;
        case 5:
            res = "fifteen";
            break;
        case 6:
            res = "sixteen";
            break;
        case 7:
            res = "seventeen";
            break;
        case 8:
            res = "eighteen";
            break;
        case 9:
            res = "nineteen";
            break;
        default: exit(0);   //! Unreachable
        }
        return res; //! In this case, we already checked the last digit.
        break;
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
