#include <cmath>
#include <cstddef>
#include <iostream>
#include <chrono>
#include <string>
#include <utility>
#include <algorithm>
#include <vector>
#include <set>

using std::cout;
using std::size_t;
using std::string;
using std::vector;
using std::sqrt;

bool is_prime(size_t i)
{
    if (i == 0 || i == 1)
        return false;

    size_t max = size_t(sqrt(i)) + 1;
    for (size_t j = 2; j < max; ++j)
    {
        if (i % j == 0)
        {
            return false;
        }
    }
    return true;
}

std::set<size_t> divisors(size_t i)
{
    std::set<size_t> divisors{ i };
    size_t max = size_t(sqrt(i)) + 1;
    for (size_t j = 2; j < max; ++j)
    {
        if (i % j == 0)
        {
            divisors.insert(j);
            divisors.insert((i / j));
        }
    }
    return divisors;
}

std::pair<size_t, size_t> reduce_fraction(std::pair<size_t, size_t> frac)
{
    size_t top = frac.first;
    size_t bot = frac.second;
    if (bot == 0)
        return { top, bot };

    while (1)
    {
        auto topdivs = divisors(top);
        auto botdivs = divisors(bot);
        bool found_div = false;
        for (auto it = botdivs.crbegin(); it != botdivs.crend(); ++it)
        {
            if (topdivs.count(*it) != 0)
            {
                top /= *it;
                bot /= *it;
                found_div = true;
                break;
            }
        }
        if (!found_div)
            break;
    }
    return { top,bot };
}

bool compare_fraction(const std::pair<size_t, size_t>& lhs,
    const std::pair<size_t, size_t>& rhs)
{
    return double(lhs.first) / lhs.second < double(rhs.first) / rhs.second;
}

size_t count_range_fractions(size_t limit)
{
    ++limit;
    std::set<std::pair<size_t, size_t>, decltype(compare_fraction)*>
        fractions(compare_fraction);

    fractions.insert({ 1,3 });
    fractions.insert({ 1,2 });

    size_t count = 0;
    size_t min = 0;
    size_t max = 0;
    for (size_t d = 2; d != limit; ++d)
    {
        if (++count == 100)
        {
            cout << d << '\n';
            count = 0;
        }
        min = d > 3 ? size_t(d * 0.333333) - 1: 1;
        max = d/2 + 1;
        bool prime = is_prime(d);
        bool two = d % 2 == 0;
        bool three = d % 3 == 0;
        bool five = d % 5 == 0;
        for (size_t n = min; n < max; ++n)
        {
            if (double(n) / d > 0.5)
                break;
            if (double(n) / d < (1.0 / 3))
                continue;
            if (n == 1 || prime)
            {
                fractions.insert({ n, d });
                continue;
            }
            if (two && n % 2 == 0 || three && n % 3 == 0 || five && n % 5 == 0)
                continue;
            if (is_prime(n))
            {
                fractions.insert({n, d});
                continue;
            }

            fractions.insert(reduce_fraction({ n,d }));
        }
    }
    return fractions.size() - 2; // remove 1/2 and 1/3
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = count_range_fractions(12000);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n' <<
        std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}