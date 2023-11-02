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

std::pair<size_t, size_t> imed_sum_dual(digits& biggies, size_t j, size_t origcarry)
{
    size_t sum = 0;
    size_t carry = 0;
    sum += biggies.first[j] + biggies.second[j] + origcarry;
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
        std::pair<size_t, size_t>
            inter = imed_sum_small_dual(biggies, carry, sizegap);

        bigworking.push_back(inter.first);
        carry = inter.second;
    }
    if (carry != 0)
    {
        bigworking.push_back(carry);
    }
    biggies.first = bigworking;
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

vector<size_t> self_sum_digits(size_t exp)
{
    exp += 1;
    digits biggies;
    biggies.first.reserve(exp);
    biggies.second.reserve(exp);
    size_t count = 1;
    biggies.first.push_back(1);
    for (size_t i = 2; i != exp; ++i)
    {
        base_n = i;
        biggies.second.push_back(i);
        for (size_t j = 1; j != i; ++j)
        {
            single(biggies);
        }
        base_n = 2;
        dual(biggies);
        biggies.second.clear();
        if (++count == 10)
        {
            count = 0;
            cout << i << '\n';
        }
    }
    for (size_t i = 0; i != biggies.first.size() - 1; ++i)
    {
        if (biggies.first[i] < 100000000000000)
            biggies.first[i + 1] *= 10;
    }
    return biggies.first;
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


int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    vector<size_t> bob = self_sum_digits(1000);

    auto finish = std::chrono::high_resolution_clock::now();

    for (int i = bob.size() - 1; i >= 0; --i)
    {
        cout << bob[i];
    }
    cout << '\n';

    //size_t sz = bob[0].size();
    //cout << bob[0].substr(sz - 10) << '\n';

    cout << std::chrono::duration_cast<std::chrono::microseconds>(finish - start) << '\n';
    cout << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start) << '\n';

}

// with deque and 100 digits, 522 ms-ish average
// with reserved vectors and 100 digits, 10-digit blocks, 55 ms average
// with reserved vectors and 100 digits, 15-digit blocks, 39 ms average