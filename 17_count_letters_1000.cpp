#include <map>
#include <string>
#include <vector>
#include <cstddef>
#include <iostream>

using std::map;
using std::vector;
using std::string;
using std::size_t;
using std::cout;

static map<char, vector<unsigned>> numbers = {
    {'0', {0, 0}},
    {'1', {3, 0}},
    {'2', {3, 6}},
    {'3', {5, 6}},
    {'4', {4, 5}},
    {'5', {4, 5}},
    {'6', {3, 5}},
    {'7', {5, 7}},
    {'8', {5, 6}},
    {'9', {4, 6}},
};

static map<string, unsigned> ones = {
    {"10", 3},
    {"11", 6},
    {"12", 6},
    {"13", 8},
    {"14", 8},
    {"15", 7},
    {"16", 7},
    {"17", 9},
    {"18", 8},
    {"19", 8}
};

size_t number_letters(size_t number)
{
    string numstring = std::to_string(number);
    size_t sz = numstring.size();
    size_t retsum = 0;
    if (sz < 5)
    {
        for (size_t i = 1; i <= number; ++i)
        {
            string ns = std::to_string(i);
            if (ns.size() == 4)
            {
                retsum += numbers.at(ns[0])[0] + 8;
                if (i % 1000 != 0)
                    retsum += numbers.at(ns[1])[0] + 7;
                if (i % 100 != 0)
                    retsum += 3;
                if (ns[2] == '1')
                    retsum += ones.at(ns.substr(2, 2));
                else
                {
                    retsum += numbers.at(ns[2])[1] + numbers.at(ns[3])[0];
                }
            }
            if (ns.size() == 3)
            {
                retsum += 7;
                if (i % 100 != 0)
                    retsum += 3;
                retsum += numbers.at(ns[0])[0];
                if (ns[1] == '1')
                    retsum += ones.at(ns.substr(1,2));
                else
                {
                    retsum += numbers.at(ns[1])[1] + numbers.at(ns[2])[0];
                }
            }
            else if (ns.size() == 2)
            {
                
                if (ns[0] == '1')
                    retsum += ones.at(ns.substr(0, 2));
                else
                {
                    retsum += numbers.at(ns[0])[1] + numbers.at(ns[1])[0];
                }
            }
            else if (ns.size() == 1)
            {
                retsum += numbers.at(ns[0])[0];
            }
        }
    }
    return retsum;
}


int main()
{
    cout << number_letters(1000);
}