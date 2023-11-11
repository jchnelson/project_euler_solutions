#include <chrono>
#include <iostream>
#include <set>
#include <map>
#include <cstddef>
#include <utility>
#include <vector>

using std::cout;
using std::size_t;
using std::string;

static std::map<size_t, size_t> chains;


size_t factorial(size_t n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }
    size_t ret = n;
    for (size_t i = n - 1; i != 1; --i)
    {
        ret *= i;
    }
    return ret;
}

size_t digit_factorial(size_t n)
{
    size_t sum = 0;
    size_t working = n;
    while (working > 0)
    {
        sum += factorial(working % 10);
        working /= 10;
    }
    return sum;
}

size_t factorial_chain_length(size_t n)
{
    std::set<size_t> links{n};
    size_t result = n;
    size_t added_count = 0;
    while (1)
    {
        result = digit_factorial(result);
        if (chains.count(result) != 0)
        {
            added_count += chains.at(result);
            break;
        }
        if (!links.insert(result).second)
            break;
    }
    return links.size() + added_count;
}


size_t digit_factorial_chains(size_t limit)
{
    ++limit;
    size_t ret = 0;

    int count = -1;
    for (size_t i = 0; i != limit; ++i)
    {
        if (++count == 20000)
        {
            cout << i << '\n';
            count = 0;
        }
        size_t chain_length = factorial_chain_length(i);
        chains.insert({i, chain_length});
        if (chain_length == 60)
            ++ret;
    }
    return ret;
}


int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = digit_factorial_chains(1000000);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n' <<
        std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}