#include <set>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <chrono>

using std::cout;
using std::size_t;

size_t sum_divisors(size_t i)
{
    std::set<size_t> divisors{ 1 };
    for (size_t j = 2; j <= sqrt(i); ++j)
    {
        if (i % j == 0)
        {
            divisors.insert(j);
            divisors.insert((i / j));
        }
    }
    size_t sum = 0;
    for (const size_t& divisor : divisors)
    {
        sum += divisor;
    }
    return sum;
}

bool abundant(size_t i)
{
    return sum_divisors(i) > i;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    std::set<size_t> abundants{};
    for (size_t i = 12; i != 28124; ++i)
        if (abundant(i))
            abundants.insert(i);

    size_t sum = 0;
    for (size_t i = 0; i != 24; ++i)
    {
        sum += i;
    }
    for (int i = 24; i != 28124; ++i)
    {
        bool is_sum = false;
        for (const auto& abundant : abundants)
        {
            if (abundant < i && abundants.count((i - abundant)) != 0)
            {
                is_sum = true;
                break;
            }
        }
        if (!is_sum)
        {
            sum += i;
        }
    }
    auto finish = std::chrono::high_resolution_clock::now();
    cout << sum << " in " 
        << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start) 
        << '\n';
}
