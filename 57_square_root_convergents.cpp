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

std::pair<size_t, size_t> imed_sum_dual(digits& biggies, size_t j, size_t origcarry)
{
    size_t sum = origcarry;
    size_t carry = 0;
    sum += biggies.first[j] + biggies.second[j];
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

std::pair<size_t, size_t> imed_sum_small_dual(digits& biggies, size_t origcarry,
    size_t sizegap)
{
    size_t sum = origcarry;
    size_t carry = 0;
    if (same_size)
        sum += biggies.first.back() + biggies.second.back();
    else if (first_big)
    {
        for (auto it = biggies.first.end() - sizegap; it != biggies.first.end(); ++it)
            sum += *it;
    }
    else
    {
        for (auto it = biggies.second.end() - sizegap; it != biggies.second.end(); ++it)
            sum += *it;
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

void dual(digits& biggies)
{
    vector<size_t> bigworking;
    bigworking.reserve(biggies.second.size() + 2);
    size_t carry = 0;
    same_size = biggies.second.size() == biggies.first.size();
    first_big = biggies.second.size() < biggies.first.size();
    size_t sz = first_big ? biggies.first.size() : biggies.second.size();
    size_t sizegap = same_size ? 0 : first_big ? biggies.first.size() -
        biggies.second.size() : biggies.second.size() - biggies.first.size();
    bool is_mul_ten = true;
    if (biggies.second.back() < 100000000000000 ||
        biggies.first.back() < 100000000000000)
        is_mul_ten = false;
    if (is_mul_ten && same_size)
    {

        for (int i = 0; i != sz; ++i)
        {
            std::pair<size_t, size_t> inter = imed_sum_dual(biggies, i, carry);
            bigworking.push_back(inter.first);
            carry = inter.second;
        }
    }
    else
    {
        if (sz > 1)
        {
            for (int i = 0; i != sz - sizegap; ++i)
            {
                std::pair<size_t, size_t>
                    inter = imed_sum_dual(biggies, i, carry);

                bigworking.push_back(inter.first);
                carry = inter.second;
            }
        }
        if (sizegap != 0 || sz < 2)
        { 
            std::pair<size_t, size_t>
                inter = imed_sum_small_dual(biggies, carry, sizegap);

            bigworking.push_back(inter.first);
            carry = inter.second;
        }
    }
    if (carry != 0)
    {
        bigworking.push_back(carry);
    }
    biggies.first = bigworking;
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

size_t square_root_convergents(size_t iterations)
{
    digits biggies;
    biggies.first.reserve(40);
    biggies.second.reserve(40);
    biggies.first.push_back(3);
    biggies.second.push_back(2);

    size_t retcount = 0;
    iterations += 1;
    for (size_t i = 2; i != iterations; ++i)
    {

        dual(biggies);
        auto temp = biggies.first;
        dual(biggies);
        biggies.second = temp;

        size_t firstdigits = biggies.first.size() > 1 ? 
            (biggies.first.size() - 1) * 15 + get_rdigits(biggies.first.back()).size() :
            get_rdigits(biggies.first[0]).size();
        size_t seconddigits = biggies.second.size() > 1 ?
            (biggies.second.size() - 1) * 15 + get_rdigits(biggies.second.back()).size() :
            get_rdigits(biggies.second[0]).size();
        if (firstdigits > seconddigits)
            ++retcount;
    }
    return retcount;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = square_root_convergents(1000);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n' <<
        std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}