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
    std::set<size_t> divisors{};
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
            if (is_prime(i/j))
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
        phi *= (1.0 - (1.0/pf));
    }
    return size_t(phi);
}

bool is_permut(size_t cand, size_t orig)
{
    size_t working = orig;
    std::vector<unsigned char> vorig;
    std::vector<unsigned char> vcand;
    vorig.reserve(20);
    vcand.reserve(20);
    while (working > 0)
    {
        vorig.push_back(working % 10);
        working /= 10;
    }
    working = cand;
    while (working > 0)
    {
        vcand.push_back(working % 10);
        working /= 10;
    }
    sort(vorig.begin(), vorig.end());
    sort(vcand.begin(), vcand.end());
    return vorig == vcand;
}

size_t totient_permut(size_t limit)
{
    ++limit;
    double min_ratio = 10.0;
    size_t ret = 0;
    size_t count = 0;
    for (size_t i = 10; i != limit; ++i)
    {    
        if (i % 2 == 0 || i % 3 == 0 || i % 5 == 0 || i % 7 == 0)
            continue;

        bool prime = is_prime(i);

        std::set<size_t> pdivisors;
        if (!prime)
            pdivisors = prime_divisors(i);
        size_t phi = prime ? i - 1 : rel_primes(i, pdivisors);

        if (!is_permut(phi, i))
            continue;

        double ratio = double(i) / phi ;
        if (ratio < min_ratio)
        {
            cout << "new minimum from " << i << '\n';
            min_ratio = ratio;
            ret = i;
        }
    }
    return ret;
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    size_t bob = totient_permut(10000000);

    auto finish = std::chrono::high_resolution_clock::now();

    cout << bob << " in " <<
        std::chrono::duration_cast<std::chrono::microseconds>(finish - start)
        << '\n' <<
        std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';
}
