#include <cmath>
#include <cstddef>
#include <iostream>
#include <chrono>
#include <string>
#include <utility>
#include <vector>
#include <deque>

// sum of the digits of 2 to the 1000

using std::cout;
using std::size_t;
using std::string;

static size_t base_n = 0;

std::pair<string,size_t> imed_sum(string* biggies, size_t j, 
                                    size_t offset, size_t origcarry)
{
    size_t sum = 0;
    size_t carry = 0;
    for (size_t i = 0; i != base_n; ++i)
    {
        sum += size_t(biggies[i][(10 * j) + 9 + offset] - '0')
            + ((biggies[i][(10 * j) + 8 + offset] - '0') * 10)
            + ((biggies[i][(10 * j) + 7 + offset] - '0') * 100)
            + ((biggies[i][(10 * j) + 6 + offset] - '0') * 1000)
            + ((biggies[i][(10 * j) + 5 + offset] - '0') * 10000)
            + ((biggies[i][(10 * j) + 4 + offset] - '0') * 100000)
            + ((biggies[i][(10 * j) + 3 + offset] - '0') * 1000000)
            + ((biggies[i][(10 * j) + 2 + offset] - '0') * 10000000)
            + ((biggies[i][(10 * j) + 1 + offset] - '0') * 100000000)
            + (size_t(biggies[i][(10 * j) + 0 + offset] - '0') * 1000000000);
    }
    string sumstring = std::to_string(sum + origcarry);
    if (sumstring.size() > 10)
    {
        size_t digits = sumstring.size() - 10;
        string carrystring = sumstring.substr(0, digits);
        sumstring = sumstring.substr(digits, 10);
        for (int i = 0; i < digits; ++i)
        {
            size_t zeroes = digits == 1 ? 0 : digits - i - 1;
            carry += (size_t(carrystring[i] - '0') *
                (std::stoi(std::string("1") + std::string(zeroes, '0'))));
        }
    }
    else if (sumstring.size() < 10)
    {
        size_t n = 10 - sumstring.size();
        sumstring.insert(0, n, '0');
    }
    
    return {sumstring, carry};
}

std::pair<string, size_t> imed_sum_small(string* biggies, size_t digits,
                                        size_t origcarry)
{
    size_t sum = origcarry;
    size_t carry = 0;
    for (size_t j = 0; j != base_n; ++j)
    {
        for (int i = 0; i < digits; ++i)
        {
            size_t zeroes = digits == 1 ? 0 : digits - i - 1;
            sum += (size_t(biggies[j][i] - '0') *
                (std::stoi(std::string("1") + std::string(zeroes, '0'))));
        }
    }
    string sumstring = std::to_string(sum);
    if (sumstring.size() < digits)
    {
        size_t n = digits - sumstring.size();
        sumstring.insert(0, n, '0');
    }
    return {sumstring, carry};
}

string single(const string& big)
{
    std::deque<string> digits(big.size()/10 + 1);
    size_t carry = 0;
    
    size_t sz = big.size();
    int rounds = sz / 10;
    bool is_mul_ten = sz % 10 == 0;
    string* biggies = new string[base_n]{};
    for (size_t i = 0; i != base_n; ++i)
    {
        biggies[i] = big;
    }
    if (is_mul_ten)
    { 
        
        for (int i = rounds; i > 0; --i)
        { 
            std::pair<string, size_t> inter = imed_sum(biggies, i-1, 0, carry);
            digits.push_front(inter.first);
            carry = inter.second;
        }
    }
    else
    {
        size_t remaining = sz % 10;
        //sum 

        for (int i = rounds; i > 0; --i)
        {
            std::pair<string, size_t> inter = imed_sum(biggies, i-1, remaining, carry);
            digits.push_front(inter.first);
            carry = inter.second;
        }
        std::pair<string, size_t> inter = imed_sum_small(biggies, remaining, carry);
        digits.push_front(inter.first);
        carry = inter.second;
    }

    

    string ret = carry != 0 ? std::to_string(carry) : "";
    for (const auto& s : digits)
        ret += s;
    delete[] biggies;
    return ret;
    // add rightmost 10, add carry to next 10 digits to the left

}

string power_digits(size_t base, size_t exp)
{
    base_n = base;
    string initial = std::to_string(base);
    for (size_t i = 1; i != exp; ++i)
    {
        initial = single(initial);
    }
    return initial;
}



int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    string bob = power_digits(2,1000);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << '\n';

    size_t digitsum = 0;
    for (const auto& ch : bob)
    {
        digitsum += (ch - '0');
    }
    cout << digitsum << '\n';

    cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start) << '\n';
}