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

std::set<size_t> divisors(size_t i)
{
    std::set<size_t> divisors{i};
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
    return double(lhs.first)/lhs.second < double(rhs.first) / rhs.second;
}

std::pair<size_t, size_t> ordered_fractions(size_t limit)
{
    std::set<std::pair<size_t, size_t>, decltype(compare_fraction)*> 
        fractions(compare_fraction);

    fractions.insert({3,7});
    fractions.insert({428,999});

    size_t count = 0;
    size_t min = 0;
    size_t max = 0;
    size_t dmin = limit < 1000000 ? limit - 50 : size_t(limit * .99999);
    for (size_t d = limit; d > dmin; --d)
    {
        min = size_t(d * .4);
        max = size_t(d/2.0);
        for (size_t n = min; n < max; ++n)
        {
            if (double(n)/d > double(3)/7)
                break;
            if (compare_fraction({n, d},*--fractions.find({3,7})))
                continue;
            fractions.insert(reduce_fraction({n,d}));
        }
    }
    auto it = fractions.find({3,7});
    return *--it;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    std::pair<size_t, size_t> bob = ordered_fractions(1000000);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob.first << '/' << bob.second << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n' <<
        std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}