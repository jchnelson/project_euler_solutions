#include <cmath>
#include <cstddef>
#include <iostream>
#include <chrono>
#include <string>
#include <utility>
#include <vector>
#include <deque>
#include <set>

using std::cout;
using std::size_t;
using std::string;
using std::vector;
using std::deque;
using std::sqrt;
using std::abs;

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
    bool is_mul_fifteen = true;
    if (biggies.second.back() < 100000000000000 ||
        biggies.first.back() < 100000000000000)
        is_mul_fifteen = false;
    if (is_mul_fifteen && same_size)
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
        if (sizegap != 0 || sz < 2) // this might be wrong
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

void single(digits& biggies)
{
    vector<size_t> bigworking;
    bigworking.reserve(biggies.second.size() + 2);
    size_t carry = 0;
    size_t sz = biggies.second.size();
    bool is_mul_fifteen = true;
    if (biggies.second.back() < 100000000000000)
        is_mul_fifteen = false;
    if (is_mul_fifteen)
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

size_t sum_block_digits(size_t i)
{
    size_t ret = 0;
    while (i > 0)
    {
        ret += i % 10;
        i /= 10;
    }
    return ret;
}

size_t e_convergents(size_t limit)
{
    // 2;1,2,1,1,4,1,1,6,1, ??  1,8,1,1,10
    limit -= 3; // we start on round 3
    size_t biground = 4;
    size_t roundcount = 0;
    // 2, 3, 8/3
    digits working;

    working.first.reserve(20);
    working.second.reserve(20);

    vector<size_t> prevtop;
    vector<size_t> prevbot;
    vector<size_t> currtop;
    vector<size_t> currbot;
    vector<size_t> temptop;
    vector<size_t> tempbot;

    prevtop.reserve(20);
    prevbot.reserve(20);
    currtop.reserve(20);
    currbot.reserve(20);
    temptop.reserve(20);
    tempbot.reserve(20);

    prevtop.push_back(3);
    prevbot.push_back(1);
    currtop.push_back(8);
    currbot.push_back(3);
    for (size_t i = 0; i != limit; ++i)
    {

        temptop = currtop;
        tempbot = currbot;
        if (++roundcount == 3)
        {
            base_n = biground;
            working.second = temptop;
            single(working);
            working.first = prevtop;
            dual(working);
            currtop = working.first;

            working.second = tempbot;
            single(working);
            working.first = prevbot;
            dual(working);
            currbot = working.first;

            roundcount = 0;
            biground += 2;

        }
        else
        {
            working.first = currtop;
            working.second = prevtop;
            dual(working);
            currtop = working.first;


            working.first = currbot;
            working.second = prevbot;
            dual(working);
            currbot = working.second;
            
        }
        prevtop = temptop;
        prevbot = tempbot;
    }
    size_t ret = 0;

    for (const auto& block : currtop)
    {
        ret += sum_block_digits(block);
    }

    return ret;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = e_convergents(100);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n' <<
        std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}