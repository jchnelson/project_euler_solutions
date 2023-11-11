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

std::set<size_t> prime_divisors(size_t i)
{
    std::set<size_t> divisors{};
    size_t max = size_t(sqrt(i)) + 1;
    for (size_t j = 2; j < max; ++j)
    {
        if (i % j == 0)
        {
            if (is_prime(j))
                divisors.insert(j);
            if (is_prime(i / j))
                divisors.insert((i / j));
        }
    }
    return divisors;
}


size_t rel_primes(size_t n, const std::set<size_t>& pdivisors)
{
    double phi = double(n);
    for (const auto& pf : pdivisors)
    {
        phi *= (1.0 - (1.0 / pf));
    }
    return size_t(phi);
}

size_t count_fractions(size_t limit)
{
    ++limit;
    size_t sum = 0;
    for (size_t d = 2; d != limit; ++d)
    {
        if (is_prime(d))
        {
            sum += d - 1;
            continue;
        }
        else
        {
            auto pdivisors = prime_divisors(d);
            sum += rel_primes(d, pdivisors);
        }
    }
    return sum;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = count_fractions(1000000);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n' <<
        std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}