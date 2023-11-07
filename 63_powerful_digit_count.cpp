#include <cmath>
#include <cstddef>
#include <iostream>
#include <chrono>
#include <string>
#include <utility>
#include <vector>
#include <deque>

using std::cout;
using std::size_t;
using std::string;
using std::vector;
using std::deque;

using digits = std::pair<vector<size_t>, vector<size_t>>;

static size_t base_n = 0;
static bool same_size = true;
static bool first_big = false;

std::pair<size_t, size_t> imed_sum_single(digits& biggies, size_t j, size_t origcarry)
{
    size_t sum = 0;
    size_t carry = 0;
    for (size_t i = 0; i != base_n; ++i)
    {
        sum += biggies.second[j];
    }
    sum += origcarry;
    size_t num_digits = 0;
    if (sum > 1000000000000000)
    {
        size_t working = sum;
        working /= 1000000000000000;
        ++num_digits;
        carry = working % 10;

        while (working >= 10)
        {
            working /= 10;
            carry += (working % 10) * size_t(pow(10, num_digits));
            ++num_digits;
        }
    }
    else if (sum == 1000000000000000)
    {
        carry = 1;
        sum = 0;
    }
    sum %= 1000000000000000;
    return { sum, carry };
}


std::pair<size_t, size_t> imed_sum_small_single(digits& biggies, size_t origcarry)
{
    size_t sum = origcarry;
    size_t carry = 0;
    for (size_t j = 0; j != base_n; ++j)
    {
        sum += biggies.second.back();
    }
    size_t num_digits = 0;
    if (sum >= 1000000000000000)
    {
        size_t working = sum;
        working /= 1000000000000000;
        carry = working % 10;
        ++num_digits;
        while (working >= 10)
        {
            working /= 10;
            carry += (working % 10) * size_t(pow(10, num_digits));
            ++num_digits;
        }
    }
    sum %= 1000000000000000;
    return { sum, carry };
}

void single(digits& biggies)
{
    vector<size_t> bigworking;
    bigworking.reserve(biggies.second.size() + 2);
    size_t carry = 0;
    size_t sz = biggies.second.size();
    bool is_mul_ten = true;
    if (biggies.second.back() < 100000000000000)
        is_mul_ten = false;
    if (is_mul_ten)
    {
        for (int i = 0; i != sz; ++i)
        {
            std::pair<size_t, size_t> inter = imed_sum_single(biggies, i, carry);
            bigworking.push_back(inter.first);
            carry = inter.second;
        }
    }
    else
    {
        if (sz > 1)
        {
            for (int i = 0; i != sz - 1; ++i)
            {
                std::pair<size_t, size_t> inter = imed_sum_single(biggies, i, carry);
                bigworking.push_back(inter.first);
                carry = inter.second;
            }
        }
        std::pair<size_t, size_t> inter = imed_sum_small_single(biggies, carry);
        bigworking.push_back(inter.first);
        carry = inter.second;
    }
    if (carry != 0)
    {
        bigworking.push_back(carry);
    }
    biggies.second = bigworking;
}

std::vector<unsigned char> get_rdigits(size_t n)
{
    std::vector<unsigned char> digits;
    digits.reserve(16);

    digits.push_back(n % 10);
    size_t working = n;
    while (working > 9)
    {
        working /= 10;
        digits.push_back(working % 10);
    }
    return digits;
}

vector<size_t> big_exp(size_t base, size_t exp)
{
    base_n = base;
    digits biggies;
    biggies.first.reserve(exp + base);
    biggies.second.reserve(exp + base);
    biggies.second.push_back(base_n);
    for (size_t j = 1; j != exp; ++j)
    {
        single(biggies);
    }
    return biggies.second;
}

size_t number_digits(size_t i)
{
    size_t ret = 0;
    while (i > 0)
    {
        i /= 10;
        ++ret;
    }
    return ret;
}

size_t powerful_digit_count(size_t limit)
{
    size_t ret = 0;
    for (size_t n = 1; n != 10; ++n)
    { 
        for (size_t i = 1; i != limit; ++i)
        {
            vector<size_t> digit_blocks = big_exp(n, i);
            size_t digits = digit_blocks.size() == 1 ? 
                number_digits(digit_blocks.back()) :
                    ((digit_blocks.size()- 1) * 15) + number_digits(digit_blocks.back());
            if (digits > i)
                break;
            if (digits == i)
                ++ret;
        }
    }
    return ret;
}    


int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = powerful_digit_count(25);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n' <<
        std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}
