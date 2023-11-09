#include <cmath>
#include <cstddef>
#include <iostream>
#include <chrono>
#include <string>
#include <utility>
#include <vector>
#include <set>

using std::cout;
using std::size_t;
using std::string;
using std::vector;
using std::sqrt;

static std::set<size_t> n_divisors;


std::set<size_t> divisors(size_t i)
{
    std::set<size_t> divisors{};
    size_t max = size_t(sqrt(i));
    for (size_t j = 2; j <= max; ++j)
    {
        if (i % j == 0)
        {
            divisors.insert(j);
            divisors.insert((i / j));
        }
    }
    return divisors;
}

bool check_divisors(size_t i)
{
    size_t max = size_t(sqrt(i));
    for (size_t j = 2; j <= max; ++j)
    {
        if (i % j == 0)
        {
            if (n_divisors.count(j) != 0 || n_divisors.count(i / j) != 0)
                return false;
        }
    }
    return true;
}

size_t rel_primes(size_t n)
{
    size_t phi = 1;
    size_t max = n/4 + 1;
    for (size_t i = 2; i != max; ++i)
    {
        if (n % i == 0) 
            continue;
        if (check_divisors(i))
        {
            ++phi;
        }
    }
    return phi;
}

size_t totient_max(size_t limit)
{
    ++limit;
    double max_ratio = 0.0;
    size_t ret = 30;

    for (size_t i = 30; i != limit; ++i)
    { 
        if (i % ret != 0)
            continue;

        n_divisors = divisors(i);

        double ratio = double(i) / rel_primes(i);
        if (ratio > max_ratio)
        {
            max_ratio = ratio;
            ret = i;
        }
    }
    return ret;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = totient_max(1000000);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n' <<
        std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}